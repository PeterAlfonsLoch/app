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


   typedef class library * ( * PFN_GET_NEW_LIBRARY)(sp(::base::application) papp);


   class CLASS_DECL_CORE library :
      virtual public ::base::library
   {
   public:



      library *         m_pca2library;
      string            m_strCa2Name;
      string            m_strRoot;


      library(sp(::base::application) papp, const char * pszRoot);
      virtual ~library();

      virtual bool open(const char * pszPath, bool bAutoClose = true);
      virtual bool close();


      virtual bool contains_app(const char * pszAppId);


      virtual void get_create_view_id_list(::array < id > & ida);


      virtual void on_create_view(::user::view_creator_data * pcreatordata);

      virtual string get_root();


      // impl
      virtual sp(::base::application) get_new_app(const char * pszId);
      virtual void get_app_list(stringa & stra);


      virtual sp(::user::uinteraction::interaction) get_new_uinteraction();
      virtual bool is_uinteraction_library();


      virtual ::dynamic_source::script_manager * create_script_manager(sp(::base::application) papp);

      virtual void get_script_list(stringa & stra);
      virtual ::dynamic_source::script * create_script(sp(::base::application) papp, const char * pszScript);
      virtual void do_default_script_registration(::dynamic_source::script_manager * pmanager);

      virtual string get_library_name();

      virtual string get_app_id(const char * pszAppName);
      virtual string get_app_name(const char * pszAppId);

   private:

      using ::base::library::open;

   };


   template < class APP >
   class single_application_library :
      virtual public library
   {
   public:

      single_application_library(sp(::base::application) papp, const char * pszRoot) : element(papp), ::base::library(papp), ::core::library(papp, pszRoot) {}

      // impl
      virtual sp(::base::application) get_new_app(const char * pszAppId);


   };



} // namespace core


