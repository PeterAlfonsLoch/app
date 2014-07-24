#pragma once


namespace user
{


   class view_creator_data;


   namespace uinteraction
   {


      class interaction;


   } // namespace uinteraction

} // namespace user



namespace dynamic_source
{


   class script;
   class script_manager;


} // namespace dynamic_source





namespace core
{




   class CLASS_DECL_CORE library:
      virtual public ::bas::single_application_library < application >,
      virtual public ::filehandler::menu_library
   {
   public:


      library(sp(::base::application) papp);


      // impl
      virtual void get_app_list(stringa & stra);
      virtual void get_extension_list(stringa & stra);
      virtual void get_extension_app(stringa & straApp,const char * pszExtension);


      //virtual sp(::base::application) get_new_app(const char * pszAppId);


   };


} // namespace core


