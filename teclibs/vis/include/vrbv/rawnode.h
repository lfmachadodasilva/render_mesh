/**
*	Initial node used only during hierarchy construction.
*	author: Paulo Ivson <psantos@tecgraf.puc-rio.br>
*	date:   4-Mar-2008
*/
#ifndef VRBV_RAWNODE_H
#define VRBV_RAWNODE_H

#include "common.h"
#include "geometry.h"
#include "node.h"
#include "plane.h"
#include "defines.h"
#include <vector>

namespace vrbv {

// This stores information only needed during hierarchy construction
// Afterwards, only a reference to the actual Geometry is stored in each Node
class VRBV_API GeometryInfo
{
public:
  GeometryInfo()
  {
    geometry = NULL;
  }
  ~GeometryInfo()
  {
    // NOTE: geometry is not deleted because it
    // may be used outside GeometryInfo.
  }

public:
	int verticesStart;
	int verticesSize;
	Geometry* geometry;
};

typedef std::vector< GeometryInfo* > GeometryInfoVector;

// Stores additional information than final hierarchy node
class RawNode
{
public:
	RawNode();
  virtual ~RawNode();
	explicit RawNode( int id );

	void setLeftChild( RawNode* child );
	RawNode* getLeftChild();

	void setRightChild( RawNode* child );
	RawNode* getRightChild();

	// Remove sub-trees that aren't needed anymore
	void removeLeftChild();
	void removeRightChild();

	int getTreeDepth() const;

	std::vector<float>& getVertices();
	const std::vector<float>& getVertices() const;

	GeometryInfoVector& getGeometryInfos();
	const GeometryInfoVector& getGeometryInfos() const;

	// This is the final node that is used for main algorithms
	Node* getHierarchyNode();

	// Recompute bounding box based on current vertices and geometry information
	void computeBoundingBox();
	// This version processes pointers to vertices, using callback to get their coords.
	void computeBoundingBox( GeomInfoCallback* cb );

	// This method is called when RawNode is found to be a leaf node.
	// Copy references to all Geometries from RawNode to hierarchy Node.
	void assignGeometriesToHierarchyNode();

	// Get total number of vertices for all geometryinfos stored in this node.
	// NOTE: valid only when NOT storing geometry but pointers in geometry.
	int getVerticesCount();

	// Set total number of vertices for all geometryinfos stored in this node.
	// NOTE: valid only when NOT storing geometry but pointers in geometry.
	void setVerticesCount( int v_count );
	
	// update total vertices count in GeometryInfo's in this node.
	// Calculate vertices count iterating over geometryinfos in this node.
	void updateVerticesCount();

private:
	int _treeDepth;				 // Tree depth at this node
	RawNode* _leftChild;   // Temporary left child
	RawNode* _rightChild;  // Temporary right child

	std::vector<float> _vertices;      // Accumulated vertices for all geometries stored
	int _vertices_count;               // Accumulated # of vertices for all geometries
	GeometryInfoVector _geometryInfos; // Geometry information

	Node* _node;           // Actual hierarchy node
};

} // namespace vrbv

#endif // VRBV_RAWNODE_H
