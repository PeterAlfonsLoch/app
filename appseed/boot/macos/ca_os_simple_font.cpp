//
//  c_os_os_simple_font.cpp
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 10/6/12.
//
//

#import "ca_os_graphics_mm.h"



os_simple_font::os_simple_font()
{
   
   m_strFontFamilyName = "helvetica";
   m_iFontWeight      = 400;
   m_dFontSize        = 10;
}

os_simple_font::~os_simple_font()
{
   
   /*if(m_hfont != NULL)
    {
    
    destroy();
    
    }*/
   
}

/*bool os_simple_font::create_indirect(LPLOGFONT  lplf)
 {
 
 m_hfont = ::CreateFontIndirect(lplf);
 
 if(m_hfont == NULL)
 return false;
 
 
 return true;
 
 }
 */
/*
vsstring os_simple_font::get_weight(int iWeight)
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
vsstring os_simple_font::get_name(int i)
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
*/



bool os_simple_font::create_point(simple_graphics & g, int nPointSize, const char * lpszFaceName, bool bBold)
{  
   
   
   m_strFontFamilyName = lpszFaceName;
   
   m_dFontSize = nPointSize;
   
   m_iFontWeight = bBold ? 800 : 400;
   
   return true;
   
}

bool os_simple_font::create_pixel(simple_graphics & g, int nPixelSize, const char * lpszFaceName, bool bBold)
{
   
   return create_point(g, nPixelSize * 72 / 96, lpszFaceName, bBold);
   
}

