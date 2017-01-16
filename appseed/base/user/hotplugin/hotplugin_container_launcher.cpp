//#include "framework.h"
//#include "base/user/user.h"


namespace hotplugin
{


   container_launcher::container_launcher(string strPlatform, const char * pszChannel)
   {
      
      m_strChannel   = pszChannel;

      m_strPlatform  = strPlatform;

   }


   string container_launcher::get_executable_path()
   {

      return ::path::app_plugin_container(m_strPlatform);

   }


   string container_launcher::get_params()
   {

      return string(": channel=") + m_strChannel;

   }


} // namespace hotplugin








