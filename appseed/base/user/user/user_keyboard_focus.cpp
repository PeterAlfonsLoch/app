#include "framework.h"

namespace user
{

   keyboard_focus::~keyboard_focus()
   {
      if(m_pbaseapp != NULL && &System != NULL && session().user().is_set())
      {
         if(session().user()->m_pkeyboardfocus == this)
         {
            session().user()->set_keyboard_focus(NULL);
         }
      }
   }

   void keyboard_focus::keyboard_focus_OnTimer(int32_t iTimer)
   {
      UNREFERENCED_PARAMETER(iTimer);
   }

   void keyboard_focus::keyboard_focus_OnChar(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void keyboard_focus::keyboard_focus_OnSysChar(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void keyboard_focus::keyboard_focus_OnKeyDown(signal_details * pobj)
   {

      SCAST_PTR(::message::key, pkey, pobj)

      if(pkey->m_ekey == ::user::key_tab)
      {
         
         control_event ev;
         
         ev.m_puie                  = (this);
         ev.m_eevent                = ::user::event_tab_key;
         ev.m_actioncontext         = ::action::source_user;
         
         GetParent()->BaseOnControlEvent(&ev);
         
         BaseOnControlEvent(&ev);

      }

   }

   void keyboard_focus::keyboard_focus_OnKeyUp(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   bool keyboard_focus::keyboard_focus_is_focusable()
   {
      return false;
   }

   bool keyboard_focus::keyboard_focus_OnSetFocus()
   {
      // get_keyboard_focus will return the control with focus

      // return true to set focus to this control
      return true;
   }

   keyboard_focus * keyboard_focus::keyboard_get_next_focusable()
   {
      sp(interaction) puiThis = (this);
      if(puiThis == NULL)
         return NULL;
      single_lock(puiThis->m_pbaseapp->m_pmutex,TRUE);
      sp(interaction) pui = puiThis->above_sibling();
      while(pui != NULL)
      {
         if(pui->keyboard_focus_is_focusable())
            return pui;
         pui = pui->above_sibling();
      }
      pui = puiThis->GetParent()->get_bottom_child();
      while(pui != NULL && pui != puiThis)
      {
         if(pui->keyboard_focus_is_focusable())
            return pui;
         pui = pui->above_sibling();
      }
      return NULL;
   }

   bool keyboard_focus::keyboard_set_focus()
   {
      session().user()->set_keyboard_focus( (this));
      return true;
   }

} // namespace user
