#include "ssp4c_private.h"
#include "ssp4c_ssd_connector.h"

const char* ssp4c_ssd_connector_getName(ssdConnectorHandle *h)
{
    return h->name;
}

ssdConnectorKind ssp4c_ssd_connector_getKind(ssdConnectorHandle *h)
{
    return h->kind;
}

const char* ssp4c_ssd_connector_getDescription(ssdConnectorHandle *h)
{
    return h->description;
}

sspDataType ssp4c_ssd_connector_getDatatype(ssdConnectorHandle *h)
{
    return h->datatype;
}

const char* ssp4c_ssd_connector_getUnit(ssdConnectorHandle *h)
{
    return h->unit;
}
