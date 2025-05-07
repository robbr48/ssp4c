#ifndef SSP4C_PRIVATE_H
#define SSP4C_PRIVATE_H

#include <stdbool.h>
#include <stdint.h>

#include "ezxml/ezxml.h"
#include "ssp4c_public.h"

struct ssdElementGeometryHandle {
    double x1;
    double y1;
    double x2;
    double y2;
    double rotation;
    const char* iconSource;
    double iconRotation;
    bool iconFlip;
    bool iconFixedAspectRatio;
};

struct ssvParameterHandle {
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
    const char* version;
    const char* name;
    const char* id;
    const char* description;

    int parameterCount;
    ssvParameterHandle *parameters;
};

struct ssdParameterValuesHandle {
    ssvParameterSetHandle *parameterSet;
};

struct sscMapEntryHandle {
    bool boolSource;
    bool boolTarget;
    int intSource;
    int intTarget;
    const char* enumSource;
    const char* enumTarget;
};

struct sscMappingTransformHandle {
    sscMappingTransform type;
    double factor;
    double offset;
    int mapEntryCount;
    sscMapEntryHandle *mapEntries;
};

struct ssmParameterMappingEntryHandle {
    const char* id;
    const char* description;
    const char* source;
    const char* target;
    bool suppressUnitConveresion;

    sscMappingTransformHandle *transform;

};

struct ssmParameterMappingHandle {
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
    const char* id;
    const char* description;
    const char* type;
    const char* source;
    ssdParameterSourceBase sourceBase;

    ssmParameterMappingHandle *parameterMapping; //! @todo parse and access functions
};

struct ssdParameterBindingHandle {
    const char* type;
    const char* source;
    ssdParameterSourceBase sourceBase;
    const char* prefix;

    ssdParameterValuesHandle *parameterValues;
    ssdParameterMappingHandle *parameterMapping;
};

struct ssdConnectorHandle {
    const char* name;
    ssdConnectorKind kind;
    const char* description;
    sspDataType datatype;
    const char* unit;
};

struct ssdComponentHandle {
    const char* name;
    const char* type;
    const char* source;
    ssdComponentImplementation implementation;

    int connectorCount;
    ssdConnectorHandle *connectors;

    ssdElementGeometryHandle geometry;

    int parameterBindingsCount;
    ssdParameterBindingHandle* parameterBindings;
};

struct ssdHandle {
    ezxml_t xml;

    const char* filename;
    const char* name;
    const char* version;
    const char* id;
    const char* description;
    const char* author;
    const char* fileversion;
    const char* copyright;
    const char* license;
    const char* generationTool;
    const char* generationDateAndTime;

    int connectorCount;
    ssdConnectorHandle *connectors;

    int componentCount;
    ssdComponentHandle* components;
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
