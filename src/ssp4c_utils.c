//#include "ssp4c.h"
#include "ssp4c_utils.h"
#include "ssp4c_common.h"
#include "ssp4c_private.h"

#include <stdlib.h>
#include <string.h>
#ifdef _MSC_VER
#include "dirent/dirent.h"
#else
#include <dirent.h>
#include <sys/stat.h>
#endif
#ifdef _WIN32
#include <windows.h>
#include <tchar.h>
#include <process.h>
#include <direct.h>
#else
#include <unistd.h>
#endif




bool hasFileExtension(const char *filename, const char *extension) {
    const char *dot = strrchr(filename, '.');
    return dot && strcmp(dot, extension) == 0;
}

char **listFiles(sspHandle *ssp, const char *path, int *nfiles) {
    char **fileList = NULL;
    int count = 0;

#ifdef _WIN32
        WIN32_FIND_DATA findData;
        char search_path[MAX_PATH];
        snprintf(search_path, MAX_PATH, "%s\\*.*", path);

        HANDLE hFind = FindFirstFile(search_path, &findData);
        if(hFind == INVALID_HANDLE_VALUE) {
            fprintf(stderr, "Could not open directory.\n");
            *nfiles = 0;
            return NULL;
        }

        do {
            if(!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                fileList = reallocAndRememberPointer(ssp, fileList, sizeof(char *) * (count + 1));
                fileList[count] = _strdup(findData.cFileName);
                count++;
            }
        } while(FindNextFile(hFind, &findData));

        FindClose(hFind);

#else
        DIR *dir = opendir(path);
        if (!dir) {
            perror("opendir");
            *nfiles = 0;
            return NULL;
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if(entry->d_type == DT_REG || entry->d_type == DT_UNKNOWN) {
                fileList = reallocAndRememberPointer(ssp, fileList, sizeof(char *) * (count + 1));
                fileList[count] = duplicateAndRememberString(ssp, entry->d_name);
                count++;
            }
        }

        closedir(dir);
#endif

        *nfiles = count;
        return fileList;
    }

void rememberPointer(sspHandle *ssp, void* ptr)
{
    ssp->numAllocatedPointers++;
    ssp->allocatedPointers = realloc(ssp->allocatedPointers, ssp->numAllocatedPointers * sizeof(void*));
    ssp->allocatedPointers[ssp->numAllocatedPointers-1] = ptr;
}

void* mallocAndRememberPointer(sspHandle *ssp, size_t size)
{
    void* ptr = malloc(size);
    rememberPointer(ssp, ptr);
    return ptr;
}

void *reallocAndRememberPointer(sspHandle *ssp, void *org, size_t size)
{
    int i=0;
    while (i < ssp->numAllocatedPointers && org != ssp->allocatedPointers[i])
        ++i;
    void* ptr = realloc(org, size);
    if (i < ssp->numAllocatedPointers)
        ssp->allocatedPointers[i] = ptr;
    else
        rememberPointer(ssp, ptr);
    return ptr;
}

char* duplicateAndRememberString(sspHandle *ssp, const char* str)
{
    char* ret = _strdup(str);
    rememberPointer(ssp, (void*)ret);
    return ret;
}


//! @brief Parses specified XML attribute and assigns it to target
//! @param element XML element
//! @param attributeName Attribute name
//! @param target Pointer to target variable
//! @returns True if attribute was found, else false
bool parseStringAttributeEzXml(ezxml_t element, const char *attributeName, const char **target)
{
    if(ezxml_attr(element, attributeName)) {
        (*target) = _strdup(ezxml_attr(element, attributeName));
        return true;
    }
    return false;
}

//! @brief Parses specified XML attribute and assigns it to target
//! @param element XML element
//! @param attributeName Attribute name
//! @param target Pointer to target variable
//! @returns True if attribute was found, else false
bool parseStringAttributeEzXmlAndRememberPointer(ezxml_t element, const char *attributeName, const char **target, sspHandle *ssp)
{
    if(ezxml_attr(element, attributeName)) {
        (*target) = duplicateAndRememberString(ssp, ezxml_attr(element, attributeName));
        return true;
    }
    return false;
}

//! @brief Parses specified XML attribute and assigns it to target
//! @param element XML element
//! @param attributeName Attribute name
//! @param target Pointer to target variable
//! @returns True if attribute was found, else false
bool parseBooleanAttributeEzXml(ezxml_t element, const char *attributeName, bool *target)
{
    if(ezxml_attr(element, attributeName)) {
        (*target) = !strcmp(ezxml_attr(element, attributeName), "true");
        return true;
    }
    return false;
}

//! @brief Parses specified XML attribute and assigns it to target
//! @param element XML element
//! @param attributeName Attribute name
//! @param target Pointer to target variable
//! @returns True if attribute was found, else false
bool parseFloat64AttributeEzXml(ezxml_t element, const char *attributeName, double *target)
{
    if(ezxml_attr(element, attributeName)) {
        (*target) = atof(ezxml_attr(element, attributeName));
        return true;
    }
    return false;
}

//! @brief Parses specified XML attribute and assigns it to target
//! @param element XML element
//! @param attributeName Attribute name
//! @param target Pointer to target variable
//! @returns True if attribute was found, else false
bool parseInt16AttributeEzXml(ezxml_t element, const char *attributeName, short *target)
{
    if(ezxml_attr(element, attributeName)) {
        (*target) = (short)atoi(ezxml_attr(element, attributeName));
        return true;
    }
    return false;
}

//! @brief Parses specified XML attribute and assigns it to target
//! @param element XML element
//! @param attributeName Attribute name
//! @param target Pointer to target variable
//! @returns True if attribute was found, else false
bool parseInt64AttributeEzXml(ezxml_t element, const char *attributeName, int64_t* target)
{
    if(ezxml_attr(element, attributeName)) {
        (*target) = atol(ezxml_attr(element, attributeName));
        return true;
    }
    return false;
}

//! @brief Parses specified XML attribute and assigns it to target
//! @param element XML element
//! @param attributeName Attribute name
//! @param target Pointer to target variable
//! @returns True if attribute was found, else false
bool parseInt32AttributeEzXml(ezxml_t element, const char *attributeName, int32_t *target)
{
    if(ezxml_attr(element, attributeName)) {
        (*target) = atoi(ezxml_attr(element, attributeName));
        return true;
    }
    return false;
}

//! @brief Parses specified XML attribute and assigns it to target
//! @param element XML element
//! @param attributeName Attribute name
//! @param target Pointer to target variable
//! @returns True if attribute was found, else false
bool parseFloat32AttributeEzXml(ezxml_t element, const char *attributeName, float *target)
{
    if(ezxml_attr(element, attributeName)) {
        (*target) = (float)atof(ezxml_attr(element, attributeName));
        return true;
    }
    return false;
}

//! @brief Parses specified XML attribute and assigns it to target
//! @param element XML element
//! @param attributeName Attribute name
//! @param target Pointer to target variable
//! @returns True if attribute was found, else false
bool parseInt8AttributeEzXml(ezxml_t element, const char *attributeName, int8_t *target)
{
    if(ezxml_attr(element, attributeName)) {
        (*target) = (int8_t)atoi(ezxml_attr(element, attributeName));
        return true;
    }
    return false;
}

//! @brief Parses specified XML attribute and assigns it to target
//! @param element XML element
//! @param attributeName Attribute name
//! @param target Pointer to target variable
//! @returns True if attribute was found, else false
bool parseUInt64AttributeEzXml(ezxml_t element, const char *attributeName, uint64_t *target)
{
    if(ezxml_attr(element, attributeName)) {
        (*target) = strtoul(ezxml_attr(element, attributeName), NULL, 10);
        return true;
    }
    return false;
}

//! @brief Parses specified XML attribute and assigns it to target
//! @param element XML element
//! @param attributeName Attribute name
//! @param target Pointer to target variable
//! @returns True if attribute was found, else false
bool parseUInt32AttributeEzXml(ezxml_t element, const char *attributeName, uint32_t *target)
{
    if(ezxml_attr(element, attributeName)) {
        (*target) = (uint32_t)strtoul(ezxml_attr(element, attributeName), NULL, 10);
        return true;
    }
    return false;
}

//! @brief Parses specified XML attribute and assigns it to target
//! @param element XML element
//! @param attributeName Attribute name
//! @param target Pointer to target variable
//! @returns True if attribute was found, else false
bool parseUInt16AttributeEzXml(ezxml_t element, const char *attributeName, uint16_t *target)
{
    if(ezxml_attr(element, attributeName)) {
        (*target) = (uint16_t)strtoul(ezxml_attr(element, attributeName), NULL, 10);
        return true;
    }
    return false;
}

//! @brief Parses specified XML attribute and assigns it to target
//! @param element XML element
//! @param attributeName Attribute name
//! @param target Pointer to target variable
//! @returns True if attribute was found, else false
bool parseUInt8AttributeEzXml(ezxml_t element, const char *attributeName, uint8_t *target)
{
    if(ezxml_attr(element, attributeName)) {
        (*target) = (uint8_t)strtoul(ezxml_attr(element, attributeName), NULL, 10);
        return true;
    }
    return false;
}

int changeToParentDirectory(const char *path) {
    char parent[FILENAME_MAX];
    strncpy(parent, path, FILENAME_MAX);
    parent[FILENAME_MAX - 1] = '\0';

    // Find the last backslash or slash
    char *lastSlash = strrchr(parent, '\\');
    if (!lastSlash) lastSlash = strrchr(parent, '/');

    if (lastSlash) {
        *lastSlash = '\0'; // Truncate path at the last slash
        chdir(parent);
    } else {
        printf("Could not determine parent directory of '%s'\n", path);
        return 1;
    }
}


//! @brief Remove a directory (including all files and sub directories)
//! @param rootDirPath The path to the directory to remove
//! @param expectedDirNamePrefix Optional directory name prefix to avoid removing unintended root dir. Set to Null to ignore.
//! @returns 0 if removed OK else a system error code or -1
int removeDirectoryRecursively(const char* rootDirPath, const char *expectedDirNamePrefix)
{
    // If expectedDirNamePrefix is set, ensure that the name of the directory being removed starts with this prefix
    // This is just an optional sanity check to prevent unexpected removal of the wrong directory
    if (expectedDirNamePrefix != NULL) {
        int dsp; // Dir separator position
        for (dsp=(int)strlen(rootDirPath); dsp>-1; dsp--) {
            if ( rootDirPath[dsp] == '/' || rootDirPath[dsp] == '\\' ) {
                break;
            }
        }
        dsp++; // Advance to first char after separator (or first char if no separator found)

        if (strncmp(expectedDirNamePrefix, rootDirPath+dsp, strlen(expectedDirNamePrefix)) != 0) {
            printf("Directory name prefix '%s' mismatch, refusing to remove directory '%s'\n", expectedDirNamePrefix, rootDirPath);
            return 1;
        }
    }

    DIR* dir = opendir(rootDirPath);
    int rc = -1;
    if (dir) {
        struct dirent *entry = readdir(dir);
        while(entry) {
            // Avoid recursing upwards
            if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) {
                entry = readdir(dir);
                continue;
            }

            // Determine full path to file or directory for current entry
            size_t fullPathLength = strlen(rootDirPath)+ strlen(entry->d_name) + 2;
            char* fullPath = malloc(fullPathLength);
            snprintf(fullPath, fullPathLength, "%s/%s", rootDirPath, entry->d_name);

            // Figure out if entry represents a directory or not
            bool entryIsDir;
            struct stat statbuf;
#ifdef _DIRENT_HAVE_D_TYPE
            entryIsDir = (entry->d_type == DT_DIR);
            // On some filesystems d_type is not set, then use stat to check the type
            if (entry->d_type == DT_UNKNOWN) {
                if (!stat(fullPath, &statbuf)) {
                    entryIsDir = S_ISDIR(statbuf.st_mode);
                }
            }
#else
            // On some systems d_type is note present, in which case stats is used
            if (!stat(fullPath, &statbuf)) {
                entryIsDir = S_ISDIR(statbuf.st_mode);
            }
#endif
            // Recurse on directory, else unlink file
            if (entryIsDir) {
                rc = removeDirectoryRecursively(fullPath, NULL);
            }
            else {
                // --- For debug ---
                //printf("Debug: Would unlink: %s\n", fullPath);
                //rc = 0;
                // -----------------
#ifdef _WIN32
                rc = _unlink(fullPath);
#else
                rc = unlink(fullPath);
#endif
                if (rc != 0) {
                    perror("Error");
                    printf("Could not remove '%s'\n", fullPath);
                }
            }
            free(fullPath);
            if (rc != 0) {
                break;
            }
            entry = readdir(dir);
        }
        closedir(dir);
        if (rc == 0) {
            // --- For debug ---git
            //printf("Debug: Would rmdir: %s\n", rootDirPath);
            //rc = 0;
            // -----------------
#ifdef _WIN32
            rc = RemoveDirectoryA(rootDirPath);
            // RemoveDirectoryA returns non-zero on success so we swap it so that rest of the code works as expected (return code 0 = OK)
            rc = (rc == 0) ? 1 : 0;
            if(rc != 0) {
                DWORD err = GetLastError();
                printf("RemoveDirectoryA failed with error: %lu\n", err);
                char cwd[MAX_PATH];
                GetCurrentDirectoryA(MAX_PATH, cwd);
                printf("Current working directory: %s\n", cwd);
            }
#else
            rc = rmdir(rootDirPath);
#endif
            if (rc != 0) {
                perror("Error");
            }
        }
        if (rc != 0) {
            printf("Could not remove '%s'\n", rootDirPath);
        }
    }
    else {
        perror("Error");
        printf("Could not access '%s' for removal\n", rootDirPath);
    }
    return rc;
}


const char* generateTempPath()
{
    char cwd[FILENAME_MAX];
#ifdef _WIN32
    _getcwd(cwd, sizeof(char)*FILENAME_MAX);
#else
    getcwd(cwd, sizeof(char)*FILENAME_MAX);
#endif

    // Decide location for where to unzip
    char unzipLocationTemp[FILENAME_MAX] = {0};

#ifdef _WIN32
    DWORD len = GetTempPathA(FILENAME_MAX, unzipLocationTemp);
    if (len == 0) {
        printf("Cannot find temp path, using current directory\n");
    }

    // Create a unique name for the temp folder
    char tempFileName[11] = "\0\0\0\0\0\0\0\0\0\0\0";
    srand(_getpid());
    for(int i=0; i<10; ++i) {
        tempFileName[i] = rand() % 26 + 65;
    }

    strncat(unzipLocationTemp, "ssp4c_", FILENAME_MAX-strlen(unzipLocationTemp)-1);
    char * ds = strrchr(tempFileName, '\\');
    if (ds) {
        strncat(unzipLocationTemp, ds+1, FILENAME_MAX-strlen(unzipLocationTemp)-1);
    }
    else {
        strncat(unzipLocationTemp, tempFileName, FILENAME_MAX-strlen(unzipLocationTemp)-1);
    }
    _mkdir(unzipLocationTemp);
#else
    const char* env_tmpdir = getenv("TMPDIR");
    const char* env_tmp = getenv("TMP");
    const char* env_temp = getenv("TEMP");
    if (env_tmpdir) {
        strncat(unzipLocationTemp, env_tmpdir, FILENAME_MAX-strlen(unzipLocationTemp)-1);
    }
    else if (env_tmp) {
        strncat(unzipLocationTemp, env_tmp, FILENAME_MAX-strlen(unzipLocationTemp)-1);
    }
    else if (env_temp) {
        strncat(unzipLocationTemp, env_temp, FILENAME_MAX-strlen(unzipLocationTemp)-1);
    }
    else if (access("/tmp/", W_OK) == 0) {
        strncat(unzipLocationTemp, "/tmp/", FILENAME_MAX-strlen(unzipLocationTemp)-1);
    }
    // If no suitable temp directory is found, the current working directory will be used

    // Append / if needed
    if (strlen(unzipLocationTemp) > 0 && unzipLocationTemp[strlen(unzipLocationTemp)-1] != '/') {
        strncat(unzipLocationTemp, "/", FILENAME_MAX-strlen(unzipLocationTemp)-1);
    }

    strncat(unzipLocationTemp, "ssp4c_", FILENAME_MAX-strlen(unzipLocationTemp)-1);
    strncat(unzipLocationTemp, "XXXXXX", FILENAME_MAX-strlen(unzipLocationTemp)-1); // XXXXXX is for unique name by mkdtemp
    mkdtemp(unzipLocationTemp);
#endif

    return _strdup(unzipLocationTemp); //Not freed automatically!
}


bool unzipSsp(const char* sspfile, const char* unzipLocation)
{
    char cwd[FILENAME_MAX];
#ifdef _WIN32
    _getcwd(cwd, sizeof(char)*FILENAME_MAX);
#else
    getcwd(cwd, sizeof(char)*FILENAME_MAX);
#endif

#ifdef SSP4C_WITH_MINIZIP
    int argc = 6;
    const char *argv[6];
    argv[0] = "miniunz";
    argv[1] = "-x";
    argv[2] = "-o";
    argv[3] = sspfile;
    argv[4] = "-d";
    argv[5] = unzipLocation;

    int status = miniunz(argc, (char**)argv);
    if (status != 0) {
        printf("Failed to unzip SSP: status = %i, to location %s\n",status, unzipLocation);
        return NULL;
    }
    // miniunzip will change dir to unzipLocation, lets change back
    chdir(cwd);
#else
#ifdef _WIN32
    const int commandLength = strlen("tar -xf \"") + strlen(sspfile) + strlen("\" -C \"") + strlen(unzipLocation) + 2;

    // Allocate memory for the command
    char *command = malloc(commandLength * sizeof(char));
    if (command == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return false;
    }
    // Build the command string
    snprintf(command, commandLength, "tar -xf \"%s\" -C \"%s\"", sspfile, unzipLocation);
#else
    const int commandLength = strlen("unzip -o \"") + strlen(sspfile) + strlen("\" -d \"") + strlen(unzipLocation) + 2;

    // Allocate memory for the command
    char *command = malloc(commandLength * sizeof(char));
    if (command == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    // Build the command string
    snprintf(command, commandLength, "unzip -o \"%s\" -d \"%s\"", sspfile, unzipLocation);
#endif
    const int status = system(command);
    free(command);
    if (status != 0) {
        printf("Failed to unzip SSP: status = %i, to location %s\n",status, unzipLocation);
        return false;
    }
#endif

    return true;
}

bool zipSsp(const char* sspfile, const char* zipLocation)
{
    char cwd[FILENAME_MAX];
#ifdef _WIN32
    _getcwd(cwd, sizeof(char)*FILENAME_MAX);
#else
    getcwd(cwd, sizeof(char)*FILENAME_MAX);
#endif

#ifdef SSP4C_WITH_MINIZIP
#ifdef _WIN32
    //Windows does not expand wildcards, so we need to manually list all files in the folder before passing it to Minizip
    WIN32_FIND_DATAA findData;
    HANDLE hFind;
    char searchPath[MAX_PATH];

    snprintf(searchPath, MAX_PATH, "%s\\*.*", zipLocation);
    hFind = FindFirstFileA(searchPath, &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Could not list directory: %s\n", zipLocation);
        return 1;
    }

    // Prepare args for minizip
    const char *argv[512];
    int argc = 0;
    argv[argc++] = "minizip";
    argv[argc++] = "-o"; // overwrite
    argv[argc++] = "-0"; // no compression
    argv[argc++] = "-j"; // junk path
    argv[argc++] = sspfile;

    do {
        //Do not include . and ..
        if(strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0) {
            continue;
        }

        //Foudn a file, append it to arguments
        char fullPath[MAX_PATH];
        snprintf(fullPath, MAX_PATH, "%s\\%s", zipLocation, findData.cFileName);
        argv[argc++] = _strdup(fullPath);
    } while(FindNextFileA(hFind, &findData));

    FindClose(hFind);

    int result = minizip(argc, (char **)argv);

    // If you strdup'd paths, you should free them here
    for (int i = 5; i < argc; ++i) {
        freeDuplicatedConstChar(argv[i]);
    }
#else

    char filesToZip[FILENAME_MAX] = {0};
    strncat(filesToZip, zipLocation, FILENAME_MAX-strlen(filesToZip)-1);
    strncat(filesToZip, "/*", FILENAME_MAX-strlen(filesToZip)-1);
    printf("filesToZip: %s\n", filesToZip);

    int argc = 6;
    const char *argv[6];
    argv[0] = "minizip";
    argv[1] = "-o";
    argv[2] = "-0";
    argv[3] = "-j";
    argv[4] = sspfile;
    argv[5] = filesToZip;
    //argv[6] = unzipLocation;

    int status = minizip(argc, (char**)argv);
    if (status != 0) {
         printf("Failed to zip SSP: status = %i, to file %s\n",status, sspfile);
         return NULL;
     }
     // miniunzip will change dir to unzipLocation, lets change back
     chdir(cwd);
#endif
#else
#ifdef _WIN32
    const int commandLength = strlen("tar -cf \"") + strlen(sspfile) + strlen("\" -C \" *") + strlen(zipLocation) + 2;

    // Allocate memory for the command
    char *command = malloc(commandLength * sizeof(char));
    if (command == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return false;
    }
    // Build the command string
    //tar -cf test.ssp -C C:\users\robbr48\git\ssp4c\build\Desktop_Qt_6_7_2_MinGW_64_bit-Debug\test *
    snprintf(command, commandLength, "tar -cf \"%s\" -C \"%s\" *", sspfile, zipLocation);
#else
    const int commandLength = strlen("zip -FS -r -j -0 \"") + strlen(sspfile) + strlen("\" \"") + strlen(zipLocation) + strlen("\"/*") + 2;

     // Allocate memory for the command
     char *command = malloc(commandLength * sizeof(char));
     if (command == NULL) {
         fprintf(stderr, "Memory allocation failed\n");
         return NULL;
     }
     // Build the command string
    snprintf(command, commandLength, "zip -FS -r -j -0 \"%s\" \"%s\"/*", sspfile, zipLocation);
#endif
    const int status = system(command);
    free(command);
    if (status != 0) {
        printf("Failed to zip SSP: status = %i, from location %s\n",status, zipLocation);
        return false;
    }
#endif

    return true;
}



sspHandle *ssp4c_loadUnzippedSsp_internal(const char *unzipLocation, bool unzippedLocationIsTemporary)
{
    sspHandle *ssp = calloc(1, sizeof(sspHandle)); // Using calloc to ensure all member pointers (and data) are initialized to NULL (0)
    ssp->numAllocatedPointers = 0;
    ssp->allocatedPointers = NULL;
    ssp->version = sspVersionUnknown;
    if (unzippedLocationIsTemporary)
    {
        ssp->unzippedLocation = unzipLocation;  //Already duplicated
        rememberPointer(ssp, (void*)unzipLocation);
    }
    else {
        ssp->unzippedLocation = duplicateAndRememberString(ssp, unzipLocation);
    }

    char cwd[FILENAME_MAX];
#ifdef _WIN32
    _getcwd(cwd, sizeof(char)*FILENAME_MAX);
#else
    getcwd(cwd, sizeof(char)*FILENAME_MAX);
#endif
    chdir(ssp->unzippedLocation);

    ssp->unzippedLocationIsTemporary = false;

    int nfiles;
    char** files = listFiles(ssp,ssp->unzippedLocation,&nfiles);

    chdir(cwd);

    return ssp;
}

bool parseConnectorsElement(ezxml_t element, int *count, ssdConnectorHandle** connectors, sspHandle *ssp)
{
    (*count) = 0;
    for(ezxml_t connectorElement = element->child; connectorElement; connectorElement = connectorElement->ordered) {
        if(!strcmp(connectorElement->name, "ssd:Connector")) {
            ++(*count);  //Just count them for now, so we can allocate memory before loading them
        }
    }
    if((*count) > 0) {
        (*connectors) = mallocAndRememberPointer(ssp, (*count)*sizeof(ssdConnectorHandle));
    }
    int i=0;
    for(ezxml_t connectorElement = element->child; connectorElement; connectorElement = connectorElement->ordered) {
        if(!strcmp(connectorElement->name, "ssd:Connector")) {
            parseStringAttributeEzXmlAndRememberPointer(connectorElement,  "name",      &(*connectors)[i].name, ssp);

            (*connectors)[i].kind = ssdConnectorKindUnspecifed;
            const char* kind = NULL;
            if(parseStringAttributeEzXml(connectorElement, "kind", &kind)) {
                if(!strcmp(kind, "input")) {
                    (*connectors)[i].kind = ssdConnectorKindInput;
                }
                else if(!strcmp(kind, "output")) {
                    (*connectors)[i].kind = ssdConnectorKindOutput;
                }
                else if(!strcmp(kind, "parameter")) {
                    (*connectors)[i].kind = ssdConnectorKindParameter;
                }
                else if(!strcmp(kind, "calculatedParameter")) {
                    (*connectors)[i].kind = ssdConnectorKindCalculatedParameter;
                }
                else if(!strcmp(kind, "calculatedParameter")) {
                    (*connectors)[i].kind = ssdConnectorKindStructuralParameter;
                }
                else if(!strcmp(kind, "calculatedConstant")) {
                    (*connectors)[i].kind = ssdConnectorKindConstant;
                }
                else if(!strcmp(kind, "local")) {
                    (*connectors)[i].kind = ssdConnectorKindLocal;
                }
                else if(!strcmp(kind, "inout")) {
                    (*connectors)[i].kind = ssdConnectorKindInout;
                }
                else if(!strcmp(kind, "unspecified")) {
                    (*connectors)[i].kind = ssdConnectorKindUnspecifed;
                }
                else {
                    printf("Unknown causality: %s\n", kind);
                    freeDuplicatedConstChar(kind);
                    return false;
                }
                freeDuplicatedConstChar(kind);
            }

            parseStringAttributeEzXmlAndRememberPointer(connectorElement,  "description",      &(*connectors)[i].description, ssp);

            for(ezxml_t subElement = connectorElement->child; subElement; subElement = subElement->ordered) {
                if(!strcmp(subElement->name, "ssc:Real")) {
                    (*connectors)[i].datatype = sspDataTypeReal;
                }
                else if(!strcmp(subElement->name, "ssc:Float64")) {
                    (*connectors)[i].datatype = sspDataTypeFloat64;
                }
                else if(!strcmp(subElement->name, "ssc:Float32")) {
                    (*connectors)[i].datatype = sspDataTypeFloat32;
                }
                else if(!strcmp(subElement->name, "ssc:Integer")) {
                    (*connectors)[i].datatype = sspDataTypeInteger;
                }
                else if(!strcmp(subElement->name, "ssc:Int8")) {
                    (*connectors)[i].datatype = sspDataTypeInt8;
                }
                else if(!strcmp(subElement->name, "ssc:UInt8")) {
                    (*connectors)[i].datatype = sspDataTypeUInt8;
                }
                else if(!strcmp(subElement->name, "ssc:Int16")) {
                    (*connectors)[i].datatype = sspDataTypeInt16;
                }
                else if(!strcmp(subElement->name, "ssc:UInt16")) {
                    (*connectors)[i].datatype = sspDataTypeUInt16;
                }
                else if(!strcmp(subElement->name, "ssc:Int32")) {
                    (*connectors)[i].datatype = sspDataTypeInt32;
                }
                else if(!strcmp(subElement->name, "ssc:UInt32")) {
                    (*connectors)[i].datatype = sspDataTypeUInt32;
                }
                else if(!strcmp(subElement->name, "ssc:Int64")) {
                    (*connectors)[i].datatype = sspDataTypeInt64;
                }
                else if(!strcmp(subElement->name, "ssc:UInt64")) {
                    (*connectors)[i].datatype = sspDataTypeUInt64;
                }
                else if(!strcmp(subElement->name, "ssc:Boolean")) {
                    (*connectors)[i].datatype = sspDataTypeBoolean;
                }
                else if(!strcmp(subElement->name, "ssc:String")) {
                    (*connectors)[i].datatype = sspDataTypeString;
                }
                else if(!strcmp(subElement->name, "ssc:Enumeration")) {
                    (*connectors)[i].datatype = sspDataTypeEnumeration;
                }
                else if(!strcmp(subElement->name, "ssc:Binary")) {
                    (*connectors)[i].datatype = sspDataTypeBinary;
                }

                //Read unit
                if((*connectors)[i].datatype == sspDataTypeReal ||
                    (*connectors)[i].datatype == sspDataTypeFloat64 ||
                    (*connectors)[i].datatype == sspDataTypeFloat32) {
                    parseStringAttributeEzXmlAndRememberPointer(subElement, "unit", &(*connectors)[i].unit, ssp);
                }
            }
        }
        ++i;
    }

    return true;
}

bool parseParameterElement(ezxml_t element, ssvParameterHandle* parameterHandle, sspHandle *ssp)
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

            parameterHandle->enumValues = mallocAndRememberPointer(ssp, sizeof(const char*)*parameterHandle->enumValuesCount);

            int i=0;
            valueElement = ezxml_child(subElement, "ssv:Value");
            while(valueElement) {
                parseStringAttributeEzXmlAndRememberPointer(valueElement, "value", &(parameterHandle->enumValues[i]), ssp);
                valueElement = valueElement->next;
                ++i;
            }
        }
        else if(!strcmp(subElement->name, "ssc:Binary")) {
            parameterHandle->datatype = sspDataTypeBinary;

            //! @todo Figure out how to parse binary values
        }
    }

    return true;
}

bool parseParameterSetElement(ezxml_t element, ssvParameterSetHandle* parameterSetHandle, sspHandle *ssp)
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
                    parseParameterElement(parameterElement, &(parameterSetHandle->parameters[i]), ssp);
                }
                ++i;
            }
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
    }

    int i=0;
    for(ezxml_t entryElement = transformationElement->child; entryElement; entryElement = entryElement->ordered) {
        parseSscMapEntryElement(entryElement, &(handle->mapEntries[i]), ssp);
        ++i;
    }
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
        handle->mappingEntries = mallocAndRememberPointer(ssp, sizeof(ssmParameterMappingEntryHandle)*handle->mappingEntryCount);
    }

    int i=0;
    for(ezxml_t entryElement = element->child; entryElement; entryElement = entryElement->ordered) {
        parseSsmMappingEntryElement(entryElement, &(handle->mappingEntries[i]), ssp);
        ++i;
    }
}

bool parseParameterMappingElement(ezxml_t element,ssdParameterMappingHandle* handle, sspHandle *ssp)
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
}

bool parseSsdParameterValuesElement(ezxml_t element, ssdParameterValuesHandle* handle, sspHandle *ssp)
{
    handle->parameterSet = NULL;
    ezxml_t parameterSetElement = ezxml_child(element, "ssv:ParameterSet");
    if(parameterSetElement) {
        handle->parameterSet = mallocAndRememberPointer(ssp, sizeof(ssvParameterSetHandle));
        parseParameterSetElement(parameterSetElement, handle->parameterSet, ssp);
    }
}

bool parseParameterBindingsElement(ezxml_t element, int *count, ssdParameterBindingHandle** parameterBindings, sspHandle *ssp)
{
    (*count) = 0;

    for (ezxml_t parameterBindingsElement = element->child; parameterBindingsElement ; parameterBindingsElement  = parameterBindingsElement ->ordered) {
        if (!strcmp(parameterBindingsElement ->name, "ssd:ParameterBinding")) {
            ++(*count);
        }
    }

    if ((*count) > 0) {
        (*parameterBindings) = mallocAndRememberPointer(ssp, sizeof(ssdParameterBindingHandle) * (*count));
    }

    int i = 0;
    for (ezxml_t parameterBindingsElement = element->child; parameterBindingsElement; parameterBindingsElement = parameterBindingsElement->ordered) {
        if (!strcmp(parameterBindingsElement->name, "ssd:ParameterBinding")) {
            (*parameterBindings[i]).type = NULL;
            (*parameterBindings[i]).source = NULL;
            (*parameterBindings[i]).prefix = NULL;
            parseStringAttributeEzXmlAndRememberPointer(parameterBindingsElement, "type", &(*parameterBindings)[i].type, ssp);
            parseStringAttributeEzXmlAndRememberPointer(parameterBindingsElement, "source", &(*parameterBindings)[i].source, ssp);
            parseStringAttributeEzXmlAndRememberPointer(parameterBindingsElement, "prefix", &(*parameterBindings)[i].prefix, ssp);

            (*parameterBindings)[i].sourceBase = ssdParameterSourceBaseSSD;
            const char* sourceBase = NULL;
            if(parseStringAttributeEzXml(parameterBindingsElement, "sourceBase", &sourceBase)) {
                if(!strcmp(sourceBase, "SSD")) {
                    (*parameterBindings)[i].sourceBase = ssdParameterSourceBaseSSD;
                }
                else if(!strcmp(sourceBase, "component")) {
                    (*parameterBindings)[i].sourceBase = ssdParameterSourceBaseComponent;
                }
                freeDuplicatedConstChar(sourceBase);
            }

            //Parse parameter sets
            (*parameterBindings)[i].parameterValues = NULL;
            ezxml_t parameterValuesElement = ezxml_child(parameterBindingsElement, "ssd:ParameterValues");
            if(parameterValuesElement) {
                (*parameterBindings)[i].parameterValues = mallocAndRememberPointer(ssp, sizeof(ssdParameterValuesHandle));
                 parseSsdParameterValuesElement(parameterValuesElement, (*parameterBindings)[i].parameterValues, ssp);
            }

            //Parse parameter mappings
            (*parameterBindings)[i].parameterMapping = NULL;
            ezxml_t parameterMappingElement = ezxml_child(parameterBindingsElement, "ssd:ParameterMapping");
            if(parameterMappingElement) {
                (*parameterBindings)[i].parameterMapping = mallocAndRememberPointer(ssp, sizeof(ssdParameterMappingHandle));
                parseParameterMappingElement(parameterMappingElement, (*parameterBindings)[i].parameterMapping, ssp);
            }
        }
    }
}

bool parseComponentsElement(ezxml_t element, int *count, ssdComponentHandle** components, sspHandle *ssp)
{
    for (ezxml_t componentElement = element->child; componentElement; componentElement = componentElement->ordered) {
        if (!strcmp(componentElement->name, "ssd:Component")) {
            ++(*count);
        }
    }

    if ((*count) > 0) {
        (*components) = mallocAndRememberPointer(ssp, sizeof(ssdComponentHandle) * (*count));
    }

    int i = 0;
    for (ezxml_t componentElement = element->child; componentElement; componentElement = componentElement->ordered) {
        if (!strcmp(componentElement->name, "ssd:Component")) {
            (*components[i]).xml = ezxml_idx(ezxml_child(element, "ssd:Component"),i);
            parseStringAttributeEzXmlAndRememberPointer(componentElement, "name", &(*components)[i].name, ssp);
            parseStringAttributeEzXmlAndRememberPointer(componentElement, "type", &(*components)[i].type, ssp);
            parseStringAttributeEzXmlAndRememberPointer(componentElement, "source", &(*components)[i].source, ssp);

            (*components)[i].implementation = ssdComponentImplementationAny;
            const char* implementation = NULL;
            if(parseStringAttributeEzXml(componentElement, "implementation", &implementation)) {
                if(!strcmp(implementation, "any")) {
                    (*components)[i].implementation = ssdComponentImplementationAny;
                }
                else if(!strcmp(implementation, "ModelExchange")) {
                    (*components)[i].implementation = ssdComponentImplementationModelExchange;
                }
                else if(!strcmp(implementation, "CoSimulation")) {
                    (*components)[i].implementation = ssdComponentImplementationCoSimulation;
                }
                else if(!strcmp(implementation, "ScheduledExecution")) {
                    (*components)[i].implementation = ssdComponentImplementationScheduledExecution;
                }
                freeDuplicatedConstChar(implementation);
            }

            //Parse connectors
            ezxml_t componentConnectorsElement = ezxml_child(componentElement, "ssd:Connectors");
            if(componentConnectorsElement) {
                parseConnectorsElement(componentConnectorsElement, &(*components)[i].connectorCount, &(*components)[i].connectors, ssp);
            }

            //Parse parameter bindings
            // Parse geometry
            (*components)[i].geometry.x1 = 0;
            (*components)[i].geometry.y1 = 0;
            (*components)[i].geometry.x2 = 0;
            (*components)[i].geometry.y2= 0;
            (*components)[i].geometry.rotation = 0;
            (*components)[i].geometry.iconRotation = 0;
            (*components)[i].geometry.iconSource = NULL;
            (*components)[i].geometry.iconFlip = false;
            (*components)[i].geometry.iconFixedAspectRatio = false;
            ezxml_t geometryElement = ezxml_child(componentElement, "ssd:ElementGeometry");
            (*components)[i].geometry.xml = geometryElement;
            if(geometryElement) {
                parseFloat64AttributeEzXml(geometryElement, "x1", &(*components)[i].geometry.x1);
                parseFloat64AttributeEzXml(geometryElement, "y1", &(*components)[i].geometry.y1);
                parseFloat64AttributeEzXml(geometryElement, "x2", &(*components)[i].geometry.x2);
                parseFloat64AttributeEzXml(geometryElement, "y2", &(*components)[i].geometry.y2);
                parseFloat64AttributeEzXml(geometryElement, "rotation", &(*components)[i].geometry.rotation);
                parseFloat64AttributeEzXml(geometryElement, "iconRotation", &(*components)[i].geometry.iconRotation);
                parseStringAttributeEzXmlAndRememberPointer(geometryElement, "iconSource", &(*components)[i].geometry.iconSource, ssp);
                parseBooleanAttributeEzXml(geometryElement, "iconFlip", &(*components)[i].geometry.iconFlip);
                parseBooleanAttributeEzXml(geometryElement, "iconFixedAspectRatio", &(*components)[i].geometry.iconFixedAspectRatio);
            }
            (*components)[i].geometry.ssp = ssp;

            ezxml_t parameterBindingsElement = ezxml_child(componentElement, "ssd:ParameterBindings");
            if(parameterBindingsElement) {
                parseParameterBindingsElement(parameterBindingsElement, &(*components)[i].parameterBindingsCount, &(*components)[i].parameterBindings, ssp);
            }

            ++i;
        }
    }
}

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
    ssd->connectorCount = 0;
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
            parseConnectorsElement(connectorsElement, &ssd->connectorCount, &ssd->connectors, ssp);
        }

        // Parse components
        ezxml_t componentsElement = ezxml_child(systemElement, "ssd:Elements");
        if (componentsElement) {
            parseComponentsElement(componentsElement, &ssd->componentCount, &ssd->components, ssp);
        }
    }

    chdir(cwd);

    return true;
}


void freeDuplicatedConstChar(const char* ptr) {
    free((void*)ptr);
}
