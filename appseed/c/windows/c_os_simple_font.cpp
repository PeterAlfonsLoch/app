#include "framework.h"
#undef new
#include <gdiplus.h>


simple_font::simple_font()
{
   
   m_pfont = NULL;

}

simple_font::~simple_font()
{
   
   if(m_pfont != NULL)
   {

      destroy();

   }

}

bool simple_font::create_point(int nPointSize, const char * lpszFaceName, simple_graphics & g, bool bBold)
{

   if(m_pfont != NULL)
   {
      
      destroy();

   }

   m_pfont = new Gdiplus::Font(wstring(lpszFaceName), nPointSize / 10.0f, bBold ? Gdiplus::FontStyleBold : Gdiplus::FontStyleRegular, Gdiplus::UnitPoint);

   if(m_pfont == NULL)
      return false;
   
   return true;

}

bool simple_font::create_point_bold(int nPointSize, const char * lpszFaceName, simple_graphics & g)
{

   return create_point(nPointSize, lpszFaceName, g, true);

}



bool simple_font::create_pixel(int nPointSize, const char * lpszFaceName, simple_graphics & g, bool bBold)
{

   if(m_pfont != NULL)
   {
      
      destroy();

   }

   m_pfont = new Gdiplus::Font(wstring(lpszFaceName), nPointSize * 0.7f / 10.0f, bBold ? Gdiplus::FontStyleBold : Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);

   if(m_pfont == NULL)
      return false;
   
   return true;

}

bool simple_font::create_pixel_bold(int nPointSize, const char * lpszFaceName, simple_graphics & g)
{

   return create_pixel(nPointSize, lpszFaceName, g, true);

}



bool simple_font::destroy()
{
   
   if(m_pfont == NULL)
      return true;

   bool bOk = true;

   try
   {
      
      delete m_pfont;

   }
   catch(...)
   {

      bOk = false;

   }

   m_pfont = NULL;

   if(!bOk)
      return false;

   return true;

}


