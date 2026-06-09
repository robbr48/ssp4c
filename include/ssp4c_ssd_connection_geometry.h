#ifndef SSP4C_SSD_CONNECTION_GEOMETRY_H
#define SSP4C_SSD_CONNECTION_GEOMETRY_H

#include "ssp4c_public.h"
#include "ssp4c_common.h"

#ifdef __cplusplus
extern "C" {
#endif

SSP4C_DLLAPI double* ssp4c_ssd_connectionGeometry_getPointsX(ssdConnectionGeometryHandle *h, int *n);
SSP4C_DLLAPI double* ssp4c_ssd_connectionGeometry_getPointsY(ssdConnectionGeometryHandle *h, int *n);
SSP4C_DLLAPI void ssp4c_ssd_connectionGeometry_setPointsX(ssdConnectionGeometryHandle *h, const double *points, int n);
SSP4C_DLLAPI void ssp4c_ssd_connectionGeometry_setPointsY(ssdConnectionGeometryHandle *h, const double *points, int n);

#ifdef __cplusplus
}
#endif

#endif // SSP4C_SSD_CONNECTION_GEOMETRY_H
