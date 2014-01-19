#include "framework.h"


#ifndef METROWIN

simple_shell_launcher::simple_shell_launcher()
{

   m_iMode              = 1;

}


simple_shell_launcher::simple_shell_launcher(oswindow oswindow, const char * pszOperation, const char * pszFile, const char * pszParameters, const char * pszDirectory, int32_t iShow)
{

   m_iMode              = 0;
   m_oswindow               = oswindow;
   m_vssOperation       = pszOperation;
   m_vssFile            = pszFile;
   m_vssParameters      = pszParameters;
   m_vssDirectory       = pszDirectory;
   m_iShow              = iShow;

}


#endif




