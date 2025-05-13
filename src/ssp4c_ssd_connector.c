#include "ssp4c_private.h"
#include "ssp4c_ssd_connector.h"

// XML attribute name constants
const char* XML_ATTR_SSD_CONNECTOR_NAME = "name";
const char* XML_ATTR_SSD_CONNETOR_DESCRIPTION = "description";
const char* XML_ATTR_SSD_CONNECTOR_ID = "id";
const char* XML_ATTR_SSD_CONNECTOR_DATATYPE = "datatype";
const char* XML_ATTR_SSC_REAL_UNIT = "unit";
const char* XML_ATTR_SSD_CONNECTOR_KIND = "kind";

const char* XML_ELEMENT_SSC_REAL = "ssc:Real";
const char* XML_ELEMENT_SSC_FLOAT64 = "ssc:Float64";
const char* XML_ELEMENT_SSC_FLOAT32 = "ssc:Float32";

const char* ssp4c_ssd_connector_getName(ssdConnectorHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_CONNECTOR_NAME);
}

const char* ssp4c_ssd_connector_getDescription(ssdConnectorHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_CONNETOR_DESCRIPTION);
}

const char *ssp4c_ssd_connector_getId(ssdConnectorHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSD_CONNECTOR_ID);
}

const char* ssp4c_ssd_connector_getUnit(ssdConnectorHandle *h)
{
    ezxml_t realElement = ezxml_child(h->xml, XML_ELEMENT_SSC_REAL);
    if(realElement) {
        return ezxml_attr(realElement, XML_ATTR_SSC_REAL_UNIT);
    }

    ezxml_t float64Element = ezxml_child(h->xml, XML_ELEMENT_SSC_FLOAT64);
    if(float64Element) {
        return ezxml_attr(float64Element, XML_ATTR_SSC_REAL_UNIT);
    }

    ezxml_t float32Element = ezxml_child(h->xml, XML_ELEMENT_SSC_FLOAT32);
    if(float32Element) {
        return ezxml_attr(float32Element, XML_ATTR_SSC_REAL_UNIT);
    }
    return NULL;
}

sspDataType ssp4c_ssd_connector_getDatatype(ssdConnectorHandle *h)
{
    for(ezxml_t subElement = h->xml->child; subElement; subElement = subElement->ordered) {
        if(!strcmp(subElement->name, "ssc:Real")) {
            return sspDataTypeReal;
        }
        else if(!strcmp(subElement->name, "ssc:Float64")) {
            return sspDataTypeFloat64;
        }
        else if(!strcmp(subElement->name, "ssc:Float32")) {
            return sspDataTypeFloat32;
        }
        else if(!strcmp(subElement->name, "ssc:Integer")) {
            return sspDataTypeInteger;
        }
        else if(!strcmp(subElement->name, "ssc:Int8")) {
            return sspDataTypeInt8;
        }
        else if(!strcmp(subElement->name, "ssc:UInt8")) {
            return sspDataTypeUInt8;
        }
        else if(!strcmp(subElement->name, "ssc:Int16")) {
            return sspDataTypeInt16;
        }
        else if(!strcmp(subElement->name, "ssc:UInt16")) {
            return sspDataTypeUInt16;
        }
        else if(!strcmp(subElement->name, "ssc:Int32")) {
            return sspDataTypeInt32;
        }
        else if(!strcmp(subElement->name, "ssc:UInt32")) {
            return sspDataTypeUInt32;
        }
        else if(!strcmp(subElement->name, "ssc:Int64")) {
            return sspDataTypeInt64;
        }
        else if(!strcmp(subElement->name, "ssc:UInt64")) {
            return sspDataTypeUInt64;
        }
        else if(!strcmp(subElement->name, "ssc:Boolean")) {
            return sspDataTypeBoolean;
        }
        else if(!strcmp(subElement->name, "ssc:String")) {
            return sspDataTypeString;
        }
        else if(!strcmp(subElement->name, "ssc:Enumeration")) {
            return sspDataTypeEnumeration;
        }
        else if(!strcmp(subElement->name, "ssc:Binary")) {
            return sspDataTypeBinary;
        }
    }
    return sspDataTypeUnspecified;
}

ssdConnectorKind ssp4c_ssd_connector_getKind(ssdConnectorHandle *h)
{
    const char* kind = ezxml_attr(h->xml, XML_ATTR_SSD_CONNECTOR_KIND);

    if(!strcmp(kind, "input")) {
        return ssdConnectorKindInput;
    }
    else if(!strcmp(kind, "output")) {
        return ssdConnectorKindOutput;
    }
    else if(!strcmp(kind, "parameter")) {
        return ssdConnectorKindParameter;
    }
    else if(!strcmp(kind, "calculatedParameter")) {
        return ssdConnectorKindCalculatedParameter;
    }
    else if(!strcmp(kind, "calculatedParameter")) {
        return ssdConnectorKindStructuralParameter;
    }
    else if(!strcmp(kind, "calculatedConstant")) {
        return ssdConnectorKindConstant;
    }
    else if(!strcmp(kind, "local")) {
        return ssdConnectorKindLocal;
    }
    else if(!strcmp(kind, "inout")) {
        return ssdConnectorKindInout;
    }
    return ssdConnectorKindUnspecified;
}

