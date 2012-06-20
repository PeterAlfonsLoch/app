#include "framework.h"
#include "mysql/mysql.h"


namespace simpledb
{


   application::application()
   {
      m_pserver      = NULL;
   }



   bool application::InitializeDataCentral()
   {

      if(is_system())
      {
         /* initialize client library */
         if (mysql_library_init (0, NULL, NULL))
         {
            TRACE("mysql_library_init() failed\n");
            return false;
         }
      }

      m_pserver = new db_server(this);


      m_pserver->add_client(this);

      if(!m_pserver->initialize())
      {
         simple_message_box(NULL, "Could not initialize simpledb.", MB_OK);
         return false;
      }

      return true;
   }

   void application::on_set_locale(const char * lpcsz, bool bUser)
   {
      if(bUser)
      {
         data_set("locale", lpcsz);
      }
      ::database::application::on_set_locale(lpcsz, bUser);
   }

   void application::on_set_schema(const char * lpcsz, bool bUser)
   {
      if(bUser)
      {
         data_set("schema", lpcsz);
      }
      ::database::application::on_set_schema(lpcsz, bUser);
   }

   bool application::FinalizeDataCentral()
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

      if(is_system())
      {

         m_pserver = NULL;

         try
         {
            mysql_library_end();
         }
         catch(...)
         {
         }

      }

      return true;
   }

   bool application::initialize2()
   {

      if(!database::application::initialize2())
         return false;

      if(command().m_varTopicQuery["locale"].get_string().has_char())
      {
         string str = command().m_varTopicQuery["locale"];
         set_locale(str, false);
      }

      if(command().m_varTopicQuery["schema"].get_string().has_char())
      {
         string str = command().m_varTopicQuery["schema"];
         set_schema(str, false);
      }

//      if(&AppUser(this) == NULL)
  //       return false;

      if(!InitializeDataCentral())  
      {
         simple_message_box(NULL, "Could not initialize data central"); 
         return false; 
      }
      ::database::client::initialize(this);

//      ::ca2::application_request * prequest = System.get_application_request();


      if(!is_installing() && !is_uninstalling())
      {

         set_keyboard_layout(NULL, false);

      }

      App(this).fill_locale_schema(*str_context()->m_plocaleschema);

      return true;

   }




   bool application::initialize()
   {

   
      
      if(!database::application::initialize())
         return false;



      return true;


   }


   bool application::finalize()
   {

      try
      {
         database::application::finalize();
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

   ::database::server * application::get_data_server()
   {
      return m_pserver;
   }

   db_server & application::db()
   {
      return *m_pserver;
   }

   bool application::set_keyboard_layout(const char * pszPath, bool bUser)
   {
      UNREFERENCED_PARAMETER(pszPath);
      UNREFERENCED_PARAMETER(bUser);
      return false;
   }

   void application::on_set_keyboard_layout(const char * pszPath, bool bUser)
   {
      
      if(bUser)
      {
      
         if(Application.m_puser != NULL)
         {
            
            data_set("keyboard_layout", pszPath);

         }

      }

   }


} // namespace application