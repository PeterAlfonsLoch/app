#include "framework.h"





namespace ca
{

   const char * psz_empty_app_id = "";

   library::library(const char * pszRoot)
   {

      m_pca2library     = ::null();

      if(pszRoot != ::null())
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

   bool library::open(sp(::ca::application) papp, const char * pszPath, bool bAutoClose)
   {

      set_app(papp);

      m_bAutoClose      = bAutoClose;

      string strCa2Name = pszPath;


      try
      {

         if(!::c::library::open(strCa2Name))
            return false;

      }
      catch(...)
      {
         return false;
      }

      ::plane::system::eengine().reset();

      PFN_GET_NEW_LIBRARY pfn_get_new_library = ::null();

      try
      {

         pfn_get_new_library = get < PFN_GET_NEW_LIBRARY > ("get_new_library");

      }
      catch(...)
      {

         close();

         return false;

      }

      if(pfn_get_new_library == ::null())
      {

         close();

         return false;

      }

      m_pca2library = pfn_get_new_library();

      if(m_pca2library == ::null())
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

      if(m_pca2library != ::null())
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

         ::ca::str::begins_eat_ci(strName, strPrefix);

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

            if(m_pca2library != ::null())
            {

               delete m_pca2library;

               m_pca2library = ::null();

            }

         }
         catch(...)
         {

            m_pca2library = ::null();

            bOk = false;

         }

         try
         {

            if(!::c::library::close())
               bOk = false;

         }
         catch(...)
         {

            m_plibrary = ::null();

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

#ifdef LINUX

      if(strLibraryName == "libca2")
      {

         strLibraryName = "ca2";

      }
      else if(!::ca::str::begins_eat(strLibraryName, "libca2"))
      {

         ::ca::str::begins_eat(strLibraryName, "lib");

      }

#elif defined(METROWIN)

//      ::ca::str::begins_eat_ci(strLibraryName, "m_");

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

#ifdef LINUX

      if(strLibraryName == "libca2")
      {

         strLibraryName = "ca2";

      }
      else if(!::ca::str::begins_eat(strLibraryName, "libca2"))
      {

         ::ca::str::begins_eat(strLibraryName, "lib");

      }

#elif defined(METROWIN)

//      ::ca::str::begins_eat_ci(strLibraryName, "m_");

#endif

      strPrefix += "/";

      strPrefix += strLibraryName;

      strPrefix += "/";

      ::ca::str::begins_eat(strAppName, strPrefix);

      if(!contains_app(strAppName))
      {

         strAppName     = pszAppId;

         strPrefix      = get_root();

         strPrefix += "/";

         ::ca::str::begins_eat(strAppName, strPrefix);

         if(!contains_app(strAppName))
            return "";
      }

      return strAppName;

   }


   sp(::ca::application) library::get_new_app(const char * pszAppId)
   {

      try
      {

         if(m_pca2library != ::null())
         {

            string strAppName = get_app_name(pszAppId);

            if(strAppName.is_empty())
               return ::null();

            sp(::ca::application) papp = m_pca2library->get_new_app(strAppName);

            if(papp == ::null())
               return ::null();

            papp->m_strLibraryName   = m_strCa2Name;

            return papp;

         }

         return ::null();
      }
      catch(...)
      {
         return ::null();
      }

   }

   void library::get_app_list(stringa & stra)
   {

      if(m_pca2library != ::null())
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

#ifdef LINUX

         ::ca::str::begins_eat(strAppId, "lib");

#elif defined(METROWIN)

//         strPrefix = "m_" + strPrefix;

#endif

         strPrefix.replace("-", "_");

         strPrefix += "_";

         if(::ca::str::begins_eat_ci(strAppId, strPrefix))
         {

            stra.add(strAppId);

         }

      }

   }


   sp(::uinteraction::interaction) library::get_new_uinteraction()
   {

      if(m_pca2library != ::null())
      {

         try
         {

            return m_pca2library->get_new_uinteraction();

         }
         catch(...)
         {

            return ::null();

         }

      }
      else
      {

         return ::null();

      }


   }


   bool library::is_uinteraction_library()
   {

      if(m_pca2library != ::null())
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

      if(m_pca2library != ::null())
      {

         return m_pca2library->m_strRoot;

      }

      return m_strRoot;

   }

   void library::get_create_view_id_list(::array < id > & ida)
   {

      UNREFERENCED_PARAMETER(ida);

   }


   ::dynamic_source::script_manager * library::create_script_manager(sp(::ca::application) papp)
   {

      if(m_pca2library != ::null())
      {
         return m_pca2library->create_script_manager(papp);
      }

      return ::null();

   }


   void library::get_script_list(stringa & stra)
   {

      if(m_pca2library != ::null())
      {
         return m_pca2library->get_script_list(stra);
      }

   }

   ::dynamic_source::script * library::create_script(sp(::ca::application) papp, const char * pszScript)
   {

      if(m_pca2library != ::null())
      {
         return m_pca2library->create_script(papp, pszScript);
      }

      return ::null();


   }

   void library::do_default_script_registration(::dynamic_source::script_manager * pmanager)
   {

      if(m_pca2library != ::null())
      {
         return m_pca2library->do_default_script_registration(pmanager);
      }

   }


} // namespace ca


