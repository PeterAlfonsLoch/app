#pragma once


namespace user
{


   class CLASS_DECL_AXIS application_as_proxy_document:
      virtual public ::aura::document
   {
   public:

      virtual bool on_open_document(var varFile);
      virtual bool on_save_document(var varFile);

   };


} // namespace user



















