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

struct ssdConnectorHandle {
    const char* name;           //! @todo Access function
    ssdConnectorKind kind;           //! @todo Access function
    const char* description;    //! @todo Access function
    sspDataType datatype;       //! @todo Access function
    const char* unit;           //! @todo Access function
};
typedef struct ssdConnectorHandle ssdConnectorHandle;

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
