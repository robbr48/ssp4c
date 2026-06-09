#ifndef SSP4C_SSD_SYSTEM_H
#define SSP4C_SSD_SYSTEM_H

#include "ssp4c_public.h"
#include "ssp4c_common.h"

#ifdef __cplusplus
extern "C" {
#endif

SSP4C_DLLAPI int ssp4c_ssd_system_getNumberOfConnectors(ssdSystemHandle *h);
SSP4C_DLLAPI ssdConnectorHandle *ssp4c_ssd_system_getConnectorByIndex(ssdSystemHandle *h, int i);
SSP4C_DLLAPI int ssp4c_ssd_system_getNumberOfComponents(ssdSystemHandle *h);
SSP4C_DLLAPI ssdComponentHandle *ssp4c_ssd_system_getComponentByIndex(ssdSystemHandle *h, int i);
SSP4C_DLLAPI int ssp4c_ssd_system_getNumberOfConnections(ssdSystemHandle *h);
SSP4C_DLLAPI ssdConnectionHandle *ssp4c_ssd_system_getConnectionByIndex(ssdSystemHandle *h, int i);
SSP4C_DLLAPI const char* ssp4c_ssd_system_getName(ssdSystemHandle *h);

#ifdef __cplusplus
}
#endif

#endif // SSP4C_SSD_SYSTEM_H