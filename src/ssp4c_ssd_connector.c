#include "ssp4c_private.h"
#include "ssp4c_ssd_connector.h"
#include "ssp4c_xml_constants.h"

const char* ssp4c_ssd_connector_getName(ssdConnectorHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_NAME);
}

const char* ssp4c_ssd_connector_getDescription(ssdConnectorHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_DESCRIPTION);
}

const char *ssp4c_ssd_connector_getId(ssdConnectorHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_ID);
}

const char* ssp4c_ssd_connector_getUnit(ssdConnectorHandle *h)
{
    ezxml_t realElement = ezxml_child(h->xml, XML_ELEMENT_SSC_REAL);
    if(realElement) {
        return ezxml_attr(realElement, XML_ATTR_UNIT);
    }

    ezxml_t float64Element = ezxml_child(h->xml, XML_ELEMENT_SSC_FLOAT64);
    if(float64Element) {
        return ezxml_attr(float64Element, XML_ATTR_UNIT);
    }

    ezxml_t float32Element = ezxml_child(h->xml, XML_ELEMENT_SSC_FLOAT32);
    if(float32Element) {
        return ezxml_attr(float32Element, XML_ATTR_UNIT);
    }
    return NULL;
}

sspDataType ssp4c_ssd_connector_getDatatype(ssdConnectorHandle *h)
{
    for(ezxml_t subElement = h->xml->child; subElement; subElement = subElement->ordered) {
        if(!strcmp(subElement->name, XML_ELEMENT_SSC_REAL)) {
            return sspDataTypeReal;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSC_FLOAT64)) {
            return sspDataTypeFloat64;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSC_FLOAT32)) {
            return sspDataTypeFloat32;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSC_INTEGER)) {
            return sspDataTypeInteger;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSC_INT8)) {
            return sspDataTypeInt8;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSC_UINT8)) {
            return sspDataTypeUInt8;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSC_INT16)) {
            return sspDataTypeInt16;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSC_UINT16)) {
            return sspDataTypeUInt16;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSC_INT32)) {
            return sspDataTypeInt32;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSC_UINT32)) {
            return sspDataTypeUInt32;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSC_INT64)) {
            return sspDataTypeInt64;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSC_UINT64)) {
            return sspDataTypeUInt64;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSC_BOOLEAN)) {
            return sspDataTypeBoolean;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSC_STRING)) {
            return sspDataTypeString;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSC_ENUMERATION)) {
            return sspDataTypeEnumeration;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSC_BINARY)) {
            return sspDataTypeBinary;
        }
    }
    return sspDataTypeUnspecified;
}

ssdConnectorKind ssp4c_ssd_connector_getKind(ssdConnectorHandle *h)
{
    const char* kind = ezxml_attr(h->xml, XML_ATTR_KIND);

    if(!strcmp(kind, XML_VALUE_INPUT)) {
        return ssdConnectorKindInput;
    }
    else if(!strcmp(kind, XML_VALUE_OUTPUT)) {
        return ssdConnectorKindOutput;
    }
    else if(!strcmp(kind, XML_VALUE_PARAMETER)) {
        return ssdConnectorKindParameter;
    }
    else if(!strcmp(kind, XML_VALUE_CALCULATED_PARAMETER)) {
        return ssdConnectorKindCalculatedParameter;
    }
    else if(!strcmp(kind, XML_VALUE_STRUCTURAL_PARAMETER)) {
        return ssdConnectorKindStructuralParameter;
    }
    else if(!strcmp(kind, XML_VALUE_CALCULATED_CONSTANT)) {
        return ssdConnectorKindConstant;
    }
    else if(!strcmp(kind, XML_VALUE_LOCAL)) {
        return ssdConnectorKindLocal;
    }
    else if(!strcmp(kind, XML_VALUE_INOUT)) {
        return ssdConnectorKindInout;
    }
    return ssdConnectorKindUnspecified;
}

