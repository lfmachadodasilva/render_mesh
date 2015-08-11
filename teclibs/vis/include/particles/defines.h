
#ifndef PARTICLES_DEFINES_H
#define PARTICLES_DEFINES_H

#ifndef PARTICLES_DLL
# ifndef TEC_DLL
#  define PARTICLES_API
#  define PARTICLESH_API
# else
#  define PARTICLES_API __declspec(dllimport)
#  define PARTICLESH_API __declspec(dllexport)
# endif
#else
# define PARTICLES_API __declspec(dllexport)
# define PARTICLESH_API __declspec(dllexport)
#endif

#endif
