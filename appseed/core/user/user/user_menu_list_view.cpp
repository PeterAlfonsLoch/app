#include "framework.h"


namespace user
{


   menu_list_view::menu_list_view(sp(::axis::application) papp) :
      element(papp),
      menu_base(papp),
      menu(papp),
      menu_list_window(papp)
   {

      m_puiNotify        = NULL;
      m_bAutoClose         = false;

   }


   void menu_list_view::install_message_handling(::message::dispatch * pinterface)
   {

      menu_list_window::install_message_handling(pinterface);

   }

   menu_list_view::~menu_list_view()
   {

   }

#ifdef DEBUG
   void menu_list_view::assert_valid() const
   {
      impact::assert_valid();
   }

   #ifndef _WIN32_WCE
   void menu_list_view::dump(dump_context & dumpcontext) const
   {
      impact::dump(dumpcontext);
   }
   #endif

#endif //DEBUG

   void menu_list_view::GuieProc(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      if(pbase->m_uiMessage == m_uiMessage)
      {
         if(base_class < ::user::place_holder >::bases(GetParent()))
         {
            pbase->set_lresult(GetParent()->GetParent()->send_message(pbase->m_uiMessage, pbase->m_wparam, pbase->m_lparam));
         }
         else
         {
            pbase->set_lresult(GetParent()->send_message(pbase->m_uiMessage, pbase->m_wparam, pbase->m_lparam));
         }
         pbase->m_bRet = true;
         return;
      }
      return impact::GuieProc(pobj);
   }

   bool menu_list_view::_001OnCmdMsg(::base::cmd_msg * pcmdmsg)
   {
      if(m_puiNotify != NULL && m_puiNotify != this)
      {
         if(m_puiNotify->_001OnCmdMsg(pcmdmsg))
            return TRUE;
      }
      return impact::_001OnCmdMsg(pcmdmsg);
   }

   bool menu_list_view::LoadMenu(sp(::xml::node) pnode, sp(::user::interaction) puiNotify, UINT uiCallbackMessage)
   {
      
      m_uiMessage = uiCallbackMessage;
      m_bAutoClose = false;

      if(!menu_list_window::LoadMenu(pnode))
         return false;

      MenuFill(this, GetParentFrame());

      m_puiNotify = puiNotify;

      return true;

   }


} // namespace user


