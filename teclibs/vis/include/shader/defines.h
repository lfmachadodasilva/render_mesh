#ifndef SHADER_DEFINES_H
#define SHADER_DEFINES_H

#ifndef SHADER_DLL
# ifndef TEC_DLL
#  define SHADER_API
# else
#  define SHADER_API __declspec(dllimport)
# endif
#else
# define SHADER_API __declspec(dllexport)
#endif

#endif
