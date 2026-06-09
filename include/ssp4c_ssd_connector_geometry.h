#ifndef SSP4C_SSD_CONNECTOR_GEOMETRY_H
#define SSP4C_SSD_CONNECTOR_GEOMETRY_H

#include "ssp4c_public.h"
#include "ssp4c_common.h"

#ifdef __cplusplus
extern "C" {
#endif

SSP4C_DLLAPI double ssp4c_ssd_connectorGeometry_getX(ssdConnectorGeometryHandle *h);
SSP4C_DLLAPI double ssp4c_ssd_connectorGeometry_getY(ssdConnectorGeometryHandle *h);

#ifdef __cplusplus
}
#endif


#endif //SSP4C_SSD_CONNECTOR_GEOMETRY_H
