#ifndef SSP4C_TYPES_H
#define SSP4C_TYPES_H

#include <stdbool.h>
#include <stdint.h>

// Types
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

typedef enum { sspVersionUnknown,
               sspVersion1,
               sspVersion2} sspVersion;

typedef struct sspHandle sspHandle;
typedef struct ssdHandle ssdHandle;
typedef struct ssdConnectorHandle ssdConnectorHandle;

#endif // SSP4C_TYPES_H
