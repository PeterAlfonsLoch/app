#pragma once


namespace user
{


   class CLASS_DECL_BASE application_as_proxy_document:
      virtual public ::user::document
   {
   public:


      application_as_proxy_document(::aura::application * papp);
      virtual ~application_as_proxy_document();


      virtual bool on_open_document(var varFile);
      virtual bool on_save_document(var varFile);


   };


} // namespace user




















