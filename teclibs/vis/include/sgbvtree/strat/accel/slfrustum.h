// Sort Last Frustum culling Strategy
// fabraham@tecgraf.puc-rio.br
// Sep 2004

#ifndef SG_SLFRUSTUM
#define SG_SLFRUSTUM

#include <sg/strat/accel.h>
#include <sgbvtree/sgbvtree.h>

class SGBVTREEAPI SGSLFrustum : public SGAccel
{
  int m_depth;
  unsigned short m_planes;
  unsigned short m_drawn_planes, m_notdrawn_planes;
  bool m_drawbv;
  bool m_useinnerproj;
  SGShapeBoundingVolumes* m_curr_shape_bvs;
public:
  SGSLFrustum (SGTransfStrategy* strategy);
  virtual ~SGSLFrustum ();
  /**
   * Requests that the shapes and nodes bounding volumes be drawn.
   * Only useful when the frustum strategy is directly attached to a immediate mode rendering strategy.
   */
  void SetDrawBV (bool drawbv)
  {
    m_drawbv = drawbv;
  }
  bool GetDrawBV ()
  {
    return m_drawbv;
  }
  void SetProjections (float cullprojection[16], float innerprojection[16], float outerprojection[16]);
  void SetProjections (float cullprojection[16], float outerprojection[16]);
  /**
   * Sets which planes must be considered for intersection
   */
  void SetPlanes (unsigned short planes)
  {
    m_planes = planes;
  }
  bool DrawnIntersectedWith (int plane)
  {
    return (m_drawn_planes & (1<<plane)) != 0;
  }
  bool NotDrawnIntersectedWith (int plane)
  {
    return (m_notdrawn_planes & (1<<plane)) != 0;
  }
  virtual bool PreLoad(SGShape* s);
  virtual bool PostLoad(SGNode* s);
  virtual void PostUnload(SGNode* n);
  virtual bool PostLoad(SGObject* o);
  virtual bool PostLoad(SGScene* s);
  virtual bool PostLoad(SGColScene* s);
};

#endif
