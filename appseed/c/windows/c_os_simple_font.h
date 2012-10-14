#pragma once


class CLASS_DECL_c simple_font
{
public:

   
   Gdiplus::Font *            m_pfont;


   simple_font();
   ~simple_font();

   bool create_point(int nPointSize, const char * lpszFaceName, simple_graphics & g, bool bBold = false);
   bool create_point_bold(int nPointSize, const char * lpszFaceName, simple_graphics & g);
   bool create_pixel(int nPixelHeight, const char * lpszFaceName, simple_graphics & g, bool bBold = false);
   bool create_pixel_bold(int nPixelHeight, const char * lpszFaceName, simple_graphics & g);
   
   // aim to be all-platoform
   bool destroy();


};

class CLASS_DECL_c simple_pixel_font :
   public simple_font
{
public:

   simple_pixel_font(int nPixelHeight, const char * lpszFaceName, simple_graphics & g, bool bBold = false)
   {
      create_pixel(nPixelHeight, lpszFaceName, g, bBold);
   }

};