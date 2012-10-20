#pragma once


class CLASS_DECL_c simple_font
{
public:

   
   Gdiplus::Font *            m_pfont;
   bool                       m_bDelete;


   simple_font();
   ~simple_font();

   bool create_point(simple_graphics & g, int nPointSize, const char * lpszFaceName, bool bBold = false);
   bool create_point_bold(simple_graphics & g, int nPointSize, const char * lpszFaceName);
   bool create_pixel(simple_graphics & g, int nPixelHeight, const char * lpszFaceName, bool bBold = false);
   bool create_pixel_bold(simple_graphics & g, int nPixelHeight, const char * lpszFaceName);
   
   // aim to be all-platoform
   bool destroy();


   simple_font & operator = (const simple_font & font);


};

