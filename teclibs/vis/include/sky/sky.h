#ifndef VISSKY_H
#define VISSKY_H

#ifndef SKY_DLL
# ifndef TEC_DLL
#  define SKY_API
# else
#  define SKY_API __declspec(dllimport)
# endif
#else
# define SKY_API __declspec(dllexport)
#endif

#include <GL/glew.h>

class SkyAstro;
class SkyBackground;
class SkyClouds;
class SkyEnvironment;
class SkyEnvironmentFactory;
class SkyEnvironmentsTransition;
class SkyStars;
class UtlTexture;

#endif
