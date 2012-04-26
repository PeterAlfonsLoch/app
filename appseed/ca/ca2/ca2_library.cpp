#include "StdAfx.h"


namespace ca2
{

   const char * psz_empty_app_id = "";   

   library::library()
   {
      
      m_pca2library     = NULL;

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


   ::ca::application * library::get_new_app(const char * pszAppId)
   {

      try
      {

         if(m_pca2library != NULL)
         {

            if(!contains_app(pszAppId))
               return NULL;

            ::ca::application * papp = m_pca2library->get_new_app(pszAppId);

            if(papp == NULL)
               return NULL;

            ::radix::application  * pradixapp = dynamic_cast < ::radix::application * > (papp);

            if(pradixapp != NULL)
            {
               pradixapp->m_strLibraryName = m_strCa2Name;
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
         if(gen::str::begins_eat_ci(strAppId, "app_"))
         {
            stra.add(strAppId);
         }
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


