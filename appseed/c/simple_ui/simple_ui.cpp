#include "framework.h"


simple_ui::simple_ui()
{

   m_puiParent    = NULL;
   m_bVisible     = true;
   m_puiFocus     = NULL;
   m_pplugin      = NULL;

}

simple_ui::~simple_ui()
{
}


void simple_ui::set_parent(simple_ui * puiParent)
{

   if(m_puiParent != NULL && m_puiParent != puiParent)
   {

      for(int i = 0; i < m_puiParent->m_uiptra.get_count(); i++)
      {

         if(m_puiParent->m_uiptra[i] == this)
         {

            m_puiParent->m_uiptra.remove_at(i);
            break;

         }

      }

   }

   m_puiParent = puiParent;

   if(m_puiParent != NULL)
   {

      m_puiParent->m_uiptra.add(this);

   }

}


void simple_ui::draw(simple_graphics & g)
{

   if(m_bVisible)
   {

      draw_this(g);

      draw_children(g);

   }

}


void simple_ui::draw_children(simple_graphics & g)
{

   for(int i = 0; i < m_uiptra.get_count(); i++)
   {

      try
      {

         m_uiptra[i]->draw(g);

      }
      catch(...)
      {

      }

   }

}

void simple_ui::on_char(int ch, UINT uScan)
{

   get_focus()->on_char(ch, uScan);

}


void simple_ui::on_lbutton_down(int x, int y)
{

   for(int i = 0; i < m_uiptra.get_count(); i++)
   {

      if(x >= m_uiptra[i]->m_rect.left
      && x <= m_uiptra[i]->m_rect.right
      && y >= m_uiptra[i]->m_rect.top
      && y <= m_uiptra[i]->m_rect.bottom)
      {

         m_uiptra[i]->on_lbutton_down(x, y);

      }

   }

}

void simple_ui::on_lbutton_up(int x, int y)
{

   for(int i = 0; i < m_uiptra.get_count(); i++)
   {

      if(x >= m_uiptra[i]->m_rect.left
      && x <= m_uiptra[i]->m_rect.right
      && y >= m_uiptra[i]->m_rect.top
      && y <= m_uiptra[i]->m_rect.bottom)
      {

         m_uiptra[i]->on_lbutton_up(x, y);

      }

   }

}


void simple_ui::on_mouse_move(int x, int y)
{

   for(int i = 0; i < m_uiptra.get_count(); i++)
   {

      if(x >= m_uiptra[i]->m_rect.left
      && x <= m_uiptra[i]->m_rect.right
      && y >= m_uiptra[i]->m_rect.top
      && y <= m_uiptra[i]->m_rect.bottom)
      {

         m_uiptra[i]->on_mouse_move(x, y);

      }

   }

}



void simple_ui::on_action(const char * pszId)
{

   if(m_puiParent != NULL)
   {

      m_puiParent->on_action(pszId);

   }

}



bool simple_ui::is_focusable()
{
   return false;
}



void simple_ui::focus_next()
{

   ::count iFind = m_puiParent->m_uiptra.get_count() - 1;

   for(int i = 0; i < m_puiParent->m_uiptra.get_count(); i++)
   {

      if(m_puiParent->m_uiptra[i] == this)
      {

         iFind = i;

         break;

      }

   }

   for(::index i = iFind + 1; i < m_puiParent->m_uiptra.get_count(); i++)
   {

      if(m_puiParent->m_uiptra[i]->is_focusable())
      {

         m_puiParent->set_focus(m_puiParent->m_uiptra[i]);

         return;

      }

   }

   for(int i = 0; i <= iFind; i++)
   {

      if(m_puiParent->m_uiptra[i]->is_focusable())
      {

         m_puiParent->set_focus(m_puiParent->m_uiptra[i]);

         return;

      }

   }

}


void simple_ui::set_focus(simple_ui * pui)
{

   if(m_puiParent == NULL)
   {

      m_puiFocus = pui;

   }
   else
   {

      m_puiParent->set_focus(pui);

   }

}


simple_ui * simple_ui::get_focus()
{

   if(m_puiParent == NULL)
   {

      return m_puiFocus;

   }
   else
   {

      return m_puiParent->get_focus();

   }


}


bool simple_ui::is_visible()
{

   return m_bVisible && (m_puiParent == NULL || m_puiParent->is_visible());

}


::hotplugin::plugin * simple_ui::get_plugin()
{

   if(m_pplugin != NULL)
      return m_pplugin;

   if(m_puiParent == NULL)
      return NULL;

   return m_puiParent->get_plugin();

}




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