#ifndef SSP4C_SSC_MAP_ENTRY_H
#define SSP4C_SSC_MAP_ENTRY_H

#ifndef SSP4C_H_INTERNAL_INCLUDE
#include "ssp4c_public.h"
#endif
#include "ssp4c_common.h"

#ifdef __cplusplus
extern "C" {
#endif

SSP4C_DLLAPI bool ssp4c_ssc_mapEntry_getBoolSource(sscMapEntryHandle *h);
SSP4C_DLLAPI bool ssp4c_ssc_mapEntry_getBoolTarget(sscMapEntryHandle *h);
SSP4C_DLLAPI int ssp4c_ssc_mapEntry_getIntSource(sscMapEntryHandle *h);
SSP4C_DLLAPI int ssp4c_ssc_mapEntry_getIntTarget(sscMapEntryHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssc_mapEntry_getEnumSource(sscMapEntryHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssc_mapEntry_getEnumTarget(sscMapEntryHandle *h);

#ifdef __cplusplus
extern "C" {
#endif

#endif // SSP4C_SSC_MAP_ENTRY_H
