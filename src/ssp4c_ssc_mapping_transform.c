#include "ssp4c_private.h"
#include "ssp4c_ssc_mapping_transform.h"

sscMappingTransform ssp4c_ssc_mappingTransform_getType(sscMappingTransformHandle *h)
{
    return h->type;
}

double ssp4c_ssc_mappingTransform_getFactor(sscMappingTransformHandle *h)
{
    return h->factor;
}

double ssp4c_ssc_mappingTransform_getOffset(sscMappingTransformHandle *h)
{
    return h->offset;
}

int ssp4c_ssc_mappingTransform_getNumberOfMapEntries(sscMappingTransformHandle *h)
{
    return h->mapEntryCount;
}

sscMapEntryHandle *ssp4c_ssc_mappingTransform_getMapEntryByIndex(sscMappingTransformHandle *h, int i)
{
    return &(h->mapEntries[i]);
}
