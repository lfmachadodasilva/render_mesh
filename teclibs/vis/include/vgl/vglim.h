#ifndef VGL_IM_H
#define VGL_IM_H

#ifndef VGLIM_DLL
# ifndef TEC_DLL
#  define VGLIMAPI
# else
#  define VGLIMAPI __declspec(dllimport)
# endif
#else
# define VGLIMAPI __declspec(dllexport)
#endif

#include <vgl/hnd/videowriter.h>

class VglCanvas;
class VglSubCanvas;

/**
 * Returns true if 'savecanvas', 'savesubcanvas' and 'savecanvasimageseq' support
 * a resolution different than the resolution of 'canvas'.
 * Returns false otherwise.
 *
 * OBS: The canvas OpenGL context must be active.
 */
VGLIMAPI bool vglim_supports_diff_resolution ();
VGLIMAPI bool vglim_savecanvas (const char *label, VglCanvas *canvas, int width, int height, const char *filename, const char *format);
VGLIMAPI bool vglim_savesubcanvas (const char *label, VglSubCanvas* subcanvas, int width, int height, const char *filename, const char *format);
/**
 * Exports the canvas image to a image which filename is given by
 * a sequence of images.
 * File name sequences are given by format 'filename_format', which
 * is used as a sprintf format parameter receiving one integer (%d).
 * Example: myfilename%d.png - will save sequence myfilename0.png,
 * myfilename1.png, and so on.
 *
 * Image is exported using width 'width' and height 'height',
 * saved using IM format 'format'.
 * 'label' specifies a string to appear before success or failure message.
 *
 * Returns true if successful, false otherwise.
 */
VGLIMAPI bool vglim_save_canvas_image_seq (const char* label,
                                           VglCanvas *canvas,
                                           int width,
                                           int height,
                                           const char *filename_format,
                                           const char *format);

#endif
