#include "ssp4c_private.h"
#include "ssp4c_ssd_parameter_mapping.h"

const char *ssp4c_ssd_parameterMapping_getDescription(ssdParameterMappingHandle *h)
{
    return h->description;
}

const char *ssp4c_ssd_parameterMapping_getId(ssdParameterMappingHandle *h)
{
    return h->id;
}

const char *ssp4c_ssd_parameterMapping_getType(ssdParameterMappingHandle *h)
{
    return h->type;
}

const char *ssp4c_ssd_parameterMapping_getSource(ssdParameterMappingHandle *h)
{
    return h->source;
}

ssdParameterSourceBase ssp4c_ssd_parameterMapping_getSourceBase(ssdParameterMappingHandle *h)
{
    return h->sourceBase;
}

ssmParameterMappingHandle *ssp4c_ssd_parameterMapping_getSsmParameterMapping(ssdParameterMappingHandle *h)
{
    return h->parameterMapping;
}

