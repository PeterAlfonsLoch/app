#pragma once


class CLASS_DECL_BASE message_queue :
   virtual public message_queue_listener
{
public:


   sp(::user::interaction)        m_spuiMessage;


   message_queue();
   message_queue(sp(::base::application) papp);
   virtual ~message_queue();


   bool create_message_queue(sp(::base::application) papp, const char * pszName);
   bool create_message_queue(const char * pszName);
   bool destroy_message_queue();

};



