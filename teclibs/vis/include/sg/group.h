// Group class
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Apr 2001

#ifndef SG_GROUP_H
#define SG_GROUP_H

#include "entity.h"
#include "nodelist.h"

/**
 * SGGroup Class.
 * 
 * This class represents a group of nodes.
 * It is derived from the SGEntity and the SGNodeList class.
 * 
 * In addition to SGEntity and SGNodeList functionalities, it provides methods to:
 * - traverse the group with a traversal strategy.
 * - write its description.
 */
class SG_API SGGroup : public SGEntity, public SGNodeList
{
public:
  static const char* CLASSNAME () { return "Group"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
	/**
	 * Constructor
	 */
  SGGroup (SGState* s=NULL);
	/**
	 * Destructor
	 */
  virtual ~SGGroup ();
  /**
   * Insert a parentless node to the group.
   * Its parent is set as 'this'.
   * If the node already has a parent, false is returned. 
   * Otherwise, true is returned.
   */
  bool Insert (SGNode* node)
	{
		return SGNodeList::Insert(node,this);
  }
  /**
   * Traverses the group with a traversal strategy.
   * If the group is enabled, this will do the following:
	 * - load itself.
	 * - load its state.
	 * - traverse all children with the strategy.
	 * - unload its state
	 * - unload itself.
   */
  virtual int Traverse(SGStrategy * s);
	/**
	 * Writes the group's description
	 */
  virtual void Write (UtlWriter * writer);
};

#endif

