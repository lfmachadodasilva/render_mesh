#ifndef SGSHADOW_H
#define SGSHADOW_H

#ifndef SGSHADOW_DLL
# ifndef TEC_DLL
#  define SGSHADOWAPI
# else
#  define SGSHADOWAPI __declspec(dllimport)
# endif
#else
# define SGSHADOWAPI __declspec(dllexport)
#endif

#include <GL/glew.h>
#include <sgshadow/shadowmap.h>
#include <sgshadow/shadowmapper.h>
#include <sgshadow/shadowupdater.h>
#include <sgshadow/shadowcaster.h>
#include <sgshadow/shadowprojector.h>

#endif
