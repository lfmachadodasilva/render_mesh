// Asynchronous loading of textures.
// fabraham@tecgraf.puc-rio.br
// Aug 2008
#ifndef UGL_IM_ASYNC_H
#define UGL_IM_ASYNC_H

#ifndef UGLIMASYNC_DLL
# ifndef TEC_DLL
#  define UGLIMASYNCAPI
# else
#  define UGLIMASYNCAPI __declspec(dllimport)
# endif
#else
# define UGLIMASYNCAPI __declspec(dllexport)
#endif

#include <stdio.h>

class UGLTexture;

/**
 * Initializes the asynchronous texture loading system.
 * Returns true if successful, false otherwise.
 */
UGLIMASYNCAPI bool uglimasync_init ();
/**
 * Finalizes the asynchronous texture loading system.
 */
UGLIMASYNCAPI void uglimasync_close ();
/**
 * Requests the asynchronous loading of a texture with
 * RGB or RGBA file 'colorfile' and alpha file 'alphafile' (optional).
 * The priority value specifies the priority of the loading of this texture
 * in comparison to other textures.
 * A negative priority will force the immediate loading of the texture.
 */ 
UGLIMASYNCAPI bool uglimasync_request_load_from_image (UGLTexture *texture, const char *colorfile, const char* alphafile=NULL, int priority=0);
/**
 * Requests the use of a texture.
 * If not already loaded, will force the immediate loading of it.
 */
UGLIMASYNCAPI bool uglimasync_synchronize (UGLTexture *texture);
/**
 * Destroys a texture.
 * Returns true if the texture was successfully destroyed.
 * Note: returns false if the texture was not created by uglimasync.
 */
UGLIMASYNCAPI bool uglimasync_destroy (UGLTexture *texture);

#endif

