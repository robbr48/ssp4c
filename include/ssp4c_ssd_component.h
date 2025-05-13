#ifndef SSP4C_SSD_COMPONENT_H
#define SSP4C_SSD_COMPONENT_H

#include "ssp4c_public.h"
#include "ssp4c_common.h"

#ifdef __cplusplus
extern "C" {
#endif

SSP4C_DLLAPI const char* ssp4c_ssd_component_getName(ssdComponentHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_component_getType(ssdComponentHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_component_getSource(ssdComponentHandle *h);
SSP4C_DLLAPI ssdComponentImplementation ssp4c_ssd_component_getImplementation(ssdComponentHandle *h);
SSP4C_DLLAPI int ssp4c_ssd_component_getNumberOfConnectors(ssdComponentHandle *h);
SSP4C_DLLAPI ssdConnectorHandle *ssp4c_ssd_component_getConnectorByIndex(ssdComponentHandle *h, int i);
SSP4C_DLLAPI ssdElementGeometryHandle *ssp4c_ssd_component_getElementGeometry(ssdComponentHandle *h);
SSP4C_DLLAPI int ssp4c_ssd_component_getNumberOfParameterBindings(ssdComponentHandle *h);
SSP4C_DLLAPI ssdParameterBindingHandle *ssp4c_ssd_component_getParameterBindingByIndex(ssdComponentHandle *h, int i);

#ifdef __cplusplus
}
#endif

#endif // SSP4C_SSD_COMPONENT_H
