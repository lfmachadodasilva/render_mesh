#ifndef VGL_MODELROTATION_H
#define VGL_MODELROTATION_H

#include "rotation.h"
#include <float.h>

class VGL_API VglModelRotation : public VglRotation
{
public:

  VglModelRotation ()
  : m_minanglex(0.0f)
  , m_maxanglex(90.0f)
  , m_minheight(0.0f)
  , m_maxheight(FLT_MAX/2)
  , m_angconstrain(false)
  , m_hgtconstrain(false)
  {
  }
  ~VglModelRotation ()
  {
  }
  bool IsConstrainingToUpperHemisphere () const // DEPRECATED
  {
    return (m_angconstrain && m_minanglex == 0.0f && m_maxanglex == 90.0f);
  }
  void ConstrainToUpperHemisphere ()
  {
    SetConstrainAngle(0.0f, 90.0f);
  }
  void SetConstrainingToUpperHemisphere (bool f) // DEPRECATED
  {
    if (f)
      SetConstrainAngle(0.0f, 90.0f);
    else
      SetConstrainAngle(false);
  }
  bool IsConstrainingAngle () const
  {
    return m_angconstrain;
  }
  bool IsConstrainingHeight () const
  {
    return m_hgtconstrain;
  }
  void SetConstrainAngle (bool state)
  {
    m_angconstrain = state;
  }
  void SetConstrainHeight (bool state)
  {
    m_hgtconstrain = state;
  }
  void GetConstrainAngle (float* minanglexdeg, float* maxanglexdeg)
  {
    *minanglexdeg = m_minanglex;
    *maxanglexdeg = m_maxanglex;
  }
  void SetConstrainAngle (float minanglexdeg, float maxanglexdeg)
  {
    m_minanglex = minanglexdeg;
    m_maxanglex = maxanglexdeg;
    m_angconstrain = true;
  }
  void SetConstrainHeight (float minheight, float maxheight)
  {
    m_minheight = minheight;
    m_maxheight = maxheight;
    m_hgtconstrain = true;
  }
  void GetConstrainHeight (float* minheight, float* maxheight)
  {
    *minheight = m_minheight;
    *maxheight = m_maxheight;
  }

  void BeginRotation (VglCamera *camera);
  /**
   * Specifies the beggining of a model rotation, given a rotation
   * center 'rcenter' (model coordinates).
   */
  void BeginRotation (VglCamera *camera, const AlgVector &rcenter);
  void RepeatRotation (VglCamera *camera);

private:

  bool HadRotationCenter () const
  {
    return m_lasthasrcenter;
  }
  const AlgVector& GetLastRotationCenter() const
  {
    return m_lastrcenter;
  }
  float GetLastRotationX () const
  {
    return m_lastanglex;
  }
  float GetLastRotationY () const
  {
    return m_lastangley;
  }

  void RotateX (float angle);
  void RotateY (float angle, const AlgVector &axis);
  float ObtainRotatedAngle () const;
  bool ApplyConstrainAngle (float& angle);
  bool ApplyConstrainHeight (float& angle);

private:

  VglCamera *m_camera;
  AlgVector m_rcenter;
  AlgVector m_rcentereye;
  bool m_hasrcenter;
  AlgVector m_lastaxisy;
  AlgVector m_lastrcenter;
  bool m_lasthasrcenter;
  float m_lastanglex;
  float m_lastangley;
  float m_minanglex;
  float m_maxanglex;
  float m_minheight;
  float m_maxheight;
  bool m_angconstrain;
  bool m_hgtconstrain;

};

#endif

