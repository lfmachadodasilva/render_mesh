/**
*	Represents a view-frustum: implements culling and traversal algorithms.
*	author: Paulo Ivson <psantos@tecgraf.puc-rio.br>
*	date:   7-Mar-2008
*/
#ifndef _VDLIB_FRUSTUMCULLER_H_
#define _VDLIB_FRUSTUMCULLER_H_

#include <vrbv/common.h>
#include <vrbv/plane.h>
#include <vrbv/preorderiterator.h>
#include <vrbv/treebuilder.h>
#include <vdlib/common.h>

namespace vdlib {

// Traversal callback
class IFrustumCallback
{
public:
	virtual ~IFrustumCallback()
	{
	}
	// Called for every node that is found inside the view frustum.
	// If method returns true, traversal continues to the node's children.
	// If method returns false, assumes traversal should not continue to the
	// node's children.
	virtual bool inside( vrbv::Node* node ) = 0;
};

// Main frustum culling algorithms
// Warning: assumes node ids are consecutive and start with zero (TreeBuilder guarantees this).
class FrustumCuller
{
public:
	// Reallocate per-node culling information.
	void init( const vrbv::TreeBuilder::Statistics& stats );

	// Extracts all 6 frustum planes from matrix.
	// If matrix equals Projection, planes will be defined in Eye Space.
	// If matrix equals View * Projection, planes will be defined in World Space.
	void updateFrustumPlanes( const float* matrix );

	// Tests frustum planes in the following order: near, left, right, bottom, top, far.
	// Implements spatial coherence (don't test planes that parent node was found to be totally inside).
	// Implements temporal coherence (tests each node against its respective previous culling plane).
	bool contains( vrbv::Node* node );

	// Traverse hierarchy performing view-frustum culling
	void traverse( vrbv::Node* node, IFrustumCallback* callback );

private:
	class CullingInfo
	{
	public:
		CullingInfo();

		unsigned int planeId;
		unsigned int planeMask;
	};

	unsigned int getParentCullingMask( vrbv::Node* node ) const;

	vrbv::Plane _planes[6];
	std::vector<CullingInfo> _cullingInfo;
	vrbv::PreOrderIterator _itr;
};

} // namespace vdlib

#endif // _VDLIB_FRUSTUMCULLER_H_
