#include "ssp4c_private.h"
#include "ssp4c_ssd_component.h"

const char* ssp4c_ssd_component_getName(ssdComponentHandle *h)
{
    return h->name;
}

const char* ssp4c_ssd_component_getType(ssdComponentHandle *h)
{
    return h->type;
}

const char* ssp4c_ssd_component_getSource(ssdComponentHandle *h)
{
    return h->source;
}

ssdComponentImplementation ssp4c_ssd_component_getImplementation(ssdComponentHandle *h)
{
    return h->implementation;
}

int ssp4c_ssd_component_getNumberOfConnectors(ssdComponentHandle *h)
{
    return h->connectors->connectorsCount;
}

ssdConnectorHandle *ssp4c_ssd_component_getConnectorByIndex(ssdComponentHandle *h, int i)
{
    return &h->connectors->connectors[i];
}

ssdParameterBindingsHandle *ssp4c_ssd_component_getParameterBindings(ssdComponentHandle *h)
{
    return h->parameterBindings;
}

ssdElementGeometryHandle *ssp4c_ssd_component_getElementGeometry(ssdComponentHandle *h)
{
    return h->geometry;
}

int ssp4c_ssd_component_getNumberOfParameterBindings(ssdComponentHandle *h)
{
    return h->parameterBindings->parameterBindingsCount;
}

ssdParameterBindingHandle *ssp4c_ssd_component_getParameterBindingByIndex(ssdComponentHandle *h, int i)
{
    return &(h->parameterBindings->parameterBindings[i]);
}

