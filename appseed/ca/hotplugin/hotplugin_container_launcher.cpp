#include "framework.h"


namespace hotplugin
{


   container_launcher::container_launcher(const char * pszChannel)
   {
      
      m_strChannel = pszChannel;

   }


   vsstring container_launcher::get_executable_path()
   {

#ifdef _M_IX86

      return dir::element("stage/x86/ca2plugin-container.exe");

#else

      return dir::element("stage/x64/ca2plugin-container.exe");

#endif

   }

   vsstring container_launcher::get_params()
   {

      return vsstring(": channel=") + m_strChannel;

   }



} // namespace hotplugin




