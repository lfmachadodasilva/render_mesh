//* colorscale.h
// An active color scale.
// Tecgraf/PUC-Rio
// Mar 2004

#ifndef vis_actelem_colorscale_h
#define vis_actelem_colorscale_h

#include <ufont/fontmanager.h>
#include <sciutils/actelem2dhv.h>
#include <sciutils/colorscale.h>
#include <sciutils/defines.h>

//* *SciActiveElementColorScale* Class
// Represents an active color scale. (32 colors max)
class SCI_API SciActiveElementColorScale : public Sci2DActiveElementHV, public SciColorScaleChangeListener
{
private:
  struct ColorScaleState
  {
    //colorscale
    SciColorScale* cs;
    //title
    char* title;
    float title_w;
    float title_h;
    float title_a;
    float title_d;
    float title_x;
    float title_y;
    //labels
    bool scientific;       // draw color scale values using scientific notation?
    bool autonumberformat; // automatic format for displaying values ?
    char numberformat[32]; // number format used when auto format is disabled
    float labels_x;
    float labels_y;
    float labelfirst_w;
    float labellast_w;
    float labelmax_w;
    float labelmax_h;
    int maxlength;    // current biggest color scale value text length in pixels
    int maxtextwidth; // max acceptable color scale value text width in pixels
    int precision;    // draw color scale values with this precision

    ColorScaleState ();
  };
public:
  SciActiveElementColorScale(const char *name);
  virtual ~SciActiveElementColorScale();
  virtual void SetColorScale(SciColorScale *cs);
  void SetColorScale2 (SciColorScale *cs2);
  SciColorScale * GetColorScale() const
  {
    return m_cs1.cs;
  }
  virtual void SetLineWidth(float value);
  virtual void SetPointSize(float value);
  /**
   * Specifies a new font for the color scale.
   * Returns true if successful (the font family is available
   * and supports the given size and style).
   */
  virtual bool SetFont (const char *font, int size, bool bold, bool italic);
  /**
   * Sets whether the font color for the color scale values must be 
   * automatically determined.
   * If true, a color contrasting to the current background will be chosen.
   * Default: true
   */
  void SetAutoFontColor (bool enabled);
  /**
   * Sets a new font color for the color scale values.
   * This color has effect only if autofontcolor is not enabled.
   */
  void SetFontColor (float r, float g, float b, float a = 1.0f);
  virtual bool SetTitleFont(const char *font, int size, bool bold, bool italic);
  /**
   * Sets whether the font color for the color scale title must be 
   * automatically determined.
   * If true, a color contrasting to the current background will be chosen.
   * Default: true
   */
  void SetTitleAutoFontColor (bool enabled);
  /**
   * Sets a new font color for the color scale title.
   * This color has effect only if autofontcolor is not enabled.
   */
  void SetTitleFontColor (float r, float g, float b, float a = 1.0f);
  virtual void SetDrawableAreaH (float x, float y, float w, float h);
  virtual void SetDrawableAreaV (float x, float y, float w, float h);
  /**
   * Obtains the maximum size of label on horizontal mode (maximum label height).
   */
  float GetTitleAndValuesH ();
  /**
   * Obtains the maximum size of label on vertical mode (maximum label width).
   */
  float GetTitleAndValuesV ();
  bool UsingSecondColorScale () const
  {
    return m_cs2.cs != NULL;
  }
  /**
   * Specifies if only first and last values must be shown (default=false).
   */
  void SetShowOnlyLimitValues (bool onlylimit)
  {
    m_showonly_limitvalues = onlylimit;
  }
  void SetMargin (float rastersize)
  {
    m_margin = rastersize;
  }
  float GetMargin () const
  {
    return m_margin;
  }
  virtual void Drag (float ammountx, float ammounty);
  virtual void SetDragged (float ammount_x, float ammount_y);
  virtual void SetAlphaAdjust(bool v);
  bool IsAlphaAdjustable () const
  {
    return m_setalpha;
  }
  virtual void SetWidth(float w);
  virtual void SetHeight(float h);
  float GetWidth() const
  {
    return IsHorizontal() ? m_hwidth : m_vwidth;
  }
  float GetHeight() const
  {
    return IsHorizontal() ? m_hheight : m_vheight;
  }
  /**
   * Has any scale alpha changed since last asked?
   */
  bool AnyAlphaChanged ()
  {
    bool ret = m_alphaschanged;
    m_alphaschanged = false;
    return ret;
  }
  float GetLineWidth() const
  {
    return m_linewidth;
  }
  float GetPointSize() const
  {
    return m_pointsize;
  }
  /**
   * Returns the clipping coordinates of a rectangle that covers
   * the entire color scale area.
   */
  void GetScaleRect (float *x1, float *y1, float *x2, float *y2);
  /**
   * Returns the clipping coordinates of the area (x,y,width and height) that
   * covers the entire color scale area.
   */
  void GetScaleArea (float *ox, float *oy, float *ow, float *oh);
  /**
   *  Sets whether automatic number format will be used for displaying
   * scale values. Default is true.
   */
  void SetAutoNumberFormat (bool flag)
  {
    m_cs1.autonumberformat = flag;
  }
  /**
   *  Sets number format (as in printf) used when automatic number
   * format is disabled.
   */
  void SetNumberFormat (const char* f);
  void SetNumberFormat2 (const char* f);
  void SetTitle (const char* t);
  void SetTitle2 (const char* t2);
  void SetTitleVertical (bool vertical);
  void UpdateDrawnArea ();
  virtual bool Pick(float x, float y);
  virtual void SetOutDated ();
protected:
  void GetDrawableAreaH (float* x, float* y, float* w, float* h) const
  {
    *x = m_hx;
    *y = m_hy;
    *w = m_hwidth;
    *h = m_hheight;
  }
  void GetDrawableAreaV (float* x, float* y, float* w, float* h) const
  {
    *x = m_vx;
    *y = m_vy;
    *w = m_vwidth;
    *h = m_vheight;
  }
  virtual void cbButton(float x, float y, int mbt, int mst, VglNotifier *ntf);
  virtual void cbButtonOutside(VglNotifier *ntf);
  void doRender();
  float GetColorsPositionXH () const
  {
    return m_colors_x;
  }
  float GetColorsPositionYH () const
  {
    return m_colors_y;
  }
  float GetColorsPositionXV () const
  {
    return m_colors_x;
  }
  float GetColorsPositionYV () const
  {
    return m_colors_y;
  }
  float GetColorsPositionX () const
  {
    if (IsHorizontal())
      return GetColorsPositionXH();
    else
      return GetColorsPositionXV();
  }
  float GetColorsPositionY () const
  {
    if (IsHorizontal())
      return GetColorsPositionYH();
    else
      return GetColorsPositionYV();
  }
  int iscolormarked(int c) const
  {
    return m_sel & (1 << c);
  }
  void SetAlphasChanged ()
  {
    m_alphaschanged = true;
  }
private:
  void SetTitle (ColorScaleState& css, const char* t);
  int GetQuadCount () const;
  void ComputeTexts ();
  float GetX () const;
  float GetY () const;
  void ComputeDimensions ();
  void ComputePositions ();
  void ComputeHorizontalScalePositions ();
  void ComputeVerticalScalePositions ();
  bool HasTitle (ColorScaleState& css) const
  {
    return css.title != NULL && strlen(css.title) > 0;
  }
  void ComputeTitle (ColorScaleState& css);
  void ComputeValues (ColorScaleState& css);
  void DrawBackground ();
  void DrawTitle (ColorScaleState& css);
  void DrawColors ();
  void DrawValues (ColorScaleState& css, bool rightvalues);
  int pickColorIndex(float x, float y);
  void markcolorsv(int from, int to, int value)
  {
    if (to < from)
    {
      int tmp = to;
      to = from;
      from = tmp;
    }
    // clean up garbage
    int v = value & 0x00000001;
    for (int i = from; i <= to; i++)
    {
      if (v)
        m_sel |= 1 << i;
      else
        m_sel &= ( (1 << i) ^ 0xFFFFFFFF );
    }
    SetOutDated();
  }
  void unmarkallcolors()
  {
    m_sel = 0;
    SetOutDated();
  }
  void markallcolors()
  {
    markcolorsv(0, GetQuadCount()-1, 1);
    SetOutDated();
  }
  void markcolor(int c)
  {
    m_sel |= (1 << c);
    SetOutDated();
  }
  void unmarkcolor(int c)
  {
    m_sel &= ( (1 << c) ^ 0xFFFFFFFF );
    SetOutDated();
  }
  void togglecolor(int c)
  {
    int v = (m_sel >> c) & 0x00000001;
    if (v)
      unmarkcolor(c);
    else
      markcolor(c);
  }
  bool anycolormarked() const
  {
    return m_sel != 0;
  }
  void CalcValuesStyleDiscreteIntegers (ColorScaleState& css, int nvalues, float wmax);
  void CalcValuesStyleNonDiscrete (ColorScaleState& css, int nvalues, float wmax);
  void CalcValuesStyle (ColorScaleState& css);
  void PushProjectionMatrix ();
  void PopProjectionMatrix ();
  virtual void RequestRedraw ();
private:
  float m_linewidth;                 // surrounding line thickness
  float m_pointsize;                 // marker size
  float m_bwidth;                    // each color block width
  float m_bheight;                   // each color block height
  int m_sel;                         // selected colors
                                     // LIMIT: 32 colors max
                                     // the least significant bit is the first color
  int m_firstcolor;                  // the beginning of the selection when 'shift' is active
  char *m_font;                      // which font to use
  int m_fontsize;                    // font size
  bool m_fontbold;                   // font is bold?
  bool m_fontitalic;                 // font is italic?
  bool m_auto_font_color;            // is automatic title font color enabled?
  float m_font_color_r;
  float m_font_color_g;
  float m_font_color_b;
  float m_font_color_a;
  char *m_title_font;                // which font to use
  int m_title_fontsize;              // font size
  bool m_title_fontbold;             // font is bold?
  bool m_title_fontitalic;           // font is italic?
  bool m_title_vertical;             // true to draw vertical titles
  bool m_title_auto_font_color;      // is automatic title font color enabled?
  float m_title_font_color_r;
  float m_title_font_color_g;
  float m_title_font_color_b;
  float m_title_font_color_a;
  bool m_setalpha;                   // allow alpha adjust or not
  bool m_alphaschanged;              // did any alpha change ?
  // horizontal mode ([0..1])
  float m_hwidth;                    // colorscale width
  float m_hheight;                   // colorscale height
  float m_hx;                        // colorscale x position
  float m_hy;                        // colorscale y position
  // vertical mode ([0..1])
  float m_vwidth;                    // colorscale width 
  float m_vheight;                   // colorscale height
  float m_vx;                        // colorscale x position
  float m_vy;                        // colorscale y position
  // used size
  float m_width;
  float m_height;
  // internal common elements
  float m_colors_x;
  float m_colors_y;
  float m_colors_w;
  float m_colors_h;
  float m_margin;                    // margin size (raster value)
  int m_gap;                         // gap size (raster value)
  int m_vpx;
  int m_vpy;
  int m_vpw;
  int m_vph;
  //colorscale states
  ColorScaleState m_cs1;
  ColorScaleState m_cs2;
  UFontManager m_fontman;
  bool m_showonly_limitvalues;       // flag to show only color scale's limit labels
  bool m_values_outdated;
};

#endif
