#include "ssp4c_private.h"
#include "ssp4c_ssd_parameter_set.h"

const char *ssp4c_ssd_parameterSet_getVersion(ssvParameterSetHandle *h)
{
    return h->version;
}

const char *ssp4c_ssd_parameterSet_getName(ssvParameterSetHandle *h)
{
    return h->name;
}

const char *ssp4c_ssd_parameterSet_getId(ssvParameterSetHandle *h)
{
    return h->id;
}

const char *ssp4c_ssd_parameterSet_getDescription(ssvParameterSetHandle *h)
{
    return h->description;
}

int ssp4c_ssd_parameterSet_getNumberOfParameters(ssvParameterSetHandle *h)
{
    return h->parameterCount;
}

ssvParameterHandle *ssp4c_ssd_parameterSet_getParameterByIndex(ssvParameterSetHandle *h, int i)
{
    return &(h->parameters[i]);
}
