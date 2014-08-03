#include "framework.h"


string_map < INT_PTR,INT_PTR > & __library();


namespace base
{


   const char * psz_empty_app_id = "";


   library::library(sp(::base::application) papp):
      element(papp)
   {

      m_bAutoClose = true;

      m_plibrary = NULL;

   }


   library::library(sp(::base::application) papp,int iDesambig,const char * pszRoot):
      element(papp)
   {

      m_bAutoClose = true;

      m_plibrary = NULL;

      if(pszRoot != NULL)
      {

         m_strRoot = pszRoot;

      }

   }


   library::~library()
   {

      if(m_bAutoClose)
      {

         close();

      }

   }


   bool library::open(const char * pszPath,bool bAutoClose,bool bCa2Path)
   {

      m_bAutoClose = bAutoClose;

#ifdef CUBE
      m_strPath = pszPath;
#else

      try
      {

         if(bCa2Path)
         {

            m_plibrary = __node_library_open_ca2(pszPath);

         }
         else
         {

            m_plibrary = __node_library_open(pszPath);

         }

         if(m_plibrary == NULL)
            return false;

         m_strPath = pszPath;

      }
      catch(...)
      {

         return false;

      }

#endif

      return true;

   }


   bool library::open_ca2_library()
   {

      if(m_pca2library != NULL)
         return true;

      System.eengine().reset();

      PFN_GET_NEW_LIBRARY pfn_get_new_library = NULL;

      try

      {
#ifdef CUBE
         pfn_get_new_library = (PFN_GET_NEW_LIBRARY)(INT_PTR)__library()[m_strPath + "_get_new_library"];
#else
         if((pfn_get_new_library = get < PFN_GET_NEW_LIBRARY >(m_strPath + "_get_new_library")) == NULL)
         {
            pfn_get_new_library = get < PFN_GET_NEW_LIBRARY >("get_new_library");
         }
#endif

      }
      catch(...)
      {

         close();

         return false;

      }

      if(pfn_get_new_library == NULL)
      {

         close();

         return false;

      }

      m_pca2library = pfn_get_new_library(get_app());

      if(m_pca2library == NULL)
      {

         close();


         return false;

      }

      m_pca2library->set_app(get_app());

      m_pca2library->m_strCa2Name = m_strPath;

      m_strCa2Name = m_strPath;

      return true;

   }


   library * library::get_ca2_library()
   {

      return m_pca2library;

   }


   string library::get_library_name()
   {

      if(m_pca2library != NULL)
      {

         return m_pca2library->get_library_name();

      }
      else
      {

         string strName(m_strCa2Name);

         string strPrefix(get_root());

#ifdef METROWIN

         //         strPrefix = "m_" + strPrefix;

#endif

         strPrefix.replace("-","_");

         strPrefix += "_";

         ::str::begins_eat_ci(strName,strPrefix);

         return strName;

      }

   }


   bool library::close()
   {
      try
      {

         bool bOk = true;

         try
         {

            if(m_pca2library != NULL)
            {

               delete m_pca2library;

               m_pca2library = NULL;

            }

         }
         catch(...)
         {

            m_pca2library = NULL;

            bOk = false;

         }

         try
         {

            if(!::__node_library_close(m_plibrary))
               bOk = false;

         }
         catch(...)
         {

            m_plibrary = NULL;

            bOk = false;

         }


         return bOk;

      }
      catch(...)
      {
         return false;
      }

   }

   string library::get_app_id(const char * pszAppName)
   {

      if(!contains_app(pszAppName))
         return "";

      string strPrefix(get_root());

      string strLibraryName(get_library_name());

#if defined(LINUX) || defined(APPLEOS)

      if(strLibraryName == "libca2")
      {

         strLibraryName = "ca2";

      }
      else if(!::str::begins_eat(strLibraryName,"libca2"))
      {

         ::str::begins_eat(strLibraryName,"lib");

      }

#elif defined(METROWIN)

      //      ::str::begins_eat_ci(strLibraryName, "m_");

#endif


      stringa straAppList;

      get_app_list(straAppList);

      strPrefix += "/";

      if(straAppList.get_count() > 1)
      {

         strPrefix += strLibraryName;

         strPrefix += "/";

      }

      return strPrefix + pszAppName;

   }

   string library::get_app_name(const char * pszAppId)
   {

      string strAppName(pszAppId);

      string strPrefix(get_root());

      string strLibraryName(get_library_name());

#if defined(LINUX) || defined(APPLEOS)

      if(strLibraryName == "libca2")
      {

         strLibraryName = "ca2";

      }
      else if(!::str::begins_eat(strLibraryName,"libca2"))
      {

         ::str::begins_eat(strLibraryName,"lib");

      }

#elif defined(METROWIN)

      //      ::str::begins_eat_ci(strLibraryName, "m_");

#endif

      strPrefix += "/";

      strPrefix += strLibraryName;

      strPrefix += "/";

      ::str::begins_eat(strAppName,strPrefix);

      if(!contains_app(strAppName))
      {

         strAppName     = pszAppId;

         strPrefix      = get_root();

         strPrefix += "/";

         ::str::begins_eat(strAppName,strPrefix);

         if(!contains_app(strAppName))
            return "";
      }

      return strAppName;

   }


   sp(::base::application) library::get_new_app(const char * pszAppId)
   {

      try
      {

         if(get_ca2_library() != NULL)
         {

            string strAppName = get_app_name(pszAppId);

            if(strAppName.is_empty())
               return NULL;

            sp(::base::application) papp = get_ca2_library()->get_new_app(strAppName);

            if(papp == NULL)
               return NULL;

            papp->m_strLibraryName   = m_strCa2Name;

            return papp;

         }

         return NULL;
      }
      catch(...)
      {
         return NULL;
      }

   }


   void library::get_app_list(stringa & stra)
   {

      if(get_ca2_library() != NULL)
      {
         try
         {
            get_ca2_library()->get_app_list(stra);
         }
         catch(...)
         {
         }
      }
      else
      {

         string strAppId = m_strCa2Name;

         string strPrefix = get_root();

#if defined(LINUX) || defined(APPLEOS)

         ::str::begins_eat(strAppId,"lib");

#elif defined(METROWIN)

         //         strPrefix = "m_" + strPrefix;

#endif

         strPrefix.replace("-","_");

         strPrefix += "_";

         if(::str::begins_eat_ci(strAppId,strPrefix))
         {

            stra.add(strAppId);

         }

      }

   }


   sp(::object) library::create_object(sp(::base::application) papp,const char * pszClassId)
   {

      if(get_ca2_library() == NULL)
         return NULL;

      return get_ca2_library()->create_object(papp, pszClassId);

   }


   bool library::has_object_class(const char * pszClassId)
   {

      if(get_ca2_library() == NULL)
         return NULL;

      return get_ca2_library()->has_object_class(pszClassId);

   }


   bool library::contains_app(const char * pszAppId)
   {

      stringa stra;

      get_app_list(stra);

      return stra.contains(pszAppId);

   }


   void library::on_create_view(::user::view_creator_data * pcreatordata)
   {

      UNREFERENCED_PARAMETER(pcreatordata);

   }


   string library::get_root()
   {

      if(m_pca2library != NULL)
      {

         return m_pca2library->m_strRoot;

      }

      return m_strRoot;

   }


   void library::get_create_view_id_list(::array < id > & ida)
   {

      UNREFERENCED_PARAMETER(ida);

   }


   bool library::is_opened()
   {

      return m_plibrary != NULL;

   }


   bool library::is_closed()
   {

      return !is_opened();

   }


   void * library::raw_get(const char * pszEntryName)
   {

      return __node_library_raw_get(m_plibrary,pszEntryName);

   }


} // namespace base





