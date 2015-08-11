#ifndef SGTERRAIN_H
#define SGTERRAIN_H

#ifndef SGTERRAIN_DLL
# ifndef TEC_DLL
#  define SGTERRAINAPI
# else
#  define SGTERRAINAPI __declspec(dllimport)
# endif
#else
# define SGTERRAINAPI __declspec(dllexport)
#endif

#endif

