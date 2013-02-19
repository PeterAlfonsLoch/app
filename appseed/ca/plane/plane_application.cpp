#include "framework.h"


namespace plane
{


   application::application()
   {
      
      m_papp      = this;
      m_pappThis  = this;

   }

   application::application(const char * pszId)
   {
      

      m_papp      = this;
      m_pappThis  = this;

      construct(pszId);

   }

   void application::construct(const char *pszId)
   {
      //if(m_strAppName.has_char())
      //   return;
      //m_strAppName.Empty();
      //m_strId.Empty();
      if(pszId == NULL)
      {
#ifdef WINDOWSEX
         wstring wstr = ::GetCommandLineW();
         string str = gen::international::unicode_to_utf8(wstr);
         strsize iFind = str.find(" : ");
         if(iFind >= 0)
         {
            iFind = str.find("app=", iFind);
            if(iFind >= 0)
            {
               strsize iEnd = str.find(" ", iFind);
               if(iEnd < 0)
               {
                  m_strId = str.Mid(iFind + 4);
               }
               else
               {
                  m_strId = str.Mid(iFind + 4, iEnd - iFind - 4);
               }
               gen::str::begins_eat(m_strId, "\"");
               gen::str::ends_eat(m_strId, "\"");
            }
         }
#endif
      }
      else
      {
         m_strId = pszId;
      }
      if(m_strId.is_empty())
         m_strId = "mplite";
      construct();
      if(m_strAppName.is_empty())
      {
         if(m_strAppId.has_char())
            m_strAppName = m_strAppId;
         else if(m_strInstallToken.has_char())
            m_strAppName = m_strInstallToken;
      }
   }

   application::~application()
   {
   }

   ::ca::application * application::get_system()
   {
      return new application();
   }

   void application::construct()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
   }


   bool application::initialize_instance()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return planebase::application::initialize_instance();
   }

   int32_t application::exit_instance()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return planebase::application::exit_instance();
   }

   void application::_001OnFileNew()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      planebase::application::_001OnFileNew(NULL);
   }


   bool application::bergedge_start()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return planebase::application::bergedge_start();
   }

   bool application::on_install()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return planebase::application::on_install();
   }

   bool application::on_uninstall()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return planebase::application::on_uninstall();
   }


   void application::on_request(::ca::create_context * pcreatecontext)
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return planebase::application::on_request(pcreatecontext);


   }

   bool application::is_serviceable()
   {


      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return planebase::application::is_serviceable();
   }

   service_base * application::allocate_new_service()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return planebase::application::allocate_new_service();
   }


   ::user::document_interface * application::_001OpenDocumentFile(var varFile)
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return ::planebase::application::_001OpenDocumentFile(varFile);

   }


   int32_t application::run()
   {

      return ::planebase::application::run();

   }


   void application::on_user_login(::fontopus::user * puser)
   {


#ifndef METROWIN

      if(!System.directrix().m_varTopicQuery.has_property("install")
      && !System.directrix().m_varTopicQuery.has_property("uninstall"))
      {

         ::ca::create_context_sp spcreatecontext(get_app());

         ::ca::application * papp = Session.start_application("application", "app-core/deepfish", spcreatecontext);

         if(papp == NULL)
         {
            simple_message_box(NULL, "deepfish subsystem - responsible for running background applications - could not be started");
         }

      }

#endif

   }


   ::planebase::application * application::assert_running(const char * pszAppId)
   {

      
      ::planebase::application * papp = NULL;


      try
      {
         
         bool bFound = false;

         for(int32_t i  = 0; i < System.m_appptra.get_count(); i++)
         {
            try
            {

               papp = dynamic_cast < ::planebase::application * > (System.m_appptra[i]);

               if(papp->m_strAppName == pszAppId)
               {
                  bFound = true;
                  break;
               }

            }
            catch(...)
            {
            }

         }

         bool bCreate = !bFound;

         if(bFound)
         {

            bool bRunning = false;

            try
            {
               if(papp->is_running())
               {
                  bRunning = true;
               }
            }
            catch(...)
            {
            }

            if(!bRunning)
            {
               
               try
               {
                  papp->post_thread_message(WM_QUIT, 0, 0);
               }
               catch(...)
               {
               }
               try
               {
                  delete papp;
               }
               catch(...)
               {
               }

               bCreate = true;

            }

            
         }

         if(bCreate)
         {

            ::ca::create_context_sp spcreatecontext(get_app());

            papp = Session.start_application("application", pszAppId, spcreatecontext);

         }

      }
      catch(::exit_exception & e)
      {
            
         throw e;

      }
      catch(::ca::exception & e)
      {
            
         if(!Application.on_run_exception(e))
            throw exit_exception(get_app());

      }
      catch(...)
      {

         papp = NULL;

      }


      return papp;

   }


} //namespace plane





