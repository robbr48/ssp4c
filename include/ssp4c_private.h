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
    const char* name;
    const char* description;
    const char* id;

    sspDataType datatype;
    const char* unit;

    double realValue;
    double float64Value;
    float float32Value;
    int intValue;
    int64_t int64Value;
    int32_t int32Value;
    int16_t int16Value;
    int8_t int8Value;
    uint64_t uint64Value;
    uint32_t uint32Value;
    uint16_t uint16Value;
    uint8_t uint8Value;
    bool booleanValue;
    const char* stringValue;
    const char* enumValue;
    int enumValuesCount;
    const char** enumValues;

};

struct ssvParameterSetHandle {
    ezxml_t xml;
    sspHandle *ssp;
    const char* version;
    const char* name;
    const char* id;
    const char* description;

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
    const char* id;
    const char* description;
    const char* source;
    const char* target;
    bool suppressUnitConveresion;

    sscMappingTransformHandle *transform;

};

struct ssmParameterMappingHandle {
    ezxml_t xml;
    sspHandle *ssp;
    const char* version;
    const char* id;
    const char* description;
    const char* author;
    const char* fileversion;
    const char* copyright;
    const char* license;
    const char* generationTool;
    const char* generationDateAndTime;

    int mappingEntryCount;
    ssmParameterMappingEntryHandle *mappingEntries;
};

struct ssdParameterMappingHandle {
    ezxml_t xml;
    sspHandle *ssp;
    const char* id;
    const char* description;
    const char* type;
    const char* source;
    ssdParameterSourceBase sourceBase;

    ssmParameterMappingHandle *parameterMapping; //! @todo parse and access functions
};

struct ssdParameterBindingHandle {
    ezxml_t xml;
    sspHandle *ssp;
    const char* type;
    const char* source;
    ssdParameterSourceBase sourceBase;
    const char* prefix;

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
