#include "framework.h"


namespace hotplugin
{


   container_launcher::container_launcher(const char * pszChannel)
   {
      
      m_strChannel = pszChannel;

   }


   string container_launcher::get_executable_path()
   {

#ifdef _M_IX86

      return dir::element("stage/x86/app.plugin.container.exe");

#else

      return dir::element("stage/x64/app.plugin.container.exe");

#endif

   }

   string container_launcher::get_params()
   {

      return string(": channel=") + m_strChannel;

   }



} // namespace hotplugin




