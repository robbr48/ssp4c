#ifndef SSP4C_SSC_MAPPING_TRANSFORM_H
#define SSP4C_SSC_MAPPING_TRANSFORM_H

#include "ssp4c_public.h"
#include "ssp4c_common.h"

#ifdef __cplusplus
extern "C" {
#endif

SSP4C_DLLAPI sscMappingTransform ssp4c_ssc_mappingTransform_getType(sscMappingTransformHandle *h);
SSP4C_DLLAPI double ssp4c_ssc_mappingTransform_getFactor(sscMappingTransformHandle *h);
SSP4C_DLLAPI double ssp4c_ssc_mappingTransform_getOffset(sscMappingTransformHandle *h);
SSP4C_DLLAPI int ssp4c_ssc_mappingTransform_getNumberOfMapEntries(sscMappingTransformHandle *h);
SSP4C_DLLAPI sscMapEntryHandle *ssp4c_ssc_mappingTransform_getMapEntryByIndex(sscMappingTransformHandle *h, int i);

#ifdef __cplusplus
}
#endif

#endif // SSP4C_SSC_MAPPING_TRANSFORM_H
