#ifndef SGIM_H
#define SGIM_H

#ifndef SGIM_DLL
# ifndef TEC_DLL
#  define SGIMAPI
# else
#  define SGIMAPI __declspec(dllimport)
# endif
#else
# define SGIMAPI __declspec(dllexport)
#endif

class SGTexture;

SGIMAPI void sgim_set_texture_path (const char *path);
SGIMAPI void sgim_reset_texture_path (void);
SGIMAPI bool sgim_load_from_image (SGTexture *texture, const char *colorfile, const char* alphafile=0);

#endif

