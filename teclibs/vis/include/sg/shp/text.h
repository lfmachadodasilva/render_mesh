// Text class
// djavanes@tecgraf.puc-rio.br
// Set 2008

#ifndef SG_TEXT_H
#define SG_TEXT_H

#include <sg/shape.h>
#include <ufont/text.h>

class UFontText;

/**
 * SGText Class.
 * This shape will draw a Text at x y z coords.
 */
class SG_API SGText : public SGShape
{
  UFontText* m_text;
  float m_x, m_y, m_z, m_red, m_green, m_blue, m_alpha;
  int m_halignment;
  int m_valignment;
  char* m_rawtext;

public:
  enum {
    CENTER = 0,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
  };
  static const char* CLASSNAME () { return "Text"; }
  const char* ClassName () const { return CLASSNAME(); }
  /**
   * Constructor
   */
  SGText ();
  /**
   * Destructor
   */
  ~SGText ();
  bool Setup (const char *font_name, int size, bool bold, bool italic);
  bool SetRenderMode (int render_mode);
  void SetColor (float r, float g, float b, float a);
  void SetPosition (float x, float y, float z);
  void SetAlignment (int h_alignment, int v_alignment = 0);
  void SetText (const char *text);
  void SetUtf8 (bool state);
  const char* GetText () const;
  const char* GetFontFamily () const
  {
    return m_text->GetFontFamily();
  }
  int GetFontSize () const
  {
    return m_text->GetFontSize();
  }
  bool IsBold () const
  {
    return m_text->IsBold();
  }
  bool IsItalic () const
  {
    return m_text->IsItalic();
  }
  bool HasCulling ()
  {
    return true;
  }
  int GetVertexCount ()
  {
    return 0;
  }
  void GetVertex (int index, float *x, float *y, float *z)
  {
  }
  int GetLineCount ();
  int GetTriangleCount ();
  void Draw ();
  void Write (UtlWriter* writer);
};

#endif
