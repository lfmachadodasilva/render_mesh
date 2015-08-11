// matrix.h
// Interpolation utilities.
// fabraham@tecgraf.puc-rio.br
// Nov 2009
#ifndef ALG_INTERP_H
#define ALG_INTERP_H

/**
 * Computes the barycentric coordinates of point 'newvcoords'
 * given a tetrahedron with coords vcoords[4][3].
 * Values are returned in 'lambdas'.
 */
bool AlgComputeBarycentricCoords (float** vcoords,
                                  float   newvcoords[3],
                                  float   lambdas[4]);

#endif

