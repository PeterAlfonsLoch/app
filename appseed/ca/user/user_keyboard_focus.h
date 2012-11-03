#pragma once


namespace ca
{


   class window;


} // namespace ca


namespace user
{

   class interaction;
   class control_event;

   class CLASS_DECL_ca keyboard_focus :
      virtual public gen::signalizable
   {
   public:
      virtual ~keyboard_focus();

      virtual void keyboard_focus_OnTimer(int iTimer);
      virtual void keyboard_focus_OnChar(gen::signal_object * pobj);
      virtual void keyboard_focus_OnSysChar(gen::signal_object * pobj);
      virtual void keyboard_focus_OnKeyDown(gen::signal_object * pobj);
      virtual void keyboard_focus_OnKeyUp(gen::signal_object * pobj);
      virtual interaction * get_parent() = 0;
      virtual ::ca::window * get_wnd() const = 0;
      virtual bool BaseOnControlEvent(control_event * pevent) = 0;
      virtual keyboard_focus * keyboard_get_next_focusable();
      virtual bool keyboard_set_focus();

      // focus
      virtual bool keyboard_focus_is_focusable();
      virtual bool keyboard_focus_OnSetFocus();
   }; 


} // namespace user