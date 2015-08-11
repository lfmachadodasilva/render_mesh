// ugl.h
// fabraham@tecgraf.puc-rio.br
// Sep 2007

#ifndef UGL_H
#define UGL_H

#ifdef GLEW_MX
# ifdef WIN32
#  include <windows.h>
# endif
# include <GL/glew.h>
#endif
#include "defines.h"
#include "error.h"

//class UGLArray;
//class UGLTriangleSet;
//class UGLQuadSet;

/**
 * Obtains the OpenGL version in float format.
 *
 * Ex: 1.5 for OpenGL 1.5, etc.
 *
 * Must be called within a valid GL context.
 */
UGL_API float ugl_getglversion();
/**
 * Obtains the OpenGL version in string format.
 *
 * Must be called within a valid GL context.
 */
UGL_API const char *ugl_getglversionstring();
/**
 * Verifies if vertical synchronization configuration is possible.
 * Notes:
 * - the OpenGL context must be active during this call.
 * - ugl_init() must have been successfully called on this OpenGL context.
 */
UGL_API bool ugl_is_vsync_switch_possible ();
/**
 * Obtains the vertical synchronization flag.
 * Notes:
 * - ugl_is_vsync_switch_possible() must have returned true.
 * - the OpenGL context must be active during this call.
 * - ugl_init() must have been successfully called on this OpenGL context.
 */
UGL_API bool ugl_is_vsync_enabled ();
/**
 * Sets the vertical synchronization flag.
 * Notes:
 * - ugl_is_vsync_switch_possible() must have returned true.
 * - the OpenGL context must be active during this call.
 * - ugl_init() must have been successfully called on this OpenGL context.
 */
UGL_API void ugl_set_vsync_enabled (bool f);

#ifdef GLEW_MX
GLEWContext* glewGetContext ();
#endif

UGL_API bool ugl_init ();
UGL_API bool ugl_was_initialized ();
UGL_API bool ugl_supports_extension (const char* name);
/**
 * Returns the bitwise OR between:
 * GL_COLOR_BUFFER_BIT;
 * GL_DEPTH_BUFFER_BIT, if there is a depth buffer in the current OpenGL context;
 * GL_STENCIL_BUFFER_BIT, if there is a stencil buffer in the current OpenGL context.
 */
UGL_API unsigned int ugl_get_framebuffer_mode ();
/**
 * Returns true if information on GPU memory usage is available.
 * Must be called with an active OpenGL context.
 */
UGL_API bool ugl_gpu_mem_info_available ();
/**
 * Returns the total GPU memory size in KBytes.
 * Must be called with an active OpenGL context.
 * ugl_gpu_mem_info_available() must have returned true.
 */
UGL_API int ugl_gpu_mem_total ();
/**
 * Returns the currently available GPU memory in KBytes.
 * Must be called with an active OpenGL context.
 * ugl_gpu_mem_info_available() must have returned true.
 */
UGL_API int ugl_gpu_mem_free ();
/**
 * Returns the current GPU memory usage where 0.0 means 0% used and 1.0 means 100% used.
 * Must be called with an active OpenGL context.
 * ugl_gpu_mem_info_available() must have returned true.
 */
UGL_API float ugl_gpu_mem_usage ();
/**
 * Obtains an integer value from the active OpenGL context.
 */
UGL_API GLint ugl_get_int (GLenum e);
/*
UGL_API void ugl_reorder_mesh (UGLArray* vertices,
                               UGLArray* normals,
                               UGLArray* texcoords[8],
                               int num_tsets,
                               int num_qsets,
                               UGLTriangleSet** tsets,
                               UGLQuadSet** qsets);
*/

#endif
