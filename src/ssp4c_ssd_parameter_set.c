#include "ssp4c_private.h"
#include "ssp4c_ssd_parameter_set.h"
#include "ssp4c_xml_constants.h"

const char *ssp4c_ssd_parameterSet_getVersion(ssvParameterSetHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_VERSION);
}

const char *ssp4c_ssd_parameterSet_getName(ssvParameterSetHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_NAME);
}

const char *ssp4c_ssd_parameterSet_getId(ssvParameterSetHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_ID);
}

const char *ssp4c_ssd_parameterSet_getDescription(ssvParameterSetHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_DESCRIPTION);
}

int ssp4c_ssd_parameterSet_getNumberOfParameters(ssvParameterSetHandle *h)
{
    return h->parameterCount;
}

ssvParameterHandle *ssp4c_ssd_parameterSet_getParameterByIndex(ssvParameterSetHandle *h, int i)
{
    return &(h->parameters[i]);
}
