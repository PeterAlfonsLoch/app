#pragma once


class CLASS_DECL_ca file_manager_form_view :
   virtual public form_view,
   virtual public FileManagerViewInterface
{
public:
   file_manager_form_view(::ax::application * papp);

   void on_update(::view * pSender, LPARAM lHint, ::radix::object* phint);
   virtual bool BaseOnControlEvent(::user::control_event * pevent);
};