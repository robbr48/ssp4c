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

SSP4C_DLLAPI const char* ssp4c_ssd_connector_getName(ssdConnectorHandle *h);
SSP4C_DLLAPI ssdConnectorKind ssp4c_ssd_connector_getKind(ssdConnectorHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_connector_getDescription(ssdConnectorHandle *h);
SSP4C_DLLAPI sspDataType ssp4c_ssd_connector_getDatatype(ssdConnectorHandle *h);
SSP4C_DLLAPI const char* ssp4c_ssd_connector_getUnit(ssdConnectorHandle *h);

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


#endif // SSP4CC_H
