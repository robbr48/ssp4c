#ifndef SSP4C_SSM_MAPPING_ENTRY_H
#define SSP4C_SSM_MAPPING_ENTRY_H

#include "ssp4c_public.h"
#include "ssp4c_common.h"

#ifdef __cplusplus
extern "C" {
#endif

SSP4C_DLLAPI const char* ssp4c_ssm_mappingEntry_getId(ssmParameterMappingEntryHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssm_mappingEntry_getDescription(ssmParameterMappingEntryHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssm_mappingEntry_getSource(ssmParameterMappingEntryHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssm_mappingEntry_getTarget(ssmParameterMappingEntryHandle *h);
SSP4C_DLLAPI bool ssp4c_ssm_mappingEntry_getSuppressUnitConveresion(ssmParameterMappingEntryHandle *h);
SSP4C_DLLAPI sscMappingTransformHandle *ssp4c_ssm_mappingEntry_getSsmMappingTransform(ssmParameterMappingEntryHandle *h);

#ifdef __cplusplus
}
#endif

#endif // SSP4C_SSM_MAPPING_ENTRY_H
