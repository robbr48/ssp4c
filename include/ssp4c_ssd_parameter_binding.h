#ifndef SSP4C_SSD_PARAMETER_BINDING_H
#define SSP4C_SSD_PARAMETER_BINDING_H

#include "ssp4c_public.h"
#include "ssp4c_common.h"

#ifdef __cplusplus
extern "C" {
#endif

SSP4C_DLLAPI const char* ssp4c_ssd_parameterBinding_getType(ssdParameterBindingHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_parameterBinding_getSource(ssdParameterBindingHandle *h);
SSP4C_DLLAPI ssdParameterSourceBase ssp4c_ssd_parameterBinding_getSourceBase(ssdParameterBindingHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_parameterBinding_getPrefix(ssdParameterBindingHandle *h);
SSP4C_DLLAPI ssdParameterValuesHandle *ssp4c_ssd_parameterBinding_getParameterValues(ssdParameterBindingHandle *h);
SSP4C_DLLAPI ssdParameterMappingHandle *ssp4c_ssd_parameterSet_getParameterMapping(ssdParameterBindingHandle *h);

#ifdef __cplusplus
}
#endif

#endif // SSP4C_SSD_PARAMETER_BINDING_H
