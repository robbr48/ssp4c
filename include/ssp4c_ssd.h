#ifndef SSP4C_SSD_H
#define SSP4C_SSD_H

#include "ssp4c_public.h"
#include "ssp4c_common.h"

#ifdef __cplusplus
extern "C" {
#endif

SSP4C_DLLAPI const char* ssp4c_ssd_getFileName(ssdHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_getName(ssdHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_getVersion(ssdHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_getId(ssdHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_getDescription(ssdHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_getAuthor(ssdHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_getFileversion(ssdHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_getCopyright(ssdHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_getLicense(ssdHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_getGenerationTool(ssdHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_getGenerationDateAndTime(ssdHandle *h);
SSP4C_DLLAPI int ssp4c_ssd_getNumberOfConnectors(ssdHandle *h);
SSP4C_DLLAPI ssdConnectorHandle *ssp4c_ssd_getConnectorByIndex(ssdHandle *h, int i);
SSP4C_DLLAPI int ssp4c_ssd_getNumberOfComponents(ssdHandle* h);
SSP4C_DLLAPI ssdComponentHandle *ssp4c_ssd_getComponentByIndex(ssdHandle *h, int i);

#ifdef __cplusplus
}
#endif

#endif // SSP4C_SSD_H
