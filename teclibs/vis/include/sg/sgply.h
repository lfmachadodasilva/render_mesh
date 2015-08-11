#ifndef SGPLY_H
#define SGPLY_H

#ifndef SGPLY_DLL
# ifndef TEC_DLL
#  define SGPLYAPI
# else
#  define SGPLYAPI __declspec(dllimport)
# endif
#else
# define SGPLYAPI __declspec(dllexport)
#endif

#endif

