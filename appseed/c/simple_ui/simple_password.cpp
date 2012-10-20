#include "framework.h"




simple_password::simple_password()
{

}

simple_password::~simple_password()
{
}




void simple_password::draw_this(simple_graphics & g)
{

   g.set_alpha_mode(::ca::alpha_mode_blend);

   simple_brush br;
   
   br.create_solid(g, ARGB(184, 255, 255, 240));

   g.fill_rect(m_rect, br);

   draw_focus_rect(g);

   simple_brush b;
   
   b.create_solid(g, ARGB(223, 49, 49, 23));

   g.select(b);

   simple_pixel_font f(g, height(m_rect) * 10, "Geneva");

   g.select(f);

   vsstring str;

   str.append('*', m_strText.get_length());

   g.text_out(m_rect.left + 2, m_rect.top, str);

}










