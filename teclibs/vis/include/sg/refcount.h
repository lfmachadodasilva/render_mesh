// Reference counter class
// fabraham@tecgraf.puc-rio.br
// Nov 2003

#ifndef SG_REFCOUNT_H
#define SG_REFCOUNT_H

#include <stdio.h>
#include "item.h"

/**
 * SGRefCount Class.
 *
 * The class provides a reference count mechanism to allow automatic memory management.
 */
class SG_API SGRefCount : public SGItem
{
  int m_ref_count;
public:
  static const char* CLASSNAME () { return "RefCount"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Constructor
   */
  SGRefCount () : 
		m_ref_count(0)
	{
	}
  /**
   * Destructor
   */
  virtual ~SGRefCount ()
	{
	}  
  /**
   * Increases the object's reference counter.
   */
  void IncRef ()
  {
    m_ref_count++;
  }
  /**
   * Decreases the object's reference counter.
   * If reference counter reaches 0, the object is freed.
   */
  void DecRef ()
  {
    if (--m_ref_count == 0)
      delete this;
  }
  /**
   * Obtains the number of references.
   */
  int GetRefCount ()
  {
    return m_ref_count;
  }
};

#endif
