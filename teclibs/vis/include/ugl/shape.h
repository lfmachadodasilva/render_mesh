#ifndef UGL_SHAPE_H
#define UGL_SHAPE_H

#include "defines.h"

class UGLArray;

struct UGLCylinder;
struct UGLSphere;

// Assumes that GL_NORMALIZE is Enabled
UGL_API UGLCylinder* ugl_createcylinder(int slices, int stacks);
/**
 * Specifies texture coordinates for each of the stack vertices.
 * (stacks+1) floats are passed on the 'texcoords' array.
 * Setting 'texcoords' == NULL cleans the current texcoords.
 */
UGL_API void ugl_setcyltexcoords (UGLCylinder* cylinder, const float* texcoords);
UGL_API void ugl_initcylinder(UGLCylinder* cylinder); //Builds Display List
UGL_API void ugl_drawcylinder(UGLCylinder* cylinder, float radius, float height); //Builds Display List (if not built before) and calls list
UGL_API void ugl_destroycylinder(UGLCylinder* cylinder);
/**
 * Creates a sphere object with 'slices' slices and 'stacks' stacks.
 */
UGL_API UGLSphere* ugl_createsphere (int slices, int stacks);
/**
 * Initializes a sphere object. OpenGL context must be active.
 */
UGL_API void ugl_initsphere (UGLSphere* sphere);
/**
 * Draws a sphere object with radius 'radius'.
 */
UGL_API void ugl_drawsphere (UGLSphere* sphere, float radius);
/**
 * Destroys the sphere object.
 */
UGL_API void ugl_destroysphere (UGLSphere* sphere);
/**
 * Computes position, normal and texture coordinates for a sphere with radius
 * 'radius', 'slices' slices and 'stacks' stacks.
 * It is assumed 'pos', 'nor' and 'tex' were correctly allocated
 * ((slices+1)*(stacks+1) vertices).
 */
UGL_API void ugl_computespherecoords (float radius,
                                      int slices,
                                      int stacks,
                                      UGLArray* pos,
                                      UGLArray* nor,
                                      UGLArray* tex);

#endif
