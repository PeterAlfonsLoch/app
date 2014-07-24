#pragma once

namespace base
{


   typedef class library * (* PFN_GET_NEW_LIBRARY)(sp(::base::application) papp);

   class CLASS_DECL_BASE library:
      virtual public ::element
   {
   public:


      void *                        m_plibrary;
      bool                          m_bAutoClose;
      string            m_strCa2Name;
      string            m_strRoot;




      library(sp(::base::application) papp);
      library(sp(::base::application) papp,const char * pszOpen);
      virtual ~library();

      virtual bool open(const char * pszPath,bool bAutoClose = true);
      virtual bool close();


      virtual bool is_opened();
      virtual bool is_closed();

      template < typename TARGET >
      TARGET get(const char * pszElement)
      {
         return reinterpret_cast <TARGET>(raw_get(pszElement));
      }

      void * raw_get(const char * pszElement);




      virtual bool contains_app(const char * pszAppId);


      virtual void get_create_view_id_list(::array < id > & ida);


      virtual void on_create_view(::user::view_creator_data * pcreatordata);

      virtual string get_root();


      // impl
      virtual sp(::base::application) get_new_app(const char * pszId);
      virtual void get_app_list(stringa & stra);


      virtual sp(::object) create_object(sp(::base::application) papp, char * pszClass);
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



} // namespace base




class CLASS_DECL_BASE ca2_library:
   virtual public ::base::library
{
public:

   ca2_library(sp(::base::application) papp);
   ca2_library(sp(::base::application) papp,const char * pszOpen);
   virtual ~ca2_library();

   virtual bool open(const char * pszPath,bool bAutoClose = true);

};

