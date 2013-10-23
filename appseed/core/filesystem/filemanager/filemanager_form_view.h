#pragma once


class CLASS_DECL_CORE file_manager_form_view :
   virtual public form_view,
   virtual public FileManagerViewInterface
{
public:
   file_manager_form_view(sp(base_application) papp);

   void on_update(sp(::user::view) pSender, LPARAM lHint, object* phint);
   virtual bool BaseOnControlEvent(::user::control_event * pevent);
};
