#pragma once


class CLASS_DECL_c simple_pixel_font :
   public simple_font
{
public:

   simple_pixel_font(simple_graphics & g, int nPixelHeight, const char * lpszFaceName, bool bBold = false)
   {
      create_pixel(g, nPixelHeight, lpszFaceName, bBold);
   }

};