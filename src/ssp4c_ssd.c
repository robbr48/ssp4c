#include "ssp4c_private.h"
#include "ssp4c_ssd.h"

// Centralized XML attribute name constants
const char *XML_ATTR_SSD_NAME = "name";
const char *XML_ATTR_SSD_VERSION = "version";
const char *XML_ATTR_SSD_ID = "id";
const char *XML_ATTR_SSD_DESCRIPTION = "description";
const char *XML_ATTR_SSD_AUTHOR = "author";
const char *XML_ATTR_SSD_FILEVERSION = "fileversion";
const char *XML_ATTR_SSD_COPYRIGHT = "copyright";
const char *XML_ATTR_SSD_LICENSE = "license";
const char *XML_ATTR_SSD_GENERATION_TOOL = "generationTool";
const char *XML_ATTR_SSD_GENERATION_DATE_AND_TIME = "generationDateAndTime";

const char *ssp4c_ssd_getFileName(ssdHandle *h)
{
    return h->filename;
}

const char *ssp4c_ssd_getName(ssdHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_NAME);
}

const char *ssp4c_ssd_getVersion(ssdHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_VERSION);
}

const char *ssp4c_ssd_getId(ssdHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_ID);
}

const char *ssp4c_ssd_getDescription(ssdHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_DESCRIPTION);
}

const char *ssp4c_ssd_getAuthor(ssdHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_AUTHOR);
}

const char *ssp4c_ssd_getFileversion(ssdHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_FILEVERSION);
}

const char *ssp4c_ssd_getCopyright(ssdHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_COPYRIGHT);
}

const char *ssp4c_ssd_getLicense(ssdHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_LICENSE);
}

const char *ssp4c_ssd_getGenerationTool(ssdHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_GENERATION_TOOL);
}

const char *ssp4c_ssd_getGenerationDateAndTime(ssdHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_GENERATION_DATE_AND_TIME);
}

int ssp4c_ssd_getNumberOfConnectors(ssdHandle *h)
{
    return h->connectors->connectorsCount;
}

ssdConnectorHandle *ssp4c_ssd_getConnectorByIndex(ssdHandle *ssd, int i)
{
    return &ssd->connectors->connectors[i];
}

int ssp4c_ssd_getNumberOfComponents(ssdHandle* h)
{
    return h->components->componentsCount;
}

ssdComponentHandle *ssp4c_ssd_getComponentByIndex(ssdHandle *h, int i)
{
    return &(h->components->components[i]);
}

void ssp4c_ssd_setFileName(ssdHandle *h, const char *value)
{
    h->filename = value;
}

void ssp4c_ssd_setName(ssdHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_SSD_NAME, value);
}

void ssp4c_ssd_setVersion(ssdHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_SSD_VERSION, value);
}

void ssp4c_ssd_setId(ssdHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_SSD_ID, value);
}

void ssp4c_ssd_setDescription(ssdHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_SSD_DESCRIPTION, value);
}

void ssp4c_ssd_setAuthor(ssdHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_SSD_AUTHOR, value);
}

void ssp4c_ssd_setFileversion(ssdHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_SSD_FILEVERSION, value);
}

void ssp4c_ssd_setCopyright(ssdHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_SSD_COPYRIGHT, value);
}

void ssp4c_ssd_setLicense(ssdHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_SSD_LICENSE, value);
}

void ssp4c_ssd_setGenerationTool(ssdHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_SSD_GENERATION_TOOL, value);
}

void ssp4c_ssd_setGenerationDateAndTime(ssdHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_SSD_GENERATION_DATE_AND_TIME, value);
}
