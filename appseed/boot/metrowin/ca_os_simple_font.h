#pragma once


class CLASS_DECL_ca os_simple_font
{
public:

   
   IDWriteTextFormat *                  m_pformat;


   os_simple_font();
   ~os_simple_font();

   bool create_point(simple_graphics & g, int nPointSize, const char * lpszFaceName, bool bBold = false);
   bool create_point_bold(simple_graphics & g, int nPointSize, const char * lpszFaceName);
   bool create_pixel(simple_graphics & g, int nPixelSize, const char * lpszFaceName, bool bBold = false);
   bool create_pixel_bold(simple_graphics & g, int nPixelSize, const char * lpszFaceName);
   
   // aim to be all-platoform
   bool destroy();

   // platform-specific
   bool create_indirect(LPLOGFONT lplf);

   os_simple_font & operator = (const os_simple_font & font);

};

