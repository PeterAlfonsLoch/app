#include "framework.h"
#undef new
#include <gdiplus.h>


os_simple_font::os_simple_font()
{
   
   m_pfont     = NULL;
   m_bDelete   = false;

}


os_simple_font::~os_simple_font()
{
   
   if(m_pfont != NULL)
   {

      destroy();

   }

}


bool os_simple_font::create_point(simple_graphics & g, int32_t nPointSize, const char * lpszFaceName, bool bBold)
{

   if(m_pfont != NULL)
   {
      
      destroy();

   }

   m_pfont = new Gdiplus::Font(wstring(lpszFaceName), nPointSize / 10.0f, bBold ? Gdiplus::FontStyleBold : Gdiplus::FontStyleRegular, Gdiplus::UnitPoint);

   if(m_pfont == NULL)
      return false;

   m_bDelete = true;
   
   return true;

}


bool os_simple_font::create_pixel(simple_graphics & g, int32_t nPointSize, const char * lpszFaceName, bool bBold)
{

   if(m_pfont != NULL)
   {
      
      destroy();

   }

   m_pfont = new Gdiplus::Font(wstring(lpszFaceName), nPointSize * 0.77f / 10.0f, bBold ? Gdiplus::FontStyleBold : Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);

   if(m_pfont == NULL)
      return false;

   m_bDelete = true;
   
   return true;

}


bool os_simple_font::destroy()
{
   
   if(m_pfont == NULL)
      return true;

   bool bOk = true;

   if(m_bDelete)
   {

      try
      {
      
         delete m_pfont;

      }
      catch(...)
      {

         bOk = false;

      }

   }

   m_bDelete = false;

   m_pfont = NULL;

   if(!bOk)
      return false;

   return true;

}





os_simple_font & os_simple_font::operator = (const os_simple_font & font)
{

   if(m_pfont != NULL)
   {

      destroy();

   }

   m_bDelete = false;

   m_pfont = font.m_pfont;

   return *this;

}









