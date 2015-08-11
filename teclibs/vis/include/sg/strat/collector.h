// Collector class
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Dec 2002

#ifndef SG_COLLECTOR_H
#define SG_COLLECTOR_H

#include "retained.h"

class SGCollection;
class SGScene;
class SGAccel;

/**
 * SGCollector Class.
 * This is the base class for all collectors.
 *
 * It provides methods to:
 * - set an acceleration strategy to speed up/minimize the collect.
 * - collect from a scene.
 * 
 * Implementations usually override this method by building some data structure
 * to store the collections and calling SGCollector::Collect() to start the
 * actual collect process.
 * 
 * Implementations must provide methods to:
 * - obtain the collect result
 * - release the collection.
 */
class SG_API SGCollector : public SGRetained
{
  SGAccel* m_accel_strat;
public:
  /**
   * Constructor
   */
  SGCollector () :
    m_accel_strat(0)
  {
  }
  /**
   * Destructor
   */
  virtual ~SGCollector ()
  {
  }
  /**
   * Sets the acceleration strategy for collect. If NULL, no strategy is used.
   */
  void SetAccelStrategy (SGAccel* strat)
  {
    m_accel_strat = strat;
  }
  /**
   * Gets the acceleration strategy for collect. Returns NULL if no strategy is being used.
   */
  SGAccel* GetAccelStrategy () const
  {
    return m_accel_strat;
  }
  /**
   * Collects a scene or root node. If an acceleration strategy is used, it will intercept
   * the calls to the collector. A camera must be set for this (set using SetCamera()).
   */
  virtual void Collect (SGScene* s);
  virtual void Collect (SGNode*  n);
  /**
   * Obtains the collect result.
   */
  virtual SGCollection* GetResult () = 0;
  /**
   * Releases the collect result.
   */
  virtual void Release () = 0;
};

#endif

