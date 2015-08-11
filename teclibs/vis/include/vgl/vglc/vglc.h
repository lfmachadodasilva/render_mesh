//* vglc.h
// celes@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Feb 2003

#ifndef VGL_C_H
#define VGL_C_H

#include <vgl/defines.h>
#include <stdio.h>

// Interactive mode values
#define VGL_DUMMY         0  // no interception
#define VGL_MANIP         1  // direct manipulation
#define VGL_SINGLE_MANIP  2  // single direct manipulation
#define VGL_ZOOM          3  // window zooming
#define VGL_SINGLE_ZOOM   4  // single window zooming
#define VGL_NAVIG         5  // navig through
#define VGL_PICK          6  // pick

#ifdef __cplusplus
extern "C" {
class VglCanvas;
class VglCamera;
class VglFrustum;
class VglSelectionHit;
#else
struct VglCanvas;
struct VglCamera;
struct VglFrustum;
typedef struct VglCanvas VglCanvas;
typedef struct VglCamera VglCamera;
typedef struct VglFrustum VglFrustum;
#endif

/**
 * Gets the canvas' camera object.
 * \param vgl Canvas object.
 * \return Camera object associated with the specified canvas.
 */
VGL_API VglCamera* vglGetCamera (VglCanvas* vgl);
VGL_API void vglDestroyCanvas (VglCanvas* vgl);

//////////////////////////////////////// Mode functions 
VGL_API void vglSetItrMode (VglCanvas* vgl, int mode);
VGL_API int vglGetItrMode (VglCanvas* vgl);
VGL_API void vglSetFbkMode (VglCanvas* vgl, int mode);
VGL_API void vglSetNavigVelocity (VglCanvas* vgl, float vel);
VGL_API void vglSetNavigAcceleration (VglCanvas* vgl, float accel);
VGL_API void vglSetNavigOnPlane (VglCanvas* vgl, int flag);
VGL_API void vglSetNavigCenterCursor (VglCanvas* vgl, int flag);
VGL_API void vglSetNavigDrawCursor (VglCanvas* vgl, int flag);
VGL_API int vglGetManipIsMoving (VglCanvas* vgl);
VGL_API void vglSetManipRotateAroundBoxCenter (VglCanvas *vgl, int flag);
VGL_API void vglSetManipYRotationAxis (VglCanvas* vgl, float nx, float ny, float nz);
VGL_API void vglSetNavigAnimated (VglCanvas* vgl, int flag);
VGL_API void vglSetManipAnimated (VglCanvas* vgl, int flag);
VGL_API void vglSetZoomAnimated (VglCanvas* vgl, int flag);

//////////////////////////////////////// Picking functions
/**
 * Sets the rendering function used for selection.
 * 'func' will be called to render the geometry, with 'data' as parameter.
 * It is expected that it pushes/pops names into the name stack.
 */
VGL_API void vglSetSelRenderFunc (VglCanvas* vgl, VglFunction func, void* data);
/**
 * Sets a function that will be called with the selection results.
 * 'func' will be called with 'data' as parameter.
 * 
 * The function receives an array with the selection hits and
 * the number of hits in the array.
 */
VGL_API void vglSetSelProcessFunc (VglCanvas* vgl, VglProcessFunction func, void *data);
/**
 * Specifies the selection buffer size (default=512 entries).
 */
VGL_API void vglSetSelBufferSize (VglCanvas *vgl, int size);
/**
 * Obtains the 'x' and 'y' position of the last mouse pick and stores them in
 * 'ox' and 'oy'.
 */
VGL_API void vglSelHitsGetPickedXY (VglCanvas *vgl, float *ox, float *oy);
/**
 * Given all selection hits 'hits', obtain the number of names in selection
 * hit 'whichhit'.
 * 'whichhit' is a 0-based index.
 */
VGL_API int vglSelHitGetNumNames (VglSelectionHit* hits, int whichhit);
/**
 * Given all selection hits 'hits', obtain the name 'whichname' in selection
 * hit 'whichhit'.
 * 'whichhit' is a 0-based index.
 * 'whichname' is a 0-based index, whichname < numnames[whichhit]
 */
VGL_API unsigned int vglSelHitGetName (VglSelectionHit* hits, int whichhit, int whichname);
/**
 * Given all selection hits 'hits', obtain the minimum z of hit 'whichhit'.
 * 'whichhit' is a 0-based index.
 *
 * The hit's zmin ranges from 0 (near plane) to 1 (far plane).
 */
VGL_API float vglSelHitGetZMin (VglSelectionHit* hits, int whichhit);
/**
 * Given all selection hits 'hits', obtain the maximum z of hit 'whichhit'.
 * 'whichhit' is a 0-based index.
 *
 * The hit's zmax ranges from 0 (near plane) to 1 (far plane).
 */
VGL_API float vglSelHitGetZMax (VglSelectionHit* hits, int whichhit);

//////////////////////////////////////// Canvas functions 
 //* GUI functions
VGL_API void vglSwapBuffers (VglCanvas* vgl);
VGL_API void vglActivate (VglCanvas* vgl);

 //* Handler functions 
VGL_API void vglSetKeyboardFunc (VglCanvas* vgl, VglKeyboardFunction func, void* data);
VGL_API VglKeyboardFunction vglGetKeyboardFunc (VglCanvas* vgl);
VGL_API void vglSetMouseButtonFunc (VglCanvas* vgl, VglMouseButtonFunction func, void* data);
VGL_API VglMouseButtonFunction vglGetMouseButtonFunc (VglCanvas* vgl);
VGL_API void vglSetMouseMotionFunc (VglCanvas* vgl, VglMouseMotionFunction func, void* data);
VGL_API VglMouseMotionFunction vglGetMouseMotionFunc (VglCanvas* vgl);
VGL_API void vglSetMouseEntryFunc (VglCanvas* vgl, VglMouseEntryFunction, void* data);
VGL_API VglMouseEntryFunction vglGetMouseEntryFunc (VglCanvas* vgl);

int vglGetShift (VglCanvas *vgl);
int vglGetCtrl (VglCanvas *vgl);
int vglGetButton (VglCanvas *vgl);

 //* Idle functions
VGL_API int vglAddIdle (VglCanvas* vgl, VglFunction func, void* data, int repeat);
VGL_API int vglRemIdle (VglCanvas* vgl, VglFunction func, void* data);

 //* Draw functions
VGL_API void vglLoad (VglCanvas* vgl);
VGL_API void vglPostRedraw (VglCanvas* vgl);
VGL_API void vglRedraw (VglCanvas* vgl);
VGL_API void vglDrawItem (VglCanvas* vgl, VglFunction func, void* data);
VGL_API void vglSetReshapeFunc (VglCanvas* vgl, VglReshapeFunction reshape, void* data);
/**
 * Specifies a function to render the application's model.
 * 'data' is passed as parameter to 'redraw'.
 */
VGL_API void vglSetRedrawFunc (VglCanvas* vgl, VglFunction redraw, void* data);
/**
 * Specifies an optional function to finalize the rendering of the frame image.
 * 'data' is passed as parameter to 'endredraw'.
 *
 * This function is called, if specified, after the model redraw function.
 *
 * This is the place to draw color scales, axes, compasses, text messages, etc.
 */
VGL_API void vglSetEndRedrawFunc (VglCanvas* vgl, VglFunction endredraw, void* data);

//////////////////////////////////////// Camera functions 

 //* Camera setup functions
VGL_API void vglSetOrtho (VglCanvas* vgl, int flag);
VGL_API void vglSetPosition (VglCanvas* vgl, float x, float y, float z);
VGL_API void vglSetTarget (VglCanvas* vgl, float x, float y, float z);
VGL_API void vglSetUp (VglCanvas* vgl, float nx, float ny, float nz);
VGL_API void vglSetAngle (VglCanvas* vgl, float fovy);
VGL_API void vglSetAspect (VglCanvas* vgl, float aspect);
VGL_API void vglSetZPlanes (VglCanvas* vgl, float znear, float zfar);
VGL_API void vglSetBox (VglCanvas* vgl, float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
VGL_API void vglGetBox (VglCanvas* vgl, float *xmin, float *xmax, float *ymin, float *ymax, float *zmin, float *zmax);
VGL_API void vglSetAutoFit (VglCanvas* vgl, int flag);
VGL_API void vglSetDOP (VglCanvas* vgl, float x, float y, float z);
VGL_API void vglSetFitFactor (VglCanvas* vgl, float factor);
VGL_API void vglSetFitMode (VglCanvas *vgl, int mode);
VGL_API void vglEnableAutoFit (VglCanvas* vgl, float x, float y, float z, float factor);
VGL_API void vglDisableAutoFit (VglCanvas* vgl);

 //* Stereo functions
VGL_API void vglSetParallax (VglCanvas* vgl, float pmin, float pmax);
VGL_API void vglSetPhysicalScreen (VglCanvas* vgl, float w, float d);
VGL_API void vglSetZeroParallax (VglCanvas* vgl, float zps);
VGL_API void vglSetStereoDistortion(VglCanvas* vgl, int avoid);
VGL_API void vglSetCurrEye (VglCanvas* vgl, int eye);
VGL_API int  vglGetCurrEye (VglCanvas* vgl);
VGL_API float vglGetComputedZPS (VglCanvas* vgl);

 //* I/O functions
VGL_API int vglWriteParams (VglCanvas* vgl, FILE* fp);
VGL_API int vglReadParams (VglCanvas* vgl, FILE* fp);
VGL_API int vglSkipParams (VglCanvas* vgl, FILE* fp);
//VGL_API int vglWriteParams (VglCanvas* vgl, char* filename);
//VGL_API int vglReadParams (VglCanvas* vgl, char* filename);

 //* Utility functions 
VGL_API void vglGetModelview (VglCanvas *vgl, float mdl[16]);
VGL_API void vglGetProjection (VglCanvas *vgl, float prj[16]);
VGL_API void vglReset (VglCanvas* vgl);
VGL_API void vglCenterView (VglCanvas* vgl);
VGL_API void vglScaleView (VglCanvas* vgl, float sx, float sy, float sz);
VGL_API void vglFitView (VglCanvas* vgl);
VGL_API void vglZoomToBox (VglCanvas* vgl, float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
VGL_API void vglUndoZoom (VglCanvas* vgl);
VGL_API void vglRedoZoom (VglCanvas* vgl);
VGL_API void vglSetHeadlight (VglCanvas* vgl, int lightid);

VGL_API void vglGetUpdatedPosition (VglCanvas *vgl, float* ox, float* oy, float* oz);
VGL_API void vglGetUpdatedUp (VglCanvas *vgl, float* onx, float* ony, float* onz);
VGL_API float vglGetUpdatedAngle (VglCanvas *vgl);
VGL_API float vglGetUpdatedZNear (VglCanvas *vgl);
VGL_API float vglGetUpdatedZFar (VglCanvas *vgl);
VGL_API void vglGetUpdatedViewDir (VglCanvas *vgl, float* ovx, float* ovy, float* ovz);

 //* Validate function
VGL_API void vglSetValidateFunc (VglCanvas* vgl, int (*func)(void*), void* data);

//////////////////////////////////////// Frustum functions 

VGL_API VglFrustum* vglFrustumCreate  (const float* mv, const float* prj);
VGL_API void        vglFrustumDestroy (VglFrustum* f);

VGL_API void  vglFrustumUpdate      (VglFrustum* f, const float* mv, const float* prj);
VGL_API void  vglFrustumGetPlane    (VglFrustum* f, int id, float* a, float* b, float* c, float* d);
VGL_API void  vglFrustumGetEyePos   (VglFrustum* f, float* x, float* y, float* z);
VGL_API void  vglFrustumGetViewDir  (VglFrustum* f, float* x, float* y, float* z);
VGL_API void  vglFrustumGetViewUp   (VglFrustum* f, float* x, float* y, float* z);
VGL_API float vglFrustumGetNearDist (VglFrustum* f);
VGL_API float vglFrustumGetFarDist  (VglFrustum* f);
VGL_API float vglFrustumGetFovy     (VglFrustum* f);
VGL_API float vglFrustumGetFovx     (VglFrustum* f);

#ifdef __cplusplus
}
#endif

#endif
