#ifndef UTL_MEMMANAGER_H_OLD
#define UTL_MEMMANAGER_H_OLD

#include <ugl/uglmem.h>

#define UTL_MEM_TYPE_RAM UGL_MEM_TYPE_CPU
#define UTL_MEM_TYPE_VERTEX UGL_MEM_TYPE_VERTEX
#define UTL_MEM_TYPE_INDEX UGL_MEM_TYPE_INDEX
#define UTL_MEM_TYPE_PIXEL_UNPACK UGL_MEM_TYPE_PIXEL_UNPACK
#define UTL_MEM_TYPE_PIXEL_PACK UGL_MEM_TYPE_PIXEL_PACK
#define UTL_MEM_TYPE_MAX UGL_MEM_TYPE_MAX

//#define utl_create ugl_create
//#define utl_destroy ugl_destroy
//#define utl_resize ugl_resize
//#define utl_getsize ugl_getsize
//#define utl_setvalues ugl_setvalues
#define utl_memmanager_init ugl_memmanager_init
#define utl_setglobalfreeaftervbo ugl_setAutoFreeAfterBO
#define utl_getglobalfreeaftervbo ugl_getAutoFreeAfterBO
#define utl_setstaticdefault ugl_setstaticdefault
#define utl_getstaticdefault ugl_getstaticdefault
//#define utl_setfreeaftervbo ugl_setfreeaftervbo
//#define utl_getfreeaftervbo ugl_getfreeaftervbo
#define utl_gettotalbytes ugl_getTotalBytes
//#define utl_setstatic ugl_setstatic
//#define utl_isstatic ugl_isstatic
//#define utl_copy ugl_copy
//#define utl_hasvbo ugl_hasvbo
//#define utl_tovbo ugl_tovbo
//#define utl_bindvbo ugl_bindvbo
//#define utl_getbuffer ugl_getbuffer
//#define utl_getpointer ugl_getpointer
//#define utl_isinram ugl_isinram

#endif
