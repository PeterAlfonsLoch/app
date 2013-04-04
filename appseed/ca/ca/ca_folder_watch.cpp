#include "framework.h"

namespace ca
{

   void folder_watch::callback::on_file_action(e_action eaction, const char * pszFolder, const char * psz)
   {
      UNREFERENCED_PARAMETER(eaction);
      UNREFERENCED_PARAMETER(pszFolder);
      UNREFERENCED_PARAMETER(psz);
   }
   

   bool folder_watch::watch(const char * pszPath)
   {
      m_strPath = pszPath;
      return true;
   }

   void folder_watch::on_file_action(e_action eaction, const char * psz)
   {
      if(m_pcallback != ::null())
      {
         m_pcallback->on_file_action(eaction, m_strPath, psz);
      }
   }
      
} // namespace ca