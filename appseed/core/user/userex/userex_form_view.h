#pragma once


class CLASS_DECL_CORE form_view :
   virtual public html_form_view
{
public:
   form_view(sp(::axis::application) papp);

   void on_update(sp(::user::impact) pSender, LPARAM lHint, object* phint);
   virtual bool BaseOnControlEvent(::user::control_event * pevent);
   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnTimer);
   DECL_GEN_SIGNAL(_001OnUser123);
   virtual void install_message_handling(::message::dispatch * pinterface);
};