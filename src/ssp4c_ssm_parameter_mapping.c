#include "ssp4c_private.h"
#include "ssp4c_ssm_parameter_mapping.h"
#include "ssp4c_xml_constants.h"

const char *ssp4c_ssm_parameterMapping_getVersion(ssmParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_VERSION);
}

const char *ssp4c_ssm_parameterMapping_getId(ssmParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_ID);
}

const char *ssp4c_ssm_parameterMapping_getDescription(ssmParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_DESCRIPTION);
}

const char *ssp4c_ssm_parameterMapping_getAuthor(ssmParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_AUTHOR);
}

const char *ssp4c_ssm_parameterMapping_getFileversion(ssmParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_FILE_VERSION);
}

const char *ssp4c_ssm_parameterMapping_getCopyright(ssmParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_COPYRIGHT);
}

const char *ssp4c_ssm_parameterMapping_getLicense(ssmParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_LICENSE);
}

const char *ssp4c_ssm_parameterMapping_getGenerationTool(ssmParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_GENERATION_TOOL);
}

const char *ssp4c_ssm_parameterMapping_getGenerationDateAndTime(ssmParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_GENERATION_DATE_AND_TIME);
}

int ssp4c_ssm_parameterMapping_getNumberOfMappingEntries(ssmParameterMappingHandle *h)
{
    return h->mappingEntryCount;
}

ssmParameterMappingEntryHandle *ssp4c_ssm_parameterMapping_getMappingEntryByIndex(ssmParameterMappingHandle *h, int i)
{
    return &(h->mappingEntries[i]);
}
