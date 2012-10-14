#include "framework.h"


simple_graphics::simple_graphics()
{

   m_pdc       = NULL;

   m_player    = NULL;

   m_pclip     = NULL;

}


simple_graphics::~simple_graphics()
{

   if(m_pdc != NULL)
   {

      destroy();

   }

}

bool simple_graphics::create(ID2D1RenderTarget * pdc)
{

   if(m_pdc != NULL)
   {
    
      destroy();

   }
   
   m_pdc = pdc;

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
   
   if(m_player != NULL)
   {
      m_pdc->PopLayer();
      m_player->Release();
      m_player = NULL;
   }

   if(m_pclip != NULL)
   {
      m_pclip->Release();
      m_pclip = NULL;
   }

   if(m_pdc != NULL)
   {
      m_pdc->Release();
      m_pdc = NULL;
   }

   return true;

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

bool simple_graphics::text_out(int x, int y, const char * pszUtf8, int iSize)
{
   WCHAR * pwsz = utf8_to_16(pszUtf8);
   bool b = TextOutW(m_hdc, x, y, pwsz, (int) wcslen_dup(pwsz)) != FALSE;
   delete  [] pwsz;
   return b;
}



bool simple_graphics::draw_line(simple_pen * ppen, int x1, int y1, int x2, int y2)
{
   simple_brush b;
   b.create_solid(ppen->m_cr, *this);
   D2D1_POINT_2F p1;
   p1.x = (FLOAT) x1;
   p1.y = (FLOAT) y1;
   D2D1_POINT_2F p2;
   p2.x = (FLOAT) x2;
   p2.y = (FLOAT) y2;
   m_pdc->DrawLine(p1, p2, b.get_os_data(), ppen->m_iWidth);
}


bool simple_graphics::replace_clip(ID2D1PathGeometry * ppath)
{
   
   if(m_player != NULL)
   {

      m_pdc->PopLayer();
      m_player->Release();
      m_player = NULL;
   }

   if(m_pclip != NULL)
   {
      m_pclip->Release();
      m_pclip = NULL;
   }

   if(ppath == NULL)
      return true;

   ppath->AddRef();

   m_pclip = ppath;

   HRESULT hr = m_pdc->CreateLayer(NULL, &m_player);

   if(FAILED(hr) || m_player == NULL)
   {
      m_pclip->Release();
      m_pclip = NULL;
      return false;
   }

   m_pdc->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), m_pclip), m_player);

   return true;

}


bool simple_graphics::exclude_clip(ID2D1PathGeometry * ppath)
{

   if(ppath == NULL)
      return true;

   if(m_player != NULL)
   {

      m_pdc->PopLayer();
      m_player->Release();
      m_player = NULL;

   }

   ID2D1Factory * pfactory = NULL;

   HRESULT hr = m_pdc->GetFactory(&pfactory);

   if(FAILED(hr))
      return false;

   if(m_pclip == NULL)
   {
      ID2D1RectangleGeometry * prect;

      hr = pfactory->CreateRectangleGeometry(D2D1::InfiniteRect(), &prect);

      if(FAILED(hr) || m_pclip == NULL)
      {
         pfactory->Release();
         return false;
      }

      hr = pfactory->CreatePathGeometry(&m_pclip);

      if(FAILED(hr) || m_pclip == NULL)
      {
         pfactory->Release();
         prect->Release();
         return false;
      }

      ID2D1GeometrySink * psink = NULL;

      hr = m_pclip->Open(&psink);

      if(FAILED(hr) || psink == NULL)
      {
         pfactory->Release();
         prect->Release();
         m_pclip->Release();
         m_pclip = NULL;
         return false;
      }

      hr = prect->Simplify(D2D1_GEOMETRY_SIMPLIFICATION_OPTION_LINES, NULL, psink);

      psink->Close();
      psink->Release();
      prect->Release();

   }


   ID2D1PathGeometry * pclipNew = NULL;

   hr = pfactory->CreatePathGeometry(&pclipNew);

   if(FAILED(hr) || pclipNew == NULL)
   {
      pfactory->Release();
      m_pclip->Release();
      m_pclip = NULL;
      return false;
   }

   ID2D1GeometrySink * psink = NULL;

   hr = m_pclip->Open(&psink);

   if(FAILED(hr) || psink == NULL)
   {
      pfactory->Release();
      m_pclip->Release();
      m_pclip = NULL;
      pclipNew->Release();
      return false;
   }
   
   
   m_pclip->CombineWithGeometry(ppath, D2D1_COMBINE_MODE_EXCLUDE, NULL, psink);

   psink->Close();
   psink->Release();
   pfactory->Release();
   m_pclip->Release();
   m_pclip = pclipNew;


   HRESULT hr = m_pdc->CreateLayer(NULL, &m_player);

   if(FAILED(hr) || m_player == NULL)
   {
      m_pclip->Release();
      m_pclip = NULL;
      return false;
   }

   m_pdc->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), m_pclip), m_player);

   return true;

}