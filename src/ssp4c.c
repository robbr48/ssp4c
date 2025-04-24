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

