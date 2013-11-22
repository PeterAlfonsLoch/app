//
//  c_os_simple_font.h
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 9/30/12.
//
//
#pragma once


class CLASS_DECL_BOOT os_simple_font
{
public:
   
   
   string               m_strFontFamilyName;
   double               m_dFontSize;
   double               m_dFontWidth;
   ::draw2d::e_unit     m_eunitFontSize;
   int32_t              m_iFontWeight;
   bool                 m_bItalic;
   bool                 m_bUnderline;
   bool                 m_bStrikeout;

   
   
   os_simple_font();
   ~os_simple_font();
   
   bool create_point(simple_graphics & g, int nPointSize, const char * lpszFaceName, bool bBold = false);
   bool create_pixel(simple_graphics & g, int nPixelSize, const char * lpszFaceName, bool bBold = false);
   
   
};
