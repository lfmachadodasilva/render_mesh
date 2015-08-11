#include <stdio.h>
#include <stdlib.h>

#define ARRAYTEMPLATE template <class TYPE>
#define ARRAYCLASS    gcArray <TYPE>

//-----------------------------//
// Constructors and Destructor //
//-----------------------------//

ARRAYTEMPLATE ARRAYCLASS::gcArray (unsigned int capacity, unsigned int increment) :
m_ArrayMax(capacity),
m_ArraySize(0),
m_ArrayIncrement(increment)
{
  if (!m_ArrayMax) m_ArrayMax = 1;
  if (!CreateArray(m_ArrayMax)) exit(-1);
}

ARRAYTEMPLATE ARRAYCLASS::~gcArray (void)
{
  if (m_Array) delete[] m_Array;
}

//--------------//
// Array access //
//--------------//

ARRAYTEMPLATE unsigned int ARRAYCLASS::GetSize (void) const
{
  return m_ArraySize;
}

ARRAYTEMPLATE unsigned int ARRAYCLASS::GetIncrement (void) const
{
  return m_ArrayIncrement;
}

ARRAYTEMPLATE unsigned int ARRAYCLASS::GetCapacity (void) const
{
  return m_ArrayMax;
}

ARRAYTEMPLATE TYPE* ARRAYCLASS::GetArray (void) const
{
  return m_Array;
}

ARRAYTEMPLATE bool ARRAYCLASS::CopyToArray (TYPE* allocatedCopy) const
{
  if (!allocatedCopy) return false;

  try
  {
    for (unsigned int i = 0; i < m_ArraySize; ++i)
      allocatedCopy[i] = m_Array[i];
  }
  catch (...)
  {
    printf("GC: Error copying to array\n");
    return false;
  }

  return true;
}

ARRAYTEMPLATE TYPE& ARRAYCLASS::operator [] (unsigned int position) const
{
  if (position >= m_ArraySize)
  {
    printf("GC: Error accessing array\n");
    if (!m_ArraySize) return m_Array[0];
    return m_Array[m_ArraySize-1];
  }
  return m_Array[position];
}

//--------------------//
// Array Manipulation //
//--------------------//

ARRAYTEMPLATE void ARRAYCLASS::SetIncrement (unsigned int increment)
{
  m_ArrayIncrement = increment;
}

ARRAYTEMPLATE bool ARRAYCLASS::Reserve (unsigned int capacity)
{
  if (m_ArrayMax >= capacity) return true;

  // Backups old array

  TYPE* oldArray = m_Array;

  // Attempts to allocate new array with requested capacity

  unsigned int newCapacity = StepMax(capacity);

  if (!CreateArray(newCapacity))
  {
    m_Array = oldArray;
    return false;
  }

  m_ArrayMax = newCapacity;

  // Copies old array into new array

  for (unsigned int i = 0; i < m_ArraySize; ++i) m_Array[i] = oldArray[i];

  // Discards old array

  delete[] oldArray;
  return true;
}

ARRAYTEMPLATE bool ARRAYCLASS::Resize (unsigned int size)
{
  if (!Reserve(size)) return false;
  m_ArraySize = size;
  return true;
}

ARRAYTEMPLATE bool ARRAYCLASS::RemoveLast (void)
{
  if (!m_ArraySize) return false;
  --m_ArraySize;
  return true;
}

ARRAYTEMPLATE bool ARRAYCLASS::AddLast (const TYPE& element)
{
  return Add(m_ArraySize, element);
}

ARRAYTEMPLATE bool ARRAYCLASS::RemoveFast (unsigned int position)
{
  if (position >= m_ArraySize) return false;
  --m_ArraySize;
  m_Array[position] = m_Array[m_ArraySize];
  return true;
}

ARRAYTEMPLATE bool ARRAYCLASS::AddFast (unsigned int position, const TYPE& element)
{
  if (position  > m_ArraySize) return false;
  if (position == m_ArraySize) return Add(m_ArraySize, element);
  if (!Add(m_ArraySize, m_Array[position])) return false;
  m_Array[position] = element;
  return true;
}

ARRAYTEMPLATE bool ARRAYCLASS::Remove (unsigned int position)
{
  if (position >= m_ArraySize) return false;

  --m_ArraySize;
  for (unsigned int i = position; i < m_ArraySize; ++i) m_Array[i] = m_Array[i+1];
  return true;
}

ARRAYTEMPLATE bool ARRAYCLASS::Add (unsigned int position, const TYPE& element)
{
  // Increases array capacity if necessary, according to increment rule

  if (position > m_ArraySize)  return false;
  if (!Reserve(m_ArraySize+1)) return false;

  // Moves array elements forward to open a slot for the new element

  for (unsigned int i = m_ArraySize; i > position; --i) m_Array[i] = m_Array[i-1];

  // Adds element to array

  m_Array[position] = element;
  ++m_ArraySize;

  return true;
}

ARRAYTEMPLATE bool ARRAYCLASS::Find (const TYPE& element, unsigned int &whatIndex)
{
  for (unsigned int i = 0; i < m_ArraySize; ++i)
  {
    if (m_Array[i] == element)
    {
      whatIndex = i;
      return true;
    }
  }
  return false;
}

ARRAYTEMPLATE void ARRAYCLASS::Clear (void)
{
  m_ArraySize = 0;
}

//----------------------//
// Obtaining debug info //
//----------------------//

ARRAYTEMPLATE void ARRAYCLASS::PrintInfo (void) const
{
  printf("<Dynamic Array Information>\n");
  printf("Array capacity:  %u\n", GetCapacity());
  printf("Array size:      %u\n", GetSize());
  printf("Array increment: %u\n", GetIncrement());
}

//---------------------//
// Auxiliary Functions //
//---------------------//

ARRAYTEMPLATE bool ARRAYCLASS::CreateArray (unsigned int capacity)
{
  try
  {
    m_Array = new TYPE[capacity];
  }
  catch (...)
  {
    printf("GC: Error allocating array\n");
    return false;
  }
  return true;
}

ARRAYTEMPLATE unsigned int ARRAYCLASS::StepMax (unsigned int capacity)
{
  unsigned int newCapacity = m_ArrayMax;

  while (newCapacity < capacity)
  {
    if (m_ArrayIncrement) newCapacity += m_ArrayIncrement;
    else                  newCapacity *= 2;
  }

  return newCapacity;
}

#undef ARRAYCLASS
#undef ARRAYTEMPLATE
