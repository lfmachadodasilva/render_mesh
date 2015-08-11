// Collection class
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Apr 2003

#ifndef SG_COLLECTION_H
#define SG_COLLECTION_H

#include "node.h"

/**
 * Collection class.
 *
 * This is an interface that all collection nodes must implement.
 */
class SG_API SGCollection : public SGNode
{
public:
	/**
	 * Releases the collection.
	 */
  virtual void Release () = 0;
};

#endif
