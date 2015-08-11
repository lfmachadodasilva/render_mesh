// Quad sets for reservoirs (with occlusion culling)
// fabraham@tecgraf.puc-rio.br
// May 2008
#ifndef TPV_QUAD_SET_OCCLUSION_H
#define TPV_QUAD_SET_OCCLUSION_H

#include "geomsetocclusion.h"
#include "quadsetsplithex.h"
#include <topsview/geometry/quadset.h>
#include <topsviewres/defines.h>

class TPVRES_API TpvResQuadSetOcclusion : public TpvResGeometrySetOcclusion
{
public:
  TpvResQuadSetOcclusion (bool disable_occlusion_culling,
                          bool disable_backface_culling)
  : TpvResGeometrySetOcclusion(4,
                               disable_occlusion_culling,
                               disable_backface_culling)
  {
  }
  TpvGeometrySet* CreateGeometrySet () const
  {
    if (!BackfaceCullingDisabled() && TpvResQuadSetSplitHex::IsCullingEnabled())
      return new TpvResQuadSetSplitHex();
    else
      return new TpvQuadSet();
  }
};

#endif

