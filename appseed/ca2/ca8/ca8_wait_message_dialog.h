#pragma once

class CLASS_DECL_ca wait_message_dialog :
   virtual public dialog
{
public:
   DWORD       m_dwStartTime;
   DWORD       m_dwDelay;
   string      m_strResponse;


   wait_message_dialog(::ax::application * papp);
   virtual ~wait_message_dialog();

   virtual void on_show(const char * pszMatter, gen::property_set & propertyset);

   virtual bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);

   virtual bool on_timeout();
   virtual void on_timer_soft_reload(DWORD dwTimeout);

};

