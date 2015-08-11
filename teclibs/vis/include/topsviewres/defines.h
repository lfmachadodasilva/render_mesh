#ifndef TPVRES_DEFINES_H
#define TPVRES_DEFINES_H

#ifndef TOPSVIEWRES_DLL
# ifndef TEC_DLL
#  define TPVRES_API
# else
#  define TPVRES_API __declspec(dllimport)
# endif
#else
# define TPVRES_API __declspec(dllexport)
#endif

#endif

