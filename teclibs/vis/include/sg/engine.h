// Engine class
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_ENGINE_H
#define SG_ENGINE_H

#include "refcount.h"

/**
 * SGEngine Class.
 *
 * This is the base class for all scene engines.
 *
 * A scene engine is an object that manipulates the scene graph according to a simulation time.
 * Methods must be provided to:
 * - Initialize the engine with the initial reference time.
 * - Update the engine with the current time, which is how many seconds passed since Start() was called.
 */
class SG_API SGEngine : public SGRefCount
{
public:
  static const char* CLASSNAME () { return "Engine"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Constructor
   */
  SGEngine () {}
  /**
   * Destructor
   */
	virtual ~SGEngine () {}
  /**
   * Initializes the engine with the reference time.
   */
	virtual void Start (float time) = 0;
  /**
   * Updates the engine with the current time, which is how many seconds passed since start() was called..
   */
	virtual void Apply (float time) = 0;
  /**
   * Writes the engine's description.
   */
  virtual void Write (UtlWriter* writer) = 0;
};

#endif
