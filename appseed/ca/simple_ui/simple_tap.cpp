#include "framework.h"



simple_tap::simple_tap()
{

   m_strId        = "submit";
   m_bDown        = false;
   m_bMouseMove   = false;

}


simple_tap::~simple_tap()
{
}


void simple_tap::draw_this(simple_graphics & g)
{

   //draw_simple(hdc);

   draw_volume(g);

}



void simple_tap::on_lbutton_down(int32_t x, int32_t y)
{

   set_focus(this);

   m_bDown = true;

}

void simple_tap::on_lbutton_up(int32_t x, int32_t y)
{

   if(m_bDown)
   {

      m_bDown = false;

      on_action(m_strId);

   }

}

void simple_tap::on_mouse_move(int32_t x, int32_t y)
{

   m_bMouseMove = true;

   //m_pplugin->redraw();

}

bool simple_tap::is_focusable()
{
   return true;
}

bool simple_tap::is_hover()
{

   RECT rectWindow = m_rect;

   ::hotplugin::plugin * pplugin = get_plugin();

   int32_t dx = pplugin->m_phost->m_rect.left;

   int32_t dy = pplugin->m_phost->m_rect.top;

   rectWindow.left      += dx;
   rectWindow.right     += dx;
   rectWindow.top       += dy;
   rectWindow.bottom    += dy;

   POINT ptCursor;

   ::GetCursorPos(&ptCursor);

   ptCursor.x += pplugin->m_ptCursorPhase.x;

   ptCursor.y += pplugin->m_ptCursorPhase.y;

   bool bHover = ptCursor.x >= rectWindow.left
              && ptCursor.x <= rectWindow.right
              && ptCursor.y >= rectWindow.top
              && ptCursor.y <= rectWindow.bottom;

   if(!bHover)
      m_bMouseMove = false;

   return bHover;


}



void simple_tap::draw_simple(simple_graphics & g)
{

   {

      g.set_alpha_mode(::draw2d::alpha_mode_blend);

#if CA2_PLATFORM_VERSION == CA2_BASIS

      simple_solid_brush br(g, ARGB(184, 255, 184, 240));

#else

      simple_solid_brush br(g, ARGB(184, 184, 255, 177));

#endif

      g.fill_rect(m_rect, br);

      draw_focus_rect(g);


   }

   draw_text(g);

}


void simple_tap::draw_volume(simple_graphics & g)
{

   {

      

      g.set_alpha_mode(::draw2d::alpha_mode_blend);

      COLORREF crOut;

      COLORREF crIn;

      COLORREF crBorderOut;

      COLORREF crBorderIn;


      if(is_hover() || m_bDown || m_bMouseMove)
      {

#if CA2_PLATFORM_VERSION == CA2_BASIS

         crOut = ARGB(184 + 49, 255, 230, 255);

         crIn = ARGB(255, 255, 84 + 49, 255);

         crBorderOut = ARGB(184, 150, 100, 150);

         crBorderIn = ARGB(184, 255, 240, 255) ;

#else

         crOut = ARGB(184 + 49, 230, 255, 225);

         crIn = ARGB(255, 84 + 49, 255, 77 + 49);

         crBorderOut = ARGB(184, 100, 150, 100);

         crBorderIn = ARGB(184, 240, 255, 235);

#endif

      }
      else
      {

#if CA2_PLATFORM_VERSION == CA2_BASIS

         crOut = ARGB(184, 255, 210, 255);

         crIn = ARGB(255, 255, 84 + 49, 255);

         crBorderOut = ARGB(184, 90, 20, 90);

         crBorderIn = ARGB(184, 255, 240, 255);

#else

         crOut = ARGB(184, 210, 255, 205);

         crIn = ARGB(255, 84 + 49, 255, 77 + 49);

         crBorderOut = ARGB(184, 20, 90, 20);

         crBorderIn = ARGB(184, 240, 255, 235);

#endif

      }

      int32_t iBorderH = height(&m_rect) / 2;

      simple_linear_gradient_brush br1(g, m_rect.left, m_rect.top - 1, m_rect.left, m_rect.top + iBorderH + 2, crOut, crIn);

      g.fill_rect(rect_dim(m_rect.left, m_rect.top, (int32_t) width(&m_rect), iBorderH), br1);

      simple_linear_gradient_brush br2(g, m_rect.left, m_rect.top + iBorderH - 1, m_rect.left, m_rect.top + iBorderH * 2 + 2, crIn, crOut);

      g.fill_rect(rect_dim( m_rect.left, m_rect.top + iBorderH, (int32_t) width(&m_rect), iBorderH), br2);

      /*Gdiplus::Pen pen1(crBorderOut);

      graphics2.DrawRectangle(&pen1, m_rect.left, m_rect.top, width(&m_rect), iBorderH * 2);*/

      draw_focus_rect(g);

      simple_solid_pen pen(g, crBorderIn);

      g.draw_rect(rect_dim(m_rect.left + 1, m_rect.top + 1, (int32_t) width(&m_rect) - 2, iBorderH * 2 - 2), pen);

   }

   draw_text(g);

}


void simple_tap::draw_text(simple_graphics & g)
{

   g.set_alpha_mode(::draw2d::alpha_mode_blend);

#if CA2_PLATFORM_VERSION == CA2_BASIS
   
   simple_solid_brush b(g, ARGB(223, 84, 49, 77));

#else

   simple_solid_brush b(g, ARGB(223, 49, 84, 23));

#endif

   g.select(b);

   simple_pixel_font f(g, (int32_t) height(m_rect) * 10, "Geneva");

   g.select(f);

   float fMargin = (height(&m_rect) * ((1.0f - 0.7f) / 2.0f));

   g.text_out((int32_t) (m_rect.left + fMargin), (int32_t) (m_rect.top + fMargin), m_strText);

}


void simple_tap::on_char(int32_t iKey, const vsstring & strChar)
{

   if(iKey == VK_RETURN || iKey == VK_SPACE)
   {

      on_action(m_strId);

   }
   else if(iKey == VK_TAB)
   {

      focus_next();

   }


}
