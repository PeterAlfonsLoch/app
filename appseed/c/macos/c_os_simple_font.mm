//
//  c_os_simple_font.cpp
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 10/6/12.
//
//

#include "framework.h"



simple_font::simple_font()
{
   
   m_strFamily    = "helvetica";
   m_iWeight      = 400;
   m_iSize        = 10;
   m_bUpdated     = false;
   m_fontset      = 0;
   
}

simple_font::~simple_font()
{
   
   /*if(m_hfont != NULL)
    {
    
    destroy();
    
    }*/
   
}

/*bool simple_font::create_indirect(LPLOGFONT  lplf)
 {
 
 m_hfont = ::CreateFontIndirect(lplf);
 
 if(m_hfont == NULL)
 return false;
 
 
 return true;
 
 }
 */

vsstring simple_font::get_weight(int iWeight)
{
   
   if(iWeight <= 400)
   {
      return "medium";
   }
   else
   {
      return "bold";
   }
   
}

vsstring simple_font::get_name(int i)
{
   
   if(i == 0)
   {
      
      vsstring strWeight = get_weight(m_iWeight);
      
      vsstring strSize = itoa_dup(m_iSize);
      
      return "-*-" + m_strFamily +"-" + strWeight + "-r-*-*-" + strSize + "-*-72-72-*-*";
   }
   if(m_iWeight > 400)
   {
      
      if(i == 1)
      {
         
         vsstring strSize = itoa_dup(m_iSize);
         
         return "-*-" + m_strFamily +"-medium-r-*-*-" + strSize + "-*-72-72-*-*";
         
      }
      else if(i == 2)
      {
         
         vsstring strWeight = get_weight(m_iWeight);
         
         return "-*-" + m_strFamily +"-" + strWeight + "-r-*-*-*-*-72-72-*-*";
      }
      else if(i == 3)
      {
         
         return "-*-" + m_strFamily +"-*-r-*-*-*-*-72-72-*-*";
         
      }
      else
      {
         
         i -= 3;
         
      }
      
   }
   if(m_strFamily != "helvetica")
   {
      
      if(i == 1)
      {
         
         vsstring strSize = itoa_dup(m_iSize);
         
         return "-*-helvetica-medium-r-*-*-" + strSize + "-*-72-72-*-*";
         
      }
      else if(i == 2)
      {
         
         vsstring strWeight = get_weight(m_iWeight);
         
         return "-*-helvetica-" + strWeight + "-r-*-*-*-*-72-72-*-*";
      }
      else if(i == 3)
      {
         
         return "-*-helvetica-*-r-*-*-*-*-72-72-*-*";
         
      }
      else
      {
         
         i -= 3;
         
      }
   }
   
   return "fixed";
   
}

bool simple_font::update(Display * pdisplay)
{
   
   if(m_bUpdated)
   {
      
      m_bUpdated = false;
      
   }
   
	int nmissing;
	char **missing;
	char *def_string;
   
   
   vsstring strName;
   
   int j = 0;
   
   while(true)
   {
      
      strName = get_name(j);
      
      if(j >= 32 || strName.is_empty())
         return false;
      
      m_fontset = XCreateFontSet(pdisplay, m_strFamily, &missing, &nmissing, &def_string);
      
      if(m_fontset != 0)
         break;
      
      
   }
   
   m_bUpdated = true;
   
   m_pdisplay = pdisplay;
   
	XFreeStringList(missing);
   
	XFontStruct ** fonts;
   
	char ** font_names;
   
	int nfonts = XFontsOfFontSet(m_fontset, &fonts, &font_names);
   
	m_iAscent = 0;
   
	m_iDescent = 0;
   
	for(int j = 0; j < nfonts; j++)
	{
      
		if(fonts[j]->ascent > m_iAscent)
         m_iAscent = fonts[j]->ascent;
      
		if(fonts[j]->descent > m_iDescent)
         m_iDescent = fonts[j]->descent;
      
	}
   
   return true;
}

bool simple_font::destroy()
{
   
   if(m_bUpdated)
   {
      
      XFreeFontSet(m_pdisplay, m_fontset);
      
      m_fontset = 0;
      
      m_pdisplay = NULL;
      
   }
   
   m_strFamily    = "";
   
   m_iWeight      = 400;
   
   m_iSize        = 0;
   
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
   
   if(g.m_pdisplay == NULL)
   {
      
      g.create();
      
   }
   
   
   m_strFamily = lpszFaceName;
   
   m_iSize = nPointSize;
   
   m_iWeight = iBold != FALSE ? 800 : 400;
   
   return update(g.m_pdisplay);
   
}

