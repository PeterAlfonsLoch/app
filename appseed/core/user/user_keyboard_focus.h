#pragma once


namespace ca2
{


   class window;


} // namespace ca2


namespace user
{

   class interaction;
   class control_event;

   class CLASS_DECL_ca2 keyboard_focus :
      virtual public signalizable
   {
   public:
      virtual ~keyboard_focus();

      virtual void keyboard_focus_OnTimer(int32_t iTimer);
      virtual void keyboard_focus_OnChar(signal_details * pobj);
      virtual void keyboard_focus_OnSysChar(signal_details * pobj);
      virtual void keyboard_focus_OnKeyDown(signal_details * pobj);
      virtual void keyboard_focus_OnKeyUp(signal_details * pobj);
      virtual sp(::user::interaction) get_parent() const = 0;
#ifdef METROWIN
      virtual sp(interaction) get_wnd() const = 0;
#else
      virtual sp(::ca2::window) get_wnd() const = 0;
#endif
      virtual bool BaseOnControlEvent(control_event * pevent) = 0;
      virtual keyboard_focus * keyboard_get_next_focusable();
      virtual bool keyboard_set_focus();

      // focus
      virtual bool keyboard_focus_is_focusable();
      virtual bool keyboard_focus_OnSetFocus();
   }; 


} // namespace user