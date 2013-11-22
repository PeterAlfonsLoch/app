#pragma once


class CLASS_DECL_BASE os_simple_font
{
public:


   string                m_strFamily;
   cairo_font_weight_t     m_weight;
   double                  m_dSize;


   os_simple_font();
   ~os_simple_font();

   bool create_point(::draw2d::graphics * pgraphics, int32_t nPointSize, const char * lpszFaceName, bool bBold = false);
   bool create_point_bold(::draw2d::graphics * pgraphics, int32_t nPointSize, const char * lpszFaceName);
   bool create_pixel(::draw2d::graphics * pgraphics, int32_t nPointSize, const char * lpszFaceName, bool bBold = false);
   bool create_pixel_bold(::draw2d::graphics * pgraphics, int32_t nPointSize, const char * lpszFaceName);

   // aim to be all-platoform
   bool destroy();



};

