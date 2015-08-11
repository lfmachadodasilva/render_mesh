// gridtex.h
// 30 Aug 2007

#ifndef UGL_GRIDTEX_H
#define UGL_GRIDTEX_H

#include <GL/glew.h>
#include <ugl/defines.h>

class UGL_API UGLGridTex
{
public:
  UGLGridTex (int maxdim=-1);
  ~UGLGridTex ();
  void SetThickness (float value);
  float GetThickness () const
  {
    return m_thickness;
  }
  void SetIntensityAttenuation (bool flag);
  /**
   * Obtains the intensity attenuation flag.
   */
  bool GetIntensityAttenuation () const
  {
    return m_intensityatt;
  }
  void SetThicknessAttenuation (bool flag);
  void SetAttenuationLimits (float zstart, float zend);

  void SetSingleColorMode (bool flag);
  bool GetSingleColorMode () const
  {
    return m_singlecolor;
  }
  /**
   * Specifies if saturation must be avoided, as described in the paper.
   * Default: true
   */
  void SetAvoidSaturation (bool flag);
  void SetOpaqueGridMode (bool flag);
  void SetColor (unsigned char r, unsigned char g, unsigned char b);
  void GetColor (unsigned char *r, unsigned char *g, unsigned char *b) const
  {
    *r = m_r;
    *g = m_g;
    *b = m_b;
  }
  void SetAutoGen (int unitindex, int mode, float a=0, float b=0, float c=0, float d=0);
  /**
   * Specifies a texture matrix for the unit of index 'unitindex',
   * where 'unit0' passed to Load is unit 0, 'unit1' is unit 1
   * and so on.
   */
  void SetTextureMatrix (int unitindex, double* m);
  /**
   * Resets the texture matrix for the unit of index 'unitindex',
   * where 'unit0' passed to Load is unit 0, 'unit1' is unit 1
   * and so on.
   */
  void ResetTextureMatrix (int unitindex);
  /**
   * Loads the texture on texture unit 'unit0'.
   * If 'defaultunit' is greater or equal to 0,
   * sets this unit as the current unit after loading.
   */
  void Load (int unit0, int defaultunit);
  /**
   * Loads the texture on texture unit 'unit0' and 'unit1'.
   * If 'defaultunit' is greater or equal to 0,
   * sets this unit as the current unit after loading.
   */
  void Load (int unit0, int unit1, int defaultunit);
  /**
   * Loads the texture on texture units 'unit0', 'unit1' and 'unit2'.
   * If 'defaultunit' is greater or equal to 0,
   * sets this unit as the current unit after loading.
   */
  void Load (int unit0, int unit1, int unit2, int defaultunit);
  /**
   * Unloads the texture.
   */
  void Unload ();
  static bool IsSupported ();
private:
  struct Color {
    unsigned char r, g, b, a;
    Color (unsigned char ir, unsigned char ig, unsigned char ib, unsigned char ia=255)
    : r(ir), g(ig), b(ib), a(ia)
    {
    }
  };
  int m_maxdim;
  int m_target;
  int m_maxlevel;
  bool m_updated;
  bool m_singlecolor;
  bool m_intensityatt;
  bool m_thicknessatt;
  unsigned char m_r, m_g, m_b;
  float m_thickness;
  float m_zstart, m_zend;
  GLuint m_texid;
  Color** m_image;
  unsigned int m_genmode[3];
  float m_genplane[3][4];
  double m_texmatrix[3][16];
  bool m_hastexmatrix[3];
  int m_loaded_units[3];
  bool m_opaque_grid;
  bool m_avoid_saturation;

  void UpdateTarget ();
  void ComputeTexture ();
  void ComputeImage (int level, const Color& c);
  void ComputeAttenuation (int level, const Color& c);
  void FillGrid (int dim, Color* img, const Color& c, float attenuation);
  void UpdateTexture ();
  void LoadUnit (int unitindex, bool first);
  void UnloadUnit (int unitindex);
  void LoadAllUnits (int defaultunit);
  void UnloadAllUnits ();
  void LoadAutoGen (int unitindex);
  void LoadTextureMatrix (int unitindex);
};

#endif
