#ifndef WATERINDEX_H
#define WATERINDEX_H

#include "defines.h"

typedef struct idx
{
  int nind;
  unsigned int * index_ptr;
} w_index;

class WaterIndexes
{
public:
  w_index middle;
  w_index upBorderHigh, downBorderHigh, leftBorderHigh, rightBorderHigh;
  w_index upBorderLow, downBorderLow, leftBorderLow, rightBorderLow;
  
  WaterIndexes();
  ~WaterIndexes();

  void initialize(int gridRealPower, int gridWantedPower);

private:
  int m_gridRealPower;
  int m_gridWantedPower;

  void calcMiddleIndex();
  void calcUpBorderIndex();
  void calcDownBorderIndex();
  void calcLeftBorderIndex();
  void calcRightBorderIndex();
};  



#endif

