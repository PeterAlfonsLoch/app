#pragma once

namespace user
{

   class tab;

   enum e_event
   {
      event_initialize_control,
      event_button_down,
      event_button_clicked,
      event_m_button_down,
      event_m_button_up,
      event_list_clicked,
      event_mouse_enter,
      event_mouse_leave,
      event_set_check,
      event_timer,
      event_enter_key,
      event_escape,
      event_tab_key,
      event_key_down,
      event_after_change_text,
      event_after_change_cur_sel,
      event_timebar_change,
      event_menu_hover,
      event_context_menu_close,
      event_set_focus,
      event_kill_focus,
      event_on_create_view,
      event_on_create_tab,
   };


   class CLASS_DECL_BASE control_event
   {
   public:


      e_event                       m_eevent;
      ::user::interaction *         m_puie;
      ::user::tab *                 m_ptab;
      id                            m_id;
      uint32_t                      m_uiEvent;
      ::action::context             m_actioncontext;
      uint32_t                      m_uiVKey;
      uint32_t                      m_uiFlags;
      bool                          m_bRet;
      bool                          m_bProcessed;
      bool                          m_bOk;
      signal_details *              m_pobj;
      ::datetime::time              m_timeOuterBeg;
      ::datetime::time              m_timeOuterEnd;
      ::datetime::time              m_timeBeg;
      ::datetime::time              m_timeEnd;
      
      
      control_event();
      virtual ~control_event();

      impact * get_view();
      ::user::document * get_document();
      ::user::impact_system * get_impact_system();
      string get_impact_matter();

   };


} // namespace user





