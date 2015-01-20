#include "framework.h"


namespace tc4
{


   toggle_view::toggle_view(::aura::application * papp):
      element(papp),
      ::user::interaction(papp),
      ::user::button(papp)
   {
      
      m_ptopview = NULL;

   }
   toggle_view::~toggle_view()
   {


   }

   void toggle_view::install_message_handling(::message::dispatch * pdispatch)
   {

      ::aura::impact::install_message_handling(pdispatch);
      ::user::button::install_message_handling(pdispatch);

   }


   void toggle_view::on_update(::aura::impact * pSender,LPARAM lHint,object* phint)
   {

      ::aura::impact::on_update(pSender,lHint,phint);

   }


   //void toggle_view::_001OnAfterChangeText(::action::context actioncontext)
   //{

   //   if(!actioncontext.is_user_source())
   //      return;

   //   if(m_pmainview == NULL || m_pmainview->m_pview == NULL)
   //      return;

   //   {
   //      synch_lock sl(&m_pmainview->m_pview->m_mutexText);
   //      _001GetText(m_pmainview->m_pview->m_strNewHelloMultiverse);
   //   }

   //   m_pmainview->m_pview->post_message(WM_USER + 1984 + 77 + 2);

   //}


   bool toggle_view::keyboard_focus_is_focusable()
   {
      
      return ::user::button::keyboard_focus_is_focusable() ;
      
   }


} // namespace tc4













