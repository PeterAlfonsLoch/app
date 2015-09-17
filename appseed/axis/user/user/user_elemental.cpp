//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


namespace user
{


   elemental::elemental()
   {

      m_bDestroying = false;

   }


   elemental::~elemental()
   {

   }


   // elemental

   void elemental::_001RedrawWindow(UINT nFlags)
   {

   }


   void elemental::pre_translate_message(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }


   // keyboard focus
   void elemental::on_keyboard_focus(::user::elemental * pfocus)
   {
      UNREFERENCED_PARAMETER(pfocus);
   }

   void elemental::keyboard_focus_OnTimer(int32_t iTimer)
   {
      UNREFERENCED_PARAMETER(iTimer);
   }

   void elemental::keyboard_focus_OnChar(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void elemental::keyboard_focus_OnSysChar(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void elemental::keyboard_focus_OnKeyDown(signal_details * pobj)
   {

   }

   void elemental::keyboard_focus_OnKeyUp(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   ::user::interaction * elemental::GetParent() const
   {

      return NULL;

   }

   ::user::interaction * elemental::get_wnd() const
   {

      return NULL;

   }

   bool elemental::BaseOnControlEvent(control_event * pevent)
   {

      UNREFERENCED_PARAMETER(pevent);

      return false;

   }


   bool elemental::keyboard_focus_is_focusable()
   {

      return Application.keyboard_focus_is_focusable(this);
   }

   bool elemental::keyboard_focus_OnSetFocus()
   {

      m_dwFocustStart = get_tick_count();

      // get_keyboard_focus will return the control with focus


      // return true to set focus to this control
      return Application.keyboard_focus_OnSetFocus(this);
   }

   
   void elemental::keyboard_focus_OnKillFocus()
   {


   }


   elemental * elemental::keyboard_get_next_focusable(elemental * pfocus,bool bSkipChild,bool bSkipSiblings,bool bSkipParent)
   {

      sp(elemental) puiThis = this;

      sp(elemental) puiFocus = pfocus != NULL ? pfocus : this;



      elemental * pfocusTry;

      if(puiFocus == NULL)
         return NULL;

      if(puiThis == NULL)
         return NULL;

      single_lock(puiThis->m_pauraapp->m_pmutex,TRUE);

      sp(elemental) pui;

      if(!bSkipChild)
      {

         pui = puiThis->first_child_elemental();

         if(pui != NULL)
         {

            if(pui->keyboard_focus_is_focusable())
               return pui;

            pui = pui->keyboard_get_next_focusable(puiFocus,false,false,true);

            if(pui != NULL)
               return pui;

         }

      }

      if(!bSkipSiblings)
      {

         pui = puiThis->next_elemental();

         while(pui != NULL)
         {

            if(pui->keyboard_focus_is_focusable())
               return pui;

            pfocusTry = pui->keyboard_get_next_focusable(puiFocus,false,true,true);

            if(pfocusTry != NULL)
               return pfocusTry;

            pui = pui->next_elemental();

         }

      }

      if(!bSkipParent)
      {


         if(puiThis->GetParent() != NULL)
         {

            pui = puiThis->get_parent()->keyboard_get_next_focusable(puiFocus,true);

            if(pui.is_set())
               return pui;

         }

      }

      if(!bSkipSiblings)
      {

         pui = puiThis->first_child_elemental();

         if(pui != puiThis)
         {

            while(pui != NULL && pui != puiFocus)
            {

               if(pui->keyboard_focus_is_focusable())
                  return pui;

               pfocusTry = pui->keyboard_get_next_focusable(puiFocus,false,true,true);

               if(pfocusTry != NULL)
                  return pfocusTry;

               pui = pui->next_elemental();

            }

         }

      }


      return NULL;

   }



   bool elemental::keyboard_set_focus()
   {
      Session.set_keyboard_focus((this));
      return true;
   }

   // mouse focus

   void elemental::mouse_focus_OnLButtonUp(signal_details * pobj)
   {
   }

   // text interface

   void elemental::_001GetText(string & str) const
   {

      UNREFERENCED_PARAMETER(str);

   }


   void elemental::_001GetSelText(string & str) const
   {

      UNREFERENCED_PARAMETER(str);

   }


   void elemental::_001SetText(const string & str,::action::context actioncontext)
   {

      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(actioncontext);

   }


   strsize elemental::get_length() const
   {

      string str;
      _001GetText(str);
      return str.get_length();

   }


   void elemental::get_string(char * psz,::primitive::memory_size len) const
   {

      string str;

      _001GetText(str);

      strncpy(psz,str,len);

   }

   void elemental::set_string(const string & str,::action::context actioncontext)
   {

      _001SetText(str,actioncontext);

   }


   // check interface

   check::e_check elemental::_001GetCheck()
   {

      return check::unchecked;

   }


   void elemental::_001SetCheck(bool bChecked,::action::context actioncontext)
   {

      _001SetCheck((check::e_check) (bChecked ? check::checked : check::unchecked),actioncontext);

   }


   void elemental::_001SetCheck(check::e_check echeck,::action::context actioncontext)
   {

      UNREFERENCED_PARAMETER(echeck);
      UNREFERENCED_PARAMETER(actioncontext);

   }


   void elemental::_001ToggleCheck(::action::context actioncontext)
   {

      if(_001GetCheck() == check::checked)
      {

         _001SetCheck(check::unchecked,actioncontext);

      }
      else if(_001GetCheck() == check::unchecked)
      {

         _001SetCheck(check::checked,actioncontext);

      }
      else if(_001GetCheck() == check::tristate)
      {

         _001SetCheck(check::unchecked,actioncontext);

      }
      else
      {

         _001SetCheck(check::unchecked,actioncontext);

      }

   }

   ::user::elemental * elemental::first_child_elemental()
   {

      return NULL;

   }


   ::user::elemental * elemental::top_elemental()
   {

      return NULL;

   }


   ::user::elemental * elemental::under_elemental()
   {

      return NULL;

   }


   ::user::elemental * elemental::above_elemental()
   {

      return NULL;

   }


   ::user::elemental * elemental::next_elemental()
   {

      return NULL;

   }


   ::user::elemental * elemental::previous_elemental()
   {

      return NULL;

   }

   ::user::elemental * elemental::get_parent() const
   {

      return NULL;

   }

   ::user::elemental * elemental::get_wnd_elemental() const
   {

      return NULL;

   }

   void elemental::_001OnTimer(::timer * ptimer)
   {

      UNREFERENCED_PARAMETER(ptimer);

   }


} // namespace user




