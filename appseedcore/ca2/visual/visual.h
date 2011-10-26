#pragma once



namespace visual
{
   class application;
} // namespace visual

#include "primitive/img.h"
#include "primitive/color.h"

CLASS_DECL_ca BOOL TextOutU(HDC hdc, int x, int y, const char * lpString, int c);
CLASS_DECL_ca BOOL GetTextExtentPoint32U(HDC hdc, const char * lpString, int c, LPSIZE psizl);
CLASS_DECL_ca int  DrawTextU(HDC hdc, const char * lpchText, int cchText, LPRECT lprc, UINT format);



#include "clip.h"

#include "visual_dib.h"
#include "fastblur.h"
#include "rgb_quad_array.h"
#include "imaging.h"
#include "image_list.h"
#include "water_routine.h"
#include "visual_cursor.h"

#include "api.h"
#include "graphics_extension.h"
#include "glyph.h"
#include "glyph_set.h"
#include "visual_font.h"
#include "font_central.h"
#include "dib_pal.h"
#include "icon.h"

#include "buffered_graphics.h"


#include "visual_visual.h"

#include "visual_application.h"

