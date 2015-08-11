// Message class
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Jul 2002

#ifndef UFONT_MESSAGE_H
#define UFONT_MESSAGE_H

#include "defines.h"
#include <stdio.h>

class UFONT_API UFontMessage
{
public:
  enum RenderMode {
    PIXMAP_FONT = 0,
    BITMAP_FONT,
    TEXTURE_FONT,
    EXTRUDED_FONT,
    OUTLINED_FONT,
    POLYGON_FONT,
    VOID_FONT
  };

public:
  UFontMessage (float x=-0.9, float y=0.9, float z = 0.9);
  virtual ~UFontMessage ();
  void SetColor (float red, float green, float blue);
  /**
   * Get the font color.
   */
  void GetColor (float color[3]) const;
  /**
   * Defines if the font has color.
   */
  void SetHasColor (bool flag)
  {
    m_has_color = flag;
  }
  /**
   * Get whether the font has color.
   */
  bool HasColor () const
  {
    return m_has_color;
  }
  void SetPosition (float x, float y, float z = 0.9)
  {
    m_x = x; m_y = y; m_z = z;
  }
  void SetRenderMode (int rendermode)
  {
    m_render_mode = rendermode;
  }
  int GetRenderMode ()
  {
    return m_render_mode;
  }
  /**
   * Specifies if the given coordinates are given in clipping coordinates
   * instead of world coordinates. (default=true)
   */
  void SetClippingCoords (bool flag)
  {
    m_clippingcoords = flag;
  }
  /**
   * Specifies if the given coordinates are given in clipping coordinates
   * instead of world coordinates (default=true).
   */
  bool AreClippingCoords () const
  {
    return m_clippingcoords;
  }
  /**
   * Defines if the font has a shadow.
   */
  void SetHasShadow (bool shadow)
  {
    m_has_shadow = shadow;
  }
  /**
   * Get whether the font has a shadow.
   */
  bool HasShadow () const
  {
    return m_has_shadow;
  }
  /**
   * Specifies the font shadow color.
   */
  void SetShadowColor (float red, float green, float blue, float alpha);
  /**
   * Get the font shadow color.
   */
  void GetShadowColor (float color[4]) const;
  /**
   * Do message positioning.
   * Returns 'true' if will position text in clipping coords, 'false' if not
   * necessary.
   */
  bool Position (float x, float y, float z, float sdx, float sdy, float sdz);
  /** 
   * Sets the shadow translation. The default value is (1,-1)
   */
  void SetShadowTranslation (float x, float y)
  {
    m_shadow_translation_x = x;
    m_shadow_translation_y = y;
  }
  /** 
   * Gets the shadow translation. The default value is (1,-1)
   */
  void GetShadowTranslation (float* x, float* y) const
  {
    *x = m_shadow_translation_x;
    *y = m_shadow_translation_y;
  }
  /**
   * Displays a plain string (already formatted).
   * For display of a formatted string (like *printf), see Display.
   * Optional dl_id and dl_needs_update control display list usage.
   */
  void DisplayPlain (const char* msg, 
                     GLuint dl_id = -1, 
                     bool dl_needs_update = false);
  /**
   * Displays a formatted string (just like *printf), given the current font.
   */
  void Display (const char* format, ...);
  /**
   * Returns the width in pixels of string 'text', given the current font.
   */
  virtual int Length (const char *text) = 0;
  /**
   * Returns the width and height i pixels of string 'text', given the current font.
   */
  virtual void GetDimensions (const char* text, int *length=0, int *height=0) = 0;
  /**
   * Returns the 3d bounding box corners of string 'text', given the current font.
   */
  virtual void GetBBox (const char* text, float *llx=0, float *lly=0, float *llz=0, float *urx=0, float *ury=0, float *urz=0)
  {
    if (llx)
      *llx = 0;
    if (lly)
      *lly = 0;
    if (llz)
      *llz = 0;
    if (urx)
      *urx = 0;
    if (ury)
      *ury = 0;
    if (urz)
      *urz = 0;
  }
  /**
   * Returns the ascender height in pixels of the font.
   */
  virtual int GetAscender() = 0;
  /**
   * Returns the descender height in pixels of the font.
   */  
  virtual int GetDescender() = 0;
  /**
   * Returns the line spacing for the font.
   */  
  virtual int GetLineHeight() = 0;
  void SetUtf8 (bool flag);
  bool IsUtf8 ();
  static const char* GetRenderModeName (int render_mode);
protected:
  virtual void Show (const char* text) = 0;
  void Render (const char* msg, 
               GLuint dl_id = -1, 
               bool dl_needs_update = false);
private:
  void ShowDL (const char* msg, 
               GLuint dl_id = -1, 
               bool dl_needs_update = false);
private:
  float m_x, m_y, m_z;
  bool m_clippingcoords;
  int m_render_mode;
  float m_shadow_translation_x;
  float m_shadow_translation_y;
  float m_shadow_color[4];
  float m_color[3];
  bool m_has_shadow;
  bool m_has_color;
  bool m_utf8;
};

#endif
