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

//! @brief Returns FMI version of SSP
//! @param ssp SSP handle
//! @returns Version of the SSP
sspVersion ssp4c_getSspVersion(sspHandle *ssp)
{
    return ssp->version;
}



//! @brief Free SSP dll
//! @param ssp SSP handle
void ssp4c_freeSsp(sspHandle *ssp)
{
    if(ssp->unzippedLocation) {
        removeDirectoryRecursively(ssp->unzippedLocation, "ssp4c_");
    }

    //Free all allocated memory
    for(int i=0; i<ssp->numAllocatedPointers; ++i) {
        free(ssp->allocatedPointers[i]);
    }

    free(ssp->allocatedPointers);
    free(ssp);
}

int ssp4c_getNumberOfSsds(sspHandle *ssp)
{
    return ssp->ssdCount;
}

ssdHandle *ssp4c_getSsdByIndex(sspHandle *ssp, int i)
{
    return &ssp->ssds[i];
}

const char *ssp4c_getSsdFileName(ssdHandle *ssd)
{
    return ssd->filename;
}

const char *ssp4c_getSsdName(ssdHandle *ssd)
{
    return ssd->name;
}

const char *ssp4c_getSsdVersion(ssdHandle *ssd)
{
    return ssd->version;
}

const char *ssp4c_getSsdId(ssdHandle *ssd)
{
    return ssd->id;
}

const char *ssp4c_getSsdDescription(ssdHandle *ssd)
{
    return ssd->description;
}

const char *ssp4c_getSsdAuthor(ssdHandle *ssd)
{
    return ssd->author;
}

const char *ssp4c_getSsdFileversion(ssdHandle *ssd)
{
    return ssd->fileversion;
}

const char *ssp4c_getSsdCopyright(ssdHandle *ssd)
{
    return ssd->copyright;
}

const char *ssp4c_getSsdLicense(ssdHandle *ssd)
{
    return ssd->license;
}

const char *ssp4c_getSsdGenerationTool(ssdHandle *ssd)
{
    return ssd->generationTool;
}

const char *ssp4c_getSsdGenerationDateAndTime(ssdHandle *ssd)
{
    return ssd->generationDateAndTime;
}

int ssp4c_getNumberOfSsdConnectors(ssdHandle *ssd)
{
    return ssd->connectorCount;
}

ssdConnectorHandle *ssp4c_getSsdConnectorByIndex(ssdHandle *ssd, int i)
{
    return &ssd->connectors[i];
}

const char* ssp4c_getSsdConnectorName(ssdConnectorHandle *con)
{
    return con->name;
}

ssdConnectorKind ssp4c_getSsdConnectorKind(ssdConnectorHandle *con)
{
    return con->kind;
}

const char* ssp4c_getSsdConnectorDescription(ssdConnectorHandle *con)
{
    return con->description;
}

sspDataType ssp4c_getSsdConnectorDatatype(ssdConnectorHandle *con)
{
    return con->datatype;
}

const char* ssp4c_getSsdConnectorUnit(ssdConnectorHandle *con)
{
    return con->unit;
}


int ssp4c_getNumberOfSsdComponents(ssdHandle* ssd)
{
    return ssd->componentCount;
}

ssdComponentHandle* ssp4c_getSsdComponentByIndex(ssdHandle* ssd, int i)
{
    return &ssd->components[i];
}

const char* ssp4c_getSsdComponentName(ssdComponentHandle* comp)
{
    return comp->name;
}

const char* ssp4c_getSsdComponentType(ssdComponentHandle* comp)
{
    return comp->type;
}

const char* ssp4c_getSsdComponentSource(ssdComponentHandle* comp)
{
    return comp->source;
}

ssdComponentImplementation ssp4c_getSsdComponentImplementation(ssdComponentHandle *comp)
{
    return comp->implementation;
}

int ssp4c_getNumberOfSsdComponentConnectors(ssdComponentHandle* comp)
{
    return comp->connectorCount;
}

ssdConnectorHandle *ssp4c_getSsdComponentConnectorByIndex(ssdComponentHandle *comp, int i)
{
    return &comp->connectors[i];
}

double ssp4c_getSsdComponentGeometryX1(ssdComponentHandle *comp)
{
    return comp->geometry.x1;
}

double ssp4c_getSsdComponentGeometryY1(ssdComponentHandle *comp)
{
    return comp->geometry.y1;
}

double ssp4c_getSsdComponentGeometryX2(ssdComponentHandle *comp)
{
    return comp->geometry.x2;
}

double ssp4c_getSsdComponentGeometryY2(ssdComponentHandle *comp)
{
    return comp->geometry.y2;
}

double ssp4c_getSsdComponentGeometryRotation(ssdComponentHandle *comp)
{
    return comp->geometry.rotation;
}

const char* ssp4c_getSsdComponentGeometryIconSource(ssdComponentHandle *comp)
{
    return comp->geometry.iconSource;
}

double ssp4c_getSsdComponentGeometryIconRotation(ssdComponentHandle *comp)
{
    return comp->geometry.iconRotation;
}

bool ssp4c_getSsdComponentGeometryIconFlip(ssdComponentHandle *comp)
{
    return comp->geometry.iconFlip;
}

bool ssp4c_getSsdComponentGeometryIconFixedAspectRatio(ssdComponentHandle *comp)
{
    return comp->geometry.iconFixedAspectRatio;
}

int ssp4c_getNumberOfSsdComponentParameterBindings(ssdComponentHandle *comp)
{
    return comp->parameterBindingsCount;
}

ssdParameterBindingHandle *ssp4c_getSsdComponentParameterBindingByIndex(ssdComponentHandle *comp, int i)
{
    return &(comp->parameterBindings[i]);
}

const char *ssp4c_getSsdComponentParameterBindingType(ssdParameterBindingHandle *binding)
{
    return binding->type;
}

const char *ssp4c_getSsdComponentParameterBindingSource(ssdParameterBindingHandle *binding)
{
    return binding->source;
}

ssdParameterSourceBase ssp4c_getSsdComponentParameterBindingSourceBase(ssdParameterBindingHandle *binding)
{
    return binding->sourceBase;
}

const char *ssp4c_getSsdComponentParameterBindingPrefix(ssdParameterBindingHandle *binding)
{
    return binding->prefix;
}

ssdParameterSetHandle *ssp4c_getParameterSet(ssdParameterBindingHandle *binding)
{
    return binding->parameterSet;
}

ssdParameterMappingHandle *ssp4c_getParameterMapping(ssdParameterBindingHandle *binding)
{
    return binding->parameterMapping;
}

const char *ssp4c_getParameterSetVersion(ssdParameterSetHandle *set)
{
    return set->version;
}

const char *ssp4c_getParameterSetName(ssdParameterSetHandle *set)
{
    return set->name;
}

const char *ssp4c_getParameterSetId(ssdParameterSetHandle *set)
{
    return set->id;
}

const char *ssp4c_getParameterSetDescription(ssdParameterSetHandle *set)
{
    return set->description;
}

int ssp4c_getNumberOfParameterSetParameters(ssdParameterSetHandle *set)
{
    return set->parameterCount;
}

ssvParameterHandle *ssp4c_getParameterSetParameterByIndex(ssdParameterSetHandle *set, int i)
{
    return &(set->parameters[i]);
}

const char *ssp4c_getParameterName(ssvParameterHandle *parameter)
{
    return parameter->name;
}

const char *ssp4c_getParameterDescription(ssvParameterHandle *parameter)
{
    return parameter->description;
}

const char *ssp4c_getParameterId(ssvParameterHandle *parameter)
{
    return parameter->id;
}

sspDataType ssp4c_getParameterDatatype(ssvParameterHandle *parameter)
{
    return parameter->datatype;
}

const char *ssp4c_getParameterUnit(ssvParameterHandle *parameter)
{
    return parameter->unit;
}

double ssp4c_getParameterRealValue(ssvParameterHandle *parameter)
{
    return parameter->realValue;
}

double ssp4c_getParameterFloat64Value(ssvParameterHandle *parameter)
{
    return parameter->float64Value;
}

float ssp4c_getParameterFloat32Value(ssvParameterHandle *parameter)
{
    return parameter->float32Value;
}

int ssp4c_getParameterIntValue(ssvParameterHandle *parameter)
{
    return parameter->intValue;
}

int64_t ssp4c_getParameterInt64Value(ssvParameterHandle *parameter)
{
    return parameter->int64Value;
}

int32_t ssp4c_getParameterInt32Value(ssvParameterHandle *parameter)
{
    return parameter->int32Value;
}

int16_t ssp4c_getParameterInt16Value(ssvParameterHandle *parameter)
{
    return parameter->int16Value;
}

int8_t ssp4c_getParameterInt8Value(ssvParameterHandle *parameter)
{
    return parameter->int8Value;
}

uint64_t ssp4c_getParameterUInt64Value(ssvParameterHandle *parameter)
{
    return parameter->uint64Value;
}

uint32_t ssp4c_getParameterUInt32Value(ssvParameterHandle *parameter)
{
    return parameter->uint32Value;
}

uint16_t ssp4c_getParameterUInt16Value(ssvParameterHandle *parameter)
{
    return parameter->uint16Value;
}

uint8_t ssp4c_getParameterUInt8Value(ssvParameterHandle *parameter)
{
    return parameter->uint8Value;
}

bool ssp4c_getParameterBooleanValue(ssvParameterHandle *parameter)
{
    return parameter->booleanValue;
}

const char *ssp4c_getParameterStringValue(ssvParameterHandle *parameter)
{
    return parameter->stringValue;
}

const char *ssp4c_getParameterEnumValue(ssvParameterHandle *parameter)
{
    return parameter->enumValue;
}

int ssp4c_getNumberOfEnumerableParameterValues(ssvParameterHandle *parameter)
{
    return parameter->enumValuesCount;
}

const char *ssp4c_getEnumerableParameterValueByIndex(ssvParameterHandle *parameter, int i)
{
    return (parameter->enumValues)[i];
}

const char *ssp4c_getParameterMappingDescription(ssdParameterMappingHandle *mapping)
{
    return mapping->description;
}

const char *ssp4c_getParameterMappingId(ssdParameterMappingHandle *mapping)
{
    return mapping->id;
}

const char *ssp4c_getParameterMappingType(ssdParameterMappingHandle *mapping)
{
    return mapping->type;
}

const char *ssp4c_getParameterMappingSource(ssdParameterMappingHandle *mapping)
{
    return mapping->source;
}

ssdParameterSourceBase ssp4c_getParameterMappingSourceBase(ssdParameterMappingHandle *mapping)
{
    return mapping->sourceBase;
}

ssmParameterMappingHandle *ssp4c_getSsmParameterMapping(ssdParameterMappingHandle *mapping)
{
    return mapping->parameterMapping;
}

const char *ssp4c_getSsmParameterMappingVersion(ssmParameterMappingHandle *mapping)
{
    return mapping->version;
}

const char *ssp4c_getSsmParameterMappingId(ssmParameterMappingHandle *mapping)
{
    return mapping->id;
}

const char *ssp4c_getSsmParameterMappingDescription(ssmParameterMappingHandle *mapping)
{
    return mapping->description;
}

const char *ssp4c_getSsmParameterMappingAuthor(ssmParameterMappingHandle *mapping)
{
    return mapping->author;
}

const char *ssp4c_getSsmParameterMappingFileversion(ssmParameterMappingHandle *mapping)
{
    return mapping->fileversion;
}

const char *ssp4c_getSsmParameterMappingCopyright(ssmParameterMappingHandle *mapping)
{
    return mapping->copyright;
}

const char *ssp4c_getSsmParameterMappingLicense(ssmParameterMappingHandle *mapping)
{
    return mapping->license;
}

const char *ssp4c_getSsmParameterMappingGenerationTool(ssmParameterMappingHandle *mapping)
{
    return mapping->generationTool;
}

const char *ssp4c_getSsmParameterMappingGenerationDateAndTime(ssmParameterMappingHandle *mapping)
{
    return mapping->generationDateAndTime;
}

int ssp4c_getNumberOfParameterMappingEntries(ssmParameterMappingHandle *mapping)
{
    return mapping->mappingEntryCount;
}

ssmParameterMappingEntryHandle *ssp4c_getSsmParameterMappingEntryByIndex(ssmParameterMappingHandle *mapping, int i)
{
    return &(mapping->mappingEntries[i]);
}

const char *ssp4c_getId(ssmParameterMappingEntryHandle *entry)
{
    return entry->id;
}

const char *ssp4c_getDescription(ssmParameterMappingEntryHandle *entry)
{
    return entry->description;
}

const char *ssp4c_getSource(ssmParameterMappingEntryHandle *entry)
{
    return entry->source;
}

const char *ssp4c_getTarget(ssmParameterMappingEntryHandle *entry)
{
    return entry->target;
}

bool ssp4c_getSuppressUnitConveresion(ssmParameterMappingEntryHandle *entry)
{
    return entry->suppressUnitConveresion;
}

sscMappingTransformHandle *getMappingTransform(ssmParameterMappingEntryHandle *entry)
{
    return entry->transform;
}

sscMappingTransform ssp4c_getMappingTransformType(sscMappingTransformHandle *transform)
{
    return transform->type;
}

double ssp4c_getMappingTransformFactor(sscMappingTransformHandle *transform)
{
    return transform->factor;
}

double ssp4c_getMappingTransformOffset(sscMappingTransformHandle *transform)
{
    return transform->offset;
}

int ssp4c_getNumberOfMapEntries(sscMappingTransformHandle *transform)
{
    return transform->mapEntryCount;
}

sscMapEntryHandle *ssp4c_getMapEntryByIndex(sscMappingTransformHandle *transform, int i)
{
    return &(transform->mapEntries[i]);
}

bool ssp4c_getMappingTransformBoolSource(sscMapEntryHandle *entry)
{
    return entry->boolSource;
}

bool ssp4c_getMappingTransformBoolTarget(sscMapEntryHandle *entry)
{
    return entry->boolTarget;
}

int ssp4c_getMappingTransformIntSource(sscMapEntryHandle *entry)
{
    return entry->intSource;
}

int ssp4c_getMappingTransformIntTarget(sscMapEntryHandle *entry)
{
    return entry->intTarget;
}

const char *ssp4c_getMappingTransformEnumSource(sscMapEntryHandle *entry)
{
    return entry->enumSource;
}

const char *ssp4c_getMappingTransformEnumTarget(sscMapEntryHandle *entry)
{
    return entry->enumTarget;
}
