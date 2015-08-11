/**
*	Basic hierarchy builder, implements "Average Center" spatial subdivision heuristic.
*	See "OBB-Tree: A Hierarchical Structure for Rapid Interference Detection"
*		S. Gottschalk, M.C. Lin, D. Manocha
*	author: Paulo Ivson <psantos@tecgraf.puc-rio.br>
*	date:   4-Mar-2008
*/
#ifndef VRBV_TREEBUILDER_H
#define VRBV_TREEBUILDER_H

#include "defines.h"
#include "common.h"
#include "rawnode.h"
#include <vr/Mat4.h>

namespace vrbv {

class VRBV_API TreeBuilder
{
public:
	// Keep statistics during construction
	class VRBV_API Statistics
	{
	public:
		void reset();
    void set(const Statistics* stats);

		int leafCount;
		int nodeCount;
		int treeDepth;
	};

	// @param cb callback for getting vertices coordinates when they are not
	// stored during tree construction. When NULL, actual vertices coordinates
	// will be stored. Otherwise, pointers will be used.
	TreeBuilder( GeomInfoCallback* cb = NULL );

	// Set callback to retrieve vertices coordinates. Useful only when using
	// pointers rather than storing geometry during tree construction.
	void setGetCoordsCB( GeomInfoCallback* cb );

	// Termination heuristics
	// If the number of vertices inside a node falls below this value, the node is declared a leaf
	void setMinVertexCount( int count );
	void setModelMatrix( vr::Mat4<float> mm );

	//////////////////////////////////////////////////////////////////////////
	// Main hierarchy construction
	// Return final hierarchy node that represents the root for the entire scene
	// After the hierarchy is built, SceneData is no longer needed
	//////////////////////////////////////////////////////////////////////////
	Node* createTree( SceneData& sceneData );

	// Get last hierarchy stats
	const Statistics& getStatistics() const;

private:
	enum Condition
	{
		Condition_Ok,
		Condition_Min_Vertex_Count,
		Condition_Min_Geometry_Count,
		Condition_Max_Tree_Depth,
		Condition_Indivisible
	};

	// Main recursive construction
	void recursiveCreateHierarchy( RawNode* node );

	// Check end of recursion based on heuristics
	Condition checkTerminateRecursion( RawNode* node );

	// Find best split position
	void findSplitPlane( Plane& plane, RawNode* node );

	// Given a split position, try to partition the node
	// If successful, return new children. Else do nothing.
	Condition partitionGeometries( RawNode* node, const Plane& splitPlane );

	// Set a final leaf node
	void setLeafNode( RawNode* node );

	Statistics _stats;
	vr::Mat4<float> _modelMatrix;
	int _maxTreeDepth;
	int _minVertexCount;
	int _minGeometryCount;
	bool _hasModelMatrix;
	bool _storeGeometry;
	GeomInfoCallback* _getCoords_cb;
};

} // namespace vrbv

#endif // VRBV_TREEBUILDER_H
