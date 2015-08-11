#ifndef SCI_DEFINES_H
#define SCI_DEFINES_H

#ifndef SCIUTILS_DLL
# ifndef TEC_DLL
#  define SCI_API
#  define SCIH_API
# else
#  define SCI_API __declspec(dllimport)
#  define SCIH_API __declspec(dllexport)
# endif
#else
# define SCI_API __declspec(dllexport)
# define SCIH_API __declspec(dllexport)
#endif

#endif
