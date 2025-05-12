#include "ssp4c_private.h"
#include "ssp4c_ssc_map_entry.h"

bool ssp4c_ssc_mapEntry_getBoolSource(sscMapEntryHandle *h)
{
    return h->boolSource;
}

bool ssp4c_ssc_mapEntry_getBoolTarget(sscMapEntryHandle *h)
{
    return h->boolTarget;
}

int ssp4c_ssc_mapEntry_getIntSource(sscMapEntryHandle *h)
{
    return h->intSource;
}

int ssp4c_ssc_mapEntry_getIntTarget(sscMapEntryHandle *h)
{
    return h->intTarget;
}

const char *ssp4c_ssc_mapEntry_getEnumSource(sscMapEntryHandle *h)
{
    return h->enumSource;
}

const char *ssp4c_ssc_mapEntry_getEnumTarget(sscMapEntryHandle *h)
{
    return h->enumTarget;
}
