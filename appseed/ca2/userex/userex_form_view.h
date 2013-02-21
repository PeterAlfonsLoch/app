#pragma once


class CLASS_DECL_ca2 form_view :
   virtual public html_form_view
{
public:
   form_view(::ca::application * papp);

   void on_update(::view * pSender, LPARAM lHint, ::gen::object* phint);
   virtual bool BaseOnControlEvent(::user::control_event * pevent);
   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnTimer)
   DECL_GEN_SIGNAL(_001OnUser123)
   virtual void install_message_handling(::gen::message::dispatch * pinterface);
};