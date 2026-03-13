#define FMI4C_H_INTERNAL_INCLUDE
#include "ssp4c.h"
#include "ssp4c_utils.h"
#include "ssp4c_xml_parsers.h"

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
    ssp->ssds = mallocAndRememberPointer(ssp, sizeof(ssdHandle)*(ssp->ssdCount+1));
    for(int i=0; i<ssp->ssdCount; ++i) {
        ssdHandle ssd;
        ssd.filename = duplicateAndRememberString(ssp, files[i]);
        parseSsd(ssp, &ssd, files[i]);
        ssp->ssds[i] = ssd;
    }

    int resourceCount = 0;

    //Create path to resources folder
    char resourcesPath[FILENAME_MAX] = {0};
    strncat(resourcesPath, ssp->unzippedLocation, FILENAME_MAX - strlen(resourcesPath) - 1);
    strncat(resourcesPath, "/resources", FILENAME_MAX - strlen(resourcesPath) - 1);

    printf("Looking for resources in: %s\n", resourcesPath);
    ssp->ssvCount = 0;    
    char** resourceFiles = listFiles(ssp, resourcesPath, &resourceCount);
    printf("Found %d resources\n", resourceCount);

    // First, count .ssv files
    ssp->ssvCount = 0;
    for(int i = 0; i < resourceCount; ++i) {
        if(hasFileExtension(resourceFiles[i], ".ssv")) {
            ssp->ssvCount++;
        }
    }
    if(ssp->ssvCount > 0) {
        ssp->ssvs = mallocAndRememberPointer(ssp, sizeof(ssvParameterSetHandle) *(ssp->ssvCount+1));
    }

    // Then, parse and assign
    int ssvIndex = 0;
    for(int i = 0; i < resourceCount; ++i) {
        if(hasFileExtension(resourceFiles[i], ".ssv")) {
            ssvParameterSetHandle ssv;
            ssv.filename = duplicateAndRememberString(ssp, resourceFiles[i]);
            parseSsv(ssp, &ssv, resourceFiles[i]);
            ssp->ssvs[ssvIndex] = ssv;
            printf("First parameter: %s\n", ezxml_attr(ssv.parameters[0].xml, "name"));
            ssvIndex++;
        }
    }

    printf("First parameter again: %s\n", ezxml_attr(ssp->ssvs[0].parameters[0].xml, "name"));

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

const char* ssp4c_getUnzippedLocation(sspHandle *h)
{
    return h->unzippedLocation;
}

int ssp4c_getNumberOfSsds(sspHandle *h)
{
    return h->ssdCount;
}

ssdHandle *ssp4c_getSsdByIndex(sspHandle *h, int i)
{
    return &h->ssds[i];
}

SSP4C_DLLAPI int ssp4c_getNumberOfSsvs(sspHandle *h)
{
    return h->ssvCount;
}

SSP4C_DLLAPI ssvParameterSetHandle *ssp4c_getSsvByIndex(sspHandle *h, int i)
{
    return &h->ssvs[i];
}

