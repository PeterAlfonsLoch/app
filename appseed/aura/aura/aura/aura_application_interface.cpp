#include "framework.h"


namespace axis
{


   application_interface::application_interface()
   {

      m_paxissystem     = NULL;
      m_paxissession    = NULL;
      m_pbasesapp       = NULL;
      m_pbasesystem     = NULL;
      m_pbasesession    = NULL;
      m_pcoreapp        = NULL;
      m_pcoresystem     = NULL;
      m_pcoreplatform   = NULL;

   }


   application_interface::~application_interface()
   {

   }


} // namespace axis




