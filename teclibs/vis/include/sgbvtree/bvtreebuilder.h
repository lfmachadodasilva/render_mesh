// bvtree builder strategy
// fabraham@tecgraf.puc-rio.br
// Feb 2005

#ifndef SG_BVTREEBUILDER
#define SG_BVTREEBUILDER

#include <sgbvtree/sgbvtree.h>
#include <ds/hash.h>

class SGNode;
class SGObject;

/**
 * Builds a bounding volume tree for node 'node'.
 */
SGBVTREEAPI void sgbvtree_buildbvtree (SGNode *node);
/**
 * Enables automatic bounding volume creation for every sg hierarchy
 * to be constructed after this call.
 */
SGBVTREEAPI void sgbvtree_listen ();
/**
 * Disables automatic bounding volume creation for sg hierarchies
 * constructed after this call.
 */
SGBVTREEAPI void sgbvtree_nolisten ();
/**
 * Obtains the shape-to-bounding volume association for object 'object'.
 * Returns NULL in case no association was ever created.
 */
SGBVTREEAPI SGShapeBoundingVolumes* sgbvtree_get_shape_bvs_for_object (SGObject *object);
/**
 * Obtains the bounding volume for node 'node'.
 * Returns NULL in case no bounding volume is found.
 */
SGBVTREEAPI bv_t* sgbvtree_get_bv (SGNode *node);
/**
 * Obtains the bounding volume for shape 'shape' using a previously obtained
 * shape-to-bounding volume association 'shapebvs' for some object.
 * Returns NULL in case no bounding volume is found for the shape.
 */
SGBVTREEAPI bv_t* sgbvtree_get_bv (SGShapeBoundingVolumes* shapebvs, SGShape *shape);

/**
 * Obtains an oriented bounding box of the volume
 * int its local coordinate system.
 */
SGBVTREEAPI void sgbvtree_getaabb (SGNode *node,
  float *xmin, float *xmax, float *ymin, float *ymax, float *zmin, float *zmax);

#endif
