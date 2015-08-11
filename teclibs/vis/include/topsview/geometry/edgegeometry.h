/**
* Modulo de definicao da classe TpvGeometry, para ser usado como geometria extraida para a TopsView
*/

#ifndef TPV_EDGE_GEOMETRY_H
#define TPV_EDGE_GEOMETRY_H

#include <tops/tops.h>
#include <topsview/defines.h>

#include "geometry3.h"

#include <stdio.h>
#include <math.h>

/**  
*/
MODEL_CLASS_TEMPLATE
class TPV_API TpvEdgeGeometry : public TpvGeometry3<MODELCLASS>
{
public:
  virtual int GetNumOfEdges(int step_id = TpvGeometry3<MODELCLASS>::NO_REZONE_STEP_ID) = 0;
  virtual TopEdgeUse* GetEdges(int step_id = TpvGeometry3<MODELCLASS>::NO_REZONE_STEP_ID) = 0;
};

#endif
