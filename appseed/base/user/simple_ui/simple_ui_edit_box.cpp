#include "framework.h"


namespace simple_ui
{


   edit_box::edit_box(sp(base_application) papp) :
      element(papp),
      interaction(papp)
   {

      m_iPos = 0;

   }


   edit_box::~edit_box()
   {

   }


   bool edit_box::on_lbutton_down(int32_t x, int32_t y)
   {

      set_focus(this);

      return true;

   }


   bool edit_box::on_lbutton_up(int32_t x, int32_t y)
   {

      return true;

   }



   bool edit_box::is_focusable()
   {

      return true;

   }


   /*

   CLASS_DECL_BASE char to_upper(int32_t ch)
   {

   if(ch >= 'a' && ch <= 'z')
   {
   ch = ch - 'a' + 'A';
   }

   return ch;

   }


   CLASS_DECL_BASE char * to_upper(char * pchParam)
   {
   char * pch = pchParam;
   while(*pch == '\0')
   {
   *pch = to_upper(*pch);
   pch++;
   }
   return pchParam;
   }


   */


   void edit_box::draw_this(::draw2d::graphics * pgraphics)
   {

      rect rectClient;

      get_client_rect(rectClient);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::draw2d::brush_sp br(allocer());

      br->create_solid(ARGB(84 + 49, 255, 255, 233));

      pgraphics->FillRect(rectClient, br);

      draw_focus_rect(pgraphics);

      br->create_solid(ARGB(223, 49, 49, 23));

      ::draw2d::font_sp f(allocer());

      f->create_pixel_font("Geneva", (int32_t)height(&rectClient)* 0.7);

      pgraphics->SelectObject(br);

      pgraphics->SelectObject(f);

      float fMargin = (height(&rectClient) * ((1.0f - 0.7f) / 2.0f));

      pgraphics->TextOut((int32_t)(rectClient.left + fMargin), (int32_t)(rectClient.top + fMargin), m_strText);

   }

   bool edit_box::on_char(int32_t iKey, const string & strChar)
   {

      if (iKey == ::user::key_control || iKey == ::user::key_lcontrol || iKey == ::user::key_rcontrol)
      {

      }
      else    if (iKey == ::user::key_alt || iKey == ::user::key_ralt || iKey == ::user::key_lalt)
      {

      }
      else    if (iKey == ::user::key_shift || iKey == ::user::key_rshift || iKey == ::user::key_lshift)
      {

      }
      else if (iKey == ::user::key_tab)
      {
         focus_next();
         return true;
      }
      else if (iKey == ::user::key_return)
      {
         on_action("submit");
         return true;
      }
      else if (iKey == ::user::key_back)
      {
         if (m_iPos > m_strText.get_length())
         {
            m_iPos = m_strText.get_length();
         }
         if (m_iPos > 0)
         {
            m_strText = m_strText.substr(0, m_iPos - 1) + m_strText.substr(m_iPos);
            m_iPos--;
         }
         else
         {
            m_iPos = 0;
         }
         return true;
      }
      else if (iKey == ::user::key_delete)
      {
         if (m_iPos < 0)
         {
            m_iPos = 0;
         }
         if (m_iPos < m_strText.get_length())
         {
            m_strText = m_strText.substr(0, m_iPos) + m_strText.substr(m_iPos + 1);
         }
         return true;
      }
      else
      {

         m_strText = m_strText.substr(0, m_iPos) + strChar + m_strText.substr(m_iPos + 1);

         m_iPos++;
         return true;

      }

      return false;

   }


} // namespace simple_ui
