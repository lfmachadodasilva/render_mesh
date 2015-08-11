// Bin class
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Apr 2003

#ifndef SG_BIN_H
#define SG_BIN_H

#include <ds/list.h>
#include "collection.h"

class SGState;
class SGStrategy;

/**
 * SGBin class.
 *  
 * This class represents a bucket sort bin.
 *  
 * It's used to collect elements of a scene graph and quickly do some kind of sorting according to the collector's sorting criteria.
 * 
 * It optionally has a state per bucket, to be loaded when each slot is traversed.
 * 
 * It contains a simple memory management mechanism to allow few reallocations during the pipeline.
 *
 * It provides methods to:
 * - set the bin dimension (number of slots).
 * - set an individual slot state.
 * - insert a collection to a slot.
 * - traverse the bin with a traversal strategy.
 * - release the memory used by the bin and their related collections.
 */
class SG_API SGBin : public SGCollection
{
  typedef DsPList<SGCollection> List;
  typedef struct
  {
    List* list;
    SGState* state;
  } Bucket;
  int m_dim;
  Bucket* m_array;
public:
  static const char* CLASSNAME () { return "Bin"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Creates a bin with 'dimension' slots.
   */
  static SGBin* Create(int dimension);
  /**
   * Constructs an empty bin. Should not be called by ordinary users,
   * use Create() instead.
   */
  SGBin () :
    m_dim(0),
    m_array(NULL)
  {
  }
  /**
   * Sets the number of slots.
   */
  void SetDimension (int dimension);
  /**
   * Sets the state of the slot 'slot'. (0<=slot<numslots)
   */
  void SetSlotState (int slot, SGState* s);
  /**
   * Inserts a collection to the slot 'slot'. (0<=slot<numslots)
   */
  void Insert (SGCollection* c, int slot);
  /**
   * Traverses the bin with a traversal strategy.
   * This bin will do the following:
   * - skip if the bin is disabled.
   * - load itself.
   * - for each slot:
   *  - load the slot state if any.
   *  - traverse each collection.
   *  - unload the slot state if any.
   * - unload itself.
   */
  virtual int Traverse (SGStrategy * s);
  /**
   * Releases the bin.
   */
  virtual void Release ();
};

#endif

