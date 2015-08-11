// Implements a packed boolean array (uses 1 bit per value).
// fabraham@tecgraf.puc-rio.br
// Mar 2011
#ifndef DS_PACKED_BOOL_ARRAY_H
#define DS_PACKED_BOOL_ARRAY_H

#include <ds/array.h>
#include <ds/defines.h>

class DSAPI DsPackedBooleanArray
{
public:
  DsPackedBooleanArray ()
  : m_size(0)
  {
  }
  void Resize (int size)
  {
    int extra = (size%8 == 0) ? 0 : 1;
    m_packed_array.Resize(size/8 + extra);
    m_size = size;
  }
  void ResizeWithZeros (int size)
  {
    int extra = (size%8 == 0) ? 0 : 1;
    m_packed_array.ResizeWithZeros(size/8 + extra);
    m_size = size;
  }
  int Size () const
  {
    return m_size;
  }
  void Set (int i, bool v)
  {
    if (v)
      SetTrue(i);
    else
      SetFalse(i);
  }
  void SetTrue (int i)
  {
    assert(0 <= i && i < m_size);

    int packed_i = i/8;
    unsigned char stored = m_packed_array.Get(packed_i);
    stored |= (1<<(i%8));
    m_packed_array[packed_i] = stored;
  }
  void SetFalse (int i)
  {
    assert(0 <= i && i < m_size);

    int packed_i = i/8;
    unsigned char stored = m_packed_array.Get(packed_i);
    stored &= ~(1<<(i%8));
    m_packed_array[packed_i] = stored;
  }
  bool Get (int i) const
  {
    assert(0 <= i && i < m_size);

    int packed_i = i/8;
    unsigned char stored = m_packed_array.Get(packed_i);
    return (stored & (1<<(i%8))) != 0;
  }
  int GetPackedSize () const
  {
    return m_packed_array.Size();
  }
  unsigned char* GetPackedArray ()
  {
    return m_packed_array.GetArray();
  }
  /**
   * |= operator.
   * Equivalent to doing (*this)[i] |= a[i] for all array positions 'i'.
   */
  void operator |= (DsPackedBooleanArray& a)
  {
    assert(m_size == a.m_size);
    int n = GetPackedSize();
    for (int i=0; i<n; ++i)
      m_packed_array[i] |= a.m_packed_array[i];
  }
private:
  DsArray<unsigned char> m_packed_array;
  int m_size;
};

#endif

