#ifndef SSP4C_UTILS_H
#define SSP4C_UTILS_H

#include "ssp4c_private.h"
#include "ezxml/ezxml.h"


bool parseSsd(sspHandle *ssp, ssdHandle *ssd, const char* path);

const char* getFunctionName(const char* modelName, const char* functionName, char* concatBuffer);

int removeDirectoryRecursively(const char* rootDirPath, const char* expectedDirNamePrefix);

void rememberPointer(sspHandle *ssp, void* ptr);
void* mallocAndRememberPointer(sspHandle *ssp, size_t size);
void *reallocAndRememberPointer(sspHandle *ssp, void *org, size_t size);
char* duplicateAndRememberString(sspHandle *ssp, const char* str);

bool hasFileExtension(const char *filename, const char *extension);
char **listFiles(sspHandle *ssp, const char *path, int *nfiles);

sspHandle *ssp4c_loadUnzippedSsp_internal(const char *unzipLocation, bool unzippedLocationIsTemporary);

bool parseStringAttributeEzXml(ezxml_t element, const char* attributeName, const char** target);
bool parseBooleanAttributeEzXml(ezxml_t element, const char* attributeName, bool* target);
bool parseFloat64AttributeEzXml(ezxml_t element, const char* attributeName, double* target);
bool parseFloat32AttributeEzXml(ezxml_t element, const char* attributeName, float *target);
bool parseInt64AttributeEzXml(ezxml_t element, const char* attributeName, int64_t* target);
bool parseInt32AttributeEzXml(ezxml_t element, const char* attributeName, int32_t* target);
bool parseInt16AttributeEzXml(ezxml_t element, const char *attributeName, int16_t* target);
bool parseInt8AttributeEzXml(ezxml_t element, const char *attributeName, int8_t* target);
bool parseUInt64AttributeEzXml(ezxml_t element, const char* attributeName, uint64_t *target);
bool parseUInt32AttributeEzXml(ezxml_t element, const char* attributeName, uint32_t* target);
bool parseUInt16AttributeEzXml(ezxml_t element, const char *attributeName, uint16_t* target);
bool parseUInt8AttributeEzXml(ezxml_t element, const char *attributeName, uint8_t *target);

const char* generateTempPath();
bool unzipSsp(const char* sspfile, const char* unzipLocation);
bool zipSsp(const char* sspfile, const char* zipLocation);

void freeDuplicatedConstChar(const char* ptr);

//bool parseModelStructureElement(fmi3ModelStructureElement *output, ezxml_t *element);

#endif // SSP4C_UTILS_H
