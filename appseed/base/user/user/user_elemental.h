#pragma once




namespace user
{


   class CLASS_DECL_BASE elemental :
      virtual public command_target,
      virtual public string_interface
   {
   public:


      DWORD       m_dwFocustStart;






      elemental();
      virtual ~elemental();


      // elemental

      virtual void _001RedrawWindow();


      virtual void pre_translate_message(signal_details * pobj);


      // keyboard focus

      virtual void keyboard_focus_OnTimer(int32_t iTimer);
      virtual void keyboard_focus_OnChar(signal_details * pobj);
      virtual void keyboard_focus_OnSysChar(signal_details * pobj);
      virtual void keyboard_focus_OnKeyDown(signal_details * pobj);
      virtual void keyboard_focus_OnKeyUp(signal_details * pobj);
      virtual ::user::interaction * GetParent() const;
      virtual ::user::interaction * GetWindow() const;
      virtual bool BaseOnControlEvent(control_event * pevent);
      virtual elemental * keyboard_get_next_focusable(elemental * pfocus = NULL,bool bSkipChild = false,bool bSkipSiblings = false,bool bSkipParent = false);
      virtual bool keyboard_set_focus();

      // focus
      virtual bool keyboard_focus_is_focusable();
      virtual bool keyboard_focus_OnSetFocus();
      virtual void keyboard_focus_OnKillFocus();

      // mouse focus

      virtual void mouse_focus_OnLButtonUp(signal_details * pobj);

      // text interface

      virtual void _001GetText(string & str) const;
      virtual void _001GetSelText(string & str) const;
      virtual void _001SetText(const string & str,::action::context actioncontext);

      // string_interface < char > interface
      virtual strsize get_length() const;
      using string_interface::get_string;
      virtual void get_string(char * psz,::primitive::memory_size len) const;
      virtual void set_string(const string & str,::action::context actioncontext);


      // check interface

      virtual check::e_check _001GetCheck();
      virtual void _001SetCheck(bool b,::action::context actioncontext);   // 0, 1
      virtual void _001SetCheck(check::e_check check,::action::context actioncontext);
      virtual void _001ToggleCheck(::action::context actioncontext);


   };


} // namespace user




