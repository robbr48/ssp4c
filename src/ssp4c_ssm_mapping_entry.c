#include "ssp4c_private.h"
#include "ssp4c_ssm_mapping_entry.h"

const char *ssp4c_ssm_mappingEntry_getId(ssmParameterMappingEntryHandle *h)
{
    return h->id;
}

const char *ssp4c_ssm_mappingEntry_getDescription(ssmParameterMappingEntryHandle *h)
{
    return h->description;
}

const char *ssp4c_ssm_mappingEntry_getSource(ssmParameterMappingEntryHandle *h)
{
    return h->source;
}

const char *ssp4c_ssm_mappingEntry_getTarget(ssmParameterMappingEntryHandle *h)
{
    return h->target;
}

bool ssp4c_ssm_mappingEntry_getSuppressUnitConveresion(ssmParameterMappingEntryHandle *h)
{
    return h->suppressUnitConveresion;
}

sscMappingTransformHandle *ssp4c_ssm_mappingEntry_getSsmMappingTransform(ssmParameterMappingEntryHandle *h)
{
    return h->transform;
}
