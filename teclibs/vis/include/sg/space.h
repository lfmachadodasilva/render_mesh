// Space class
// fabraham@tecgraf.puc-rio.br
// Oct 2003

#ifndef SG_SPACE_H
#define SG_SPACE_H

#include <alg/matrix.h>
#include "node.h"
#include "transform.h"

/**
 * SGSpace Class.
 * 
 * This class represents a node with a coordinate system.
 * This is achieved by being both a SGNode and a SGTransform.
 * This is done using the SGTransform information.
 */
class SG_API SGSpace : public SGNode, public SGTransform
{
public:
  static const char* CLASSNAME () { return "Space"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Constructor
   */
  SGSpace ();
  /**
   * Destructor
   */
  virtual ~SGSpace ();
  virtual AlgMatrix GetToLocal ();
  virtual AlgMatrix GetToGlobal ();
  /**
   * Updates the transformation from the node to its parent node.
   */
  virtual void UpdateTransform ();
  /**
   * Writes the space description
   */
  virtual void Write(UtlWriter* writer);
};

#endif

