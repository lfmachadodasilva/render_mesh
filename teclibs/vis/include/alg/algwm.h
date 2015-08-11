#ifndef ALG_WM_H
#define ALG_WM_H

#include "vector.h"
#include <float.h>

// TODO: mover para alg/box.h ?
struct AlgBox
{
  AlgVector center;
  AlgVector axes[3];
  float extents[3];
  AlgBox ()
  : center(FLT_MAX, FLT_MAX, FLT_MAX)
  {
  }
  AlgBox (const AlgBox& b)
  {
    center = b.center;
    axes[0] = b.axes[0];
    axes[1] = b.axes[1];
    axes[2] = b.axes[2];
    extents[0] = b.extents[0];
    extents[1] = b.extents[1];
    extents[2] = b.extents[2];
  }
  bool IsInitialized () const
  {
    return center.x != FLT_MAX &&
           center.y != FLT_MAX &&
           center.z != FLT_MAX;
  }
  bool operator == (const AlgBox& b) const
  {
    return center     == b.center     &&
           axes[0]    == b.axes[0]    &&
           axes[1]    == b.axes[1]    &&
           axes[2]    == b.axes[2]    &&
           extents[0] == b.extents[0] &&
           extents[1] == b.extents[1] &&
           extents[2] == b.extents[2];
  }
  bool operator != (const AlgBox& b) const
  {
    return !operator==(b);
  }
};

/**
 * Computes the minimum bounding sphere of 'numpoints' coordinates,
 * which are specified by 'vertices' (xyz, xyz, xyz, totalling 3*numpoints
 * floating point values).
 * Bounding sphere center is returned in *ocenter and radius is returned in *oradius.
 */
void AlgWMComputeBoundingSphere (int numpoints,
                                 const float* vertices,
                                 AlgVector* ocenter,
                                 float* oradius);
/**
 * Merges 'numspheres' bounding spheres, where center[s] is the center of the sphere
 * with index 's', 0 <= s < numspheres.
 * Resulting sphere is returned in *oresultcenter and *oresultradius.
 */
void AlgWMMergeBoundingSpheres (int numspheres,
                                const AlgVector* centers,
                                const float* radii,
                                AlgVector* oresultcenter,
                                float* oresultradius);
/**
 * Computes the minimum oriented bounding box of 'numpoints' coordinates,
 * which are specified by 'vertices' (xyz, xyz, xyz, totalling 3*numpoints
 * floating point values).
 */
AlgBox AlgWMComputeBoundingBox (int numpoints, const float* vertices);
/**
 * Merges 'numboxes' oriented bounding boxes, where box[b] is bounding box
 * with index 'b', 0 <= b < numboxes.
 */
AlgBox AlgWMMergeBoundingBoxes (int numboxes, const AlgBox* boxes);
/**
 * Computes the 8 vertices of bounding box 'box'.
 */
void AlgWMComputeVertices (const AlgBox& box, AlgVector vertices[8]);
/**
 * Returns true if 'v' is inside the bounding box volume.
 * Otherwise, returns false, and in *fail_coef / *fail_extent the projection
 * of the point in the failed axis and the extents of the axis. Can be used
 * to accept a given tolerance.
 */
bool AlgWMIsInsideBox (const AlgVector& v, const AlgBox& box, float* fail_coef=NULL, float* fail_extent=NULL);

#endif

