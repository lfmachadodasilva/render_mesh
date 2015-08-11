// Frustum culling Strategy
// fabraham@tecgraf.puc-rio.br
// Apr 2003

#ifndef SG_FRUSTUM
#define SG_FRUSTUM

#include <sgbvtree/sgbvtree.h>
#include <sg/strat/accel.h>

/**
 * Frustum culling traversal strategy.
 * This strategy will intercept the calls to a strategy performing frustum culling
 * on nodes and shapes.
 */
class SGBVTREEAPI SGFrustum : public SGAccel
{
  int m_depth;
  bool m_drawbv;
  AlgMatrix *m_base;
  SGShapeBoundingVolumes* m_curr_shape_bvs;
  void SetFrustum ();
public:
  SGFrustum (SGTransfStrategy* strategy);
  virtual ~SGFrustum ();
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
  /**
   * Sets a user-defined frustum.
   */
  void SetFrustum (AlgMatrix base);
  /**
   * Turns of the user-defined frustum.
   * Frustum will be obtained from the SGTransfStrategy.
   */
  void UnsetFrustum ();
  virtual bool PreLoad(SGShape* s);
  virtual bool PostLoad(SGNode* s);
  virtual bool PostLoad(SGObject* o);
  virtual void PostUnload(SGNode* n);
  virtual bool PostLoad(SGScene* s);
  virtual bool PostLoad(SGColScene* s);
};

#endif
