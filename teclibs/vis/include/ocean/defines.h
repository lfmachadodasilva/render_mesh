#ifndef OCEAN_DEFINES_H
#define OCEAN_DEFINES_H

#ifdef OCEAN_DLL
 #define OCEAN_API __declspec(dllexport)
#else
 #define OCEAN_API
#endif

#include <GL/glew.h>

#endif
