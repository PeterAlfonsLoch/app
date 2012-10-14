#include "framework.h"
#undef new
#include <gdiplus.h>


simple_graphics::simple_graphics()
{

   m_pgraphics    = NULL;

   m_hwnd         = NULL;

   m_iType        = 0;

   m_pbitmap      = NULL;

   m_pbrush       = NULL;

   m_pfont        = NULL;

   m_ppen         = NULL;

}


simple_graphics::~simple_graphics()
{

   if(m_hdc != NULL && m_iType != 0)
   {

      destroy();

   }

}

bool simple_graphics::create(HDC hdc)
{

   if(m_iType != 0)
      destroy();
   
   m_hdc = ::CreateCompatibleDC(hdc);

   if(m_hdc == NULL)
      return false;
   
   ::ReleaseDC(NULL, hdc);
   
   m_iType = 1;
   
   return true;

}

bool simple_graphics::create_from_bitmap(simple_bitmap & b)
{

   if(m_iType != 0)
      destroy();
   
   m_hdc = ::CreateCompatibleDC(NULL);

   if(m_hdc == NULL)
      return false;

   m_hbitmapOld = (HBITMAP) ::SelectObject(m_hdc, b.m_hbitmap);

   if(m_hbitmapOld == NULL)
   {
      
      ::DeleteDC(m_hdc);
      
      m_hdc = NULL;

      return false;

   }
   
   m_iType = 3;
   
   return true;

}

bool simple_graphics::detach_bitmap()
{

   if(m_iType != 0)
      destroy();
   
   if(m_hdc == NULL)
      return false;

   if(m_hbitmapOld == NULL)
      return false;

   if(m_iType != 3)
      return false;

   HBITMAP hbitmap = (HBITMAP) ::SelectObject(m_hdc, m_hbitmapOld);

   m_iType = 1;
      
   return hbitmap != NULL;

}

bool simple_graphics::from_entire_window(HWND hwnd)
{

   if(m_iType != 0)
      destroy();

   m_hdc = ::GetWindowDC(hwnd);

   if(m_hdc == NULL)
      return false;

   m_hwnd = hwnd;

   m_iType = 2;
   
   return true;

}


bool simple_graphics::from_window(HWND hwnd)
{

   if(m_iType != 0)
      destroy();

   m_hdc = ::GetDC(hwnd);

   if(m_hdc == NULL)
      return false;

   m_hwnd = hwnd;

   m_iType = 2;
   
   return true;

}

bool simple_graphics::from_window_paint(HWND hwnd, LPRECT lprectPaint)
{

   if(m_iType != 0)
      destroy();

    m_hdc = BeginPaint(hwnd, &m_ps);

    if(m_hdc == NULL)
       return false;
    
    m_hwnd = hwnd;

    if(lprectPaint != NULL)
    {
    
       *lprectPaint = m_ps.rcPaint;

    }

    m_iType = 4;

    return true;
    
}

bool simple_graphics::reference_os_data(HDC hdc)
{
   
   m_iType = 5;

   m_hdc = hdc;

   return true;

}


bool simple_graphics::create()
{
   
   simple_graphics g;

   g.from_window(NULL);
   
   return create(g);
   
}

bool simple_graphics::create(simple_graphics & g)
{
   
   return create(g.m_hdc);
   
}

bool simple_graphics::create_from_screen()
{
   
   return from_window(NULL);
   
}

bool simple_graphics::select(simple_font & font)
{
   
   HFONT hfontOld = (HFONT) ::SelectObject(m_hdc, font.m_hfont);

   if(m_hfontOld == NULL)
      m_hfontOld = hfontOld;

   return hfontOld != NULL;

}

bool simple_graphics::select(simple_brush & brush)
{
   
   HBRUSH hbrushOld = (HBRUSH) ::SelectObject(m_hdc, brush.m_hbrush);

   if(m_hbrushOld == NULL)
      m_hbrushOld = hbrushOld;

   return hbrushOld != NULL;

}

bool simple_graphics::select(simple_pen & pen)
{
   
   HPEN hpenOld = (HPEN) ::SelectObject(m_hdc, pen.m_hpen);

   if(m_hpenOld == NULL)
      m_hpenOld = hpenOld;

   return hpenOld != NULL;

}

bool simple_graphics::destroy()
{
   
   bool bOk = true;

   bool bOkOldBitmap = true;

   bool bOkOldPen = true;

   bool bOkOldBrush = true;

   bool bOkOldFont = true;

   if(m_hbitmapOld != NULL)
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

   }


   if(m_iType == 1)
   {
      
      bOk = ::DeleteDC(m_hdc) != FALSE;

   }
   else if(m_iType == 2)
   {

      bOk = ::ReleaseDC(m_hwnd, m_hdc) != FALSE;

   }
   else if(m_iType == 3)
   {

      bOk = ::DeleteDC(m_hdc) != FALSE;

   }
   else if(m_iType == 4)
   {

      bOk = EndPaint(m_hwnd, &m_ps) != FALSE;

   }

   m_hwnd   = NULL;

   m_hdc    = NULL;

   m_iType  = 0;

   return bOk && bOkOldBitmap && bOkOldBrush && bOkOldFont && bOkOldPen;

}

bool simple_graphics::set_offset(int x, int y)
{
   
   POINT ptViewport;

   if(!SetViewportOrgEx(m_hdc, x, y, &ptViewport))
      return false;

   return true;

}

bool simple_graphics::offset(int x, int y)
{

   POINT ptViewport;

   if(!OffsetViewportOrgEx(m_hdc, x, y, &ptViewport))
      return false;

   return true;

}


bool simple_graphics::bit_blt(int x, int y, int cx, int cy, simple_graphics & gSrc, int x1, int y1, DWORD rop)
{
   
   return ::BitBlt(m_hdc, x, y, cx, cy, gSrc.m_hdc, x1, y1, rop) != FALSE;

}

bool simple_graphics::blend_bitmap_data(int x, int y, int cx, int cy, COLORREF * pdata)
{
   
   try
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

   return false;

}

SIZE simple_graphics::get_text_extent(const char * psz, int iLen)
{

   if(iLen < 0)
      iLen = strlen(psz);

   vsstring str(psz, iLen);

   wstring wstr(str);

   SIZE size;

   if(!::GetTextExtentPointW(m_hdc, wstr, wstr.get_length(), &size))
   {

      size.cx = 0;

      size.cy = 0;

   }

   return size;

}


bool simple_graphics::draw_line(int x1, int y1, int x2, int y2, simple_pen & pen)
{

   return m_pgraphics->DrawLine(pen.m_ppen, Gdiplus::Point(x1, y1), Gdiplus::Point(x2, y2));

}


bool simple_graphics::rectangle(LPCRECT lpcrect)
{
   
   return ::Rectangle(m_hdc, lpcrect->left, lpcrect->top, lpcrect->right, lpcrect->bottom) != FALSE;

}

bool simple_graphics::fill_rect(LPCRECT lpcrect, simple_brush & brush)
{
   
   return ::FillRect(m_hdc, lpcrect, brush.m_hbrush) != FALSE;

}

bool simple_graphics::set_text_color(COLORREF cr)
{
   
   return ::SetTextColor(m_hdc, cr) != FALSE;

}

bool simple_graphics::set_alpha_mode(::ca::e_alpha_mode emode)
{

   switch(emode)
   {
   case ::ca::alpha_mode_blend:
      return m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver);
   case ::ca::alpha_mode_set:
      return m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceCopy);
   };

   return false;

}

bool simple_graphics::replace_clip(simple_path & path)
{

   return m_pgraphics->SetClip(path.m_ppath, Gdiplus::CombineModeReplace) == Gdiplus::Ok;

}

bool simple_graphics::exclude_clip(simple_path & path)
{

   return m_pgraphics->SetClip(path.m_ppath, Gdiplus::CombineModeExclude) == Gdiplus::Ok;

}

bool replace_clip(const RECT & r)
{

   Gdiplus::Rect rect;

   rect.X = r.left;
   rect.Y = r.top;
   rect.Width = width(r);
   rect.Height = height(r);

   return m_pgraphics->SetClip(rect, Gdiplus::CombineModeReplace) == Gdiplus::Ok;

}

bool simple_graphics::alpha_blend(int x, int y, int cx, int cy, simple_graphics & gSrc, int x1, int y1, int cx1, int cy1, BLENDFUNCTION bf)
{

   return ::AlphaBlend(m_hdc, x, y, cx, cy, gSrc.m_hdc, x1, y1, cx1, cy1, bf) != FALSE;

}

void simple_graphics::fill_solid_rect(LPCRECT lpRect, COLORREF clr)
{
   ::SetBkColor(m_hdc, clr);
   ::ExtTextOut(m_hdc, 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
}

bool simple_graphics::text_out(int x, int y, const char * pszUtf8, int iSize)
{
   WCHAR * pwsz = utf8_to_16(pszUtf8);
   bool b = TextOutW(m_hdc, x, y, pwsz, (int) wcslen_dup(pwsz)) != FALSE;
   delete  [] pwsz;
   return b;
}


bool simple_graphics::fill_polygon(POINT * p, int iCount, ::ca::e_fill_mode)
{

   Gdiplus::Point * ppa = new Gdiplus::Point[iCount];

   for(int i = 0; i < iCount; i++)
   {
      ppa[i].X = p[i].x;
      ppa[i].Y = p[i].y;
   }

   bool bOk = m_pgraphics->FillPolygon(m_brush.m_pbrush, ppa, 4, Gdiplus::FillModeWinding) == Gdiplus::Ok;

   delete ppa;

   return bOk;


}




