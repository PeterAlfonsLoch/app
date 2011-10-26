#include "StdAfx.h"

namespace verifile
{


   application::application()
   {
   }


   void application::construct()
   {
      m_strAppName         = "verifile";
      m_strBaseSupportId   = "votagus_ca2_filemanager";
      m_strInstallToken    = "_set_filemanager";
   }


   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
      if(!cube2::application::initialize_instance())
         return false;

      return true;
   }
    
   void application::on_request(::ca::create_context * pcreatecontext)
   {
      
      if(GetStdFileManagerTemplate()->m_pdoctemplateMain->get_document_count() <= 0)
      {
         GetStdFileManagerTemplate()->open(this, pcreatecontext);
      }

      if(!pcreatecontext->m_spCommandLine->m_varFile.is_empty())
      {
         Bergedge.open_by_file_extension(pcreatecontext->m_spCommandLine->m_varFile);
      }
      
   }


   BOOL application::exit_instance()
   {
      return TRUE;
   }

   bool application::on_install()
   {
      string strCommand = m_strModulePath;
      strCommand = System.url().url_encode(strCommand);
      DWORD dwSessId;

      HANDLE hProcess = ::GetCurrentProcess();
      DWORD dwId = ::GetProcessId(hProcess);

      ProcessIdToSessionId(dwId, &dwSessId);
      xml::node * pnode = new xml::node(get_app());
      pnode->m_strName = "run";
      pnode->add_attr("sessionid", dwSessId);
      pnode->add_attr("command", strCommand);
      System.machine_event_central().command(pnode);
      return true;
   }

   void application::OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      if(itema.get_count() > 0)
      {
         string strPath = itema[0].m_strPath;
         System.open_by_file_extension(0, strPath); // true, false);
      }
   }

} // namespace filemanager

