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

    //Parse root element attributes
    ssd->name = "";
    ssd->version = "";
    ssd->id = "";
    ssd->description = "";
    ssd->author = "";
    ssd->fileversion = "";
    ssd->copyright = "";
    ssd->license = "";
    ssd->generationTool = "";
    ssd->generationDateAndTime = "";
    ssd->componentCount = 0;

    parseStringAttributeEzXmlAndRememberPointer(ssd->xml , "name", &ssd->name, ssp);
    parseStringAttributeEzXmlAndRememberPointer(ssd->xml , "version", &ssd->version, ssp);
    parseStringAttributeEzXmlAndRememberPointer(ssd->xml , "id", &ssd->id, ssp);
    parseStringAttributeEzXmlAndRememberPointer(ssd->xml , "description", &ssd->description, ssp);
    parseStringAttributeEzXmlAndRememberPointer(ssd->xml , "author", &ssd->author, ssp);
    parseStringAttributeEzXmlAndRememberPointer(ssd->xml , "fileversion", &ssd->fileversion, ssp);
    parseStringAttributeEzXmlAndRememberPointer(ssd->xml , "copyright", &ssd->copyright, ssp);
    parseStringAttributeEzXmlAndRememberPointer(ssd->xml , "license", &ssd->license, ssp);
    parseStringAttributeEzXmlAndRememberPointer(ssd->xml , "generationTool", &ssd->generationTool, ssp);
    parseStringAttributeEzXmlAndRememberPointer(ssd->xml , "generationDateAndTime", &ssd->generationDateAndTime, ssp);

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
    int i=0;

    parseStringAttributeEzXmlAndRememberPointer(element,  "name",      &h->name, ssp);

    h->kind = ssdConnectorKindUnspecifed;
    const char* kind = NULL;
    if(parseStringAttributeEzXml(element, "kind", &kind)) {
        if(!strcmp(kind, "input")) {
            h->kind = ssdConnectorKindInput;
        }
        else if(!strcmp(kind, "output")) {
            h->kind = ssdConnectorKindOutput;
        }
        else if(!strcmp(kind, "parameter")) {
            h->kind = ssdConnectorKindParameter;
        }
        else if(!strcmp(kind, "calculatedParameter")) {
            h->kind = ssdConnectorKindCalculatedParameter;
        }
        else if(!strcmp(kind, "calculatedParameter")) {
            h->kind = ssdConnectorKindStructuralParameter;
        }
        else if(!strcmp(kind, "calculatedConstant")) {
            h->kind = ssdConnectorKindConstant;
        }
        else if(!strcmp(kind, "local")) {
            h->kind = ssdConnectorKindLocal;
        }
        else if(!strcmp(kind, "inout")) {
            h->kind = ssdConnectorKindInout;
        }
        else if(!strcmp(kind, "unspecified")) {
            h->kind = ssdConnectorKindUnspecifed;
        }
        else {
            printf("Unknown causality: %s\n", kind);
            freeDuplicatedConstChar(kind);
            return false;
        }
        freeDuplicatedConstChar(kind);
    }

    parseStringAttributeEzXmlAndRememberPointer(element,  "description",      &h->description, ssp);

    for(ezxml_t subElement = element->child; subElement; subElement = subElement->ordered) {
        if(!strcmp(subElement->name, "ssc:Real")) {
            h->datatype = sspDataTypeReal;
        }
        else if(!strcmp(subElement->name, "ssc:Float64")) {
            h->datatype = sspDataTypeFloat64;
        }
        else if(!strcmp(subElement->name, "ssc:Float32")) {
            h->datatype = sspDataTypeFloat32;
        }
        else if(!strcmp(subElement->name, "ssc:Integer")) {
            h->datatype = sspDataTypeInteger;
        }
        else if(!strcmp(subElement->name, "ssc:Int8")) {
            h->datatype = sspDataTypeInt8;
        }
        else if(!strcmp(subElement->name, "ssc:UInt8")) {
            h->datatype = sspDataTypeUInt8;
        }
        else if(!strcmp(subElement->name, "ssc:Int16")) {
            h->datatype = sspDataTypeInt16;
        }
        else if(!strcmp(subElement->name, "ssc:UInt16")) {
            h->datatype = sspDataTypeUInt16;
        }
        else if(!strcmp(subElement->name, "ssc:Int32")) {
            h->datatype = sspDataTypeInt32;
        }
        else if(!strcmp(subElement->name, "ssc:UInt32")) {
            h->datatype = sspDataTypeUInt32;
        }
        else if(!strcmp(subElement->name, "ssc:Int64")) {
            h->datatype = sspDataTypeInt64;
        }
        else if(!strcmp(subElement->name, "ssc:UInt64")) {
            h->datatype = sspDataTypeUInt64;
        }
        else if(!strcmp(subElement->name, "ssc:Boolean")) {
            h->datatype = sspDataTypeBoolean;
        }
        else if(!strcmp(subElement->name, "ssc:String")) {
            h->datatype = sspDataTypeString;
        }
        else if(!strcmp(subElement->name, "ssc:Enumeration")) {
            h->datatype = sspDataTypeEnumeration;
        }
        else if(!strcmp(subElement->name, "ssc:Binary")) {
            h->datatype = sspDataTypeBinary;
        }
        else {
            printf("Illegal data type for connector!\n");
            return false;
        }

        //Read unit
        if(h->datatype == sspDataTypeReal ||
            h->datatype == sspDataTypeFloat64 ||
            h->datatype == sspDataTypeFloat32) {
            parseStringAttributeEzXmlAndRememberPointer(subElement, "unit", &h->unit, ssp);
        }
    }

    return true;
}

bool parseSsdComponentsElement(ezxml_t element, ssdComponentsHandle* h, sspHandle *ssp)
{
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
    parseStringAttributeEzXmlAndRememberPointer(element, "name", &h->name, ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "type", &h->type, ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "source", &h->source, ssp);

    h->implementation = ssdComponentImplementationAny;
    const char* implementation = NULL;
    if(parseStringAttributeEzXml(element, "implementation", &implementation)) {
        if(!strcmp(implementation, "any")) {
            h->implementation = ssdComponentImplementationAny;
        }
        else if(!strcmp(implementation, "ModelExchange")) {
            h->implementation = ssdComponentImplementationModelExchange;
        }
        else if(!strcmp(implementation, "CoSimulation")) {
            h->implementation = ssdComponentImplementationCoSimulation;
        }
        else if(!strcmp(implementation, "ScheduledExecution")) {
            h->implementation = ssdComponentImplementationScheduledExecution;
        }
        freeDuplicatedConstChar(implementation);
    }

    //Parse connectors
    h->connectors = mallocAndRememberPointer(ssp, sizeof(ssdConnectorsHandle));
    ezxml_t componentConnectorsElement = ezxml_child(element, "ssd:Connectors");
    if(componentConnectorsElement) {
        parseSsdConnectorsElement(componentConnectorsElement, h->connectors, ssp);
    }

    //Parse parameter bindings
    // Parse geometry
    h->geometry.x1 = 0;
    h->geometry.y1 = 0;
    h->geometry.x2 = 0;
    h->geometry.y2= 0;
    h->geometry.rotation = 0;
    h->geometry.iconRotation = 0;
    h->geometry.iconSource = NULL;
    h->geometry.iconFlip = false;
    h->geometry.iconFixedAspectRatio = false;
    ezxml_t geometryElement = ezxml_child(element, "ssd:ElementGeometry");
    h->geometry.xml = geometryElement;
    if(geometryElement) {
        parseFloat64AttributeEzXml(geometryElement, "x1", &h->geometry.x1);
        parseFloat64AttributeEzXml(geometryElement, "y1", &h->geometry.y1);
        parseFloat64AttributeEzXml(geometryElement, "x2", &h->geometry.x2);
        parseFloat64AttributeEzXml(geometryElement, "y2", &h->geometry.y2);
        parseFloat64AttributeEzXml(geometryElement, "rotation", &h->geometry.rotation);
        parseFloat64AttributeEzXml(geometryElement, "iconRotation", &h->geometry.iconRotation);
        parseStringAttributeEzXmlAndRememberPointer(geometryElement, "iconSource", &h->geometry.iconSource, ssp);
        parseBooleanAttributeEzXml(geometryElement, "iconFlip", &h->geometry.iconFlip);
        parseBooleanAttributeEzXml(geometryElement, "iconFixedAspectRatio", &h->geometry.iconFixedAspectRatio);
    }
    h->geometry.ssp = ssp;

    ezxml_t parameterBindingsElement = ezxml_child(element, "ssd:ParameterBindings");
    if(parameterBindingsElement) {
        h->parameterBindings = mallocAndRememberPointer(ssp, sizeof(ssdParameterBindingsHandle));
        parseSsdParameterBindingsElement(parameterBindingsElement, h->parameterBindings, ssp);
    }

    return true;
}

bool parseSsdParameterBindingsElement(ezxml_t element, ssdParameterBindingsHandle* h, sspHandle *ssp)
{
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

bool parseSsdParameterValuesElement(ezxml_t element, ssdParameterValuesHandle* handle, sspHandle *ssp)
{
    handle->parameterSet = NULL;
    ezxml_t parameterSetElement = ezxml_child(element, "ssv:ParameterSet");
    if(parameterSetElement) {
        handle->parameterSet = mallocAndRememberPointer(ssp, sizeof(ssvParameterSetHandle));
        parseSsvParameterSetElement(parameterSetElement, handle->parameterSet, ssp);
    }

    return true;
}

bool parseSsdParameterMappingElement(ezxml_t element,ssdParameterMappingHandle* handle, sspHandle *ssp)
{
    handle->id = NULL;
    handle->description = NULL;
    handle->type = NULL;
    handle->source = NULL;
    handle->sourceBase = ssdParameterSourceBaseSSD;
    parseStringAttributeEzXmlAndRememberPointer(element, "id", &(handle->id), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "description", &(handle->description), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "type", &(handle->type), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "source", &(handle->source), ssp);

    handle->sourceBase = ssdParameterSourceBaseSSD;
    const char* sourceBase = NULL;
    if(parseStringAttributeEzXml(element, "sourceBase", &sourceBase)) {
        if(!strcmp(sourceBase, "SSD")) {
            handle->sourceBase = ssdParameterSourceBaseSSD;
        }
        else if(!strcmp(sourceBase, "component")) {
            handle->sourceBase = ssdParameterSourceBaseComponent;
        }
        freeDuplicatedConstChar(sourceBase);
    }

    //Parse parameter entries
    handle->parameterMapping = NULL;
    ezxml_t ssmParameterMappingElement = ezxml_child(element, "ssm:ParameterMapping");
    if(ssmParameterMappingElement) {
        handle->parameterMapping = mallocAndRememberPointer(ssp, sizeof(ssmParameterMappingHandle));
        parseSsmParameterMappingElement(ssmParameterMappingElement, handle->parameterMapping, ssp);
    }

    return true;
}

bool parseSsmParameterMappingElement(ezxml_t element, ssmParameterMappingHandle *handle, sspHandle *ssp)
{
    handle->id = NULL;
    handle->description = NULL;
    handle->author= NULL;
    handle->fileversion = NULL;
    handle->copyright = NULL;
    handle->license = NULL;
    handle->generationTool = NULL;
    handle->generationDateAndTime = NULL;
    handle->version = NULL;
    parseStringAttributeEzXmlAndRememberPointer(element, "id", &(handle->id), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "description", &(handle->description), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "author", &(handle->author), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "fileversion", &(handle->fileversion), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "copyright", &(handle->copyright), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "license", &(handle->license), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "generationTool", &(handle->generationTool), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "generationDateAndTime", &(handle->generationDateAndTime), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "version", &(handle->version), ssp);

    handle->mappingEntryCount = 0;
    for(ezxml_t entryElement = element->child; entryElement; entryElement = entryElement->ordered) {
        if (!strcmp(entryElement->name, "ssm:MappingEntry")) {
            handle->mappingEntryCount++;
        }
    }

    if (handle->mappingEntryCount > 0) {
        int i=0;
        handle->mappingEntries = mallocAndRememberPointer(ssp, sizeof(ssmParameterMappingEntryHandle)*handle->mappingEntryCount);
        for(ezxml_t entryElement = element->child; entryElement; entryElement = entryElement->ordered) {
            parseSsmMappingEntryElement(entryElement, &(handle->mappingEntries[i]), ssp);
            ++i;
        }
    }

    return true;
}

bool parseSsmMappingEntryElement(ezxml_t element, ssmParameterMappingEntryHandle *handle, sspHandle *ssp)
{
    handle->id = NULL;
    handle->description = NULL;
    handle->source = NULL;
    handle->target = NULL;
    handle->suppressUnitConveresion = false;
    parseStringAttributeEzXmlAndRememberPointer(element, "id", &(handle->id), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "description", &(handle->description), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "source", &(handle->source), ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "target", &(handle->target), ssp);
    parseBooleanAttributeEzXml(element, "suppressUnitConersion", &(handle->suppressUnitConveresion));

    handle->transform = NULL;
    ezxml_t transformationChoiceElement = ezxml_child(element, "ssc:TransformationChoice");
    if(transformationChoiceElement) {
        handle->transform = mallocAndRememberPointer(ssp, sizeof(sscMappingTransformHandle));
        parseSscTransformationChoiceElement(transformationChoiceElement, handle->transform, ssp);
    }
    return true;
}

bool parseSscTransformationChoiceElement(ezxml_t element, sscMappingTransformHandle *handle, sspHandle *ssp)
{
    ezxml_t transformationElement = element->child;
    handle->factor = 1;
    handle->offset = 0;

    if (!strcmp(transformationElement->name, "ssc:LinearTransformation")) {

        handle->type = sscMappingTransformLinear;
        parseFloat64AttributeEzXml(transformationElement, "factor", &(handle->factor));
        parseFloat64AttributeEzXml(transformationElement, "offset", &(handle->offset));
    }
    else if (!strcmp(transformationElement ->name, "ssc:BooleanMappingTransformation")) {
        handle->type = sscMappingTransformBoolean;
    }
    else if (!strcmp(transformationElement ->name, "ssc:IntegerMappingTransformation")) {
        handle->type = sscMappingTransformInteger;
    }
    else if (!strcmp(transformationElement ->name, "ssc:EnumerationMappingTransformation")) {
        handle->type = sscMappingTransformEnumeration;
    }

    handle->mapEntryCount = 0;
    for(ezxml_t entryElement = transformationElement->child; entryElement; entryElement = entryElement->ordered) {
        if (!strcmp(entryElement->name, "ssc:MapEntry")) {
            handle->mapEntryCount++;
        }
    }

    handle->mapEntries = NULL;
    if (handle->mapEntryCount > 0) {
        handle->mapEntries = mallocAndRememberPointer(ssp, sizeof(sscMapEntryHandle)*handle->mapEntryCount);

        int i=0;
        for(ezxml_t entryElement = transformationElement->child; entryElement; entryElement = entryElement->ordered) {
            parseSscMapEntryElement(entryElement, &(handle->mapEntries[i]), ssp);
            ++i;
        }
    }
    return true;
}

bool parseSscMapEntryElement(ezxml_t element, sscMapEntryHandle *handle, sspHandle *ssp)
{
    handle->boolSource = false;
    handle->boolTarget= false;
    handle->intSource = 0;
    handle->intTarget = 0;
    handle->enumSource = NULL;
    handle->enumTarget = NULL;
    if(!strcmp(element->parent->name, "ssc:BooleanMappingTransformation")) {
        parseBooleanAttributeEzXml(element, "source", &(handle->boolSource));
        parseBooleanAttributeEzXml(element, "target", &(handle->boolTarget));
    }
    else if(!strcmp(element->parent->name, "ssc:IntegerMappingTransformation")) {
        parseInt32AttributeEzXml(element, "source", &(handle->intSource));
        parseInt32AttributeEzXml(element, "target", &(handle->intTarget));
    }
    else if(!strcmp(element->parent->name, "ssc:EnumerationMappingTransformation")) {
        parseStringAttributeEzXmlAndRememberPointer(element, "source", &(handle->enumSource), ssp);
        parseStringAttributeEzXmlAndRememberPointer(element, "target", &(handle->enumTarget), ssp);
    }
    return true;
}

bool parseSsvParameterSetElement(ezxml_t element, ssvParameterSetHandle* parameterSetHandle, sspHandle *ssp)
{
    parameterSetHandle->version = NULL;
    parameterSetHandle->name = NULL;
    parameterSetHandle->id = NULL;
    parameterSetHandle->description = NULL;
    parseStringAttributeEzXmlAndRememberPointer(element, "version", &parameterSetHandle->version, ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "name", &parameterSetHandle->name, ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "id", &parameterSetHandle->id, ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "description", &parameterSetHandle->description, ssp);


    parameterSetHandle->parameterCount = 0;
    ezxml_t parametersElement = ezxml_child(element, "ssv:Parameters");
    if(parametersElement) {
        for (ezxml_t parameterElement = parametersElement->child; parameterElement; parameterElement = parameterElement->ordered) {
            if (!strcmp(parameterElement->name, "ssv:Parameter")) {
                ++(parameterSetHandle->parameterCount);
            }
        }

        if (parameterSetHandle->parameterCount > 0) {
            parameterSetHandle->parameters = mallocAndRememberPointer(ssp, sizeof(ssvParameterHandle) * (parameterSetHandle->parameterCount));


            int i = 0;
            for (ezxml_t parameterElement = parametersElement->child; parameterElement; parameterElement = parameterElement->ordered) {
                if (!strcmp(parameterElement->name, "ssv:Parameter")) {
                    parseSsvParameterElement(parameterElement, &(parameterSetHandle->parameters[i]), ssp);
                }
                ++i;
            }
        }
    }
    return true;
}

bool parseSsvParameterElement(ezxml_t element, ssvParameterHandle* parameterHandle, sspHandle *ssp)
{
    parameterHandle->name = NULL;
    parameterHandle->description = NULL;
    parameterHandle->id = NULL;
    parseStringAttributeEzXmlAndRememberPointer(element, "name", &parameterHandle->name, ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "description", &parameterHandle->description, ssp);
    parseStringAttributeEzXmlAndRememberPointer(element, "id", &parameterHandle->id, ssp);

    for(ezxml_t subElement = element->child; subElement; subElement = subElement->ordered) {
        if(!strcmp(subElement->name, "ssv:Real")) {
            parameterHandle->datatype = sspDataTypeReal;
            parameterHandle->realValue = 0;
            parseFloat64AttributeEzXml(subElement, "value", &(parameterHandle->realValue));
            parseStringAttributeEzXmlAndRememberPointer(subElement, "unit", &parameterHandle->unit, ssp);
        }
        else if(!strcmp(subElement->name, "ssv:Float64")) {
            parameterHandle->datatype = sspDataTypeFloat64;
            parameterHandle->float64Value = 0;
            parseFloat64AttributeEzXml(subElement, "value", &(parameterHandle->float64Value));
            parseStringAttributeEzXmlAndRememberPointer(subElement, "unit", &parameterHandle->unit, ssp);
        }
        else if(!strcmp(subElement->name, "ssv:Float32")) {
            parameterHandle->datatype = sspDataTypeFloat32;
            parameterHandle->float32Value = 0;
            parseFloat32AttributeEzXml(subElement, "value", &(parameterHandle->float32Value));
            parseStringAttributeEzXmlAndRememberPointer(subElement, "unit", &parameterHandle->unit, ssp);
        }
        else if(!strcmp(subElement->name, "ssv:Integer")) {
            parameterHandle->datatype = sspDataTypeInteger;
            parameterHandle->intValue = 0;
            parseInt32AttributeEzXml(subElement, "value", &(parameterHandle->intValue));
        }
        else if(!strcmp(subElement->name, "ssv:Int8")) {
            parameterHandle->datatype = sspDataTypeInt8;
            parameterHandle->int8Value = 0;
            parseInt8AttributeEzXml(subElement, "value", &(parameterHandle->int8Value));
        }
        else if(!strcmp(subElement->name, "ssv:UInt8")) {
            parameterHandle->datatype = sspDataTypeUInt8;
            parameterHandle->uint8Value = 0;
            parseUInt8AttributeEzXml(subElement, "value", &(parameterHandle->uint8Value));
        }
        else if(!strcmp(subElement->name, "ssv:Int16")) {
            parameterHandle->datatype = sspDataTypeInt16;
            parameterHandle->int16Value = 0;
            parseInt16AttributeEzXml(subElement, "value", &(parameterHandle->int16Value));
        }
        else if(!strcmp(subElement->name, "ssv:UInt16")) {
            parameterHandle->datatype = sspDataTypeUInt16;
            parameterHandle->uint16Value = 0;
            parseUInt16AttributeEzXml(subElement, "value", &(parameterHandle->uint16Value));
        }
        else if(!strcmp(subElement->name, "ssv:Int32")) {
            parameterHandle->datatype = sspDataTypeInt32;
            parameterHandle->int32Value = 0;
            parseInt32AttributeEzXml(subElement, "value", &(parameterHandle->int32Value));
        }
        else if(!strcmp(subElement->name, "ssv:UInt32")) {
            parameterHandle->datatype = sspDataTypeUInt32;
            parameterHandle->uint32Value = 0;
            parseUInt32AttributeEzXml(subElement, "value", &(parameterHandle->uint32Value));
        }
        else if(!strcmp(subElement->name, "ssv:Int64")) {
            parameterHandle->datatype = sspDataTypeInt64;
            parameterHandle->int64Value = 0;
            parseInt64AttributeEzXml(subElement, "value", &(parameterHandle->int64Value));
        }
        else if(!strcmp(subElement->name, "ssv:UInt64")) {
            parameterHandle->datatype = sspDataTypeUInt64;
            parameterHandle->uint64Value = 0;
            parseUInt64AttributeEzXml(subElement, "value", &(parameterHandle->uint64Value));
        }
        else if(!strcmp(subElement->name, "ssv:Boolean")) {
            parameterHandle->datatype = sspDataTypeBoolean;
            parameterHandle->booleanValue = false;
            parseBooleanAttributeEzXml(subElement, "value", &(parameterHandle->booleanValue));
        }
        else if(!strcmp(subElement->name, "ssv:String")) {
            parameterHandle->datatype = sspDataTypeString;
            parameterHandle->stringValue = NULL;
            parseStringAttributeEzXmlAndRememberPointer(subElement, "value", &(parameterHandle->stringValue), ssp);
        }
        else if(!strcmp(subElement->name, "ssv:Enumeration")) {
            parameterHandle->datatype = sspDataTypeEnumeration;
            parameterHandle->enumValue = NULL;
            parseStringAttributeEzXmlAndRememberPointer(subElement, "value", &(parameterHandle->enumValue), ssp);

            parameterHandle->enumValuesCount = 0;
            ezxml_t valueElement = ezxml_child(subElement, "ssv:Value");
            while(valueElement) {
                ++(parameterHandle->enumValuesCount);
                valueElement = valueElement->next;
            }

            if(parameterHandle->enumValuesCount > 0) {
                parameterHandle->enumValues = mallocAndRememberPointer(ssp, sizeof(const char*)*parameterHandle->enumValuesCount);

                int i=0;
                valueElement = ezxml_child(subElement, "ssv:Value");
                while(valueElement) {
                    parseStringAttributeEzXmlAndRememberPointer(valueElement, "value", &(parameterHandle->enumValues[i]), ssp);
                    valueElement = valueElement->next;
                    ++i;
                }
            }
        }
        else if(!strcmp(subElement->name, "ssc:Binary")) {
            parameterHandle->datatype = sspDataTypeBinary;

            //! @todo Figure out how to parse binary values
        }
    }

    return true;
}
