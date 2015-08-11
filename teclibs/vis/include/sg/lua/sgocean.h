#ifndef SGOCEAN_H
#define SGOCEAN_H

#ifndef SGOCEAN_DLL
# ifndef TEC_DLL
#  define SGOCEANAPI
# else
#  define SGOCEANAPI __declspec(dllimport)
# endif
#else
# define SGOCEANAPI __declspec(dllexport)
#endif

#endif
