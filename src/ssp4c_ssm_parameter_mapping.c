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

const char *ssp4c_ssm_parameterMapping_getFilename(ssmParameterMappingHandle *h)
{
    return h->filename;
}

int ssp4c_ssm_parameterMapping_getNumberOfMappingEntries(ssmParameterMappingHandle *h)
{
    return h->mappingEntryCount;
}

ssmParameterMappingEntryHandle *ssp4c_ssm_parameterMapping_getMappingEntryByIndex(ssmParameterMappingHandle *h, int i)
{
    return &(h->mappingEntries[i]);
}

void ssp4c_ssm_parameterMapping_setVersion(ssmParameterMappingHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_VERSION, value);
}

void ssp4c_ssm_parameterMapping_setId(ssmParameterMappingHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_ID, value);
}

void ssp4c_ssm_parameterMapping_setDescription(ssmParameterMappingHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_DESCRIPTION, value);
}

void ssp4c_ssm_parameterMapping_setAuthor(ssmParameterMappingHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_AUTHOR, value);
}

void ssp4c_ssm_parameterMapping_setFileversion(ssmParameterMappingHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_FILE_VERSION, value);
}

void ssp4c_ssm_parameterMapping_setCopyright(ssmParameterMappingHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_COPYRIGHT, value);
}

void ssp4c_ssm_parameterMapping_setLicense(ssmParameterMappingHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_LICENSE, value);
}

void ssp4c_ssm_parameterMapping_setGenerationTool(ssmParameterMappingHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_GENERATION_TOOL, value);
}

void ssp4c_ssm_parameterMapping_setGenerationDateAndTime(ssmParameterMappingHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_GENERATION_DATE_AND_TIME, value);
}

void ssp4c_ssm_parameterMapping_setFilename(ssmParameterMappingHandle *h, const char *value)
{
    h->filename = value;
}
