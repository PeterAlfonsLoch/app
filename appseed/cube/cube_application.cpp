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
      if(chFirst == 'b')
      {
         if(strId == "biteditor")
         {
            return biteditor_application::construct();
         }
      }
      else if(chFirst == 'd')
      {
         if(strId == "devedge")
         {
            return devedge::application::construct();
         }
      }
      else if(chFirst == 'f')
      {
         if(strId == "fontopus")
         {
            return fontopus::application::construct();
         }
      }
      else if(chFirst == 'r')
      {
         if(m_strId == "rtprx")
         {
            return rtprx::application::construct();
         }
         else if(m_strId == "rtptx")
         {
            return rtptx::application::construct();
         }
      }
      else if(chFirst == 'n')
      {
         if(m_strId == "netnode")
         {
            return netnode::application::construct();
         }
         else if(strId == "netnodecfg")
         {
            return netnodecfg::application::construct();
         }
      }
      else if(m_strId == "eluce")
      {
         return eluce::application::construct();
      }
      else if(m_strId == "mplite")
      {
         return mplite::application::construct();
      }
      else if(m_strId == "status")
      {
         return status::application::construct();
      }
      else if(m_strId == "i2com")
      {
         return i2com::application::construct();
      }
      else if(chFirst == 'v')
      {
         if(m_strId == "veriedit")
         {
            return veriedit::application::construct();
         }
         else if(m_strId == "verifile")
         {
            return verifile::application::construct();
         }
         else if(m_strId == "verisimplevideo")
         {
            return verisimplevideo::application::construct();
         }
         else if(m_strId == "syllomatter")
         {
            return syllomatter::application::construct();
         }
         else if(strId == "veriview")
         {
            return veriview::application::construct();
         }
         else if(strId == "vmp")
         {
            return vmsp::application::construct();
         }
      }
      else if(chFirst == 'w')
      {
         if(m_strId == "whiteboard")
         {
            return whiteboard::application::construct();
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
      if(chFirst == 'b')
      {
         if(strId == "biteditor")
         {
            return biteditor_application::initialize_instance();
         }
      }
      else if(chFirst == 'd')
      {
         if(strId == "devedge")
         {
            return devedge::application::initialize_instance();
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
         else if(m_strId == "netnodecfg")
         {
            return netnodecfg::application::initialize_instance();
         }
      }
      else if(chFirst == 'r')
      {
         if(m_strId == "rtprx")
         {
            return rtprx::application::initialize_instance();
         }
         else if(m_strId == "rtptx")
         {
            return rtptx::application::initialize_instance();
         }
      }
      else if(m_strId == "eluce")
      {
         return eluce::application::initialize_instance();
      }
      else if(m_strId == "mplite")
      {
         return mplite::application::initialize_instance();
      }
      else if(m_strId == "status")
      {
         return status::application::initialize_instance();
      }
      else if(m_strId == "i2com")
      {
         return i2com::application::initialize_instance();
      }
      else if(chFirst == 'v')
      {
         if(m_strId == "veriedit")
         {
            return veriedit::application::initialize_instance();
         }
         else if(m_strId == "verifile")
         {
            return verifile::application::initialize_instance();
         }
         else if(m_strId == "verisimplevideo")
         {
            return verisimplevideo::application::initialize_instance();
         }
         else if(m_strId == "syllomatter")
         {
            return syllomatter::application::initialize_instance();
         }
         else if(m_strId == "veriview")
         {
            return veriview::application::initialize_instance();
         }
         else if(m_strId == "vmp")
         {
            return vmsp::application::initialize_instance();
         }
      }
      else if(chFirst == 'w')
      {
         if(m_strId == "whiteboard")
         {
            return whiteboard::application::initialize_instance();
         }
      }
      return acube::application::initialize_instance();
   }

   void application::_001OnFileNew()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      if(chFirst == 'd')
      {
         if(strId == "devedge")
         {
            return devedge::application::_001OnFileNew();
         }
      }
      else if(chFirst == 'v')
      {
         if(strId == "veriedit")
         {
            return veriedit::application::_001OnFileNew();
         }
         else if(strId == "verisimplevideo")
         {
            return verisimplevideo::application::_001OnFileNew();
         }
         else if(strId == "veriview")
         {
            return veriview::application::_001OnFileNew();
         }
         else if(strId == "vmp")
         {
            return vmsp::application::_001OnFileNew();
         }
      }
      else if(m_strId == "mplite")
      {
         return mplite::application::_001OnFileNew();
      }
      else if(m_strId == "i2com")
      {
         //i2com::application::_001OnFileNew();
      }
      else if(chFirst == 'w')
      {
         if(m_strId == "whiteboard")
         {
            whiteboard::application::_001OnFileNew();
         }
      }
      else
      {
      }
      ca84::application::_001OnFileNew();
   }


   bool application::bergedge_start()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      if(chFirst == 'b')
      {
         if(strId == "biteditor")
         {
            return biteditor_application::bergedge_start();
         }
      }
      else if(chFirst == 'f')
      {
         if(strId == "i2com")
         {
            return fontopus::application::bergedge_start();
         }
      }
      else if(chFirst == 'i')
      {
         if(strId == "i2com")
         {
            return i2com::application::bergedge_start();
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
         if(strId == "rtprx")
         {
            return rtprx::application::bergedge_start();
         }
         else if(strId == "rtptx")
         {
            return rtptx::application::bergedge_start();
         }
      }
      else if(chFirst == 's')
      {
         if(strId == "status")
         {
            return status::application::bergedge_start();
         }
      }
      else if(chFirst == 'v')
      {
         if(m_strId == "verifile")
         {
            return verifile::application::bergedge_start();
         }
         else if(m_strId == "verisimplevideo")
         {
            return verisimplevideo::application::bergedge_start();
         }
         else if(m_strId == "syllomatter")
         {
            return syllomatter::application::bergedge_start();
         }
         else if(m_strId == "veriview")
         {
            return veriview::application::bergedge_start();
         }
         else if(m_strId == "vmp")
         {
            return vmsp::application::bergedge_start();
         }
      }
      else if(chFirst == 'w')
      {
         if(m_strId == "whiteboard")
         {
            return whiteboard::application::bergedge_start();
         }
      }
      return ca84::application::bergedge_start();
   }

   bool application::on_install()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      if(chFirst == 'b')
      {
      }
      else if(chFirst == 'd')
      {
         if(strId == "devedge")
         {
            return devedge::application::on_install();
         }
      }
      else if(chFirst == 'm')
      {
         if(strId == "mplite")
         {
            return mplite::application::on_install();
         }
      }
      else if(chFirst == 'v')
      {
         if(strId == "vmp")
         {
            return vmsp::application::on_install();
         }
         else if(strId == "verisimplevideo")
         {
            return verisimplevideo::application::on_install();
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

   void application::on_request(var & varFile, var & varQuery)
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      if(chFirst == 'b')
      {
         if(strId == "biteditor")
         {
            return biteditor_application::on_request(varFile, varQuery);
         }
      }
      else if(chFirst == 'd')
      {
         if(strId == "devedge")
         {
            return devedge::application::on_request(varFile, varQuery);
         }
      }
      else if(chFirst == 'v')
      {
         if(strId == "veriedit")
         {
            return veriedit::application::on_request(varFile, varQuery);
         }
         else if(strId == "verifile")
         {
            return verifile::application::on_request(varFile, varQuery);
         }
         else if(strId == "verisimplevideo")
         {
            return verisimplevideo::application::on_request(varFile, varQuery);
         }
         else if(strId == "vmp")
         {
            return vmsp::application::on_request(varFile, varQuery);
         }
      }
      else if(m_strId == "eluce")
      {
         return eluce::application::on_request(varFile, varQuery);
      }
      else if(m_strId == "mplite")
      {
         return mplite::application::on_request(varFile, varQuery);
      }
      else if(m_strId == "netnode")
      {
         return netnode::application::on_request(varFile, varQuery);
      }
   }

   ::document * application::_001OpenDocumentFile(var varFile)
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      if(chFirst == 'm')
      {
         if(strId == "mplite")
         {
            return mplite::application::_001OpenDocumentFile(varFile);
         }
      }
      else if(chFirst == 'r')
      {
         if(strId == "rtprx")
         {
            return rtprx::application::_001OpenDocumentFile(varFile);
         }
      }
      else if(chFirst == 'v')
      {
         if(strId == "veriedit")
         {
            return veriedit::application::_001OpenDocumentFile(varFile);
         }
         else if(strId == "vmp")
         {
            return vmsp::application::_001OpenDocumentFile(varFile);
         }
         else if(strId == "verisimplevideo")
         {
            return verisimplevideo::application::_001OpenDocumentFile(varFile);
         }
      }
      return ::icube::application::_001OpenDocumentFile(varFile);
   }


   BOOL application::run()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      if(chFirst == 'b')
      {
      }
      return ::veriview::application::run();
   }

   CLASS_DECL_CA2_CUBE application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

} //namespace cube



CLASS_DECL_CA2_CUBE ::ca::application * get_new_app()
{
   return new ::cube::application();
}
