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
        ssdHandle *ssd = ssp4c_getSsdByIndex(ssp,i);
        printf("---------------------------------------\n");
        printf("SSD file: %s\n", ssp4c_getSsdFileName(ssd));
        printf("  name: %s\n", ssp4c_getSsdName(ssd));
        printf("  version: %s\n", ssp4c_getSsdVersion(ssd));
        printf("  id: %s\n", ssp4c_getSsdId(ssd));
        printf("  description: %s\n", ssp4c_getSsdDescription(ssd));
        printf("  author: %s\n", ssp4c_getSsdAuthor(ssd));
        printf("  fileversion: %s\n", ssp4c_getSsdFileversion(ssd));
        printf("  copyright: %s\n", ssp4c_getSsdCopyright(ssd));
        printf("  license: %s\n", ssp4c_getSsdLicense(ssd));
        printf("  generationTool: %s\n", ssp4c_getSsdGenerationTool(ssd));
        printf("  generationDateAndTime: %s\n", ssp4c_getSsdGenerationDateAndTime(ssd));

        int ssdConnectorCount = ssp4c_getNumberOfSsdConnectors(ssd);
        printf("  number of connectors: %i\n", ssdConnectorCount);
        int ssdComponentCount = ssp4c_getNumberOfSsdComponents(ssd);
        printf("  number of components: %i\n", ssdComponentCount);

        for(int j=0; j<ssdConnectorCount; ++j) {
            ssdConnectorHandle *con = ssp4c_getSsdConnectorByIndex(ssd, j);
            printf("  connector:\n");
            printf("    name: %s\n", ssp4c_getSsdConnectorName(con));
            printf("    kind: %i\n", ssp4c_getSsdConnectorKind(con));
            printf("    description: %s\n", ssp4c_getSsdConnectorDescription(con));
            printf("    datatype: %i\n", ssp4c_getSsdConnectorDatatype(con));
            printf("    unit: %s\n", ssp4c_getSsdConnectorUnit(con));
        }

        for(int j=0; j<ssdComponentCount; ++j) {
            ssdComponentHandle *comp = ssp4c_ssd_getComponentByIndex(ssd, j);
            printf("  component:\n");
            printf("    name: %s\n", ssp4c_ssd_component_getName(comp));
            printf("    source: %s\n", ssp4c_ssd_component_getSource(comp));
            printf("    type: %s\n", ssp4c_ssd_component_getType(comp));
            printf("    implementation: %i\n", ssp4c_ssd_component_getImplementation(comp));
            int ssdConnectorCount = ssp4c_getNumberOfSsdComponentConnectors(comp);
            printf("    number of connectors: %i\n", ssdConnectorCount);
            int ssdParameterBindingsCount = ssp4c_getNumberOfSsdComponentParameterBindings(comp);
            printf("    number of parameter bindings: %i\n", ssdParameterBindingsCount);

            for(int j=0; j<ssdConnectorCount; ++j) {
                ssdConnectorHandle *con = ssp4c_ssd_component_getConnectorByIndex(comp, j);
                printf("    connector:\n");
                printf("      name: %s\n", ssp4c_getSsdConnectorName(con));
                printf("      kind: %i\n", ssp4c_getSsdConnectorKind(con));
                printf("      description: %s\n", ssp4c_getSsdConnectorDescription(con));
                printf("      datatype: %i\n", ssp4c_getSsdConnectorDatatype(con));
                printf("      unit: %s\n", ssp4c_getSsdConnectorUnit(con));
            }

            printf("    geometry:\n");
            printf("      x1: %f\n", ssp4c_ssd_component_getGeometryX1(comp));
            printf("      y1: %f\n", ssp4c_ssd_component_getGeometryY1(comp));
            printf("      x2: %f\n", ssp4c_ssd_component_getGeometryX2(comp));
            printf("      y2: %f\n", ssp4c_ssd_component_getGeometryY2(comp));
            printf("      rotation: %f\n", ssp4c_ssd_component_getGeometryRotation(comp));
            printf("      iconSource: %s\n", ssp4c_ssd_component_getGeometryIconSource(comp));
            printf("      iconRotation: %f\n", ssp4c_ssd_component_getGeometryIconRotation(comp));
            printf("      iconFlip: %i\n", ssp4c_ssd_component_getGeometryIconFlip(comp));
            printf("      iconFixedAspectRatio: %i\n", ssp4c_ssd_component_getGeometryIconFixedAspectRatio(comp));

            for(int j=0; j<ssdParameterBindingsCount; ++j) {
                ssdParameterBindingHandle *binding = ssp4c_ssd_component_getParameterBindingByIndex(comp, j);
                printf("    parameter binding:\n");
                printf("      type: %s\n", ssp4c_ssd_parameterBinding_getType(binding));
                printf("      prefix: %s\n", ssp4c_ssd_parameterBinding_getPrefix(binding));
                printf("      source: %s\n", ssp4c_ssd_parameterBinding_getSource(binding));
                printf("      sourceBase: %d\n", ssp4c_ssd_parameterBinding_getSourceBase(binding));

                ssdParameterValuesHandle *values = ssp4c_ssd_parameterBinding_getParameterValues(binding);

                ssvParameterSetHandle *set = ssp4c_ssd_parameterValues_getParameterSet(values);
                if(set) {
                    printf("      parameter set:\n");
                    printf("        version: %s\n", ssp4c_ssd_parameterSet_getVersion(set));
                    printf("        name: %s\n", ssp4c_ssd_parameterSet_getName(set));
                    printf("        id %s\n", ssp4c_ssd_parameterSet_getId(set));
                    printf("        description: %s\n", ssp4c_ssd_parameterSet_getDescription(set));
                    int parameterSetParameterCount = ssp4c_ssd_parameterSet_getNumberOfParameters(set);
                    printf("        number of parameters: %i\n", parameterSetParameterCount);
                    for(int k=0; k<parameterSetParameterCount; ++k) {
                        ssvParameterHandle *par = ssp4c_ssd_parameterSet_getParameterByIndex(set, k);
                        printf("        parameter:\n");
                        printf("          name: %s\n", ssp4c_ssv_parameter_getName(par));
                        printf("          description: %s\n", ssp4c_ssv_parameter_getDescription(par));
                        printf("          id: %s\n", ssp4c_ssv_parameter_getId(par));
                        if(ssp4c_ssv_parameter_getDatatype(par) == sspDataTypeReal) {
                            printf("          data type: ssv:Real\n");
                            printf("          value: %f\n", ssp4c_ssv_parameter_getRealValue(par));
                            printf("          unit: %s\n", ssp4c_ssv_parameter_getUnit(par));
                        }
                        else if(ssp4c_ssv_parameter_getDatatype(par) == sspDataTypeFloat64) {
                            printf("          data type: ssv:Float64\n");
                            printf("          value: %f\n", ssp4c_ssv_parameter_getFloat64Value(par));
                            printf("          unit: %s\n", ssp4c_ssv_parameter_getUnit(par));
                        }
                        else if(ssp4c_ssv_parameter_getDatatype(par) == sspDataTypeFloat32) {
                            printf("          data type: ssv:Float32\n");
                            printf("          value: %f\n", ssp4c_ssv_parameter_getFloat32Value(par));
                            printf("          unit: %s\n", ssp4c_ssv_parameter_getUnit(par));
                        }
                        else if(ssp4c_ssv_parameter_getDatatype(par) == sspDataTypeInteger) {
                            printf("          data type: ssv:Integer\n");
                            printf("          value: %d\n", ssp4c_ssv_parameter_getIntValue(par));
                        }
                        else if(ssp4c_ssv_parameter_getDatatype(par) == sspDataTypeInt64) {
                            printf("          data type: ssv:Int64\n");
                            printf("          value: %d\n", ssp4c_ssv_parameter_getInt64Value(par));
                        }
                        else if(ssp4c_ssv_parameter_getDatatype(par) == sspDataTypeInt32) {
                            printf("          data type: ssv:Int32\n");
                            printf("          value: %d\n", ssp4c_ssv_parameter_getInt32Value(par));
                        }
                        else if(ssp4c_ssv_parameter_getDatatype(par) == sspDataTypeInt16) {
                            printf("          data type: ssv:Int16\n");
                            printf("          value: %d\n", ssp4c_ssv_parameter_getInt16Value(par));
                        }
                        else if(ssp4c_ssv_parameter_getDatatype(par) == sspDataTypeInt8) {
                            printf("          data type: ssv:Int8\n");
                            printf("          value: %d\n", ssp4c_ssv_parameter_getInt8Value(par));
                        }
                        else if(ssp4c_ssv_parameter_getDatatype(par) == sspDataTypeUInt64) {
                            printf("          data type: ssv:UInt64\n");
                            printf("          value: %d\n", ssp4c_ssv_parameter_getUInt64Value(par));
                        }
                        else if(ssp4c_ssv_parameter_getDatatype(par) == sspDataTypeUInt32) {
                            printf("          data type: ssv:UInt32\n");
                            printf("          value: %d\n", ssp4c_ssv_parameter_getUInt32Value(par));
                        }
                        else if(ssp4c_ssv_parameter_getDatatype(par) == sspDataTypeUInt16) {
                            printf("          data type: ssv:UInt16\n");
                            printf("          value: %d\n", ssp4c_ssv_parameter_getUInt16Value(par));
                        }
                        else if(ssp4c_ssv_parameter_getDatatype(par) == sspDataTypeUInt8) {
                            printf("          data type: ssv:UInt8\n");
                            printf("          value: %d\n", ssp4c_ssv_parameter_getUInt8Value(par));
                        }
                        else if(ssp4c_ssv_parameter_getDatatype(par) == sspDataTypeBoolean) {
                            printf("          data type: ssv:Boolean\n");
                            printf("          value: %i\n", ssp4c_ssv_parameter_getBooleanValue(par));
                        }
                        else if(ssp4c_ssv_parameter_getDatatype(par) == sspDataTypeString) {
                            printf("          data type: ssv:String\n");
                            printf("          value: %s\n", ssp4c_ssv_parameter_getStringValue(par));
                        }
                        else if(ssp4c_ssv_parameter_getDatatype(par) == sspDataTypeEnumeration) {
                            printf("          data type: ssv:Enumeration\n");
                            printf("          value: %s\n", ssp4c_ssv_parameter_getEnumValue(par));
                            for(int l=0; l<ssp4c_ssv_parameter_getNumberOfEnumerationValues(par); ++l) {
                                printf("          alternative value: %s\n", ssp4c_ssv_parameter_getEnumerationValueByIndex(par, l));
                            }
                        }
                    }
                }

                ssdParameterMappingHandle *mapping = ssp4c_ssd_parameterSet_getParameterMapping(binding);
                if(mapping) {
                    printf("      parameter mapping:\n");
                    printf("        desciption: %s\n", ssp4c_ssd_parameterMapping_getDescription(mapping));
                    printf("        id: %s\n", ssp4c_ssd_parameterMapping_getId(mapping));
                    printf("        type: %s\n", ssp4c_ssd_parameterMapping_getType(mapping));
                    printf("        source: %s\n", ssp4c_ssd_parameterMapping_getSource(mapping));
                    printf("        sourceBase: %d\n", ssp4c_ssd_parameterMapping_getSourceBase(mapping));

                    ssmParameterMappingHandle *ssmMapping = ssp4c_ssd_parameterMapping_getSsmParameterMapping(mapping);
                    if(ssmMapping) {
                        printf("        ssm parameter mapping:\n");
                        printf("          version: %s\n", ssp4c_ssm_parameterMapping_getVersion(ssmMapping));
                        printf("          id: %s\n", ssp4c_ssm_parameterMapping_getId(ssmMapping));
                        printf("          description: %s\n", ssp4c_ssm_parameterMapping_getDescription(ssmMapping));
                        printf("          author: %s\n", ssp4c_ssm_parameterMapping_getAuthor(ssmMapping));
                        printf("          fileversion: %s\n", ssp4c_ssm_parameterMapping_getFileversion(ssmMapping));
                        printf("          copyright: %s\n", ssp4c_ssm_parameterMapping_getCopyright(ssmMapping));
                        printf("          license: %s\n", ssp4c_ssm_parameterMapping_getLicense(ssmMapping));
                        printf("          generationTool: %s\n", ssp4c_ssm_parameterMapping_getGenerationTool(ssmMapping));
                        printf("          generationDateAndTime: %s\n", ssp4c_ssm_parameterMapping_getGenerationDateAndTime(ssmMapping));
                        printf("          number of entries: %d\n", ssp4c_ssm_parameterMapping_getNumberOfMappingEntries(ssmMapping));

                        for(int k=0; k<ssp4c_ssm_parameterMapping_getNumberOfMappingEntries(ssmMapping); ++k) {
                            ssmParameterMappingEntryHandle *entry = ssp4c_ssm_parameterMapping_getMappingEntryByIndex(ssmMapping, k);
                            printf("          parameter mapping entry:\n");
                            printf("            id: %s\n", ssp4c_ssm_mappingEntry_getId(entry));
                            printf("            description: %s\n", ssp4c_ssm_mappingEntry_getDescription(entry));
                            printf("            source: %s\n", ssp4c_ssm_mappingEntry_getSource(entry));
                            printf("            target: %s\n", ssp4c_ssm_mappingEntry_getTarget(entry));
                            printf("            suppressUnitConversion: %d\n", ssp4c_ssm_mappingEntry_getSuppressUnitConveresion(entry));
                            sscMappingTransformHandle *transform = _ssm_mappingEntry_getSsmMappingTransform(entry);
                            if(transform) {
                                printf("            transform:\n");
                                printf("              type: %d\n", ssp4c_ssc_mapEntry_getType(transform));
                                printf("              factor: %f\n", ssp4c_ssc_mapEntry_getFactor(transform));
                                printf("              offset: %f\n", ssp4c_ssc_mapEntry_getOffset(transform));
                                printf("              number of map entries: %d\n", ssp4c_getNumberOfMapEntries(transform));

                                for(int l=0; l<ssp4c_getNumberOfMapEntries(transform); ++l) {
                                    sscMapEntryHandle *entry = ssp4c_getMapEntryByIndex(transform, l);
                                    printf("              map entry:\n");
                                    printf("                boolSource: %d\n", ssp4c_ssc_mapEntry_getBoolSource(entry));
                                    printf("                boolTarget: %d\n", ssp4c_ssc_mapEntry_getBoolTarget(entry));
                                    printf("                intSource: %d\n", ssp4c_ssc_mapEntry_getIntSource(entry));
                                    printf("                intTarget: %d\n", ssp4c_ssc_mapEntry_getIntTarget(entry));
                                    printf("                enumSource: %s\n", ssp4c_ssc_mapEntry_getEnumSource(entry));
                                    printf("                enumTarget: %s\n", ssp4c_ssc_mapEntry_getEnumTarget(entry));
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    ssp4c_freeSsp(ssp);

    return 0;
}


