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
    if(ssp->version == sspVersion1) {
        // for(int i=0; i<ssp->fmi1.numberOfVariables; ++i) {
        //     freeDuplicatedConstChar(ssp->fmi1.variables[i].name);
        //     freeDuplicatedConstChar(ssp->fmi1.variables[i].description);
        // }
        // free(ssp->fmi1.variables);
        // freeDuplicatedConstChar(ssp->fmi1.modelName);
        // freeDuplicatedConstChar(ssp->fmi1.modelIdentifier);
        // freeDuplicatedConstChar(ssp->fmi1.guid);
        // freeDuplicatedConstChar(ssp->fmi1.description);
        // freeDuplicatedConstChar(ssp->fmi1.author);
        // freeDuplicatedConstChar(ssp->fmi1.version);
        // freeDuplicatedConstChar(ssp->fmi1.generationTool);
        // freeDuplicatedConstChar(ssp->fmi1.generationDateAndTime);
        // freeDuplicatedConstChar(ssp->fmi1.variableNamingConvention);
    }
    else if(ssp->version == sspVersion2) {
        // for(int i=0; i<ssp->fmi2.numberOfVariables; ++i) {
        //     freeDuplicatedConstChar(ssp->fmi2.variables[i].name);
        //     freeDuplicatedConstChar(ssp->fmi2.variables[i].description);
        // }
        // free(ssp->fmi2.variables);
        // freeDuplicatedConstChar(ssp->fmi2.modelName);
        // freeDuplicatedConstChar(ssp->fmi2.guid);
        // freeDuplicatedConstChar(ssp->fmi2.description);
        // freeDuplicatedConstChar(ssp->fmi2.author);
        // freeDuplicatedConstChar(ssp->fmi2.version);
        // freeDuplicatedConstChar(ssp->fmi2.copyright);
        // freeDuplicatedConstChar(ssp->fmi2.license);
        // freeDuplicatedConstChar(ssp->fmi2.generationTool);
        // freeDuplicatedConstChar(ssp->fmi2.generationDateAndTime);
        // freeDuplicatedConstChar(ssp->fmi2.variableNamingConvention);
        // if(ssp->fmi2.supportsCoSimulation) {
        //     freeDuplicatedConstChar(ssp->fmi2.cs.modelIdentifier);
        // }
        // if(ssp->fmi2.supportsModelExchange) {
        //     freeDuplicatedConstChar(ssp->fmi2.me.modelIdentifier);
        // }
    }

    if(ssp->unzippedLocation) {
        removeDirectoryRecursively(ssp->unzippedLocation, "ssp4c_");
    }

    freeDuplicatedConstChar(ssp->resourcesLocation);
    freeDuplicatedConstChar(ssp->unzippedLocation);
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
