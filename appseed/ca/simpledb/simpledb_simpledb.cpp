#include "framework.h"
#ifndef METROWIN
#include "mysql/mysql.h"
#endif


namespace simpledb
{


   simpledb::simpledb()
   {

      m_pserver      = NULL;

   }


   bool simpledb::InitializeDataCentral()
   {

      if(m_papp->is_system())
      {
#ifndef METROWIN
         /* initialize client library */
         if (mysql_library_init (0, NULL, NULL))
         {
            TRACE("mysql_library_init() failed\n");
            return false;
         }
#endif
      }

      m_pserver = new db_server(m_papp);


      m_pserver->add_client(this);

      if(!m_pserver->initialize())
      {
         Application.user()->simple_message_box(NULL, "Could not initialize simpledb.", MB_OK);
         return false;
      }

      return true;
   }

   void simpledb::on_set_locale(const char * lpcsz, bool bUser)
   {
      if(bUser)
      {
         data_set("locale", lpcsz);
      }
      m_papp->m_pappThis->on_set_locale(lpcsz, bUser);
   }

   void simpledb::on_set_schema(const char * lpcsz, bool bUser)
   {
      if(bUser)
      {
         data_set("schema", lpcsz);
      }
      m_papp->m_pappThis->on_set_schema(lpcsz, bUser);
   }

   bool simpledb::FinalizeDataCentral()
   {

      try
      {
         m_pserver->finalize();
      }
      catch(...)
      {
      }

      try
      {
         delete m_pserver;
      }
      catch(...)
      {
      }

      if(m_papp->is_system())
      {

         m_pserver = NULL;
#ifndef METROWIN
         try
         {
            mysql_library_end();
         }
         catch(...)
         {
         }
#endif
      }

      return true;
   }

   bool simpledb::initialize2()
   {

      if(m_papp->m_pappThis->command().m_varTopicQuery["locale"].get_string().has_char())
      {
         string str = m_papp->m_pappThis->command().m_varTopicQuery["locale"];
         m_papp->m_pappThis->set_locale(str, false);
      }

      if(m_papp->m_pappThis->command().m_varTopicQuery["schema"].get_string().has_char())
      {
         string str = m_papp->m_pappThis->command().m_varTopicQuery["schema"];
         m_papp->m_pappThis->set_schema(str, false);
      }

//      if(&AppUser(this) == NULL)
  //       return false;

      if(!InitializeDataCentral())
      {
         m_papp->m_pappThis->simple_message_box(NULL, "Could not initialize data central");
         return false;
      }

      ::database::client::initialize_data_client(m_pserver);

//      ::ca::application_request * prequest = System.get_application_request();


      m_papp->m_pappThis->fill_locale_schema(*m_papp->m_pappThis->str_context()->m_plocaleschema);


      if(!m_papp->m_pappThis->is_installing() && !m_papp->m_pappThis->is_uninstalling())
      {

         set_keyboard_layout(NULL, false);

      }


      return true;

   }




   bool simpledb::initialize()
   {



      if(!::database::database::initialize())
         return false;



      return true;


   }


   bool simpledb::finalize()
   {

      try
      {
       //  ::database::database::finalize();
      }
      catch(...)
      {
      }

      try
      {
         FinalizeDataCentral();
      }
      catch(...)
      {
      }


      return true;


   }

   ::database::server * simpledb::get_data_server()
   {
      return m_pserver;
   }

   db_server & simpledb::db()
   {
      return *m_pserver;
   }

   bool simpledb::set_keyboard_layout(const char * pszPath, bool bUser)
   {
      return Application.user()->set_keyboard_layout(pszPath, bUser);

   }

   void simpledb::on_set_keyboard_layout(const char * pszPath, bool bUser)
   {

      if(bUser)
      {

         if(App(m_papp).get_safe_user() != NULL)
         {

            data_set("keyboard_layout", pszPath);

         }

      }

   }


} // namespace simpledb



