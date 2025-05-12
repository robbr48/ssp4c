#ifndef SSP4C_SSM_PARAMETER_MAPPING_H
#define SSP4C_SSM_PARAMETER_MAPPING_H

#include "ssp4c_public.h"
#include "ssp4c_common.h"

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif // SSP4C_SSM_PARAMETER_MAPPING_H
