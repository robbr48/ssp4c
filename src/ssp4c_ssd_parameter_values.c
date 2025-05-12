#include "ssp4c_private.h"
#include "ssp4c_ssd_parameter_values.h"


ssvParameterSetHandle *ssp4c_ssd_parameterValues_getParameterSet(ssdParameterValuesHandle *h)
{
    return h->parameterSet;
}
