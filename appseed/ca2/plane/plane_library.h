#pragma once


namespace plane
{


   class CLASS_DECL_ca2 library :
      virtual public ::ca::single_application_library < application >,
      virtual public ::filehandler::menu_library
   {
   public:


      library();
      

      // impl
      virtual void get_app_list(stringa & stra);
      virtual void get_extension_list(stringa & stra);
      virtual void get_extension_app(stringa & straApp, const char * pszExtension);


      virtual sp(::ca::application) get_new_app(const char * pszAppId);


   };



} // namespace plane