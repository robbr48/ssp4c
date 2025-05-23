#include "ssp4c_private.h"
#include "ssp4c_ssd.h"
#include "ssp4c_xml_constants.h"
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
    if(strcmp(ssd->xml ->name, XML_ELEMENT_SSD)) {
        printf("Wrong root tag name: %s\n", ssd->xml ->name);
        return false;
    }

    ezxml_t systemElement = ezxml_child(ssd->xml , XML_ELEMENT_SSD_SYSTEM);
    if(systemElement) {

        //Parse connectors
        ezxml_t connectorsElement = ezxml_child(systemElement, XML_ELEMENT_SSD_CONNECTORS);
        if(connectorsElement) {
            ssd->connectors = mallocAndRememberPointer(ssp, sizeof(ssdConnectorsHandle));
            parseSsdConnectorsElement(connectorsElement, ssd->connectors, ssp);
        }

        // Parse components
        ssd->components = NULL;
        ezxml_t componentsElement = ezxml_child(systemElement, XML_ELEMENT_SSD_ELEMENTS);
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
    h->ssp = ssp;

    h->connectorsCount = 0;
    for(ezxml_t connectorElement = element->child; connectorElement; connectorElement = connectorElement->ordered) {
        if(!strcmp(connectorElement->name, XML_ELEMENT_SSD_CONNECTOR)) {
            ++(h->connectorsCount);  //Just count them for now, so we can allocate memory before loading them
        }
    }
    if((h->connectorsCount) > 0) {
        h->connectors = mallocAndRememberPointer(ssp, (h->connectorsCount)*sizeof(ssdConnectorHandle));
        int i=0;
        for(ezxml_t connectorElement = element->child; connectorElement; connectorElement = connectorElement->ordered) {
            if(!strcmp(connectorElement->name, XML_ELEMENT_SSD_CONNECTOR)) {
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
    h->ssp = ssp;

    return true;
}

bool parseSsdComponentsElement(ezxml_t element, ssdComponentsHandle* h, sspHandle *ssp)
{
    h->xml = element;
    h->ssp = ssp;

    h->componentsCount = 0;
    for (ezxml_t componentElement = element->child; componentElement; componentElement = componentElement->ordered) {
        if (!strcmp(componentElement->name, XML_ELEMENT_SSD_COMPONENT)) {
            ++h->componentsCount;
        }
    }

    if (h->componentsCount > 0) {
        h->components = mallocAndRememberPointer(ssp, sizeof(ssdComponentHandle) * h->componentsCount);

        int i = 0;
        for (ezxml_t componentElement = element->child; componentElement; componentElement = componentElement->ordered) {
            if (!strcmp(componentElement->name, XML_ELEMENT_SSD_COMPONENT)) {
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
    h->ssp = ssp;

    //Parse connectors
    h->connectors = mallocAndRememberPointer(ssp, sizeof(ssdConnectorsHandle));
    ezxml_t componentConnectorsElement = ezxml_child(element, XML_ELEMENT_SSD_CONNECTORS);
    if(componentConnectorsElement) {
        parseSsdConnectorsElement(componentConnectorsElement, h->connectors, ssp);
    }

    //Parse parameter bindings
    // Parse geometry

    ezxml_t geometryElement = ezxml_child(element, XML_ELEMENT_SSD_ELEMENT_GEOMETRY);
    if(geometryElement) {
        h->geometry = mallocAndRememberPointer(ssp, sizeof(ssdElementGeometryHandle));
        parseSsdElementGeometryElement(geometryElement, h->geometry, ssp);
    }

    ezxml_t parameterBindingsElement = ezxml_child(element, XML_ELEMENT_SSD_PARAMETER_BINDINGS);
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
    h->ssp = ssp;
    h->parameterBindingsCount = 0;

    for (ezxml_t parameterBindingElement = element->child; parameterBindingElement ; parameterBindingElement  = parameterBindingElement ->ordered) {
        if (!strcmp(parameterBindingElement ->name, XML_ELEMENT_SSD_PARAMETER_BINDING)) {
            ++h->parameterBindingsCount;
        }
    }

    if (h->parameterBindingsCount > 0) {
        h->parameterBindings = mallocAndRememberPointer(ssp, sizeof(ssdParameterBindingHandle) * h->parameterBindingsCount);


        int i = 0;
        for (ezxml_t parameterBindingsElement = element->child; parameterBindingsElement; parameterBindingsElement = parameterBindingsElement->ordered) {
            if (!strcmp(parameterBindingsElement->name, XML_ELEMENT_SSD_PARAMETER_BINDING)) {
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
    h->ssp = ssp;

    //Parse parameter sets
    h->parameterValues = NULL;
    ezxml_t parameterValuesElement = ezxml_child(element, XML_ELEMENT_SSD_PARAMETER_VALUES);
    if(parameterValuesElement) {
        h->parameterValues = mallocAndRememberPointer(ssp, sizeof(ssdParameterValuesHandle));
        parseSsdParameterValuesElement(parameterValuesElement, h->parameterValues, ssp);
    }

    //Parse parameter mappings
    h->parameterMapping = NULL;
    ezxml_t parameterMappingElement = ezxml_child(element, XML_ELEMENT_SSD_PARAMETER_MAPPING);
    if(parameterMappingElement) {
        h->parameterMapping = mallocAndRememberPointer(ssp, sizeof(ssdParameterMappingHandle));
        parseSsdParameterMappingElement(parameterMappingElement, h->parameterMapping, ssp);
    }

    return true;
}

bool parseSsdParameterValuesElement(ezxml_t element, ssdParameterValuesHandle* h, sspHandle *ssp)
{
    h->xml = element;
    h->ssp = ssp;
    h->parameterSet = NULL;
    ezxml_t parameterSetElement = ezxml_child(element, XML_ELEMENT_SSV_PARAMETER_SET);
    if(parameterSetElement) {
        h->parameterSet = mallocAndRememberPointer(ssp, sizeof(ssvParameterSetHandle));
        parseSsvParameterSetElement(parameterSetElement, h->parameterSet, ssp);
    }

    return true;
}

bool parseSsdParameterMappingElement(ezxml_t element,ssdParameterMappingHandle* h, sspHandle *ssp)
{
    h->xml = element;
    h->ssp = ssp;

    //Parse parameter entries
    h->parameterMapping = NULL;
    ezxml_t ssmParameterMappingElement = ezxml_child(element, XML_ELEMENT_SSM_PARAMETER_MAPPING);
    if(ssmParameterMappingElement) {
        h->parameterMapping = mallocAndRememberPointer(ssp, sizeof(ssmParameterMappingHandle));
        parseSsmParameterMappingElement(ssmParameterMappingElement, h->parameterMapping, ssp);
    }

    return true;
}

bool parseSsmParameterMappingElement(ezxml_t element, ssmParameterMappingHandle *h, sspHandle *ssp)
{
    h->xml = element;
    h->ssp = ssp;
    h->mappingEntryCount = 0;
    for(ezxml_t entryElement = element->child; entryElement; entryElement = entryElement->ordered) {
        if (!strcmp(entryElement->name, XML_ELEMENT_SSM_MAPPING_ENTRY)) {
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
    h->ssp = ssp;
    h->transform = NULL;
    ezxml_t transformationChoiceElement = ezxml_child(element, XML_ELEMENT_SSC_TRANSFORMATION_CHOICE);
    if(transformationChoiceElement) {
        h->transform = mallocAndRememberPointer(ssp, sizeof(sscMappingTransformHandle));
        parseSscTransformationChoiceElement(transformationChoiceElement, h->transform, ssp);
    }
    return true;
}

bool parseSscTransformationChoiceElement(ezxml_t element, sscMappingTransformHandle *h, sspHandle *ssp)
{
    h->xml = element;
    h->ssp = ssp;
    ezxml_t transformationElement = element->child;
    h->factor = 1;
    h->offset = 0;

    if (!strcmp(transformationElement->name, XML_ELEMENT_SSC_LINEAR_TRANSFORMATION)) {

        h->type = sscMappingTransformLinear;
        parseFloat64AttributeEzXml(transformationElement, XML_ATTR_FACTOR, &(h->factor));
        parseFloat64AttributeEzXml(transformationElement, XML_ATTR_OFFSET, &(h->offset));
    }
    else if (!strcmp(transformationElement ->name, XML_ELEMENT_SSC_BOOLEAN_MAPPING_TRANSFORMATION)) {
        h->type = sscMappingTransformBoolean;
    }
    else if (!strcmp(transformationElement ->name, XML_ELEMENT_SSC_INTEGER_MAPPING_TRANSFORMATION)) {
        h->type = sscMappingTransformInteger;
    }
    else if (!strcmp(transformationElement ->name, XML_ELEMENT_SSC_ENUMERATION_MAPPING_TRANSFORMATION)) {
        h->type = sscMappingTransformEnumeration;
    }

    h->mapEntryCount = 0;
    for(ezxml_t entryElement = transformationElement->child; entryElement; entryElement = entryElement->ordered) {
        if (!strcmp(entryElement->name, XML_ELEMENT_SSC_MAP_ENTRY)) {
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
    h->ssp = ssp;
    h->boolSource = false;
    h->boolTarget= false;
    h->intSource = 0;
    h->intTarget = 0;
    h->enumSource = NULL;
    h->enumTarget = NULL;
    if(!strcmp(element->parent->name, XML_ELEMENT_SSC_BOOLEAN_MAPPING_TRANSFORMATION)) {
        h->boolSource = !strcmp(ezxml_attr(h->xml, XML_ATTR_SOURCE), XML_VALUE_TRUE);
        h->boolTarget = !strcmp(ezxml_attr(h->xml, XML_ATTR_TARGET), XML_VALUE_TRUE);
    }
    else if(!strcmp(element->parent->name, XML_ELEMENT_SSC_INTEGER_MAPPING_TRANSFORMATION)) {
        parseInt32AttributeEzXml(element, XML_ATTR_SOURCE, &(h->intSource));
        parseInt32AttributeEzXml(element, XML_ATTR_TARGET, &(h->intTarget));
    }
    else if(!strcmp(element->parent->name, XML_ELEMENT_SSC_ENUMERATION_MAPPING_TRANSFORMATION)) {
        parseStringAttributeEzXmlAndRememberPointer(element, XML_ATTR_SOURCE, &(h->enumSource), ssp);
        parseStringAttributeEzXmlAndRememberPointer(element, XML_ATTR_TARGET, &(h->enumTarget), ssp);
    }
    return true;
}

bool parseSsvParameterSetElement(ezxml_t element, ssvParameterSetHandle* h, sspHandle *ssp)
{
    h->xml = element;
    h->ssp = ssp;

    h->parameterCount = 0;
    ezxml_t parametersElement = ezxml_child(element, XML_ELEMENT_SSV_PARAMETERS);
    if(parametersElement) {
        for (ezxml_t parameterElement = parametersElement->child; parameterElement; parameterElement = parameterElement->ordered) {
            if (!strcmp(parameterElement->name, XML_ELEMENT_SSV_PARAMETER)) {
                ++(h->parameterCount);
            }
        }

        if (h->parameterCount > 0) {
            h->parameters = mallocAndRememberPointer(ssp, sizeof(ssvParameterHandle) * (h->parameterCount));


            int i = 0;
            for (ezxml_t parameterElement = parametersElement->child; parameterElement; parameterElement = parameterElement->ordered) {
                if (!strcmp(parameterElement->name, XML_ELEMENT_SSV_PARAMETER)) {
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
    h->ssp = ssp;

    return true;
}
