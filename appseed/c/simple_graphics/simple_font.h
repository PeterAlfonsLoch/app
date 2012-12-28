//
//  simple_font.h
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 10/21/12.
//
//
#pragma once


class CLASS_DECL_c simple_font :
   public os_simple_font
{
public:

   
   inline bool create_point_bold(simple_graphics & g, int32_t nPointHeight, const char * lpszFaceName);
   inline bool create_pixel_bold(simple_graphics & g, int32_t nPixelHeight, const char * lpszFaceName);
   
   
};



inline bool simple_font::create_point_bold(simple_graphics & g, int32_t nPixelHeight, const char * lpszFaceName)
{
   
   return create_point(g, nPixelHeight, lpszFaceName, true);
   
}


inline bool simple_font::create_pixel_bold(simple_graphics & g, int32_t nPixelHeight, const char * lpszFaceName)
{
   
   return create_pixel(g, nPixelHeight, lpszFaceName, true);
   
}



