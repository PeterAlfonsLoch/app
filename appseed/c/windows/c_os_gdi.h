#pragma once


namespace ca
{

   // backlink from ca2.dll on 2012-10-14 11:04 Alameda Princesa Izabel, 3000 - CWB-PR-Brasil

   enum e_alpha_mode
   {
      alpha_mode_set,
      alpha_mode_blend,
   };

   enum e_fill_mode
   {
      fill_mode_winding,
      fill_mode_alternate,
   };


} // namespace ca


namespace Gdiplus
{

   class Brush;
   class Bitmap;
   class Font;
   class Pen;
   class GraphicsPath;
   class Graphics;


} // namespace GdiPlus


#include "c_os_simple_brush.h"
#include "c_os_simple_bitmap.h"
#include "c_os_simple_font.h"
#include "c_os_simple_pen.h"


#include "c_os_simple_path.h"


#include "c_os_simple_graphics.h"



