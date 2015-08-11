// State class
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_STATE_H
#define SG_STATE_H

#include <ds/array.h>
#include "attribute.h"

/**
 * SGState Class.
 * 
 * This is the base class for all states.
 *
 * It provides an interface for concrete classes to:
 * - obtain the state's id.
 * - load/unload state.
 * - check the state's opacity status. Rendering strategies can use this information to do correct or partially correct transparency.
 * 
 * This module maintains an state list, indexable by the state id.
 * Load/Unload must save and restore the OpenGL state variables with glPush/glPopAttrib.
 */
class SG_API SGState : public SGAttribute
{
  int m_id;
protected:
  /**
   * Constructor
   */
  SGState ();
public:
  static const char* CLASSNAME () { return "State"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Obtains the number of state in the state table.
   */
  static int GetTabDimension ();
  /**
   * Obtains the state with id 'id'.
   */
  static SGState* GetState (int id);
  /**
   * Destructor.
   */
  virtual ~SGState ();
  /**
   * Obtains the state id.
   */
  int GetId () const { return m_id; }
  /**
   * Loads state.
   */
  virtual void Load () = 0;
  /**
   * Unloads state.
   */
  virtual void Unload () = 0;
  /**
   * Checks if state is opaque or translucent.
   */
  virtual bool IsOpaque () const = 0;
  /**
   * Writes the state's description.
   */
  virtual void Write (UtlWriter* writer);
};

#endif

