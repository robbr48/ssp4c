#include "ssp4c_private.h"
#include "ssp4c_ssd_connector_geometry.h"
#include "ssp4c_utils.h"
#include "ssp4c_xml_constants.h"

double ssp4c_ssd_connectorGeometry_getX(ssdConnectorGeometryHandle *h)
{
    double x;
    if(parseFloat64AttributeEzXml(h->xml, XML_ATTR_X, &x)) {
        printf("Parsing: %s", ezxml_attr(h->xml, XML_ATTR_X));
        printf("Returning x = %f\n", x);
        return x;
    }
    return 0;
}


double ssp4c_ssd_connectorGeometry_getY(ssdConnectorGeometryHandle *h)
{
    double y;
    if(parseFloat64AttributeEzXml(h->xml, XML_ATTR_Y, &y)) {
        printf("Parsing: %s", ezxml_attr(h->xml, XML_ATTR_Y));
        printf("Returning y = %f\n", y);
        return y;
    }
    return 0;
}
