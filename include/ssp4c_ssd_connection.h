#ifndef SSP4C_SSD_CONNECTION_H
#define SSP4C_SSD_CONNECTION_H

#include "ssp4c_public.h"
#include "ssp4c_common.h"

#ifdef __cplusplus
extern "C" {
#endif

SSP4C_DLLAPI const char* ssp4c_ssd_connection_getStartElement(ssdConnectionHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_connection_getStartConnector(ssdConnectionHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_connection_getEndElement(ssdConnectionHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_connection_getEndConnector(ssdConnectionHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_connection_getDescription(ssdConnectionHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_connection_getId(ssdConnectionHandle *h);
SSP4C_DLLAPI bool ssp4c_ssd_connection_isSuppressed(ssdConnectionHandle *h);

#ifdef __cplusplus
}
#endif

#endif
