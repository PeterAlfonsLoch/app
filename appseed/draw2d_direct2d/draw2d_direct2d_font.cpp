#include "framework.h"


#undef new


namespace draw2d_direct2d
{


   font::font(::ca2::application * papp) :
      ca2(papp)
   {

   }


   font::~font()
   { 


   }

   //   font::operator HFONT() const
   // {
   //  return (HFONT)(this == NULL ? NULL : get_handle()); 
   //}
   //font* font::from_handle(::ca2::application * papp, HFONT hFont)
   //{
   // return dynamic_cast < font * > (::draw2d_direct2d::object::from_handle(papp, hFont)); 
   //}
/*   bool font::CreateFontIndirect(const LOGFONT* lpLogFont)
   { 

      m_strFontFamilyName = lpLogFont->lfFaceName;
      if(lpLogFont->lfHeight < 0)
         m_dFontSize = (int) abs(lpLogFont->lfHeight);
      else
         m_dFontSize = lpLogFont->lfHeight / 10.0;
      m_eunitFontSize = ::ca2::unit_point;
      m_bBold = lpLogFont->lfWeight >= 500;
      m_bItalic = lpLogFont->lfItalic != FALSE;
      m_bStrikeout = lpLogFont->lfStrikeOut != FALSE;

      return TRUE;
      //return Attach(::CreateFontIndirect(lpLogFont)); 
   }
   bool font::CreateFont(int nHeight, int nWidth, int nEscapement,
      int nOrientation, int nWeight, BYTE bItalic, BYTE bUnderline,
      BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision,
      BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily,
      const char * lpszFacename)
   { 
      return FALSE;
      //return Attach(::CreateFont(nHeight, nWidth, nEscapement,
      //nOrientation, nWeight, bItalic, bUnderline, cStrikeOut,
      //nCharSet, nOutPrecision, nClipPrecision, nQuality,
      //nPitchAndFamily, lpszFacename)); 
   }

   int font::GetLogFont(LOGFONT* pLogFont)
   { 

      return 0;
      //   return ::GetObject(get_handle(), sizeof(LOGFONT), pLogFont);

   }

   */
   /////////////////////////////////////////////////////////////////////////////

   /*void font::construct(const ::draw2d::font & fontParam)
   {
      class font & font = const_cast < ::draw2d_direct2d::font & > (dynamic_cast < const ::draw2d_direct2d::font & > (fontParam));
      if(font.m_pfont == NULL)
      {
         if(m_pfont != NULL)
         {
            delete m_pfont;
            m_pfont = NULL;
         }
      }
      else
      {
         m_pfont = font.m_pfont->Clone();
      }
      //         if(get_handle() != NULL)
      //          delete_object();
      //     if(font.get_handle() != NULL)
      /*   {
      LOGFONT lf;
      memset(&lf, 0, sizeof(lf));
      font.GetLogFont(&lf);
      CreateFontIndirect(&lf);
      }*/
   //}


   void font::dump(dump_context & dumpcontext) const
   {
      ::draw2d::object::dump(dumpcontext);

      /*         if (get_handle() == NULL)
      return;

      if (!afxData.bWin95 && ::GetObjectType(get_handle()) != OBJ_FONT)
      {
      // not a valid GDI object
      dumpcontext << "has ILLEGAL HFONT!";
      return;
      }

      LOGFONT lf;
      VERIFY(GetObject(sizeof(lf), &lf));
      dumpcontext << "lf.lfHeight = " << lf.lfHeight;
      dumpcontext << "\nlf.lfWidth = " << lf.lfWidth;
      dumpcontext << "\nlf.lfEscapement = " << lf.lfEscapement;
      dumpcontext << "\nlf.lfOrientation = " << lf.lfOrientation;
      dumpcontext << "\nlf.lfWeight = " << lf.lfWeight;
      dumpcontext << "\nlf.lfItalic = " << (int)lf.lfItalic;
      dumpcontext << "\nlf.lfUnderline = " << (int)lf.lfUnderline;
      dumpcontext << "\nlf.lfStrikeOut = " << (int)lf.lfStrikeOut;
      dumpcontext << "\nlf.lfCharSet = " << (int)lf.lfCharSet;
      dumpcontext << "\nlf.lfOutPrecision = " << (int)lf.lfOutPrecision;
      dumpcontext << "\nlf.lfClipPrecision = " << (int)lf.lfClipPrecision;
      dumpcontext << "\nlf.lfQuality = " << (int)lf.lfQuality;
      dumpcontext << "\nlf.lfPitchAndFamily = " << (int)lf.lfPitchAndFamily;
      dumpcontext << "\nlf.lfFaceName = " << (const char *)lf.lfFaceName;

      dumpcontext << "\n";*/
   }


   /////////////////////////////////////////////////////////////////////////////
   // out-of-line ::draw2d::brush, font, etc. helpers

   // nPointSize is actually scaled 10x
/*   bool font::CreatePointFont(int nPointSize, const char * lpszFaceName, ::draw2d::graphics * pgraphics)
   {
      ASSERT(__is_valid_string(lpszFaceName));

      LOGFONT logFont;
      memset(&logFont, 0, sizeof(LOGFONT));
      logFont.lfCharSet = DEFAULT_CHARSET;
      logFont.lfHeight = nPointSize;
      ::ca2::strncpy_s(logFont.lfFaceName, _countof(logFont.lfFaceName), lpszFaceName, _TRUNCATE);

      return CreatePointFontIndirect(&logFont, pgraphics);
   }

   // pLogFont->nHeight is interpreted as PointSize * 10
   bool font::CreatePointFontIndirect(const LOGFONT* lpLogFont, ::draw2d::graphics * pgraphics)
   {
      return ::draw2d::font::CreatePointFontIndirect(lpLogFont, pgraphics);
      /* ASSERT(__is_valid_address(lpLogFont, sizeof(LOGFONT), FALSE));
      HDC hDC;
      if (pgraphics != NULL)
      {
      ASSERT_VALID(pgraphics);
      ASSERT((dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->get_handle2() != NULL);
      hDC = (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->get_handle2();
      }
      else
      hDC = ::GetDC(NULL);

      // convert nPointSize to logical units based on pgraphics
      LOGFONT logFont = *lpLogFont;
      POINT pt;
      // 72 points/inch, 10 decipoints/point
      pt.y = ::MulDiv(::GetDeviceCaps(hDC, LOGPIXELSY), logFont.lfHeight, 720);
      pt.x = 0;
      ::DPtoLP(hDC, &pt, 1);
      POINT ptOrg = { 0, 0 };
      ::DPtoLP(hDC, &ptOrg, 1);
      logFont.lfHeight = -abs(pt.y - ptOrg.y);

      if (pgraphics == NULL)
      ReleaseDC(NULL, hDC);

      return CreateFontIndirect(&logFont);*/
  // }


   IDWriteTextFormat * font::get_os_font(::draw2d_direct2d::graphics * pgraphics) const
   {

      if(m_pformat == NULL || !m_bUpdated)
      {

         if(m_pformat != NULL)
         {
            ((font *)  this)->destroy();
         }


         IDWriteFactory * pfactory = TlsGetWriteFactory();


         DWRITE_FONT_STYLE style;

         if(m_bItalic)
            style = DWRITE_FONT_STYLE_ITALIC;
         else
            style = DWRITE_FONT_STYLE_NORMAL;

         DWRITE_FONT_STRETCH stretch;

         stretch = DWRITE_FONT_STRETCH_NORMAL;

         HRESULT hr = pfactory->CreateTextFormat(
            //wstring(lplf->lfFaceName),
            wstring(m_strFontFamilyName),
            NULL,
            //(DWRITE_FONT_WEIGHT) lplf->lfWeight,
            (DWRITE_FONT_WEIGHT) m_iFontWeight ,
            style,
            stretch,
            (float) ((m_eunitFontSize == ::draw2d::unit_point ? point_dpi((float) m_dFontSize) : dpiy((float) m_dFontSize)) * pgraphics->m_dFontFactor),
            L"",
            &((font *)  this)->m_pformat);


         if(FAILED(hr) || m_pformat == NULL)
            return false;

      }


      if(m_pformat != NULL)
      {
         ((font *) this)->m_bUpdated = true;
      }

      return (IDWriteTextFormat *) m_pformat.Get();

   }


   bool font::destroy()
   {

      if(m_pformat == NULL)
         return true;


      m_pformat = nullptr;


      return true;

   }


} // namespace draw2d_direct2d