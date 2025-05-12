#ifndef SSP4C_SSV_PARAMETER_H
#define SSP4C_SSV_PARAMETER_H

#include "ssp4c_public.h"
#include "ssp4c_common.h"

#ifdef __cplusplus
extern "C" {
#endif

SSP4C_DLLAPI const char* ssp4c_ssv_parameter_getName(ssvParameterHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssv_parameter_getDescription(ssvParameterHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssv_parameter_getId(ssvParameterHandle *h);
SSP4C_DLLAPI sspDataType ssp4c_ssv_parameter_getDatatype(ssvParameterHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssv_parameter_getUnit(ssvParameterHandle *h);
SSP4C_DLLAPI double ssp4c_ssv_parameter_getRealValue(ssvParameterHandle *h);
SSP4C_DLLAPI double ssp4c_ssv_parameter_getFloat64Value(ssvParameterHandle *h);
SSP4C_DLLAPI float ssp4c_ssv_parameter_getFloat32Value(ssvParameterHandle *h);
SSP4C_DLLAPI int ssp4c_ssv_parameter_getIntValue(ssvParameterHandle *h);
SSP4C_DLLAPI int64_t ssp4c_ssv_parameter_getInt64Value(ssvParameterHandle *h);
SSP4C_DLLAPI int32_t ssp4c_ssv_parameter_getInt32Value(ssvParameterHandle *h);
SSP4C_DLLAPI int16_t ssp4c_ssv_parameter_getInt16Value(ssvParameterHandle *h);
SSP4C_DLLAPI int8_t ssp4c_ssv_parameter_getInt8Value(ssvParameterHandle *h);
SSP4C_DLLAPI uint64_t ssp4c_ssv_parameter_getUInt64Value(ssvParameterHandle *h);
SSP4C_DLLAPI uint32_t ssp4c_ssv_parameter_getUInt32Value(ssvParameterHandle *h);
SSP4C_DLLAPI uint16_t ssp4c_ssv_parameter_getUInt16Value(ssvParameterHandle *h);
SSP4C_DLLAPI uint8_t ssp4c_ssv_parameter_getUInt8Value(ssvParameterHandle *h);
SSP4C_DLLAPI bool ssp4c_ssv_parameter_getBooleanValue(ssvParameterHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssv_parameter_getStringValue(ssvParameterHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssv_parameter_getEnumValue(ssvParameterHandle *h);
SSP4C_DLLAPI int ssp4c_ssv_parameter_getNumberOfEnumerationValues(ssvParameterHandle *h);
SSP4C_DLLAPI const char *ssp4c_ssv_parameter_getEnumerationValueByIndex(ssvParameterHandle *h, int i);

#ifdef __cplusplus
}
#endif

#endif // SSP4C_SSV_PARAMETER_H
