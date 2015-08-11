// coverage.h
// fabraham@tecgraf.puc-rio.br
// Nov 2008

#ifndef UGL_COVERAGE_H
#define UGL_COVERAGE_H

#include <GL/glew.h>
#include "defines.h"
#include <stdio.h>
#include <alg/vector.h>
#include <alg/matrix.h>

/**
 * Computes the rectangle that contains the projection of an array of vertices.
 * 'vertices' must be an array of 'numvertices'.
 * 'projmodelview' is the concatenation of the projection, view and model matrices.
 * 'viewport' is the window view port, in pixels. If NULL, it is obtained from OpenGL.
 *
 * If any of the given vertices are inside the screen, 'true' is returned and the rectangle
 * area is returned on *ox, *oy, *ow and *oh. 'false' is returned otherwise.
 */
bool UGLComputeScreenCoverage (int numvertices,
                               const AlgVector *vertices,
                               const AlgMatrix *projmodelview,
                               int* ox,
                               int* oy,
                               int* ow,
                               int* oh,
                               const GLint* viewport = NULL);

#endif // UGL_COVERAGE_H
