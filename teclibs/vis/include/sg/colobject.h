// Collected object class
// fabraham@tecgraf.puc-rio.br
// Apr 2003

#ifndef SG_COL_OBJECT_H
#define SG_COL_OBJECT_H

#include <alg/matrix.h>
#include "collection.h"

class SGObject;
class SGStrategy;
class SGState;

/**
 * Collected object class.
 * 
 * This is a collection that is created when an object is collected.
 * It contains:
 * - a reference to the object.
 * - the object's state.
 * - the matrix that was active when the object was loaded.
 * - an object pool to minimize allocation/reallocation.
 * 
 * It provides methods to:
 * - obtain the object node.
 * - obtain the matrix (coordinate system) when the object node was collected.
 * - traverse this collection with a traversal strategy.
 * - release this collection.
 */
class SG_API SGColObject : public SGCollection
{
  AlgMatrix m_mtx;
  SGObject* m_obj;
  SGState* m_state;
public:
  static const char* CLASSNAME () { return "ColObject"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
	/**
	 * Creates a new collected object of object node 'o' with state 's'
	 * when the transformation matrix was 'm'.
	 */
  static SGColObject * Create (SGObject* o, SGState* s, AlgMatrix m);
	/**
	 * Obtains the matrix (coordinate system) when the object node was collected.
	 */
	AlgMatrix& GetMatrix () 
	{
		return m_mtx;
	}
	/**
	 * Obtains the object node.
	 */
  SGObject* GetObj () const
	{
		return m_obj; 
	}
	/**
	 * Obtains the object's state.
	 */
  SGState* GetState () const
	{
		return m_state;
	}
	/**
	 * Traverses the collection with a traversal strategy.
   * This will do the following:
	 * - skip if the colobject is disabled.
	 * - load itself.
	 * - load its state if any.
	 * - call obj->TraverseShapes() (collected object's shapes).
	 * - unload its state if any.
	 * - unload itself.
	 */
  virtual int Traverse (SGStrategy * s);
	/**
	 * Releases the collection.
	 */
  virtual void Release ();
};

#endif
