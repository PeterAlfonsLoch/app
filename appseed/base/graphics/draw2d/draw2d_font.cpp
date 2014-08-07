#include "framework.h"


namespace draw2d
{


   font::font()
   {

      m_strFontFamilyName  = "Times New Roman";
      m_dFontSize          = 17.0;
      m_dFontWidth         = 1.0;
      m_eunitFontSize      = ::draw2d::unit_point;
      m_iFontWeight        = 400;
      m_bItalic            = false;
      m_bUnderline         = false;
      m_bStrikeout         = false;

   }

   font::font(const font & font)
   {

      operator = (font);
   }

   font::~font()
   {

   }


   void font::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      throw interface_only_exception(get_app());
   }


   bool font::create_pixel_font(const char * lpszFacename, double dSize, int32_t iWeight, bool bItalic, bool bUnderline, bool bStrikeOut, double dWidth)
   {

#ifdef WINDOWS
      if(stricmp(lpszFacename, "sans-serif") == 0)
      {
         m_strFontFamilyName = "Arial";
      }
      else
      {
         m_strFontFamilyName     = lpszFacename;
      }
#else
      m_strFontFamilyName     = lpszFacename;

#endif
      
      m_dFontSize             = dSize;
      m_dFontWidth            = 1.0;
      m_eunitFontSize         = ::draw2d::unit_pixel;
      m_iFontWeight           = iWeight;
      m_bItalic               = bItalic;
      m_bUnderline            = bUnderline;
      m_bStrikeout            = bStrikeOut;
      m_bUpdated              = false;

      return true;

   }

   bool font::create_point_font(const char * lpszFacename, double dSize, int32_t iWeight, bool bItalic, bool bUnderline, bool bStrikeOut, double dWidth)
   {
      
      m_strFontFamilyName     = lpszFacename;
      m_dFontSize             = dSize;
      m_dFontWidth            = 1.0;
      m_eunitFontSize         = ::draw2d::unit_point;
      m_iFontWeight           = iWeight;
      m_bItalic               = bItalic;
      m_bUnderline            = bUnderline;
      m_bStrikeout            = bStrikeOut;
      m_bUpdated              = false;

      return true;

   }


   font & font::operator = (const font & fontSrc)
   {

      if(this != &fontSrc)
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
      }

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


} // namespace draw2d


