#ifndef SSP4C_TYPES_H
#define SSP4C_TYPES_H

#include <stdbool.h>
#include <stdint.h>

// Types
typedef enum { sspVersionUnknown,
               sspVersion1,
               sspVersion2} sspVersion;

typedef enum { sspDataTypeReal,
               sspDataTypeFloat64,
               sspDataTypeFloat32,
               sspDataTypeInteger,
               sspDataTypeInt8,
               sspDataTypeUInt8,
               sspDataTypeInt16,
               sspDataTypeUInt16,
               sspDataTypeInt32,
               sspDataTypeUInt32,
               sspDataTypeInt64,
               sspDataTypeUInt64,
               sspDataTypeBoolean,
               sspDataTypeString,
               sspDataTypeEnumeration,
               sspDataTypeBinary } sspDataType;

typedef enum { ssdConnectorKindInput,
               ssdConnectorKindOutput,
               ssdConnectorKindParameter,
               ssdConnectorKindCalculatedParameter,
               ssdConnectorKindStructuralParameter,
               ssdConnectorKindConstant,
               ssdConnectorKindLocal,
               ssdConnectorKindInout,
               ssdConnectorKindUnspecifed } ssdConnectorKind;

typedef enum { ssdComponentImplementationAny,
               ssdComponentImplementationCoSimulation,
               ssdComponentImplementationModelExchange,
               ssdComponentImplementationScheduledExecution } ssdComponentImplementation;

typedef enum { ssdParameterBindingsSourceBaseSSD,
               ssdParameterBindingsSourceBaseComponent } ssdParameterBindingsSourceBase;

typedef enum { ssmMappingTransformLinear,
               ssmMappingTransformBoolean,
               ssmMappingTransformInteger,
               ssmMappingTransformEnumeration} ssmMappingTransform;

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
typedef struct ssdElementGeometryHandle ssdElementGeometryHandle;

struct ssvParameterSetHandle {

};
typedef struct ssvParameterSetHandle ssvParameterSetHandle;

struct ssmMappingTransformHandle {
    ssmMappingTransform type;
    double factor;
    double offset;
    bool boolSource;
    bool booltarget;
    int intSource;
    int intTarget;
    const char* enumSource;
    const char* enumTarget;
};

struct ssmParameterMappingEntryHandle {
    const char* id;
    const char* description;
    const char* source;
    const char* target;
    bool suppressUnitConveresion;


};
typedef struct ssmParameterMappingEntryHandle ssmParameterMappingEntryHandle;

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


};
typedef struct ssmParameterMappingHandle ssmParameterMappingHandle;

struct ssdComponentParameterMappingHandle {
    const char* type;
    const char* source;
    ssdParameterBindingsSourceBase sourceBase;

    ssmParameterMappingHandle parameterMapping;
};
typedef struct ssdComponentParameterMappingHandle ssdComponentParameterMappingHandle;

struct ssdParameterBindingHandle {
    const char* type;
    const char* source;
    ssdParameterBindingsSourceBase sourceBase;
    const char* prefix;

    int parameterSetsCount;
    ssvParameterSetHandle *parameterSets;   //! @todo parse and access functions

    int parameterMappingsCount;
    ssdComponentParameterMappingHandle *parameterMappings;  //! @todo parse and access functions
};
typedef struct ssdParameterBindingHandle ssdParameterBindingHandle;

struct ssdConnectorHandle {
    const char* name;
    ssdConnectorKind kind;
    const char* description;
    sspDataType datatype;
    const char* unit;
};
typedef struct ssdConnectorHandle ssdConnectorHandle;

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
typedef struct ssdComponentHandle ssdComponentHandle;

struct ssdHandle {
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
typedef struct ssdHandle ssdHandle;

struct sspHandle {
    sspVersion version;
    bool unzippedLocationIsTemporary;
    const char* unzippedLocation;
    const char* resourcesLocation;

    int ssdCount;
    ssdHandle *ssds;

    void** allocatedPointers;
    int numAllocatedPointers;
};
typedef struct sspHandle sspHandle;



#endif // SSP4C_TYPES_H
