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
            ssdComponentHandle *comp = ssp4c_getSsdComponentByIndex(ssd, j);
            printf("  component:\n");
            printf("    name: %s\n", ssp4c_getSsdComponentName(comp));
            printf("    source: %s\n", ssp4c_getSsdComponentSource(comp));
            printf("    type: %s\n", ssp4c_getSsdComponentType(comp));
            printf("    implementation: %i\n", ssp4c_getSsdComponentImplementation(comp));
            int ssdConnectorCount = ssp4c_getNumberOfSsdComponentConnectors(comp);
            printf("    number of connectors: %i\n", ssdConnectorCount);
            int ssdParameterBindingsCount = ssp4c_getNumberOfSsdComponentParameterBindings(comp);
            printf("    number of parameter bindings: %i\n", ssdParameterBindingsCount);

            for(int j=0; j<ssdConnectorCount; ++j) {
                ssdConnectorHandle *con = ssp4c_getSsdComponentConnectorByIndex(comp, j);
                printf("    connector:\n");
                printf("      name: %s\n", ssp4c_getSsdConnectorName(con));
                printf("      kind: %i\n", ssp4c_getSsdConnectorKind(con));
                printf("      description: %s\n", ssp4c_getSsdConnectorDescription(con));
                printf("      datatype: %i\n", ssp4c_getSsdConnectorDatatype(con));
                printf("      unit: %s\n", ssp4c_getSsdConnectorUnit(con));
            }

            printf("    geometry:\n");
            printf("      x1: %f\n", ssp4c_getSsdComponentGeometryX1(comp));
            printf("      y1: %f\n", ssp4c_getSsdComponentGeometryY1(comp));
            printf("      x2: %f\n", ssp4c_getSsdComponentGeometryX2(comp));
            printf("      y2: %f\n", ssp4c_getSsdComponentGeometryY2(comp));
            printf("      rotation: %f\n", ssp4c_getSsdComponentGeometryRotation(comp));
            printf("      iconSource: %s\n", ssp4c_getSsdComponentGeometryIconSource(comp));
            printf("      iconRotation: %f\n", ssp4c_getSsdComponentGeometryIconRotation(comp));
            printf("      iconFlip: %i\n", ssp4c_getSsdComponentGeometryIconFlip(comp));
            printf("      iconFixedAspectRatio: %i\n", ssp4c_getSsdComponentGeometryIconFixedAspectRatio(comp));

            for(int j=0; j<ssdParameterBindingsCount; ++j) {
                ssdParameterBindingHandle *binding = ssp4c_getSsdComponentParameterBindingByIndex(comp, j);
                printf("    parameter binding:\n");
                printf("      type: %s\n", ssp4c_getSsdComponentParameterBindingType(binding));
                printf("      prefix: %s\n", ssp4c_getSsdComponentParameterBindingPrefix(binding));
                printf("      source: %s\n", ssp4c_getSsdComponentParameterBindingSource(binding));
                printf("      sourceBase: %d\n", ssp4c_getSsdComponentParameterBindingSourceBase(binding));

                ssdParameterSetHandle *set = ssp4c_getParameterSet(binding);
                if(set) {
                    printf("      parameter set:\n");
                    printf("        version: %s\n", ssp4c_getParameterSetVersion(set));
                    printf("        name: %s\n", ssp4c_getParameterSetName(set));
                    printf("        id %s\n", ssp4c_getParameterSetId(set));
                    printf("        description: %s\n", ssp4c_getParameterSetDescription(set));
                    int parameterSetParameterCount = ssp4c_getNumberOfParameterSetParameters(set);
                    printf("        number of parameters: %i\n", parameterSetParameterCount);
                    for(int k=0; k<parameterSetParameterCount; ++k) {
                        ssvParameterHandle *par = ssp4c_getParameterSetParameterByIndex(set, k);
                        printf("        parameter:\n");
                        printf("          name: %s\n", ssp4c_getParameterName(par));
                        printf("          description: %s\n", ssp4c_getParameterDescription(par));
                        printf("          id: %s\n", ssp4c_getParameterId(par));
                        if(ssp4c_getParameterDatatype(par) == sspDataTypeReal) {
                            printf("          data type: ssv:Real\n");
                            printf("          value: %f\n", ssp4c_getParameterRealValue(par));
                            printf("          unit: %s\n", ssp4c_getParameterUnit(par));
                        }
                        else if(ssp4c_getParameterDatatype(par) == sspDataTypeFloat64) {
                            printf("          data type: ssv:Float64\n");
                            printf("          value: %f\n", ssp4c_getParameterFloat64Value(par));
                            printf("          unit: %s\n", ssp4c_getParameterUnit(par));
                        }
                        else if(ssp4c_getParameterDatatype(par) == sspDataTypeFloat32) {
                            printf("          data type: ssv:Float32\n");
                            printf("          value: %f\n", ssp4c_getParameterFloat32Value(par));
                            printf("          unit: %s\n", ssp4c_getParameterUnit(par));
                        }
                        else if(ssp4c_getParameterDatatype(par) == sspDataTypeInteger) {
                            printf("          data type: ssv:Integer\n");
                            printf("          value: %d\n", ssp4c_getParameterIntValue(par));
                        }
                        else if(ssp4c_getParameterDatatype(par) == sspDataTypeInt64) {
                            printf("          data type: ssv:Int64\n");
                            printf("          value: %d\n", ssp4c_getParameterInt64Value(par));
                        }
                        else if(ssp4c_getParameterDatatype(par) == sspDataTypeInt32) {
                            printf("          data type: ssv:Int32\n");
                            printf("          value: %d\n", ssp4c_getParameterInt32Value(par));
                        }
                        else if(ssp4c_getParameterDatatype(par) == sspDataTypeInt16) {
                            printf("          data type: ssv:Int16\n");
                            printf("          value: %d\n", ssp4c_getParameterInt16Value(par));
                        }
                        else if(ssp4c_getParameterDatatype(par) == sspDataTypeInt8) {
                            printf("          data type: ssv:Int8\n");
                            printf("          value: %d\n", ssp4c_getParameterInt8Value(par));
                        }
                        else if(ssp4c_getParameterDatatype(par) == sspDataTypeUInt64) {
                            printf("          data type: ssv:UInt64\n");
                            printf("          value: %d\n", ssp4c_getParameterUInt64Value(par));
                        }
                        else if(ssp4c_getParameterDatatype(par) == sspDataTypeUInt32) {
                            printf("          data type: ssv:UInt32\n");
                            printf("          value: %d\n", ssp4c_getParameterUInt32Value(par));
                        }
                        else if(ssp4c_getParameterDatatype(par) == sspDataTypeUInt16) {
                            printf("          data type: ssv:UInt16\n");
                            printf("          value: %d\n", ssp4c_getParameterUInt16Value(par));
                        }
                        else if(ssp4c_getParameterDatatype(par) == sspDataTypeUInt8) {
                            printf("          data type: ssv:UInt8\n");
                            printf("          value: %d\n", ssp4c_getParameterUInt8Value(par));
                        }
                        else if(ssp4c_getParameterDatatype(par) == sspDataTypeBoolean) {
                            printf("          data type: ssv:Boolean\n");
                            printf("          value: %i\n", ssp4c_getParameterBooleanValue(par));
                        }
                        else if(ssp4c_getParameterDatatype(par) == sspDataTypeString) {
                            printf("          data type: ssv:String\n");
                            printf("          value: %s\n", ssp4c_getParameterStringValue(par));
                        }
                        else if(ssp4c_getParameterDatatype(par) == sspDataTypeEnumeration) {
                            printf("          data type: ssv:Enumeration\n");
                            printf("          value: %s\n", ssp4c_getParameterEnumValue(par));
                            for(int l=0; l<ssp4c_getNumberOfEnumerableParameterValues(par); ++l) {
                                printf("          alternative value: %s\n", ssp4c_getEnumerableParameterValueByIndex(par, l));
                            }
                        }
                    }
                }

                ssdParameterMappingHandle *mapping = ssp4c_getParameterMapping(binding);
                if(mapping) {
                    printf("      parameter mapping:\n");
                    printf("        desciption: %s\n", ssp4c_getParameterMappingDescription(mapping));
                    printf("        id: %s\n", ssp4c_getParameterMappingId(mapping));
                    printf("        type: %s\n", ssp4c_getParameterMappingType(mapping));
                    printf("        source: %s\n", ssp4c_getParameterMappingSource(mapping));
                    printf("        sourceBase: %d\n", ssp4c_getParameterMappingSourceBase(mapping));
                }
            }
        }
    }

    ssp4c_freeSsp(ssp);

    return 0;
}


