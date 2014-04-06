#include "framework.h"


string_map < INT_PTR, INT_PTR > & __library();


namespace core
{

   const char * psz_empty_app_id = "";

   library::library(sp(base_application) papp, const char * pszRoot) :
      element(papp),
      base_library(papp)
   {

      m_pca2library     = NULL;

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

   bool library::open(const char * pszPath, bool bAutoClose)
   {

      try
      {

         string strCa2Name = pszPath;

#ifndef CUBE

         try
         {

            if(!base_library::open(strCa2Name, bAutoClose))
               return false;

         }
         catch(...)
         {

            return false;

         }

#endif

         ::plane::system::eengine().reset();

         PFN_GET_NEW_LIBRARY pfn_get_new_library = NULL;

         try
      
{
#ifdef CUBE
            pfn_get_new_library = (PFN_GET_NEW_LIBRARY) (INT_PTR) __library()[strCa2Name + "_get_new_library"];
#else
            pfn_get_new_library = get < PFN_GET_NEW_LIBRARY >("get_new_library");
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

         m_pca2library->m_strCa2Name = strCa2Name;

         m_strCa2Name = strCa2Name;

         return true;

      }
      catch(...)
      {
      }

      try
      {

         close();

         //System.file().del(pszPath);

      }
      catch(...)
      {
      }


      return false;

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

         strPrefix.replace("-", "_");

         strPrefix += "_";

         ::str::begins_eat_ci(strName, strPrefix);

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

            if(!base_library::close())
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

#if defined(LINUX) || defined(MACOS)

      if(strLibraryName == "libca2")
      {

         strLibraryName = "ca2";

      }
      else if(!::str::begins_eat(strLibraryName, "libca2"))
      {

         ::str::begins_eat(strLibraryName, "lib");

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

#if defined(LINUX) || defined(MACOS)

      if(strLibraryName == "libca2")
      {

         strLibraryName = "ca2";

      }
      else if(!::str::begins_eat(strLibraryName, "libca2"))
      {

         ::str::begins_eat(strLibraryName, "lib");

      }

#elif defined(METROWIN)

//      ::str::begins_eat_ci(strLibraryName, "m_");

#endif

      strPrefix += "/";

      strPrefix += strLibraryName;

      strPrefix += "/";

      ::str::begins_eat(strAppName, strPrefix);

      if(!contains_app(strAppName))
      {

         strAppName     = pszAppId;

         strPrefix      = get_root();

         strPrefix += "/";

         ::str::begins_eat(strAppName, strPrefix);

         if(!contains_app(strAppName))
            return "";
      }

      return strAppName;

   }


   sp(base_application) library::get_new_app(const char * pszAppId)
   {

      try
      {

         if(m_pca2library != NULL)
         {

            string strAppName = get_app_name(pszAppId);

            if(strAppName.is_empty())
               return NULL;

            sp(base_application) papp = m_pca2library->get_new_app(strAppName);

            if(papp == NULL)
               return NULL;

            papp->m_pplaneapp->m_strLibraryName   = m_strCa2Name;

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

      if(m_pca2library != NULL)
      {
         try
         {
            m_pca2library->get_app_list(stra);
         }
         catch(...)
         {
         }
      }
      else
      {

         string strAppId = m_strCa2Name;

         string strPrefix = get_root();

#if defined(LINUX) || defined(MACOS)

         ::str::begins_eat(strAppId, "lib");

#elif defined(METROWIN)

//         strPrefix = "m_" + strPrefix;

#endif

         strPrefix.replace("-", "_");

         strPrefix += "_";

         if(::str::begins_eat_ci(strAppId, strPrefix))
         {

            stra.add(strAppId);

         }

      }

   }


   sp(::user::uinteraction::interaction) library::get_new_uinteraction()
   {

      if(m_pca2library != NULL)
      {

         try
         {

            return m_pca2library->get_new_uinteraction();

         }
         catch(...)
         {

            return NULL;

         }

      }
      else
      {

         return NULL;

      }


   }


   bool library::is_uinteraction_library()
   {

      if(m_pca2library != NULL)
      {

         try
         {

            return m_pca2library->is_uinteraction_library();

         }
         catch(...)
         {

            return false;

         }

      }
      else
      {

         return false;

      }

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


   ::dynamic_source::script_manager * library::create_script_manager(sp(base_application) papp)
   {

      if(m_pca2library != NULL)
      {
         return m_pca2library->create_script_manager(papp);
      }

      return NULL;

   }


   void library::get_script_list(stringa & stra)
   {

      if(m_pca2library != NULL)
      {
         return m_pca2library->get_script_list(stra);
      }

   }

   ::dynamic_source::script * library::create_script(sp(base_application) papp, const char * pszScript)
   {

      if(m_pca2library != NULL)
      {
         return m_pca2library->create_script(papp, pszScript);
      }

      return NULL;


   }

   void library::do_default_script_registration(::dynamic_source::script_manager * pmanager)
   {

      if(m_pca2library != NULL)
      {
         return m_pca2library->do_default_script_registration(pmanager);
      }

   }


} // namespace core


