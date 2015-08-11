// Definitions
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef UTL_DEFINES_H
#define UTL_DEFINES_H

#ifndef UTL_DLL
# ifndef TEC_DLL
#  define UTL_API
#  define UTLH_API
# else
#  define UTL_API __declspec(dllimport)
#  define UTLH_API __declspec(dllexport)
# endif
#else
# define UTL_API __declspec(dllexport)
# define UTLH_API __declspec(dllexport)
#endif

#ifdef _MSC_VER
# define UTL_FORCE_INLINE  __forceinline
#else
# define UTL_FORCE_INLINE  inline
#endif

//* Unsigned types
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;

//* Callback function type
typedef void (*UtlFunction) (void*); 

#define UTL_TOL     1.0e-7f
#define UTL_PI      3.14159f

#endif
