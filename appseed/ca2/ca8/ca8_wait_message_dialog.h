#pragma once


namespace ca8
{


   class CLASS_DECL_ca2 wait_message_dialog :
      virtual public dialog
   {
   public:
      DWORD       m_dwStartTime;
      DWORD       m_dwDelay;
      string      m_strResponse;


      wait_message_dialog(::ca::application * papp);
      virtual ~wait_message_dialog();

      virtual void on_show(const char * pszMatter, gen::property_set & propertyset);

      virtual bool BaseOnControlEvent(::user::control_event * pevent);

      virtual bool on_timeout();
      virtual void on_timer_soft_reload(DWORD dwTimeout);

   };


} // namespace ca8


