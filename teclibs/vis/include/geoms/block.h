/**
 * Block structure used for grouping polys.
 * author: Cesar Palomo <cpalomo@tecgraf.puc-rio.br>
 * date:   13-Oct-2011
 */
#ifndef GEOMS_BLOCK_H
#define GEOMS_BLOCK_H

#include <stdio.h>

namespace geoms { 

class Block
{
public:
  Block (const int* firstpoly_ptr = NULL, int count = 0) 
    : m_polys(firstpoly_ptr), m_count(count) 
  {
    ;
  }
public:
  void SetPolys (const int* polys)
  {
    m_polys = polys;
  }
  int GetPoly (int i) const
  {
    return m_polys[i];
  }
  void IncPolyCount ()
  {
    m_count++;
  }
  void SetPolyCount (int count)
  {
    m_count = count;
  }
  int GetPolyCount () const
  {
    return m_count;
  }
private:
  const int* m_polys;
  int m_count;
};

} // namespace geoms

#endif   // GEOMS_BLOCK_H

