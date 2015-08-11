// frustumpred.h
// Tecgraf/PUC-Rio
// gustavo@tecgraf.puc-rio.br
// vbarata@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Mar 2010

#ifndef VGL_VIEW_PARAMS_H
#define VGL_VIEW_PARAMS_H

#include <alg/vector.h>
#include <vgl/frustum.h>
#include <float.h>
#include <limits.h>
#include <string.h>

class VglViewParameters
{
public:
  AlgMatrix viewmatrix;
  AlgMatrix projmatrix;
  int viewport[4];
  double time;
public:
  VglViewParameters ()
  : viewmatrix(AlgMatrix::GetIdentity())
  , projmatrix(AlgMatrix::GetIdentity())
  , position(FLT_MAX, FLT_MAX, FLT_MAX)
  , viewprojmatrix(AlgMatrix::GetIdentity())
  , frustum(viewprojmatrix)
  , m_fru_updated(false)
  {
    memset(this->viewport, INT_MAX, sizeof(this->viewport));
  }
  VglViewParameters (const VglViewParameters& vp)
  : viewmatrix(AlgMatrix::GetIdentity())
  , projmatrix(AlgMatrix::GetIdentity())
  , position(FLT_MAX, FLT_MAX, FLT_MAX)
  , viewprojmatrix(AlgMatrix::GetIdentity())
  , frustum(viewprojmatrix)
  , m_fru_updated(false)
  {
    *this = vp;
  }
  void Update (const AlgMatrix& pm, const AlgMatrix& vm, const int* viewport)
  {
    this->projmatrix = pm;
    this->viewmatrix = vm;
    memcpy(this->viewport, viewport, sizeof(this->viewport));
    SetOutdated();
  }
  VglFrustum& GetFrustum ()
  {
    Update();
    return this->frustum;
  }
  const AlgVector& GetPosition ()
  {
    Update();
    return this->position;
  }
  const AlgMatrix& GetViewProjMatrix ()
  {
    Update();
    return this->viewprojmatrix;
  }
  void operator = (const VglViewParameters& vp)
  {
    this->projmatrix = vp.projmatrix;
    this->viewmatrix = vp.viewmatrix;
    this->time = vp.time;
    memcpy(this->viewport, vp.viewport, sizeof(this->viewport));
    SetOutdated();
  }
  bool operator == (VglViewParameters& vp)
  {
    Update();
    vp.Update();
    return viewprojmatrix == vp.viewprojmatrix;
  }
  bool operator != (VglViewParameters& vp)
  {
    Update();
    vp.Update();
    return viewprojmatrix != vp.viewprojmatrix;
  }
  void Update ()
  {
    if (!m_fru_updated) {
      this->viewprojmatrix.SetMatrix(this->projmatrix);
      this->viewprojmatrix.Accum(this->viewmatrix);
      this->frustum.Update(this->viewprojmatrix);
      this->position = this->frustum.GetEyePos();
      m_fru_updated = true;
    }
  }
  void SetOutdated ()
  {
    m_fru_updated = false;
  }
private:
  AlgVector position;
  AlgMatrix viewprojmatrix;
  VglFrustum frustum;
  bool m_fru_updated;
};

/**
 * Input:
 *
 * new_vp:  new frame parameters.
 * curr_vp: previous frame parameters.
 * first:   if this is the first frame.
 *
 * Output:
 * Return value: true if view parameters changed, false otherwise.
 * pred_vp:      predicted frame parameters (extrapolated).
 */
bool VglPredictView (VglViewParameters& new_vp,
                     VglViewParameters& curr_vp, 
                     bool first,
                     VglViewParameters& pred_vp);

#endif

