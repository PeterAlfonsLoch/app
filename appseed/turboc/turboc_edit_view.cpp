#include "framework.h"


namespace turboc
{


   edit_view::edit_view(::aura::application * papp):
      element(papp),
      ::user::interaction(papp),
      ::user::scroll_view(papp),
      ::data::listener(papp),
      ::user::edit_plain_text(papp),
      ::user::edit_plain_text_view(papp)
   {
      
      m_ptopview = NULL;
 
   }

   edit_view::~edit_view()
   {

   }


   void edit_view::on_update(::aura::impact * pSender,LPARAM lHint,object* phint)
   {

      ::user::edit_plain_text_view::on_update(pSender,lHint,phint);

   }


   void edit_view::_001OnAfterChangeText(::action::context actioncontext)
   {

      if(!actioncontext.is_user_source())
         return;

      if(m_ptopview == NULL || m_ptopview->m_pview == NULL)
         return;

      {

         synch_lock sl(&m_ptopview->m_pview->m_mutexText);

         _001GetText(m_ptopview->m_pview->m_strNewHelloMultiverse);

      }

      m_ptopview->m_pview->post_message(WM_USER + 1984 + 77 + 2);

   }


   bool edit_view::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && IsWindowVisible();

   }


   int64_t edit_view::add_ref()
   {
      return ::root::add_ref();
   }
   int64_t edit_view::dec_ref()
   {
      return ::root::dec_ref();
   }



} // namespace turboc




