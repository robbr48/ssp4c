#include "ssp4c_private.h"
#include "ssp4c_ssd_connection_geometry.h"
#include "ssp4c_utils.h"
#include "ssp4c_xml_constants.h"

double *ssp4c_ssd_connectionGeometry_getPointsX(ssdConnectionGeometryHandle *h, int *n)
{
    *n = 0;
    char *text = NULL;

    if (!parseStringAttributeEzXml(h->xml, XML_ATTR_POINTSX, (const char**)&text) || text == NULL) {
        return NULL;
    }

    int capacity = 10;
    int count = 0;
    double* result = malloc(capacity * sizeof(double));
    if (!result) {
        free(text);
        return NULL;
    }

    char* ptr = text;
    char* end;

    while (*ptr != '\0') {
        double value = strtod(ptr, &end);

        if (ptr == end) {
            // No conversion happened → skip character
            ptr++;
            continue;
        }

        if (count >= capacity) {
            capacity *= 2;
            double* newResult = realloc(result, capacity * sizeof(double));
            if (!newResult) {
                free(result);
                free(text);
                return NULL;
            }
            result = newResult;
        }

        result[count++] = value;
        ptr = end;
    }

    *n = count;
    free(text);
    return result;
}


double *ssp4c_ssd_connectionGeometry_getPointsY(ssdConnectionGeometryHandle *h, int *n)
{
    *n = 0;
    char *text = NULL;

    if (!parseStringAttributeEzXml(h->xml, XML_ATTR_POINTSY, (const char**)&text) || text == NULL) {
        return NULL;
    }

    int capacity = 10;
    int count = 0;
    double* result = malloc(capacity * sizeof(double));
    if (!result) {
        free(text);
        return NULL;
    }

    char* ptr = text;
    char* end;

    while (*ptr != '\0') {
        double value = strtod(ptr, &end);

        if (ptr == end) {
            // No conversion happened → skip character
            ptr++;
            continue;
        }

        if (count >= capacity) {
            capacity *= 2;
            double* newResult = realloc(result, capacity * sizeof(double));
            if (!newResult) {
                free(result);
                free(text);
                return NULL;
            }
            result = newResult;
        }

        result[count++] = value;
        ptr = end;
    }

    *n = count;
    free(text);
    
    // Add functions for setting points arrays
    return result;
}

void ssp4c_ssd_connectionGeometry_setPointsX(ssdConnectionGeometryHandle *h, const double *points, int n)
{
    if (!h || !h->xml) {
        return;
    }

    if (n <= 0 || points == NULL) {
        setAttributeAndRememberPointersEzxml(h->xml, XML_ATTR_POINTSX, "", h->ssp);
        return;
    }

    size_t bufSize = (size_t)n * 32 + 1;
    char *buf = malloc(bufSize);
    if (!buf) {
        return;
    }

    size_t used = 0;
    for (int i = 0; i < n; ++i) {
        int written = snprintf(buf + used, bufSize - used, i == 0 ? "%g" : " %g", points[i]);
        if (written < 0) {
            free(buf);
            return;
        }

        if ((size_t)written >= bufSize - used) {
            size_t newSize = used + (size_t)written + 1;
            char *newBuf = realloc(buf, newSize);
            if (!newBuf) {
                free(buf);
                return;
            }
            buf = newBuf;
            bufSize = newSize;
            written = snprintf(buf + used, bufSize - used, i == 0 ? "%g" : " %g", points[i]);
            if (written < 0 || (size_t)written >= bufSize - used) {
                free(buf);
                return;
            }
        }

        used += (size_t)written;
    }

    setAttributeAndRememberPointersEzxml(h->xml, XML_ATTR_POINTSX, buf, h->ssp);
    free(buf);
}

void ssp4c_ssd_connectionGeometry_setPointsY(ssdConnectionGeometryHandle *h, const double *points, int n)
{
    if (!h || !h->xml) {
        return;
    }

    if (n <= 0 || points == NULL) {
        setAttributeAndRememberPointersEzxml(h->xml, XML_ATTR_POINTSY, "", h->ssp);
        return;
    }

    size_t bufSize = (size_t)n * 32 + 1;
    char *buf = malloc(bufSize);
    if (!buf) {
        return;
    }

    size_t used = 0;
    for (int i = 0; i < n; ++i) {
        int written = snprintf(buf + used, bufSize - used, i == 0 ? "%g" : " %g", points[i]);
        if (written < 0) {
            free(buf);
            return;
        }

        if ((size_t)written >= bufSize - used) {
            size_t newSize = used + (size_t)written + 1;
            char *newBuf = realloc(buf, newSize);
            if (!newBuf) {
                free(buf);
                return;
            }
            buf = newBuf;
            bufSize = newSize;
            written = snprintf(buf + used, bufSize - used, i == 0 ? "%g" : " %g", points[i]);
            if (written < 0 || (size_t)written >= bufSize - used) {
                free(buf);
                return;
            }
        }

        used += (size_t)written;
    }

    setAttributeAndRememberPointersEzxml(h->xml, XML_ATTR_POINTSY, buf, h->ssp);
    free(buf);
}
