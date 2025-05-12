#include "ssp4c_private.h"
#include "ssp4c_ssv_parameter.h"

const char *ssp4c_ssv_parameter_getName(ssvParameterHandle *h)
{
    return h->name;
}

const char *ssp4c_ssv_parameter_getDescription(ssvParameterHandle *h)
{
    return h->description;
}

const char *ssp4c_ssv_parameter_getId(ssvParameterHandle *h)
{
    return h->id;
}

sspDataType ssp4c_ssv_parameter_getDatatype(ssvParameterHandle *h)
{
    return h->datatype;
}

const char *ssp4c_ssv_parameter_getUnit(ssvParameterHandle *h)
{
    return h->unit;
}

double ssp4c_ssv_parameter_getRealValue(ssvParameterHandle *h)
{
    return h->realValue;
}

double ssp4c_ssv_parameter_getFloat64Value(ssvParameterHandle *h)
{
    return h->float64Value;
}

float ssp4c_ssv_parameter_getFloat32Value(ssvParameterHandle *h)
{
    return h->float32Value;
}

int ssp4c_ssv_parameter_getIntValue(ssvParameterHandle *h)
{
    return h->intValue;
}

int64_t ssp4c_ssv_parameter_getInt64Value(ssvParameterHandle *h)
{
    return h->int64Value;
}

int32_t ssp4c_ssv_parameter_getInt32Value(ssvParameterHandle *h)
{
    return h->int32Value;
}

int16_t ssp4c_ssv_parameter_getInt16Value(ssvParameterHandle *h)
{
    return h->int16Value;
}

int8_t ssp4c_ssv_parameter_getInt8Value(ssvParameterHandle *h)
{
    return h->int8Value;
}

uint64_t ssp4c_ssv_parameter_getUInt64Value(ssvParameterHandle *h)
{
    return h->uint64Value;
}

uint32_t ssp4c_ssv_parameter_getUInt32Value(ssvParameterHandle *h)
{
    return h->uint32Value;
}

uint16_t ssp4c_ssv_parameter_getUInt16Value(ssvParameterHandle *h)
{
    return h->uint16Value;
}

uint8_t ssp4c_ssv_parameter_getUInt8Value(ssvParameterHandle *h)
{
    return h->uint8Value;
}

bool ssp4c_ssv_parameter_getBooleanValue(ssvParameterHandle *h)
{
    return h->booleanValue;
}

const char *ssp4c_ssv_parameter_getStringValue(ssvParameterHandle *h)
{
    return h->stringValue;
}

const char *ssp4c_ssv_parameter_getEnumValue(ssvParameterHandle *h)
{
    return h->enumValue;
}

int ssp4c_ssv_parameter_getNumberOfEnumerationValues(ssvParameterHandle *h)
{
    return h->enumValuesCount;
}

const char *ssp4c_ssv_parameter_getEnumerationValueByIndex(ssvParameterHandle *h, int i)
{
    return (h->enumValues)[i];
}
