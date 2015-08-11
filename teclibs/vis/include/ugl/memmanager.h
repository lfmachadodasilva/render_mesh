// RAM and VRAM memory manager
// fabraham@tecgraf.puc-rio.br
// vbarata@tecgraf.puc-rio.br
// Apr 2005 - Jul 2007

#ifndef UGL_MEMMANAGER_H
#define UGL_MEMMANAGER_H

#include "defines.h"
#include "uglmem.h"

UGL_API void ugl_setCreateBO (Mem mem, bool state);
UGL_API void ugl_setFreeAfterBO (Mem mem, bool state);
UGL_API void ugl_setUpdateBO (Mem mem, bool state);
UGL_API void ugl_setFeedbackIndex (Mem mem, unsigned int index);
UGL_API bool ugl_getCreateBO (Mem mem);
UGL_API bool ugl_getFreeAfterBO (Mem mem);
UGL_API bool ugl_getUpdateBO (Mem mem);
UGL_API unsigned int ugl_getFeedbackIndex (Mem mem);
UGL_API Mem ugl_create (int type = 0, int accessHint = -1, int timeHint = -1);
UGL_API void ugl_setGrowRate (Mem mem, float rate);
UGL_API bool ugl_setMemValues (Mem mem, const void *values, size_t base = 0, size_t size = 0);
UGL_API bool ugl_setBOValues (Mem mem, const void *values, size_t base = 0, size_t size = 0);
UGL_API void ugl_flagMemChanged (Mem mem);
UGL_API void ugl_flagBOChanged (Mem mem);
UGL_API void ugl_setBO (Mem mem, int type = -1, int accessHint = -1, int timeHint = -1);
UGL_API float ugl_getGrowRate (Mem mem);
UGL_API void* ugl_getBuffer (Mem mem);
UGL_API void* ugl_getGLPointer (Mem mem);
UGL_API size_t ugl_getMemSize (Mem mem);
UGL_API size_t ugl_getMemMaxSize (Mem mem);
UGL_API size_t ugl_getBOSize (Mem mem);
UGL_API size_t ugl_getBOMaxSize (Mem mem);
UGL_API GLuint ugl_getBOId (Mem mem);
UGL_API int ugl_getBOType (Mem mem);
UGL_API int ugl_getBOTimeHint (Mem mem);
UGL_API int ugl_getBOAccessHint (Mem mem);
UGL_API bool ugl_isMemUpdated (Mem mem);
UGL_API bool ugl_isBOUpdated (Mem mem);
UGL_API void* ugl_mapBO (Mem mem, int accessType);
UGL_API bool ugl_unmapBO (Mem mem, bool unbind = true);
UGL_API bool ugl_copy (Mem dst, Mem src);
UGL_API void ugl_destroy (Mem mem);
UGL_API bool ugl_isInCpu (Mem mem);
UGL_API bool ugl_isInGpu (Mem mem);
UGL_API void ugl_freeCpu (Mem mem);
UGL_API void ugl_freeGpu (Mem mem);
/**
 * Obtains the total number of bytes occupied by the buffer (CPU and GPU).
 */
UGL_API size_t ugl_getTotalSize (Mem mem);
/*
 * - For resize() and reserve(), using (copyFromCpu/copyFromGpu) forces a size match with the other (cpu/gpu)
 *   array size, and also makes the entire array be automatically copied between cpu/gpu.
 * - resize() and reserve() preserve the array's contents after memory reallocation. This can be
 *   specially slow on gpu, since it involves a manual copy of the entire array. If a clean reallocation
 *   is desired, the array should first be freed.
 * - For copy(), using both (base=0) and (size=0) makes a full array copy between cpu/gpu, and also
 *   forces both arrays to end up with the same size, even if the destination array has to shrink.
 *   The reserved size, however, will only grow as required, never shrink.
 */

UGL_API bool ugl_resizeCpu (Mem mem, size_t size = 0, bool exactSize = false, bool copyFromGpu = false, bool unbind = true);
UGL_API bool ugl_reserveCpu (Mem mem, size_t size = 0, bool exactSize = false, bool copyFromGpu = false, bool unbind = true);
UGL_API bool ugl_resizeGpu (Mem mem, size_t boSize = 0, bool exactSize = false, bool copyFromCpu = false, bool unbind = true);
UGL_API bool ugl_reserveGpu (Mem mem, size_t boSize = 0, bool exactSize = false, bool copyFromCpu = false, bool unbind = true);
UGL_API bool ugl_copyToCpu (Mem mem, GLintptrARB base = 0, GLsizeiptrARB size = 0, bool unbind = true);
UGL_API bool ugl_copyToGpu (Mem mem, GLintptrARB base = 0, GLsizeiptrARB size = 0, bool unbind = true);
UGL_API void ugl_getBOValues (Mem mem, void* buffer, GLintptrARB base = 0, GLsizeiptrARB size = 0, bool unbind = true);
UGL_API void ugl_bindGpu (Mem mem);
UGL_API void ugl_unbindGpu (Mem mem);
UGL_API void ugl_bindGpuFeedback (Mem mem, GLintptrARB offset = 0, GLsizeiptrARB size = 0);
UGL_API void ugl_unbindGpuFeedback (Mem mem);

#endif
