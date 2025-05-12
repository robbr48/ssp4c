#include "ssp4c_private.h"
#include "ssp4c_ssm_parameter_mapping.h"

const char *ssp4c_ssm_parameterMapping_getVersion(ssmParameterMappingHandle *h)
{
    return h->version;
}

const char *ssp4c_ssm_parameterMapping_getId(ssmParameterMappingHandle *h)
{
    return h->id;
}

const char *ssp4c_ssm_parameterMapping_getDescription(ssmParameterMappingHandle *h)
{
    return h->description;
}

const char *ssp4c_ssm_parameterMapping_getAuthor(ssmParameterMappingHandle *h)
{
    return h->author;
}

const char *ssp4c_ssm_parameterMapping_getFileversion(ssmParameterMappingHandle *h)
{
    return h->fileversion;
}

const char *ssp4c_ssm_parameterMapping_getCopyright(ssmParameterMappingHandle *h)
{
    return h->copyright;
}

const char *ssp4c_ssm_parameterMapping_getLicense(ssmParameterMappingHandle *h)
{
    return h->license;
}

const char *ssp4c_ssm_parameterMapping_getGenerationTool(ssmParameterMappingHandle *h)
{
    return h->generationTool;
}

const char *ssp4c_ssm_parameterMapping_getGenerationDateAndTime(ssmParameterMappingHandle *h)
{
    return h->generationDateAndTime;
}

int ssp4c_ssm_parameterMapping_getNumberOfMappingEntries(ssmParameterMappingHandle *h)
{
    return h->mappingEntryCount;
}

ssmParameterMappingEntryHandle *ssp4c_ssm_parameterMapping_getMappingEntryByIndex(ssmParameterMappingHandle *h, int i)
{
    return &(h->mappingEntries[i]);
}
