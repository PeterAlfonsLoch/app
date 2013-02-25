#pragma once


namespace cube
{


   class CLASS_DECL_ca2 library :
      virtual public ::ca::single_application_library < application >,
      virtual public ::filehandler::menu_library
   {
   public:


      library();
      

      virtual void get_app_list(stringa & stra);

      virtual void get_extension_list(stringa & stra);

      virtual void get_extension_app(stringa & straApp, const char * pszExtension);

      virtual ::ca::application * get_new_app(const char * pszAppId);


   };


} // namespace cube



