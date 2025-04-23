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
        while (entry = readdir(dir)) != NULL) {
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


//! @brief Remove a directory (including all files and sub directories)
//! @param rootDirPath The path to the directory to remove
//! @param expectedDirNamePrefix Optional directory name prefix to avoid removing unintended root dir. Set to Null to ignore.
//! @returns 0 if removed OK else a system error code or -1
int removeDirectoryRecursively(const char* rootDirPath, const char *expectedDirNamePrefix) {
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
            // --- For debug ---
            //printf("Debug: Would rmdir: %s\n", rootDirPath);
            //rc = 0;
            // -----------------
#ifdef _WIN32
            rc = RemoveDirectoryA(rootDirPath);
            // RemoveDirectoryA returns non-zero on success so we swap it so that rest of the code works as expected (return code 0 = OK)
            rc = (rc == 0) ? 1 : 0;
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
    for(int i=0; i<nfiles; ++i) {
        //add to ssdHandle
        printf("%s\n",files[i]);
    }

    return ssp;
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

    ezxml_t rootElement = ezxml_parse_file(path);
    if(strcmp(rootElement->name, "ssd:SystemStructureDescription")) {
        printf("Wrong root tag name: %s\n", rootElement->name);
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

    parseStringAttributeEzXml(rootElement, "name", &ssd->name);
    parseStringAttributeEzXml(rootElement, "version", &ssd->version);
    parseStringAttributeEzXml(rootElement, "id", &ssd->id);
    parseStringAttributeEzXml(rootElement, "description", &ssd->description);
    parseStringAttributeEzXml(rootElement, "author", &ssd->author);
    parseStringAttributeEzXml(rootElement, "fileversion", &ssd->fileversion);
    parseStringAttributeEzXml(rootElement, "copyright", &ssd->copyright);
    parseStringAttributeEzXml(rootElement, "license", &ssd->license);
    parseStringAttributeEzXml(rootElement, "generationTool", &ssd->generationTool);
    parseStringAttributeEzXml(rootElement, "generationDateAndTime", &ssd->generationDateAndTime);

    ezxml_t systemElement = ezxml_child(rootElement, "ssd:System");
    if(systemElement) {

        //Parse connectors
        ezxml_t connectorsElement = ezxml_child(systemElement, "ssd:Connectors");
        if(connectorsElement) {
            for(ezxml_t connectorElement = connectorsElement->child; connectorElement; connectorElement = connectorElement->ordered) {
                if(!strcmp(connectorElement->name, "ssd:Connector")) {
                    ++ssd->connectorCount;  //Just count them for now, so we can allocate memory before loading them
                }
            }
            if(ssd->connectorCount > 0) {
                ssd->connectors = mallocAndRememberPointer(ssp, ssd->connectorCount*sizeof(ssdConnectorHandle));
            }
            int j=0;
            for(ezxml_t connectorElement = connectorsElement->child; connectorElement; connectorElement = connectorElement->ordered) {
                if(!strcmp(connectorElement->name, "ssd:Connector")) {
                    parseStringAttributeEzXmlAndRememberPointer(connectorElement,  "name",      &ssd->connectors[j].name, ssp);
                    parseStringAttributeEzXmlAndRememberPointer(connectorElement,  "kind",      &ssd->connectors[j].kind, ssp);
                    parseStringAttributeEzXmlAndRememberPointer(connectorElement,  "description",      &ssd->connectors[j].description, ssp);
                    //! @todo Read type, dimensions and geometry
                }
                ++j;
            }
        }
    }

    ezxml_free(rootElement);

    chdir(cwd);

    printf("Finished parsing: %s\n",path);

    return true;
}


void freeDuplicatedConstChar(const char* ptr) {
    free((void*)ptr);
}
