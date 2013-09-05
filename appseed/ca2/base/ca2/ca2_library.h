#pragma once


namespace user
{


   class view_creator_data;


} // namespace user



namespace dynamic_source
{


   class script;
   class script_manager;


} // namespace dynamic_source


namespace uinteraction
{


   class interaction;


} // namespace uinteraction



namespace ca2
{


   typedef class library * (* PFN_GET_NEW_LIBRARY)();


   class CLASS_DECL_ca2 library :
      virtual public ::ca::library,
      virtual public object
   {
   public:



      library *         m_pca2library;
      string            m_strCa2Name;
      string            m_strRoot;


      library(const char * pszRoot);
      virtual ~library();

      virtual bool open(sp(base_application) papp, const char * pszPath, bool bAutoClose = true);
      virtual bool close();


      virtual bool contains_app(const char * pszAppId);


      virtual void get_create_view_id_list(::array < id > & ida);


      virtual void on_create_view(::user::view_creator_data * pcreatordata);

      virtual string get_root();


      // impl
      virtual sp(base_application) get_new_app(const char * pszId);
      virtual void get_app_list(stringa & stra);


      virtual sp(::uinteraction::interaction) get_new_uinteraction();
      virtual bool is_uinteraction_library();


      virtual ::dynamic_source::script_manager * create_script_manager(sp(base_application) papp);

      virtual void get_script_list(stringa & stra);
      virtual ::dynamic_source::script * create_script(sp(base_application) papp, const char * pszScript);
      virtual void do_default_script_registration(::dynamic_source::script_manager * pmanager);

      virtual string get_library_name();

      virtual string get_app_id(const char * pszAppName);
      virtual string get_app_name(const char * pszAppId);

   private:

      using ::ca::library::open;

   };


   template < class APP >
   class single_application_library :
      virtual public library
   {
   public:

      single_application_library(const char * pszRoot) : ::ca2::library(pszRoot) {}

      // impl
      virtual sp(base_application) get_new_app(const char * pszAppId);


   };



} // namespace ca2


