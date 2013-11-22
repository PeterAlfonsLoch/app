#include "framework.h"

#define type_shared DWRITE_FACTORY_TYPE_SHARED


os_simple_font::os_simple_font()
{
   
   m_pformat = NULL;

}

os_simple_font::~os_simple_font()
{
   
   if(m_pformat != NULL)
   {

      destroy();

   }

}

bool os_simple_font::destroy()
{
   
   if(m_pformat == NULL)
      return true;


   bool bOk = m_pformat->Release() == 0;

   m_pformat = NULL;

   if(!bOk)
      return false;

   return true;

}


bool os_simple_font::create_point(simple_graphics & g, int nPointSize, const char * lpszFaceName, bool bBold)
{

   IDWriteFactory * pfactory = TlsGetWriteFactory();


   DWRITE_FONT_STYLE style;

   //if(lplf->lfItalic)
     // style = DWRITE_FONT_STYLE_ITALIC;
   //else
      style = DWRITE_FONT_STYLE_NORMAL;

   DWRITE_FONT_STRETCH stretch;

   stretch = DWRITE_FONT_STRETCH_NORMAL;

   HRESULT hr = pfactory->CreateTextFormat(
      //wstring(lplf->lfFaceName),
      wstring(lpszFaceName),
      NULL,
      //(DWRITE_FONT_WEIGHT) lplf->lfWeight,
      (DWRITE_FONT_WEIGHT) bBold ? DWRITE_FONT_WEIGHT_BOLD : DWRITE_FONT_WEIGHT_NORMAL,
      style,
      stretch,
      point_dpi(nPointSize / 10.f),
      L"",
      &m_pformat);


   if(FAILED(hr) || m_pformat == NULL)
      return false;


   return true;

}


bool os_simple_font::create_point_bold(simple_graphics & g, int nPointSize, const char * lpszFaceName)
{

   return create_point(g, nPointSize, lpszFaceName, true);

}



bool os_simple_font::create_pixel(simple_graphics & g, int nPixelSize, const char * lpszFaceName, bool bBold)
{

   IDWriteFactory * pfactory = TlsGetWriteFactory();


   DWRITE_FONT_STYLE style;

   //if(lplf->lfItalic)
     // style = DWRITE_FONT_STYLE_ITALIC;
   //else
      style = DWRITE_FONT_STYLE_NORMAL;

   DWRITE_FONT_STRETCH stretch;

   stretch = DWRITE_FONT_STRETCH_NORMAL;

   HRESULT hr = pfactory->CreateTextFormat(
      //wstring(lplf->lfFaceName),
      wstring(lpszFaceName),
      NULL,
      (DWRITE_FONT_WEIGHT) bBold ? DWRITE_FONT_WEIGHT_BOLD : DWRITE_FONT_WEIGHT_NORMAL,
      style,
      stretch,
      dpiy(nPixelSize / 15.f),
      L"",
      &m_pformat);


   if(FAILED(hr) || m_pformat == NULL)
      return false;

   return true;
   
}


bool os_simple_font::create_pixel_bold(simple_graphics & g, int nPixelSize, const char * lpszFaceName)
{

   return create_pixel(g, nPixelSize, lpszFaceName, true);

}








os_simple_font & os_simple_font::operator = (const os_simple_font & font)
{

   if(m_pformat != NULL)
   {

      destroy();

   }

   m_pformat = font.m_pformat;

   m_pformat->AddRef();

   return *this;

}




