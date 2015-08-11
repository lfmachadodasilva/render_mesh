// RAM and VRAM memory manager
// fabraham@tecgraf.puc-rio.br
// vbarata@tecgraf.puc-rio.br
// Apr 2005 - Jul 2007

#ifndef UGL_MEM_EXPORTS_H
#define UGL_MEM_EXPORTS_H

#include "defines.h"
#include <stdlib.h>

typedef struct _Mem* Mem;

UGL_API void ugl_memmanager_init ();
UGL_API size_t ugl_getTotalBytes (int type);

UGL_API void ugl_setstaticdefault (bool f);
UGL_API bool ugl_getstaticdefault ();

UGL_API void ugl_setAutoCreateBO (bool state);
UGL_API void ugl_setAutoFreeAfterBO (bool state);
UGL_API void ugl_setAutoUpdateBO (bool state);
UGL_API void ugl_setAutoAccessHint (int accessHint);
UGL_API void ugl_setAutoTimeHint (int timeHint);
UGL_API void ugl_setUseMapToCopy (bool state);

UGL_API bool ugl_getAutoCreateBO (void);
UGL_API bool ugl_getAutoFreeAfterBO (void);
UGL_API bool ugl_getAutoUpdateBO (void);
UGL_API int ugl_getAutoAccessHint (void);
UGL_API int ugl_getAutoTimeHint (void);
UGL_API bool ugl_getUseMapToCopy (void);

#endif

