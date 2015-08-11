#ifndef GC_ARRAY_H
#define GC_ARRAY_H

#include <memory.h>

#define ARRAYTEMPLATE template <class TYPE>

//---------------------------------------------------------//
// Exchanging the position of two elements inside a vector //
//---------------------------------------------------------//

ARRAYTEMPLATE void gcExchange (TYPE* element1, TYPE* element2)
{
  TYPE tempElement = *element1;
  *element1 = *element2;
  *element2 = tempElement;
}

//---------------------------------------------------------------//
// Copying and merging vertex arrays into newly allocated arrays //
//---------------------------------------------------------------//

ARRAYTEMPLATE TYPE* gcCopyArray  (TYPE source[], int firstIndex, int lastIndex)
{
  int numElements = lastIndex - firstIndex + 1;
  TYPE* newArray = new TYPE[numElements];
  memcpy(newArray, source+firstIndex, numElements * sizeof(TYPE));
  return newArray;
}

ARRAYTEMPLATE TYPE** gcDuplicateArray (TYPE* source[], int firstIndex, int lastIndex) // Extra level of indirection!!!
{
  int numElements = lastIndex - firstIndex + 1;
  TYPE** newArray = new TYPE*[numElements];
  for (int i = 0; i < numElements; ++i) newArray[i] = new TYPE(*(source[i]));
  return newArray;
}

ARRAYTEMPLATE TYPE* gcMergeArrays (TYPE source1[], int size1, TYPE source2[], int size2)
{
  int numElements = size1 + size2;
  TYPE* newArray = new TYPE[numElements];
  memcpy(newArray, source1, size1 * sizeof(TYPE));
  memcpy(newArray+size1, source2, size2 * sizeof(TYPE));
  return newArray;
}

ARRAYTEMPLATE TYPE* gcMergeArrays (TYPE source1[], int size1, TYPE source2[], int size2, TYPE source3[], int size3)
{
  int numElements = size1 + size2 + size3;
  TYPE* newArray = new TYPE[numElements];
  memcpy(newArray, source1, size1 * sizeof(TYPE));
  memcpy(newArray+size1, source2, size2 * sizeof(TYPE));
  memcpy(newArray+size1+size2, source3, size3 * sizeof(TYPE));
  return newArray;
}

//-------------------------//
// Releasing vertex arrays //
//-------------------------//

ARRAYTEMPLATE void gcReleaseArray (TYPE* source[])
{
  delete[] *source;
  *source = 0;
}

ARRAYTEMPLATE void gcReleaseAll (TYPE* source[], int arraySize)
{
  TYPE* src = *source;
  if (src)
  {
    for (int i = 0; i < arraySize; ++i) delete (src[i]);
    gcReleaseArray<TYPE>(source);
  }
}

#undef ARRAYTEMPLATE

#endif // GC_ARRAY_H
