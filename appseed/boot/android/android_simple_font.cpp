#include "framework.h"



os_simple_font::os_simple_font()
{

   m_strFamily    = "helvetica";
   m_weight       = CAIRO_FONT_WEIGHT_NORMAL;
   m_dSize        = 10.0;

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



bool os_simple_font::create_point(::draw2d::graphics * pgraphics, int32_t nPointSize, const char * lpszFaceName, bool bBold)
{

   return create_pixel(g, nPointSize * 96 / 72, lpszFaceName, bBold);

}

bool os_simple_font::create_point_bold(::draw2d::graphics * pgraphics, int32_t nPointSize, const char * lpszFaceName)
{

   return create_point(g, nPointSize, lpszFaceName, true);


}


bool os_simple_font::create_pixel(::draw2d::graphics * pgraphics, int32_t nPixelSize, const char * lpszFaceName, bool bBold)
{

   m_strFamily    = lpszFaceName;

   m_weight       = bBold ? CAIRO_FONT_WEIGHT_BOLD  : CAIRO_FONT_WEIGHT_NORMAL;

   m_dSize        = nPixelSize / 10.0;

   return true;


}

bool os_simple_font::create_pixel_bold(::draw2d::graphics * pgraphics, int32_t nPointSize, const char * lpszFaceName)
{

   return create_point(g, nPointSize, lpszFaceName, true);

}

