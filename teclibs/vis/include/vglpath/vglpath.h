// fabraham@tecgraf.puc-rio.br
// May 2006
#ifndef VGL_VGLPATH_H
#define VGL_VGLPATH_H

#include "defines.h"

class VglCamera;

/**
 * Obtains camera parameters like:
 * - position
 * - field of view (Y)
 * - orientation (angle and rotation axis)
 */
VGLPATH_API void vglpath_get_params (VglCamera *camera, float *opx, float *opy, float *opz, float *ofovy, float *orangle, float *orx, float *ory, float *orz);
/**
 * Sets camera parameters:
 * - position
 * - field of view (Y)
 * - orientation (angle and rotation axis)
 */
VGLPATH_API void vglpath_set_params (VglCamera *camera, float px, float py, float pz, float fovy, float rangle, float rx, float ry, float rz);

#endif

