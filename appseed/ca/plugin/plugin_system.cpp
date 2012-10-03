#include "framework.h"


namespace plugin
{


   system::system(::ca::application * papp) :
      ::plane::system(papp)
   {

      m_bShouldInitializeGTwf    = false;

      m_bRun = true;

   }


   bool system::os_native_bergedge_start()
   {

      return m_pplugin->os_native_bergedge_start();

   }


   bool system::open_link(const char * pszLink, const char * pszTarget)
   {

      UNREFERENCED_PARAMETER(pszTarget);

      m_pplugin->m_puiHost->PostMessage(host_interaction::message_check, 2, (LPARAM) (void *) (new vsstring(pszLink)));

      return true;

   }


   bool system::verb()
   {

      return ::plane::application::verb();

   }


   string system::get_host_location_url()
   {
      
      return (const char *) m_pplugin->get_host_location_url();

   }


} // namespace plugin




