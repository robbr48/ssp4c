#ifndef SSP4C_SSD_CONNECTOR_H
#define SSP4C_SSD_CONNECTOR_H

#include "ssp4c_public.h"
#include "ssp4c_common.h"

#ifdef __cplusplus
extern "C" {
#endif

SSP4C_DLLAPI const char* ssp4c_ssd_connector_getName(ssdConnectorHandle *h);
SSP4C_DLLAPI ssdConnectorKind ssp4c_ssd_connector_getKind(ssdConnectorHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_connector_getDescription(ssdConnectorHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_connector_getId(ssdConnectorHandle *h);
SSP4C_DLLAPI sspDataType ssp4c_ssd_connector_getDatatype(ssdConnectorHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_connector_getUnit(ssdConnectorHandle *h);

#ifdef __cplusplus
}
#endif

#endif // SSP4C_SSD_CONNECTOR_H
