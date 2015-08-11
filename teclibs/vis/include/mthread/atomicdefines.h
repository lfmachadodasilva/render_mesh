//* atomicdefines.h
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Mai 2009

#ifndef ATOMIC_DEFINES_H
#define ATOMIC_DEFINES_H

//-----------------//
// DLL Definitions //
//-----------------//

#ifndef ATOMIC_DLL
# ifndef TEC_DLL
#  define ATOMIC_API
#  define ATOMICH_API
# else
#  define ATOMIC_API __declspec(dllimport)
#  define ATOMICH_API __declspec(dllexport)
# endif
#else
# define ATOMIC_API __declspec(dllexport)
# define ATOMICH_API __declspec(dllexport)
#endif

//----------------------//
// Standard Definitions //
//----------------------//

#ifndef NULL
# ifdef __cplusplus
#  define NULL    0
# else
#  define NULL    ((void *)0)
# endif
#endif

//---------------------//
// Compilation Options //
//---------------------//

#define ATOMIC_FORCE_MUTEXES

//----------------------//
// Internal Definitions //
//----------------------//

#undef ATOMIC_USE_MUTEXES

#endif // ATOMIC_DEFINES_H
