#include "framework.h"

#define d2d1_fax_options D2D1_FACTORY_OPTIONS // fax of merde
#define single_threaded D2D1_FACTORY_TYPE_SINGLE_THREADED // ???? muliple performance multi thread hidden option there exists cost uses?

os_simple_graphics::os_simple_graphics()
{

   m_pdc       = NULL;

   m_player    = NULL;

   m_pclip     = NULL;

}


os_simple_graphics::~os_simple_graphics()
{

   if(m_pdc != NULL)
   {

      destroy();

   }

}

bool os_simple_graphics::reference_os_data(ID2D1DeviceContext * pdc)
{

   if(m_pdc != NULL)
   {
    
      destroy();

   }
   
   m_pdc = pdc;

   m_iType = 1;

   return true;

}

bool os_simple_graphics::create_device()
{
   if(m_iType != 0)
      destroy();

   if(!create_device())

   TlsGetD2D1Factory1()->CreateDevice(TlsGetDXGIDevice(), &m_pd);

   m_pd->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &m_pdc);

   if(m_pdc == NULL)
   {
      m_pd->Release();
      m_pdc = NULL;
      return false;
   }


}

bool os_simple_graphics::create_from_bitmap(simple_bitmap & b)
{

   if(m_iType != 0)
      destroy();

   if(!create_device())
      return false;

   m_pdc->SetTarget(b.m_pbitmap);

   m_iType = 3;
   
   return true;

}

bool os_simple_graphics::from_window( Windows::UI::Core::CoreWindow ^ w)
{
   // Allocate a descriptor.
   DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {0};
   swapChainDesc.Width = 0;                                     // use automatic sizing
   swapChainDesc.Height = 0;
   swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;           // this is the most common swapchain format
   swapChainDesc.Stereo = false; 
   swapChainDesc.SampleDesc.Count = 1;                          // don't use multi-sampling
   swapChainDesc.SampleDesc.Quality = 0;
   swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
   swapChainDesc.BufferCount = 2;                               // use double buffering to enable flip
   swapChainDesc.Scaling = DXGI_SCALING_NONE;
   swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; // all Metro style apps must use this SwapEffect
   swapChainDesc.Flags = 0;


   TlsGetDXGIDevice()->GetAdapter(&m_pad);

   m_pad->GetParent(IID_PPV_ARGS(&m_pfax));

   // Get the final swap chain for this window from the DXGI factory.
   /*m_pfax->CreateSwapChainForCoreWindow(
      TlsGetD3D11Device1()->Get(), 
      reinterpret_cast<IUnknown*>(w), 
      &swapChainDesc, 
      nullptr,    // allow on all displays
      &m_swapChain);*/

        // Ensure that DXGI doesn't queue more than one frame at a time.
   //TlsGetDXGIDevice()->SetMaximumFrameLatency(1)

}


ID2D1Factory1 * TlsGetD2D1Factory1()
{

   ID2D1Factory1 * pfactory = (ID2D1Factory1 *) TlsGetValue(TLS_D2D1_FACTORY1);

   if(pfactory != NULL)
      return pfactory;

   d2d1_fax_options options;
   memset(&options, 0, sizeof(options));

   HRESULT hr = ::D2D1CreateFactory(single_threaded, __uuidof(ID2D1Factory1), &options, (void **) &pfactory);

   TlsSetValue(TLS_D2D1_FACTORY1, pfactory);

   if(FAILED(hr))
       return NULL;

   return pfactory;

}


ID3D11Device * TlsGetD3D11Device()
{

   ID3D11Device * pdevice = (ID3D11Device *) TlsGetValue(TLS_d3_1);

   if(pdevice != NULL)
      return pdevice;

   // This flag adds support for surfaces with a different color channel ordering than the API default.
   // You need it for compatibility with Direct2D.
   UINT create = D3D11_CREATE_DEVICE_BGRA_SUPPORT;


   // This array defines the set of DirectX hardware feature levels this app  supports.
   // The ordering is important and you should  preserve it.
   // Don't forget to declare your app's minimum required feature level in its
   // description.  All apps are assumed to support 9.1 unless otherwise stated.
   D3D_FEATURE_LEVEL featurelevel[] = 
   {
      D3D_FEATURE_LEVEL_11_1 /*,
      D3D_FEATURE_LEVEL_11_0,
      D3D_FEATURE_LEVEL_10_1,
      D3D_FEATURE_LEVEL_10_0,
      D3D_FEATURE_LEVEL_9_3,
      D3D_FEATURE_LEVEL_9_2,
      D3D_FEATURE_LEVEL_9_1*/
   };

   D3D_FEATURE_LEVEL lv;

   d2d1_fax_options options;
   memset(&options, 0, sizeof(options));

   ID3D11DeviceContext * pcontext = NULL;

   HRESULT hr = 
        D3D11CreateDevice(
            nullptr,                    // specify null to use the default adapter
            D3D_DRIVER_TYPE_HARDWARE,
            0,                          
            create,              // optionally set debug and Direct2D compatibility flags
            featurelevel,              // list of feature levels this app can support
            ARRAYSIZE(featurelevel),   // number of possible feature levels
            D3D11_SDK_VERSION,          // always set this to D3D11_SDK_VERSION for Metro style apps.
            &pdevice,                    // returns the Direct3D device created
            &lv,            // returns feature level of device created
            &pcontext                    // returns the device immediate context
            );

   TlsSetValue(TLS_d3_1, pdevice);
   TlsSetValue(TLS_d3_2, pcontext);

   if(FAILED(hr))
       return NULL;

   return pdevice;

}


ID3D11DeviceContext * TlsGetD3D11DeviceContext()
{

   ID3D11DeviceContext * pcontext = (ID3D11DeviceContext *) TlsGetValue(TLS_d3_2);

   if(pcontext != NULL)
      return pcontext;

   ID3D11Device * pdevice = (ID3D11Device *) TlsGetValue(TLS_d3_1);

   if(pdevice == NULL)
      return NULL;

   pcontext = (ID3D11DeviceContext *) TlsGetValue(TLS_d3_2);

   if(pcontext == NULL)
      return NULL;
   
   return pcontext;

}

ID3D11Device1 * TlsGetD3D11Device1()
{

   ID3D11Device1 * pdevice1 = (ID3D11Device1 *) TlsGetValue(TLS_d3_3);

   if(pdevice1 != NULL)
      return pdevice1;

   ID3D11Device * pdevice = (ID3D11Device *) TlsGetValue(TLS_d3_1);

   if(pdevice == NULL)
      return NULL;

   HRESULT hr = pdevice->QueryInterface(__uuidof(ID3D11Device1), (void **) &pdevice1);

   TlsSetValue(TLS_d3_3, pdevice1);

   if(pdevice1 == NULL)
      return NULL;

   return pdevice1;

}

IDXGIDevice * TlsGetDXGIDevice()
{

   IDXGIDevice * pdxgidevice = (IDXGIDevice *) TlsGetValue(TLS_d3_4);

   if(pdxgidevice == NULL)
      return NULL;

   ID3D11Device1 * pdevice1 = (ID3D11Device1 *) TlsGetValue(TLS_d3_3);

   if(pdevice1 == NULL)
      return NULL;

   HRESULT hr = pdevice1->QueryInterface(__uuidof(IDXGIDevice), (void **) &pdxgidevice);

   TlsSetValue(TLS_d3_4, pdxgidevice);

   if(pdxgidevice == NULL)
      return NULL;

   return pdxgidevice;

}



/*bool os_simple_graphics::detach_bitmap()
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

}*/

/*bool os_simple_graphics::from_entire_window(HWND hwnd)
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


bool os_simple_graphics::from_window(HWND hwnd)
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

bool os_simple_graphics::from_window_paint(HWND hwnd, LPRECT lprectPaint)
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
    
}*/

/*
bool os_simple_graphics::reference_os_data(HDC hdc)
{
   
   m_iType = 5;

   m_hdc = hdc;

   return true;

}
*/

bool os_simple_graphics::create()
{
   
   os_simple_graphics g;

   g.from_window(NULL);
   
   return create(g);
   
}

bool os_simple_graphics::create(os_simple_graphics & g)
{
   
   return create(g.m_hdc);
   
}

bool os_simple_graphics::create_from_screen()
{
   
   return from_window(NULL);
   
}

bool os_simple_graphics::select(simple_font & font)
{
   
   HFONT hfontOld = (HFONT) ::SelectObject(m_hdc, font.m_hfont);

   if(m_hfontOld == NULL)
      m_hfontOld = hfontOld;

   return hfontOld != NULL;

}

bool os_simple_graphics::select(simple_brush & brush)
{
   
   HBRUSH hbrushOld = (HBRUSH) ::SelectObject(m_hdc, brush.m_hbrush);

   if(m_hbrushOld == NULL)
      m_hbrushOld = hbrushOld;

   return hbrushOld != NULL;

}

bool os_simple_graphics::select(simple_pen & pen)
{
   
   HPEN hpenOld = (HPEN) ::SelectObject(m_hdc, pen.m_hpen);

   if(m_hpenOld == NULL)
      m_hpenOld = hpenOld;

   return hpenOld != NULL;

}

bool os_simple_graphics::destroy()
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

bool os_simple_graphics::set_offset(int x, int y)
{
   
   POINT ptViewport;

   if(!SetViewportOrgEx(m_hdc, x, y, &ptViewport))
      return false;

   return true;

}

bool os_simple_graphics::offset(int x, int y)
{

   POINT ptViewport;

   if(!OffsetViewportOrgEx(m_hdc, x, y, &ptViewport))
      return false;

   return true;

}


bool os_simple_graphics::bit_blt(int x, int y, int cx, int cy, os_simple_graphics & gSrc, int x1, int y1, DWORD rop)
{
   
   return ::BitBlt(m_hdc, x, y, cx, cy, gSrc.m_hdc, x1, y1, rop) != FALSE;

}

bool os_simple_graphics::blend_bitmap_data(int x, int y, int cx, int cy, COLORREF * pdata)
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

SIZE os_simple_graphics::get_text_extent(const char * psz, int iLen)
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


bool os_simple_graphics::rectangle(LPCRECT lpcrect)
{
   
   return ::Rectangle(m_hdc, lpcrect->left, lpcrect->top, lpcrect->right, lpcrect->bottom) != FALSE;

}


bool os_simple_graphics::draw_rect(LPCRECT lpcrect, simple_pen & pen)
{

   if(&pen == NULL)
      return true;

   if(pen.get_os_brush() == NULL)
      return true;

   D2D1_RECT_F r;

   r.left      = lpcrect->left;
   r.top       = lpcrect->top;
   r.right     = lpcrect->right;
   r.bottom    = lpcrect->bottom;

   m_pdc->DrawRectangle(r, m_pen.get_os_brush(), m_pen.m_iWidth);

   return true;

}

bool os_simple_graphics::fill_rect(LPCRECT lpcrect, simple_brush & brush)
{
   
   return ::FillRect(m_hdc, lpcrect, brush.m_hbrush) != FALSE;

}

bool os_simple_graphics::set_text_color(COLORREF cr)
{
   
   return ::SetTextColor(m_hdc, cr) != FALSE;

}

bool os_simple_graphics::set_alpha_mode(::ca::e_alpha_mode emode)
{

   switch(emode)
   {
   
   case ::ca::alpha_mode_blend:
   
      return SUCCEEDED(m_pdc->SetPrimitiveBlend(D2D1_PRIMITIVE_BLEND_SOURCE_OVER));

   case ::ca::alpha_mode_copy:
   
      return SUCCEEDED(m_pdc->SetPrimitiveBlend(D2D1_PRIMITIVE_BLEND_SOURCE_COPY));

   };

   return false;

}

bool os_simple_graphics::alpha_blend(int x, int y, int cx, int cy, os_simple_graphics & gSrc, int x1, int y1, int cx1, int cy1, BLENDFUNCTION bf)
{

   return ::AlphaBlend(m_hdc, x, y, cx, cy, gSrc.m_hdc, x1, y1, cx1, cy1, bf) != FALSE;

}

void os_simple_graphics::fill_solid_rect(LPCRECT lpRect, COLORREF clr)
{
   ::SetBkColor(m_hdc, clr);
   ::ExtTextOut(m_hdc, 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
}

bool os_simple_graphics::draw_path(simple_path & path, simple_pen & pen)
{
   
   return SUCCEEDED(m_pdc->DrawGeometry(path.get_os_data(), pen.get_os_brush(), pen.m_iWidth));

}

bool os_simple_graphics::fill_path(simple_path & path, simple_brush & brush)
{
   
   return SUCCEEDED(m_pdc->DrawGeometry(path.get_os_data(), brush.get_os_brush(), pen.m_iWidth));

}

bool os_simple_graphics::fill_polygon(LPPOINT lpa, int iCount, ::ca::e_fill_mode emode)
{
   m_pgraphics->FillPolygon();
}

bool os_simple_graphics::text_out(int x, int y, const char * pszUtf8, int iSize)
{
   WCHAR * pwsz = utf8_to_16(pszUtf8);
   bool b = TextOutW(m_hdc, x, y, pwsz, (int) wcslen_dup(pwsz)) != FALSE;
   delete  [] pwsz;
   return b;
}



bool os_simple_graphics::draw_line(simple_pen * ppen, int x1, int y1, int x2, int y2)
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

bool os_simple_graphics::replace_clip(const RECT & rect)
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

   simple_path path(true);

   path.add_rect(rect);

   if(path.get_os_data() == NULL)
      return true;

   path.get_os_data()->AddRef();

   m_pclip = path.get_os_data();

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


bool os_simple_graphics::replace_clip(ID2D1PathGeometry * ppath)
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


bool os_simple_graphics::exclude_clip(ID2D1PathGeometry * ppath)
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


