#pragma once


class job;

enum e_stock_icon
{
   
   stock_icon_none,
   stock_icon_control_box_begin,
   // TO Begin - TIGHTLY ORDERED Begin (relations : {ca2/app/core}::user::wndfrm::frame::e_button[button_close:stock_icon_close,...])
   stock_icon_close =  stock_icon_control_box_begin,
   stock_icon_level_up,
   stock_icon_level_down,
   stock_icon_iconify,
   stock_icon_restore,
   stock_icon_zoom,
   stock_icon_notify,
   stock_icon_dock,
   // TO END - TIGHTLY ORDERED End
   stock_icon_control_box_end = stock_icon_dock
};




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



#if defined(CUBE)


void draw2d_factory_exchange(sp(application) papp);


#endif









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


#include "user/user/user_draw_context.h"
#include "draw2d_graphics.h"






