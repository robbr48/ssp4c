#ifndef SSP4CC_H
#define SSP4CC_H

#include "ssp4c_public.h"
#include "ssp4c_common.h"

#ifdef __cplusplus
extern "C" {
#endif

//Public functions
SSP4C_DLLAPI sspVersion ssp4c_getSspVersion(sspHandle *h);
SSP4C_DLLAPI sspHandle* ssp4c_loadSsp(const char *sspfile);
SSP4C_DLLAPI bool ssp4c_saveSsp(sspHandle *h, const char *sspfile);
SSP4C_DLLAPI void ssp4c_freeSsp(sspHandle* h);
SSP4C_DLLAPI const char* ssp4c_getErrorMessages();

SSP4C_DLLAPI int ssp4c_getNumberOfSsds(sspHandle *h);
SSP4C_DLLAPI ssdHandle *ssp4c_getSsdByIndex(sspHandle *h, int i);



#ifdef __cplusplus
}
#endif


#endif // SSP4CC_H
