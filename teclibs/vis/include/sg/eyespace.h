// Eye Space class
// fabraham@tecgraf.puc-rio.br
// Oct 2003

#ifndef SG_EYESPACE_H
#define SG_EYESPACE_H

#include <alg/matrix.h>
#include "contspace.h"

class AlgStack;
class SGCamera;

/**
 * SGEyeSpace Class.
 * 
 * The eyespace class is a SGContainerSpace (therefore a Space with a child node list)
 * that lies in the eye space. Therefore, their children will also lie on it.
 *
 * Optionally, a transformation can be done so that child nodes will be on eyespace + this transform.
 * 
 * It provides methods to:
 * - load/unload the transformation to/from the eyespace.
 * - write its description.
 */
class SG_API SGEyeSpace : public SGContainerSpace
{
	SGCamera* m_camera;
public:
  static const char* CLASSNAME () { return "EyeSpace"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
	/**
	 * Constructor. Receives the current rendering camera. It must be a valid camera.
	 */
  SGEyeSpace (SGCamera* camera);
	/**
	 * Destructor.
	 */
  virtual ~SGEyeSpace ();
	/**
	 * Sets the current rendering camera.
	 */
  bool SetCamera (SGCamera* camera);
	/**
	 * Gets the current rendering camera.
	 */
  SGCamera* GetCamera () const
	{
		return m_camera;
	}
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
	/**
	 * Unloads the transformation.
	 */
  virtual void UnloadTransf (AlgStack* s) const;
	/**
	 * Writes the eyespace description.
	 */
  virtual void Write (UtlWriter* writer);
};

#endif

