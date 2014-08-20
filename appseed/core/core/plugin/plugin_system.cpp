#include "framework.h"


namespace plugin
{


   system::system(sp(::axis::application) papp) :
      element(papp),
      ::axis::system(papp),
      ::base::system(papp),
      ::core::system(papp)
   {

         if (papp.is_set())
         {
            m_paxisapp = papp;
         }
         
      
      if (m_pbasesession == NULL)
      {
         
            m_pbasesession = m_paxisapp->m_pbasesession;

      }

      m_bShouldInitializeGTwf    = false;

      m_bRun = true;

   }


   bool system::os_native_bergedge_start()
   {

      return m_pplugin->os_native_bergedge_start();

   }


   bool system::open_link(const string & pszLink, const string & pszTarget)
   {

      UNREFERENCED_PARAMETER(pszTarget);

      m_pplugin->m_puiHost->post_message(host_interaction::message_check, 2, (LPARAM) (void *) (new string(pszLink)));

      return true;

   }


   bool system::verb()
   {

      return ::core::application::verb();

   }


   string system::get_host_location_url()
   {
      
      return (const string &) m_pplugin->get_host_location_url();

   }


} // namespace plugin




