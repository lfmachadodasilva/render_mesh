// Material class
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_MATERIAL_H
#define SG_MATERIAL_H

#include <sg/state.h>

class SG_API SGMaterial : public SGState
{
  enum {
    AMBIENT=1,
    DIFFUSE=2,
    SPECULAR=4,
    EMISSION=8,
    SHININESS=16,
    AMBIENTDIFFUSE=32
  };

  int   m_flag;
  float m_amb[4];
  float m_dif[4];
  float m_spe[4];
  float m_emi[4];
  float m_shi;
public:
  static const char* CLASSNAME () { return "Material"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  SGMaterial ();
  SGMaterial (float red, float green, float blue, float alpha=1.0f);
  virtual ~SGMaterial ()
  {
  }
  void SetAmbient (float red, float green, float blue, float alpha=1.0f);
  void SetDiffuse (float red, float green, float blue, float alpha=1.0f);
  void SetSpecular (float red, float green, float blue, float alpha=1.0f);
  void SetEmission (float red, float green, float blue, float alpha=1.0f);
  void GetAmbient (float * red, float * green, float * blue, float * alpha) const
  {
    *red   = m_amb[0];
    *green = m_amb[1];
    *blue  = m_amb[2];
    *alpha = m_amb[3];
  }
  void GetDiffuse (float * red, float * green, float * blue, float * alpha) const
  {
    *red   = m_dif[0];
    *green = m_dif[1];
    *blue  = m_dif[2];
    *alpha = m_dif[3];
  }
  void GetSpecular (float * red, float * green, float * blue, float * alpha) const
  {
    *red   = m_spe[0];
    *green = m_spe[1];
    *blue  = m_spe[2];
    *alpha = m_spe[3];
  }
  void GetEmission (float * red, float * green, float * blue, float * alpha) const
  {
    *red   = m_emi[0];
    *green = m_emi[1];
    *blue  = m_emi[2];
    *alpha = m_emi[3];
  }
  void SetShininess (float value );
  float GetShininess () const
  {
    return m_shi;
  }
  virtual void Load ();
  virtual void Unload ();
  virtual bool IsOpaque () const;
  virtual void Write (UtlWriter* writer);
};

#endif
