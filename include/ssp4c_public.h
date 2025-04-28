#ifndef SSP4C_PUBLIH_H
#define SSP4C_PUBLIH_H

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

typedef enum { ssdComponentImplementationAny,
               ssdComponentImplementationCoSimulation,
               ssdComponentImplementationModelExchange,
               ssdComponentImplementationScheduledExecution } ssdComponentImplementation;

typedef enum { ssdParameterBindingsSourceBaseSSD,
               ssdParameterBindingsSourceBaseComponent } ssdParameterBindingsSourceBase;

typedef struct sspHandle sspHandle;
typedef struct ssdHandle ssdHandle;
typedef struct ssdConnectorHandle ssdConnectorHandle;
typedef struct ssdComponentHandle ssdComponentHandle;
typedef struct ssdElementGeometryHandle ssdElementGeometryHandle;
typedef struct ssdParameterBindingHandle ssdParameterBindingHandle;
typedef struct ssvParameterHandle ssvParameterHandle;
typedef struct ssdParameterSetHandle ssdParameterSetHandle;
typedef struct ssmParameterMappingHandle ssmParameterMappingHandle;
typedef struct ssdComponentParameterMappingHandle ssdComponentParameterMappingHandle;

#endif // SSP4C_PUBLIH_H
