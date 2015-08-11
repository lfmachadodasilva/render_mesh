//* axis.h
// An active IJK axis.
// Tecgraf/PUC-Rio
// Mar 2004

#ifndef SCI_AXIS_H
#define SCI_AXIS_H

#include <sciutils/actelem.h>
#include <sciutils/defines.h>
#include <ufont/fontmanager.h>

//* *SciActiveElementAxis* Class
// Represents an active IJK axis.
class SCI_API SciActiveElementAxis : public SciActiveElement
{
public:
  SciActiveElementAxis(const char *name);

  virtual ~SciActiveElementAxis();

  void SetIAxisColor(float r, float g, float b)
  {
    m_icolor[0] = r;
    m_icolor[1] = g;
    m_icolor[2] = b;
  }

  void SetJAxisColor(float r, float g, float b)
  {
    m_jcolor[0] = r;
    m_jcolor[1] = g;
    m_jcolor[2] = b;
  }

  void SetKAxisColor(float r, float g, float b)
  {
    m_kcolor[0] = r;
    m_kcolor[1] = g;
    m_kcolor[2] = b;
  }

  void GetIAxisColor(float *r, float *g, float *b)
  {
    *r = m_icolor[0];
    *g = m_icolor[1];
    *b = m_icolor[2];
  }

  void GetJAxisColor(float *r, float *g, float *b)
  {
    *r = m_jcolor[0];
    *g = m_jcolor[1];
    *b = m_jcolor[2];
  }

  void GetKAxisColor(float *r, float *g, float *b)
  {
    *r = m_kcolor[0];
    *g = m_kcolor[1];
    *b = m_kcolor[2];
  }

  void SetIAxisLabel (const char* label);

  const char* GetIAxisLabel ();

  void SetJAxisLabel (const char* label);

  const char* GetJAxisLabel ();

  void SetKAxisLabel (const char* label);

  const char* GetKAxisLabel ();
  /**
   * Specifies if the I axis direction must be inverted. Default=false.
   */
  void SetIAxisInverted (bool f)
  {
    m_i_inverted = f;
  }
  /**
   * Specifies if the J axis direction must be inverted. Default=false.
   */
  void SetJAxisInverted (bool f)
  {
    m_j_inverted = f;
  }
  /**
   * Specifies if the K axis direction must be inverted. Default=false.
   */
  void SetKAxisInverted (bool f)
  {
    m_k_inverted = f;
  }
  virtual void SetDrawableArea (float x, float y, float w, float h)
  {
    SetDrawnArea(x,y,w,h);
  }
protected:
  virtual void doRender ();
  virtual bool Pick(float x, float y)
  {
    return false;
  }
private:
  void SetViewport ();
  void RenderAxisLabels (AlgVector vI, AlgVector vJ, AlgVector vK, float model_scale);
  void RenderAxisLines (AlgVector vI, AlgVector vJ, AlgVector vK, float model_scale);
  void RenderAxisCones (AlgVector vI, AlgVector vJ, AlgVector vK, float model_scale);
  void RenderSolidCone (AlgVector pos, float rot_angle, AlgVector rot_vec);
  void RenderAxisCube (AlgVector vI, AlgVector vJ, AlgVector vK);
private:
  UFontManager m_fontman;
  float m_icolor[3];
  float m_jcolor[3];
  float m_kcolor[3];
  char* m_ilabel;
  char* m_jlabel;
  char* m_klabel; 
  GLUquadricObj* m_cone_base_disk;
  bool m_i_inverted;
  bool m_j_inverted;
  bool m_k_inverted;
};

#endif
