#pragma once


#include "ca/userpresence/userpresence.h"

#include "ft2build.h"
#include FT_FREETYPE_H


namespace visual
{
   class application;
} // namespace visual

#include "primitive/img.h"
#include "primitive/color.h"

CLASS_DECL_ca BOOL TextOutU(HDC hdc, int x, int y, const char * lpString, int c);
CLASS_DECL_ca BOOL GetTextExtentPoint32U(HDC hdc, const char * lpString, int c, LPSIZE psizl);
CLASS_DECL_ca int  DrawTextU(HDC hdc, const char * lpchText, int cchText, LPRECT lprc, UINT format);



#include "visual_clip.h"

#include "visual_dib.h"
#include "visual_fastblur.h"
#include "visual_rgb_quad_array.h"
#include "visual_imaging.h"
#include "visual_image_list.h"
#include "visual_water_routine.h"
#include "visual_cursor.h"

#include "visual_api.h"
#include "visual_graphics_extension.h"
#include "visual_glyph.h"
#include "visual_glyph_set.h"
#include "visual_font.h"
#include "visual_font_central.h"
#include "visual_dib_pal.h"
#include "visual_icon.h"

#include "visual_buffered_graphics.h"


#include "visual_visual.h"

#include "visual_application.h"

