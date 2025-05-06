#ifndef SSP4CC_H
#define SSP4CC_H

#ifndef SSP4C_H_INTERNAL_INCLUDE
#include "ssp4c_public.h"
#endif

#ifdef _WIN32
#include <direct.h>
#include <windows.h>
#endif

#ifdef _WIN32
#if defined(SSP4C_STATIC)
#define SSP4C_DLLAPI
#elif defined(SSP4C_DLLEXPORT)
#define SSP4C_DLLAPI __declspec(dllexport)
#else
#define SSP4C_DLLAPI __declspec(dllimport)
#endif
#else
#define SSP4C_DLLAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif

//Public functions
SSP4C_DLLAPI sspVersion ssp4c_getSspVersion(sspHandle *h);
SSP4C_DLLAPI sspHandle* ssp4c_loadSsp(const char *sspfile);
SSP4C_DLLAPI void ssp4c_freeSsp(sspHandle* h);
SSP4C_DLLAPI const char* ssp4c_getErrorMessages();

SSP4C_DLLAPI int ssp4c_getNumberOfSsds(sspHandle *h);
SSP4C_DLLAPI ssdHandle *ssp4c_getSsdByIndex(sspHandle *h, int i);

SSP4C_DLLAPI const char* ssp4c_getSsdFileName(ssdHandle *h);
SSP4C_DLLAPI const char* ssp4c_getSsdName(ssdHandle *h);
SSP4C_DLLAPI const char* ssp4c_getSsdVersion(ssdHandle *h);
SSP4C_DLLAPI const char* ssp4c_getSsdId(ssdHandle *h);
SSP4C_DLLAPI const char* ssp4c_getSsdDescription(ssdHandle *h);
SSP4C_DLLAPI const char* ssp4c_getSsdAuthor(ssdHandle *h);
SSP4C_DLLAPI const char* ssp4c_getSsdFileversion(ssdHandle *h);
SSP4C_DLLAPI const char* ssp4c_getSsdCopyright(ssdHandle *h);
SSP4C_DLLAPI const char* ssp4c_getSsdLicense(ssdHandle *h);
SSP4C_DLLAPI const char* ssp4c_getSsdGenerationTool(ssdHandle *h);
SSP4C_DLLAPI const char* ssp4c_getSsdGenerationDateAndTime(ssdHandle *h);

SSP4C_DLLAPI int ssp4c_getNumberOfSsdConnectors(ssdHandle *h);
SSP4C_DLLAPI ssdConnectorHandle *ssp4c_getSsdConnectorByIndex(ssdHandle *h, int i);
SSP4C_DLLAPI const char* ssp4c_getSsdConnectorName(ssdConnectorHandle *h);
SSP4C_DLLAPI ssdConnectorKind ssp4c_getSsdConnectorKind(ssdConnectorHandle *h);
SSP4C_DLLAPI const char* ssp4c_getSsdConnectorDescription(ssdConnectorHandle *h);
SSP4C_DLLAPI sspDataType ssp4c_getSsdConnectorDatatype(ssdConnectorHandle *h);
SSP4C_DLLAPI const char* ssp4c_getSsdConnectorUnit(ssdConnectorHandle *h);
SSP4C_DLLAPI int ssp4c_getNumberOfSsdComponents(ssdHandle* h);
SSP4C_DLLAPI ssdComponentHandle* ssp4c_ssd_getComponentByIndex(ssdHandle* h, int i);

SSP4C_DLLAPI const char* ssp4c_ssd_component_getName(ssdComponentHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_component_getType(ssdComponentHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_component_getSource(ssdComponentHandle *h);
SSP4C_DLLAPI ssdComponentImplementation ssp4c_ssd_component_getImplementation(ssdComponentHandle *h);
SSP4C_DLLAPI int ssp4c_getNumberOfSsdComponentConnectors(ssdComponentHandle *h);
SSP4C_DLLAPI ssdConnectorHandle *ssp4c_ssd_component_getConnectorByIndex(ssdComponentHandle *h, int i);
SSP4C_DLLAPI double ssp4c_ssd_component_getGeometryX1(ssdComponentHandle *h);
SSP4C_DLLAPI double ssp4c_ssd_component_getGeometryY1(ssdComponentHandle *h);
SSP4C_DLLAPI double ssp4c_ssd_component_getGeometryX2(ssdComponentHandle *h);
SSP4C_DLLAPI double ssp4c_ssd_component_getGeometryY2(ssdComponentHandle *h);
SSP4C_DLLAPI double ssp4c_ssd_component_getGeometryRotation(ssdComponentHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_component_getGeometryIconSource(ssdComponentHandle *h);
SSP4C_DLLAPI double ssp4c_ssd_component_getGeometryIconRotation(ssdComponentHandle *h);
SSP4C_DLLAPI bool ssp4c_ssd_component_getGeometryIconFlip(ssdComponentHandle *h);
SSP4C_DLLAPI bool ssp4c_ssd_component_getGeometryIconFixedAspectRatio(ssdComponentHandle *h);
SSP4C_DLLAPI int ssp4c_getNumberOfSsdComponentParameterBindings(ssdComponentHandle *h);
SSP4C_DLLAPI ssdParameterBindingHandle *ssp4c_ssd_component_getParameterBindingByIndex(ssdComponentHandle *h, int i);

SSP4C_DLLAPI const char* ssp4c_ssd_parameterBinding_getType(ssdParameterBindingHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_parameterBinding_getSource(ssdParameterBindingHandle *h);
SSP4C_DLLAPI ssdParameterSourceBase ssp4c_ssd_parameterBinding_getSourceBase(ssdParameterBindingHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_parameterBinding_getPrefix(ssdParameterBindingHandle *h);
SSP4C_DLLAPI ssdParameterValuesHandle *ssp4c_ssd_parameterBinding_getParameterValues(ssdParameterBindingHandle *h);
SSP4C_DLLAPI ssdParameterMappingHandle *ssp4c_ssd_parameterSet_getParameterMapping(ssdParameterBindingHandle *h);

SSP4C_DLLAPI ssvParameterSetHandle *ssp4c_ssd_parameterValues_getParameterSet(ssdParameterValuesHandle *h);


SSP4C_DLLAPI const char* ssp4c_ssd_parameterSet_getVersion(ssvParameterSetHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_parameterSet_getName(ssvParameterSetHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_parameterSet_getId(ssvParameterSetHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_parameterSet_getDescription(ssvParameterSetHandle *h);
SSP4C_DLLAPI int ssp4c_ssd_parameterSet_getNumberOfParameters(ssvParameterSetHandle *h);
SSP4C_DLLAPI ssvParameterHandle *ssp4c_ssd_parameterSet_getParameterByIndex(ssvParameterSetHandle *h, int i);

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

SSP4C_DLLAPI const char* ssp4c_ssd_parameterMapping_getDescription(ssdParameterMappingHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_parameterMapping_getId(ssdParameterMappingHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_parameterMapping_getType(ssdParameterMappingHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_parameterMapping_getSource(ssdParameterMappingHandle *h);
SSP4C_DLLAPI ssdParameterSourceBase ssp4c_ssd_parameterMapping_getSourceBase(ssdParameterMappingHandle *h);

SSP4C_DLLAPI ssmParameterMappingHandle *ssp4c_ssd_parameterMapping_getSsmParameterMapping(ssdParameterMappingHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssm_parameterMapping_getVersion(ssmParameterMappingHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssm_parameterMapping_getId(ssmParameterMappingHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssm_parameterMapping_getDescription(ssmParameterMappingHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssm_parameterMapping_getAuthor(ssmParameterMappingHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssm_parameterMapping_getFileversion(ssmParameterMappingHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssm_parameterMapping_getCopyright(ssmParameterMappingHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssm_parameterMapping_getLicense(ssmParameterMappingHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssm_parameterMapping_getGenerationTool(ssmParameterMappingHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssm_parameterMapping_getGenerationDateAndTime(ssmParameterMappingHandle *h);
SSP4C_DLLAPI int ssp4c_ssm_parameterMapping_getNumberOfMappingEntries(ssmParameterMappingHandle *h);
SSP4C_DLLAPI ssmParameterMappingEntryHandle *ssp4c_ssm_parameterMapping_getMappingEntryByIndex(ssmParameterMappingHandle *h, int i);

SSP4C_DLLAPI const char* ssp4c_ssm_mappingEntry_getId(ssmParameterMappingEntryHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssm_mappingEntry_getDescription(ssmParameterMappingEntryHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssm_mappingEntry_getSource(ssmParameterMappingEntryHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssm_mappingEntry_getTarget(ssmParameterMappingEntryHandle *h);
SSP4C_DLLAPI bool ssp4c_ssm_mappingEntry_getSuppressUnitConveresion(ssmParameterMappingEntryHandle *h);
SSP4C_DLLAPI sscMappingTransformHandle *ssp4c_ssm_mappingEntry_getSsmMappingTransform(ssmParameterMappingEntryHandle *h);

SSP4C_DLLAPI sscMappingTransform ssp4c_ssc_mapEntry_getType(sscMappingTransformHandle *h);
SSP4C_DLLAPI double ssp4c_ssc_mapEntry_getFactor(sscMappingTransformHandle *h);
SSP4C_DLLAPI double ssp4c_ssc_mapEntry_getOffset(sscMappingTransformHandle *h);
SSP4C_DLLAPI int ssp4c_getNumberOfMapEntries(sscMappingTransformHandle *h);
SSP4C_DLLAPI sscMapEntryHandle *ssp4c_getMapEntryByIndex(sscMappingTransformHandle *h, int i);
SSP4C_DLLAPI bool ssp4c_ssc_mapEntry_getBoolSource(sscMapEntryHandle *h);
SSP4C_DLLAPI bool ssp4c_ssc_mapEntry_getBoolTarget(sscMapEntryHandle *h);
SSP4C_DLLAPI int ssp4c_ssc_mapEntry_getIntSource(sscMapEntryHandle *h);
SSP4C_DLLAPI int ssp4c_ssc_mapEntry_getIntTarget(sscMapEntryHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssc_mapEntry_getEnumSource(sscMapEntryHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssc_mapEntry_getEnumTarget(sscMapEntryHandle *h);

#ifdef __cplusplus
}
#endif


#endif // SSP4CC_H
