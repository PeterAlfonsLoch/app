#include "StdAfx.h"


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
         int iFind = str.find(" : ");
         if(iFind >= 0)
         {
            iFind = str.find("app=", iFind);
            if(iFind >= 0)
            {
               int iEnd = str.find(" ", iFind);
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

   ::ax::application * application::get_system()
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
            return ::ca2::filehandler::application::construct();
         }
      }
      else if(chFirst == 'f')
      {
         if(strId == "fontopus")
         {
            return fontopus::application::construct();
         }
      }
      else if(chFirst == 'n')
      {
         if(m_strId == "netnode")
         {
            return netnode::application::construct();
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
            return ::ca2::filehandler::application::initialize_instance();
         }
      }
      else if(chFirst == 'f')
      {
         if(strId == "fontopus")
         {
            return fontopus::application::initialize_instance();
         }
      }
      else if(chFirst == 'n')
      {
         if(m_strId == "netnode")
         {
            return netnode::application::initialize_instance();
         }
      }
      return acube::application::initialize_instance();
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
            return ::ca2::filehandler::application::exit_instance();
         }
      }
      else if(chFirst == 'f')
      {
         if(strId == "fontopus")
         {
            return fontopus::application::exit_instance();
         }
      }
      else if(chFirst == 'n')
      {
         if(m_strId == "netnode")
         {
            return netnode::application::exit_instance();
         }
      }
      else if(chFirst == 'r')
      {
      }
      return acube::application::exit_instance();
   }

   void application::_001OnFileNew()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      cube4::application::_001OnFileNew();
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
            return ::ca2::filehandler::application::bergedge_start();
         }
      }
      else if(chFirst == 'f')
      {
         if(strId == "i2com")
         {
            return fontopus::application::bergedge_start();
         }
      }
      else if(chFirst == 'n')
      {
         if(strId == "netnode")
         {
            return netnode::application::bergedge_start();
         }
      }
      else if(chFirst == 'r')
      {
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
            return ::ca2::filehandler::application::on_install();
         }
      }
      else if(chFirst == 'n')
      {
         if(strId == "netnode")
         {
            return netnode::application::on_install();
         }
      }
      return acube::application::on_install();
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
            return ::ca2::filehandler::application::on_uninstall();
         }
      }
      else if(chFirst == 'n')
      {
         if(strId == "netnode")
         {
            return netnode::application::on_uninstall();
         }
      }
      return acube::application::on_uninstall();
   }


   void application::on_request(::ax::create_context * pcreatecontext)
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
            return ::ca2::filehandler::application::on_request(pcreatecontext);
         }
      }
      else if(m_strId == "netnode")
      {
         return netnode::application::on_request(pcreatecontext);
      }
      else if(chFirst == 'r')
      {
      }
      return cube4::application::on_request(pcreatecontext);
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
            return ::ca2::filehandler::application::is_serviceable();
         }
      }
      else if(m_strId == "netnode")
      {
         return netnode::application::is_serviceable();
      }
      else if(chFirst == 'r')
      {
      }
      
      return cube4::application::is_serviceable();
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
            return ::ca2::filehandler::application::allocate_new_service();
         }
      }
      else if(m_strId == "netnode")
      {
         return netnode::application::allocate_new_service();
      }
      else if(chFirst == 'r')
      {
      }
      
      return cube4::application::allocate_new_service();
   }


   ::document * application::_001OpenDocumentFile(var varFile)
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
            return ::ca2::filehandler::application::_001OpenDocumentFile(varFile);
         }
      }
      else if(chFirst == 'r')
      {
      }
      return ::cube4::application::_001OpenDocumentFile(varFile);
   }


   BOOL application::run()
   {
      return ::cube4::application::run();
   }

   CLASS_DECL_ca application & app_cast(::ax::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }



} //namespace cube



