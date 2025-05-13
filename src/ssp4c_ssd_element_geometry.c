#include "ssp4c_private.h"
#include "ssp4c_ssd_element_geometry.h"
#include "ssp4c_utils.h"

double ssp4c_ssd_elementGeometry_getX1(ssdElementGeometryHandle *h)
{
    return h->x1;
}

double ssp4c_ssd_elementGeometry_getY1(ssdElementGeometryHandle *h)
{
    return h->y1;
}

double ssp4c_ssd_elementGeometry_getX2(ssdElementGeometryHandle *h)
{
    return h->x2;
}

double ssp4c_ssd_elementGeometry_getY2(ssdElementGeometryHandle *h)
{
    return h->y2;
}

double ssp4c_ssd_elementGeometry_getRotation(ssdElementGeometryHandle *h)
{
    return h->rotation;
}

const char* ssp4c_ssd_elementGeometry_getIconSource(ssdElementGeometryHandle *h)
{
    return h->iconSource;
}

double ssp4c_ssd_elementGeometry_getIconRotation(ssdElementGeometryHandle *h)
{
    return h->iconRotation;
}

bool ssp4c_ssd_elementGeometry_getIconFlip(ssdElementGeometryHandle *h)
{
    return h->iconFlip;
}

bool ssp4c_ssd_elementGeometry_getIconFixedAspectRatio(ssdElementGeometryHandle *h)
{
    return h->iconFixedAspectRatio;
}

void ezxml_set_attr_copy(ezxml_t xml, const char *key, const char *value, sspHandle *ssp) {

    char *key_copy = duplicateAndRememberString(ssp, key);
    char *val_copy = duplicateAndRememberString(ssp, value);
    ezxml_set_attr(xml, key_copy, val_copy);

}

void ssp4c_ssd_elementGeometry_setX1(ssdElementGeometryHandle *h, double value)
{
    h->x1 = value;
    char buf[255];
    sprintf(buf, "%f", value);
    ezxml_set_attr_copy(h->xml, "x1", buf, h->ssp);
}
