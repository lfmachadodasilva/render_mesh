#ifndef SGOBJ_DEFINES_H
#define SGOBJ_DEFINES_H

#ifndef SGOBJ_DLL
# ifndef TEC_DLL
#  define SGOBJAPI
# else
#  define SGOBJAPI __declspec(dllimport)
# endif
#else
# define SGOBJAPI __declspec(dllexport)
#endif

#endif

