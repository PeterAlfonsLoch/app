//
//  c_os_simple_font.h
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 9/30/12.
//
//
#pragma once


class CLASS_DECL_c os_simple_font
{
public:
   
   
   vsstring                m_strFamily;
   int                     m_iWeight;
   int                     m_iSize;
   //XFontSet                m_fontset;
   bool                    m_bUpdated;
   //Display *               m_pdisplay;
   int                     m_iAscent;
   int                     m_iDescent;
#ifdef __MM
   NSFont *     m_nsfont;
#else
   void *                  m_pnsfont;
  
#endif
   
   
   os_simple_font();
   ~os_simple_font();
   
   bool create_point(simple_graphics & g, int nPointSize, const char * lpszFaceName, bool bBold = false);
   bool create_pixel(simple_graphics & g, int nPixelSize, const char * lpszFaceName, bool bBold = false);
   
   // aim to be all-platoform
   bool destroy();
   
   
   // platform-specific
   //   bool create_indirect(LPLOGFONT lplf);
   vsstring get_name(int i);
   vsstring get_weight(int iWeight);
   bool update();
   
};
