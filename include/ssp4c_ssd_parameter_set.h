#ifndef SSP4C_SSD_PARAMETER_SET_H
#define SSP4C_SSD_PARAMETER_SET_H

#include "ssp4c_public.h"
#include "ssp4c_common.h"

#ifdef __cplusplus
extern "C" {
#endif

SSP4C_DLLAPI const char* ssp4c_ssd_parameterSet_getVersion(ssvParameterSetHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_parameterSet_getName(ssvParameterSetHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_parameterSet_getId(ssvParameterSetHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_parameterSet_getDescription(ssvParameterSetHandle *h);
SSP4C_DLLAPI int ssp4c_ssd_parameterSet_getNumberOfParameters(ssvParameterSetHandle *h);
SSP4C_DLLAPI ssvParameterHandle *ssp4c_ssd_parameterSet_getParameterByIndex(ssvParameterSetHandle *h, int i);

#ifdef __cplusplus
}
#endif

#endif // SSP4C_SSD_PARAMETER_SET_H
