#pragma once


namespace base
{


   class CLASS_DECL_BASE library:
      virtual public ::object
   {
   public:


      void *            m_plibrary;
      sp(library)       m_pca2library;
      bool              m_bAutoClose;
      string            m_strCa2Name;
      string            m_strRoot;
      string            m_strPath;




      library(sp(::base::application) papp);
      library(sp(::base::application) papp,int iDesmabi, const char * pszRoot);
      virtual ~library();

      virtual bool open(const char * pszPath, bool bCa2Path = false, bool bAutoClose = true);

      virtual bool open_ca2_library();

      library * get_ca2_library();


      virtual bool close();


      virtual bool is_opened();
      virtual bool is_closed();

      template < typename TARGET >
      TARGET get(const char * pszEntryName)
      {
         return reinterpret_cast <TARGET>(raw_get(pszEntryName));
      }

      void * raw_get(const char * pszEntryName);




      virtual bool contains_app(const char * pszAppId);


      virtual void get_create_view_id_list(::array < id > & ida);


      virtual void on_create_view(::user::view_creator_data * pcreatordata);

      virtual string get_root();


      // impl
      virtual sp(::base::application) get_new_app(const char * pszId);
      virtual void get_app_list(stringa & stra);


      virtual sp(::object) create_object(sp(::base::application) papp, const char * pszClass);
      virtual bool has_object_class(const char * pszClass);


//      virtual ::dynamic_source::script_manager * create_script_manager(sp(::base::application) papp);

  //    virtual void get_script_list(stringa & stra);
  //    virtual ::dynamic_source::script * create_script(sp(::base::application) papp,const char * pszScript);
//      virtual void do_default_script_registration(::dynamic_source::script_manager * pmanager);

      virtual string get_library_name();

      virtual string get_app_id(const char * pszAppName);
      virtual string get_app_name(const char * pszAppId);

   
   };



   CLASS_DECL_BASE void * open_ca2_library(const char * psz);





   template < class APP >
   class single_application_library:
      virtual public library
   {
   public:

      single_application_library(sp(::base::application) papp,const char * pszRoot): element(papp),::base::library(papp),::core::library(papp,pszRoot) {}

      // impl
      virtual sp(::base::application) get_new_app(const char * pszAppId);


   };



   typedef class library * (* PFN_GET_NEW_LIBRARY)(sp(::base::application) papp);


} // namespace base







CLASS_DECL_BASE void * __node_library_open(const char * pszPath);
CLASS_DECL_BASE void * __node_library_open_ca2(const char * pszPath);
CLASS_DECL_BASE bool __node_library_close(void * plibrary);
CLASS_DECL_BASE void * __node_library_raw_get(void * plibrary,const char * pszEntryName);


