#ifndef _SYS_CDEFS_H
#define _SYS_CDEFS_H 1

#define __cozyos_libc 1

#endif


// Helpers to do make C headers work for C++ too
#ifdef __cplusplus
#define __BEGIN_EXTERN_C extern "C" {
#else
#define __BEGIN_EXTERN_C 
#endif

#ifdef __cplusplus
#define __END_EXTERN_C }
#else
#define __END_EXTERN_C 
#endif
