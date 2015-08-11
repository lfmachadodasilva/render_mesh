// OpenGL font factory
// Tecgraf/PUC-Rio
// cpalomo@tecgraf.puc-rio.br
// Oct 2009

#ifndef UFONT_FACTORY_H
#define UFONT_FACTORY_H

#include "defines.h"
#include <ds/array.h>

class UFONT_API UFontFactory
{
public:
  class Font {
  public:  
    Font () 
    {
      isglut = true;
      family_name = NULL;
    }
    ~Font ()
    {
      free(family_name);
    }
    bool isglut;
    DsArray<int> sizes;
    char *family_name;
  };

public:
  /**
   * Create a truetype font.
   * @param family_name TT font family name.
   * @return created TT font, or NULL when family invalid.
   */
  static Font* CreateTTFont (const char* family_name);

  /**
   * Create a GLUT font with predefined possible sizes.
   * @param family_name GLUT font name.
   * @return created GLUT font.
   */
  static Font* CreateGlutFont (const char* family_name);

  /**
   * Does family name 'family_name' have a regular font?
   */
  static bool FontHasRegular (const char *family_name);

  /**
   * Does family name 'family_name' have a bold font?
   */
  static bool FontHasBold (const char *family_name);

  /**
   * Does family name 'family_name' have a italic font?
   */
  static bool FontHasItalic (const char *family_name);

  /**
   * Does family name 'family_name' have a bold+italic font?
   */
  static bool FontHasBoldItalic (const char *family_name);

  /**
   * Does family name 'family_name' have a font with this bold/italic style?
   */
  static bool FontHasStyle (const char *family_name, bool bold, bool italic);

  /**
   * Returns the 'index'th available size for the font
   */
  static bool IsGlutFontSizeAvailable (const char *family_name, int size);

  /**
   * Returns the internal low-level GLUT font identifier
   */
  static void* GetGlutFont (const char *family_name, int size);

  /**
   * Checks whether family name corresponds to a GLUT font
   */
  static bool IsGlutFont (const char *family_name);

  /**
   * Check whether a font family/bold/italic combination is allowed.
   * @param ff font family.
   * @param size font size.
   * @param bold flag.
   * @param italic flag.
   * @return true when combination allowed.
   * NOTE: when GLUT font informed, bold and italic must be false since
   * GLUT fonts do not allow bold or italic texts.
   */
  static bool IsFontAllowed (const char* ff, int size, bool bold, bool italic);

private:
  /**
   * Get allowed sizes for a GLUT font.
   * @param font_name GLUT font name.
   * @param sizes array of possible font sizes (return param).
   */
  static void GetAllowedGlutFontSizes (const char* font_name, 
                                       DsArray<int>& sizes);
};

#endif
