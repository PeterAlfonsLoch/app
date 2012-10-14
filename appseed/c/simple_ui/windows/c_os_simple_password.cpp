#include "framework.h"
#include <GdiPlus.h>


void simple_password::draw_this(simple_graphics & g)
{

   g.set_alpha_mode(::ca::alpha_mode_blend);

   simple_brush br;
   
   br.create_solid(ARGB(184, 255, 255, 240));

   g.fill_rect(m_rect, br);

   draw_focus_rect(g);

   simple_brush b;
   
   b.create_solid(ARGB(223, 49, 49, 23));

   simple_pixel_font f(height(&m_rect), "Geneva", g);

   wstring wstr;

   wstr.append(L'*', m_strText.get_length());

   graphics2.DrawString(pwsz, wcslen_dup(pwsz), &f, Gdiplus::PointF((Gdiplus::REAL) (m_rect.left + 2), (Gdiplus::REAL) m_rect.top), &b);

}










