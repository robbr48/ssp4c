#ifndef SSP4C_SSD_ELEMENT_GEOMETRY_H
#define SSP4C_SSD_ELEMENT_GEOMETRY_H

#include "ssp4c_public.h"
#include "ssp4c_common.h"

#ifdef __cplusplus
extern "C" {
#endif

SSP4C_DLLAPI double ssp4c_ssd_elementGeometry_getX1(ssdElementGeometryHandle *h);
SSP4C_DLLAPI double ssp4c_ssd_elementGeometry_getY1(ssdElementGeometryHandle *h);
SSP4C_DLLAPI double ssp4c_ssd_elementGeometry_getX2(ssdElementGeometryHandle *h);
SSP4C_DLLAPI double ssp4c_ssd_elementGeometry_getY2(ssdElementGeometryHandle *h);
SSP4C_DLLAPI double ssp4c_ssd_elementGeometry_getRotation(ssdElementGeometryHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_elementGeometry_getIconSource(ssdElementGeometryHandle *h);
SSP4C_DLLAPI double ssp4c_ssd_elementGeometry_getIconRotation(ssdElementGeometryHandle *h);
SSP4C_DLLAPI bool ssp4c_ssd_elementGeometry_getIconFlip(ssdElementGeometryHandle *h);
SSP4C_DLLAPI bool ssp4c_ssd_elementGeometry_getIconFixedAspectRatio(ssdElementGeometryHandle *h);

SSP4C_DLLAPI void ssp4c_ssd_elementGeometry_setX1(ssdElementGeometryHandle *h, double value);
SSP4C_DLLAPI void ssp4c_ssd_elementGeometry_setY1(ssdElementGeometryHandle *h, double value);
SSP4C_DLLAPI void ssp4c_ssd_elementGeometry_setX2(ssdElementGeometryHandle *h, double value);
SSP4C_DLLAPI void ssp4c_ssd_elementGeometry_setY2(ssdElementGeometryHandle *h, double value);
SSP4C_DLLAPI void ssp4c_ssd_elementGeometry_setRotation(ssdElementGeometryHandle *h, double value);
SSP4C_DLLAPI void ssp4c_ssd_elementGeometry_setIconSource(ssdElementGeometryHandle *h, const char* value);
SSP4C_DLLAPI void ssp4c_ssd_elementGeometry_setIconRotation(ssdElementGeometryHandle *h, double value);
SSP4C_DLLAPI void ssp4c_ssd_elementGeometry_setIconFlip(ssdElementGeometryHandle *h, bool value);
SSP4C_DLLAPI void ssp4c_ssd_elementGeometry_setIconFixedAspectRatio(ssdElementGeometryHandle *h, bool value);

#ifdef __cplusplus
}
#endif


#endif // SSP4C_SSD_ELEMENT_GEOMETRY_H
