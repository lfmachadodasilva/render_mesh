// Object class
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_OBJECT_H
#define SG_OBJECT_H

#include <ds/list.h>
#include "entity.h"

class SGShape;

/**
 * SGObject Class.
 * 
 * This class represents an object on the scene.
 * It is derived from the SGEntity class.
 * In addition to SGEntity, it has a list of shapes,
 * and a current shape.
 *
 * It provides methods to:
 * - insert/remove shapes from the list.
 * - clear the shape list.
 * - update the shape list transform.
 * - set which shape is the current shape.
 * - traverse the object with a traversal strategy.
 * - write its description.
 */
class SG_API SGObject : public SGEntity
{
public:
  typedef DsPList<SGShape> List;
private:
  List m_list;
public:
  static const char* CLASSNAME () { return "Object"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
	/**
	 * Constructor
	 */
  SGObject (SGState* s=0);
	/**
	 * Destructor
	 */
  virtual ~SGObject ();
  /**
   * Insert a shape to the list.
	 * The shape can be shared between multiple objects (recommended).
   */
  void Insert (SGShape* shp);
  /**
   * Removes a shape from the list. Returns true if the shape was on the list.
   */
  bool Remove (SGShape* shp);
	/**
	 * Removes all shapes from the list.
	 */
  void Clear ();
  /**
   * Obtains the number of shapes in the list.
   */
  int GetNumShapes ()
  {
    return m_list.Size();
  }
  /**
   * Obtains an iterator to the shape list.
   */
  List::Iterator GetShapes ()
  {
    return m_list.Begin();
  }
  /**
   * Traverses the object's shapes with a traversal strategy.
   */
  void TraverseShapes (SGStrategy* s);
  /**
   * Traverses the object with a traversal strategy.
   * This object will do the following:
	 * - skip if the object is disabled.
	 * - load itself.
	 * - load its state.
	 * - call TraverseShapes().
	 * - unload its state.
	 * - unload itself.
   */
  virtual int Traverse (SGStrategy *s);
	/**
	 * Writes the object description
	 */
  virtual void Write (UtlWriter * writer);
};

#endif

