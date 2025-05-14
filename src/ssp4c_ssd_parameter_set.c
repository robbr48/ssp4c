#include "ssp4c_private.h"
#include "ssp4c_ssd_parameter_set.h"


const char* XML_ATTR_SSD_PARAMETER_SET_VERSION = "type";
const char* XML_ATTR_SSD_PARAMETER_SET_NAME = "type";
const char* XML_ATTR_SSD_PARAMETER_SET_ID = "id";
const char* XML_ATTR_SSD_PARAMETER_SET_DESCRIPTION = "description";
const char* XML_ATTR_SSD_PARAMETER_SET_SOURCE = "source";
const char* XML_ATTR_SSD_PARAMETER_SET_SOURCE_BASE = "sourceBase";

const char *ssp4c_ssd_parameterSet_getVersion(ssvParameterSetHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_PARAMETER_SET_VERSION);
}

const char *ssp4c_ssd_parameterSet_getName(ssvParameterSetHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_PARAMETER_SET_NAME);
}

const char *ssp4c_ssd_parameterSet_getId(ssvParameterSetHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_PARAMETER_SET_ID);
}

const char *ssp4c_ssd_parameterSet_getDescription(ssvParameterSetHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_PARAMETER_SET_DESCRIPTION);
}

int ssp4c_ssd_parameterSet_getNumberOfParameters(ssvParameterSetHandle *h)
{
    return h->parameterCount;
}

ssvParameterHandle *ssp4c_ssd_parameterSet_getParameterByIndex(ssvParameterSetHandle *h, int i)
{
    return &(h->parameters[i]);
}
