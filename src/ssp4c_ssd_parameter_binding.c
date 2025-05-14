#include "ssp4c_private.h"
#include "ssp4c_ssd_parameter_binding.h"

const char* XML_ATTR_SSD_PARAMETER_BINDINGS_TYPE = "type";
const char* XML_ATTR_SSD_PARAMETER_BINDINGS_SOURCE = "source";
const char* XML_ATTR_SSD_PARAMETER_BINDINGS_PREFIX = "prefix";
const char* XML_ATTR_SSD_PARAMETER_BINDINGS_SOURCE_BASE = "sourceBase";

const char *ssp4c_ssd_parameterBinding_getType(ssdParameterBindingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_PARAMETER_BINDINGS_TYPE);
}

const char *ssp4c_ssd_parameterBinding_getSource(ssdParameterBindingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_PARAMETER_BINDINGS_SOURCE);
}

ssdParameterSourceBase ssp4c_ssd_parameterBinding_getSourceBase(ssdParameterBindingHandle *h)
{
    const char* sourceBase = ezxml_attr(h->xml, XML_ATTR_SSD_PARAMETER_BINDINGS_SOURCE_BASE);
    if(sourceBase && !strcmp(sourceBase, "SSD")) {
        return ssdParameterSourceBaseSSD;
    }
    else if(sourceBase && !strcmp(sourceBase, "component")) {
        return ssdParameterSourceBaseComponent;
    }
    return ssdParameterSourceBaseSSD;
}

const char *ssp4c_ssd_parameterBinding_getPrefix(ssdParameterBindingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_PARAMETER_BINDINGS_PREFIX);
}


ssdParameterValuesHandle *ssp4c_ssd_parameterBinding_getParameterValues(ssdParameterBindingHandle *h)
{
    return h->parameterValues;
}

ssdParameterMappingHandle *ssp4c_ssd_parameterSet_getParameterMapping(ssdParameterBindingHandle *h)
{
    return h->parameterMapping;
}
