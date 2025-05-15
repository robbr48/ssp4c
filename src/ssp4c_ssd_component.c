#include "ssp4c_private.h"
#include "ssp4c_ssd_component.h"
#include "ssp4c_xml_constants.h"

const char* ssp4c_ssd_component_getName(ssdComponentHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_NAME);
}

const char* ssp4c_ssd_component_getType(ssdComponentHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_TYPE);
}

const char* ssp4c_ssd_component_getSource(ssdComponentHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SOURCE);
}

ssdComponentImplementation ssp4c_ssd_component_getImplementation(ssdComponentHandle *h)
{
    const char* implementation = ezxml_attr(h->xml, XML_ATTR_IMPLEMENTATION);
    if(implementation && !strcmp(implementation, XML_VALUE_ANY)) {
        return ssdComponentImplementationAny;
    }
    else if(implementation && !strcmp(implementation, XML_VALUE_MODELEXCHANGE)) {
        return ssdComponentImplementationModelExchange;
    }
    else if(implementation && !strcmp(implementation, XML_VALUE_COSIMULATION)) {
        return ssdComponentImplementationCoSimulation;
    }
    else if(implementation && !strcmp(implementation, XML_VALUE_SCHEDULED_EXECUTION)) {
        return ssdComponentImplementationScheduledExecution;
    }

    return ssdComponentImplementationAny;
}

int ssp4c_ssd_component_getNumberOfConnectors(ssdComponentHandle *h)
{
    return h->connectors->connectorsCount;
}

ssdConnectorHandle *ssp4c_ssd_component_getConnectorByIndex(ssdComponentHandle *h, int i)
{
    return &h->connectors->connectors[i];
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
