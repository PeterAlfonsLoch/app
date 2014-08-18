#pragma once


namespace axis
{


   class CLASS_DECL_AXIS library:
      virtual public ::object
   {
   public:


      void *            m_plibrary;
      sp(library)       m_pca2library;
      bool              m_bAutoClose;
      string            m_strCa2Name;
      string            m_strRoot;
      string            m_strPath;




      library(sp(::axis::application) papp);
      library(sp(::axis::application) papp,int iDesmabi, const char * pszRoot);
      virtual ~library();

      virtual bool open(const char * pszPath,bool bAutoClose = true,bool bCa2Path = false);

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


      virtual string get_root();


      // impl
      virtual sp(::axis::application) get_new_app(const char * pszId);
      virtual void get_app_list(string_array & stra);


      virtual sp(::object) create_object(sp(::axis::application) papp, const char * pszClass);
      virtual bool has_object_class(const char * pszClass);


      virtual string get_library_name();

      virtual string get_app_id(const char * pszAppName);
      virtual string get_app_name(const char * pszAppId);

   
   };



   CLASS_DECL_AXIS void * open_ca2_library(const char * psz);





   template < class APP >
   class single_application_library:
      virtual public library
   {
   public:

      single_application_library(sp(::axis::application) papp,const char * pszRoot): element(papp),::axis::library(papp,0, pszRoot) {}

      // impl
      virtual sp(::axis::application) get_new_app(const char * pszAppId);


   };



   typedef class library * (* PFN_GET_NEW_LIBRARY)(sp(::axis::application) papp);


} // namespace axis







CLASS_DECL_AXIS void * __node_library_open(const char * pszPath);
CLASS_DECL_AXIS void * __node_library_open_ca2(const char * pszPath);
CLASS_DECL_AXIS bool __node_library_close(void * plibrary);
CLASS_DECL_AXIS void * __node_library_raw_get(void * plibrary,const char * pszEntryName);


