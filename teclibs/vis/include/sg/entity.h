// Entity class
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_ENTITY_H
#define SG_ENTITY_H

#include <alg/vector.h>
#include <alg/matrix.h>
#include <alg/quatern.h>
#include <alg/stack.h>
#include "space.h"

class SGState;

/**
 * SGEntity Class.
 * 
 * This is the base class for all entity nodes.
 * It is composed by:
 * - 3d position (relative to its parent node's coordinate system) composed of:
 *	 - a 3d translation
 *	 - a 3d reference point for:
 *	   - rotation around an arbitrary axis
 *	   - scale
 * - an associated state (NULL means no state).
 *
 * It provides methods to:
 * - manipulate the entity's local coordinate system with set/get methods that access:
 *   - the position.
 *   - the reference point for scale and rotation.
 *   - the rotation.
 *   - the scale (uniform or non-uniform).
 * - set/get the associated state.
 * - load/unload its coordinate system on a matrix stack.
 * - check/get the transformation from the parent node's coordinate system to the entity's coordinate system.
 * - write its description.
 */
class SG_API SGEntity : public SGSpace
{
  enum 
  {
    REFERENCE=1,
    POSITION=2,
    SCALE=4,
    ROTATION=8
  };
  int m_flag;
  AlgVector m_pos;
  AlgVector m_ref;
  AlgVector m_scale;
  AlgQuatern m_rot;
  SGState* m_state;

  void CalcTransf ();
public:
  static const char* CLASSNAME () { return "Entity"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
	/**
	 * Constructor. Receives the entity's associated state (default=NULL).
	 */
  SGEntity (SGState* s=0);
	/**
	 * Destructor.
	 */
  virtual ~SGEntity ();
	/**
	 * Sets the position.
	 */
  void SetPosition (float x, float y, float z);
	/**
	 * Sets the position.
	 */	
  void SetPosition (const AlgVector& pos);
	/**
	 * Gets the position.
	 */	
  void GetPosition (float* x, float* y, float* z) const;
	/**
	 * Gets the position.
	 */	
  const AlgVector& GetPosition () const;
  /**
   * Informs if the entity has a position configured.
   */
  int HasPosition () const
  {
    return m_flag & POSITION;
  }
	/**
	 * Sets the reference point for rotation/scaling.  
	 */
  void SetReference (float x, float y, float z);
	/**
	 * Sets the reference point for rotation/scaling.  
	 */
  void SetReference (const AlgVector& ref);
	/**
	 * Gets the reference point for rotation/scaling.  
	 */
  void GetReference (float* x, float* y, float* z) const;
	/**
	 * Gets the reference point for rotation/scaling.  
	 */
  const AlgVector& GetReference () const;
  /**
   * Informs if the entity has a rotation reference point configured.
   */
  int HasReference () const
  {
    return m_flag & REFERENCE;
  }
	/**
	 * Sets the rotation.  
	 */
  void SetRotation (float angle, float x, float y, float z);
	/**
	 * Sets the rotation.  
	 */
  void SetRotation (const AlgQuatern& rot);
	/**
	 * Gets the rotation.  
	 */
  void GetRotation (float* angle, float* x, float* y, float* z) const;
	/**
	 * Gets the rotation.  
	 */
  const AlgQuatern& GetRotation () const;
  /**
   * Informs if the entity has a rotation configured.
   */
  int HasRotation () const
  {
    return m_flag & ROTATION;
  }
	/**
	 * Sets the scale (uniform).  
	 */
	void SetScale (float s);
	/**
	 * Sets the scale (nonuniform).
	 */
  void SetScale (float x, float y, float z);
	/**
	 * Sets the scale.  
	 */
  void SetScale (const AlgVector& s);
	/**
	 * Gets the scale.  
	 */
  void GetScale (float* x, float* y, float* z) const;
	/**
	 * Gets the scale.  
	 */
  const AlgVector& GetScale () const;
  /**
   * Informs if the entity has a scale configured.
   */
  int HasScale () const
  {
    return m_flag & SCALE;
  }
	/**
	 * Sets the entity's associated state.
	 */
  void SetState (SGState* s);
	/**
	 * Gets the state.
	 */
  SGState* GetState () const { return m_state; }
  /**
   * Resets the entity's transformation.
   */
  virtual void LoadIdentity ();
	/**
	 * Accumulates the transformation onto a matrix stack.
	 */
  virtual void AccumTransf (AlgStack* s) const;
	/**
	 * Loads the entity's coordinate system transformation onto the matrix stack s.
	 */
  virtual void LoadTransf (AlgStack* s) const;
	/**
	 * Unloads the entity's transformation.
	 */
  virtual void UnloadTransf (AlgStack* s) const;
	/**
	 * Writes the entity's description.
	 */
  virtual void Write (UtlWriter * writer);
};

#endif
