#ifndef SSP4C_XML_PARSERS_H
#define SSP4C_XML_PARSERS_H

#include <ezxml/ezxml.h>
#include "ssp4c_public.h"

bool parseSsd(sspHandle *ssp, ssdHandle *ssd, const char* path);
bool parseSsdConnectorsElement(ezxml_t element, ssdConnectorsHandle* h, sspHandle *ssp);
bool parseSsdConnectorElement(ezxml_t element, ssdConnectorHandle *h, sspHandle *ssp);
bool parseSsdComponentsElement(ezxml_t element, ssdComponentsHandle* h, sspHandle *ssp);
bool parseSsdComponentElement(ezxml_t element, ssdComponentHandle* h, sspHandle *ssp);
bool parseSsdElementGeometryElement(ezxml_t element, ssdElementGeometryHandle *h, sspHandle *ssp);
bool parseSsdParameterBindingsElement(ezxml_t element, ssdParameterBindingsHandle* h, sspHandle *ssp);
bool parseSsdParameterBindingElement(ezxml_t element, ssdParameterBindingHandle *h, sspHandle *ssp);
bool parseSsdParameterValuesElement(ezxml_t element, ssdParameterValuesHandle* handle, sspHandle *ssp);
bool parseSsdParameterMappingElement(ezxml_t element,ssdParameterMappingHandle* handle, sspHandle *ssp);
bool parseSsmParameterMappingElement(ezxml_t element, ssmParameterMappingHandle *h, sspHandle *ssp);
bool parseSsmMappingEntryElement(ezxml_t element, ssmParameterMappingEntryHandle *h, sspHandle *ssp);
bool parseSscTransformationChoiceElement(ezxml_t element, sscMappingTransformHandle *h, sspHandle *ssp);
bool parseSscMapEntryElement(ezxml_t element, sscMapEntryHandle *h, sspHandle *ssp);
bool parseSsvParameterSetElement(ezxml_t element, ssvParameterSetHandle* parameterSetHandle, sspHandle *ssp);
bool parseSsvParameterElement(ezxml_t element, ssvParameterHandle* h, sspHandle *ssp);

#endif // SSP4C_XML_PARSERS_H
