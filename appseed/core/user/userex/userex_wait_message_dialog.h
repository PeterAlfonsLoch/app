#pragma once


namespace userex // ca8 + cube
{


   class CLASS_DECL_CORE wait_message_dialog :
      virtual public dialog
   {
   public:
      
      
      uint32_t          m_dwStartTime;
      uint32_t          m_dwDelay;
      string            m_strResponse;


      wait_message_dialog(::aura::application * papp);
      virtual ~wait_message_dialog();


      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void on_show(const char * pszMatter, property_set & propertyset);

      virtual bool BaseOnControlEvent(::user::control_event * pevent);

      virtual void _001OnTimer(::timer * ptimer) override;

      DECL_GEN_SIGNAL(_001OnCreate);

      virtual bool on_timeout_check();
      virtual bool on_timeout();
      virtual void on_timer_soft_reload(uint32_t dwTimeout);


   };


} // namespace core // ca8 + cube


