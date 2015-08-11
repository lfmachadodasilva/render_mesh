//* bubblecolorscale.h
// An active color scale for bubble map.
// Tecgraf/PUC-Rio
// Oct 2006

#ifndef vis_actelem_bubblecolorscale_h
#define vis_actelem_bubblecolorscale_h

#include <sciutils/actelem2dhv.h>
#include <sciutils/colorscale.h>
#include <sciutils/defines.h>

//* *SciActiveBubbleColorScale* Class
class SCI_API SciActiveBubbleColorScale : public Sci2DActiveElementHV
{
public:
  SciActiveBubbleColorScale(const char* name);
  virtual ~SciActiveBubbleColorScale();

  void SetNumberOfProperties(int p);
  void SetPropertyName( int prop, const char* name );
  void SetPropertyColor( int prop, unsigned char color[3] );
  void SetPropertyMaxValue( int prop, float v );

  virtual void SetDrawableAreaH (float x, float y, float w, float h);
  virtual void SetDrawableAreaV (float x, float y, float w, float h);

  /**
   * Method that does the actual render of the element.
   * Must be defined in all derived classes.
   */
  virtual void doRender();
  /**
   * Pick method.
   * Returns true if given normalized coordinate lies inside the element,
   * false otherwise.
   */
  virtual bool Pick(float x, float y)
  {
    return false;
  }
  
private:
  int m_bubbleMapNProperties; // number of properties on a bubble (max = 4)
  char* m_bubbleMapPropertiesName[4];
  float m_bubbleMapMaxWellPropertiesValues[4];
  unsigned char m_bubbleMapPropertiesColor[12];
  GLUquadricObj *d_quadric;
};

#endif
