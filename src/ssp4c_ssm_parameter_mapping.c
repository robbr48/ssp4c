#include "ssp4c_private.h"
#include "ssp4c_ssm_parameter_mapping.h"

const char* XML_ATTR_SSM_PARAMETER_MAPPING_VERSION = "version";
const char* XML_ATTR_SSM_PARAMETER_MAPPING_ID = "id";
const char* XML_ATTR_SSM_PARAMETER_MAPPING_DESCRIPTION = "description";
const char* XML_ATTR_SSM_PARAMETER_MAPPING_AUTHOR = "author";
const char* XML_ATTR_SSM_PARAMETER_MAPPING_FILE_VERSION = "fileversion";
const char* XML_ATTR_SSM_PARAMETER_MAPPING_COPYRIGHT = "copyright";
const char* XML_ATTR_SSM_PARAMETER_MAPPING_LICENSE = "license";
const char* XML_ATTR_SSM_PARAMETER_MAPPING_GENERATION_TOOL = "generationTool";
const char* XML_ATTR_SSM_PARAMETER_MAPPING_GENERATION_DATE_AND_TIME = "generationDateAndTime";

const char *ssp4c_ssm_parameterMapping_getVersion(ssmParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSM_PARAMETER_MAPPING_VERSION);
}

const char *ssp4c_ssm_parameterMapping_getId(ssmParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSM_PARAMETER_MAPPING_ID);
}

const char *ssp4c_ssm_parameterMapping_getDescription(ssmParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSM_PARAMETER_MAPPING_DESCRIPTION);
}

const char *ssp4c_ssm_parameterMapping_getAuthor(ssmParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSM_PARAMETER_MAPPING_AUTHOR);
}

const char *ssp4c_ssm_parameterMapping_getFileversion(ssmParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSM_PARAMETER_MAPPING_FILE_VERSION);
}

const char *ssp4c_ssm_parameterMapping_getCopyright(ssmParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSM_PARAMETER_MAPPING_COPYRIGHT);
}

const char *ssp4c_ssm_parameterMapping_getLicense(ssmParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSM_PARAMETER_MAPPING_LICENSE);
}

const char *ssp4c_ssm_parameterMapping_getGenerationTool(ssmParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSM_PARAMETER_MAPPING_GENERATION_TOOL);
}

const char *ssp4c_ssm_parameterMapping_getGenerationDateAndTime(ssmParameterMappingHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSM_PARAMETER_MAPPING_GENERATION_DATE_AND_TIME);
}

int ssp4c_ssm_parameterMapping_getNumberOfMappingEntries(ssmParameterMappingHandle *h)
{
    return h->mappingEntryCount;
}

ssmParameterMappingEntryHandle *ssp4c_ssm_parameterMapping_getMappingEntryByIndex(ssmParameterMappingHandle *h, int i)
{
    return &(h->mappingEntries[i]);
}
