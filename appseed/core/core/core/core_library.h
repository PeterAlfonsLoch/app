#pragma once


namespace core
{


   class CLASS_DECL_CORE library:
      virtual public ::axis::single_application_library < application >,
      virtual public ::filehandler::menu_library
   {
   public:


      library(sp(::aura::application) papp);


      // impl
      virtual void get_app_list(stringa & stra);
      virtual void get_extension_list(stringa & stra);
      virtual void get_extension_app(stringa & straApp,const char * pszExtension);


      //virtual sp(::aura::application) get_new_app(const char * pszAppId);


   };


} // namespace core


