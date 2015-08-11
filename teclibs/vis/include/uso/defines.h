// Definitions
// fabraham@tecgraf.puc-rio.br
// Nov 2006

#ifndef USO_DEFINES_H
#define USO_DEFINES_H

#ifndef USO_DLL
# ifndef TEC_DLL
#  define USO_API
# else
#  define USO_API __declspec(dllimport)
# endif
#else
# define USO_API __declspec(dllexport)
#endif

#endif
