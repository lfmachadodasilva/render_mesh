// Vgl Definitions
// fabraham@tecgraf.puc-rio.br
// celes@tecgraf.puc-rio.br
// Feb 2003

#ifndef VGL_DEFINES_H
#define VGL_DEFINES_H

#define VGL_VERSION "2.0a"

#ifndef VGL_DLL
# ifndef TEC_DLL
#  define VGL_API
# else
#  define VGL_API __declspec(dllimport)
# endif
#else
# define VGL_API __declspec(dllexport)
#endif

#include <GL/glew.h>

#define VGL_TOL 1.0e-5f
#define VGL_PI  3.1415926f

//* Undef/uninitialize constant
#define VGL_NONE 0

//* Feedback mode
#define VGL_FEEDBACK_NONE  0
#define VGL_FEEDBACK_BOX   1
#define VGL_FEEDBACK_MODEL 2

//* Manipulation modes
#define VGL_TRANSLATION_1D    0
#define VGL_TRANSLATION_2D    1
#define VGL_RESIZE_1D         2
#define VGL_SCALE             3
#define VGL_UNIFORM_SCALE     4

//* Directions
#define VGL_X_AXIS 0
#define VGL_Y_AXIS 1
#define VGL_Z_AXIS 2

//* Idle repeat mode constants
#define VGL_NEVER         0
#define VGL_ONE_TIME      1
#define VGL_ONCE          VGL_ONE_TIME
#define VGL_UNTIL_EVENT   2
#define VGL_FOREVER       3

//* Some keys
#define VGL_KEY_ESC   27
//* Special keys 
#define VGL_KEY_UP        256
#define VGL_KEY_DOWN      257
#define VGL_KEY_LEFT      258
#define VGL_KEY_RIGHT     259
#define VGL_KEY_F1        261
#define VGL_KEY_F2        262
#define VGL_KEY_F3        263
#define VGL_KEY_F4        264
#define VGL_KEY_F5        265
#define VGL_KEY_F6        266
#define VGL_KEY_F7        267
#define VGL_KEY_F8        268
#define VGL_KEY_F9        269
#define VGL_KEY_F10       270
#define VGL_KEY_F11       271
#define VGL_KEY_F12       272
#define VGL_KEY_PAGE_UP   273
#define VGL_KEY_PAGE_DOWN 274
#define VGL_KEY_HOME      327
#define VGL_KEY_END       335
#define VGL_KEY_INSERT    338
#define VGL_KEY_DELETE    339

#define VGL_MAX_KEY   512

//* Camera eye constants
#define VGL_EYE_LEFT  -1
#define VGL_EYE_MONO   0
#define VGL_EYE_RIGHT  1

//* Camera autofit modes
#define VGL_FIT_SPHERE 1
#define VGL_FIT_2D     2
#define VGL_FIT_3D     VGL_FIT_SPHERE

//* Mouse buttons
#define VGL_BUTTON_LEFT   1
#define VGL_BUTTON_MIDDLE 2
#define VGL_BUTTON_RIGHT  4

//* Button/key state
#define VGL_RELEASE 0
#define VGL_PRESS   1

//* Frustum plane ids
#define VGL_PLANE_LEFT    0
#define VGL_PLANE_RIGHT   1
#define VGL_PLANE_BOTTOM  2
#define VGL_PLANE_TOP     3
#define VGL_PLANE_NEAR    4
#define VGL_PLANE_FAR     5

#ifdef __cplusplus
class VglSelectionHit;
#else
struct VglSelectionHit;
typedef struct VglSelectionHit VglSelectionHit;
#endif
//* Callback function types
typedef void (*VglFunction) (void *data); 
typedef void (*VglReshapeFunction) (int w, int h,void *data); 
typedef void (*VglKeyboardFunction) (int k, int st, float x, float y, void *data);
typedef void (*VglMouseButtonFunction) (int bt, int st, float x, float y, void *data);
typedef void (*VglMouseMotionFunction) (int bt, float x, float y, void *data);
typedef void (*VglMouseEntryFunction) (int st, void *data);
typedef void (*VglMouseWheelFunction) (float delta, float x, float y, void *data);
/**
 * 'hits' is an array with 'n' selection hits.
 */
typedef void (*VglProcessFunction) (VglSelectionHit *hits, int n, void *data);
/**
 * Selection function data type.
 */  
typedef void (*VglSelectionFunction)(void* data);

#endif
