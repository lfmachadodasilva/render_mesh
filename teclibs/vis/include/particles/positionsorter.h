/************************************************************************
  Performs visibility sorting of a set o point positions with respect
  to a given viewing direction.

  rcosta@tecgraf.puc-rio.br
  rodesp@tecgraf.puc-rio.br

  Feb 2011

*************************************************************************/

#ifndef _PARTICLES_POSITION_SORTER_H_
#define _PARTICLES_POSITION_SORTER_H_

#include <alg/vector.h>
#include <utl/sort.h>
#include "defines.h"

/************************************************************************
  Forward Declarations
*************************************************************************/

/************************************************************************
  Class Declaration
*************************************************************************/

class PARTICLESH_API PtcPositionSorter
{
public:
  PtcPositionSorter ()
  {
  }

  ~PtcPositionSorter ()
  {
  }

  UTL_FORCE_INLINE void SetPositionArray (const float* positions, int dimension)
  {
    m_sort.GetCompareFunctor().SetPositionArray(positions, dimension);
  }

  UTL_FORCE_INLINE void SetLookAt (const AlgVector& direction)
  {
    m_sort.GetCompareFunctor().SetLookAt(direction);
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
      unsigned int i1dim = i1*m_dimension;
      unsigned int i2dim = i2*m_dimension;
      float dist1 = m_camdir.x*m_positions[i1dim] + m_camdir.y*m_positions[i1dim+1];
      float dist2 = m_camdir.x*m_positions[i2dim] + m_camdir.y*m_positions[i2dim+1];
      if (m_dimension == 3) {
        dist1 += m_camdir.z*m_positions[i1dim+2];
        dist2 += m_camdir.z*m_positions[i2dim+2];
      }
      if (dist1 > dist2) {
        return -1;
      }
      else if (dist2 > dist1) {
        return 1;
      }
      else if (i2 > i1) {
        return -1;
      }  
      return 1;
    }

    UTL_FORCE_INLINE void SetPositionArray (const float* positions, int dimension)
    { 
      m_positions = positions;
      m_dimension = dimension;
    }
    UTL_FORCE_INLINE void SetLookAt (const AlgVector& direction) 
    { 
      m_camdir = direction;
    }

  private:
    const float* m_positions;
    int m_dimension;
    AlgVector m_camdir;
  };

private:
  UtlSort<unsigned int, SortComparator, UtlSortPivotMiddle<unsigned int> > m_sort;
};

#endif