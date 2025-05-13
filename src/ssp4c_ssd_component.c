#include "ssp4c_private.h"
#include "ssp4c_ssd_component.h"

// XML attribute name constants
const char* XML_ATTR_SSD_COMPONENT_NAME = "name";
const char* XML_ATTR_SSD_COMPONENT_TYPE = "type";
const char* XML_ATTR_SSD_COMPONENT_SOURCE = "source";
const char* XML_ATTR_SSD_COMPONENT_IMPLEMENTATION = "implementation";

const char* ssp4c_ssd_component_getName(ssdComponentHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_COMPONENT_NAME);
}

const char* ssp4c_ssd_component_getType(ssdComponentHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_COMPONENT_TYPE);
}

const char* ssp4c_ssd_component_getSource(ssdComponentHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_COMPONENT_SOURCE);
}

ssdComponentImplementation ssp4c_ssd_component_getImplementation(ssdComponentHandle *h)
{
    const char* implementation = ezxml_attr(h->xml, XML_ATTR_SSD_COMPONENT_IMPLEMENTATION);
    if(implementation && !strcmp(implementation, "any")) {
        return ssdComponentImplementationAny;
    }
    else if(implementation && !strcmp(implementation, "ModelExchange")) {
        return ssdComponentImplementationModelExchange;
    }
    else if(implementation && !strcmp(implementation, "CoSimulation")) {
        return ssdComponentImplementationCoSimulation;
    }
    else if(implementation && !strcmp(implementation, "ScheduledExecution")) {
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
