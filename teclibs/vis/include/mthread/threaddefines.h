//* defines.h
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Mai 2009

#ifndef MTHREAD_DEFINES_H
#define MTHREAD_DEFINES_H

//-----------------//
// DLL Definitions //
//-----------------//

#ifndef MTHREAD_DLL
# ifndef TEC_DLL
#  define MTHREAD_API
#  define MTHREADH_API
# else
#  define MTHREAD_API __declspec(dllimport)
#  define MTHREADH_API __declspec(dllexport)
# endif
#else
# define MTHREAD_API __declspec(dllexport)
# define MTHREADH_API __declspec(dllexport)
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

#define MTHREAD_USE_POSIX
//#define MTHREAD_USE_JAVA
//#define MTHREAD_USE_WIN

//----------------------//
// Internal Definitions //
//----------------------//

// Reverting to Posix in case something is wrong

#if !defined _WIN32 
# define MTHREAD_FORCE_POSIX
#elif defined MTHREAD_USE_POSIX
# define MTHREAD_FORCE_POSIX
#elif defined MTHREAD_USE_WIN && defined MTHREAD_USE_JAVA
# define MTHREAD_FORCE_POSIX
#elif !defined MTHREAD_USE_WIN && !defined MTHREAD_USE_JAVA
# define MTHREAD_FORCE_POSIX
#endif

#ifdef MTHREAD_FORCE_POSIX
# undef MTHREAD_FORCE_POSIX
# undef MTHREAD_USE_WIN
# undef MTHREAD_USE_JAVA
# undef MTHREAD_USE_POSIX
# define MTHREAD_USE_POSIX
#endif

#endif // MTHREAD_DEFINES_H
