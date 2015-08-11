#ifndef GC_TEMPLATE_DYNAMIC_ARRAY_H
#define GC_TEMPLATE_DYNAMIC_ARRAY_H

#include "defines.h"

// Generic class implemented through a template
// Data structure: Dynamic Array

// Notes:
// - The type TYPE must be concrete
// - Type TYPE may implement a method "operator == (const TYPE&) const"
//   so that the array can be searched in O(n) for a given element.

template <class TYPE>
class GCH_API gcArray
{
public:

  // Constructors and Destructor

  gcArray (unsigned int capacity = 1, unsigned int increment = 0);

  virtual ~gcArray (void);

  // Array access

  unsigned int GetSize      (void) const;
  unsigned int GetIncrement (void) const;
  unsigned int GetCapacity  (void) const;
  TYPE*        GetArray     (void) const;
  bool         CopyToArray  (TYPE* allocatedCopy) const;

  TYPE&        operator []  (unsigned int position) const;

  // Array Manipulation

  void         SetIncrement (unsigned int increment);
  bool         Reserve      (unsigned int capacity);
  bool         Resize       (unsigned int size);

  bool         RemoveLast   (void);
  bool         AddLast      (const TYPE& element);

  bool         RemoveFast   (unsigned int position);                      // O(1), brings last element to position
  bool         AddFast      (unsigned int position, const TYPE& element); // O(1), makes position's element the last

  bool         Remove       (unsigned int position);                      // O(n) worst case, pulls  elements back
  bool         Add          (unsigned int position, const TYPE& element); // O(n) worst case, pushes elements forward

  bool         Find         (const TYPE&  element, unsigned int &whatIndex);
  void         Clear        (void);

  // Obtaining debug info

  void         PrintInfo    (void) const;

protected:

  // Auxiliary Functions

  bool         CreateArray (unsigned int capacity);
  unsigned int StepMax     (unsigned int capacity);

  // Internal Data

  TYPE*        m_Array;
  unsigned int m_ArrayMax;
  unsigned int m_ArraySize;
  unsigned int m_ArrayIncrement;

};

#include "array.inl"

#endif // GC_TEMPLATE_DYNAMIC_ARRAY_H
