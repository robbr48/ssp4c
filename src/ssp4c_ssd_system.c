#include "ssp4c_private.h"
#include "ssp4c_ssd_system.h"

int ssp4c_ssd_system_getNumberOfConnectors(ssdSystemHandle *h)
{
    return h->connectors->connectorsCount;
}

ssdConnectorHandle *ssp4c_ssd_system_getConnectorByIndex(ssdSystemHandle *h, int i)
{
    return &h->connectors->connectors[i];
}

int ssp4c_ssd_system_getNumberOfComponents(ssdSystemHandle *h)
{
    return h->components->componentsCount;
}

ssdComponentHandle *ssp4c_ssd_system_getComponentByIndex(ssdSystemHandle *h, int i)
{
    return &(h->components->components[i]);
}

int ssp4c_ssd_system_getNumberOfConnections(ssdSystemHandle *h)
{
    return h->connections->connectionsCount;
}

ssdConnectionHandle *ssp4c_ssd_system_getConnectionByIndex(ssdSystemHandle *h, int i)
{
    return &(h->connections->connections[i]);
}

const char* ssp4c_ssd_system_getName(ssdSystemHandle *h)
{
    return h->name;
}