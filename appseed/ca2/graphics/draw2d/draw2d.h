#pragma once


namespace draw2d
{


   class object;
   class pen;
   class graphics;
   class bitmap;
   class brush;
   class font;
   class palette;
   class region;


   enum e_unit
   {
      unit_pixel,
      unit_point,
   };


   enum e_text_rendering
   {
      text_rendering_anti_alias,
      text_rendering_anti_alias_grid_fit,
      text_rendering_single_bit_per_pixel,
      text_rendering_clear_type_grid_fit,
   };


} // namespace draw2d


#include "draw2d_object.h"
#include "draw2d_pen.h"
#include "draw2d_bitmap.h"
#include "draw2d_brush.h"
#include "draw2d_font.h"
#include "draw2d_palette.h"
#include "draw2d_region.h"
#include "draw2d_igui.h"
#include "draw2d_dib.h"
//#include "ca2_draw_dib.h"
#include "draw2d_path.h"


namespace user
{


   class str_context;


}


#include "user/user_draw_context.h"
#include "draw2d_graphics.h"



