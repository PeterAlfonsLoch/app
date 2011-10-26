#pragma once

namespace user
{
   

   enum e_event
   {
      event_initialize_control,
      event_button_clicked,
      event_list_clicked,
      event_mouse_enter,
      event_mouse_leave,
      event_set_check,
      event_timer,
      event_enter_key,
      event_tab_key,
      event_key_down,
      event_after_change_text,
   };

   class CLASS_DECL_ca control_event
   {
   public:
      control_event();
      virtual ~control_event();

      e_event                 m_eevent;
      ::user::interaction*    m_puie;
      uint                    m_uiEvent;
      bool                    m_bUser;
      uint                    m_uiVKey;
      uint                    m_uiFlags;
   };


} // namespace user