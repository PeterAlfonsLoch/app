#include "framework.h" // from "axis/user/user.h"

namespace user
{

   keyboard_focus::~keyboard_focus()
   {

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

      m_dwFocustStart = get_tick_count();

      // get_keyboard_focus will return the control with focus

      // return true to set focus to this control
      return true;
   }

   
   keyboard_focus * keyboard_focus::keyboard_get_next_focusable(keyboard_focus * pfocus)
   {
      
      sp(interaction) puiThis = this;

      sp(interaction) puiFocus = pfocus != NULL ? pfocus : this;

      keyboard_focus * pfocusTry;

      if(puiFocus == NULL)
         return NULL;

      if(puiThis == NULL)
         return NULL;

      single_lock(puiThis->m_pauraapp->m_pmutex,TRUE);

      sp(interaction) pui = puiThis->first_child();

      if(pui != NULL)
      {

         pui = keyboard_get_next_focusable(pfocus);

         if(pui != NULL)
            return pui;

      }

      pui = puiThis->next_sibling();

      while(pui != NULL)
      {

         if(pui->keyboard_focus_is_focusable())
            return pui;

         pfocusTry = pui->keyboard_get_next_focusable(pfocus);

         if(pfocusTry != NULL)
            return pfocusTry;

         pui = pui->next_sibling();

      }

      pui = puiThis->first_sibling();

      while(pui != NULL && pui != puiFocus)
      {

         if(pui->keyboard_focus_is_focusable())
            return pui;

         pfocusTry = pui->keyboard_get_next_focusable(pfocus);

         if(pfocusTry != NULL)
            return pfocusTry;

         pui = pui->next_sibling();

      }

      return NULL;

   }



   bool keyboard_focus::keyboard_set_focus()
   {
      Session.user()->set_keyboard_focus( (this));
      return true;
   }

} // namespace user
