#include "ssp4c_private.h"
#include "ssp4c_ssd_parameter_binding.h"


int ssp4c_ssd_parameterBindings_getNumberOfParameterBindings(ssdParameterBindingsHandle *h)
{
    return h->parameterBindingsCount;
}

ssdParameterBindingHandle *ssp4c_ssd_parameterBindings_getParameterBindingByIndex(ssdParameterBindingsHandle *h, int i)
{
    return &(h->parameterBindings[i]);
}

const char *ssp4c_ssd_parameterBinding_getType(ssdParameterBindingHandle *h)
{
    return h->type;
}

const char *ssp4c_ssd_parameterBinding_getSource(ssdParameterBindingHandle *h)
{
    return h->source;
}

ssdParameterSourceBase ssp4c_ssd_parameterBinding_getSourceBase(ssdParameterBindingHandle *h)
{
    return h->sourceBase;
}

const char *ssp4c_ssd_parameterBinding_getPrefix(ssdParameterBindingHandle *h)
{
    return h->prefix;
}


ssdParameterValuesHandle *ssp4c_ssd_parameterBinding_getParameterValues(ssdParameterBindingHandle *h)
{
    return h->parameterValues;
}

ssdParameterMappingHandle *ssp4c_ssd_parameterSet_getParameterMapping(ssdParameterBindingHandle *h)
{
    return h->parameterMapping;
}
