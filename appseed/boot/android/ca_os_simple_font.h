#pragma once


class CLASS_DECL_c os_simple_font
{
public:


   string                m_strFamily;
   cairo_font_weight_t     m_weight;
   double                  m_dSize;


   os_simple_font();
   ~os_simple_font();

   bool create_point(simple_graphics & g, int32_t nPointSize, const char * lpszFaceName, bool bBold = false);
   bool create_point_bold(simple_graphics & g, int32_t nPointSize, const char * lpszFaceName);
   bool create_pixel(simple_graphics & g, int32_t nPointSize, const char * lpszFaceName, bool bBold = false);
   bool create_pixel_bold(simple_graphics & g, int32_t nPointSize, const char * lpszFaceName);

   // aim to be all-platoform
   bool destroy();



};

