#include "ssp4c_private.h"
#include "ssp4c_ssm_mapping_entry.h"

const char* XML_TRUE = "true";

const char* XML_ATTR_SSM_PARAMETER_ENTRY_ID = "id";
const char* XML_ATTR_SSM_PARAMETER_ENTRY_DESCRIPTION = "description";
const char* XML_ATTR_SSM_PARAMETER_ENTRY_SOURCE = "source";
const char* XML_ATTR_SSM_PARAMETER_ENTRY_TARGET = "target";
const char* XML_ATTR_SSM_PARAMETER_ENTRY_SUPPRESS_UNIT_CONVERSION = "target";

const char *ssp4c_ssm_mappingEntry_getId(ssmParameterMappingEntryHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSM_PARAMETER_ENTRY_ID);
}

const char *ssp4c_ssm_mappingEntry_getDescription(ssmParameterMappingEntryHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSM_PARAMETER_ENTRY_DESCRIPTION);
}

const char *ssp4c_ssm_mappingEntry_getSource(ssmParameterMappingEntryHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSM_PARAMETER_ENTRY_SOURCE);
}

const char *ssp4c_ssm_mappingEntry_getTarget(ssmParameterMappingEntryHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSM_PARAMETER_ENTRY_TARGET);
}

bool ssp4c_ssm_mappingEntry_getSuppressUnitConveresion(ssmParameterMappingEntryHandle *h)
{
    return !strcmp(ezxml_attr(h->xml, XML_ATTR_SSM_PARAMETER_ENTRY_SUPPRESS_UNIT_CONVERSION), XML_TRUE);
}

sscMappingTransformHandle *ssp4c_ssm_mappingEntry_getSsmMappingTransform(ssmParameterMappingEntryHandle *h)
{
    return h->transform;
}
