#ifndef SSP4C_COMMON_H
#define SSP4C_COMMON_H

#ifndef _WIN32
#define _strdup strdup
#endif

#define UNUSED(x) (void)(x);


#ifdef _WIN32
#if defined(SSP4C_STATIC)
#define SSP4C_DLLAPI
#elif defined(SSP4C_DLLEXPORT)
#define SSP4C_DLLAPI __declspec(dllexport)
#else
#define SSP4C_DLLAPI __declspec(dllimport)
#endif
#else
#define SSP4C_DLLAPI
#endif

#endif // SSP4C_COMMON_H
