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
        printf("Number of SSD connectors: %i\n", ssdConnectorCount);

        for(int j=0; j<ssdConnectorCount; ++j) {
            ssdConnectorHandle *con = ssp4c_getSsdConnectorByIndex(ssd, j);
            printf("  -------------------------------------\n");
            printf("SSD connector name: %s\n", ssp4c_getSsdConnectorName(con));
            printf("SSD connector kind: %i\n", ssp4c_getSsdConnectorKind(con));
            printf("SSD connector description: %s\n", ssp4c_getSsdConnectorDescription(con));
            printf("SSD connector datatype: %i\n", ssp4c_getSsdConnectorDatatype(con));
            printf("SSD connector unit: %s\n", ssp4c_getSsdConnectorUnit(con));
        }

    }
    printf("---------------------------------------\n");

    ssp4c_freeSsp(ssp);

    return 0;
}


