#pragma once


class CLASS_DECL_ca simple_pixel_font :
   public simple_font
{
public:

   
   inline simple_pixel_font(simple_graphics & g, int32_t nPixelHeight, const char * lpszFaceName, bool bBold = false);


};



inline simple_pixel_font::simple_pixel_font(simple_graphics & g, int32_t nPixelHeight, const char * lpszFaceName, bool bBold)
{
   
   create_pixel(g, nPixelHeight, lpszFaceName, bBold);
   
}



