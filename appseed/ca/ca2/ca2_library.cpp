#include "framework.h"





namespace ca2
{

   const char * psz_empty_app_id = "";

   library::library(const char * pszRoot)
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

   bool library::open(::ca::application * papp, const char * pszPath, bool bAutoClose)
   {

      set_app(papp);

      m_bAutoClose      = bAutoClose;

      string strCa2Name = pszPath;


      try
      {

         if(!::ca::library::open(strCa2Name))
            return false;

      }
      catch(...)
      {
         return false;
      }

      ::plane::system::eengine().reset();

      PFN_GET_NEW_LIBRARY pfn_get_new_library = NULL;

      try
      {

         pfn_get_new_library = get < PFN_GET_NEW_LIBRARY > ("get_new_library");

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

      m_pca2library = pfn_get_new_library();

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

         strPrefix.replace("-", "_");

         strPrefix += "_";

         gen::str::begins_eat_ci(strName, strPrefix);

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

            if(!::ca::library::close())
               bOk = false;

         }
         catch(...)
         {

            m_plibrary = false;

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

      strPrefix += "/";

      strPrefix += strLibraryName;

      strPrefix += "/";

      gen::str::begins_eat(strAppName, strPrefix);

      if(!contains_app(strAppName))
      {

         strAppName     = pszAppId;
         
         strPrefix      = get_root();

         strPrefix += "/";

         gen::str::begins_eat(strAppName, strPrefix);

         if(!contains_app(strAppName))
            return "";
      }

      return strAppName;

   }


   ::ca::application * library::get_new_app(const char * pszAppId)
   {

      try
      {

         if(m_pca2library != NULL)
         {

            string strAppName = get_app_name(pszAppId);

            if(strAppName.is_empty())
               return NULL;

            ::ca::application * papp = m_pca2library->get_new_app(strAppName);

            if(papp == NULL)
               return NULL;

            ::radix::application  * pradixapp = dynamic_cast < ::radix::application * > (papp);

            if(pradixapp != NULL)
            {
               pradixapp->m_strLibraryName   = m_strCa2Name;
            }

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

         strPrefix.replace("-", "_");

         strPrefix += "_";

         if(gen::str::begins_eat_ci(strAppId, strPrefix))
         {

            stra.add(strAppId);

         }

      }

   }


   ::uinteraction::interaction * library::get_new_uinteraction()
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

   void library::get_create_view_id_list(::raw_array < id > & ida)
   {

      UNREFERENCED_PARAMETER(ida);

   }


   ::dynamic_source::script_manager * library::create_script_manager(::ca::application * papp)
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

   ::dynamic_source::script * library::create_script(::ca::application * papp, const char * pszScript)
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


} // namespace ca2


