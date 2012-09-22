#include "framework.h"
#include <gdiplus.h>



bool simple_graphics::text_out(int x, int y, const char * pszUtf8, int iSize)
{
   WCHAR * pwsz = utf8_to_16(pszUtf8);
   bool b = TextOutW(m_hdc, x, y, pwsz, (int) wcslen_dup(pwsz)) != FALSE;
   delete  [] pwsz;
   return b;
}

bool simple_font::create_point(int nPointSize, const char * lpszFaceName, simple_graphics * pg)
{

   return create_point_bold(nPointSize, lpszFaceName, FALSE, pg);

}

bool simple_font::create_point_bold(int nPointSize, const char * lpszFaceName, int iBold, simple_graphics * pg)
{

   LOGFONT logFont;

   memset_dup(&logFont, 0, sizeof(LOGFONT));

   logFont.lfCharSet = DEFAULT_CHARSET;

   simple_graphics g;

   if (pg == NULL)
   {

      g.create_from_screen();

      pg = &g;

   }

   // convert nPointSize to logical units based on pgraphics
   POINT pt;
   // 72 points/inch, 10 decipoints/point
   pt.y = ::MulDiv(::GetDeviceCaps(g.m_hdc, LOGPIXELSY), logFont.lfHeight, 720);
   pt.x = 0;
   ::DPtoLP(g.m_hdc, &pt, 1);
   POINT ptOrg = { 0, 0 };
   ::DPtoLP(g.m_hdc, &ptOrg, 1);
   logFont.lfHeight = -abs(pt.y - ptOrg.y);

   logFont.lfWeight = iBold ? FW_BOLD : FW_NORMAL;

   strncpy_dup(logFont.lfFaceName, lpszFaceName, sizeof(logFont.lfFaceName));

   return create_indirect(&logFont);

}



                                        
simple_graphics::simple_graphics()
{

   m_hdc    = NULL;

   m_hwnd   = NULL;

   m_iType  = 0;

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

bool simple_graphics::alpha_blend(int x, int y, int cx, int cy, simple_graphics & gSrc, int x1, int y1, int cx1, int cy1, BLENDFUNCTION bf)
{

   return ::AlphaBlend(m_hdc, x, y, cx, cy, gSrc.m_hdc, x1, y1, cx1, cy1, bf) != FALSE;

}

void simple_graphics::fill_solid_rect(LPCRECT lpRect, COLORREF clr)
{
   ::SetBkColor(m_hdc, clr);
   ::ExtTextOut(m_hdc, 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
}



simple_brush::simple_brush()
{

   m_hbrush = NULL;

}

simple_brush::~simple_brush()
{
   
   if(m_hbrush != NULL)
   {

      destroy();

   }

}

bool simple_brush::create_solid(COLORREF cr)
{

   if(m_hbrush != NULL)
      destroy();

   m_bDelete = true;

   m_hbrush = ::CreateSolidBrush(cr);

   if(m_hbrush == NULL)
      return false;

   return true;

}


bool simple_brush::from_stock(int iId)
{

   if(m_hbrush != NULL)
      destroy();

   m_bDelete = false;

   m_hbrush = (HBRUSH) ::GetStockObject(iId);

   if(m_hbrush == NULL)
      return false;

   if(::GetObjectType(m_hbrush) != OBJ_BRUSH)
   {
      
      m_hbrush = NULL;

      return false;

   }

   return true;

}



bool simple_brush::destroy()
{

   if(!m_bDelete)
      return false;
   
   if(m_hbrush == NULL)
      return true;


   bool bOk = ::DeleteObject(m_hbrush) != FALSE;

   m_hbrush = NULL;

   if(!bOk)
      return false;

   return true;

}




simple_bitmap::simple_bitmap()
{
   
   m_hbitmap = NULL;

}

simple_bitmap::~simple_bitmap()
{
   
   if(m_hbitmap != NULL)
   {

      destroy();

   }

}

bool simple_bitmap::create(int cx, int cy, COLORREF ** ppdata)
{

   BITMAPINFO m_Info;

	m_Info.bmiHeader.biSize=sizeof (BITMAPINFOHEADER);
	m_Info.bmiHeader.biWidth=cx;
	m_Info.bmiHeader.biHeight=cy;
	m_Info.bmiHeader.biPlanes=1;
	m_Info.bmiHeader.biBitCount=32;
	m_Info.bmiHeader.biCompression=BI_RGB;
	m_Info.bmiHeader.biSizeImage=cx*cy*4;

	m_hbitmap = CreateDIBSection ( NULL, &m_Info, DIB_RGB_COLORS, (void **)ppdata, NULL, 0);

   if(m_hbitmap == NULL)
      return false;

   return true;

}


bool simple_bitmap::create_from_data(int cx, int cy, COLORREF * pdata)
{

   m_hbitmap = ::CreateBitmap(cx, cy, 1, 32, pdata);

   if(m_hbitmap == NULL)
      return false;

   return true;

}



bool simple_bitmap::destroy()
{
   
   if(m_hbitmap == NULL)
      return true;


   bool bOk = ::DeleteObject(m_hbitmap) != FALSE;

   m_hbitmap = NULL;

   if(!bOk)
      return false;

   return true;

}




simple_font::simple_font()
{
   
   m_hfont = NULL;

}

simple_font::~simple_font()
{
   
   if(m_hfont != NULL)
   {

      destroy();

   }

}

bool simple_font::create_indirect(LPLOGFONT  lplf)
{

   m_hfont = ::CreateFontIndirect(lplf);

   if(m_hfont == NULL)
      return false;


   return true;

}

bool simple_font::destroy()
{
   
   if(m_hfont == NULL)
      return true;


   bool bOk = ::DeleteObject(m_hfont) != FALSE;

   m_hfont = NULL;

   if(!bOk)
      return false;

   return true;

}


simple_pen::simple_pen()
{
   
   m_hpen = NULL;

}

simple_pen::~simple_pen()
{
   
   if(m_hpen != NULL)
   {

      destroy();

   }

}

bool simple_pen::create_solid(int iWidth, COLORREF cr)
{

   m_hpen = ::CreatePen(PS_SOLID, iWidth, cr);

   if(m_hpen == NULL)
      return false;

   return TRUE;

}

bool simple_pen::destroy()
{
   
   if(m_hpen == NULL)
      return true;


   bool bOk = ::DeleteObject(m_hpen) != FALSE;

   m_hpen = NULL;

   if(!bOk)
      return false;

   return true;

}


