// GeographicScale class
// fabraham@tecgraf.puc-rio.br
// Aug 2006
#ifndef SCI_GEOSCALE_H
#define SCI_GEOSCALE_H

#include <sciutils/actelem.h>
#include <sciutils/defines.h>
#include <ufont/fontmanagercompat.h>

/**
 * SciActiveElementGeographicScale class
 * Draws a geographic scale.
 */
class SCI_API SciActiveElementGeographicScale : public SciActiveElement
{
public:
  SciActiveElementGeographicScale(const char *name);
  virtual ~SciActiveElementGeographicScale();
  void SetDrawableArea (float x, float y, float w, float h)
  {
    SetDrawnArea(x,y,w,h);
  }
  void SetScaleHeight (float h)
  {
    m_scale_h = 2*h;
  }
  bool SetFont (const char *font, int size, bool bold, bool italic)
  {
    if (!ufontfm_font_has_style(font,bold,italic))
      return false;
    free(m_font_family);
    m_font_family = strdup(font);
    m_font_size = size;
    m_font_bold = bold;
    m_font_italic = italic;
    return true;
  }
  void SetDistanceUnit (const char *unit)
  {
    free(m_distance_unit);
    if (unit)
      m_distance_unit = strdup(unit);
    else
      m_distance_unit = NULL;
  }
  const char *GetDistanceUnit () const
  {
    return m_distance_unit;
  }
  void SetModelsViewSurface (VglViewSurface *surface)
  {
    m_models_surface = surface;
  }
  VglViewSurface *GetModelsViewSurface () const
  {
    return m_models_surface;
  }
  void SetDistanceScale (float scale)
  {
    m_distance_scale = scale;
  }
  float GetDistanceScale () const
  {
    return m_distance_scale;
  }
protected:
  virtual bool Pick(float x, float y);
  virtual void doRender();
  VglCamera *GetCamera () const
  {
    if (GetModelsViewSurface())
      return GetModelsViewSurface()->GetCamera();
    else if (GetSubCanvas())
      return GetSubCanvas()->GetCamera();
    else if (GetCanvas())
      return GetCanvas()->GetCamera();
    else
      return NULL;
  }
  bool CalcScaleSizeAndArea (float *o_scale_size, float *o_scale_x, float *o_scale_w);
  float CalcSizeOfArea (VglCamera *camera, float x, float y, float width);
  float CalcSizeOfAreaRatio (float orig_scale_size, float width);
  static float ReduceScaleSize (float orig_scale_size);
  static float MinimumScaleSizePercentage ()
  {
    return 0.8f;
  }
  float GetScaleHeight () const
  {
    return m_scale_h;
  }
private:
  static bool GreatestLesserValueWithMostZeroes (
    float value,
    float valuelog10,
    int *io_best_num_zeroes,
    float *o_best_result);
  static int GetNumberOfZeroes (float value, int rounded_log10, float greatest_power_of_10);
  static int RoundedLog10 (float value)
  {
    return (int)ceil(float(log10(value)));
  }
  void GetTextWidths (float orig_scale_size, float *o_first_value_width, float *o_last_value_width, float *o_add_unit_width);
  //void SetViewport ();
  void BeginRender();
  void DrawBackground();
  void DivideInQuads (float scale_w, float scale_h, int num_quads, int invertcolors);
  void DrawQuads(float scale_x, float scale_y, float scale_w, float scale_h);
  void DrawLines(float scale_x, float scale_y, float scale_w, float scale_h);
  void DrawMarkers(float scale_x, float scale_y, float scale_w, float scale_h);
  void DrawValues(float scale_x, float scale_y, float scale_w, float scale_h, float scale_size);
  void DrawUnit(int unit_num_zeroes);
  void EndRender();
  int GetNumberOfQuads () const
  {
    return 4;
  }
  int GetNumberOfSubQuads () const
  {
    return 4;
  }
  void SetFont () const
  {
    if (m_font_family)
      ufontfm_set_font(m_font_family,m_font_size,m_font_bold,m_font_italic);
  }
  VglViewSurface *m_models_surface;
  float m_scale_h;
  float m_distance_scale;
  char *m_distance_unit;
  char *m_font_family;
  int m_font_size;
  bool m_font_bold;
  bool m_font_italic;
};

#endif
