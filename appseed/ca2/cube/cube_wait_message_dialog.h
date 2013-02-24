#pragma once


namespace cube // ca8 + cube
{


   class CLASS_DECL_ca2 wait_message_dialog :
      virtual public dialog
   {
   public:
      uint32_t       m_dwStartTime;
      uint32_t       m_dwDelay;
      string      m_strResponse;


      wait_message_dialog(::ca::application * papp);
      virtual ~wait_message_dialog();

      virtual void on_show(const char * pszMatter, ca::property_set & propertyset);

      virtual bool BaseOnControlEvent(::user::control_event * pevent);

      virtual bool on_timeout();
      virtual void on_timer_soft_reload(uint32_t dwTimeout);

   };


} // namespace cube // ca8 + cube


