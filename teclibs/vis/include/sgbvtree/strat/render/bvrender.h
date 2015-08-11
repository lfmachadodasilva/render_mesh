// BV Render Strategy
// fabraham@tecgraf.puc-rio.br
// Feb 2005

#ifndef SG_BVRENDER
#define SG_BVRENDER

#include <sgbvtree/sgbvtree.h>
#include <sg/strat/interceptor.h>

/**
 * BV Render traversal strategy.
 * This strategy adds bv drawing to rendering strategies.
 */
class SGBVTREEAPI SGBVRender : public SGInterceptor
{
  bool m_drawbv;
  SGShapeBoundingVolumes* m_curr_shape_bvs;
public:
  SGBVRender (SGStrategy *s);
  virtual ~SGBVRender ();
  /**
   * Requests that the shapes bounding volumes be drawn aswell.
   */
  void SetDrawBV (bool f)
  {
    m_drawbv = f;
  }
  bool GetDrawBV ()
  {
    return m_drawbv;
  }
  virtual int Load (SGObject *o);
  virtual int Load (SGColObject *o);
  virtual void Load (SGShape *s);
};

#endif
