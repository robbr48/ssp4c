#ifndef SSP4C_PRIVATE_H
#define SSP4C_PRIVATE_H

#include <stdbool.h>
#include <stdint.h>

#include "ezxml/ezxml.h"
#include "ssp4c_public.h"

struct ssdElementGeometryHandle {
    ezxml_t xml;
    sspHandle *ssp;
};

struct ssvParameterHandle {
    ezxml_t xml;
    sspHandle *ssp;
};

struct ssvParameterSetHandle {
    ezxml_t xml;
    sspHandle *ssp;
    int parameterCount;
    ssvParameterHandle *parameters;
};

struct ssdParameterValuesHandle {
    ezxml_t xml;
    sspHandle *ssp;
    ssvParameterSetHandle *parameterSet;
};

struct sscMapEntryHandle {
    ezxml_t xml;
    sspHandle *ssp;
    bool boolSource;
    bool boolTarget;
    int intSource;
    int intTarget;
    const char* enumSource;
    const char* enumTarget;
};

struct sscMappingTransformHandle {
    ezxml_t xml;
    sspHandle *ssp;
    sscMappingTransform type;
    double factor;
    double offset;
    int mapEntryCount;
    sscMapEntryHandle *mapEntries;
};

struct ssmParameterMappingEntryHandle {
    ezxml_t xml;
    sspHandle *ssp;
    sscMappingTransformHandle *transform;

};

struct ssmParameterMappingHandle {
    ezxml_t xml;
    sspHandle *ssp;
    int mappingEntryCount;
    ssmParameterMappingEntryHandle *mappingEntries;
};

struct ssdParameterMappingHandle {
    ezxml_t xml;
    sspHandle *ssp;
    ssmParameterMappingHandle *parameterMapping;
};

struct ssdParameterBindingHandle {
    ezxml_t xml;
    sspHandle *ssp;
    ssdParameterValuesHandle *parameterValues;
    ssdParameterMappingHandle *parameterMapping;
};

struct ssdParameterBindingsHandle {
    ezxml_t xml;
    sspHandle *ssp;
    int parameterBindingsCount;
    ssdParameterBindingHandle *parameterBindings;
};

struct ssdConnectorHandle {
    ezxml_t xml;
    sspHandle *ssp;
};

struct ssdConnectorsHandle {
    ezxml_t xml;
    sspHandle *ssp;
    int connectorsCount;
    ssdConnectorHandle *connectors;
};

struct ssdComponentHandle {
    ezxml_t xml;
    sspHandle *ssp;
    ssdConnectorsHandle *connectors;
    ssdElementGeometryHandle *geometry;
    ssdParameterBindingsHandle* parameterBindings;
};

struct ssdComponentsHandle {
    ezxml_t xml;
    sspHandle *ssp;
    int componentsCount;
    ssdComponentHandle *components;
};

struct ssdHandle {
    ezxml_t xml;
    sspHandle *ssp;
    const char* filename;
    ssdConnectorsHandle *connectors;
    ssdComponentsHandle *components;
};

struct sspHandle {
    sspVersion version;
    bool unzippedLocationIsTemporary;
    const char* unzippedLocation;

    int ssdCount;
    ssdHandle *ssds;

    void** allocatedPointers;
    int numAllocatedPointers;
};

#endif // SSP4C_PUBLIC_H
