#include "StdAfx.h"


namespace ca
{


   font::font()
   {

      m_strFontFamilyName  = "Arial";
      m_dFontSize          = 12.0;
      m_eunitFontSize      = ::ca::unit_point;
      m_bBold              = false;
      m_bItalic            = false;
      m_bUnderline         = false;
      m_bStrikeout         = false;

   }

#ifdef _DEBUG
   void font::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      throw interface_only_exception();   
   }
#endif

   /////////////////////////////////////////////////////////////////////////////
   // out-of-line ::ca::brush, font, etc. helpers

   // nPointSize is actually scaled 10x
   BOOL font::CreatePointFont(int nPointSize, const char * lpszFaceName, ::ca::graphics * pgraphics)
   {
      UNREFERENCED_PARAMETER(nPointSize);
      UNREFERENCED_PARAMETER(lpszFaceName);
      UNREFERENCED_PARAMETER(pgraphics);
      throw interface_only_exception();   
   }

   // pLogFont->nHeight is interpreted as PointSize * 10
   BOOL font::CreatePointFontIndirect(const LOGFONT* lpLogFont, ::ca::graphics * pgraphics)
   {
      return ::ca::font::CreateFontIndirect(lpLogFont);
   }

   BOOL font::CreateFontIndirect(const LOGFONT* lpLogFont)
   {
      
      m_strFontFamilyName  = lpLogFont->lfFaceName;
      m_dFontSize          = lpLogFont->lfHeight;
      m_bUpdated           = false;

      return TRUE;

   }

   BOOL font::CreateFont(int nHeight, int nWidth, int nEscapement,
      int nOrientation, int nWeight, BYTE bItalic, BYTE bUnderline,
      BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision,
      BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily,
      const char * lpszFacename)
   {
      UNREFERENCED_PARAMETER(nHeight);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nEscapement);
      UNREFERENCED_PARAMETER(nOrientation);
      UNREFERENCED_PARAMETER(nWeight);
      UNREFERENCED_PARAMETER(bItalic);
      UNREFERENCED_PARAMETER(bUnderline);
      UNREFERENCED_PARAMETER(cStrikeOut);
      UNREFERENCED_PARAMETER(nCharSet);
      UNREFERENCED_PARAMETER(nOutPrecision);
      UNREFERENCED_PARAMETER(nClipPrecision);
      UNREFERENCED_PARAMETER(nQuality);
      UNREFERENCED_PARAMETER(nPitchAndFamily);
      UNREFERENCED_PARAMETER(lpszFacename);
      throw interface_only_exception();   
   }

   font & font::operator = (const font & fontSrc)
   {

      m_strFontFamilyName     = fontSrc.m_strFontFamilyName;
      m_dFontSize             = fontSrc.m_dFontSize;
      m_bBold                 = fontSrc.m_bBold;
      m_bItalic               = fontSrc.m_bItalic;
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

      m_bBold        = bBold;
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


