//* color.h
// A color scale.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef SCIUTILS_COLOR_SCALE_H
#define SCIUTILS_COLOR_SCALE_H

#include "defines.h"
#include <ds/defines.h>

class SciColorScaleTex;
class SciActiveElementColorScale;

// 'SciColor' Type
// Represents a system color
typedef struct
{
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char alpha;
} SciColor;

class SCIH_API SciColorScaleChangeListener
{
public:
  virtual ~SciColorScaleChangeListener ()
  {
  }
  virtual void SetOutDated () = 0;
};

// 'SciColorScale' Class
// Represents a color scale.
class SCI_API SciColorScale
{
public:
  enum Mode {
    // Default mode.
    // Each color represents the range between two consecutive values.
    MODE_ISOVALUES = 0,
    // Each color represents a single discrete value.
    // Each value may have a text string associated to it.
    MODE_DISCRETE,
    // Each value is associated to a color in the continuous space.
    // Colors are interpolated between two consecutive values.
    MODE_CONTINUOUS,
    // Same was MODE_ISOVALUES, but colors are interpolated. Used only on Geresim.
    MODE_GCONTINUOUS
  };

private:
  float *ColorValues;

  int m_num_colors;
  bool m_has_transparent_colors;

  int m_num_dvalues; // number of discrete values: most of the times its the same as num_colors

  // linear interpolation toggle
  // uses binary search if it's disabled
  bool bLinearInterpolation;

  // array of value texts
  char **pValueTexts;
  // color mapping array: used when scale is discrete
  // indexed by the value index, contains the corresponding color index
  int *m_dvaluecolor;

  // the smallest interval of the color scale
  float fSmallestRange;

  Mode m_mode;

  void reset (int size, int ndvalues = -1, int *cmap = 0);

public:
    //* Constructor
    // Builds a color scale given it's size.
    // Adjusts all colors to {0, 0, 0, 255} and value[i] to i, for 0 <= i <= size.
    // Linear interpolation is activated.
  SciColorScale (int size);
  virtual ~SciColorScale ();

  /**
   * Copies all settings from another colorscale object.
   * Any listeners set to the other object will not be copied.
   */
  void CopyFrom (const SciColorScale* sci);

  SciColorScaleChangeListener* GetListener () const
  {
    return m_listener;
  }
  SciColorScaleTex* GetColorScaleTex () const;
    //* Amount of colors query
    // Returns the number of colors.
  int GetNumberOfColors () const
  {
    return m_num_colors;
  }

  int GetNumberOfValues () const
  {
    switch (m_mode) {
      case MODE_ISOVALUES:
        return m_num_colors + 1;
      case MODE_DISCRETE:
        return GetNumberOfDiscreteValues();
      case MODE_CONTINUOUS:
        return m_num_colors;
      case MODE_GCONTINUOUS:
        return m_num_colors + 1;
      default:
        return 0;
    }
  }

  bool IsValidValueIndex (int i) const
  {
    return (i >= 0 && i < GetNumberOfValues());
  }

  int GetNumberOfDiscreteValues () const
  {
    return IsDiscrete() ? m_num_dvalues : 0;
  }

  bool HasTransparentColors () const
  {
    return m_has_transparent_colors;
  }

    //* Color adjust
    // Adjusts the ith color to the specified value.
    // Returns zero if the index is invalid, non zero otherwise.
  int SetColor (int i, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha = 255);

    //* Color alpha adjust
    // Adjusts the alpha value of the ith color, maintaining it's RGB current components.
  int SetAlpha (int i, unsigned char alpha);

  /**
   * Specifies a global scale value for all alphas, ranging from 0 to 1.
   */
  void SetGlobalAlphaScale (float s);

  void SetOutofRangeColor (unsigned char r, unsigned char g, unsigned char b, unsigned char a=255);
  void SetNoOutOfRangeColor ();

  /**
   * Specifies the scale mode:
   * - MODE_ISOVALUES: each color represents a range of consecutive values (default);
   * - MODE_DISCRETE: each color represents a single discrete value.
   * - MODE_CONTINUOUS: each value is associated to a color in the continuous color space.
   *                    Colors are interpolated between two consecutive colors.
   */
  void SetMode (Mode mode);

  Mode GetMode () const { return m_mode; }

  /**
   * Turns on/off color scale contour (iso-lines).
   */
  void SetContour (bool flag);

    //* Value adjust
    // Adjusts the ith value.
    // Returns zero if the index is invalid, non zero otherwise.
    // Disables linear interpolation and enables binary search.
  int SetValue (int i, float value);

    //* Value text adjust
    // Adjusts the text of the ith value
    // Setting this value to NULL displays the numerical value of the element.
    // Returns zero if the index is invalid, non zero otherwise.
  int SetValueText (int i, const char *text);

    //* Value limits adjust
    // Adjusts the whole color scale values by giving it's minimum and maximum.
    // Enables linear interpolation and disables binary search.
    // Sets the scale to isovalues mode (if resetmode == true).
  int SetValueLimits (float vmin, float vmax, bool resetmode = true);
  void GetValueLimits (float* vmin, float *vmax);

    //* Discrete mode query
  bool IsDiscrete () const
  {
    return m_mode == MODE_DISCRETE;
  }

    // COLOCAR COMENTARIO!
  int GetValueRangeIndex (float v);
  int GetValueIndex (float v);

    //* Value query
    // Returns the value given it's index.
    // Returns -1 if the index is invalid.
  float GetValue (int i);

    //* Value text query
    // Returns the value text given it's index.
    // Returns NULL if the index is invalid.
  const char * GetValueText (int i);

    //* Smallest range query
    // Returns the smallest interval of the color scale.
  float GetSmallestRange () const
  {
    return fSmallestRange;
  }

    //* Index query
    // Returns the color scale index according to a value.
    // Returns -1 if the value is invalid (for instance, out of range)
  DS_DEPRECATED int GetValueColor (float p)
  {
    return (int)GetValueColorF(p);
  }

  void GetValueColor (float p,
                      unsigned char* r,
                      unsigned char* g,
                      unsigned char* b,
                      unsigned char* a);

    //* Discrete value color index
    // Returns the color scale index of the ith discrete value (when in discrete mode).
    // Returns -1 if the value is invalid (for instance, out of range)
  int GetDiscreteValueColor (int i);

  void GetColor (int i, int *r, int *g, int *b, int *a);
  /**
   * Same as 'GetColor', but returns the alpha value already multiplied by the global
   * alpha scale setting.
   */
  void GetColorWithAlphaScale (int i, int *r, int *g, int *b, int *a);

    //* Scale reset
    // Resets the structure, given a new size.
    // 'ndvalues' equals size, if not set
    // 'cmap' is a color mapping array: cmap[0] contains the color index
    // to be assigned to the first discrete value
  void Reset (int size) { reset(size); };
  void Reset (int size, int ndvalues, int *cmap) { reset(size, ndvalues, cmap); }
  void LoadTexture (unsigned int unit = 0);
  void UnloadTexture (unsigned int unit = 0);
  void SetOutDated ();
  void SetChangeListener (SciColorScaleChangeListener* listener)
  {
    m_listener = listener;
  }

  void SetDistributionValuesType (int type);
  void UpdateScaleValues ();
private:
  float GetValueColorF (float p);
private:
  SciColorScaleChangeListener *m_listener;
  SciColorScaleTex *m_tex;
};

#endif
