// Container Space class
// fabraham@tecgraf.puc-rio.br
// Oct 2003

#ifndef SG_CONTSPACE_H
#define SG_CONTSPACE_H

#include "space.h"
#include "nodelist.h"

class SGStrategy;
class UtlWriter;

/**
 * SGContainerSpace Class.
 * 
 * This class represents a space that has child nodes.
 * It inherits the functionalities from SGSpace and SGNodeList.
 *
 * It provides methods to:
 * - traverse the space and its children with a traversal strategy.
 * - write its description.
 */
class SG_API SGContainerSpace : public SGSpace, public SGNodeList
{
public:
  static const char* CLASSNAME () { return "ContainerSpace"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
	/**
	 * Constructor
	 */
  SGContainerSpace ()
	{
	}
	/**
	 * Destructor
	 */
  virtual ~SGContainerSpace ()
	{
	}
  /**
   * Insert a parentless node to the container space.
   * Its parent is set as 'this'.
	 * 
   * If the node already has a parent, false is returned. 
   * Otherwise, true is returned.
   */
  bool Insert (SGNode* node)
  {
    return SGNodeList::Insert(node,this);
  }
  /**
   * Traverses the space with a traversal strategy.
	 * 
   * If the space is enabled, this will do the following:
	 * - load itself.
	 * - traverse all children with the strategy.
	 * - unload itself.
	 */
	virtual int Traverse(SGStrategy* s);
	/**
	 * Writes the space description.
	 */
	virtual void Write(UtlWriter* writer);
};

#endif

