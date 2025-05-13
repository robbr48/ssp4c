#ifndef SSP4C_XML_PARSERS_H
#define SSP4C_XML_PARSERS_H

#include <ezxml/ezxml.h>
#include "ssp4c_public.h"

bool parseSsd(sspHandle *ssp, ssdHandle *ssd, const char* path);
bool parseSsdConnectorsElement(ezxml_t element, ssdConnectorsHandle* h, sspHandle *ssp);
bool parseSsdConnectorElement(ezxml_t element, ssdConnectorHandle *h, sspHandle *ssp);
bool parseSsdComponentsElement(ezxml_t element, ssdComponentsHandle* h, sspHandle *ssp);
bool parseSsdComponentElement(ezxml_t element, ssdComponentHandle* h, sspHandle *ssp);
bool parseSsdParameterBindingsElement(ezxml_t element, ssdParameterBindingsHandle* h, sspHandle *ssp);
bool parseSsdParameterBindingElement(ezxml_t element, ssdParameterBindingHandle *h, sspHandle *ssp);
bool parseSsdParameterValuesElement(ezxml_t element, ssdParameterValuesHandle* handle, sspHandle *ssp);
bool parseSsdParameterMappingElement(ezxml_t element,ssdParameterMappingHandle* handle, sspHandle *ssp);
bool parseSsmParameterMappingElement(ezxml_t element, ssmParameterMappingHandle *handle, sspHandle *ssp);
bool parseSsmMappingEntryElement(ezxml_t element, ssmParameterMappingEntryHandle *handle, sspHandle *ssp);
bool parseSscTransformationChoiceElement(ezxml_t element, sscMappingTransformHandle *handle, sspHandle *ssp);
bool parseSscMapEntryElement(ezxml_t element, sscMapEntryHandle *handle, sspHandle *ssp);
bool parseSsvParameterSetElement(ezxml_t element, ssvParameterSetHandle* parameterSetHandle, sspHandle *ssp);
bool parseSsvParameterElement(ezxml_t element, ssvParameterHandle* parameterHandle, sspHandle *ssp);

#endif // SSP4C_XML_PARSERS_H
