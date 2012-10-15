#include "framework.h"
#include <GdiPlus.h>


void simple_password::draw_this(simple_graphics & g)
{

   g.set_alpha_mode(::ca::alpha_mode_blend);

   simple_brush br;
   
   br.create_solid(ARGB(184, 255, 255, 240), g);

   g.fill_rect(m_rect, br);

   draw_focus_rect(g);

   simple_brush b;
   
   b.create_solid(ARGB(223, 49, 49, 23), g);

   g.select(b);

   simple_pixel_font f(height(m_rect), "Geneva", g);

   g.select(f);

   vsstring str;

   str.append('*', m_strText.get_length());

   g.text_out(m_rect.left + 2, m_rect.top, str);

}










