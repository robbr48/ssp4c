#include <stdio.h>
#include <stdlib.h>
#ifndef _WIN32
#include <unistd.h>
#endif

#include "ssp4c.h"

void printUsage() {
    printf("Usage: ssp4ctest <options> <fmu_file(s)>\n");
    printf("Options:                 Meaning:\n");
    printf("-i, --input              Path to input CSV file\n");
    printf("-o, --output             Path to output CSV file\n");
    printf("-m, --mode               Simulation mode: \n"
           "                         auto: use co-simulation if possible, else model excghange (defualt)\n"
           "                         me: force model excghange mode\n"
           "                         cs: force co-simulation mode\n");
    printf("-h, --stepsize=TIMESTEP  Specify communication step size\n");
    printf("-s, --stoptime=STOPTIME  Specify simulation stop time\n");
    printf("-l, --loglevel=LOGLEVEL  Specify log level: \n"
           "                         0: no logging\n"
           "                         1: fatal"
           "                         2: fatal & errors\n"
           "                         3: fatal, errors & warnings\n"
           "                         4: fatal, errors, warning & info\n"
           "                         5: fatal, errors, warnings, info & debug.\n");
    printf("-t, --tlm                Run a TLM test (requires two FMUs)\n");
}

void print_ssc_mapEntry(sscMapEntryHandle *entry, int indentation)
{
    printf("%*cmap entry:\n", indentation, ' ');
    printf("%*c  boolSource: %d\n", indentation, ' ', ssp4c_ssc_mapEntry_getBoolSource(entry));
    printf("%*c  boolTarget: %d\n", indentation, ' ', ssp4c_ssc_mapEntry_getBoolTarget(entry));
    printf("%*c  intSource: %d\n", indentation, ' ', ssp4c_ssc_mapEntry_getIntSource(entry));
    printf("%*c  intTarget: %d\n", indentation, ' ', ssp4c_ssc_mapEntry_getIntTarget(entry));
    printf("%*c  enumSource: %s\n", indentation, ' ', ssp4c_ssc_mapEntry_getEnumSource(entry));
    printf("%*c  enumTarget: %s\n", indentation, ' ', ssp4c_ssc_mapEntry_getEnumTarget(entry));
}

void print_ssc_mappingTransform(sscMappingTransformHandle *h, int indentation)
{
    if(h) {
        printf("%*ctransform:\n", indentation, ' ');
        printf("%*c  type: %d\n", indentation, ' ', ssp4c_ssc_mapEntry_getType(h));
        printf("%*c  factor: %f\n", indentation, ' ', ssp4c_ssc_mapEntry_getFactor(h));
        printf("%*c  offset: %f\n", indentation, ' ', ssp4c_ssc_mapEntry_getOffset(h));
        printf("%*c  number of map entries: %d\n", indentation, ' ', ssp4c_getNumberOfMapEntries(h));

        for(int l=0; l<ssp4c_getNumberOfMapEntries(h); ++l) {
            print_ssc_mapEntry(ssp4c_getMapEntryByIndex(h, l), indentation+2);
        }
    }
}

void print_ssm_parameterMappingEntry(ssmParameterMappingEntryHandle *entry, int indentation)
{
    printf("%*cparameter mapping entry:\n", indentation, ' ');
    printf("%*c  id: %s\n", indentation, ' ', ssp4c_ssm_mappingEntry_getId(entry));
    printf("%*c  description: %s\n", indentation, ' ', ssp4c_ssm_mappingEntry_getDescription(entry));
    printf("%*c  source: %s\n", indentation, ' ', ssp4c_ssm_mappingEntry_getSource(entry));
    printf("%*c  target: %s\n", indentation, ' ', ssp4c_ssm_mappingEntry_getTarget(entry));
    printf("%*c  suppressUnitConversion: %d\n", indentation, ' ', ssp4c_ssm_mappingEntry_getSuppressUnitConveresion(entry));

    print_ssc_mappingTransform(ssp4c_ssm_mappingEntry_getSsmMappingTransform(entry),indentation+2);
}

void print_ssm_parameterMapping(ssmParameterMappingHandle *ssmMapping, int indentation)
{
    if(ssmMapping) {
        printf("%*cssm parameter mapping:\n", indentation, ' ');
        printf("%*c  version: %s\n", indentation, ' ', ssp4c_ssm_parameterMapping_getVersion(ssmMapping));
        printf("%*c  id: %s\n", indentation, ' ', ssp4c_ssm_parameterMapping_getId(ssmMapping));
        printf("%*c  description: %s\n", indentation, ' ', ssp4c_ssm_parameterMapping_getDescription(ssmMapping));
        printf("%*c  author: %s\n", indentation, ' ', ssp4c_ssm_parameterMapping_getAuthor(ssmMapping));
        printf("%*c  fileversion: %s\n", indentation, ' ', ssp4c_ssm_parameterMapping_getFileversion(ssmMapping));
        printf("%*c  copyright: %s\n", indentation, ' ', ssp4c_ssm_parameterMapping_getCopyright(ssmMapping));
        printf("%*c  license: %s\n", indentation, ' ', ssp4c_ssm_parameterMapping_getLicense(ssmMapping));
        printf("%*c  generationTool: %s\n", indentation, ' ', ssp4c_ssm_parameterMapping_getGenerationTool(ssmMapping));
        printf("%*c  generationDateAndTime: %s\n", indentation, ' ', ssp4c_ssm_parameterMapping_getGenerationDateAndTime(ssmMapping));
        printf("%*c  number of entries: %d\n", indentation, ' ', ssp4c_ssm_parameterMapping_getNumberOfMappingEntries(ssmMapping));

        for(int k=0; k<ssp4c_ssm_parameterMapping_getNumberOfMappingEntries(ssmMapping); ++k) {
            print_ssm_parameterMappingEntry(ssp4c_ssm_parameterMapping_getMappingEntryByIndex(ssmMapping, k), indentation+2);
        }
    }
}

void print_ssd_parameterMapping(ssdParameterMappingHandle *mapping, int indentation)
{
    if(mapping) {
        printf("%*cparameter mapping:\n", indentation, ' ');
        printf("%*c  desciption: %s\n", indentation, ' ', ssp4c_ssd_parameterMapping_getDescription(mapping));
        printf("%*c  id: %s\n", indentation, ' ', ssp4c_ssd_parameterMapping_getId(mapping));
        printf("%*c  type: %s\n", indentation, ' ', ssp4c_ssd_parameterMapping_getType(mapping));
        printf("%*c  source: %s\n", indentation, ' ', ssp4c_ssd_parameterMapping_getSource(mapping));
        printf("%*c  sourceBase: %d\n", indentation, ' ', ssp4c_ssd_parameterMapping_getSourceBase(mapping));

        print_ssm_parameterMapping(ssp4c_ssd_parameterMapping_getSsmParameterMapping(mapping), indentation+2);
    }
}

void print_ssd_connector(ssdConnectorHandle *h, int indentation) {
    printf("%*cconnector:\n", indentation, ' ');
    printf("%*c  name: %s\n", indentation, ' ', ssp4c_getSsdConnectorName(h));
    printf("%*c  kind: %i\n", indentation, ' ', ssp4c_getSsdConnectorKind(h));
    printf("%*c  description: %s\n", indentation, ' ', ssp4c_getSsdConnectorDescription(h));
    printf("%*c  datatype: %i\n", indentation, ' ', ssp4c_getSsdConnectorDatatype(h));
    printf("%*c  unit: %s\n", indentation, ' ', ssp4c_getSsdConnectorUnit(h));
}

void print_ssv_parameter(ssvParameterHandle *h, int indentation)
{
    printf("%*cparameter:\n", indentation, ' ');
    printf("%*c  name: %s\n", indentation, ' ', ssp4c_ssv_parameter_getName(h));
    printf("%*c  description: %s\n", indentation, ' ', ssp4c_ssv_parameter_getDescription(h));
    printf("%*c  id: %s\n", indentation, ' ', ssp4c_ssv_parameter_getId(h));
    if(ssp4c_ssv_parameter_getDatatype(h) == sspDataTypeReal) {
        printf("%*c  data type: ssv:Real\n", indentation, ' ');
        printf("%*c  value: %f\n", indentation, ' ', ssp4c_ssv_parameter_getRealValue(h));
        printf("%*c  unit: %s\n", indentation, ' ', ssp4c_ssv_parameter_getUnit(h));
    }
    else if(ssp4c_ssv_parameter_getDatatype(h) == sspDataTypeFloat64) {
        printf("%*c  data type: ssv:Float64\n", indentation, ' ');
        printf("%*c  value: %f\n", indentation, ' ', ssp4c_ssv_parameter_getFloat64Value(h));
        printf("%*c  unit: %s\n", indentation, ' ', ssp4c_ssv_parameter_getUnit(h));
    }
    else if(ssp4c_ssv_parameter_getDatatype(h) == sspDataTypeFloat32) {
        printf("%*c  data type: ssv:Float32\n", indentation, ' ');
        printf("%*c  value: %f\n", indentation, ' ', ssp4c_ssv_parameter_getFloat32Value(h));
        printf("%*c  unit: %s\n", indentation, ' ', ssp4c_ssv_parameter_getUnit(h));
    }
    else if(ssp4c_ssv_parameter_getDatatype(h) == sspDataTypeInteger) {
        printf("%*c  data type: ssv:Integer\n", indentation, ' ');
        printf("%*c  value: %d\n", indentation, ' ', ssp4c_ssv_parameter_getIntValue(h));
    }
    else if(ssp4c_ssv_parameter_getDatatype(h) == sspDataTypeInt64) {
        printf("%*c  data type: ssv:Int64\n", indentation, ' ');
        printf("%*c  value: %d\n", indentation, ' ', ssp4c_ssv_parameter_getInt64Value(h));
    }
    else if(ssp4c_ssv_parameter_getDatatype(h) == sspDataTypeInt32) {
        printf("%*c  data type: ssv:Int32\n", indentation, ' ');
        printf("%*c  value: %d\n", indentation, ' ', ssp4c_ssv_parameter_getInt32Value(h));
    }
    else if(ssp4c_ssv_parameter_getDatatype(h) == sspDataTypeInt16) {
        printf("%*c  data type: ssv:Int16\n", indentation, ' ');
        printf("%*c  value: %d\n", indentation, ' ', ssp4c_ssv_parameter_getInt16Value(h));
    }
    else if(ssp4c_ssv_parameter_getDatatype(h) == sspDataTypeInt8) {
        printf("%*c  data type: ssv:Int8\n", indentation, ' ');
        printf("%*c  value: %d\n", indentation, ' ', ssp4c_ssv_parameter_getInt8Value(h));
    }
    else if(ssp4c_ssv_parameter_getDatatype(h) == sspDataTypeUInt64) {
        printf("%*c  data type: ssv:UInt64\n", indentation, ' ');
        printf("%*c  value: %d\n", indentation, ' ', ssp4c_ssv_parameter_getUInt64Value(h));
    }
    else if(ssp4c_ssv_parameter_getDatatype(h) == sspDataTypeUInt32) {
        printf("%*c  data type: ssv:UInt32\n", indentation, ' ');
        printf("%*c  value: %d\n", indentation, ' ', ssp4c_ssv_parameter_getUInt32Value(h));
    }
    else if(ssp4c_ssv_parameter_getDatatype(h) == sspDataTypeUInt16) {
        printf("%*c  data type: ssv:UInt16\n", indentation, ' ');
        printf("%*c  value: %d\n", indentation, ' ', ssp4c_ssv_parameter_getUInt16Value(h));
    }
    else if(ssp4c_ssv_parameter_getDatatype(h) == sspDataTypeUInt8) {
        printf("%*c  data type: ssv:UInt8\n", indentation, ' ');
        printf("%*c  value: %d\n", indentation, ' ', ssp4c_ssv_parameter_getUInt8Value(h));
    }
    else if(ssp4c_ssv_parameter_getDatatype(h) == sspDataTypeBoolean) {
        printf("%*c  data type: ssv:Boolean\n", indentation, ' ');
        printf("%*c  value: %i\n", indentation, ' ', ssp4c_ssv_parameter_getBooleanValue(h));
    }
    else if(ssp4c_ssv_parameter_getDatatype(h) == sspDataTypeString) {
        printf("%*c  data type: ssv:String\n", indentation, ' ');
        printf("%*c  value: %s\n", indentation, ' ', ssp4c_ssv_parameter_getStringValue(h));
    }
    else if(ssp4c_ssv_parameter_getDatatype(h) == sspDataTypeEnumeration) {
        printf("%*c  data type: ssv:Enumeration\n", indentation, ' ');
        printf("%*c  value: %s\n", indentation, ' ', ssp4c_ssv_parameter_getEnumValue(h));
        for(int l=0; l<ssp4c_ssv_parameter_getNumberOfEnumerationValues(h); ++l) {
            printf("%*c  alternative value: %s\n", indentation, ' ', ssp4c_ssv_parameter_getEnumerationValueByIndex(h, l));
        }
    }
}

void print_ssv_parameterSet(ssvParameterSetHandle *h, int indentation)
{
    if(h) {
        printf("%*cparameter set:\n", indentation, ' ');
        printf("%*c  version: %s\n", indentation, ' ', ssp4c_ssd_parameterSet_getVersion(h));
        printf("%*c  name: %s\n", indentation, ' ', ssp4c_ssd_parameterSet_getName(h));
        printf("%*c  id %s\n", indentation, ' ', ssp4c_ssd_parameterSet_getId(h));
        printf("%*c  description: %s\n", indentation, ' ', ssp4c_ssd_parameterSet_getDescription(h));
        int parameterSetParameterCount = ssp4c_ssd_parameterSet_getNumberOfParameters(h);
        printf("        number of parameters: %i\n", parameterSetParameterCount);
        for(int k=0; k<parameterSetParameterCount; ++k) {
            print_ssv_parameter(ssp4c_ssd_parameterSet_getParameterByIndex(h, k), indentation+2);
        }
    }
}

void print_ssd_parameterBinding(ssdParameterBindingHandle *h, int indentation)
{
    printf("%*cparameter binding:\n", indentation, ' ');
    printf("%*c  type: %s\n", indentation, ' ', ssp4c_ssd_parameterBinding_getType(h));
    printf("%*c  prefix: %s\n", indentation, ' ', ssp4c_ssd_parameterBinding_getPrefix(h));
    printf("%*c  source: %s\n", indentation, ' ', ssp4c_ssd_parameterBinding_getSource(h));
    printf("%*c  sourceBase: %d\n", indentation, ' ', ssp4c_ssd_parameterBinding_getSourceBase(h));

    ssdParameterValuesHandle *values = ssp4c_ssd_parameterBinding_getParameterValues(h);

    print_ssv_parameterSet(ssp4c_ssd_parameterValues_getParameterSet(values), indentation+2);

    print_ssd_parameterMapping(ssp4c_ssd_parameterSet_getParameterMapping(h), indentation+2);
}

void print_ssd_elementGeometry(ssdElementGeometryHandle *h, int indentation)
{
    printf("%*cgeometry:\n", indentation, ' ');
    printf("%*c  x1: %f\n", indentation, ' ', ssp4c_ssd_elementGeometry_getX1(h));
    printf("%*c  y1: %f\n", indentation, ' ', ssp4c_ssd_elementGeometry_getY1(h));
    printf("%*c  x2: %f\n", indentation, ' ', ssp4c_ssd_elementGeometry_getX2(h));
    printf("%*c  y2: %f\n", indentation, ' ', ssp4c_ssd_elementGeometry_getY2(h));
    printf("%*c  rotation: %f\n", indentation, ' ', ssp4c_ssd_elementGeometry_getRotation(h));
    printf("%*c  iconSource: %s\n", indentation, ' ', ssp4c_ssd_elementGeometry_getIconSource(h));
    printf("%*c  iconRotation: %f\n", indentation, ' ', ssp4c_ssd_elementGeometry_getIconRotation(h));
    printf("%*c  iconFlip: %i\n", indentation, ' ', ssp4c_ssd_elementGeometry_getIconFlip(h));
    printf("%*c  iconFixedAspectRatio: %i\n", indentation, ' ', ssp4c_ssd_elementGeometry_getIconFixedAspectRatio(h));
}

void print_ssd_component(ssdComponentHandle *h, int indentation)
{
    printf("%*ccomponent:\n", indentation, ' ');
    printf("%*c  name: %s\n", indentation, ' ', ssp4c_ssd_component_getName(h));
    printf("%*c  source: %s\n", indentation, ' ', ssp4c_ssd_component_getSource(h));
    printf("%*c  type: %s\n", indentation, ' ', ssp4c_ssd_component_getType(h));
    printf("%*c  implementation: %i\n", indentation, ' ', ssp4c_ssd_component_getImplementation(h));
    int ssdConnectorCount = ssp4c_getNumberOfSsdComponentConnectors(h);
    printf("%*c  number of connectors: %i\n", indentation, ' ', ssdConnectorCount);
    int ssdParameterBindingsCount = ssp4c_getNumberOfSsdComponentParameterBindings(h);
    printf("%*c  number of parameter bindings: %i\n", indentation, ' ', ssdParameterBindingsCount);

    for(int j=0; j<ssdConnectorCount; ++j) {
        print_ssd_connector(ssp4c_ssd_component_getConnectorByIndex(h, j), indentation+2);
    }

    print_ssd_elementGeometry(ssp4c_ssd_component_getElementGeometry(h), indentation+2);

    for(int j=0; j<ssdParameterBindingsCount; ++j) {
        print_ssd_parameterBinding(ssp4c_ssd_component_getParameterBindingByIndex(h, j), indentation+2);
    }
}

void print_ssd(ssdHandle *h, int indentation)
{
    printf("%*cSSD file: %s\n", indentation, ' ', ssp4c_getSsdFileName(h));
    printf("%*c  name: %s\n", indentation, ' ', ssp4c_getSsdName(h));
    printf("%*c  version: %s\n", indentation, ' ', ssp4c_getSsdVersion(h));
    printf("%*c  id: %s\n", indentation, ' ', ssp4c_getSsdId(h));
    printf("%*c  description: %s\n", indentation, ' ', ssp4c_getSsdDescription(h));
    printf("%*c  author: %s\n", indentation, ' ', ssp4c_getSsdAuthor(h));
    printf("%*c  fileversion: %s\n", indentation, ' ', ssp4c_getSsdFileversion(h));
    printf("%*c  copyright: %s\n", indentation, ' ', ssp4c_getSsdCopyright(h));
    printf("%*c  license: %s\n", indentation, ' ', ssp4c_getSsdLicense(h));
    printf("%*c  generationTool: %s\n", indentation, ' ', ssp4c_getSsdGenerationTool(h));
    printf("%*c  generationDateAndTime: %s\n", indentation, ' ', ssp4c_getSsdGenerationDateAndTime(h));

    int ssdConnectorCount = ssp4c_getNumberOfSsdConnectors(h);
    printf("%*c  number of connectors: %i\n", indentation, ' ', ssdConnectorCount);
    int ssdComponentCount = ssp4c_getNumberOfSsdComponents(h);
    printf("%*c  number of components: %i\n", indentation, ' ', ssdComponentCount);

    for(int j=0; j<ssdConnectorCount; ++j) {
        print_ssd_connector(ssp4c_getSsdConnectorByIndex(h, j), indentation+2);
    }

    for(int j=0; j<ssdComponentCount; ++j) {
        print_ssd_component(ssp4c_ssd_getComponentByIndex(h, j), indentation+2);
    }
}

int main(int argc, char *argv[])
{
    if(argc == 1) {
        printUsage();
        exit(0);
    }

    const char* sspfile = argv[1];

    printf("Loading SSP: %s\n", sspfile);

    sspHandle *ssp = ssp4c_loadSsp(sspfile);

    int ssdCount = ssp4c_getNumberOfSsds(ssp);
    printf("Number of SSDs: %i\n", ssdCount);

    for(int i=0; i<ssdCount; ++i) {
        print_ssd(ssp4c_getSsdByIndex(ssp,i), 0);
    }

    ssp4c_freeSsp(ssp);

    return 0;
}


