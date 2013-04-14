#include "framework.h"



#if defined(LINUX) || defined(MACOS)
#include <dlfcn.h>
#endif



namespace plane
{


   application::application()
   {

      m_papp      = this;
      m_pappThis  = this;

      m_dir.set_app(this);
      m_file.set_app(this);
      m_http.set_app(this);

      m_bIfs            = true;



   }

/*   application::application(const char * pszId)
   {


      m_papp      = this;
      m_pappThis  = this;

      construct(pszId);

   }*/

   void application::construct(const char *pszId)
   {
      //if(m_strAppName.has_char())
      //   return;
      //m_strAppName.Empty();
      //m_strId.Empty();
      if(pszId == ::null())
      {
#ifdef WINDOWSEX
         wstring wstr = ::GetCommandLineW();
         string str = ::ca::international::unicode_to_utf8(wstr);
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
               ::ca::str::begins_eat(m_strId, "\"");
               ::ca::str::ends_eat(m_strId, "\"");
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

   sp(::ca::application) application::get_system()
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
      return ::ca::application::initialize_instance();
   }

   int32_t application::exit_instance()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return ::ca::application::exit_instance();
   }

   void application::_001OnFileNew()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      ::ca::application::_001OnFileNew(::null());
   }


   bool application::bergedge_start()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return ::ca::application::bergedge_start();
   }

   bool application::on_install()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return ::ca::application::on_install();
   }

   bool application::on_uninstall()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return ::ca::application::on_uninstall();
   }


   void application::on_request(sp(::ca::create_context) pcreatecontext)
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return ::ca::application::on_request(pcreatecontext);


   }

   bool application::is_serviceable()
   {


      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return ::ca::application::is_serviceable();
   }

   service_base * application::allocate_new_service()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return ::ca::application::allocate_new_service();
   }


   sp(::user::document_interface) application::_001OpenDocumentFile(var varFile)
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return ::ca::application::_001OpenDocumentFile(varFile);

   }


   int32_t application::run()
   {

      return ::ca::application::run();

   }




   sp(::plane::application) application::assert_running(const char * pszAppId)
   {


      sp(::plane::application) papp = ::null();


      try
      {

         bool bFound = false;

         for(int32_t i  = 0; i < System.m_appptra.get_count(); i++)
         {
            try
            {

               papp = System.m_appptra(i);

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
                  papp.release();
               }
               catch(...)
               {
               }

               bCreate = true;

            }


         }

         if(bCreate)
         {

            sp(::ca::create_context) spcreatecontext(allocer());

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

         papp = ::null();

      }


      return papp;

   }





typedef  void (* PFN_ca2_factory_exchange)(sp(::ca::application) papp);




   ::ca::filesp application::friendly_get_file(var varFile, UINT nOpenFlags)
   {

      try
      {

         return m_file.get_file(varFile, nOpenFlags);

      }
      catch(::ca::file_exception & e)
      {

         string strMessage = e.get_message();

         App(this).simple_message_box(::null(), strMessage, MB_OK);

         return ::ca::null();

      }

   }


   ::fontopus::fontopus * application::create_fontopus()
   {

      return new ::ca::fontopus::fontopus();

   }


   ::user::user * application::create_user()
   {

      return new ::user::user();

   }


   ::fs::fs * application::create_fs()
   {

      return new ::ca::fs::fs();

   }


   ::html::html * application::create_html()
   {

      return new ::html::html();

   }






} //namespace plane





