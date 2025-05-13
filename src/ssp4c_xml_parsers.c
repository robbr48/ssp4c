#include "ssp4c_private.h"
#include "ssp4c_ssd.h"
#include "ssp4c_xml_parsers.h"
#include "ssp4c_utils.h"

bool parseSsd(sspHandle *ssp, ssdHandle *ssd, const char* path)
{
    char cwd[FILENAME_MAX];
#ifdef _WIN32
    _getcwd(cwd, sizeof(char)*FILENAME_MAX);
#else
    getcwd(cwd, sizeof(char)*FILENAME_MAX);
#endif
    chdir(ssp->unzippedLocation);

    ssd->xml = ezxml_parse_file(path);
    if(strcmp(ssd->xml ->name, "ssd:SystemStructureDescription")) {
        printf("Wrong root tag name: %s\n", ssd->xml ->name);
        return false;
    }

    ezxml_t systemElement = ezxml_child(ssd->xml , "ssd:System");
    if(systemElement) {

        //Parse connectors
        ezxml_t connectorsElement = ezxml_child(systemElement, "ssd:Connectors");
        if(connectorsElement) {
            ssd->connectors = mallocAndRememberPointer(ssp, sizeof(ssdConnectorsHandle));
            parseSsdConnectorsElement(connectorsElement, ssd->connectors, ssp);
        }

        // Parse components
        ssd->components = NULL;
        ezxml_t componentsElement = ezxml_child(systemElement, "ssd:Elements");
        if (componentsElement) {
            ssd->components = mallocAndRememberPointer(ssp, sizeof(ssdComponentsHandle));
            parseSsdComponentsElement(componentsElement, ssd->components, ssp);
        }
    }

    chdir(cwd);

    return true;
}

bool parseSsdConnectorsElement(ezxml_t element, ssdConnectorsHandle* h, sspHandle *ssp)
{
    h->xml = element;

    h->connectorsCount = 0;
    for(ezxml_t connectorElement = element->child; connectorElement; connectorElement = connectorElement->ordered) {
        if(!strcmp(connectorElement->name, "ssd:Connector")) {
            ++(h->connectorsCount);  //Just count them for now, so we can allocate memory before loading them
        }
    }
    if((h->connectorsCount) > 0) {
        h->connectors = mallocAndRememberPointer(ssp, (h->connectorsCount)*sizeof(ssdConnectorHandle));
        int i=0;
        for(ezxml_t connectorElement = element->child; connectorElement; connectorElement = connectorElement->ordered) {
            if(!strcmp(connectorElement->name, "ssd:Connector")) {
                parseSsdConnectorElement(connectorElement, &(h->connectors[i]), ssp);
                ++i;
            }
        }
    }

    return true;
}

bool parseSsdConnectorElement(ezxml_t element, ssdConnectorHandle *h, sspHandle *ssp)
{
    h->xml = element;

    return true;
}

bool parseSsdComponentsElement(ezxml_t element, ssdComponentsHandle* h, sspHandle *ssp)
{
    h->xml = element;

    h->componentsCount = 0;
    for (ezxml_t componentElement = element->child; componentElement; componentElement = componentElement->ordered) {
        if (!strcmp(componentElement->name, "ssd:Component")) {
            ++h->componentsCount;
        }
    }

    if (h->componentsCount > 0) {
        h->components = mallocAndRememberPointer(ssp, sizeof(ssdComponentHandle) * h->componentsCount);

        int i = 0;
        for (ezxml_t componentElement = element->child; componentElement; componentElement = componentElement->ordered) {
            if (!strcmp(componentElement->name, "ssd:Component")) {
                parseSsdComponentElement(componentElement, &(h->components[i]), ssp);
                ++i;
            }
        }
    }
    return true;
}

bool parseSsdComponentElement(ezxml_t element, ssdComponentHandle* h, sspHandle *ssp)
{
    h->xml = element;

    //Parse connectors
    h->connectors = mallocAndRememberPointer(ssp, sizeof(ssdConnectorsHandle));
    ezxml_t componentConnectorsElement = ezxml_child(element, "ssd:Connectors");
    if(componentConnectorsElement) {
        parseSsdConnectorsElement(componentConnectorsElement, h->connectors, ssp);
    }

    //Parse parameter bindings
    // Parse geometry

    ezxml_t geometryElement = ezxml_child(element, "ssd:ElementGeometry");
    if(geometryElement) {
        h->geometry = mallocAndRememberPointer(ssp, sizeof(ssdElementGeometryHandle));
        parseSsdElementGeometryElement(geometryElement, h->geometry, ssp);
    }

    ezxml_t parameterBindingsElement = ezxml_child(element, "ssd:ParameterBindings");
    if(parameterBindingsElement) {
        h->parameterBindings = mallocAndRememberPointer(ssp, sizeof(ssdParameterBindingsHandle));
        parseSsdParameterBindingsElement(parameterBindingsElement, h->parameterBindings, ssp);
    }

    return true;
}

bool parseSsdElementGeometryElement(ezxml_t element, ssdElementGeometryHandle *h, sspHandle *ssp)
{
    h->xml = element;
    h->ssp = ssp;
    return true;
}

bool parseSsdParameterBindingsElement(ezxml_t element, ssdParameterBindingsHandle* h, sspHandle *ssp)
{
    h->xml = element;
    h->parameterBindingsCount = 0;

    for (ezxml_t parameterBindingElement = element->child; parameterBindingElement ; parameterBindingElement  = parameterBindingElement ->ordered) {
        if (!strcmp(parameterBindingElement ->name, "ssd:ParameterBinding")) {
            ++h->parameterBindingsCount;
        }
    }

    if (h->parameterBindingsCount > 0) {
        h->parameterBindings = mallocAndRememberPointer(ssp, sizeof(ssdParameterBindingHandle) * h->parameterBindingsCount);


        int i = 0;
        for (ezxml_t parameterBindingsElement = element->child; parameterBindingsElement; parameterBindingsElement = parameterBindingsElement->ordered) {
            if (!strcmp(parameterBindingsElement->name, "ssd:ParameterBinding")) {
                parseSsdParameterBindingElement(parameterBindingsElement, &(h->parameterBindings[i]), ssp);
                ++i;
            }
        }
    }

    return true;
}

bool parseSsdParameterBindingElement(ezxml_t element, ssdParameterBindingHandle *h, sspHandle *ssp)
{
    h->xml = element;
    h->type = NULL;
    h->source = NULL;
    h->prefix = NULL;
    parseStringAttributeEzXmlAndRememberPointer(element, "type", &(h->type), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "source", &(h->source), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "prefix", &(h->prefix), ssp);

    h->sourceBase = ssdParameterSourceBaseSSD;
    const char* sourceBase = NULL;
    if(parseStringAttributeEzXml(element, "sourceBase", &sourceBase)) {
        if(!strcmp(sourceBase, "SSD")) {
            h->sourceBase = ssdParameterSourceBaseSSD;
        }
        else if(!strcmp(sourceBase, "component")) {
            h->sourceBase = ssdParameterSourceBaseComponent;
        }
        freeDuplicatedConstChar(sourceBase);
    }

    //Parse parameter sets
    h->parameterValues = NULL;
    ezxml_t parameterValuesElement = ezxml_child(element, "ssd:ParameterValues");
    if(parameterValuesElement) {
        h->parameterValues = mallocAndRememberPointer(ssp, sizeof(ssdParameterValuesHandle));
        parseSsdParameterValuesElement(parameterValuesElement, h->parameterValues, ssp);
    }

    //Parse parameter mappings
    h->parameterMapping = NULL;
    ezxml_t parameterMappingElement = ezxml_child(element, "ssd:ParameterMapping");
    if(parameterMappingElement) {
        h->parameterMapping = mallocAndRememberPointer(ssp, sizeof(ssdParameterMappingHandle));
        parseSsdParameterMappingElement(parameterMappingElement, h->parameterMapping, ssp);
    }

    return true;
}

bool parseSsdParameterValuesElement(ezxml_t element, ssdParameterValuesHandle* h, sspHandle *ssp)
{
    h->xml = element;
    h->parameterSet = NULL;
    ezxml_t parameterSetElement = ezxml_child(element, "ssv:ParameterSet");
    if(parameterSetElement) {
        h->parameterSet = mallocAndRememberPointer(ssp, sizeof(ssvParameterSetHandle));
        parseSsvParameterSetElement(parameterSetElement, h->parameterSet, ssp);
    }

    return true;
}

bool parseSsdParameterMappingElement(ezxml_t element,ssdParameterMappingHandle* h, sspHandle *ssp)
{
    h->xml = element;
    h->id = NULL;
    h->description = NULL;
    h->type = NULL;
    h->source = NULL;
    h->sourceBase = ssdParameterSourceBaseSSD;
    parseStringAttributeEzXmlAndRememberPointer(element, "id", &(h->id), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "description", &(h->description), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "type", &(h->type), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "source", &(h->source), ssp);

    h->sourceBase = ssdParameterSourceBaseSSD;
    const char* sourceBase = NULL;
    if(parseStringAttributeEzXml(element, "sourceBase", &sourceBase)) {
        if(!strcmp(sourceBase, "SSD")) {
            h->sourceBase = ssdParameterSourceBaseSSD;
        }
        else if(!strcmp(sourceBase, "component")) {
            h->sourceBase = ssdParameterSourceBaseComponent;
        }
        freeDuplicatedConstChar(sourceBase);
    }

    //Parse parameter entries
    h->parameterMapping = NULL;
    ezxml_t ssmParameterMappingElement = ezxml_child(element, "ssm:ParameterMapping");
    if(ssmParameterMappingElement) {
        h->parameterMapping = mallocAndRememberPointer(ssp, sizeof(ssmParameterMappingHandle));
        parseSsmParameterMappingElement(ssmParameterMappingElement, h->parameterMapping, ssp);
    }

    return true;
}

bool parseSsmParameterMappingElement(ezxml_t element, ssmParameterMappingHandle *h, sspHandle *ssp)
{
    h->xml = element;
    h->id = NULL;
    h->description = NULL;
    h->author= NULL;
    h->fileversion = NULL;
    h->copyright = NULL;
    h->license = NULL;
    h->generationTool = NULL;
    h->generationDateAndTime = NULL;
    h->version = NULL;
    parseStringAttributeEzXmlAndRememberPointer(element, "id", &(h->id), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "description", &(h->description), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "author", &(h->author), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "fileversion", &(h->fileversion), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "copyright", &(h->copyright), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "license", &(h->license), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "generationTool", &(h->generationTool), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "generationDateAndTime", &(h->generationDateAndTime), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "version", &(h->version), ssp);

    h->mappingEntryCount = 0;
    for(ezxml_t entryElement = element->child; entryElement; entryElement = entryElement->ordered) {
        if (!strcmp(entryElement->name, "ssm:MappingEntry")) {
            h->mappingEntryCount++;
        }
    }

    if (h->mappingEntryCount > 0) {
        int i=0;
        h->mappingEntries = mallocAndRememberPointer(ssp, sizeof(ssmParameterMappingEntryHandle)*h->mappingEntryCount);
        for(ezxml_t entryElement = element->child; entryElement; entryElement = entryElement->ordered) {
            parseSsmMappingEntryElement(entryElement, &(h->mappingEntries[i]), ssp);
            ++i;
        }
    }

    return true;
}

bool parseSsmMappingEntryElement(ezxml_t element, ssmParameterMappingEntryHandle *h, sspHandle *ssp)
{
    h->xml = element;
    h->id = NULL;
    h->description = NULL;
    h->source = NULL;
    h->target = NULL;
    h->suppressUnitConveresion = false;
    parseStringAttributeEzXmlAndRememberPointer(element, "id", &(h->id), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "description", &(h->description), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "source", &(h->source), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "target", &(h->target), ssp);
    parseBooleanAttributeEzXml(element, "suppressUnitConersion", &(h->suppressUnitConveresion));

    h->transform = NULL;
    ezxml_t transformationChoiceElement = ezxml_child(element, "ssc:TransformationChoice");
    if(transformationChoiceElement) {
        h->transform = mallocAndRememberPointer(ssp, sizeof(sscMappingTransformHandle));
        parseSscTransformationChoiceElement(transformationChoiceElement, h->transform, ssp);
    }
    return true;
}

bool parseSscTransformationChoiceElement(ezxml_t element, sscMappingTransformHandle *h, sspHandle *ssp)
{
    h->xml = element;
    ezxml_t transformationElement = element->child;
    h->factor = 1;
    h->offset = 0;

    if (!strcmp(transformationElement->name, "ssc:LinearTransformation")) {

        h->type = sscMappingTransformLinear;
        parseFloat64AttributeEzXml(transformationElement, "factor", &(h->factor));
        parseFloat64AttributeEzXml(transformationElement, "offset", &(h->offset));
    }
    else if (!strcmp(transformationElement ->name, "ssc:BooleanMappingTransformation")) {
        h->type = sscMappingTransformBoolean;
    }
    else if (!strcmp(transformationElement ->name, "ssc:IntegerMappingTransformation")) {
        h->type = sscMappingTransformInteger;
    }
    else if (!strcmp(transformationElement ->name, "ssc:EnumerationMappingTransformation")) {
        h->type = sscMappingTransformEnumeration;
    }

    h->mapEntryCount = 0;
    for(ezxml_t entryElement = transformationElement->child; entryElement; entryElement = entryElement->ordered) {
        if (!strcmp(entryElement->name, "ssc:MapEntry")) {
            h->mapEntryCount++;
        }
    }

    h->mapEntries = NULL;
    if (h->mapEntryCount > 0) {
        h->mapEntries = mallocAndRememberPointer(ssp, sizeof(sscMapEntryHandle)*h->mapEntryCount);

        int i=0;
        for(ezxml_t entryElement = transformationElement->child; entryElement; entryElement = entryElement->ordered) {
            parseSscMapEntryElement(entryElement, &(h->mapEntries[i]), ssp);
            ++i;
        }
    }
    return true;
}

bool parseSscMapEntryElement(ezxml_t element, sscMapEntryHandle *h, sspHandle *ssp)
{
    h->xml = element;
    h->boolSource = false;
    h->boolTarget= false;
    h->intSource = 0;
    h->intTarget = 0;
    h->enumSource = NULL;
    h->enumTarget = NULL;
    if(!strcmp(element->parent->name, "ssc:BooleanMappingTransformation")) {
        parseBooleanAttributeEzXml(element, "source", &(h->boolSource));
        parseBooleanAttributeEzXml(element, "target", &(h->boolTarget));
    }
    else if(!strcmp(element->parent->name, "ssc:IntegerMappingTransformation")) {
        parseInt32AttributeEzXml(element, "source", &(h->intSource));
        parseInt32AttributeEzXml(element, "target", &(h->intTarget));
    }
    else if(!strcmp(element->parent->name, "ssc:EnumerationMappingTransformation")) {
        parseStringAttributeEzXmlAndRememberPointer(element, "source", &(h->enumSource), ssp);
        parseStringAttributeEzXmlAndRememberPointer(element, "target", &(h->enumTarget), ssp);
    }
    return true;
}

bool parseSsvParameterSetElement(ezxml_t element, ssvParameterSetHandle* h, sspHandle *ssp)
{
    h->xml = element;
    h->version = NULL;
    h->name = NULL;
    h->id = NULL;
    h->description = NULL;
    parseStringAttributeEzXmlAndRememberPointer(element, "version", &h->version, ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "name", &h->name, ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "id", &h->id, ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "description", &h->description, ssp);


    h->parameterCount = 0;
    ezxml_t parametersElement = ezxml_child(element, "ssv:Parameters");
    if(parametersElement) {
        for (ezxml_t parameterElement = parametersElement->child; parameterElement; parameterElement = parameterElement->ordered) {
            if (!strcmp(parameterElement->name, "ssv:Parameter")) {
                ++(h->parameterCount);
            }
        }

        if (h->parameterCount > 0) {
            h->parameters = mallocAndRememberPointer(ssp, sizeof(ssvParameterHandle) * (h->parameterCount));


            int i = 0;
            for (ezxml_t parameterElement = parametersElement->child; parameterElement; parameterElement = parameterElement->ordered) {
                if (!strcmp(parameterElement->name, "ssv:Parameter")) {
                    parseSsvParameterElement(parameterElement, &(h->parameters[i]), ssp);
                }
                ++i;
            }
        }
    }
    return true;
}

bool parseSsvParameterElement(ezxml_t element, ssvParameterHandle* h, sspHandle *ssp)
{
    h->xml = element;
    h->name = NULL;
    h->description = NULL;
    h->id = NULL;
    parseStringAttributeEzXmlAndRememberPointer(element, "name", &h->name, ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "description", &h->description, ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "id", &h->id, ssp);

    for(ezxml_t subElement = element->child; subElement; subElement = subElement->ordered) {
        if(!strcmp(subElement->name, "ssv:Real")) {
            h->datatype = sspDataTypeReal;
            h->realValue = 0;
            parseFloat64AttributeEzXml(subElement, "value", &(h->realValue));
            parseStringAttributeEzXmlAndRememberPointer(subElement, "unit", &h->unit, ssp);
        }
        else if(!strcmp(subElement->name, "ssv:Float64")) {
            h->datatype = sspDataTypeFloat64;
            h->float64Value = 0;
            parseFloat64AttributeEzXml(subElement, "value", &(h->float64Value));
            parseStringAttributeEzXmlAndRememberPointer(subElement, "unit", &h->unit, ssp);
        }
        else if(!strcmp(subElement->name, "ssv:Float32")) {
            h->datatype = sspDataTypeFloat32;
            h->float32Value = 0;
            parseFloat32AttributeEzXml(subElement, "value", &(h->float32Value));
            parseStringAttributeEzXmlAndRememberPointer(subElement, "unit", &h->unit, ssp);
        }
        else if(!strcmp(subElement->name, "ssv:Integer")) {
            h->datatype = sspDataTypeInteger;
            h->intValue = 0;
            parseInt32AttributeEzXml(subElement, "value", &(h->intValue));
        }
        else if(!strcmp(subElement->name, "ssv:Int8")) {
            h->datatype = sspDataTypeInt8;
            h->int8Value = 0;
            parseInt8AttributeEzXml(subElement, "value", &(h->int8Value));
        }
        else if(!strcmp(subElement->name, "ssv:UInt8")) {
            h->datatype = sspDataTypeUInt8;
            h->uint8Value = 0;
            parseUInt8AttributeEzXml(subElement, "value", &(h->uint8Value));
        }
        else if(!strcmp(subElement->name, "ssv:Int16")) {
            h->datatype = sspDataTypeInt16;
            h->int16Value = 0;
            parseInt16AttributeEzXml(subElement, "value", &(h->int16Value));
        }
        else if(!strcmp(subElement->name, "ssv:UInt16")) {
            h->datatype = sspDataTypeUInt16;
            h->uint16Value = 0;
            parseUInt16AttributeEzXml(subElement, "value", &(h->uint16Value));
        }
        else if(!strcmp(subElement->name, "ssv:Int32")) {
            h->datatype = sspDataTypeInt32;
            h->int32Value = 0;
            parseInt32AttributeEzXml(subElement, "value", &(h->int32Value));
        }
        else if(!strcmp(subElement->name, "ssv:UInt32")) {
            h->datatype = sspDataTypeUInt32;
            h->uint32Value = 0;
            parseUInt32AttributeEzXml(subElement, "value", &(h->uint32Value));
        }
        else if(!strcmp(subElement->name, "ssv:Int64")) {
            h->datatype = sspDataTypeInt64;
            h->int64Value = 0;
            parseInt64AttributeEzXml(subElement, "value", &(h->int64Value));
        }
        else if(!strcmp(subElement->name, "ssv:UInt64")) {
            h->datatype = sspDataTypeUInt64;
            h->uint64Value = 0;
            parseUInt64AttributeEzXml(subElement, "value", &(h->uint64Value));
        }
        else if(!strcmp(subElement->name, "ssv:Boolean")) {
            h->datatype = sspDataTypeBoolean;
            h->booleanValue = false;
            parseBooleanAttributeEzXml(subElement, "value", &(h->booleanValue));
        }
        else if(!strcmp(subElement->name, "ssv:String")) {
            h->datatype = sspDataTypeString;
            h->stringValue = NULL;
            parseStringAttributeEzXmlAndRememberPointer(subElement, "value", &(h->stringValue), ssp);
        }
        else if(!strcmp(subElement->name, "ssv:Enumeration")) {
            h->datatype = sspDataTypeEnumeration;
            h->enumValue = NULL;
            parseStringAttributeEzXmlAndRememberPointer(subElement, "value", &(h->enumValue), ssp);

            h->enumValuesCount = 0;
            ezxml_t valueElement = ezxml_child(subElement, "ssv:Value");
            while(valueElement) {
                ++(h->enumValuesCount);
                valueElement = valueElement->next;
            }

            if(h->enumValuesCount > 0) {
                h->enumValues = mallocAndRememberPointer(ssp, sizeof(const char*)*h->enumValuesCount);

                int i=0;
                valueElement = ezxml_child(subElement, "ssv:Value");
                while(valueElement) {
                    parseStringAttributeEzXmlAndRememberPointer(valueElement, "value", &(h->enumValues[i]), ssp);
                    valueElement = valueElement->next;
                    ++i;
                }
            }
        }
        else if(!strcmp(subElement->name, "ssc:Binary")) {
            h->datatype = sspDataTypeBinary;

            //! @todo Figure out how to parse binary values
        }
    }

    return true;
}
