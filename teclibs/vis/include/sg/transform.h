// Transform class
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_TRANSFORM_H
#define SG_TRANSFORM_H

#include <alg/vector.h>
#include <alg/quatern.h>
#include <alg/matrix.h>
#include "defines.h"

class UtlWriter;
class AlgStack;

/**
 * SGTransform class.
 * 
 * This class takes care of all coordinate system transformations.
 * 
 * It provides methods to:
 * - change the transformation:
 *		- loadidentity/translate/rotate/scale.
 *		- set an arbitrary transformation matrix.
 * - get the transformation matrix and its inverse.
 * - write its description.
 * - accumulate/load/unload the transformation onto a matrix stack.
 *
 * Derived classes must implement the Update() method, which informs
 * whatever entities that this transformation has changed.
 */
class SG_API SGTransform
{
  AlgMatrix* m_matrix;

  void assertmatrix ();
public:
	/**
	 * Constructor
	 */
  SGTransform ();
	/**
	 * Destructor
	 */
  virtual ~SGTransform ();
	/**
	 * Resets the transformation.
	 */
  virtual void LoadIdentity ();
	/**
	 * Accumulates a translation matrix.
	 */
  void Translate (float x, float y, float z);
	/**
	 * Accumulates a translation matrix.
	 */
  void Translate (const AlgVector& v);
	/**
	 * Accumulates a rotation matrix.
	 */
  void Rotate (float angle, float x, float y, float z);
	/**
	 * Accumulates a rotation matrix.
	 */
	void Rotate (AlgQuatern& q);
	/**
	 * Accumulates a scale matrix.
	 */
  void Scale (float x, float y, float z);
	/**
	 * Accumulates a scale matrix.
	 */
	void Scale (AlgVector& s);
	/**
	 * Accumulates an uniform scale matrix.
	 */
  void Scale (float s);
  /**
   * Sets the transform.
   */
  void SetTransform (const AlgMatrix& matrix);
	/**
	 * Accumulates an arbitrary matrix.
	 */
  void Transform (const AlgMatrix& matrix);
	/**
	 * Checks whether there is a transformation.
	 */
	bool HasTransform () const;
	/**
	 * Obtains the transformation matrix.
	 */
  const AlgMatrix GetTransform () const;
	/**
	 * Obtains the inverse transformation matrix.
	 */
  const AlgMatrix GetInvTransform () const;
	/**
	 * Writes the transformation description.
	 */
	void Write(UtlWriter* writer) const;
	/**
	 * Accumulates the transformation onto a matrix stack.
	 */
  virtual void AccumTransf (AlgStack* s) const;
	/**
	 * Loads the transformation onto a matrix stack.
	 */
  virtual void LoadTransf (AlgStack* s) const;
	/**
	 * Unloads the transformation.
	 */
  virtual void UnloadTransf (AlgStack* s) const;
	/**
	 * Updates the nodes/components that require the updated transformation matrix.
	 * Must be implemented in every concrete class.
	 */
	virtual void UpdateTransform () = 0;
};

#endif
