//* vglciup.h
// celes@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Feb 2003

#ifndef VGL_C_IUP_H
#define VGL_C_IUP_H

#include <vgl/vglc/vglc.h>

#include "iup.h"
#include "iupgl.h"

#ifndef VGLIUPAPI
# ifndef VGLIUP_DLL
#  ifndef TEC_DLL
#   define VGLIUPAPI
#  else
#   define VGLIUPAPI __declspec(dllimport)
#  endif
# else
#  define VGLIUPAPI __declspec(dllexport)
# endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

VGLIUPAPI VglCanvas* vglIupCanvas (Ihandle* handle);
VGLIUPAPI Ihandle* vglGetIupHandle (VglCanvas* vgl);

#ifdef __cplusplus
}
#endif

#endif
