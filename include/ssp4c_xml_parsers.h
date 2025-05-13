#ifndef SSP4C_XML_PARSERS_H
#define SSP4C_XML_PARSERS_H

#include <ezxml/ezxml.h>
#include "ssp4c_public.h"

bool parseSsd(sspHandle *ssp, ssdHandle *ssd, const char* path);
bool parseConnectorsElement(ezxml_t element, ssdConnectorsHandle* h, sspHandle *ssp);
bool parseConnectorElement(ezxml_t element, ssdConnectorHandle *h, sspHandle *ssp);
bool parseComponentsElement(ezxml_t element, ssdComponentsHandle* h, sspHandle *ssp);
bool parseComponentElement(ezxml_t element, ssdComponentHandle* h, sspHandle *ssp);
bool parseParameterBindingsElement(ezxml_t element, ssdParameterBindingsHandle* h, sspHandle *ssp);
bool parseParameterBindingElement(ezxml_t element, ssdParameterBindingHandle *h, sspHandle *ssp);
bool parseSsdParameterValuesElement(ezxml_t element, ssdParameterValuesHandle* handle, sspHandle *ssp);
bool parseParameterMappingElement(ezxml_t element,ssdParameterMappingHandle* handle, sspHandle *ssp);
bool parseSsmParameterMappingElement(ezxml_t element, ssmParameterMappingHandle *handle, sspHandle *ssp);
bool parseSsmMappingEntryElement(ezxml_t element, ssmParameterMappingEntryHandle *handle, sspHandle *ssp);
bool parseSscTransformationChoiceElement(ezxml_t element, sscMappingTransformHandle *handle, sspHandle *ssp);
bool parseSscMapEntryElement(ezxml_t element, sscMapEntryHandle *handle, sspHandle *ssp);
bool parseParameterSetElement(ezxml_t element, ssvParameterSetHandle* parameterSetHandle, sspHandle *ssp);
bool parseParameterElement(ezxml_t element, ssvParameterHandle* parameterHandle, sspHandle *ssp);

#endif // SSP4C_XML_PARSERS_H
