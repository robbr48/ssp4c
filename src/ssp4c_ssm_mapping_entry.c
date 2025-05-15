#include "ssp4c_private.h"
#include "ssp4c_ssm_mapping_entry.h"
#include "ssp4c_xml_constants.h"
#include "ssp4c_utils.h"

const char *ssp4c_ssm_mappingEntry_getId(ssmParameterMappingEntryHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_ID);
}

const char *ssp4c_ssm_mappingEntry_getDescription(ssmParameterMappingEntryHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_DESCRIPTION);
}

const char *ssp4c_ssm_mappingEntry_getSource(ssmParameterMappingEntryHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SOURCE);
}

const char *ssp4c_ssm_mappingEntry_getTarget(ssmParameterMappingEntryHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_TARGET);
}

bool ssp4c_ssm_mappingEntry_getSuppressUnitConveresion(ssmParameterMappingEntryHandle *h)
{
    bool value;
    if(parseBooleanAttributeEzXml(h->xml, XML_ATTR_SUPPRESS_UNIT_CONVERSION, &value)) {
        return value;
    }
    return false;
}

sscMappingTransformHandle *ssp4c_ssm_mappingEntry_getSsmMappingTransform(ssmParameterMappingEntryHandle *h)
{
    return h->transform;
}
