#include "framework.h"

namespace plugin
{

   run_start_installer::run_start_installer(sp(::axis::application) papp, plugin * pplugin) :
      m_pplugin(pplugin)
   {
      UNREFERENCED_PARAMETER(papp);
   }
         
   void run_start_installer::run_start_install(const char * pszStart)
   {
      m_pplugin->run_start_install(pszStart);
   }

} // namespace plugin