// World Space class
// fabraham@tecgraf.puc-rio.br
// Oct 2003

#ifndef SG_WRLSPACE_H
#define SG_WRLSPACE_H

#include <alg/matrix.h>
#include "contspace.h"

class AlgStack;

/**
 * SGWorldSpace Class.
 * 
 * The worldspace class is a SGContainerSpace (therefore a Space with a child node list)
 * that lies in the world space coordinates. Therefore, their children will also lie on it.
 * 
 * Optionally, a transformation can be done so that child nodes will be on worldspace + this transform.
 * 
 * It provides methods to:
 * - load/unload the transformation to/from the worldspace
 * - write its description.
 */
class SG_API SGWorldSpace : public SGContainerSpace
{
public:
  static const char* CLASSNAME () { return "WorldSpace"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
	/**
	 * Constructor. 
	 */
  SGWorldSpace ();
	/**
	 * Destructor.
	 */
  virtual ~SGWorldSpace ();
  virtual AlgMatrix GetToLocal ();
  virtual AlgMatrix GetToGlobal ();
  /**
   * Accumulates the coordinate system transformation from this to the child nodes.
	 * Calls LoadTransf() since this coordinate system change does not accumulate.
   */
  virtual void AccumTransf (AlgStack* s) const;
  /**
   * Loads the coordinate system transformation from this to the child nodes.
   */
  virtual void LoadTransf (AlgStack* s) const;
	/*
	 * Unloads the transformation.
	 */
  virtual void UnloadTransf (AlgStack* s) const;
	/*
	 * Writes the worldspace description.
	 */
  virtual void Write (UtlWriter * writer);
};

#endif

