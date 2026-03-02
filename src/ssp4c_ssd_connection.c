#include "ssp4c_private.h"
#include "ssp4c_ssd_connection.h"
#include "ssp4c_xml_constants.h"

const char* ssp4c_ssd_connection_getStartElement(ssdConnectionHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_START_ELEMENT);
}

const char* ssp4c_ssd_connection_getStartConnector(ssdConnectionHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_START_CONNECTOR);
}

const char* ssp4c_ssd_connection_getEndElement(ssdConnectionHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_END_ELEMENT);
}

const char* ssp4c_ssd_connection_getEndConnector(ssdConnectionHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_END_CONNECTOR);
}

const char* ssp4c_ssd_connection_getDescription(ssdConnectionHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_DESCRIPTION);
}

const char* ssp4c_ssd_connection_getId(ssdConnectionHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_ID);
}

