//#include "framework.h"
//#include "base/user/user.h"


namespace hotplugin
{


   container_launcher::container_launcher(const char * pszChannel)
   {
      
      m_strChannel = pszChannel;

   }


   string container_launcher::get_executable_path()
   {

      return ::path::app_plugin_container();

   }


   string container_launcher::get_params()
   {

      return string(": channel=") + m_strChannel;

   }


} // namespace hotplugin








