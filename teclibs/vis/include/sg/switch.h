// Switch class
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Apr 2001

#ifndef SG_SWITCH_H
#define SG_SWITCH_H

#include "group.h"

class SGStrategy;

/**
 * SGSwitch Class.
 * 
 * This class represents node switcher.
 * It is derived from the SGGroup class so nodelist and entity functionality is inherited.
 * 
 * It provides methods to:
 * - set/get the active node in the switch.
 * - traverse the switch with a traversal strategy.
 * - write its description.
 */
class SG_API SGSwitch : public SGGroup
{
  int m_active;
public:
  static const char* CLASSNAME () { return "Switch"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
	/**
	 * Constructor. Receives the switch's associated state (NULL means no state).
	 */
  SGSwitch (SGState* s=0);
	/**
	 * Destructor.
	 */
  virtual ~SGSwitch ();
	/**
	 * Sets the active node. If 'id' = -1, no node is selected, else (0<=id<GetNodeNumber())
	 */
  void SetActive (int id);
	/**
	 * Gets the active node, returns NULL of there is no active node.
	 */
  SGNode* GetActiveNode () const
	{
		if (GetActive() == -1)
			return NULL;
		else
			return SGGroup::GetNode(GetActive());
	}
	/**
	 * Gets the active node index, returns -1 if no node is selected.
	 */
  int GetActive () const
	{
		return m_active;
	}
  /**
   * Traverses the switch with a traversal strategy.
   * If the switch is enabled, this will do the following:
	 * - load itself.
	 * - load its state.
	 * - traverse selected child, if any, with the strategy.
	 * - unload its state
	 * - unload itself.
   */
  virtual int Traverse (SGStrategy* s);
	/**
	 * Writes the switch's description
	 */
  virtual void Write (UtlWriter * writer);
};

#endif
