#include "framework.h"
#ifndef METROWIN
#include "mysql/mysql.h"
#endif


namespace simpledb
{


   simpledb::simpledb(::aura::application * papp) :
      ::object(papp),
      ::aura::department(papp)
   {

      m_pserver      = NULL;

   }

   simpledb::~simpledb()
   {

   }

   bool simpledb::InitializeDataCentral()
   {

      if(m_pauraapp->is_system())
      {
      }

      m_pserver = new db_server(m_pauraapp);


      m_pserver->add_client(this);

      if(!m_pserver->initialize())
      {
         Platform.userex()->simple_message_box(NULL, "Could not initialize simpledb.", MB_OK);
         return false;
      }

      return true;
   }

   void simpledb::on_set_locale(const char * lpcsz, ::action::context actioncontext)
   {
      if(actioncontext.is_user_source())
      {
         data_set(".local://locale", lpcsz);
      }
      m_pauraapp->m_pbasesession->on_set_locale(lpcsz, actioncontext);
   }

   void simpledb::on_set_schema(const char * lpcsz, ::action::context actioncontext)
   {
      if(actioncontext.is_user_source())
      {
         data_set(".local://schema", lpcsz);
      }
      m_pauraapp->m_pbasesession->on_set_schema(lpcsz,actioncontext);
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

      if(m_pauraapp->is_system())
      {

         m_pserver = NULL;
      }

      return true;
   }

   bool simpledb::initialize2()
   {

      if(m_pauraapp->m_pcoreapp->command()->m_varTopicQuery["locale"].get_count() > 0)
      {
         string str = m_pauraapp->m_pcoreapp->command()->m_varTopicQuery["locale"].stra()[0];
         m_pauraapp->m_pbasesession->set_locale(str,::action::source::database());
      }

      if(m_pauraapp->m_pcoreapp->command()->m_varTopicQuery["schema"].get_count() > 0)
      {
         string str = m_pauraapp->m_pcoreapp->command()->m_varTopicQuery["schema"].stra()[0];
         m_pauraapp->m_pbasesession->set_schema(str,::action::source::database());
      }

//      if(&AppUser(this) == NULL)
  //       return false;

      if(!InitializeDataCentral())
      {
         m_pauraapp->m_pcoreapp->simple_message_box(NULL, "Could not initialize data central");
         return false;
      }

      ::database::client::initialize_data_client(m_pserver);

      if (Application.m_spdataserver.is_null())
      {

         Application.m_spdataserver = m_pserver;

      }


//      ::core::application_request * prequest = System.get_application_request();


      m_pauraapp->m_pbasesession->fill_locale_schema(*m_pauraapp->m_pbasesession->str_context()->m_plocaleschema);


      //if(!m_pauraapp->m_pcoreapp->is_installing() && !m_pauraapp->m_pcoreapp->is_uninstalling() && !m_pauraapp->m_pcoreapp->is_system())
      //{

      //   set_keyboard_layout(NULL, ::action::source::system());

      //}


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


   bool simpledb::set_keyboard_layout(const char * pszPath, ::action::context actioncontext)
   {

      return Session.set_keyboard_layout(pszPath, actioncontext);

   }


   void simpledb::on_set_keyboard_layout(const char * pszPath, ::action::context actioncontext)
   {

      if(actioncontext.is_user_source())
      {

         if(Sess(m_pauraapp).safe_get_user() != NULL)
         {

            data_set("keyboard_layout", pszPath);

         }

      }

   }


} // namespace simpledb



