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

   class CLASS_DECL_ca2 control_event
   {
   public:
      control_event();
      virtual ~control_event();

      e_event                 m_eevent;
      sp(::user::interaction)    m_puie;
      uint32_t                    m_uiEvent;
      bool                    m_bUser;
      uint32_t                    m_uiVKey;
      uint32_t                    m_uiFlags;
   };


} // namespace user