#include "ssp4c_private.h"
#define FMI4C_H_INTERNAL_INCLUDE
#include "ssp4c.h"
#include "ssp4c_utils.h"

#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#ifndef _WIN32
#include "ssp4c.h"
#include <dlfcn.h>
#include <unistd.h>
#include <sys/stat.h>
#endif


//! @brief Loads the specified SSP file
//! First unzips the SSP, then parses modelDescription.xml, and then loads all required FMI functions.
//! @param ssp SSP handle
//! @returns Handle to SSP
sspHandle *ssp4c_loadSsp(const char *sspfile)
{
    const char* unzipLocation = generateTempPath();
    if(!unzipSsp(sspfile, unzipLocation)) {
        return NULL;
    }
    sspHandle *ssp = ssp4c_loadUnzippedSsp_internal(unzipLocation, true);
    ssp->unzippedLocationIsTemporary = true;
    ssp->ssdCount = 0;
    char** files = listFiles(ssp,ssp->unzippedLocation,&ssp->ssdCount);
    //printf("Looking for files in %s\n",ssp->unzippedLocation);
    //printf("Found %i files\n",ssdCount);
    ssp->ssds = mallocAndRememberPointer(ssp, sizeof(ssdHandle)*(ssp->ssdCount+1));
    for(int i=0; i<ssp->ssdCount; ++i) {
        //printf("%s\n",files[i]);
        ssdHandle ssd;
        ssd.filename = duplicateAndRememberString(ssp, files[i]);
        parseSsd(ssp, &ssd, files[i]);
        ssp->ssds[i] = ssd;
    }

    return ssp;
}

bool ssp4c_saveSsp(sspHandle *h, const char *sspfile)
{

    char cwd[FILENAME_MAX];
#ifdef _WIN32
    _getcwd(cwd, sizeof(char)*FILENAME_MAX);
#else
    getcwd(cwd, sizeof(char)*FILENAME_MAX);
#endif
    chdir(h->unzippedLocation);
    for(int i=0; i<h->ssdCount; ++i) {
        FILE* fp = fopen(h->ssds[i].filename, "w");
        if (fp == NULL)
        {
            printf("Could not open file for writing: %s\n", h->ssds[i].filename);
            return false;
        }
        else
        {
            const char* xmlText = ezxml_toxml(h->ssds[i].xml);
            fprintf(fp, xmlText);
            freeDuplicatedConstChar(xmlText);
            fclose(fp);
        }
    }
    chdir(cwd);

    if(!zipSsp(sspfile, h->unzippedLocation)) {
        printf("Zip failed\n");
        return false;
    }

    return true;
}

//! @brief Returns FMI version of SSP
//! @param h SSP handle
//! @returns Version of the SSP
sspVersion ssp4c_getSspVersion(sspHandle *h)
{
    return h->version;
}



//! @brief Free SSP dll
//! @param h SSP handle
void ssp4c_freeSsp(sspHandle *h)
{
    //Free all loaded XML objects
    for(int i=0; i<h->ssdCount; ++i) {
        ezxml_free(h->ssds[i].xml);
    }

    //Remove temporary unzipped location
    if(h->unzippedLocation) {
        removeDirectoryRecursively(h->unzippedLocation, "ssp4c_");
    }

    //Free all allocated memory
    for(int i=0; i<h->numAllocatedPointers; ++i) {
        free(h->allocatedPointers[i]);
    }

    free(h->allocatedPointers);
    free(h);
}

int ssp4c_getNumberOfSsds(sspHandle *h)
{
    return h->ssdCount;
}

ssdHandle *ssp4c_getSsdByIndex(sspHandle *h, int i)
{
    return &h->ssds[i];
}

const char *ssp4c_ssd_getFileName(ssdHandle *h)
{
    return h->filename;
}

const char *ssp4c_ssd_getName(ssdHandle *h)
{
    return h->name;
}

const char *ssp4c_ssd_getVersion(ssdHandle *h)
{
    return h->version;
}

const char *ssp4c_ssd_getId(ssdHandle *h)
{
    return h->id;
}

const char *ssp4c_ssd_getDescription(ssdHandle *h)
{
    return h->description;
}

const char *ssp4c_ssd_getAuthor(ssdHandle *h)
{
    return h->author;
}

const char *ssp4c_ssd_getFileversion(ssdHandle *h)
{
    return h->fileversion;
}

const char *ssp4c_ssd_getCopyright(ssdHandle *h)
{
    return h->copyright;
}

const char *ssp4c_ssd_getLicense(ssdHandle *h)
{
    return h->license;
}

const char *ssp4c_ssd_getGenerationTool(ssdHandle *h)
{
    return h->generationTool;
}

const char *ssp4c_ssd_getGenerationDateAndTime(ssdHandle *h)
{
    return h->generationDateAndTime;
}

int ssp4c_ssd_getNumberOfConnectors(ssdHandle *h)
{
    return h->connectors->connectorsCount;
}

ssdConnectorHandle *ssp4c_ssd_getConnectorByIndex(ssdHandle *ssd, int i)
{
    return &ssd->connectors->connectors[i];
}

const char* ssp4c_ssd_connector_getName(ssdConnectorHandle *h)
{
    return h->name;
}

ssdConnectorKind ssp4c_ssd_connector_getKind(ssdConnectorHandle *h)
{
    return h->kind;
}

const char* ssp4c_ssd_connector_getDescription(ssdConnectorHandle *h)
{
    return h->description;
}

sspDataType ssp4c_ssd_connector_getDatatype(ssdConnectorHandle *h)
{
    return h->datatype;
}

const char* ssp4c_ssd_connector_getUnit(ssdConnectorHandle *h)
{
    return h->unit;
}


int ssp4c_ssd_getNumberOfComponents(ssdHandle* h)
{
    return h->components->componentsCount;
}

ssdComponentHandle *ssp4c_ssd_getComponentByIndex(ssdHandle *h, int i)
{
    return &(h->components->components[i]);
}

const char* ssp4c_ssd_component_getName(ssdComponentHandle *h)
{
    return h->name;
}

const char* ssp4c_ssd_component_getType(ssdComponentHandle *h)
{
    return h->type;
}

const char* ssp4c_ssd_component_getSource(ssdComponentHandle *h)
{
    return h->source;
}

ssdComponentImplementation ssp4c_ssd_component_getImplementation(ssdComponentHandle *h)
{
    return h->implementation;
}

int ssp4c_ssd_component_getNumberOfConnectors(ssdComponentHandle *h)
{
    return h->connectors->connectorsCount;
}

ssdConnectorHandle *ssp4c_ssd_component_getConnectorByIndex(ssdComponentHandle *h, int i)
{
    return &h->connectors->connectors[i];
}

ssdParameterBindingsHandle *ssp4c_ssd_component_getParameterBindings(ssdComponentHandle *h)
{
    return h->parameterBindings;
}

ssdElementGeometryHandle *ssp4c_ssd_component_getElementGeometry(ssdComponentHandle *h)
{
    return &(h->geometry);
}

int ssp4c_ssd_parameterBindings_getNumberOfParameterBindings(ssdParameterBindingsHandle *h)
{
    return h->parameterBindingsCount;
}

ssdParameterBindingHandle *ssp4c_ssd_parameterBindings_getParameterBindingByIndex(ssdParameterBindingsHandle *h, int i)
{
    return &(h->parameterBindings[i]);
}

double ssp4c_ssd_elementGeometry_getX1(ssdElementGeometryHandle *h)
{
    return h->x1;
}

double ssp4c_ssd_elementGeometry_getY1(ssdElementGeometryHandle *h)
{
    return h->y1;
}

double ssp4c_ssd_elementGeometry_getX2(ssdElementGeometryHandle *h)
{
    return h->x2;
}

double ssp4c_ssd_elementGeometry_getY2(ssdElementGeometryHandle *h)
{
    return h->y2;
}

double ssp4c_ssd_elementGeometry_getRotation(ssdElementGeometryHandle *h)
{
    return h->rotation;
}

const char* ssp4c_ssd_elementGeometry_getIconSource(ssdElementGeometryHandle *h)
{
    return h->iconSource;
}

double ssp4c_ssd_elementGeometry_getIconRotation(ssdElementGeometryHandle *h)
{
    return h->iconRotation;
}

bool ssp4c_ssd_elementGeometry_getIconFlip(ssdElementGeometryHandle *h)
{
    return h->iconFlip;
}

bool ssp4c_ssd_elementGeometry_getIconFixedAspectRatio(ssdElementGeometryHandle *h)
{
    return h->iconFixedAspectRatio;
}

void ezxml_set_attr_copy(ezxml_t xml, const char *key, const char *value, sspHandle *ssp) {

    char *key_copy = duplicateAndRememberString(ssp, key);
    char *val_copy = duplicateAndRememberString(ssp, value);
    ezxml_set_attr(xml, key_copy, val_copy);

}

void ssp4c_ssd_elementGeometry_setX1(ssdElementGeometryHandle *h, double value)
{
    h->x1 = value;
    char buf[255];
    sprintf(buf, "%f", value);
    ezxml_set_attr_copy(h->xml, "x1", buf, h->ssp);
}

const char *ssp4c_ssd_parameterBinding_getType(ssdParameterBindingHandle *h)
{
    return h->type;
}

const char *ssp4c_ssd_parameterBinding_getSource(ssdParameterBindingHandle *h)
{
    return h->source;
}

ssdParameterSourceBase ssp4c_ssd_parameterBinding_getSourceBase(ssdParameterBindingHandle *h)
{
    return h->sourceBase;
}

const char *ssp4c_ssd_parameterBinding_getPrefix(ssdParameterBindingHandle *h)
{
    return h->prefix;
}


ssdParameterValuesHandle *ssp4c_ssd_parameterBinding_getParameterValues(ssdParameterBindingHandle *h)
{
    return h->parameterValues;
}

ssdParameterMappingHandle *ssp4c_ssd_parameterSet_getParameterMapping(ssdParameterBindingHandle *h)
{
    return h->parameterMapping;
}

ssvParameterSetHandle *ssp4c_ssd_parameterValues_getParameterSet(ssdParameterValuesHandle *h)
{
    return h->parameterSet;
}

const char *ssp4c_ssd_parameterSet_getVersion(ssvParameterSetHandle *h)
{
    return h->version;
}

const char *ssp4c_ssd_parameterSet_getName(ssvParameterSetHandle *h)
{
    return h->name;
}

const char *ssp4c_ssd_parameterSet_getId(ssvParameterSetHandle *h)
{
    return h->id;
}

const char *ssp4c_ssd_parameterSet_getDescription(ssvParameterSetHandle *h)
{
    return h->description;
}

int ssp4c_ssd_parameterSet_getNumberOfParameters(ssvParameterSetHandle *h)
{
    return h->parameterCount;
}

ssvParameterHandle *ssp4c_ssd_parameterSet_getParameterByIndex(ssvParameterSetHandle *h, int i)
{
    return &(h->parameters[i]);
}

const char *ssp4c_ssv_parameter_getName(ssvParameterHandle *h)
{
    return h->name;
}

const char *ssp4c_ssv_parameter_getDescription(ssvParameterHandle *h)
{
    return h->description;
}

const char *ssp4c_ssv_parameter_getId(ssvParameterHandle *h)
{
    return h->id;
}

sspDataType ssp4c_ssv_parameter_getDatatype(ssvParameterHandle *h)
{
    return h->datatype;
}

const char *ssp4c_ssv_parameter_getUnit(ssvParameterHandle *h)
{
    return h->unit;
}

double ssp4c_ssv_parameter_getRealValue(ssvParameterHandle *h)
{
    return h->realValue;
}

double ssp4c_ssv_parameter_getFloat64Value(ssvParameterHandle *h)
{
    return h->float64Value;
}

float ssp4c_ssv_parameter_getFloat32Value(ssvParameterHandle *h)
{
    return h->float32Value;
}

int ssp4c_ssv_parameter_getIntValue(ssvParameterHandle *h)
{
    return h->intValue;
}

int64_t ssp4c_ssv_parameter_getInt64Value(ssvParameterHandle *h)
{
    return h->int64Value;
}

int32_t ssp4c_ssv_parameter_getInt32Value(ssvParameterHandle *h)
{
    return h->int32Value;
}

int16_t ssp4c_ssv_parameter_getInt16Value(ssvParameterHandle *h)
{
    return h->int16Value;
}

int8_t ssp4c_ssv_parameter_getInt8Value(ssvParameterHandle *h)
{
    return h->int8Value;
}

uint64_t ssp4c_ssv_parameter_getUInt64Value(ssvParameterHandle *h)
{
    return h->uint64Value;
}

uint32_t ssp4c_ssv_parameter_getUInt32Value(ssvParameterHandle *h)
{
    return h->uint32Value;
}

uint16_t ssp4c_ssv_parameter_getUInt16Value(ssvParameterHandle *h)
{
    return h->uint16Value;
}

uint8_t ssp4c_ssv_parameter_getUInt8Value(ssvParameterHandle *h)
{
    return h->uint8Value;
}

bool ssp4c_ssv_parameter_getBooleanValue(ssvParameterHandle *h)
{
    return h->booleanValue;
}

const char *ssp4c_ssv_parameter_getStringValue(ssvParameterHandle *h)
{
    return h->stringValue;
}

const char *ssp4c_ssv_parameter_getEnumValue(ssvParameterHandle *h)
{
    return h->enumValue;
}

int ssp4c_ssv_parameter_getNumberOfEnumerationValues(ssvParameterHandle *h)
{
    return h->enumValuesCount;
}

const char *ssp4c_ssv_parameter_getEnumerationValueByIndex(ssvParameterHandle *h, int i)
{
    return (h->enumValues)[i];
}

const char *ssp4c_ssd_parameterMapping_getDescription(ssdParameterMappingHandle *h)
{
    return h->description;
}

const char *ssp4c_ssd_parameterMapping_getId(ssdParameterMappingHandle *h)
{
    return h->id;
}

const char *ssp4c_ssd_parameterMapping_getType(ssdParameterMappingHandle *h)
{
    return h->type;
}

const char *ssp4c_ssd_parameterMapping_getSource(ssdParameterMappingHandle *h)
{
    return h->source;
}

ssdParameterSourceBase ssp4c_ssd_parameterMapping_getSourceBase(ssdParameterMappingHandle *h)
{
    return h->sourceBase;
}

ssmParameterMappingHandle *ssp4c_ssd_parameterMapping_getSsmParameterMapping(ssdParameterMappingHandle *h)
{
    return h->parameterMapping;
}

const char *ssp4c_ssm_parameterMapping_getVersion(ssmParameterMappingHandle *h)
{
    return h->version;
}

const char *ssp4c_ssm_parameterMapping_getId(ssmParameterMappingHandle *h)
{
    return h->id;
}

const char *ssp4c_ssm_parameterMapping_getDescription(ssmParameterMappingHandle *h)
{
    return h->description;
}

const char *ssp4c_ssm_parameterMapping_getAuthor(ssmParameterMappingHandle *h)
{
    return h->author;
}

const char *ssp4c_ssm_parameterMapping_getFileversion(ssmParameterMappingHandle *h)
{
    return h->fileversion;
}

const char *ssp4c_ssm_parameterMapping_getCopyright(ssmParameterMappingHandle *h)
{
    return h->copyright;
}

const char *ssp4c_ssm_parameterMapping_getLicense(ssmParameterMappingHandle *h)
{
    return h->license;
}

const char *ssp4c_ssm_parameterMapping_getGenerationTool(ssmParameterMappingHandle *h)
{
    return h->generationTool;
}

const char *ssp4c_ssm_parameterMapping_getGenerationDateAndTime(ssmParameterMappingHandle *h)
{
    return h->generationDateAndTime;
}

int ssp4c_ssm_parameterMapping_getNumberOfMappingEntries(ssmParameterMappingHandle *h)
{
    return h->mappingEntryCount;
}

ssmParameterMappingEntryHandle *ssp4c_ssm_parameterMapping_getMappingEntryByIndex(ssmParameterMappingHandle *h, int i)
{
    return &(h->mappingEntries[i]);
}

const char *ssp4c_ssm_mappingEntry_getId(ssmParameterMappingEntryHandle *h)
{
    return h->id;
}

const char *ssp4c_ssm_mappingEntry_getDescription(ssmParameterMappingEntryHandle *h)
{
    return h->description;
}

const char *ssp4c_ssm_mappingEntry_getSource(ssmParameterMappingEntryHandle *h)
{
    return h->source;
}

const char *ssp4c_ssm_mappingEntry_getTarget(ssmParameterMappingEntryHandle *h)
{
    return h->target;
}

bool ssp4c_ssm_mappingEntry_getSuppressUnitConveresion(ssmParameterMappingEntryHandle *h)
{
    return h->suppressUnitConveresion;
}

sscMappingTransformHandle *ssp4c_ssm_mappingEntry_getSsmMappingTransform(ssmParameterMappingEntryHandle *h)
{
    return h->transform;
}

sscMappingTransform ssp4c_ssc_mapEntry_getType(sscMappingTransformHandle *h)
{
    return h->type;
}

double ssp4c_ssc_mapEntry_getFactor(sscMappingTransformHandle *h)
{
    return h->factor;
}

double ssp4c_ssc_mapEntry_getOffset(sscMappingTransformHandle *h)
{
    return h->offset;
}

int ssp4c_getNumberOfMapEntries(sscMappingTransformHandle *h)
{
    return h->mapEntryCount;
}

sscMapEntryHandle *ssp4c_getMapEntryByIndex(sscMappingTransformHandle *h, int i)
{
    return &(h->mapEntries[i]);
}

bool ssp4c_ssc_mapEntry_getBoolSource(sscMapEntryHandle *h)
{
    return h->boolSource;
}

bool ssp4c_ssc_mapEntry_getBoolTarget(sscMapEntryHandle *h)
{
    return h->boolTarget;
}

int ssp4c_ssc_mapEntry_getIntSource(sscMapEntryHandle *h)
{
    return h->intSource;
}

int ssp4c_ssc_mapEntry_getIntTarget(sscMapEntryHandle *h)
{
    return h->intTarget;
}

const char *ssp4c_ssc_mapEntry_getEnumSource(sscMapEntryHandle *h)
{
    return h->enumSource;
}

const char *ssp4c_ssc_mapEntry_getEnumTarget(sscMapEntryHandle *h)
{
    return h->enumTarget;
}
