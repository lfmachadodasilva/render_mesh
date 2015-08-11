// OpenGL font manager
// Tecgraf/PUC-Rio
// fabraham@tecgraf.puc-rio.br
// rodesp@tecgraf.puc-rio.br
// Sep 2006

#ifndef UFONT_MANAGER_H
#define UFONT_MANAGER_H

#include "defines.h"
#include "message.h"
#include "ttmessage.h"
#include "fontenumerator.h"
#include <ds/hash.h>
#include <ds/array.h>
#include <alg/vector.h>
#include <alg/matrix.h>

#define UFONT_MANAGER_CACHE_SIZE 50

class UFontCache;

class UFONT_API UFontManager
{
public:
  /**
  * Initializes the font manager. 
  * Must be called once before creating the first UFontManager object.
  * Requires a valid OpenGL context.
  */
  static void Init ();

  /**
  * Shuts down the font manager. 
  * Must be called before the program terminates, to release allocated
  * resources.
  */
  static void Close ();

  /**
  * Creates a new UFontManager object.
  * Requires a valid OpenGL context.
  */
  UFontManager ();


  //void utlfm_close ();
  ~UFontManager ();

  /**
  * Obtains the number of available font family names
  */
  static int GetFontFamilyNumber ();

  /**
  * Obtains family name of index 'index'. (0 based)
  */
  static const char* GetFontFamilyName (int index);

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
  * Returns the number of sizes available for the font
  */
  static int GetFontAvailableSizes (const char *family_name);

  /**
  * Returns the 'index'th available size for the font
  */
  static int GetFontAvailableSize (const char *family_name, int index);

  /**
  * Returns whether the given font is available
  */
  static bool IsFontAvailable (const char *family_name, int size, bool bold, bool italic);

  /**
   * Adds a path to a folder with true type fonts.
   */
  static void AddFontsPath (const char* path);

  /**
  * Set a font as the current font.
  * Family_name must have been obtained from GetFamilyName().
  * Render mode determines if the font will be rendered as bitmap, pixmap or
  * texture.
  * For glut fonts, render_mode is ignored. True type fonts support
  * UFontManager::PIXMAP_FONT and UFontManager::TEXTURE_FONT, while
  * UFontManager::BITMAP_FONT is ignored.
  * Check wether the family_name supports bold/italic/bold+italic/regular
  * styles before using.
  */
  bool SetFont (const char *family_name, int size, bool bold = false, bool italic = false, int render_mode = UFontMessage::PIXMAP_FONT, float depth = 0.0f);

  /**
  * Prints a string in the current OpenGL canvas, using current transformation matrices,
  * at the specified position.
  * deltas are applied in projected space.
  */
  void PrintString (const char *str, float x, float y, float z, float sdx = 0.0f, float sdy = 0.0f, float sdz = 0.0f);

  /**
  * Returns the length of a string in pixels, given the current font.
  */
  int StrLen (const char *str);

  /**
  * Returns the width and height of a string in pixels, given the current font.
  */
  void Dimensions (const char *str, int *width=0, int *height=0);

  /**
  * Returns the 3D Bounding Box of a string, given the current font.
  */
  void BBox (const char *str, float *llx=0, float *lly=0, float *llz=0, float *urx=0, float *ury=0, float *urz=0);

  /**
  * Returns the ascender height in pixels of the font.
  */
  int Ascender ();

  /**
  * Returns the descender height in pixels of the font.
  */
  int Descender ();

  /**
  * Returns the line spacing for the font.
  */
  int LineHeight ();

  /**
   * Defines if the font has a shadow.
   */
  bool SetHasShadow (bool shadow);

  /**
   * Specifies the font shadow color.
   */
  bool SetShadowColor (float red, float green, float blue, float alpha);

  /** 
   * Sets the shadow translation. The default value is (2,-2)
   */
  bool SetShadowTranslation (float x, float y);

  /**
  * Automatic shadow configuration: sets color, translation and enables shadow.
  */
  void EnableAutoShadow (float red, float green, float blue, float shadowgap);

private:
  UFontMessage* m_curr_message;
  UFontCache* m_cache;
  static int s_init_count;
};

#endif
