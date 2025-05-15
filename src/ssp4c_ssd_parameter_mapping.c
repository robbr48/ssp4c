#include "ssp4c_private.h"
#include "ssp4c_ssd_parameter_mapping.h"
#include "ssp4c_xml_constants.h"

const char *ssp4c_ssd_parameterMapping_getDescription(ssdParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_DESCRIPTION);
}

const char *ssp4c_ssd_parameterMapping_getId(ssdParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_ID);
}

const char *ssp4c_ssd_parameterMapping_getType(ssdParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_TYPE);
}

const char *ssp4c_ssd_parameterMapping_getSource(ssdParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SOURCE);
}

ssdParameterSourceBase ssp4c_ssd_parameterMapping_getSourceBase(ssdParameterMappingHandle *h)
{
    const char* sourceBase = ezxml_attr(h->xml, XML_ATTR_SOURCE_BASE);
    if(sourceBase && !strcmp(sourceBase, XML_VALUE_SSD)) {
        return ssdParameterSourceBaseSSD;
    }
    else if(sourceBase && !strcmp(sourceBase, XML_VALUE_COMPONENT)) {
        return ssdParameterSourceBaseComponent;
    }
    return ssdParameterSourceBaseSSD;
}

ssmParameterMappingHandle *ssp4c_ssd_parameterMapping_getSsmParameterMapping(ssdParameterMappingHandle *h)
{
    return h->parameterMapping;
}

