// colorcale_tex.h
// 18 Jun 2007

#ifndef SCI_COLORSCALE_TEX_H
#define SCI_COLORSCALE_TEX_H

#include <assert.h>
#include "defines.h"

class SciColorScale;

class SCI_API SciColorScaleTex
{
  typedef unsigned char uchar;
  typedef unsigned int uint;
  struct ColorStatus {
    bool locked;
    bool selected;
  };
public:
  struct Color {
    uchar r, g, b, a;
  };
  enum Method {
    NEAREST,
    LINEAR,
    CUBIC
  }; 

  enum DistrValuesType {
    TEX_EXPONENTIAL = 0,
    TEX_LINEAR,    //default
    TEX_LOGARITHM
  };

  enum Filter {
    FILTER_NEAREST = 0,
    FILTER_LINEAR
  };

  SciColorScaleTex (int texdim=-1);
  ~SciColorScaleTex ();

  void SetLimit (float vmin, float vmax);
  void GetLimit (float* vmin, float* vmax) const
  {
    *vmin = m_vmin;
    *vmax = m_vmax;
  }
  void SetNumberOfColors (int ncolor);
  void SetColor (int i, uchar r, uchar g, uchar b, uchar a=255);
  void SetOutofRangeColor (uchar r, uchar g, uchar b, uchar a=255);
  void SetNoOutOfRangeColor ();
  bool GetPaintOutOfRange () const
  {
    return m_paintoutofrange;
  }
  void GetOutofRangeColor (uchar *r, uchar *g, uchar *b, uchar *a)
  {
    *r = (uchar)(m_outofrangecolor[0]*255.0f);
    *g = (uchar)(m_outofrangecolor[1]*255.0f);
    *b = (uchar)(m_outofrangecolor[2]*255.0f);
    *a = (uchar)(m_outofrangecolor[3]*255.0f);
  }
  void SetColors (uchar* color);
  void SetSelectedAlpha (uchar a);
  void SetAlpha (int i, uchar a);
  void SetGlobalAlphaScale (float s);
  float GetGlobalAlphaScale () const
  {
    return m_global_alpha_scale;
  }
  void SetInterpolation (Method meth);
  void SetContinuous (bool flag);
  void SetContour (bool flag);
  void SetLocked (int i, bool locked);
  void SetSelected (int i, bool selected);
  void SetAllAlphaMax ();
  void SetAllAlphaMin ();
  void SetAllAlphaHalf ();
  void SetColorScale (SciColorScale *cs)
  {
    m_cs = cs;
  }
  void SetOutDated ();
  /**
   * Copies all settings from another colorscaletex object.
   */
  void CopyFrom (SciColorScaleTex* cst);
  /**
   * Specifies automatic texture coordinate generation.
   * 'mode' can be any of the texture coordinate generation allowed by OpenGL or
   * 0 to disable.
   * If the mode expects a generation plane, this is specified by values 'a',
   * 'b', 'c' and 'd'.
   * The texture matrix mapping the minimum value to 0 and the maximum value to 1
   * still applies (see SetLimit).
   */
  void SetTexGen (int mode, float a=0, float b=0, float c=0, float d=0);
  unsigned int GetTexGenMode () const
  {
    return m_genmode;
  }
  void GetTexGenPlane (float *a, float *b, float *c, float *d) const
  {
    *a = m_genplane[0];
    *b = m_genplane[1];
    *c = m_genplane[2];
    *d = m_genplane[3];
  }
  int GetDimension () const
  {
    return m_texdim;
  }

  int GetNumberOfColors () const
  {
    return m_ncolor;
  }
  Method GetInterpolation () const
  {
    return m_method;
  }

  bool GetContinuous () const
  {
    return m_continuous;
  }

  bool GetContour () const
  {
    return m_contour;
  }

  bool IsLocked (int i) const
  {
    assert(i<m_ncolor);
    return m_status[i].locked;
  }
  bool IsSelected (int i) const
  {
    assert(i<m_ncolor);
    return m_status[i].selected;
  }
  // Get number of subdivisions needed for volume rendering.
  // The amount of samples (odd number) between control points
  // can be provided.
  int GetNumberOfSubdivisions (int nsamples = 1)
  {
    return (1+nsamples) * (m_continuous && m_ncolor > 1 ? (m_ncolor-1) : (m_ncolor));
  }

  Color GetColor (int i);
  /**
   * Same as 'GetColor', but returns the alpha value already multiplied by the global
   * alpha scale setting.
   */
  Color GetColorWithAlphaScale (int i);
  /**
   * Obtains the texture color at index 'i'.
   * The alpha value comes multiplied by the global
   * alpha scale setting if 'withalphascale' is true.
   */
  Color GetTexColor (int i, bool withalphascale);

  unsigned int GetTextureId ();

  void ComputeTex ();
  void LoadTexture (unsigned int unit = 0);
  void UnloadTexture (unsigned int unit = 0);
  uchar* GetTexture (int level=0);
  void Draw (bool vertical=false);
  void DrawOutline (bool vertical=false);
  void DrawBackground (bool alpha_line=true);
  void DrawAlphaLine ();
  void GetQuadCoord (float* xmin, float* ymin, float* xmax, float* ymax);

  bool LoadAlpha (const char* filename);
  /**
   * Specifies if texture should be modulated (f=true) with current color/material
   * or if it should replace the current color (f=false).
   * Default: modulate=true.
   */
  void SetModulate (bool f)
  {
    m_modulate = f;
  }
  /**
   * Obtains texture modulated flag (see SetModulate).
   * Default: modulate=true.
   */
  bool GetModulate () const
  {
    return m_modulate;
  }
  /**
   * Sets the texture magnification filter.
   * Default: FILTER_LINEAR
   */
  void SetMagnificationFilter (Filter param);
  /**
   * Sets the texture minification filter.
   * Default: FILTER_LINEAR
   */
  void SetMinificationFilter (Filter param);

  void SetDistributionValuesType (int t);
  float GetRatio ();
  /**
   * Obtains the scale and offset for the construction of a texture coordinate
   * matrix. This matrix will transform any scalar value into the correct texture
   * coordinate for texture access.
   */
  void ComputeTextureMatrixScaleAndOffset (float* pscale, float* poffset);
private:
  bool m_updated;
  bool m_glupdated;
  uint m_texid;
  int m_texdim;
  int m_nlevel;
  Color* m_tex;
  int m_ncolor;
  Color* m_color;
  ColorStatus* m_status;
  Method m_method;
  float m_outofrangecolor[4];
  bool m_paintoutofrange;
  bool m_continuous;
  bool m_contour;
  float m_vmin; 
  float m_vmax;
  SciColorScale *m_cs;
  unsigned int m_genmode;
  float m_genplane[4];
  float m_global_alpha_scale;
  float m_ratio;
  int m_distributiontype;
  bool m_modulate;
  Filter m_mag_filter;
  Filter m_min_filter;

  int TexIndex (float i, int texdim, bool forceDiscrete = false);  // control point tex index
  float TexIndexInv (int i, bool forceDiscrete = false);
  int TexContourIndex (int i);
  void Interpolate (int from, int to, int texdim, Color* tex);
  void ComputeRGB (int level);
  void ComputeAlpha (int level);

  // Drawing functions
  void DrawUpperBackground ();
};

#endif
