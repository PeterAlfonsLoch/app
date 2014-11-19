#pragma once




namespace user
{


   class CLASS_DECL_AXIS elemental :
      virtual public ::signalizable
   {
   public:


      DWORD       m_dwFocustStart;






      elemental();
      virtual ~elemental();

      virtual void _001RedrawWindow();


      virtual void pre_translate_message(signal_details * pobj);



      virtual void keyboard_focus_OnTimer(int32_t iTimer);
      virtual void keyboard_focus_OnChar(signal_details * pobj);
      virtual void keyboard_focus_OnSysChar(signal_details * pobj);
      virtual void keyboard_focus_OnKeyDown(signal_details * pobj);
      virtual void keyboard_focus_OnKeyUp(signal_details * pobj);
      virtual ::user::interaction * GetParent() const = 0;
      virtual ::user::interaction * GetWindow() const = 0;
      virtual bool BaseOnControlEvent(control_event * pevent) = 0;
      virtual elemental * keyboard_get_next_focusable(elemental * pfocus = NULL,bool bSkipChild = false,bool bSkipSiblings = false,bool bSkipParent = false);
      virtual bool keyboard_set_focus();

      // focus
      virtual bool keyboard_focus_is_focusable();
      virtual bool keyboard_focus_OnSetFocus();

      virtual void mouse_focus_OnLButtonUp(signal_details * pobj);


      virtual void _001GetText(string & str) const;
      virtual void _001GetSelText(string & str) const;
      virtual void _001SetText(const string & str,::action::context actioncontext);

      // string_interface < char > interface
      virtual strsize get_length() const;
      using string_interface::get_string;
      virtual void get_string(char * psz,::primitive::memory_size len) const;
      virtual void set_string(const string & str,::action::context actioncontext);

   };


} // namespace user




