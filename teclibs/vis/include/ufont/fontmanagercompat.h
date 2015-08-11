// OpenGL font manager
// Tecgraf/PUC-Rio
// fabraham@tecgraf.puc-rio.br
// Dec 2005

#ifndef UFONT_FONT_MANAGER_COMPAT_H
#define UFONT_FONT_MANAGER_COMPAT_H

#include "defines.h"

enum {
  UFONTFM_PIXMAP_FONT = 0,
  UFONTFM_BITMAP_FONT,
  UFONTFM_TEXTURE_FONT,
  UFONTFM_EXTRUDED_FONT,
  UFONTFM_OUTLINED_FONT,
  UFONTFM_POLYGON_FONT
};

/**
 * Initilizes the available fonts
 */
UFONT_API void ufontfm_init ();
/**
 * Shuts down the font manager
 */
UFONT_API void ufontfm_close ();
/**
 * Add path to folder with fonts.
 */
UFONT_API void ufontfm_add_fonts_path (const char* path);
/**
 * Obtains the number of available font family names
 */
UFONT_API int ufontfm_get_font_family_number ();
/**
 * Obtains family name of index 'index'. (0 based)
 */
UFONT_API const char* ufontfm_get_font_family_name (int index);
/**
 * Does family name 'family_name' have a regular font?
 */
UFONT_API bool ufontfm_font_has_regular (const char *family_name);
/**
 * Does family name 'family_name' have a bold font?
 */
UFONT_API bool ufontfm_font_has_bold (const char *family_name);
/**
 * Does family name 'family_name' have a italic font?
 */
UFONT_API bool ufontfm_font_has_italic (const char *family_name);
/**
 * Does family name 'family_name' have a bold+italic font?
 */
UFONT_API bool ufontfm_font_has_bold_italic (const char *family_name);
/**
 * Does family name 'family_name' have a font with this bold/italic style?
 */
UFONT_API bool ufontfm_font_has_style (const char *family_name, bool bold, bool italic);
/**
 * Returns the number of sizes available for the font
 */
UFONT_API int ufontfm_get_font_available_sizes (const char *family_name);
/**
 * Returns the 'index'th available size for the font
 */
UFONT_API int ufontfm_get_font_available_size (const char *family_name, int index);
/**
 * Set a font as the current font.
 * Family_name must have been obtained from GetFamilyName().
 * Render mode determines if the font will be rendered as bitmap, pixmap or texture.
 * For glut fonts, render_mode is ignored. True type fonts support UTL_PIXMAP_FONT and
 * UTL_TEXTURE_FONT, while UTL_BITMAP_FONT is ignored.
 * Check wether the family_name supports bold/italic/bold+italic/regular
 * styles before using.
 */
UFONT_API bool ufontfm_set_font (const char *family_name, int size, bool bold = false, bool italic = false, int render_mode = UFONTFM_PIXMAP_FONT);
/**
 * Prints a string in the current OpenGL canvas, using current transformation matrices,
 * at the specified position.
 * deltas are applied in projected space.
 */
UFONT_API void ufontfm_print_string (const char *str, float x, float y, float z, float sdx = 0.0f, float sdy = 0.0f, float sdz = 0.0f);
/**
 * Returns the length of a string in pixels, given the current font.
 */
UFONT_API int ufontfm_strlen (const char *str);
/**
 * Returns the width and height of a string in pixels, given the current font.
 */
UFONT_API void ufontfm_dimensions (const char *str, int *width=0, int *height=0);
/**
 * Returns the ascender height in pixels of the font.
 */
UFONT_API int ufontfm_ascender ();
/**
 * Returns the descender height in pixels of the font.
 */
UFONT_API int ufontfm_descender ();
/**
 * Returns the line spacing for the font.
 */
UFONT_API int ufontfm_line_height ();

#endif
