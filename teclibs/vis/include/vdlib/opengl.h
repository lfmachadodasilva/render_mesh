/**
*	Initialize OpenGL support and extensions
*	author: Paulo Ivson <psantos@tecgraf.puc-rio.br>
*	date:   10-Mar-2008
*/
#ifndef _VDLIB_OPENGL_H_
#define _VDLIB_OPENGL_H_

#ifdef _WIN32
# include <windows.h>
#endif
#include <GL/glew.h>

#include <vdlib/common.h>

namespace vdlib {

class OpenGL
{
public:
	static bool init();
};

} // namespace vdlib

#endif // _VDLIB_OPENGL_H_
