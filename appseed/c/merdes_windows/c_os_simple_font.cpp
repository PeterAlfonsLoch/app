#include "framework.h"

#define type_shared DWRITE_FACTORY_TYPE_SHARED

simple_font::simple_font()
{
   
   m_pformat = NULL;

}

simple_font::~simple_font()
{
   
   if(m_pformat != NULL)
   {

      destroy();

   }

}

bool simple_font::create_indirect(LPLOGFONT  lplf)
{

   IDWriteFactory * pfactory = TlsGetWriteFactory();


   DWRITE_FONT_STYLE style;

   if(lplf->lfItalic)
      style = DWRITE_FONT_STYLE_ITALIC;
   else
      style = DWRITE_FONT_STYLE_NORMAL;

   DWRITE_FONT_STRETCH stretch;

   stretch = DWRITE_FONT_STRETCH_NORMAL;

   HRESULT hr = pfactory->CreateTextFormat(
      wstring(lplf->lfFaceName),
      NULL,
      (DWRITE_FONT_WEIGHT) lplf->lfWeight,
      style,
      stretch,
      lplf->lfHeight / 100.0f,
      L"",
      &m_pformat);


   if(FAILED(hr) || m_pformat == NULL)
      return false;


   return true;

}

bool simple_font::destroy()
{
   
   if(m_pformat == NULL)
      return true;


   bool bOk = m_pformat->Release() == 0;

   m_pformat = NULL;

   if(!bOk)
      return false;

   return true;

}


bool simple_font::create_point(int nPointSize, const char * lpszFaceName, simple_graphics & g)
{

   return create_point_bold(nPointSize, lpszFaceName, FALSE, g);

}

bool simple_font::create_point_bold(int nPointSize, const char * lpszFaceName, int iBold, simple_graphics & g)
{

   LOGFONT logFont;

   memset_dup(&logFont, 0, sizeof(LOGFONT));

   logFont.lfCharSet = DEFAULT_CHARSET;

   logFont.lfHeight = nPointSize / 10.0f;
   logFont.lfWeight = iBold ? FW_BOLD : FW_NORMAL;
   wcsncpy_dup(logFont.lfFaceName, wstring(lpszFaceName), sizeof(logFont.lfFaceName));

   return create_indirect(&logFont);

}



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


