#include "framework.h"


namespace install
{


   installer_launcher::installer_launcher(::aura::application * papp, const char * pszConfiguration) :
      ::object(papp)
   {

      m_strConfiguration = pszConfiguration;

   }


   bool installer_launcher::ensure_executable()
   {

      m_strPath = System.install().app_install_get_extern_executable_path(m_strConfiguration);

      return true;

   }


   string installer_launcher::get_executable_path()
   {

      ensure_executable();

      return m_strPath;

   }


} // namespace install



