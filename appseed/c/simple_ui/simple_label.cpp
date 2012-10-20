#include "framework.h"

simple_label::simple_label()
{

}

simple_label::~simple_label()
{
}




void simple_label::draw_this(simple_graphics & g)
{



   COLORREF c;

   if(get_plugin()->m_eschema == ::hotplugin::plugin::schema_darker)
   {

#if CA2_PLATFORM_VERSION == CA2_BASIS
      c = ARGB(255, 184 + 49, 149 + 49, 177 + 49);
#else
      c = ARGB(255, 149 + 49, 184 + 49, 123 + 49);
#endif

   }
   else
   {

#if CA2_PLATFORM_VERSION == CA2_BASIS
      c = ARGB(255, 84, 49, 77);
#else
      c = ARGB(255, 49, 84, 23);
#endif

   }

   simple_brush b;

   b.create_solid(g, c);

   simple_font f;
   
   f.create_pixel(g, height(&m_rect) * 10, "Geneva");

   float fMargin = (height(&m_rect) * ((1.0f - 0.7f) / 2.0f));

   g.select(f);

   g.select(b);

   g.text_out(m_rect.left, (int) (m_rect.top + fMargin), m_strText);

}

