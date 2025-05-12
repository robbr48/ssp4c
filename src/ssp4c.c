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

int ssp4c_ssd_component_getNumberOfParameterBindings(ssdComponentHandle *h)
{
    return h->parameterBindings->parameterBindingsCount;
}

ssdParameterBindingHandle *ssp4c_ssd_component_getParameterBindingByIndex(ssdComponentHandle *h, int i)
{
    return &(h->parameterBindings->parameterBindings[i]);
}

int ssp4c_ssd_parameterBindings_getNumberOfParameterBindings(ssdParameterBindingsHandle *h)
{
    return h->parameterBindingsCount;
}

ssdParameterBindingHandle *ssp4c_ssd_parameterBindings_getParameterBindingByIndex(ssdParameterBindingsHandle *h, int i)
{
    return &(h->parameterBindings[i]);
}
