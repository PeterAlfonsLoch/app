#pragma once


class CLASS_DECL_c os_simple_font
{
public:

   
   Gdiplus::Font *            m_pfont;
   bool                       m_bDelete;


   os_simple_font();
   ~os_simple_font();

   bool create_point(simple_graphics & g, int32_t nPointSize, const char * lpszFaceName, bool bBold = false);
   bool create_pixel(simple_graphics & g, int32_t nPixelHeight, const char * lpszFaceName, bool bBold = false);
   
   // aim to be all-platoform
   bool destroy();


   os_simple_font & operator = (const os_simple_font & font);


};

