#pragma once


namespace ace
{


   class CLASS_DECL_ACE library:
      virtual public ::object
   {
   public:


      void *            m_plibrary;
      library *         m_pca2library;
      bool              m_bAutoClose;
      string            m_strCa2Name;
      string            m_strRoot;
      ::file::path      m_strPath;




      library(::ace::application * papp);
      library(::ace::application * papp,int iDesmabi, const char * pszRoot);
      virtual ~library();

      virtual bool open(const char * pszPath,bool bAutoClose = true,bool bCa2Path = false);

      virtual bool open_ca2_library();

      library * get_ca2_library();


      virtual bool close();

      virtual void * get_os_data();


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


      virtual string get_root();


      // impl
      virtual sp(::ace::application) get_new_app(const char * pszId);
      virtual void get_app_list(stringa & stra);


      virtual sp(::object) create_object(::ace::application * papp, const char * pszClass, object * p);
      virtual bool has_object_class(const char * pszClass);


      virtual string get_library_name();

      virtual string get_app_id(const char * pszAppName);
      virtual string get_app_name(const char * pszAppId);


   };



   CLASS_DECL_ACE void * open_ca2_library(const char * psz);





   template < class APP >
   class single_application_library:
      virtual public library
   {
   public:

      single_application_library(::ace::application * papp,const char * pszRoot): object(papp),::ace::library(papp,0, pszRoot) {}

      // impl
      virtual sp(::ace::application) get_new_app(const char * pszAppId);


   };



   typedef class library * (* PFN_GET_NEW_LIBRARY)(::ace::application * papp);


} // namespace ace







CLASS_DECL_ACE void * __node_library_open(const char * pszPath);
CLASS_DECL_ACE void * __node_library_open_ca2(const char * pszPath);
CLASS_DECL_ACE bool __node_library_close(void * plibrary);
CLASS_DECL_ACE void * __node_library_raw_get(void * plibrary,const char * pszEntryName);


CLASS_DECL_ACE ::ace::library * lib(const char * psz);

#define LIBCALL(library, entry)  (lib(#library)->get<decltype(&entry)>(#entry))


CLASS_DECL_ACE ::file::path libfilename(const string & str);

