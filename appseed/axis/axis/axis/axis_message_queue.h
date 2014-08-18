#pragma once


class CLASS_DECL_AXIS message_queue :
   virtual public ::user::interaction,
   virtual public message_queue_listener
{
public:


   sp(::user::interaction)          m_spuiMessage;
   message_queue_listener *         m_plistener;


   message_queue(sp(::base::application) papp);
   virtual ~message_queue();


   virtual bool create_message_queue(const char * pszName,::message_queue_listener * plistener = NULL);


   virtual void message_handler(signal_details * pobj);
   virtual void message_queue_message_handler(signal_details * pobj);


};







