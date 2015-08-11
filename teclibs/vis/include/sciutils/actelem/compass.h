// Compass class
// fabraham@tecgraf.puc-rio.br
// Jan 2006
#ifndef SCI_COMPASS_H
#define SCI_COMPASS_H

#include <sciutils/actelem.h>
#include <sciutils/defines.h>
#include <alg/vector.h>

class UGLTexture;

/**
 * SciActiveElementCompass class
 * Draws a compass in viewports bottom-right corner.
 */
class SCI_API SciActiveElementCompass : public SciActiveElement
{
  AlgVector m_north;
  UGLTexture *m_texture;
  void SetViewport ();
public:
  SciActiveElementCompass(const char *name);
  virtual ~SciActiveElementCompass();
  /**
   * Specifies the application's north (world coordinates).
   */
  virtual void SetNorth (float x, float y, float z)
  {
    m_north.Set(x,y,z);
  }
  virtual void SetDrawableArea (float x, float y, float w, float h)
  {
    SetDrawnArea(x,y,w,h);
  }
  /**
   * Specifies the texture files for the compass' quad.
   * Returns true if successful, false otherwise.
   */
  virtual bool SetFilenames (const char *rgbfile, const char *alphafile);
  /**
   * Return texture dimensions.
   * Useful for compass resizing.
   */
  void GetTextureDimensions (int* w, int* h);
protected:
  virtual bool Pick(float x, float y)
  {
    return false;
  }
  virtual void doRender();
};

#endif
