#include "ssp4c_private.h"
#include "ssp4c_ssd_parameter_mapping.h"

const char* XML_ATTR_SSD_PARAMETER_MAPPING_ID = "id";
const char* XML_ATTR_SSD_PARAMETER_MAPPING_DESCRIPTION = "description";
const char* XML_ATTR_SSD_PARAMETER_MAPPING_TYPE = "type";
const char* XML_ATTR_SSD_PARAMETER_MAPPING_SOURCE = "source";
const char* XML_ATTR_SSD_PARAMETER_MAPPING_SOURCE_BASE = "sourceBase";

const char *ssp4c_ssd_parameterMapping_getDescription(ssdParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_PARAMETER_MAPPING_DESCRIPTION);
}

const char *ssp4c_ssd_parameterMapping_getId(ssdParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_PARAMETER_MAPPING_ID);
}

const char *ssp4c_ssd_parameterMapping_getType(ssdParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_PARAMETER_MAPPING_TYPE);
}

const char *ssp4c_ssd_parameterMapping_getSource(ssdParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_PARAMETER_MAPPING_SOURCE);
}

ssdParameterSourceBase ssp4c_ssd_parameterMapping_getSourceBase(ssdParameterMappingHandle *h)
{
    const char* sourceBase = ezxml_attr(h->xml, XML_ATTR_SSD_PARAMETER_MAPPING_SOURCE_BASE);
    if(sourceBase && !strcmp(sourceBase, "SSD")) {
        return ssdParameterSourceBaseSSD;
    }
    else if(sourceBase && !strcmp(sourceBase, "component")) {
        return ssdParameterSourceBaseComponent;
    }
    return ssdParameterSourceBaseSSD;
}

ssmParameterMappingHandle *ssp4c_ssd_parameterMapping_getSsmParameterMapping(ssdParameterMappingHandle *h)
{
    return h->parameterMapping;
}

