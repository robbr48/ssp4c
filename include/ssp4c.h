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

SSP4C_DLLAPI int ssp4c_getNumberOfSsdConnectors(ssdHandle *ssd);
SSP4C_DLLAPI ssdConnectorHandle *ssp4c_getSsdConnectorByIndex(ssdHandle *ssd, int i);
SSP4C_DLLAPI const char* ssp4c_getSsdConnectorName(ssdConnectorHandle *con);
SSP4C_DLLAPI ssdConnectorKind ssp4c_getSsdConnectorKind(ssdConnectorHandle *con);
SSP4C_DLLAPI const char* ssp4c_getSsdConnectorDescription(ssdConnectorHandle *con);
SSP4C_DLLAPI sspDataType ssp4c_getSsdConnectorDatatype(ssdConnectorHandle *con);
SSP4C_DLLAPI const char* ssp4c_getSsdConnectorUnit(ssdConnectorHandle *con);

SSP4C_DLLAPI int ssp4c_getNumberOfSsdComponents(ssdHandle* ssd);
SSP4C_DLLAPI ssdComponentHandle* ssp4c_getSsdComponentByIndex(ssdHandle* ssd, int i);
SSP4C_DLLAPI const char* ssp4c_getSsdComponentName(ssdComponentHandle* comp);
SSP4C_DLLAPI const char* ssp4c_getSsdComponentType(ssdComponentHandle* comp);
SSP4C_DLLAPI const char* ssp4c_getSsdComponentSource(ssdComponentHandle* comp);
SSP4C_DLLAPI ssdComponentImplementation ssp4c_getSsdComponentImplementation(ssdComponentHandle* comp);
SSP4C_DLLAPI int ssp4c_getNumberOfSsdComponentConnectors(ssdComponentHandle* comp);
SSP4C_DLLAPI ssdConnectorHandle *ssp4c_getSsdComponentConnectorByIndex(ssdComponentHandle *comp, int i);

SSP4C_DLLAPI double ssp4c_getSsdComponentGeometryX1(ssdComponentHandle *comp);
SSP4C_DLLAPI double ssp4c_getSsdComponentGeometryY1(ssdComponentHandle *comp);
SSP4C_DLLAPI double ssp4c_getSsdComponentGeometryX2(ssdComponentHandle *comp);
SSP4C_DLLAPI double ssp4c_getSsdComponentGeometryY2(ssdComponentHandle *comp);
SSP4C_DLLAPI double ssp4c_getSsdComponentGeometryRotation(ssdComponentHandle *comp);
SSP4C_DLLAPI const char* ssp4c_getSsdComponentGeometryIconSource(ssdComponentHandle *comp);
SSP4C_DLLAPI double ssp4c_getSsdComponentGeometryIconRotation(ssdComponentHandle *comp);
SSP4C_DLLAPI bool ssp4c_getSsdComponentGeometryIconFlip(ssdComponentHandle *comp);
SSP4C_DLLAPI bool ssp4c_getSsdComponentGeometryIconFixedAspectRatio(ssdComponentHandle *comp);

SSP4C_DLLAPI int ssp4c_getNumberOfSsdComponentParameterBindings(ssdComponentHandle *comp);
SSP4C_DLLAPI ssdParameterBindingHandle *ssp4c_getSsdComponentParameterBindingByIndex(ssdComponentHandle *comp, int i);
SSP4C_DLLAPI const char* ssp4c_getSsdComponentParameterBindingType(ssdParameterBindingHandle *binding);
SSP4C_DLLAPI const char* ssp4c_getSsdComponentParameterBindingSource(ssdParameterBindingHandle *binding);
SSP4C_DLLAPI ssdParameterBindingsSourceBase ssp4c_getSsdComponentParameterBindingSourceBase(ssdParameterBindingHandle *binding);
SSP4C_DLLAPI const char* ssp4c_getSsdComponentParameterBindingPrefix(ssdParameterBindingHandle *binding);

const char* type;
const char* source;
ssdParameterBindingsSourceBase sourceBase;
const char* prefix;

#ifdef __cplusplus
}
#endif


#endif // SSP4CC_H
