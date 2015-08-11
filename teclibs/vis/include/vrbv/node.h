/**
*	Main hierarchy node.
*	author: Paulo Ivson <psantos@tecgraf.puc-rio.br>
*	date:   4-Mar-2008
*/
#ifndef VRBV_NODE_H
#define VRBV_NODE_H

#include "geometry.h"
#include "box.h"
#include "defines.h"

namespace vrbv {

// Hierarchy node used in main hierarchy
class VRBV_API Node
{
public:
	Node();
	~Node();

	// Only TreeBuilder should use this
	explicit Node( int id );

	// Specifies the identifier for this node.
	void setId( int id )
	{
		_id = id;
	}

	// Obtains the identifier of this node.
	int getId() const;

	// Hierarchy
	Node* getParent();

	void setLeftChild( Node* child );
	Node* getLeftChild();

	void setRightChild( Node* child );
	Node* getRightChild();
	
	bool isLeaf() const;

	// Geometry
	Box& getBoundingBox();
	const Box& getBoundingBox() const;
	GeometryVector& getGeometries();
	const GeometryVector& getGeometries() const;

  // added just for correct compilation of vdlib/example (uses vr::ref_ptr)
  void incRef () {}
  void decRef () {}
private:
	int _id;

	Node* _parent;
	Node* _leftChild;
	Node* _rightChild;

	Box _bbox;
	GeometryVector _geometries;
};

} // namespace vrbv

#endif // VRBV_NODE_H
