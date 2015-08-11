// OpenGL Abstraction for font text
// Tecgraf/PUC-Rio
// cpalomo@tecgraf.puc-rio.br
// Sep 2009

#ifndef UFONT_TEXT_H
#define UFONT_TEXT_H

#include "defines.h"
#include "fontfactory.h"
#include "message.h"
#include <GL/glew.h>
#include <alg/vector.h>

class UFontCache;
class UFontMessage;

class UFONT_API UFontText
{
public:
  /**
   * Constructor.
   * @param text optional: text to draw.
   */
  UFontText (const char* text = NULL);
  /**
   * Class destructor.
   */
  virtual ~UFontText ();
  
  /**
   * Set local cache: useful especially when using texture fonts.
   * @NOTE: ask Vitor and Marcio.
   */
  void SetLocalCache (UFontCache* c);

  /**
   * Static initializer: must be called at least once.
   * @return success of failure in initialization.
   */
  static bool Init ();

  /**
   * Static shutdown. 
   * Must be called before the program terminates, to release allocated
   * resources.
   */
  static void Close ();

  /**
   * Adds a path to a folder with true type fonts.
   */
  static void AddFontsPath (const char* path);

  /**
   * Check validity of a font setup.
   *
   * @param ff font family name.
   * @param size font size.
   * @param bold flag.
   * @param italic flag.
   * @param utf8 Specifies whether text is utf8.
   * @param mode render mode
   * @return whether configuration is valid.
   */
  static bool IsValid (const char* ff, 
                       int size, 
                       bool bold, 
                       bool italic, 
                       bool utf8, 
                       UFontMessage::RenderMode mode = UFontMessage::VOID_FONT);

  /**
   * Setup font family, size etc.
   *
   * @param ff font family name.
   * @param size font size.
   * @param bold flag.
   * @param italic flag.
   * @param utf8 Specifies whether text is utf8.
   * @param mode render mode
   * @return success of failure in operation. In the latter case,
   * object remains in the same state it had before Setup call.
   */
  bool Setup (const char* ff, 
              int size, 
              bool bold = false, 
              bool italic = false, 
              bool utf8 = false, 
              UFontMessage::RenderMode mode = UFontMessage::VOID_FONT);
  /**
   * Set font render mode.
   * @param mode render mode.
   */
  bool SetRenderMode (UFontMessage::RenderMode mode);

  /**
   * Set whether text is utf8.
   * @param utf8 flag.
   */
  void SetUtf8 (bool flag);
  /**
   * Set text to draw.
   * @param text string.
   */
  void SetText (const char* format, ...);
  /**
   * Specifies if drawing coordinates are being specified in clipping
   * coordinates instead of in world coordinates. (default=true)
   * @param flag true if in clipping coordinates, false if in world coordinates.
   */
  void SetClippingCoords (bool flag);
  /**
   * Specifies a color for the text. If not set,
   * uses whatever color is configured in the opengl state.
   */
  void SetColor (const AlgVector& color);
  /**
   * Specifies a color for the text. If not set,
   * uses whatever color is configured in the opengl state.
   */
  void SetColor (float red, float green, float blue);
  /**
   * Defines if the text has a shadow.
   */
  void SetHasShadow (bool shadow);
  /**
   * Specifies the text shadow color.
   */
  void SetShadowColor (float red, float green, float blue, float alpha);
  /** 
   * Sets the shadow translation. The default value is (1,-1).
   */
  void SetShadowTranslation (float x, float y);
  /**
   * Get text to draw.
   * @return text string.
   */
  const char* GetText () const;
  /**
   * Get font family.
   * @return font family name.
   */
  const char* GetFontFamily () const;
  /**
   * Get font size.
   * @return font size.
   */
  int GetFontSize () const;
  /**
   * Get whether font is bold.
   * @return bold flag.
   */
  bool IsBold () const;
  /**
   * Get whether font is italic.
   * @return italic flag.
   */
  bool IsItalic () const;
  /**
   * Get whether text is utf8.
   * @return utf8 flag.
   */
  bool IsUtf8 () const;
  /**
   * Return whether text is ready to be drawn.
   */
  bool IsReady () const;

  /**
   * Get font render mode.
   * @return render mode.
   */
  UFontMessage::RenderMode GetRenderMode () const;

  /**
   * Returns the 3d bounding box corners of string 'text', given the current font.
   */
  void GetBBox (float *llx=0, 
                float *lly=0, 
                float *llz=0, 
                float *urx=0, 
                float *ury=0, 
                float *urz=0);

  /**
   * Returns the pixelsize of the 'text', given the current font.
   */
  void GetDimensions (int* length = NULL, int* height = NULL);

  /**
   * Draw text.
   * @param pos text coordinates.
   * @param delta delta in text coordinates.
   */
  void Draw (const AlgVector& pos = AlgVector(-0.9f, 0.9f, 0.9f), 
             const AlgVector& delta = AlgVector(0.f, 0.f, 0.f));

  /**
   * Draw text.
   * @param x x text coordinate.
   * @param y y text coordinate.
   * @param z z text coordinate.
   * @param sdx delta in x text coordinate.
   * @param sdy delta in y text coordinate.
   * @param sdz delta in z text coordinate.
   */
  void Draw (float x = -0.9,
             float y = 0.9,
             float z = 0.9,
             float sdx = 0.0f, 
             float sdy = 0.0f, 
             float sdz = 0.0f);

private:
  UFontCache* GetCache ();
  void SetTextInt (const char* t);
  void InitDraw (UFontMessage* msg,
                 float x, 
                 float y, 
                 float z, 
                 float sdx, 
                 float sdy, 
                 float sdz);
  void EndDraw (UFontMessage* msg);
private:
  char* m_text;                           /**< Text to be rendered.      */
  char* m_font_family;                    /**< Font family.              */
  int   m_font_size;                      /**< Font size.                */
  bool  m_bold;                           /**< Bold font flag.           */
  bool  m_italic;                         /**< Italic font flag.         */
  bool  m_utf8;                           /**< Utf8 flag: HAS NO EFFECT! */
  bool  m_clipping_coords;                /**< Clipping coords flag.     */
  UFontMessage::RenderMode m_render_mode; /**< Render mode.              */
  bool m_has_color;                       /**< Color parameters          */
  AlgVector m_color; 
  bool m_has_shadow;                      /**< Shadow parameters         */
  float m_shadow_translation_x;
  float m_shadow_translation_y;
  float m_shadow_color[4];
  bool m_old_has_color;                   /**< Old color parameters       */
  float m_old_color[3];
  bool m_old_has_shadow;                  /**< Old shadow parameters      */
  float m_old_shadow_translation_x;
  float m_old_shadow_translation_y;
  float m_old_shadow_color[4];
  bool  m_dl_needs_update;                /**< DL out-of-date flag.       */
  GLuint m_dl_id;                         /**< display list id.           */
  UFontCache* m_font_cache;               /**< local cache                */
  static UFontCache* s_font_cache;        /**< cache shared by instances. */
  static int s_init_count;                /**< # of calls to Init().      */
};

#endif

