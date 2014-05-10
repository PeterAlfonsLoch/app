#pragma once


class CLASS_DECL_CORE menu_view :
   virtual public form_view
{
public:
   menu_view(sp(::base::application) papp);

   void on_update(sp(::user::impact) pSender, LPARAM lHint, object* phint);
   virtual bool BaseOnControlEvent(::user::control_event * pevent);
   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnTimer);
   DECL_GEN_SIGNAL(_001OnUser123);
   virtual void install_message_handling(::message::dispatch * pinterface);
};