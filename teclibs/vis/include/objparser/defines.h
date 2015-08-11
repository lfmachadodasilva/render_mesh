#ifndef OBJPARSER_DEFINES_H
#define OBJPARSER_DEFINES_H

#ifndef OBJPARSER_DLL
# ifndef TEC_DLL
#  define OBJPARSERAPI
# else
#  define OBJPARSERAPI __declspec(dllimport)
# endif
#else
# define OBJPARSERAPI __declspec(dllexport)
#endif

#endif

