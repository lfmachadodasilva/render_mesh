// Font enumerator
// fabraham@tecgraf.puc-rio.br
// Oct 2005
#ifndef UFONT_FONT_ENUMERATOR_H
#define UFONT_FONT_ENUMERATOR_H

#include "defines.h"

/**
 * Initializes the font enumerator.
 */
UFONT_API bool ufont_fe_init ();
/**
 * Shuts down the font enumerator.
 */
UFONT_API void ufont_fe_close ();
/**
 * Adds a path to a folder with true type fonts.
 */
UFONT_API void ufont_fe_add_dir (const char *directory);
/**
 * Obtains the number of font family names available.
 */
UFONT_API int ufont_fe_get_num_family_names ();
/**
 * Obtains the name of the font family 'index'. (0<=index && index<numfamilies)
 */
UFONT_API const char *ufont_fe_get_family_name (int index);
/**
 * Does the font family have a bold font?
 */
UFONT_API bool ufont_fe_has_bold (const char *familyname);
/**
 * Does the font family have an italic font?
 */
UFONT_API bool ufont_fe_has_italic (const char *familyname);
/**
 * Does the font family have a bold and italic font?
 */
UFONT_API bool ufont_fe_has_bold_italic (const char *familyname);
/**
 * Does the font family have a regular font?
 */
UFONT_API bool ufont_fe_has_regular (const char *familyname);
/**
 * Does the font family have this style?
 */
UFONT_API bool ufont_fe_has_style (const char *familyname, bool bold, bool italic);
/**
 * Obtains the filename of the font, given its family, if it's bold and/or italic.
 * Returns NULL in case there is no such family or style for this family.
 */
UFONT_API const char *ufont_fe_get_filename (const char *familyname, bool bold, bool italic);

#endif

