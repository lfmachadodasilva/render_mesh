#ifndef SHADER_CG_DEFINES_H
#define SHADER_CG_DEFINES_H

#ifndef SHADERCG_DLL
# ifndef TEC_DLL
#  define SHADERCGAPI
# else
#  define SHADERCGAPI __declspec(dllimport)
# endif
#else
# define SHADERCGAPI __declspec(dllexport)
#endif

#endif
