#ifndef SSP4C_TYPES_H
#define SSP4C_TYPES_H

#include <stdbool.h>
#include <stdint.h>

// Types
typedef enum { sspVersionUnknown, sspVersion1, sspVersion2} sspVersion;
typedef struct sspHandle sspHandle;
typedef struct ssdHandle ssdHandle;
typedef struct ssdConnectorHandle ssdConnectorHandle;

#endif // SSP4C_TYPES_H
