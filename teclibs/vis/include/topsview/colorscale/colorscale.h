//* color.h
// A color scale.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef TPV_COLOR_SCALE_H
#define TPV_COLOR_SCALE_H

#include <topsview/defines.h>

struct TpvColor
{
  float r, g, b, a;
  TpvColor() {}
  TpvColor(float r, float g, float b, float a = 1) 
    : r(r), g(g), b(b), a(a) 
  {}
};

class TPV_API TpvColorScale
{
private:
  int        m_ncolors; 
  TpvColor*  m_colors;
  int        m_nvalues;
  float*     m_values; // size: ncolors+1
  int        m_interp_mode;
  int        m_discrete_value;

  // linear interpolation toggle
  // uses binary search if it's disabled
  bool m_is_uniform;

  // Discrete values
  bool m_is_discrete;

  // the smallest interval of the color scale
  float m_smallest_range;

public:
  enum InterpMode {
    INTERP_CONSTANT = 0,
    INTERP_DISCRETE,
    INTERP_LINEAR
  };

  /**
      Builds a color scale given the number of colors.
      Values are mapped to the interval [0, 1] and colors are
    set to (0,0,0,1).
      Default interpolation mode is INTERP_CONSTANT.
  */
  TpvColorScale(int ncolors = 16);

  TpvColorScale(const TpvColorScale& c);

  ~TpvColorScale();

  /**
      Resets the color scale to the given size (number of colors).
    Values are mapped to the interval [0, 1] and colors are
    set to (0,0,0,1).
  */
  void Reset(int ncolors);

  /**
      Resizes color scale to the given number of colors.
    This method will interpolate colors and values.
  */
  void Resize(int ncolors);

  /**
      Sets one of the color interpolation modes defined in InterpMode.
      Resets color scale to fit mode requirements.
  */
  void SetInterpolationMode(int m);

  /**
      Gets the current interpolation mode.
  */
  int GetInterpolationMode() const { return m_interp_mode; }

  /** 
      Returns the number of colors.
  */
  int GetNumberOfColors() const { return m_ncolors; }
  
  /**
      Sets the color at the given index.
      Returns zero if the index is invalid, non zero otherwise.
  */
  int SetColor(int i, float r, float g, float b, float a=1);

  /**
      Sets the array of color values. 
      The parameter ncolors must be equal to the number of colors
    of the color scale. The size of color_array must be 4*ncolors*sizeof(float).
      Returns zero if the size doens't match m_colors's size , non zero otherwise.
  */
  int SetColor(int ncolors, float* color_array);

  /**
      Sets the alpha value of the given index.
  */
  int SetAlpha(int i, float alpha);
  
  /**
      Returns the color at the given index, or NULL if the index is invalid.
  */
  TpvColor* GetColor(int i);
  
  /**
      Returns the color at the given index.
  */
  void GetColor(int i, float* r, float* g, float* b, float* a);

  /**
     Returns the alpha value at the given index.
  */
  float GetAlpha(int i);

  /**
      Returns the number of values. If color scale is discrete,
    (nvalues == ncolors), else (nvalues == ncolors + 1).
  */
  int GetNumberOfValues() const { return m_nvalues; }

  /**
      Sets the value at the given index.
      Returns zero if the index is invalid, non zero otherwise.
      Disables direct indexing and enables binary search.
  */
  int SetValue(int i, float value);

  /**
      Returns the value at the given index, or -1 if index is invalid.
  */
  float GetValue(int i);

  /**
      Adjusts the whole color scale values by giving it's minimum and maximum.
      Enables linear interpolation and disables binary search.
      Disables discrete mode.
  */
  void SetValueLimits(float vmin, float vmax);

  /**
      Returns the minimum and maximum values of the scale.
  */
  void GetValueLimits(float* vmin, float* vmax);

  /**
      Returns the smallest interval of the color scale.
  */
  float GetSmallestRange() const { return m_smallest_range; }

  /**
      Returns the color index associated to the given value.
      Returns -1 if the value is invalid (for instance, out of range).
      This method uses binary search to look for the color if color scale 
    is not uniform.
  */
  int GetValueColor(float p);

  /**
      Maps the given value to the respective color in the colorscale.
      Color interpolation is performed when needed.
  */
  void MapValueToColor(float v, float* r, float* g, float* b, float* a);

  /**
    @deprecated
  */
  void SetDiscreteMode()
  {
    m_interp_mode = INTERP_DISCRETE;
    m_is_uniform = false;
  }

  /**
    @deprecated
  */
  void SetUniformMode()
  {
    m_interp_mode = INTERP_CONSTANT;
    m_is_uniform = true;
  }

  /**
      Returns whether color scale is uniform. 
      This is an optimized state of the color.
      The color scale is uniform when the intermediate values have been 
    automatically generated. This occurs, for instance, when only limits are 
    given. So the color scale generates the intermediate values.       
  */
  bool IsUniform() const
  {
    return m_is_uniform;
  }

  /**
    @deprecated
  */
  bool IsDiscrete() const
  {
    return m_interp_mode == INTERP_DISCRETE;
  }

  /**
    @deprecated
  */
  void SetNumDiscreteValues(int value)
  {
    m_discrete_value = value;
    if (IsDiscrete())
      m_nvalues = m_discrete_value;
  }

  /**
    @deprecated
  */
  int GetNumDiscreteValues(void) const
  {
    return m_discrete_value;
  }

  /**
      Creates a texture array with the the color scale resampled
    to the given size.
      The array is allocated by this method (using malloc) and 
    returned in the tex parameter.
  */
  /*deprecated*/  
  void CreateTexArray(int size, float** tex);
  
  /**
      Creates a texture array with the the color scale resampled
    to the given size.
      Put the results in tex.
  */  
  void GetTexArray(int size, float* tex);  

  /**
  Returns the colors as a float array.
  */  
  const float* GetColors() const
  {
    return (float*)m_colors;
  }
};

#endif
