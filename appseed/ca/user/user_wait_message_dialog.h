#pragma once

class CLASS_DECL_ca wait_message_dialog :
   virtual public ::ca::object
{
public:
   uint32_t       m_dwStartTime;
   uint32_t       m_dwDelay;
   string      m_strResponse;


   wait_message_dialog(::ca::application * papp);
   virtual ~wait_message_dialog();

   virtual void on_show(const char * pszMatter, ca::property_set & propertyset);

//   virtual bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);

   virtual bool on_timeout();
   virtual void on_timer_soft_reload(uint32_t dwTimeout);

};

