#include "framework.h"


namespace simple_ui
{


   edit_box::edit_box(sp(::base::application) papp) :
      element(papp)
   {

      m_iPos = 0;

   }


   edit_box::~edit_box()
   {

   }

   void edit_box::install_message_handling(::message::dispatch * pdispatch)
   {

      ::simple_ui::interaction::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_KEYDOWN, pdispatch, this, &edit_box::_001OnKeyDown);
      IGUI_LBUTTONDOWN(edit_box);
      IGUI_LBUTTONUP(edit_box);


   }


   void edit_box::_001OnLButtonDown(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      keyboard_set_focus();

      pmouse->m_bRet = true;

   }


   void edit_box::_001OnLButtonUp(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      pmouse->m_bRet = true;

   }



   bool edit_box::keyboard_focus_is_focusable()
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


   void edit_box::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      rect rectClient;

      GetClientRect(rectClient);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::draw2d::brush_sp br(allocer());

      br->create_solid(ARGB(84 + 49, 255, 255, 233));

      pgraphics->FillRect(rectClient, br);

      simple_ui_draw_focus_rect(pgraphics);

      br->create_solid(ARGB(223, 49, 49, 23));

      ::draw2d::font_sp f(allocer());

      f->create_pixel_font("Geneva", (int32_t)height(&rectClient)* 0.7);

      pgraphics->SelectObject(br);

      pgraphics->SelectObject(f);

      float fMargin = (height(&rectClient) * ((1.0f - 0.7f) / 2.0f));

      string strText;

      GetWindowText(strText);

      pgraphics->TextOut((int32_t)(rectClient.left + fMargin), (int32_t)(rectClient.top + fMargin), strText);

   }

   void edit_box::_001OnKeyDown(signal_details * pobj)
   {

      SCAST_PTR(::message::key,pkey,pobj);

      ::user::e_key iKey =  pkey->m_ekey;

      if (iKey == ::user::key_control || iKey == ::user::key_lcontrol || iKey == ::user::key_rcontrol)
      {
         pkey->m_bRet = false;

      }
      else    if (iKey == ::user::key_alt || iKey == ::user::key_ralt || iKey == ::user::key_lalt)
      {
         pkey->m_bRet = false;

      }
      else    if (iKey == ::user::key_shift || iKey == ::user::key_rshift || iKey == ::user::key_lshift)
      {

      }
      else if (iKey == ::user::key_tab)
      {
         
         sp(::user::interaction) pui = keyboard_get_next_focusable();

         if(pui != NULL)
            pui->keyboard_set_focus();

         pkey->m_bRet = true;


      }
      else if (iKey == ::user::key_return)
      {
         on_action("submit");
         pkey->m_bRet = true;
      }
      else if (iKey == ::user::key_back)
      {

         string strText;

         GetWindowText(strText);

         if(m_iPos > strText.get_length())
         {
            m_iPos = strText.get_length();
         }
         if (m_iPos > 0)
         {
            SetWindowText(strText.substr(0,m_iPos - 1) + strText.substr(m_iPos));
            m_iPos--;
         }
         else
         {
            m_iPos = 0;
         }
         pkey->m_bRet = true;
      }
      else if (iKey == ::user::key_delete)
      {

         string strText;

         GetWindowText(strText);
         if (m_iPos < 0)
         {
            m_iPos = 0;
         }
         if (m_iPos < strText.get_length())
         {
            SetWindowText(strText.substr(0, m_iPos) + strText.substr(m_iPos + 1));
         }
         pkey->m_bRet = true;
      }
      else if(iKey == ::user::key_refer_to_text_member)
      {
         
         string strText;
         
         GetWindowText(strText);
         
         string strChar = pkey->m_strText;
         
         SetWindowText(strText.substr(0,m_iPos) + strChar + strText.substr(m_iPos + 1));
         
         m_iPos++;
         
         pkey->m_bRet = true;
         
      }
      else
      {

         string strText;

         GetWindowText(strText);

         string strChar = Application.user()->keyboard().process_key(pkey->m_ekey);

         SetWindowText(strText.substr(0,m_iPos) + strChar + strText.substr(m_iPos + 1));

         m_iPos++;
         pkey->m_bRet = true;

        

      }

   }


} // namespace simple_ui
