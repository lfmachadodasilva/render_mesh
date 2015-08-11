// Collected light class
// fabraham@tecgraf.puc-rio.br
// Apr 2003

#ifndef SG_COL_LIGHT_H
#define SG_COL_LIGHT_H

#include <alg/matrix.h>
#include "collection.h"

class SGLight;
class SGStrategy;

/**
 * Collected light class.
 * 
 * This is a collection that is created when a light is collected.
 * 
 * It contains a reference to the light node and the matrix that was active when the light was loaded.
 * 
 * It contains a object pool to minimize allocation/reallocation.
 * 
 * It provides methods to:
 * - obtain the light node.
 * - obtain the matrix (coordinate system) when the light node was collected.
 * - traverse this collection with a traversal strategy.
 * - release this collection.
 */
class SG_API SGColLight : public SGCollection
{
  AlgMatrix m_mtx;
  SGLight* m_light;
public:
  static const char* CLASSNAME () { return "ColLight"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
	/**
	 * Creates a new collected light of light node 'l' when the transformation matrix was 'm'.
	 */
  static SGColLight* Create (SGLight* l, AlgMatrix m);
	/**
	 * Obtains the matrix (coordinate system) when the light node was collected.
	 */
	AlgMatrix& GetMatrix ()
	{
		return m_mtx;
	}
	/**
	 * Obtains the light node.
	 */
  SGLight* GetLight () const
	{
		return m_light;
	}
	/**
	 * Traverses the collection with a traversal strategy. Will load/unload itself.
	 */
  virtual int Traverse (SGStrategy* s);
	/**
	 * Releases the collection.
	 */
  virtual void Release ();
};

#endif
