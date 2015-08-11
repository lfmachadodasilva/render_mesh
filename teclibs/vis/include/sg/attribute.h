// Attribute class
// fabraham@tecgraf.puc-rio.br
// May 2003

#ifndef SG_ATTRIBUTE_H
#define SG_ATTRIBUTE_H

#include "refcount.h"

/**
 * SGAttribute Class.
 *
 * This class represents the attributes of the scene graph nodes, like:
 * - states
 * - backgrounds
 * - shapes
 * 
 * All attributes have Load*() and Unload*() methods on the SGStrategy class.
 */
class SG_API SGAttribute : public SGRefCount
{
public:
  static const char* CLASSNAME () { return "Attribute"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
};

#endif
