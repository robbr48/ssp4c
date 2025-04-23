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
SSP4C_DLLAPI sspVersion ssp4c_getSspVersion(sspHandle *ssp);
SSP4C_DLLAPI sspHandle* ssp4c_loadSsp(const char *sspfile);
SSP4C_DLLAPI void ssp4c_freeSsp(sspHandle* ssp);
SSP4C_DLLAPI const char* ssp4c_getErrorMessages();

SSP4C_DLLAPI int ssp4c_getNumberOfSsds(sspHandle *ssp);
SSP4C_DLLAPI ssdHandle *ssp4c_getSsdByIndex(sspHandle *ssp, int i);

SSP4C_DLLAPI const char* ssp4c_getSsdFileName(ssdHandle *ssd);
SSP4C_DLLAPI const char* ssp4c_getSsdName(ssdHandle *ssd);
SSP4C_DLLAPI const char* ssp4c_getSsdVersion(ssdHandle *ssd);
SSP4C_DLLAPI const char* ssp4c_getSsdId(ssdHandle *ssd);
SSP4C_DLLAPI const char* ssp4c_getSsdDescription(ssdHandle *ssd);
SSP4C_DLLAPI const char* ssp4c_getSsdAuthor(ssdHandle *ssd);
SSP4C_DLLAPI const char* ssp4c_getSsdFileversion(ssdHandle *ssd);
SSP4C_DLLAPI const char* ssp4c_getSsdCopyright(ssdHandle *ssd);
SSP4C_DLLAPI const char* ssp4c_getSsdLicense(ssdHandle *ssd);
SSP4C_DLLAPI const char* ssp4c_getSsdGenerationTool(ssdHandle *ssd);
SSP4C_DLLAPI const char* ssp4c_getSsdGenerationDateAndTime(ssdHandle *ssd);

#ifdef __cplusplus
}
#endif


#endif // SSP4CC_H
