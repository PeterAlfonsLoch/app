#include "framework.h"


// Windows Desktop Thread Local Storage for Draw2d Direct2d plugin



   Microsoft::WRL::ComPtr<IDWriteFactory> g_pwritefactory;
   Microsoft::WRL::ComPtr<ID2D1Factory1> g_pd2factory;
   Microsoft::WRL::ComPtr<ID2D1Device> g_pd2device;
   Microsoft::WRL::ComPtr<ID2D1DeviceContext> g_pd2devicecontext;
   Microsoft::WRL::ComPtr<ID3D11DeviceContext> g_pd3devicecontext;
   Microsoft::WRL::ComPtr<ID3D11DeviceContext1> g_pd3devicecontext1;
   Microsoft::WRL::ComPtr<ID3D11Device> g_pd3device;
   Microsoft::WRL::ComPtr<ID3D11Device1> g_pd3device1;
   Microsoft::WRL::ComPtr<IDXGIDevice> g_pdxgidevice;
   D3D_FEATURE_LEVEL g_featurelevel;


   namespace draw2d_direct2d
   {

void factory_exchange::draw2d_direct2d_initialize()
{
      // This flag adds support for surfaces with a different color channel ordering
      // than the API default. It is required for compatibility with Direct2D.
      UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
      // If the project is in a debug build, enable debugging via SDK Layers with this flag.
      creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

      // This array defines the set of DirectX hardware feature levels this app will support.
      // Note the ordering should be preserved.
      // Don't forget to declare your application's minimum required feature level in its
      // description.  All applications are assumed to support 9.1 unless otherwise stated.
      D3D_FEATURE_LEVEL featureLevels[] =
      {
         D3D_FEATURE_LEVEL_11_1,
         D3D_FEATURE_LEVEL_11_0,
         D3D_FEATURE_LEVEL_10_1,
         D3D_FEATURE_LEVEL_10_0,
         D3D_FEATURE_LEVEL_9_3,
         D3D_FEATURE_LEVEL_9_2,
         D3D_FEATURE_LEVEL_9_1
      };

      // Create the Direct3D 11 API device object and a corresponding context.
      Microsoft::WRL::ComPtr<ID3D11Device> device;
      Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
      ::draw2d_direct2d::throw_if_failed(
         D3D11CreateDevice(
         nullptr,                    // Specify nullptr to use the default adapter.
         D3D_DRIVER_TYPE_HARDWARE,
         0,
         creationFlags,              // Set debug and Direct2D compatibility flags.
         featureLevels,              // List of feature levels this app can support.
         ARRAYSIZE(featureLevels),
         D3D11_SDK_VERSION,          // Always set this to D3D11_SDK_VERSION for Metro style apps.
         &device,                    // Returns the Direct3D device created.
         &g_featurelevel,            // Returns feature level of device created.
         &context                    // Returns the device immediate context.
         )
         );

      // Get the Direct3D 11.1 API device and context interfaces.
      ::draw2d_direct2d::throw_if_failed(
         device.As(&g_pd3device)
         );
      ::draw2d_direct2d::throw_if_failed(
         device.As(&g_pd3device1)
         );

      ::draw2d_direct2d::throw_if_failed(
         context.As(&g_pd3devicecontext)
         );
      ::draw2d_direct2d::throw_if_failed(
         context.As(&g_pd3devicecontext1)
         );

      // Get the underlying DXGI device of the Direct3D device.
      ::draw2d_direct2d::throw_if_failed(
         device.As(&g_pdxgidevice)
         );

      // Create the Direct2D device object and a corresponding context.
      ::draw2d_direct2d::throw_if_failed(
         GetD2D1Factory1()->CreateDevice(g_pdxgidevice.Get(), &g_pd2device)
         );

      ::draw2d_direct2d::throw_if_failed(
         g_pd2device->CreateDeviceContext(
         D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
         //D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS,
         &g_pd2devicecontext
         )
         );

      ID2D1DeviceContext * pdevicecontext = g_pd2devicecontext.Get();

      System.m_pdevicecontext    = pdevicecontext;
      //System.m_pmutexDc          = new mutex(get_app());


}

   } // namespace draw2d_direct2d

#define d2d1_fax_options D2D1_FACTORY_OPTIONS // fax of merde
#define single_threaded D2D1_FACTORY_TYPE_MULTI_THREADED // ???? muliple performance multi thread hidden option there exists cost uses?

CLASS_DECL_DRAW2D_DIRECT2D IDWriteFactory * TlsGetWriteFactory(bool bCreate)
{

   if(g_pwritefactory != NULL || !bCreate)
      return g_pwritefactory.Get();

   HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &g_pwritefactory);

   if(FAILED(hr))
      return NULL;

   return g_pwritefactory.Get();

}


ID2D1Factory1 * GetD2D1Factory1(bool bCreate)
{


   if(g_pd2factory != NULL || !bCreate)
      return g_pd2factory.Get();

   d2d1_fax_options options;
   memset(&options, 0, sizeof(options));

   HRESULT hr = ::D2D1CreateFactory(single_threaded, __uuidof(ID2D1Factory1), &options, &g_pd2factory);

   if(FAILED(hr))
       return NULL;

   return g_pd2factory.Get();

}


ID3D11Device * TlsGetD3D11Device()
{

   return g_pd3device.Get();

}


ID3D11DeviceContext * TlsGetD3D11DeviceContext()
{

   return g_pd3devicecontext.Get();

}

ID3D11DeviceContext1 * TlsGetD3D11DeviceContext1()
{

   return g_pd3devicecontext1.Get();

}

ID3D11Device1 * TlsGetD3D11Device1()
{

   return g_pd3device1.Get();

}

IDXGIDevice * TlsGetDXGIDevice()
{

   return g_pdxgidevice.Get();

}
ID2D1DeviceContext * TlsGetD2D1DeviceContext()
{

   return g_pd2devicecontext.Get();

}

ID2D1Device * TlsGetD2D1Device()
{

   return g_pd2device.Get();

}

CLASS_DECL_DRAW2D_DIRECT2D float point_dpi(float points)
{

   FLOAT dpiX, dpiY;

   GetD2D1Factory1()->GetDesktopDpi(&dpiX, &dpiY);

	return points * dpiY / 72.f;

}

CLASS_DECL_DRAW2D_DIRECT2D float dpiy(float y)
{
   
   FLOAT dpiX, dpiY;

   GetD2D1Factory1()->GetDesktopDpi(&dpiX, &dpiY);

   return y * dpiY / 96.f;

}

CLASS_DECL_DRAW2D_DIRECT2D float dpix(float x)
{
   
   FLOAT dpiX, dpiY;

   GetD2D1Factory1()->GetDesktopDpi(&dpiX, &dpiY);

   return x * dpiX / 96.f;

}


CLASS_DECL_DRAW2D_DIRECT2D float y_dpi(float y)
{
   
   FLOAT dpiX, dpiY;

   GetD2D1Factory1()->GetDesktopDpi(&dpiX, &dpiY);

   return y / dpiY;

}

CLASS_DECL_DRAW2D_DIRECT2D float x_dpi(float x)
{
   
   FLOAT dpiX, dpiY;

   GetD2D1Factory1()->GetDesktopDpi(&dpiX, &dpiY);

   return x / dpiX;

}



