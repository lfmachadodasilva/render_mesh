#ifndef UGL_ERROR_H
#define UGL_ERROR_H

#include "defines.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _UGLContextState UGLContextState;

UGL_API int ugl_printglerrorline (const char *label, const char *file, int line);
UGL_API int ugl_printglerrormsg (const char *label, const char *msg);
UGL_API void ugl_printglstacksstatus (const char *label);
UGL_API const char* ugl_errorstring (GLenum errCode);

#define ugl_printglerror(l) ugl_printglerrorline((l),__FILE__,__LINE__)

/**
 * Creates and returns a copy of the state of the currently 
 * active OpenGL context.
 *
 * NOTE: This function is work in progress... Currently, only a small 
 * subset of the complete OpenGL state is queried. It is expected that
 * new state variables are added in the future. 
 */
UGL_API UGLContextState* ugl_getglcontextstate ();

/**
 * Releases a UGLContextState object.
 */
UGL_API void ugl_freeglcontextstate (UGLContextState *state);

/**
 * Asserts that the state of the currently active OpenGL context is identical
 * to the given input state. If assertion fails, 'msg' is displayed and the 
 * function returns 0. Otherwise, 1 is returned.
 */
UGL_API int ugl_assertglcontextstate (const UGLContextState *state, const char *msg);
  
#ifdef __cplusplus
}
#endif

#endif
