#pragma once


namespace sphere
{


   class CLASS_DECL_sphere library :
      virtual public ::ca2::single_application_library < application >,
      virtual public ::filehandler::menu_library
   {
   public:


      library();
      

      virtual void get_app_list(stringa & stra);

      virtual void get_extension_list(stringa & stra);

      virtual void get_extension_app(stringa & straApp, const char * pszExtension);

//      virtual sp(::ca2::application) get_new_app(const char * pszAppId);


   };


} // namespace sphere



