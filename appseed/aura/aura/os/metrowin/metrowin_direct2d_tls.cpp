#include "framework.h"


#define d2d1_fax_options D2D1_FACTORY_OPTIONS // fax of merde
#define single_threaded D2D1_FACTORY_TYPE_MULTI_THREADED // ???? muliple performance multi thread hidden option there exists cost uses?

IDWriteFactory * TlsGetWriteFactory()
{

   IDWriteFactory * pfactory = (IDWriteFactory *) TlsGetValue(TLS_WRITE_FACTORY);

   if(pfactory != NULL)
      return pfactory;

   HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pfactory));

   TlsSetValue(TLS_WRITE_FACTORY, pfactory);

   if(FAILED(hr))
      return NULL;

   return pfactory;

}


ID2D1Factory1 * GetD2D1Factory1()
{

   static ID2D1Factory1 * s_pfactory = NULL;

   if(s_pfactory != NULL)
      return s_pfactory;

   d2d1_fax_options options;
   memset(&options, 0, sizeof(options));

   HRESULT hr = ::D2D1CreateFactory(single_threaded, __uuidof(ID2D1Factory1), &options, (void **) &s_pfactory);

   if(FAILED(hr))
       return NULL;

   return s_pfactory;

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
      D3D_FEATURE_LEVEL_11_1 ,
      D3D_FEATURE_LEVEL_11_0,
      D3D_FEATURE_LEVEL_10_1,
      D3D_FEATURE_LEVEL_10_0,
      D3D_FEATURE_LEVEL_9_3,
      D3D_FEATURE_LEVEL_9_2,
      D3D_FEATURE_LEVEL_9_1
   };

   D3D_FEATURE_LEVEL lv;

   d2d1_fax_options options;
   memset(&options, 0, sizeof(options));

   ID3D11DeviceContext * pcontext = NULL;

   HRESULT hr = 
        D3D11CreateDevice(
            nullptr,                    // specify NULL to use the default adapter
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

   ID3D11Device * pdevice = TlsGetD3D11Device();

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

   ID3D11Device * pdevice = TlsGetD3D11Device();

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

   if(pdxgidevice != NULL)
      return pdxgidevice;

   ID3D11Device1 * pdevice1 = TlsGetD3D11Device1();

   if(pdevice1 == NULL)
      return NULL;

   HRESULT hr = pdevice1->QueryInterface(__uuidof(IDXGIDevice), (void **) &pdxgidevice);

   TlsSetValue(TLS_d3_4, pdxgidevice);

   if(pdxgidevice == NULL)
      return NULL;

   return pdxgidevice;

}


float point_dpi(float points)
{

   FLOAT dpiX, dpiY;

   GetD2D1Factory1()->GetDesktopDpi(&dpiX, &dpiY);

	return points * dpiY / 72.f;

}

float dpiy(float y)
{
   
   FLOAT dpiX, dpiY;

   GetD2D1Factory1()->GetDesktopDpi(&dpiX, &dpiY);

   return y * dpiY / 96.f;

}

float dpix(float x)
{
   
   FLOAT dpiX, dpiY;

   GetD2D1Factory1()->GetDesktopDpi(&dpiX, &dpiY);

   return x * dpiX / 96.f;

}


float y_dpi(float y)
{
   
   FLOAT dpiX, dpiY;

   GetD2D1Factory1()->GetDesktopDpi(&dpiX, &dpiY);

   return y / dpiY;

}

float x_dpi(float x)
{
   
   FLOAT dpiX, dpiY;

   GetD2D1Factory1()->GetDesktopDpi(&dpiX, &dpiY);

   return x / dpiX;

}



