#pragma once


class CLASS_DECL_ca2 file_manager_form_view :
   virtual public form_view,
   virtual public FileManagerViewInterface
{
public:
   file_manager_form_view(::ca::application * papp);

   void on_update(::view * pSender, LPARAM lHint, ::ca::object* phint);
   virtual bool BaseOnControlEvent(::user::control_event * pevent);
};