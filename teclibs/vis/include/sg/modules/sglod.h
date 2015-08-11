#ifndef SGLOD_H
#define SGLOD_H

#ifndef SGLOD_DLL
# ifndef TEC_DLL
#  define SGLODAPI
# else
#  define SGLODAPI __declspec(dllimport)
# endif
#else
# define SGLODAPI __declspec(dllexport)
#endif

SGLODAPI void sglod_open ();
SGLODAPI void sglod_close ();

#endif
