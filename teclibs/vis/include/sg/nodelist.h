// List of nodes class
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Apr 2001

#ifndef SG_NODELIST_H
#define SG_NODELIST_H

#include <ds/list.h>
#include <alg/matrix.h>
#include "defines.h"

class SGStrategy;
class SGNode;
class SGSpace;
class UtlWriter;

/**
 * SGNodeList Class.
 * This class implements a node list.
 * Methods are provided to:
 * - insert/remove nodes.
 * - obtain the node at a specified position.
 * - traverse the nodelist with a traversal strategy.
 * - write their description.
 */
class SG_API SGNodeList
{
  typedef DsPList<SGNode> List;
  List m_list;
public:
  static const char* CLASSNAME () { return "NodeList"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Construtor
   */
  SGNodeList ();
  /**
   * Destructor
   */
  virtual ~SGNodeList ();
  /**
   * Insert a parentless node to the list. Its parent must be specified.
   * If the node already has a parent, false is returned. 
   * If the insertion is successful, true is returned.
   */
  bool Insert (SGNode* node, SGSpace* parent);
  /**
   * Removes a node from the list. Returns true if the node was on the list.
   */
  bool Remove (SGNode* node);
  /**
   * Replaces a node 'a' with node 'b'.
   */
  bool Replace (SGNode *a, SGNode *b);
	/**
	 * Obtains the node at position 'index' on the list.
	 */
	SGNode* GetNode (int index) const;
	/**
	 * Obtains the number of nodes on the list.
	 */
	int GetNodeNumber () const;
  /**
   * Traverses the node list with a traversal strategy.
   */
  int Traverse (SGStrategy* s);
  /**
   * Writes the nodes descriptions separated by commas.
   */
  void Write (UtlWriter* writer) const;
};

#endif

