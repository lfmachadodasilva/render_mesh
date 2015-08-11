#ifndef UFONT_FONT_MANAGER_H_OLD
#define UFONT_FONT_MANAGER_H_OLD

#include <ufont/fontmanagercompat.h>

#define UTL_PIXMAP_FONT  UFONTFM_PIXMAP_FONT
#define UTL_BITMAP_FONT  UFONTFM_BITMAP_FONT
#define UTL_TEXTURE_FONT UFONTFM_TEXTURE_FONT

#define utlfm_init                     ufontfm_init
#define utlfm_close                    ufontfm_close
#define utlfm_get_font_family_number   ufontfm_get_font_family_number
#define utlfm_get_font_family_name     ufontfm_get_font_family_name
#define utlfm_font_has_regular         ufontfm_font_has_regular
#define utlfm_font_has_bold            ufontfm_font_has_bold
#define utlfm_font_has_italic          ufontfm_font_has_italic
#define utlfm_font_has_bold_italic     ufontfm_font_has_bold_italic
#define utlfm_font_has_style           ufontfm_font_has_style
#define utlfm_get_font_available_sizes ufontfm_get_font_available_sizes
#define utlfm_get_font_available_size  ufontfm_get_font_available_size
#define utlfm_set_font                 ufontfm_set_font
#define utlfm_print_string             ufontfm_print_string
#define utlfm_strlen                   ufontfm_strlen
#define utlfm_dimensions               ufontfm_dimensions
#define utlfm_ascender                 ufontfm_ascender
#define utlfm_descender                ufontfm_descender
#define utlfm_line_height              ufontfm_line_height

#endif
