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
               sspDataTypeBinary,
               sspDataTypeUnspecified } sspDataType;

typedef enum { ssdConnectorKindInput,
               ssdConnectorKindOutput,
               ssdConnectorKindParameter,
               ssdConnectorKindCalculatedParameter,
               ssdConnectorKindStructuralParameter,
               ssdConnectorKindConstant,
               ssdConnectorKindLocal,
               ssdConnectorKindInout,
               ssdConnectorKindUnspecified } ssdConnectorKind;

typedef enum { sspVersionUnknown,
               sspVersion1,
               sspVersion2} sspVersion;

typedef enum { ssdComponentImplementationAny,
               ssdComponentImplementationCoSimulation,
               ssdComponentImplementationModelExchange,
               ssdComponentImplementationScheduledExecution } ssdComponentImplementation;

typedef enum { ssdParameterSourceBaseSSD,
               ssdParameterSourceBaseComponent } ssdParameterSourceBase;

typedef enum { sscMappingTransformLinear,
               sscMappingTransformBoolean,
               sscMappingTransformInteger,
               sscMappingTransformEnumeration} sscMappingTransform;

typedef struct sspHandle sspHandle;
typedef struct ssdHandle ssdHandle;
typedef struct ssdConnectorHandle ssdConnectorHandle;
typedef struct ssdConnectorsHandle ssdConnectorsHandle;
typedef struct ssdComponentHandle ssdComponentHandle;
typedef struct ssdComponentsHandle ssdComponentsHandle;
typedef struct ssdElementGeometryHandle ssdElementGeometryHandle;
typedef struct ssdParameterBindingHandle ssdParameterBindingHandle;
typedef struct ssdParameterBindingsHandle ssdParameterBindingsHandle;
typedef struct ssvParameterHandle ssvParameterHandle;
typedef struct ssvParameterSetHandle ssvParameterSetHandle;
typedef struct ssdParameterValuesHandle ssdParameterValuesHandle;
typedef struct ssmParameterMappingEntryHandle ssmParameterMappingEntryHandle;
typedef struct ssmParameterMappingHandle ssmParameterMappingHandle;
typedef struct ssdParameterMappingHandle ssdParameterMappingHandle;
typedef struct sscMappingTransformHandle sscMappingTransformHandle;
typedef struct sscMapEntryHandle sscMapEntryHandle;

#endif // SSP4C_PUBLIH_H
