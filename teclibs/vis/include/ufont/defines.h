// Definitions
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Jul 2002

#ifndef UFONT_DEFINES_H
#define UFONT_DEFINES_H

#ifndef UFONT_DLL
# ifndef TEC_DLL
#  define UFONT_API
# else
#  define UFONT_API __declspec(dllimport)
# endif
#else
# define UFONT_API __declspec(dllexport)
#endif

#include <GL/glew.h>

#define UFONT_UTF8STRING_PREFIX "UTF8STRING: "

#endif

