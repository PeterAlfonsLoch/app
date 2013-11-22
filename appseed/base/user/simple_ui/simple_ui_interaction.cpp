#include "framework.h"


namespace simple_ui
{


   interaction::interaction(sp(base_application) papp) :
      element(papp)
   {

      m_pstyle = NULL;
      m_puiParent = NULL;

   }

   interaction::~interaction()
   {
   }


   void interaction::set_parent(interaction * puiParent)
   {

      if (m_puiParent != NULL && m_puiParent != puiParent)
      {

         for (int32_t i = 0; i < m_puiParent->m_uiptra.get_count(); i++)
         {

            if (m_puiParent->m_uiptra[i] == this)
            {

               m_puiParent->m_uiptra.remove_at(i);
               break;

            }

         }

      }

      m_puiParent = puiParent;

      if (m_puiParent != NULL)
      {

         m_puiParent->m_uiptra.add(this);

      }

   }

   interaction * interaction::get_top_level_parent()
   {

      if (m_puiParent == NULL)
         return this;

      return m_puiParent->get_top_level_parent();

   }


   void interaction::draw(::draw2d::graphics * pgraphics)
   {

      if (m_bVisible)
      {

         rect rectWindow;

         get_window_rect(rectWindow);

         get_top_level_parent()->screen_to_client(rectWindow);

         pgraphics->SetViewportOrg(rectWindow.left, rectWindow.top);

         draw_this(pgraphics);

         draw_children(pgraphics);

      }

   }


   void interaction::draw_children(::draw2d::graphics * pgraphics)
   {

      for (int32_t i = 0; i < m_uiptra.get_count(); i++)
      {

         try
         {

            m_uiptra[i]->draw(pgraphics);

         }
         catch (...)
         {

         }

      }

   }

   bool interaction::on_char(int32_t iKey, const string & strChar)
   {

      if (get_focus() == NULL)
         focus_next();

      if (get_focus() == NULL)
         return false;

      return get_focus()->on_char(iKey, strChar);

   }


   bool interaction::on_lbutton_down(int32_t x, int32_t y)
   {

      point pt(x, y);

      for (int32_t i = 0; i < m_uiptra.get_count(); i++)
      {

         if (m_uiptra[i]->m_rect.contains(pt))
         {

            if (m_uiptra[i]->on_lbutton_down(x - m_uiptra[i]->m_rect.left, y - m_uiptra[i]->m_rect.top))
               return true;

         }

      }

      return false;

   }

   bool interaction::on_lbutton_up(int32_t x, int32_t y)
   {

      for (int32_t i = 0; i < m_uiptra.get_count(); i++)
      {

         if (x >= m_uiptra[i]->m_rect.left
            && x <= m_uiptra[i]->m_rect.right
            && y >= m_uiptra[i]->m_rect.top
            && y <= m_uiptra[i]->m_rect.bottom)
         {

            if (m_uiptra[i]->on_lbutton_up(x - m_uiptra[i]->m_rect.left, y - m_uiptra[i]->m_rect.top))
               return true;

         }

      }

      return false;

   }


   bool interaction::on_mouse_move(int32_t x, int32_t y)
   {

      for (int32_t i = 0; i < m_uiptra.get_count(); i++)
      {

         if (x >= m_uiptra[i]->m_rect.left
            && x <= m_uiptra[i]->m_rect.right
            && y >= m_uiptra[i]->m_rect.top
            && y <= m_uiptra[i]->m_rect.bottom)
         {

            if (m_uiptra[i]->on_mouse_move(x - m_uiptra[i]->m_rect.left, y - m_uiptra[i]->m_rect.top))
               return true;

         }

      }

      return false;

   }



   bool interaction::on_action(const char * pszId)
   {

      if (m_puiParent != NULL)
      {

         if (m_puiParent->on_action(pszId))
            return true;

      }

      return false;

   }



   bool interaction::is_focusable()
   {
      return false;
   }



   void interaction::focus_next()
   {

      ::count iFind = m_puiParent->m_uiptra.get_count() - 1;

      for (int32_t i = 0; i < m_puiParent->m_uiptra.get_count(); i++)
      {

         if (m_puiParent->m_uiptra[i] == this)
         {

            iFind = i;

            break;

         }

      }

      for (::index i = iFind + 1; i < m_puiParent->m_uiptra.get_count(); i++)
      {

         if (m_puiParent->m_uiptra[i]->is_focusable())
         {

            m_puiParent->set_focus(m_puiParent->m_uiptra[i]);

            return;

         }

      }

      for (int32_t i = 0; i <= iFind; i++)
      {

         if (m_puiParent->m_uiptra[i]->is_focusable())
         {

            m_puiParent->set_focus(m_puiParent->m_uiptra[i]);

            return;

         }

      }

   }


   void interaction::set_focus(interaction * pui)
   {

      if (m_puiParent == NULL)
      {

         m_puiFocus = pui;

      }
      else
      {

         m_puiParent->set_focus(pui);

      }

   }


   interaction * interaction::get_focus()
   {

      if (m_puiParent == NULL)
      {

         return m_puiFocus;

      }
      else
      {

         return m_puiParent->get_focus();

      }


   }


   bool interaction::is_visible()
   {

      return m_bVisible && (m_puiParent == NULL || m_puiParent->is_visible());

   }


   style * interaction::get_style()
   {

      if (m_pstyle != NULL)
         return m_pstyle;

      if (m_puiParent == NULL)
         return NULL;

      return m_puiParent->get_style();

   }


   void interaction::draw_back_01_old(style::e_schema eschema, rect m_rect, ::draw2d::graphics * pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      COLORREF crOut;

      COLORREF crIn;

      /*   if (eschema == ::hotplugin::plugin::schema_darker)
         {

         crOut = ARGB(0, 84, 84, 77);

         crIn = ARGB(84 + 49, 84, 84, 77);

         }
         else*/
      {

         crOut = ARGB(0, 255, 255, 233);

         crIn = ARGB(84 + 49, 255, 255, 233);

      }

      int32_t iBorderH = min(height(&m_rect) / 2, 49);

      ::draw2d::brush_sp br(allocer());

      br->CreateLinearGradientBrush(m_rect.top_left(), point(m_rect.left, m_rect.top + iBorderH), crOut, crIn);

      pgraphics->FillRect(rect(m_rect.left, m_rect.top, (int32_t)width(&m_rect), iBorderH), br);

      br->create_solid(crIn);

      pgraphics->FillRect(rect(m_rect.left, m_rect.top + iBorderH, (int32_t)width(&m_rect), (int32_t)height(&m_rect) - (iBorderH * 2)), br);

      br->CreateLinearGradientBrush(point(m_rect.left, m_rect.bottom - iBorderH), m_rect.bottom_left(), crIn, crOut);

      pgraphics->FillRect(rect(m_rect.left, m_rect.bottom - iBorderH, (int32_t)width(&m_rect), iBorderH), br);

   }

   void draw_back_01_new(rect m_rect, ::draw2d::graphics * pgraphics)
   {

      /*simple_solid_brush br(g, ARGB(255, 255, 255, 255));

      simple_pen pen;

      pen.create_solid(g, ARGB(255, 0, 0, 0));

      pgraphics->select(br);

      pgraphics->select(pen);

      m_rect.deflate(0, 0, 1, 1);

      pgraphics->rectangle(m_rect);*/

   }

   void interaction::draw_this(::draw2d::graphics * pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);

      draw_back_01_new(m_rect, pgraphics);

   }


   void interaction::draw_focus_rect(::draw2d::graphics * pgraphics)
   {

      rect rectClient;

      get_client_rect(rectClient);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      int32_t iStyle = 1;

      if (get_focus() == this)
      {

         if (iStyle == 1)
         {

            {

               ::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(255, 108, 149, 255));

               pgraphics->DrawRect(rectClient, pen);

            }

            rectClient.left--;
            rectClient.right++;
            rectClient.top--;
            rectClient.bottom++;

            {

               ::draw2d::path_sp pathRound(allocer());

               pathRound->begin_figure(true, ::draw2d::fill_mode_winding);

               pathRound->add_round_rect(rectClient, 1 * 2);

               pathRound->end_figure(true);

               ::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(84, 108, 149, 255));

               pgraphics->SelectObject(pen);

               pgraphics->draw_path(pathRound);

            }

            rectClient.left--;
            rectClient.right++;
            rectClient.top--;
            rectClient.bottom++;

            {

               ::draw2d::path_sp pathRound(allocer());

               pathRound->begin_figure(true, ::draw2d::fill_mode_winding);

               pathRound->add_round_rect(rectClient, 1 * 2);

               pathRound->end_figure(true);

               ::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(72, 108, 149, 255));

               pgraphics->SelectObject(pen);

               pgraphics->draw_path(pathRound);

            }

            rectClient.left--;
            rectClient.right++;
            rectClient.top--;
            rectClient.bottom++;

            {

               ::draw2d::path_sp pathRound(allocer());

               pathRound->begin_figure(true, ::draw2d::fill_mode_winding);

               pathRound->add_round_rect(rectClient, 1 * 2);

               pathRound->end_figure(true);

               ::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(60, 108, 149, 255));

               pgraphics->SelectObject(pen);

               pgraphics->draw_path(pathRound);

            }


            rectClient.left--;
            rectClient.right++;
            rectClient.top--;
            rectClient.bottom++;

            {

               ::draw2d::path_sp pathRound(allocer());

               pathRound->begin_figure(true, ::draw2d::fill_mode_winding);

               pathRound->add_round_rect(rectClient, 1 * 2);

               pathRound->end_figure(true);

               ::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(48, 108, 149, 255));

               pgraphics->SelectObject(pen);

               pgraphics->draw_path(pathRound);

            }



            rectClient.left--;
            rectClient.right++;
            rectClient.top--;
            rectClient.bottom++;

            {

               ::draw2d::path_sp pathRound(allocer());

               pathRound->begin_figure(true, ::draw2d::fill_mode_winding);

               pathRound->add_round_rect(rectClient, 1 * 2);

               pathRound->end_figure(true);

               ::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(36, 108, 149, 255));

               pgraphics->SelectObject(pen);

               pgraphics->draw_path(pathRound);

            }





            rectClient.left--;
            rectClient.right++;
            rectClient.top--;
            rectClient.bottom++;

            {

               ::draw2d::path_sp pathRound(allocer());

               pathRound->begin_figure(true, ::draw2d::fill_mode_winding);

               pathRound->add_round_rect(rectClient, 1 * 2);

               pathRound->end_figure(true);

               ::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(24, 108, 149, 255));

               pgraphics->SelectObject(pen);

               pgraphics->draw_path(pathRound);

            }


         }
         else
         {

            ::draw2d::pen_sp pen(pgraphics, 3.0, ARGB(255, 84, 77, 255));

            pgraphics->DrawRect(rectClient, pen);

         }

      }
      else
      {

         ::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(255, 149, 149, 123));

         pgraphics->DrawRect(rectClient, pen);

      }


   }


   void interaction::client_to_screen(POINT * ppt)
   {

      ppt->x += m_rect.left;
      ppt->y += m_rect.top;

      if (m_puiParent != NULL)
      {
         m_puiParent->client_to_screen(ppt);

      }


   }


   void interaction::screen_to_client(POINT * ppt)
   {

      ppt->x -= m_rect.left;
      ppt->y -= m_rect.top;

      if (m_puiParent != NULL)
      {
         m_puiParent->screen_to_client(ppt);

      }


   }


   void interaction::client_to_screen(RECT * prect)
   {

      client_to_screen((POINT *)&prect->left);
      client_to_screen((POINT *)&prect->right);

   }


   void interaction::screen_to_client(RECT * prect)
   {

      screen_to_client((POINT *)&prect->left);
      screen_to_client((POINT *)&prect->right);

   }


   void interaction::get_window_rect(RECT * prect)
   {

      get_client_rect(prect);

      client_to_screen(prect);

   }

   void interaction::get_client_rect(RECT * prect)
   {

      prect->left = 0;
      prect->top = 0;
      prect->right = width(m_rect);
      prect->bottom = height(m_rect);

   }


   void interaction::layout()
   {



   }


   void interaction::set_capture()
   {

      get_top_level_parent()->set_capture();

   }


   void interaction::release_capture()
   {

      get_top_level_parent()->release_capture();

   }


} // namespace simple_ui