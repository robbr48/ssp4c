#ifndef SSP4C_SSD_PARAMETER_MAPPING_H
#define SSP4C_SSD_PARAMETER_MAPPING_H

#include "ssp4c_public.h"
#include "ssp4c_common.h"

#ifdef __cplusplus
extern "C" {
#endif

SSP4C_DLLAPI const char* ssp4c_ssd_parameterMapping_getDescription(ssdParameterMappingHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_parameterMapping_getId(ssdParameterMappingHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_parameterMapping_getType(ssdParameterMappingHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_parameterMapping_getSource(ssdParameterMappingHandle *h);
SSP4C_DLLAPI ssdParameterSourceBase ssp4c_ssd_parameterMapping_getSourceBase(ssdParameterMappingHandle *h);
SSP4C_DLLAPI ssmParameterMappingHandle *ssp4c_ssd_parameterMapping_getSsmParameterMapping(ssdParameterMappingHandle *h);

#ifdef __cplusplus
}
#endif

#endif // SSP4C_SSD_PARAMETER_MAPPING_H
