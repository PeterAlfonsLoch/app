#pragma once


class job;


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
   // backlink from ca.dll on 2012-10-14 11:04 Alameda Princesa Izabel, 3000 - CWB-PR-Brasil

   enum e_alpha_mode
   {
      alpha_mode_set,
      alpha_mode_blend
   };

   enum e_fill_mode
   {
      fill_mode_winding,
      fill_mode_alternate
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



