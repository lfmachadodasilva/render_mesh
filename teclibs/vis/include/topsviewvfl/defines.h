#ifndef TPVVFL_DEFINES_H
#define TPVVFL_DEFINES_H

#ifndef TOPSVIEWVFL_DLL
# ifndef TEC_DLL
#  define TPVVFL_API
#  define TPVVFLH_API
# else
#  define TPVVFL_API __declspec(dllimport)
#  define TPVVFLH_API __declspec(dllexport)
# endif
#else
# define TPVVFL_API __declspec(dllexport)
# define TPVVFLH_API __declspec(dllexport)
#endif

#endif // TPVVFL_DEFINES_H
