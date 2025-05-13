#include "ssp4c_private.h"
#include "ssp4c_ssd_element_geometry.h"
#include "ssp4c_utils.h"

const char* XML_ATTR_SSD_ELEMENT_GEOMETRY_X1 = "x1";
const char* XML_ATTR_SSD_ELEMENT_GEOMETRY_Y1 = "y1";
const char* XML_ATTR_SSD_ELEMENT_GEOMETRY_X2 = "x2";
const char* XML_ATTR_SSD_ELEMENT_GEOMETRY_Y2 = "y2";
const char* XML_ATTR_SSD_ELEMENT_GEOMETRY_ROTATION = "rotation";
const char* XML_ATTR_SSD_ELEMENT_GEOMETRY_ICON_ROTATION = "iconRotation";
const char* XML_ATTR_SSD_ELEMENT_GEOMETRY_ICON_SOURCE = "iconSource";
const char* XML_ATTR_SSD_ELEMENT_GEOMETRY_ICON_FLIP = "iconFlip";
const char* XML_ATTR_SSD_ELEMENT_GEOMETRY_ICON_FIXED_ASPECT_RATIO = "iconFixedAspectRatio";

double ssp4c_ssd_elementGeometry_getX1(ssdElementGeometryHandle *h)
{
    double value;
    parseFloat64AttributeEzXml(h->xml, XML_ATTR_SSD_ELEMENT_GEOMETRY_X1, &value);
    return value;
}

double ssp4c_ssd_elementGeometry_getY1(ssdElementGeometryHandle *h)
{
    double value;
    parseFloat64AttributeEzXml(h->xml, XML_ATTR_SSD_ELEMENT_GEOMETRY_Y1, &value);
    return value;
}

double ssp4c_ssd_elementGeometry_getX2(ssdElementGeometryHandle *h)
{
    double value;
    parseFloat64AttributeEzXml(h->xml, XML_ATTR_SSD_ELEMENT_GEOMETRY_X2, &value);
    return value;
}

double ssp4c_ssd_elementGeometry_getY2(ssdElementGeometryHandle *h)
{
    double value;
    parseFloat64AttributeEzXml(h->xml, XML_ATTR_SSD_ELEMENT_GEOMETRY_Y2, &value);
    return value;
}

double ssp4c_ssd_elementGeometry_getRotation(ssdElementGeometryHandle *h)
{
    double value;
    parseFloat64AttributeEzXml(h->xml, XML_ATTR_SSD_ELEMENT_GEOMETRY_ROTATION, &value);
    return value;
}

const char* ssp4c_ssd_elementGeometry_getIconSource(ssdElementGeometryHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_ELEMENT_GEOMETRY_ICON_SOURCE);
}

double ssp4c_ssd_elementGeometry_getIconRotation(ssdElementGeometryHandle *h)
{
    double value;
    parseFloat64AttributeEzXml(h->xml, XML_ATTR_SSD_ELEMENT_GEOMETRY_ICON_ROTATION, &value);
    return value;
}

bool ssp4c_ssd_elementGeometry_getIconFlip(ssdElementGeometryHandle *h)
{
    bool value;
    parseBooleanAttributeEzXml(h->xml, XML_ATTR_SSD_ELEMENT_GEOMETRY_ICON_FLIP, &value);
    return value;
}

bool ssp4c_ssd_elementGeometry_getIconFixedAspectRatio(ssdElementGeometryHandle *h)
{
    bool value;
    parseBooleanAttributeEzXml(h->xml, XML_ATTR_SSD_ELEMENT_GEOMETRY_ICON_FIXED_ASPECT_RATIO, &value);
    return value;
}

void ssp4c_ssd_elementGeometry_setX1(ssdElementGeometryHandle *h, double value)
{
    setFloat64AttributeEzxml(h->xml, XML_ATTR_SSD_ELEMENT_GEOMETRY_X1, value, h->ssp);
}

void ssp4c_ssd_elementGeometry_setY1(ssdElementGeometryHandle *h, double value)
{
    setFloat64AttributeEzxml(h->xml, XML_ATTR_SSD_ELEMENT_GEOMETRY_Y1, value, h->ssp);
}

void ssp4c_ssd_elementGeometry_setX2(ssdElementGeometryHandle *h, double value)
{
    setFloat64AttributeEzxml(h->xml, XML_ATTR_SSD_ELEMENT_GEOMETRY_X2, value, h->ssp);
}

void ssp4c_ssd_elementGeometry_setY2(ssdElementGeometryHandle *h, double value)
{
   setFloat64AttributeEzxml(h->xml, XML_ATTR_SSD_ELEMENT_GEOMETRY_Y2, value, h->ssp);
}

void ssp4c_ssd_elementGeometry_setRotation(ssdElementGeometryHandle *h, double value)
{
    setFloat64AttributeEzxml(h->xml, XML_ATTR_SSD_ELEMENT_GEOMETRY_ROTATION, value, h->ssp);
}

void ssp4c_ssd_elementGeometry_setIconSource(ssdElementGeometryHandle *h, const char *value)
{
    ezxml_set_attr(h->xml, XML_ATTR_SSD_ELEMENT_GEOMETRY_ICON_SOURCE, value);
}

void ssp4c_ssd_elementGeometry_setIconRotation(ssdElementGeometryHandle *h, double value)
{
    setFloat64AttributeEzxml(h->xml, XML_ATTR_SSD_ELEMENT_GEOMETRY_Y2, value, h->ssp);
}

void ssp4c_ssd_elementGeometry_setIconFlip(ssdElementGeometryHandle *h, bool value)
{
    setBooleanAttributeEzxml(h->xml, XML_ATTR_SSD_ELEMENT_GEOMETRY_ICON_FLIP, value);
}

void ssp4c_ssd_elementGeometry_setIconFixedAspectRatio(ssdElementGeometryHandle *h, bool value)
{
    setBooleanAttributeEzxml(h->xml, XML_ATTR_SSD_ELEMENT_GEOMETRY_ICON_FIXED_ASPECT_RATIO, value);
}
