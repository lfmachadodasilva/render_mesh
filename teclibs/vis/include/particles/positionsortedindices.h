/************************************************************************  
  rcosta@tecgraf.puc-rio.br
  rodesp@tecgraf.puc-rio.br
  Nov 2008
*************************************************************************/

#ifndef _PARTICLES_POSITION_SORTED_INDICES_H_
#define _PARTICLES_POSITION_SORTED_INDICES_H_

#include "renderer.h"
#include "defines.h"
#include "positionsorter.h"

class AlgVector;
class UGLArray;

/**
 * Point indices sorted by their positions with respect to an observer.
 */
class PARTICLES_API PtcPositionSortedIndices
{
public:
  PtcPositionSortedIndices ();

  ~PtcPositionSortedIndices ();

  void SetPositions (int dimension, int count, const float* positions);

  void SetCamera (const AlgVector & position, const AlgVector & direction);

  /**
   * Sets the minimum number of times positions must be set before sorted indices 
   * are updated, after no changes have ocurred to the camera position.
   *
   * Default: 0 (every time)
   */
  void SetSortDelay (int delay);

  const int* GetArray ();

private:
  void Update ();

private:
  PtcPositionSorter m_sorter;
  int m_dimension;
  int m_count;
  const float* m_positions;
  UGLArray* m_sorted_indexes;
  unsigned int m_sortcount;
  unsigned int m_sortdelay;
  bool m_outdated;
};

#endif