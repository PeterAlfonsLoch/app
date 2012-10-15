#include "framework.h"
#undef new
#include <GdiPlus.h>


void simple_ui::draw_this(simple_graphics & g)
{

   g.set_alpha_mode(::ca::alpha_mode_blend);

   //Gdiplus::Color crOut(0, 255, 255, 233);

   //Gdiplus::Color crIn(84 + 49, 255, 255, 233);

   COLORREF crOut;

   COLORREF crIn;

   if(get_plugin()->m_eschema == ::hotplugin::plugin::schema_darker)
   {

      crOut = ARGB(0, 84, 84, 77);

      crIn  = ARGB(84 + 49, 84, 84, 77);

   }
   else
   {

      crOut = ARGB(0, 255, 255, 233);

      crIn  = ARGB(84 + 49, 255, 255, 233);

   }

   int iBorderH = min(height(&m_rect) / 2, 49);

   simple_linear_gradient_brush br1(0, 0, 0, iBorderH, crOut, crIn);

   g.fill_rect(rect_dim(m_rect.left, m_rect.top, width(&m_rect), iBorderH), br1);

   simple_solid_brush br(crIn, g);

   g.fill_rect(rect_dim(m_rect.left, m_rect.top + iBorderH, width(&m_rect), height(&m_rect) - (iBorderH * 2)), br);

   simple_linear_gradient_brush br2(0, m_rect.bottom - iBorderH, 0, m_rect.bottom, crIn, crOut);

   g.fill_rect(rect_dim(m_rect.left, m_rect.bottom - iBorderH, width(&m_rect), iBorderH), br2);


}


void simple_ui::draw_focus_rect(simple_graphics & g)
{

   g.set_alpha_mode(::ca::alpha_mode_blend);

   int iStyle = 1;

   if(get_focus() == this)
   {

      if(iStyle == 1)
      {

         RECT rect;

         rect = m_rect;

         {
         
            simple_solid_pen pen(ARGB(255, 108, 149, 255));

            g.draw_rect(rect, pen);

         }

         rect.left--;
         rect.right++;
         rect.top--;
         rect.bottom++;

         {
         
            simple_path pathRound;
            
            graphics_round_rect::get_round_rect(pathRound, rect, 1 * 2);

            simple_solid_pen pen(ARGB(84, 108, 149, 255));

            g.draw_path(pathRound, pen);

         }

         rect.left--;
         rect.right++;
         rect.top--;
         rect.bottom++;

         {

            simple_path pathRound;

            graphics_round_rect::get_round_rect(pathRound, rect, 2 * 2);

            simple_solid_pen pen(ARGB(72, 108, 149, 255));

            g.draw_path(pathRound, pen);

         }

         rect.left--;
         rect.right++;
         rect.top--;
         rect.bottom++;

         {

            simple_path pathRound;

            graphics_round_rect::get_round_rect(pathRound, rect, 3 * 2);

            simple_solid_pen pen(ARGB(60, 108, 149, 255));

            g.draw_path(pathRound, pen);

         }


         rect.left--;
         rect.right++;
         rect.top--;
         rect.bottom++;

         {

            simple_path pathRound;

            graphics_round_rect::get_round_rect(pathRound, rect, 4 * 2);

            simple_solid_pen pen(ARGB(48, 108, 149, 255));

            g.draw_path(pathRound, pen);

         }



         rect.left--;
         rect.right++;
         rect.top--;
         rect.bottom++;

         {

            simple_path pathRound;

            graphics_round_rect::get_round_rect(pathRound, rect, 5 * 2);

            simple_solid_pen pen(ARGB(36, 108, 149, 255));

            g.draw_path(pathRound, pen);

         }





         rect.left--;
         rect.right++;
         rect.top--;
         rect.bottom++;

         {

            simple_path pathRound;

            graphics_round_rect::get_round_rect(pathRound, rect, 6 * 2);

            simple_solid_pen pen(ARGB(24, 108, 149, 255));

            g.draw_path(pathRound, pen);

         }


      }
      else
      {
         
         simple_solid_pen pen(ARGB(255, 84, 77, 255), 3);

         g.draw_rect(m_rect, pen);

      }

   }
   else
   {

      simple_solid_pen pen(ARGB(255, 149, 149, 123));

      g.draw_rect(m_rect, pen);

   }


}