#include "framework.h"



#include "linux/c_os_cross_win_gdi_internal.h"



void set(XColor & color, COLORREF cr)
{
   color.pixel    = cr;
   color.red      = GetRValue(cr);
   color.green    = GetGValue(cr);
   color.blue     = GetBValue(cr);
}











os_simple_graphics::os_simple_graphics()
{

   m_pdc           = NULL;

}


os_simple_graphics::~os_simple_graphics()
{

}


bool os_simple_graphics::is_null()
{

      return m_pdc == NULL;

}

bool os_simple_graphics::create(HDC hdc)
{

   if(m_iType != 0)
      destroy();

//   m_hdc = ::CreateCompatibleDC(hdc);

   //if(m_hdc == NULL)
     // return false;

  // ::ReleaseDC(NULL, hdc);

   m_iType = 1;

   return true;

}

bool os_simple_graphics::create_from_bitmap(simple_bitmap & b)
{

   if(m_iType != 0)
      destroy();

/*   m_hdc = ::CreateCompatibleDC(NULL);

   if(m_hdc == NULL)
      return false;

   m_hbitmapOld = (HBITMAP) ::SelectObject(m_hdc, b.m_hbitmap);

   if(m_hbitmapOld == NULL)
   {

      ::DeleteDC(m_hdc);

      m_hdc = NULL;

      return false;

   }*/

   m_iType = 3;

   return true;

}

bool os_simple_graphics::detach_bitmap()
{

   if(m_iType != 0)
      destroy();

/*   if(m_hdc == NULL)
      return false;

   if(m_hbitmapOld == NULL)
      return false;

   if(m_iType != 3)
      return false;

   HBITMAP hbitmap = (HBITMAP) ::SelectObject(m_hdc, m_hbitmapOld);

   m_iType = 1;*/

//   return hbitmap != NULL;
   return false;

}

bool os_simple_graphics::from_entire_window(oswindow hwnd)
{

   if(m_iType != 0)
      destroy();

/*   m_hdc = ::GetWindowDC(hwnd);

   if(m_hdc == NULL)
      return false;

   m_hwnd = hwnd;*/

   m_iType = 2;

   return true;

}


bool os_simple_graphics::from_window(oswindow hwnd)
{

   if(m_iType != 0)
      destroy();

/*   m_hdc = ::GetDC(hwnd);

   if(m_hdc == NULL)
      return false;

   m_hwnd = hwnd;*/

   m_iType = 2;

   return true;

}

bool os_simple_graphics::from_window_paint(oswindow hwnd, LPRECT lprectPaint)
{

   if(m_iType != 0)
      destroy();

/*    m_hdc = BeginPaint(hwnd, &m_ps);

    if(m_hdc == NULL)
       return false;

    m_hwnd = hwnd;

    if(lprectPaint != NULL)
    {

       *lprectPaint = m_ps.rcPaint;

    }*/

    m_iType = 4;

    return true;

}

bool os_simple_graphics::reference_os_data(HDC hdc)
{

   m_iType = 5;

//   m_hdc = hdc;

   return true;

}



/*bool os_simple_graphics::create()
{

   os_simple_graphics g;

   g.from_window(NULL);

   return create(g);

}

bool os_simple_graphics::create(os_simple_graphics & g)
{

//   return create(g.m_hdc);
return false;

}

bool os_simple_graphics::create_from_screen()
{

   return from_window(NULL);

}
*/

bool os_simple_graphics::select(simple_font & font)
{

   m_font = font;

   return true;

}

bool os_simple_graphics::select(simple_brush & brush)
{

   m_brush = brush;

   return true;

}

bool os_simple_graphics::select(simple_pen & pen)
{

   m_pen = pen;

   return true;

}

bool os_simple_graphics::destroy()
{

   bool bOk = true;

   bool bOkOldBitmap = true;

   bool bOkOldPen = true;

   bool bOkOldBrush = true;

   bool bOkOldFont = true;



/*   if(m_hbitmapOld != NULL)
   {

      bOkOldBitmap   = ::SelectObject(m_hdc, m_hbitmapOld) != NULL;

      m_hbitmapOld   = NULL;

   }

   if(m_hbrushOld != NULL)
   {

      bOkOldBrush    = ::SelectObject(m_hdc, m_hbrushOld) != NULL;

      m_hbrushOld    = NULL;

   }

   if(m_hpenOld != NULL)
   {

      bOkOldPen      = ::SelectObject(m_hdc, m_hpenOld) != NULL;

      m_hpenOld      = NULL;
   }

   if(m_hfontOld != NULL)
   {

      bOkOldFont     = ::SelectObject(m_hdc, m_hfontOld) != NULL;

      m_hfontOld     = NULL;

   }*/


   if(m_iType == 1)
   {

//      bOk = ::DeleteDC(m_hdc) != FALSE;

   }
   else if(m_iType == 2)
   {

  //    bOk = ::ReleaseDC(m_hwnd, m_hdc) != FALSE;

   }
   else if(m_iType == 3)
   {

    //  bOk = ::DeleteDC(m_hdc) != FALSE;

   }
   else if(m_iType == 4)
   {

      //bOk = EndPaint(m_hwnd, &m_ps) != FALSE;

   }


//   m_hwnd   = NULL;

  // m_hdc    = NULL;

   m_iType  = 0;

   return bOk && bOkOldBitmap && bOkOldBrush && bOkOldFont && bOkOldPen;

}

bool os_simple_graphics::set_offset(int32_t x, int32_t y)
{

   POINT ptViewport;

//   if(!SetViewportOrgEx(m_hdc, x, y, &ptViewport))
  //    return false;

   return true;

}

bool os_simple_graphics::offset(int32_t x, int32_t y)
{

   POINT ptViewport;

//   if(!OffsetViewportOrgEx(m_hdc, x, y, &ptViewport))
  //    return false;

   return true;

}


bool os_simple_graphics::bit_blt(int32_t x, int32_t y, int32_t cx, int32_t cy, simple_graphics & gSrc, int32_t x1, int32_t y1, DWORD rop)
{

//   return ::BitBlt(m_hdc, x, y, cx, cy, gSrc.m_hdc, x1, y1, rop) != FALSE;
return false;


}

bool os_simple_graphics::blend_bitmap_data(int32_t x, int32_t y, int32_t cx, int32_t cy, COLORREF * pdata)
{

   /*try
   {

      Gdiplus::Bitmap b(cx, cy, cx *4 , PixelFormat32bppARGB, (BYTE *) pdata);

      Gdiplus::Graphics * pg = new Gdiplus::Graphics(m_hdc);

      pg->SetCompositingMode(Gdiplus::CompositingModeSourceOver);

      pg->SetCompositingQuality(Gdiplus::CompositingQualityHighQuality);

      pg->DrawImage(&b, x, y, 0, 0, cx, cy, Gdiplus::UnitPixel);

      pg->Flush(Gdiplus::FlushIntentionSync);

      delete pg;

      ::GdiFlush();

      return true;

   }
   catch(...)
   {

   }
*/
   return false;

}

SIZE os_simple_graphics::get_text_extent(const char * psz, int32_t iLen)
{

   vsstring str(psz, iLen);

   cairo_text_extents_t ex;

   cairo_text_extents(m_pdc, str, &ex);

	SIZE size;

	size.cx = ex.width;

	size.cy = ex.height;

   return size;

}


bool os_simple_graphics::rectangle(LPCRECT lpcrect)
{

   bool bOk1 = true;

   if(m_brush.m_iStock != NULL_BRUSH)
   {

      set(m_brush);

      cairo_rectangle(m_pdc, lpcrect->left, lpcrect->top, lpcrect->right - lpcrect->left, lpcrect->bottom - lpcrect->top);

      if(m_pen.m_iStock != NULL_PEN)
      {

         cairo_fill_preserve(m_pdc);

      }
      else
      {

         cairo_fill(m_pdc);

      }


   }

   bool bOk2 = true;

   if(m_pen.m_iStock != NULL_PEN)
   {

      set(m_pen);

      cairo_stroke(m_pdc);

   }

   return bOk1 && bOk2;

}



bool os_simple_graphics::fill_rect(LPCRECT lpcrect, simple_brush & brush)
{

   set(m_brush);

   cairo_rectangle(m_pdc, lpcrect->left, lpcrect->top, lpcrect->right - lpcrect->left, lpcrect->bottom - lpcrect->top);

   cairo_fill(m_pdc);

   return true;

}


/*XColor green_col;
Colormap colormap;
char green[] = "#00FF00";

Assign a colormap to the colormap variable with the DefaultColormap function. The DefaultColormap function takes two arguments. The first argument is the display connection. The second argument is the screen number.


colormap = DefaultColormap(dis, 0);

Create the graphics context using XCreateGC and put the GC information in green_gc


green_gc = XCreateGC(dis, win, 0, 0);

Parse the color 00FF00 and allocate the color for later use.*/

/*

XParseColor(dis, colormap, green, &green_col);
XAllocColor(dis, colormap, &green_col);

Now that the color has been allocated set the foreground of the graphics context with XSetForeground. The last argument to XSetForeground is the pixel value of the color allocated.


XSetForeground(dis, green_gc, green_col.pixel);

Now the program can draw using the foreground color set for green_gc.


case Expose:
XDrawRectangle(dis, win, green_gc, 1, 1, 497, 497);
XDrawRectangle(dis, win, green_gc, 50, 50, 398, 398);
break;



   return ::FillRect(m_hdc, lpcrect, brush.m_hbrush) != FALSE;

}
*/

/*
bool os_simple_graphics::set_text_color(COLORREF cr)
{

   m_crTextColor = cr;

   return true;


}


*/
/*
bool os_simple_graphics::alpha_blend(int32_t x, int32_t y, int32_t cx, int32_t cy, os_simple_graphics & gSrc, int32_t x1, int32_t y1, int32_t cx1, int32_t cy1, BLENDFUNCTION bf)
{

   //return ::AlphaBlend(m_hdc, x, y, cx, cy, gSrc.m_hdc, x1, y1, cx1, cy1, bf) != FALSE;

   return false;

}
*/

void os_simple_graphics::fill_solid_rect(LPCRECT lpRect, COLORREF cr)
{

   simple_brush brush;

   brush.create_solid((simple_graphics &) *this, cr);

   fill_rect(lpRect, brush);

}


bool os_simple_graphics::text_out(int32_t x, int32_t y, const char * pszUtf8, int32_t iSize)
{

   cairo_move_to(m_pdc, x, y);

   set(m_brush);

   vsstring str(pszUtf8, iSize);

   cairo_show_text(m_pdc, str);

   return true;

}



bool os_simple_graphics::set_alpha_mode(::ca::e_alpha_mode emode)
{
   switch(emode)
   {
    case ::ca::alpha_mode_set:
         cairo_set_operator(m_pdc, CAIRO_OPERATOR_SOURCE);
         return true;
   case ::ca::alpha_mode_blend:
         cairo_set_operator(m_pdc, CAIRO_OPERATOR_OVER);
         default:;

   }

   return false;
}



bool os_simple_graphics::draw_path(simple_path & path, simple_pen & pen)
{

   set(path);

   set(pen);

   cairo_stroke(m_pdc);

   return true;

}

bool os_simple_graphics::fill_path(simple_path & path, simple_brush & brush)
{

   set(path);

   set(brush);

   cairo_fill(m_pdc);

   return true;

}


bool os_simple_graphics::set(simple_font & font)
{

   cairo_select_font_face(m_pdc, font.m_strFamily, CAIRO_FONT_SLANT_NORMAL, font.m_weight);

   cairo_set_font_size(m_pdc, font.m_dSize);

}

bool os_simple_graphics::set(simple_brush & brush)
{

   cairo_set_source_rgba(m_pdc, GetRValue(brush.m_cr) / 255.0, GetGValue(brush.m_cr) / 255.0, GetBValue(brush.m_cr) / 255.0, GetAValue(brush.m_cr) / 255.0);

}

bool os_simple_graphics::set(simple_pen & pen)
{

   cairo_set_source_rgba(m_pdc, GetRValue(pen.m_cr) / 255.0, GetGValue(pen.m_cr) / 255.0, GetBValue(pen.m_cr) / 255.0, GetAValue(pen.m_cr) / 255.0);

   cairo_set_line_width(m_pdc, pen.m_iWidth);

}

bool os_simple_graphics::set(simple_path & path)
{

   for(int32_t i = 0; i < path.m_elementa.get_count(); i++)
   {

      set(path.m_elementa[i]);

   }

   if(path.m_efillmode == ::ca::fill_mode_alternate)
   {

      cairo_set_fill_rule(m_pdc, CAIRO_FILL_RULE_EVEN_ODD);

   }
   else
   {

      cairo_set_fill_rule(m_pdc, CAIRO_FILL_RULE_WINDING);

   }


   return true;

}


bool os_simple_graphics::set(simple_path::element & e)
{

   switch(e.m_etype)
   {
   case simple_path::element::type_arc:
      set(e.m_arc);
      break;
   case simple_path::element::type_line:
      set(e.m_line);
      break;
   case simple_path::element::type_close:
      cairo_close_path(m_pdc);
      break;
   default:
      throw "unexpected simple os graphics element type";
   }

   return false;

}

bool os_simple_graphics::set(simple_path::arc & a)
{

   cairo_translate(m_pdc, a.m_xCenter, a.m_yCenter);

   cairo_scale(m_pdc, 1.0, a.m_dRadiusY / a.m_dRadiusX);

   cairo_arc(m_pdc, 0.0, 0.0, a.m_dRadiusX, a.m_dAngle1, a.m_dAngle2);

   cairo_scale(m_pdc, 1.0, a.m_dRadiusX / a.m_dRadiusY);

   cairo_translate(m_pdc, -a.m_xCenter, -a.m_yCenter);

   return true;

}

bool os_simple_graphics::set(simple_path::line & l)
{

   if(cairo_has_current_point(m_pdc))
   {

      cairo_move_to(m_pdc, l.m_x1, l.m_y1);

   }
   else
   {

      cairo_line_to(m_pdc, l.m_x1, l.m_y1);

   }

   cairo_line_to(m_pdc, l.m_x2, l.m_y2);

   return true;

}


bool os_simple_graphics::exclude_clip(simple_path & path)
{

   return true;

}


bool os_simple_graphics::replace_clip(simple_path & path)
{

   return true;

}

bool os_simple_graphics::replace_clip(const RECT & rect)
{

   return true;

}

bool os_simple_graphics::fill_polygon(POINT * p, int32_t iCount, ::ca::e_fill_mode)
{

      return true;

}


bool os_simple_graphics::draw_rect(LPCRECT lpcrect, simple_pen &pen)
{

   return true;

}


bool os_simple_graphics::draw_line(int32_t, int32_t, int32_t, int32_t, simple_pen &)
{

   return true;

}



