#pragma once


class CLASS_DECL_CORE file_manager_form_view :
   virtual public form_view,
   virtual public ::filemanager::impact
{
public:
   file_manager_form_view(sp(::base::application) papp);

   void on_update(sp(::user::impact) pSender, LPARAM lHint, object* phint);
   virtual bool BaseOnControlEvent(::user::control_event * pevent);
};
