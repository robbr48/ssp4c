#include "ssp4c_private.h"
#include "ssp4c_ssd_parameter_binding.h"
#include "ssp4c_xml_constants.h"

const char *ssp4c_ssd_parameterBinding_getType(ssdParameterBindingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_TYPE);
}

const char *ssp4c_ssd_parameterBinding_getSource(ssdParameterBindingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SOURCE);
}

ssdParameterSourceBase ssp4c_ssd_parameterBinding_getSourceBase(ssdParameterBindingHandle *h)
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

const char *ssp4c_ssd_parameterBinding_getPrefix(ssdParameterBindingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_PREFIX);
}


ssdParameterValuesHandle *ssp4c_ssd_parameterBinding_getParameterValues(ssdParameterBindingHandle *h)
{
    return h->parameterValues;
}

ssdParameterMappingHandle *ssp4c_ssd_parameterSet_getParameterMapping(ssdParameterBindingHandle *h)
{
    return h->parameterMapping;
}
