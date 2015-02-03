#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE form :
      virtual public ::user::form,
      virtual public ::filemanager::impact
   {
   public:
      
      
      form(::aura::application * papp);


      void on_update(::aura::impact * pSender,LPARAM lHint,object* phint);
      virtual bool BaseOnControlEvent(::user::control_event * pevent);


   };



} // namespace filemanager



















