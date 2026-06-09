#include "ssp4c_private.h"
#include "ssp4c_ssd.h"
#include "ssp4c_xml_constants.h"

const char *ssp4c_ssd_getFileName(ssdHandle *h)
{
    return h->filename;
}

const char *ssp4c_ssd_getName(ssdHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_NAME);
}

const char *ssp4c_ssd_getVersion(ssdHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_VERSION);
}

const char *ssp4c_ssd_getId(ssdHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_ID);
}

const char *ssp4c_ssd_getDescription(ssdHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_DESCRIPTION);
}

const char *ssp4c_ssd_getAuthor(ssdHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_AUTHOR);
}

const char *ssp4c_ssd_getFileversion(ssdHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_FILE_VERSION);
}

const char *ssp4c_ssd_getCopyright(ssdHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_COPYRIGHT);
}

const char *ssp4c_ssd_getLicense(ssdHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_LICENSE);
}

const char *ssp4c_ssd_getGenerationTool(ssdHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_GENERATION_TOOL);
}

const char *ssp4c_ssd_getGenerationDateAndTime(ssdHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_GENERATION_DATE_AND_TIME);
}

ssdSystemHandle *ssp4c_ssd_getRootSystem(ssdHandle *h)
{
    return h->system;
}

void ssp4c_ssd_setFileName(ssdHandle *h, const char *value)
{
    h->filename = value;
}

void ssp4c_ssd_setName(ssdHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_NAME, value);
}

void ssp4c_ssd_setVersion(ssdHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_VERSION, value);
}

void ssp4c_ssd_setId(ssdHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_ID, value);
}

void ssp4c_ssd_setDescription(ssdHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_DESCRIPTION, value);
}

void ssp4c_ssd_setAuthor(ssdHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_AUTHOR, value);
}

void ssp4c_ssd_setFileversion(ssdHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_FILE_VERSION, value);
}

void ssp4c_ssd_setCopyright(ssdHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_COPYRIGHT, value);
}

void ssp4c_ssd_setLicense(ssdHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_LICENSE, value);
}

void ssp4c_ssd_setGenerationTool(ssdHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_GENERATION_TOOL, value);
}

void ssp4c_ssd_setGenerationDateAndTime(ssdHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_GENERATION_DATE_AND_TIME, value);
}

int ssp4c_ssd_getNumberOfParameterBindings(ssdComponentHandle *h)
{
    return h->parameterBindings->parameterBindingsCount;
}

ssdParameterBindingHandle *ssp4c_ssd_getParameterBindingByIndex(ssdComponentHandle *h, int i)
{
    return &(h->parameterBindings->parameterBindings[i]);
}