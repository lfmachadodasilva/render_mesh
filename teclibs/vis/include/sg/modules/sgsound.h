#ifndef SGSOUND_H
#define SGSOUND_H

#ifndef SGSOUND_DLL
# ifndef TEC_DLL
#  define SGSOUNDAPI
# else
#  define SGSOUNDAPI __declspec(dllimport)
# endif
#else
# define SGSOUNDAPI __declspec(dllexport)
#endif

#include <sg/eng/soundmanager.h>

#endif
