// SG3DSLoader
// romano@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Jan 2003

#ifndef SG_3DSLOADER
#define SG_3DSLOADER

#ifndef SG3DS_DLL
# ifndef TEC_DLL
#  define SG3DSAPI
# else
#  define SG3DSAPI __declspec(dllimport)
# endif
#else
# define SG3DSAPI __declspec(dllexport)
#endif

class SGGroup;
class SGPLight;

SG3DSAPI SGGroup* sg3ds_loadfile (const char* name, const char* filename, const char* texture_dir=0, bool geometryonly=true, bool ignoretextures=false, bool sharevertices=true, bool shareindices=true);
SG3DSAPI void sg3ds_setfilter(int min, int mag, bool mipmap);

#endif

