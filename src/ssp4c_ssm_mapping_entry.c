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

void ssp4c_ssm_mappingEntry_setId(ssmParameterMappingEntryHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_ID, value);
}

void ssp4c_ssm_mappingEntry_setDescription(ssmParameterMappingEntryHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_DESCRIPTION, value);
}

void ssp4c_ssm_mappingEntry_setSource(ssmParameterMappingEntryHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_SOURCE, value);
}

void ssp4c_ssm_mappingEntry_setTarget(ssmParameterMappingEntryHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_TARGET, value);
}

void ssp4c_ssm_mappingEntry_setSuppressUnitConveresion(ssmParameterMappingEntryHandle *h, bool value)
{
    setBooleanAttributeEzxml(h->xml, XML_ATTR_SUPPRESS_UNIT_CONVERSION, value);
}
