#include "framework.h"


namespace axis
{


   session_interface::session_interface()
   {

      m_pplatformcomposite = NULL;

   }


   session_interface::~session_interface()
   {

   }


   ::count session_interface::get_monitor_count()
   {

      return m_pbasesession->get_monitor_count();

   }


   bool session_interface::get_monitor_rect(index iMonitor,LPRECT lprect)
   {

      return m_pbasesession->get_monitor_rect(iMonitor,lprect);

   }

   

} // namespace axis
















