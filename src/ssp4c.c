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
