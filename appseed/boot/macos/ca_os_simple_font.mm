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
   
   m_strFamily    = "helvetica";
   m_iWeight      = 400;
   m_iSize        = 10;
   m_bUpdated     = false;
//   m_fontset      = 0;
   m_nsfont = NULL;
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


bool os_simple_font::update()
{
   
   if(m_bUpdated)
   {
      
      m_bUpdated = false;
      
   }

   NSFontManager * fontmanager = [NSFontManager sharedFontManager];
   
   m_nsfont = [fontmanager fontWithFamily: [[NSString alloc] initWithUTF8String: m_strFamily]
                                       traits: 0
                                             weight: m_iWeight
                                             size: m_iSize / 10.0];
   
   if(m_nsfont == NULL)
   {
      m_nsfont = [NSFont controlContentFontOfSize: m_iSize / 10.f];
      
   }
   
   
   m_bUpdated = true;
   
   
	m_iAscent = 0;
   
	m_iDescent = 0;
   
   
   return true;
}

bool os_simple_font::destroy()
{
   
   if(m_bUpdated)
   {
      
      [m_nsfont release];
      
      
   }
   
   m_strFamily    = "";
   
   m_iWeight      = 400;
   
   m_iSize        = 0;
   
   return true;
   
}


bool os_simple_font::create_point(simple_graphics & g, int nPointSize, const char * lpszFaceName, bool bBold)
{  
   
   
   m_strFamily = lpszFaceName;
   
   m_iSize = nPointSize;
   
   m_iWeight = bBold ? 800 : 400;
   
   return update();
   
}

bool os_simple_font::create_pixel(simple_graphics & g, int nPixelSize, const char * lpszFaceName, bool bBold)
{
   
   return create_point(g, nPixelSize * 72 / 96, lpszFaceName, bBold);
   
}

