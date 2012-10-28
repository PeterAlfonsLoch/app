#include "framework.h"


namespace ca
{


   font::font()
   {

      m_strFontFamilyName  = "Times New Roman";
      m_dFontSize          = 17.0;
      m_dFontWidth         = 1.0;
      m_eunitFontSize      = ::ca::unit_point;
      m_iFontWeight        = 400;
      m_bItalic            = false;
      m_bUnderline         = false;
      m_bStrikeout         = false;

   }

   void font::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      throw interface_only_exception(get_app());
   }

   /////////////////////////////////////////////////////////////////////////////
   // out-of-line ::ca::brush, font, etc. helpers

   // nPointSize is actually scaled 10x
   bool font::CreatePointFont(int nPointSize, const char * lpszFaceName, ::ca::graphics * pgraphics)
   {

      m_strFontFamilyName     = lpszFaceName;
      m_dFontSize             = nPointSize / 10.0;
      m_dFontWidth            = 1.0;
      m_eunitFontSize         = ::ca::unit_point;
      m_iFontWeight           = 400;
      m_bItalic               = false;
      m_bUnderline            = false;
      m_bStrikeout            = false;
      m_bUpdated              = false;

      return true;
   }

   // pLogFont->nHeight is interpreted as PointSize * 10
   bool font::CreatePointFontIndirect(const LOGFONT* lpLogFont, ::ca::graphics * pgraphics)
   {
      m_strFontFamilyName     = lpLogFont->lfFaceName;
      m_dFontSize             = lpLogFont->lfHeight * 96.0 / (72.0 * 10.0);
      m_dFontWidth            = 1.0;
      m_eunitFontSize         = ::ca::unit_pixel;
      m_iFontWeight           = lpLogFont->lfWeight;
      m_bItalic               = lpLogFont->lfItalic != FALSE;
      m_bUnderline            = lpLogFont->lfUnderline != FALSE;
      m_bStrikeout            = lpLogFont->lfStrikeOut != FALSE;
      m_bUpdated              = false;

      return true;

   }

   bool font::CreateFontIndirect(const LOGFONT* lpLogFont)
   {

      m_strFontFamilyName     = lpLogFont->lfFaceName;
      m_dFontSize             = lpLogFont->lfHeight / 10.0;
      m_dFontWidth            = 1.0;
      m_eunitFontSize         = ::ca::unit_pixel;
      m_iFontWeight           = lpLogFont->lfWeight;
      m_bItalic               = lpLogFont->lfItalic != FALSE;
      m_bUnderline            = lpLogFont->lfUnderline != FALSE;
      m_bStrikeout            = lpLogFont->lfStrikeOut != FALSE;
      m_bUpdated              = false;
                        /*,
                        lpLogFont->lfWidth,
                        lpLogFont->lfEscapement,
                        lpLogFont->lfOrientation,
                        lpLogFont->lfWeight,
                        lpLogFont->lfItalic,
                        lpLogFont->lfUnderline,
                        lpLogFont->lfStrikeOut,
                        lpLogFont->lfCharSet,
                        lpLogFont->lfOutPrecision,
                        lpLogFont->lfClipPrecision,
                        lpLogFont->lfQuality,
                        lpLogFont->lfPitchAndFamily,
                        lpLogFont->lfFaceName);*/
      return true;

   }

   bool font::CreateFont(int nHeight, int nWidth, int nEscapement,
      int nOrientation, int nWeight, BYTE bItalic, BYTE bUnderline,
      BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision,
      BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily,
      const char * lpszFacename)
   {

      m_strFontFamilyName     = lpszFacename;
      m_dFontSize             = nHeight / 10.0;
      m_dFontWidth            = 1.0;
      m_eunitFontSize         = ::ca::unit_pixel;
      m_iFontWeight           = nWeight;
      m_bItalic               = bItalic != FALSE;
      m_bUnderline            = bUnderline != FALSE;
      m_bStrikeout            = cStrikeOut != FALSE;
      m_bUpdated              = false;

      return true;

   }

   font & font::operator = (const font & fontSrc)
   {

      m_strFontFamilyName     = fontSrc.m_strFontFamilyName;
      m_dFontSize             = fontSrc.m_dFontSize;
      m_dFontWidth            = fontSrc.m_dFontWidth;
      m_eunitFontSize         = fontSrc.m_eunitFontSize;
      m_iFontWeight           = fontSrc.m_iFontWeight;
      m_bItalic               = fontSrc.m_bItalic;
      m_bUnderline            = fontSrc.m_bUnderline;
      m_bStrikeout            = fontSrc.m_bStrikeout;
      m_bUpdated              = false;

      return *this;

   }


   void font::set_family_name(const char * pszFamilyName)
   {

      m_strFontFamilyName  = pszFamilyName;
      m_bUpdated           = false;


   }

   void font::set_size(double dSize, e_unit eunit)
   {

      m_dFontSize       = dSize;
      m_eunitFontSize   = eunit;
      m_bUpdated        = false;


   }

   void font::set_bold(bool bBold)
   {

      if(bBold)
      {
         m_iFontWeight  = 700;
      }
      else
      {
         m_iFontWeight  = 400;
      }

      m_bUpdated     = false;

   }

   void font::set_italic(bool bItalic)
   {

      m_bItalic      = bItalic;
      m_bUpdated     = false;

   }

   void font::set_underline(bool bUnderline)
   {

      m_bUnderline   = bUnderline;
      m_bUpdated     = false;

   }

   void font::set_strikeout(bool bStrikeout)
   {

      m_bStrikeout   = bStrikeout;
      m_bUpdated     = false;

   }


} // namespace ca


