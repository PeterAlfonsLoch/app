#include "framework.h"


simple_shell_launcher::simple_shell_launcher(HWND hwnd, const char * pszOperation, const char * pszFile, const char * pszParameters, const char * pszDirectory, int iShow)
{

   m_hwnd               = hwnd;
   m_vssOperation       = pszOperation;
   m_vssFile            = pszFile;
   m_vssParameters      = pszParameters;
   m_vssDirectory       = pszDirectory;
   m_iShow              = iShow;

}
