// Image utils for OpenGL
// fabraham@tecgraf.puc-rio.br
// Jun 2005
#ifndef UGL_IMAGE_H
#define UGL_IMAGE_H

#include "defines.h"
#include "uglim.h"

class UGLTexture;

/**
 * Image utils for OpenGL.
 * 
 * This module implements some utilities to read and write images from and to images, respectively.
 * Functions are available to do operations:
 * - in and out of texture memory.
 * - in and out of the framebuffer.
 * - color, depth, stencil and other buffers. (currently, only color/depth).
 *
 * These modules use the IM toolkit (http://www.tecgraf.puc-rio.br/im) as the low level handler of different file formats, data sources and sinks.
 * Some other utilities are available to use in conjunction with IM:
 * - error debugging
 */

/**
 * prints the IM error, if any. Appends the suffix 'label' to the message (useful to distinguish which of your modules failed).
 */
UGLIMAPI bool uglim_print_im_error (const char *label, int error);
UGLIMAPI bool uglim_write_rgb_image (const char *label, const char *filename, const char *format, int width, int height, const void *buffer);
UGLIMAPI bool uglim_write_rgba_image (const char *label, const char *filename, const char *format, int width, int height, const void *buffer);
UGLIMAPI bool uglim_write_depth_image (const char *label, const char *filename, const char *format, int width, int height, unsigned int *buffer);
UGLIMAPI bool uglim_write_screen_tile (const char *label, const char *filename, const char *format, int x, int y, int width, int height);
UGLIMAPI bool uglim_write_alpha_tile (const char *label, const char *filename, const char *format, int x, int y, int w, int h);
UGLIMAPI bool uglim_write_depth_tile (const char *label, const char *filename, const char *format, int x, int y, int width, int height);
UGLIMAPI bool uglim_write_screen (const char *label, const char *filename, const char *format);
UGLIMAPI bool uglim_write_screen_alpha (const char *label, const char *filename, const char *format);
UGLIMAPI bool uglim_write_screen_depth(const char *label, const char *filename, const char *format, bool normalized=true);
UGLIMAPI bool uglim_setrgbadataub (UGLTexture *texture, unsigned char *data, bool isopaque=true);
UGLIMAPI bool uglim_setrgbadataub (UGLTexture *texture, unsigned char *red, unsigned char *green, unsigned char *blue, unsigned char *alpha=0, bool isopaque = true);
UGLIMAPI bool uglim_setrgbadataf(UGLTexture *texture, float *red, float *green, float *blue, float *alpha=0);
/**
 * 'takeownership' specifies if the data pointer can be used directly. if true, memory must have been allocated with m/calloc.
 */
UGLIMAPI bool uglim_setdepthdata (UGLTexture *texture, int width, int height, void* data, bool takeownership=false);
/**
 * Specifies a path to be appended as a prefix to the filename specified on the
 * texture loading functions.
 */
UGLIMAPI void uglim_set_texture_path (const char *path);
UGLIMAPI void uglim_reset_texture_path (void);
/**
 * Requires an active OpenGL state.
 */
UGLIMAPI bool uglim_get_image_dimensions (const char *imagefile, int *width, int *height);
UGLIMAPI bool uglim_load_from_image (UGLTexture *texture, const char *colorfile, const char* alphafile=0, bool npot = false);
/**
 * Adds print messages for image loading. Set with 'true' to enable, 'false' to disable.
 */
UGLIMAPI void uglim_set_verbose (bool v);

#endif
