/************************************************************************
  Performs visibility sorting of a set o point positions with respect
  to a given viewing direction.

  rcosta@tecgraf.puc-rio.br
  rodesp@tecgraf.puc-rio.br

  Feb 2011

*************************************************************************/

#ifndef _PARTICLES_RADIUS_SORTER_H_
#define _PARTICLES_RADIUS_SORTER_H_

#include <utl/sort.h>
#include "defines.h"

/************************************************************************
  Forward Declarations
*************************************************************************/

/************************************************************************
  Class Declaration
*************************************************************************/

class PARTICLESH_API PtcRadiusSorter
{
public:
  PtcRadiusSorter ()
  {
  }

  ~PtcRadiusSorter ()
  {
  }

  UTL_FORCE_INLINE void SetRadiusArray (const float* radii)
  {    
    m_sort.GetCompareFunctor().SetRadiusArray(radii);
  }

  UTL_FORCE_INLINE void Sort (unsigned int* indices, int firsti, int lasti)
  {
    m_sort.QuickSort(indices, firsti, lasti);
  }

private:
  class SortComparator
  {
  public:
    UTL_FORCE_INLINE int operator() (const unsigned int i1, const unsigned int i2) const
    {
      if (m_radii[i1] > m_radii[i2])
        return 1;
      else if (m_radii[i2] > m_radii[i1])
        return -1;
      else if (i2 > i1)
        return -1;
      else
        return 1;
    }

    void SetRadiusArray (const float* radii)
    { 
      m_radii = radii;
    }

  private:
    const float* m_radii;
  };

private:
  UtlSort<unsigned int, SortComparator, UtlSortPivotMiddle<unsigned int> > m_sort;
};

#endif