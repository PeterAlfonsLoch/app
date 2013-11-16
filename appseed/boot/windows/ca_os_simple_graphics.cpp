#include "framework.h"
#undef new
#include <gdiplus.h>


os_simple_graphics::os_simple_graphics()
{

   m_pgraphics    = NULL;

   m_oswindow         = NULL;

   m_iType        = 0;

   m_hdc          = NULL;

}


os_simple_graphics::~os_simple_graphics()
{

   if(m_pgraphics != NULL && m_iType != 0)
   {

      destroy();

   }

}

bool os_simple_graphics::create(HDC hdc)
{

   if(m_iType != 0)
      destroy();
   
   m_pgraphics = new Gdiplus::Graphics(hdc);

   if(m_pgraphics == NULL)
      return false;
   
   m_iType = 1;
   
   return true;

}

bool os_simple_graphics::create_from_bitmap(simple_bitmap & b)
{

   if(m_iType != 0)
      destroy();
   
   m_pgraphics = new ::Gdiplus::Graphics(b.m_pbitmap);

   if(m_pgraphics == NULL)
      return false;

   m_iType = 3;
   
   return true;

}

bool os_simple_graphics::from_entire_window(oswindow oswindow)
{

   if(m_iType != 0)
      destroy();

   m_hdc = ::GetWindowDC(oswindow);

   if(m_hdc == NULL)
      return false;

   m_pgraphics = new Gdiplus::Graphics(m_hdc);

   if(m_pgraphics == NULL)
   {
      ::ReleaseDC(oswindow, m_hdc);
      m_hdc = NULL;
      return false;
   }

   m_oswindow = oswindow;

   m_iType = 2;
   
   return true;

}


bool os_simple_graphics::from_window(oswindow oswindow)
{

   if(m_iType != 0)
      destroy();

   m_hdc = ::GetDC(oswindow);

   if(m_hdc == NULL)
      return false;

   m_pgraphics = new Gdiplus::Graphics(m_hdc);

   if(m_pgraphics == NULL)
   {
      ::ReleaseDC(oswindow, m_hdc);
      m_hdc = NULL;
      return false;
   }

   m_oswindow = oswindow;

   m_iType = 2;
   
   return true;

}

bool os_simple_graphics::from_window_paint(oswindow oswindow, LPRECT lprectPaint)
{


   if(m_iType != 0)
      destroy();

   m_hdc = BeginPaint(oswindow, &m_ps);

   if(m_hdc == NULL)
      return false;

   m_pgraphics = new Gdiplus::Graphics(m_hdc);

   if(m_pgraphics == NULL)
   {
      ::EndPaint(oswindow, &m_ps);
      memset(&m_ps, 0, sizeof(m_ps));
      m_hdc = NULL;
      return false;
   }

   m_oswindow = oswindow;

   m_iType = 4;

   if(lprectPaint != NULL)
   {
    
      *lprectPaint = m_ps.rcPaint;

   }

   
   return true;


}

bool os_simple_graphics::reference_os_data(Gdiplus::Graphics * pgraphics)
{
   
   m_iType = 5;

   m_pgraphics = pgraphics;

   return true;

}


bool os_simple_graphics::create()
{

   os_simple_graphics g;

   g.from_window(NULL);
   
   return create(g.m_hdc);
   
}

bool os_simple_graphics::create_from_screen()
{
   
   return from_window(NULL);
   
}

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

   if(m_pgraphics != NULL && m_iType != 5)
   {
      
      try
      {
         
         delete m_pgraphics;

      }
      catch(...)
      {

         bOk = false;

      }
      
   }

   m_pgraphics = NULL;


   if(m_iType == 2)
   {

      try
      {

         if(!::ReleaseDC(m_oswindow, m_hdc))
         {
         
            bOk = false;

         }

      }
      catch(...)
      {

         bOk = false;

      }

   }
   else if(m_iType == 4)
   {

      try
      {

         if(!EndPaint(m_oswindow, &m_ps))
         {

            bOk = false;
         }

      }
      catch(...)
      {

         bOk = false;

      }

   }


   m_oswindow   = NULL;

   m_hdc    = NULL;

   m_iType  = 0;

   return bOk;

}


POINT os_simple_graphics::get_offset()
{

   Gdiplus::Matrix m;

   m_pgraphics->GetTransform(&m);

   Gdiplus::PointF origin(0, 0);

   m.TransformPoints(&origin);

   return point_coord((int64_t) origin.X, (int64_t) origin.Y);
}



bool os_simple_graphics::set_offset(int32_t x, int32_t y)
{
   
   Gdiplus::Matrix m;

   m.Translate((Gdiplus::REAL) x, (Gdiplus::REAL) y);

   return m_pgraphics->SetTransform(&m) == Gdiplus::Ok;

}

bool os_simple_graphics::offset(int32_t x, int32_t y)
{

   POINT pt = get_offset();

   ::offset(pt, x, y);

   return set_offset(pt.x, pt.y);

}


bool os_simple_graphics::bit_blt(int32_t x, int32_t y, int32_t cx, int32_t cy, simple_graphics & gSrc, int32_t x1, int32_t y1, uint32_t rop)
{
   
   return m_pgraphics->DrawImage(gSrc.m_bitmap.m_pbitmap, x, y, x1, y1, cx, cy, Gdiplus::UnitPixel) != FALSE;

}

bool os_simple_graphics::blend_bitmap_data(int32_t x, int32_t y, int32_t cx, int32_t cy, COLORREF * pdata)
{
   
   try
   {
   
      Gdiplus::Bitmap b(cx, cy, cx *4 , PixelFormat32bppARGB, (BYTE *) pdata);

      set_alpha_mode(::draw2d::alpha_mode_blend);

      m_pgraphics->SetCompositingQuality(Gdiplus::CompositingQualityHighQuality);

      m_pgraphics->DrawImage(&b, x, y, 0, 0, cx, cy, Gdiplus::UnitPixel);

      m_pgraphics->Flush(Gdiplus::FlushIntentionSync);

      return true;

   }
   catch(...)
   {

   }

   return false;

}

SIZE os_simple_graphics::get_text_extent(const char * psz, strsize iLen)
{

   if(iLen < 0)
      iLen = strlen(psz);

   string str(psz, iLen);

   wstring wstr(str);

   Gdiplus::RectF box;

   Gdiplus::PointF origin(0, 0);

   Gdiplus::StringFormat strFormat(Gdiplus::StringFormat::GenericTypographic());

   strFormat.SetFormatFlags(strFormat.GetFormatFlags() 
                           | Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
                           | Gdiplus::StringFormatFlagsLineLimit | Gdiplus::StringFormatFlagsNoWrap);

   m_pgraphics->MeasureString(wstr, (int32_t) wstr.get_length(), m_font.m_pfont, origin, &strFormat,  &box);

   SIZE size;

   size.cx = (LONG) box.Width;
   size.cy = (LONG) box.Height;

   return size;

}


bool os_simple_graphics::draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2, simple_pen & pen)
{

   return m_pgraphics->DrawLine(pen.m_ppen, Gdiplus::Point(x1, y1), Gdiplus::Point(x2, y2)) == Gdiplus::Ok;

}


bool os_simple_graphics::rectangle(LPCRECT lpcrect)
{
   
   bool bOk1 = fill_rect(lpcrect, m_brush);

   bool bOk2 = draw_rect(lpcrect, m_pen);

   return bOk1 && bOk2;

}

bool os_simple_graphics::draw_rect(LPCRECT lpcrect, simple_pen & pen)
{

   if(&pen == NULL)
      return true;

   if(pen.m_ppen == NULL)
      return true;
   
   return m_pgraphics->DrawRectangle(pen.m_ppen, lpcrect->left, lpcrect->top, width(lpcrect), height(lpcrect)) == Gdiplus::Ok;

}


bool os_simple_graphics::fill_rect(LPCRECT lpcrect, simple_brush & brush)
{

   if(&brush == NULL)
      return true;
   
   if(brush.m_pbrush == NULL)
      return true;
   
   return m_pgraphics->FillRectangle(brush.m_pbrush, lpcrect->left, lpcrect->top, width(lpcrect), height(lpcrect)) == Gdiplus::Ok;

}

bool os_simple_graphics::set_text_color(COLORREF cr)
{
   
   return ::SetTextColor(m_hdc, cr) != FALSE;

}

bool os_simple_graphics::set_alpha_mode(::draw2d::e_alpha_mode emode)
{

   switch(emode)
   {
   case ::draw2d::alpha_mode_blend:

      return m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver) == Gdiplus::Ok;

   case ::draw2d::alpha_mode_set:

      return m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceCopy) == Gdiplus::Ok;

   };

   return false;

}

bool os_simple_graphics::replace_clip(simple_path & path)
{

   return m_pgraphics->SetClip(path.m_ppath, Gdiplus::CombineModeReplace) == Gdiplus::Ok;

}

bool os_simple_graphics::exclude_clip(simple_path & path)
{

   return m_pgraphics->SetClip(path.m_ppath, Gdiplus::CombineModeExclude) == Gdiplus::Ok;

}

bool os_simple_graphics::replace_clip(const RECT & r)
{

   Gdiplus::Rect rect;

   rect.X = r.left;
   rect.Y = r.top;
   rect.Width = width(r);
   rect.Height = height(r);

   return m_pgraphics->SetClip(rect, Gdiplus::CombineModeReplace) == Gdiplus::Ok;

}


/* fatty fat

bool os_simple_graphics::alpha_blend(int32_t x, int32_t y, int32_t cx, int32_t cy, simple_graphics & gSrc, int32_t x1, int32_t y1, int32_t cx1, int32_t cy1, BLENDFUNCTION bf)
{

   return ::AlphaBlend(m_hdc, x, y, cx, cy, gSrc.m_hdc, x1, y1, cx1, cy1, bf) != FALSE;

}

*/

void os_simple_graphics::fill_solid_rect(LPCRECT lpRect, COLORREF clr)
{
   m_pgraphics->FillRectangle(&Gdiplus::SolidBrush(Gdiplus::Color(GetAValue(clr), GetRValue(clr), GetGValue(clr), GetBValue(clr))), lpRect->left, lpRect->top, width(lpRect), height(lpRect));
}

bool os_simple_graphics::text_out(int32_t x, int32_t y, const char * pszUtf8, strsize iSize)
{
   
   wstring wstr(pszUtf8);

   Gdiplus::StringFormat strFormat(Gdiplus::StringFormat::GenericTypographic());

   strFormat.SetFormatFlags(strFormat.GetFormatFlags() 
                           | Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
                           | Gdiplus::StringFormatFlagsLineLimit | Gdiplus::StringFormatFlagsNoWrap);

   return m_pgraphics->DrawString(wstr, (INT) wstr.get_length(), m_font.m_pfont, Gdiplus::PointF((Gdiplus::REAL) x, (Gdiplus::REAL)  y), &strFormat, m_brush.m_pbrush) == Gdiplus::Ok;

}


bool os_simple_graphics::fill_polygon(POINT * p, int32_t iCount, ::draw2d::e_fill_mode)
{

   if(m_brush.m_pbrush == NULL)
      return true;

   Gdiplus::Point * ppa = new Gdiplus::Point[iCount];

   for(int32_t i = 0; i < iCount; i++)
   {
      ppa[i].X = p[i].x;
      ppa[i].Y = p[i].y;
   }

   bool bOk = m_pgraphics->FillPolygon(m_brush.m_pbrush, ppa, 4, Gdiplus::FillModeWinding) == Gdiplus::Ok;

   delete ppa;

   return bOk;


}


bool os_simple_graphics::draw_polygon(POINT * p, int32_t iCount, ::draw2d::e_fill_mode)
{

   if (m_pen.m_ppen == NULL)
      return true;

   Gdiplus::Point * ppa = new Gdiplus::Point[iCount];

   for (int32_t i = 0; i < iCount; i++)
   {
      ppa[i].X = p[i].x;
      ppa[i].Y = p[i].y;
   }

   bool bOk = m_pgraphics->DrawPolygon(m_pen.m_ppen, ppa, 4) == Gdiplus::Ok;

   delete ppa;

   return bOk;


}


bool os_simple_graphics::draw_path(simple_path & path, simple_pen & pen)
{

   return m_pgraphics->DrawPath(pen.m_ppen, path.m_ppath) == Gdiplus::Ok;

}

bool os_simple_graphics::fill_path(simple_path & path, simple_brush & brush)
{
   
   return m_pgraphics->FillPath(brush.m_pbrush, path.m_ppath) == Gdiplus::Ok;

}

bool os_simple_graphics::is_null()
{
   return m_pgraphics == NULL;
}