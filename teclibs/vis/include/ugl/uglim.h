/**
  Image utility functions.
  Tecgraf/PUC-Rio
*/

#ifndef UGL_IM_H
#define UGL_IM_H

#ifdef UGLIM_DLL
#define UGLIMAPI __declspec(dllexport)
#else
#define UGLIMAPI
#endif

/** 
  Dumps the current color read buffer to a file.
  Format one of the format strigs supported by IM.
  Returns true on success, false otherwise.
*/
typedef void (*UGLIMRedrawFunc)(void* data);

#if 0
UGLIMAPI bool uglim_save_snapshot(const char *file, const char* format, int width, int height);
#else
UGLIMAPI bool uglim_save_snapshot(const char* label, const char *file, const char* format, int w, int h,
                                  UGLIMRedrawFunc redrawfunc, void* redrawdata=0);
#endif

/**
  Prints the current color read buffer.
  Returns true on success, false otherwise.
*/
#if 0
UGLIMAPI bool uglim_print_snapshot(int width, int height);
#else
UGLIMAPI bool uglim_print_snapshot(int width, int height, 
                                   UGLIMRedrawFunc redrawfunc, void* redrawdata=0);
#endif

/** 
  Copies the current color read buffer to the clipboard.
  Returns true on success, false otherwise.
*/
#if 0
UGLIMAPI bool uglim_copy_snapshot_to_clipboard(int width, int height);
#else
UGLIMAPI bool uglim_copy_snapshot_to_clipboard(int width, int height,
                                  UGLIMRedrawFunc redrawfunc, void* redrawdata=0);
#endif

#endif

