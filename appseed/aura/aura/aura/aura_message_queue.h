#pragma once


class CLASS_DECL_AURA message_queue :
   virtual public message_queue_listener
{
public:


   message_queue_listener *         m_plistener;


   message_queue(sp(::aura::application) papp);
   virtual ~message_queue();


   virtual bool create_message_queue(const char * pszName,::message_queue_listener * plistener = NULL);


   virtual void message_handler(signal_details * pobj);
   virtual void message_queue_message_handler(signal_details * pobj);


   virtual bool is_initialized();


   virtual bool message_queue_set_timer(uint_ptr uiId,DWORD dwMillis);

};







