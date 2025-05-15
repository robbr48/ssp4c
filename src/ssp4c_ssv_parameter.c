#include "ssp4c_private.h"
#include "ssp4c_ssv_parameter.h"
#include "ssp4c_xml_constants.h"
#include "ssp4c_utils.h"

const char *ssp4c_ssv_parameter_getName(ssvParameterHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_NAME);
}

const char *ssp4c_ssv_parameter_getDescription(ssvParameterHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_DESCRIPTION);
}

const char *ssp4c_ssv_parameter_getId(ssvParameterHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_ID);
}

sspDataType ssp4c_ssv_parameter_getDatatype(ssvParameterHandle *h)
{
    //return h->datatype;
    for(ezxml_t subElement = h->xml->child; subElement; subElement = subElement->ordered) {
        if(!strcmp(subElement->name, XML_ELEMENT_SSV_REAL)) {
            return sspDataTypeReal;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSV_FLOAT64)) {
            return sspDataTypeFloat64;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSV_FLOAT32)) {
            return sspDataTypeFloat32;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSV_INTEGER)) {
            return sspDataTypeInteger;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSV_INT8)) {
            return sspDataTypeInt8;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSV_UINT8)) {
            return sspDataTypeUInt8;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSV_INT16)) {
            return sspDataTypeInt16;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSV_UINT16)) {
            return sspDataTypeUInt16;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSV_INT32)) {
            return sspDataTypeInt32;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSV_UINT32)) {
            return sspDataTypeUInt32;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSV_INT64)) {
            return sspDataTypeInt64;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSV_UINT64)) {
            return sspDataTypeUInt64;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSV_BOOLEAN)) {
            return sspDataTypeBoolean;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSV_STRING)) {
            return sspDataTypeString;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSV_ENUMERATION)) {
            return sspDataTypeEnumeration;
        }
        else if(!strcmp(subElement->name, XML_ELEMENT_SSV_BINARY)) {
            return sspDataTypeBinary;
        }
    }
    return sspDataTypeUnspecified;
}

const char *ssp4c_ssv_parameter_getUnit(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, XML_ELEMENT_SSV_REAL);
    if(dataElement) {
        return ezxml_attr(dataElement, XML_ATTR_UNIT);
    }

    ezxml_t float64Element = ezxml_child(h->xml, XML_ELEMENT_SSV_FLOAT64);
    if(float64Element) {
        return ezxml_attr(float64Element, XML_ATTR_UNIT);
    }

    ezxml_t float32Element = ezxml_child(h->xml, XML_ELEMENT_SSV_FLOAT32);
    if(float32Element) {
        return ezxml_attr(float32Element, XML_ATTR_UNIT);
    }
    return NULL;
}

double ssp4c_ssv_parameter_getRealValue(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, XML_ELEMENT_SSV_REAL);
    if(dataElement) {
        double value;
        if(parseFloat64AttributeEzXml(dataElement, XML_ATTR_VALUE, &value)) {
            return value;
        }
    }
    return 0;
}

double ssp4c_ssv_parameter_getFloat64Value(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, XML_ELEMENT_SSV_FLOAT64);
    if(dataElement) {
        double value;
        if(parseFloat64AttributeEzXml(dataElement, XML_ATTR_VALUE, &value)) {
            return value;
        }
    }
    return 0;
}

float ssp4c_ssv_parameter_getFloat32Value(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, XML_ELEMENT_SSV_FLOAT32);
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, XML_ATTR_VALUE);
        if(valueStr) {
            return atof(valueStr);
        }
    }
    return 0;
}

int ssp4c_ssv_parameter_getIntValue(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, XML_ELEMENT_SSV_INTEGER);
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, XML_ATTR_VALUE);
        if(valueStr) {
            return atoi(valueStr);
        }
    }
    return 0;
}

int64_t ssp4c_ssv_parameter_getInt64Value(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, XML_ELEMENT_SSV_INT64);
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, XML_ATTR_VALUE);
        if(valueStr) {
            return atoi(valueStr);
        }
    }
    return 0;
}

int32_t ssp4c_ssv_parameter_getInt32Value(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, XML_ELEMENT_SSV_INT32);
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, XML_ATTR_VALUE);
        if(valueStr) {
            return atoi(valueStr);
        }
    }
    return 0;
}

int16_t ssp4c_ssv_parameter_getInt16Value(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, XML_ELEMENT_SSV_INT16);
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, XML_ATTR_VALUE);
        if(valueStr) {
            return atoi(valueStr);
        }
    }
    return 0;
}

int8_t ssp4c_ssv_parameter_getInt8Value(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, XML_ELEMENT_SSV_INT8);
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, XML_ATTR_VALUE);
        if(valueStr) {
            return atoi(valueStr);
        }
    }
    return 0;
}

uint64_t ssp4c_ssv_parameter_getUInt64Value(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, XML_ELEMENT_SSV_UINT64);
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, XML_ATTR_VALUE);
        if(valueStr) {
            return atoi(valueStr);
        }
    }
    return 0;
}

uint32_t ssp4c_ssv_parameter_getUInt32Value(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, XML_ELEMENT_SSV_UINT32);
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, XML_ATTR_VALUE);
        if(valueStr) {
            return atoi(valueStr);
        }
    }
    return 0;
}

uint16_t ssp4c_ssv_parameter_getUInt16Value(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, XML_ELEMENT_SSV_UINT16);
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, XML_ATTR_VALUE);
        if(valueStr) {
            return atoi(valueStr);
        }
    }
    return 0;
}

uint8_t ssp4c_ssv_parameter_getUInt8Value(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, XML_ELEMENT_SSV_UINT8);
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, XML_ATTR_VALUE);
        if(valueStr) {
            return atoi(valueStr);
        }
    }
    return 0;
}

bool ssp4c_ssv_parameter_getBooleanValue(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, XML_ELEMENT_SSV_BOOLEAN);
    if(dataElement) {
        bool value;
        if(parseBooleanAttributeEzXml(dataElement, XML_ATTR_VALUE, &value)) {
            return value;
        }
    }
    return false;
}

const char *ssp4c_ssv_parameter_getStringValue(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, XML_ELEMENT_SSV_STRING);
    if(dataElement) {
        return ezxml_attr(dataElement, XML_ATTR_VALUE);
    }
    return NULL;
}

const char *ssp4c_ssv_parameter_getEnumValue(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, XML_ELEMENT_SSV_ENUMERATION);
    if(dataElement) {
        return ezxml_attr(dataElement, XML_ATTR_VALUE);
    }
    return NULL;
}

int ssp4c_ssv_parameter_getNumberOfEnumerationValues(ssvParameterHandle *h)
{
    int count = 0;
    ezxml_t dataElement = ezxml_child(h->xml, XML_ELEMENT_SSV_ENUMERATION);
    if(dataElement) {
        ezxml_t valueElement = ezxml_child(dataElement, XML_ELEMENT_SSV_VALUE);
        while(valueElement) {
            ++(count);
            valueElement = valueElement->next;
        }
    }
    return count;
}

const char *ssp4c_ssv_parameter_getEnumerationValueByIndex(ssvParameterHandle *h, int i)
{
    ezxml_t dataElement = ezxml_child(h->xml, XML_ELEMENT_SSV_ENUMERATION);
    if(dataElement) {
        ezxml_t valueElement = ezxml_child(dataElement, XML_ELEMENT_SSV_VALUE);
        for(int j=0; j<i; ++j) {
            valueElement = valueElement->next;
        }
        if(valueElement) {
            return ezxml_attr(valueElement, XML_ATTR_VALUE);
        }
    }
    return NULL;
}
