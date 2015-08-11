// VglPath Definitions
// fabraham@tecgraf.puc-rio.br
// celes@tecgraf.puc-rio.br
// Feb 2003

#ifndef VGLPATH_DEFINES_H
#define VGLPATH_DEFINES_H

#ifndef VGLPATH_DLL
# ifndef TEC_DLL
#  define VGLPATH_API
# else
#  define VGLPATH_API __declspec(dllimport)
# endif
#else
# define VGLPATH_API __declspec(dllexport)
#endif

#endif  // VGLPATH_DEFINES_H

