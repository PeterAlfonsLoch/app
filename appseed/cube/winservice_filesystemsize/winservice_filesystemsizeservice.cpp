#include "StdAfx.h"
#include <ShlObj.h>
#include <math.h>

namespace winservice_filesystemsize
{

/*service::service(::ca::application * papp) :
   ca(papp),
   m_stopping(false), 
   service_base(papp)
{
}

service::~service()
{
}

void service::Start(DWORD)
    {

       thread_pool::QueueUserWorkItem(&service::ServiceThread, 
                                            this);
    }

void service::Stop(DWORD)
{
   m_stopping = true;
   m_stopped.Wait();
}


void service::ServiceThread()
{
   m_stopping = false;


   /*db_server * pcentral = &System.db();
   pcentral->m_pfilesystemsizeset->m_table.m_hwnd = 
      ::CreateFileMapping(
         (HANDLE)0xFFFFFFFF,NULL,PAGE_READWRITE,0,
         sizeof(file_size_table::get_fs_size),
         "Global\\ca2_fontopus::file_size_table::shared_memory::7807e510-5579-11dd-ae16-0800200c7784");
   
   if(GetLastError() == ERROR_ALREADY_EXISTS)
      goto exit;

   pcentral->m_pfilesystemsizeset->m_table.m_pgetfssize = (file_size_table::get_fs_size *) 
      ::MapViewOfFile(
         pcentral->m_pfilesystemsizeset->m_table.m_hmap,
         FILE_MAP_WRITE,0,0,sizeof(file_size_table::get_fs_size));*/

   /*while(!m_stopping)
   {
      if (pcentral->m_pfilesystemsizeset->m_table.m_pevExec->Lock())
      {
         pcentral->m_pfilesystemsizeset->m_table.m_pgetfssize->m_bRet = 
         pcentral->m_pfilesystemsizeset->get_fs_size(
            pcentral->m_pfilesystemsizeset->m_table.m_pgetfssize->m_iSize,
            pcentral->m_pfilesystemsizeset->m_table.m_pgetfssize->m_szPath,
            pcentral->m_pfilesystemsizeset->m_table.m_pgetfssize->m_bPending);
         // Inform client that server is done
         pcentral->m_pfilesystemsizeset->m_table.m_pevDone->SetEvent();
      }
   }*/
  /* while(!m_stopping)
   {
      AfxPumpMessage();
   }
exit:
   m_stopped.Signal();
}





string service::stage()
{
   char path[MAX_PATH * 4];
   if(!SHGetSpecialFolderPath(
      NULL,
      path,
      CSIDL_PROGRAM_FILES | CSIDL_FLAG_CREATE,
      1))
      return "";
   else 
      return path;
}

*/


} // namespace winservice_filesystemsize