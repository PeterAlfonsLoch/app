#include "framework.h"


namespace install
{

   installer_launcher::installer_launcher(::aura::application * papp, const char * pszVersion, const char * pszBuild) :
      ::object(papp)
   {

      m_strVersion = pszVersion;

      m_strBuild = pszBuild;

   }


   bool installer_launcher::ensure_executable()
   {

      m_strPath = System.install().app_install_get_extern_executable_path(m_strVersion, m_strBuild);

      return true;

   }

   string installer_launcher::get_executable_path()
   {
      ensure_executable();
      return m_strPath;
   }


} // namespace install



