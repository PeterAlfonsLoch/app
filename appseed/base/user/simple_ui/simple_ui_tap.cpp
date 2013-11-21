#include "framework.h"
#include "base/spa/spa_style.h"
#include "simple_ui.h"
#include "simple_tap.h"



simple_tap::simple_tap()
{

   m_strId        = "submit";
   m_bDown        = false;
   m_bMouseMove   = false;

}


simple_tap::~simple_tap()
{
}


void simple_tap::_001OnDraw(::draw2d::graphics * pgraphics)
{

   //draw_simple(hdc);

   draw_volume(pgraphics);

}



bool simple_tap::on_lbutton_down(int32_t x, int32_t y)
{

   set_focus(this);

   m_bDown = true;

   return true;

}

bool simple_tap::on_lbutton_up(int32_t x, int32_t y)
{

   if(m_bDown)
   {

      m_bDown = false;

      on_action(m_strId);

   }

   return true;

}

bool simple_tap::on_mouse_move(int32_t x, int32_t y)
{

   m_bMouseMove = true;

   //m_pplugin->redraw();

   return true;

}

bool simple_tap::is_focusable()
{
   return true;
}

bool simple_tap::is_hover()
{

   rect rectWindow;

   get_window_rect(&rectWindow);

   POINT ptCursor;

   ui_get_cursor_pos(&ptCursor);

   bool bHover = rectWindow.contains(ptCursor);

   if(!bHover)
      m_bMouseMove = false;

   return bHover;


}



void simple_tap::draw_simple(::draw2d::graphics * pgraphics)
{

   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

#if CA2_PLATFORM_VERSION == CA2_BASIS

      ::draw2d::brush_sp br(allocer(), ARGB(184, 255, 184, 240));

#else

      simple_solid_brush br(g, ARGB(184, 184, 255, 177));

#endif

      rect rectClient;

      get_client_rect(rectClient);

      pgraphics->FillRect(rectClient, br);

      draw_focus_rect(pgraphics);


   }

   draw_text(pgraphics);

}


void simple_tap::draw_volume(::draw2d::graphics * pgraphics)
{

   {

      

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

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

         crIn = ARGB(255, 255, 184 + 49, 255);

         crBorderOut = ARGB(184, 90, 20, 90);

         crBorderIn = ARGB(184, 255, 240, 255);

#else

         crOut = ARGB(184, 210, 255, 205);

         crIn = ARGB(255, 84 + 49, 255, 77 + 49);

         crBorderOut = ARGB(184, 20, 90, 20);

         crBorderIn = ARGB(184, 240, 255, 235);

#endif

      }

      rect rectClient;

      get_client_rect(rectClient);

      int32_t iBorderH = height(&rectClient) / 2;

      ::draw2d::brush_sp br(allocer());

      br->CreateLinearGradientBrush(point(rectClient.left, rectClient.top - 1), point(rectClient.left, rectClient.top + iBorderH + 2), crOut, crIn);

      pgraphics->FillRect(rect(rectClient.left, rectClient.top, (int32_t)width(&rectClient), iBorderH), br);

      br->CreateLinearGradientBrush(point(rectClient.left, rectClient.top + iBorderH - 1), point(rectClient.left, rectClient.top + iBorderH * 2 + 2), crIn, crOut);

      pgraphics->FillRect(rect(rectClient.left, rectClient.top + iBorderH, (int32_t)width(&rectClient), iBorderH), br);

      /*Gdiplus::Pen pen1(crBorderOut);

      graphics2.DrawRectangle(&pen1, rectClient.left, rectClient.top, width(&rectClient), iBorderH * 2);*/

      draw_focus_rect(pgraphics);

      ::draw2d::pen_sp pen(pgraphics, 1.0, crBorderIn);

      pgraphics->DrawRect(rect(rectClient.left + 1, rectClient.top + 1, (int32_t)width(&rectClient) - 2, iBorderH * 2 - 2), pen);

   }

   draw_text(pgraphics);

}


void simple_tap::draw_text(::draw2d::graphics * pgraphics)
{

   rect rectClient;

   get_client_rect(rectClient);

   pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

#if CA2_PLATFORM_VERSION == CA2_BASIS
   
   ::draw2d::brush_sp b(allocer(), ARGB(223, 84, 49, 77));

#else

   simple_solid_brush b(g, ARGB(223, 49, 84, 23));

#endif

   pgraphics->SelectObject(b);

   ::draw2d::font_sp f(allocer());
   
   f->create_pixel_font("Geneva", (int32_t)height(rectClient) * 10);

   pgraphics->SelectObject(f);

   float fMargin = (height(&rectClient) * ((1.0f - 0.7f) / 2.0f));

   pgraphics->TextOut((int32_t)(rectClient.left + fMargin), (int32_t)(rectClient.top + fMargin), m_strText);

}


bool simple_tap::on_char(int32_t iKey, const string & strChar)
{

   if(iKey == VK_RETURN || iKey == VK_SPACE)
   {

      on_action(m_strId);

      return true;

   }
   else if(iKey == VK_TAB)
   {

      focus_next();

      return true;

   }

   return false;

}
