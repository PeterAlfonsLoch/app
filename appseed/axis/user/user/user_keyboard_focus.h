#pragma once


namespace user
{


   class CLASS_DECL_AXIS keyboard_focus :
      virtual public signalizable
   {
   public:


      DWORD       m_dwFocustStart;


      virtual ~keyboard_focus();


      virtual void keyboard_focus_OnTimer(int32_t iTimer);
      virtual void keyboard_focus_OnChar(signal_details * pobj);
      virtual void keyboard_focus_OnSysChar(signal_details * pobj);
      virtual void keyboard_focus_OnKeyDown(signal_details * pobj);
      virtual void keyboard_focus_OnKeyUp(signal_details * pobj);
      virtual ::user::interaction * GetParent() const = 0;
      virtual sp(::user::interaction) GetWindow() const = 0;
      virtual bool BaseOnControlEvent(control_event * pevent) = 0;
      virtual keyboard_focus * keyboard_get_next_focusable(keyboard_focus * pfocus = NULL, bool bSkipChild = false);
      virtual bool keyboard_set_focus();

      // focus
      virtual bool keyboard_focus_is_focusable();
      virtual bool keyboard_focus_OnSetFocus();
   };


} // namespace user




