#include "ssp4c_private.h"
#include "ssp4c_ssd.h"

const char *ssp4c_ssd_getFileName(ssdHandle *h)
{
    return h->filename;
}

const char *ssp4c_ssd_getName(ssdHandle *h)
{
    return h->name;
}

const char *ssp4c_ssd_getVersion(ssdHandle *h)
{
    return h->version;
}

const char *ssp4c_ssd_getId(ssdHandle *h)
{
    return h->id;
}

const char *ssp4c_ssd_getDescription(ssdHandle *h)
{
    return h->description;
}

const char *ssp4c_ssd_getAuthor(ssdHandle *h)
{
    return h->author;
}

const char *ssp4c_ssd_getFileversion(ssdHandle *h)
{
    return h->fileversion;
}

const char *ssp4c_ssd_getCopyright(ssdHandle *h)
{
    return h->copyright;
}

const char *ssp4c_ssd_getLicense(ssdHandle *h)
{
    return h->license;
}

const char *ssp4c_ssd_getGenerationTool(ssdHandle *h)
{
    return h->generationTool;
}

const char *ssp4c_ssd_getGenerationDateAndTime(ssdHandle *h)
{
    return h->generationDateAndTime;
}

int ssp4c_ssd_getNumberOfConnectors(ssdHandle *h)
{
    return h->connectors->connectorsCount;
}

ssdConnectorHandle *ssp4c_ssd_getConnectorByIndex(ssdHandle *ssd, int i)
{
    return &ssd->connectors->connectors[i];
}



int ssp4c_ssd_getNumberOfComponents(ssdHandle* h)
{
    return h->components->componentsCount;
}

ssdComponentHandle *ssp4c_ssd_getComponentByIndex(ssdHandle *h, int i)
{
    return &(h->components->components[i]);
}
