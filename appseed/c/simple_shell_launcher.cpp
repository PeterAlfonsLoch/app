#include "framework.h"
#include <Shellapi.h>


simple_shell_launcher::simple_shell_launcher()
{

   m_iMode              = 1;

}


simple_shell_launcher::simple_shell_launcher(HWND hwnd, const char * pszOperation, const char * pszFile, const char * pszParameters, const char * pszDirectory, int iShow)
{

   m_iMode              = 0;
   m_hwnd               = hwnd;
   m_vssOperation       = pszOperation;
   m_vssFile            = pszFile;
   m_vssParameters      = pszParameters;
   m_vssDirectory       = pszDirectory;
   m_iShow              = iShow;

}


#ifdef LINUX


void simple_shell_launcher::execute()
{

   if(m_iMode == 0)
   {

      if(m_vssOperation.is_empty())
      {
         call_sync(m_vssFile, m_vssParameters, m_vssDirectory, m_iShow, -1, 284, NULL, 0);
      }
      else if(stricmp(m_vssOperation, "open") == 0
      {
         call_sync("gnome-open", m_vssFile, m_vssDirectory, m_iShow, -1, 284, NULL, 0);
      }

   }
      
}


#endif




