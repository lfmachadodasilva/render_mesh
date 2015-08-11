// Node class
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_NODE_H
#define SG_NODE_H

#include <alg/matrix.h>
#include "item.h"

class SGSpace;
class SGStrategy;

/**
 * SGNode abstract Class.
 *
 * This is the base class for all scene graph nodes.
 *
 * It provides methods to:
 * - set/get the node's parent node.
 * - get the matrices that describe the transformation:
 *    - from the global coordinate system to the node's coordinate system.
 *    - from the node's coordinate system to the global coordinate system.
 * - traverse the node with a traversal strategy.
 */
class SG_API SGNode : public SGItem
{
  SGSpace* m_parent;
protected:
  /**
   * Constructor
   */
  SGNode ();
public:
  static const char* CLASSNAME () { return "Node"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Destructor
   */
  virtual ~SGNode ();
  /**
   * Sets the node's parent.
   */
  void SetParent (SGSpace* node)
	{
		m_parent = node; 
	}
  /**
   * Obtains the node's parent. (NULL if this is a root node)
   */
  SGSpace* GetParent () const
	{
		return m_parent; 
	}
  /**
   * Obtains the matrix that describes the transformation from 
   * the global coordinate system this coordinate system.
   */
  virtual AlgMatrix GetToLocal ();
  /**
   * Obtains the matrix that describes the transformation from 
   * this coordinate system to the global coordinate system.
   */
  virtual AlgMatrix GetToGlobal ();
	/**
   * Traverses the node with a traversal strategy.
   * If enabled, this node will do the following:
   * - load itself
   * - unload itself
   */
  virtual int Traverse(SGStrategy* s);
};

#endif

