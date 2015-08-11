#ifndef DS_DEFINES_H
#define DS_DEFINES_H

#ifdef TEC_DLL
# define DSAPI __declspec(dllexport)
#else
# define DSAPI
#endif

#ifdef _MSC_VER
# define DS_FORCE_INLINE  __forceinline
#else
# define DS_FORCE_INLINE  inline
#endif

#if defined(_MSC_VER) && _MSC_VER >= 1300 && !defined(MIDL_PASS)
# define DS_DEPRECATED __declspec(deprecated)
#elif defined(__GNUC__) &&  (__GNUC__ > 3 || (__GNUC__ == 3 && (__GNUC_MINOR__ > 1 || (__GNUC_MINOR__ == 1 && __GNUC_PATCHLEVEL__ >= 1))))
# define DS_DEPRECATED __attribute__((deprecated))
#else
# define DS_DEPRECATED
#endif

#endif

