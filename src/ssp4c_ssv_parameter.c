#include "ssp4c_private.h"
#include "ssp4c_ssv_parameter.h"


const char* XML_ATTR_SSV_PARAMETER_NAME = "name";
const char* XML_ATTR_SSV_PARAMETER_DESCRIPTION = "description";
const char* XML_ATTR_SSV_PARAMETER_ID = "id";
const char* XML_ATTR_SSV_PARAMETER_DATATYPE = "datatype";
const char* XML_ATTR_SSV_PARAMETER_UNIT = "unit";
// const char* XML_ATTR_SSV_PARAMETER_FILE_VERSION = "fileversion";
// const char* XML_ATTR_SSV_PARAMETER_COPYRIGHT = "copyright";
// const char* XML_ATTR_SSV_PARAMETER_LICENSE = "license";
// const char* XML_ATTR_SSV_PARAMETER_GENERATION_TOOL = "generationTool";
// const char* XML_ATTR_SSV_PARAMETER_GENERATION_DATE_AND_TIME = "generationDateAndTime";

const char *ssp4c_ssv_parameter_getName(ssvParameterHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSV_PARAMETER_NAME);
}

const char *ssp4c_ssv_parameter_getDescription(ssvParameterHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSV_PARAMETER_DESCRIPTION);
}

const char *ssp4c_ssv_parameter_getId(ssvParameterHandle *h)
{
    return ezxml_attr(h->xml, XML_ATTR_SSV_PARAMETER_ID);
}

sspDataType ssp4c_ssv_parameter_getDatatype(ssvParameterHandle *h)
{
    //return h->datatype;
    for(ezxml_t subElement = h->xml->child; subElement; subElement = subElement->ordered) {
        if(!strcmp(subElement->name, "ssv:Real")) {
            return sspDataTypeReal;
        }
        else if(!strcmp(subElement->name, "ssv:Float64")) {
            return sspDataTypeFloat64;
        }
        else if(!strcmp(subElement->name, "ssv:Float32")) {
            return sspDataTypeFloat32;
        }
        else if(!strcmp(subElement->name, "ssv:Integer")) {
            return sspDataTypeInteger;
        }
        else if(!strcmp(subElement->name, "ssv:Int8")) {
            return sspDataTypeInt8;
        }
        else if(!strcmp(subElement->name, "ssv:UInt8")) {
            return sspDataTypeUInt8;
        }
        else if(!strcmp(subElement->name, "ssv:Int16")) {
            return sspDataTypeInt16;
        }
        else if(!strcmp(subElement->name, "ssv:UInt16")) {
            return sspDataTypeUInt16;
        }
        else if(!strcmp(subElement->name, "ssv:Int32")) {
            return sspDataTypeInt32;
        }
        else if(!strcmp(subElement->name, "ssv:UInt32")) {
            return sspDataTypeUInt32;
        }
        else if(!strcmp(subElement->name, "ssv:Int64")) {
            return sspDataTypeInt64;
        }
        else if(!strcmp(subElement->name, "ssv:UInt64")) {
            return sspDataTypeUInt64;
        }
        else if(!strcmp(subElement->name, "ssv:Boolean")) {
            return sspDataTypeBoolean;
        }
        else if(!strcmp(subElement->name, "ssv:String")) {
            return sspDataTypeString;
        }
        else if(!strcmp(subElement->name, "ssv:Enumeration")) {
            return sspDataTypeEnumeration;
        }
        else if(!strcmp(subElement->name, "ssv:Binary")) {
            return sspDataTypeBinary;
        }
    }
    return sspDataTypeUnspecified;
}

const char *ssp4c_ssv_parameter_getUnit(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, "ssv:Real");
    if(dataElement) {
        return ezxml_attr(dataElement, XML_ATTR_SSV_PARAMETER_UNIT);
    }

    ezxml_t float64Element = ezxml_child(h->xml, "ssv:Float64");
    if(float64Element) {
        return ezxml_attr(float64Element, XML_ATTR_SSV_PARAMETER_UNIT);
    }

    ezxml_t float32Element = ezxml_child(h->xml, "ssv:Float32");
    if(float32Element) {
        return ezxml_attr(float32Element, XML_ATTR_SSV_PARAMETER_UNIT);
    }
    return NULL;
}

double ssp4c_ssv_parameter_getRealValue(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, "ssv:Real");
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, "value");
        if(valueStr) {
            return atof(valueStr);
        }
    }
    return 0;
}

double ssp4c_ssv_parameter_getFloat64Value(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, "ssv:Float64");
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, "value");
        if(valueStr) {
            return atof(valueStr);
        }
    }
    return 0;
}

float ssp4c_ssv_parameter_getFloat32Value(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, "ssv:Float32");
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, "value");
        if(valueStr) {
            return atof(valueStr);
        }
    }
    return 0;
}

int ssp4c_ssv_parameter_getIntValue(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, "ssv:Integer");
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, "value");
        if(valueStr) {
            return atoi(valueStr);
        }
    }
    return 0;
}

int64_t ssp4c_ssv_parameter_getInt64Value(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, "ssv:Int64");
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, "value");
        if(valueStr) {
            return atoi(valueStr);
        }
    }
    return 0;
}

int32_t ssp4c_ssv_parameter_getInt32Value(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, "ssv:Int32");
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, "value");
        if(valueStr) {
            return atoi(valueStr);
        }
    }
    return 0;
}

int16_t ssp4c_ssv_parameter_getInt16Value(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, "ssv:In1t6");
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, "value");
        if(valueStr) {
            return atoi(valueStr);
        }
    }
    return 0;
}

int8_t ssp4c_ssv_parameter_getInt8Value(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, "ssv:Int8");
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, "value");
        if(valueStr) {
            return atoi(valueStr);
        }
    }
    return 0;
}

uint64_t ssp4c_ssv_parameter_getUInt64Value(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, "ssv:UInt64");
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, "value");
        if(valueStr) {
            return atoi(valueStr);
        }
    }
    return 0;
}

uint32_t ssp4c_ssv_parameter_getUInt32Value(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, "ssv:UInt32");
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, "value");
        if(valueStr) {
            return atoi(valueStr);
        }
    }
    return 0;
}

uint16_t ssp4c_ssv_parameter_getUInt16Value(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, "ssv:UInt16");
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, "value");
        if(valueStr) {
            return atoi(valueStr);
        }
    }
    return 0;
}

uint8_t ssp4c_ssv_parameter_getUInt8Value(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, "ssv:UInt8");
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, "value");
        if(valueStr) {
            return atoi(valueStr);
        }
    }
    return 0;
}

bool ssp4c_ssv_parameter_getBooleanValue(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, "ssv:Boolean");
    if(dataElement) {
        const char* valueStr = ezxml_attr(dataElement, "value");
        if(valueStr) {
            return !strcmp(valueStr, "true");
        }
    }
    return false;
}

const char *ssp4c_ssv_parameter_getStringValue(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, "ssv:Boolean");
    if(dataElement) {
        return ezxml_attr(dataElement, "value");
    }
    return NULL;
}

const char *ssp4c_ssv_parameter_getEnumValue(ssvParameterHandle *h)
{
    ezxml_t dataElement = ezxml_child(h->xml, "ssv:Enumeration");
    if(dataElement) {
        return ezxml_attr(dataElement, "value");
    }
    return NULL;
}

int ssp4c_ssv_parameter_getNumberOfEnumerationValues(ssvParameterHandle *h)
{
    int count = 0;
    ezxml_t dataElement = ezxml_child(h->xml, "ssv:Enumeration");
    if(dataElement) {
        ezxml_t valueElement = ezxml_child(dataElement, "ssv:Value");
        while(valueElement) {
            ++(count);
            valueElement = valueElement->next;
        }
    }
    return count;
}

const char *ssp4c_ssv_parameter_getEnumerationValueByIndex(ssvParameterHandle *h, int i)
{
    ezxml_t dataElement = ezxml_child(h->xml, "ssv:Enumeration");
    if(dataElement) {
        ezxml_t valueElement = ezxml_child(dataElement, "ssv:Value");
        for(int j=0; j<i; ++j) {
            valueElement = valueElement->next;
        }
        if(valueElement) {
            return ezxml_attr(valueElement, "value");
        }
    }
    return NULL;
}
