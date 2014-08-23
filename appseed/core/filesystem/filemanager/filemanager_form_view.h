#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE form_view:
      virtual public ::form_view,
      virtual public ::filemanager::impact
   {
   public:
      
      
      form_view(sp(::aura::application) papp);


      void on_update(sp(::user::impact) pSender,LPARAM lHint,object* phint);
      virtual bool BaseOnControlEvent(::user::control_event * pevent);


   };



} // namespace filemanager



















