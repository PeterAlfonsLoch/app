#include "framework.h"


namespace cube
{


   application::application()
   {
   }

   application::application(const char * pszId)
   {
      construct(pszId);
   }

   void application::construct(const char *pszId)
   {
      if(m_strAppName.has_char())
         return;
      m_strAppName.Empty();
      m_strId.Empty();
      if(pszId == NULL)
      {
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
         if(m_strLicense.has_char())
            m_strAppName = m_strLicense;
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
      if(chFirst == 'd')
      {
         if(strId == "default_file_handler")
         {
            return ::filehandler::application::construct();
         }
      }
      else if(chFirst == 'f')
      {
         if(strId == "fontopus2")
         {
            return ::ca2::fontopus::application::construct();
         }
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
      if(chFirst == 'd')
      {
         if(strId == "default_file_handler")
         {
            return ::filehandler::application::initialize_instance();
         }
      }
      else if(chFirst == 'f')
      {
         if(strId == "fontopus2")
         {
            return ::ca2::fontopus::application::initialize_instance();
         }
      }
      return cubebase::application::initialize_instance();
   }

   int application::exit_instance()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      if(chFirst == 'd')
      {
         if(strId == "default_file_handler")
         {
            return ::filehandler::application::exit_instance();
         }
      }
      else if(chFirst == 'f')
      {
         if(strId == "fontopus2")
         {
            return ::ca2::fontopus::application::exit_instance();
         }
      }
      return cubebase::application::exit_instance();
   }

   void application::_001OnFileNew()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      cube2::application::_001OnFileNew();
   }


   bool application::bergedge_start()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      if(chFirst == 'd')
      {
         if(strId == "default_file_handler")
         {
            return ::filehandler::application::bergedge_start();
         }
      }
      else if(chFirst == 'f')
      {
         if(strId == "fontopus2")
         {
            return ::ca2::fontopus::application::bergedge_start();
         }
      }
      return cube2::application::bergedge_start();
   }

   bool application::on_install()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      if(chFirst == 'd')
      {
         if(strId == "default_file_handler")
         {
            return ::filehandler::application::on_install();
         }
      }
      else if(chFirst == 'f')
      {
         if(strId == "fontopus2")
         {
            return ::ca2::fontopus::application::on_install();
         }
      }
      return cubebase::application::on_install();
   }

   bool application::on_uninstall()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      if(chFirst == 'd')
      {
         if(strId == "default_file_handler")
         {
            return ::filehandler::application::on_uninstall();
         }
      }
      else if(chFirst == 'f')
      {
         if(strId == "fontopus2")
         {
            return ::ca2::fontopus::application::on_uninstall();
         }
      }
      return cubebase::application::on_uninstall();
   }


   void application::on_request(::ca::create_context * pcreatecontext)
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      if(chFirst == 'd')
      {
         if(strId == "default_file_handler")
         {
            return ::filehandler::application::on_request(pcreatecontext);
         }
      }
      else if(chFirst == 'f')
      {
         if(strId == "fontopus2")
         {
            return ::ca2::fontopus::application::on_request(pcreatecontext);
         }
      }
      return cube2::application::on_request(pcreatecontext);


   }

   bool application::is_serviceable()
   {


      string strId = m_strId;

      char chFirst = '\0';

      if(strId.get_length() > 0)
      {

         chFirst = strId[0];

      }

      if(chFirst == 'd')
      {

         if(strId == "default_file_handler")
         {

            return ::filehandler::application::is_serviceable();

         }

      }
      
      return cube2::application::is_serviceable();

   }

   service_base * application::allocate_new_service()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      if(chFirst == 'd')
      {
         if(strId == "default_file_handler")
         {
            return ::filehandler::application::allocate_new_service();
         }
      }
      
      return cube2::application::allocate_new_service();
   }


   ::user::document_interface * application::_001OpenDocumentFile(var varFile)
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      if(chFirst == 'd')
      {
         if(strId == "default_file_handler")
         {
            return ::filehandler::application::_001OpenDocumentFile(varFile);
         }
      }
      else if(chFirst == 'r')
      {
      }

      return ::cube2::application::_001OpenDocumentFile(varFile);

   }


   int application::run()
   {

      return ::cube2::application::run();

   }


} //namespace cube



