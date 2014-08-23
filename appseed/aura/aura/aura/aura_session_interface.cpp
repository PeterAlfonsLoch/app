#include "framework.h"


namespace aura
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

      return m_paxissession->get_monitor_count();

   }


   bool session_interface::get_monitor_rect(index iMonitor,LPRECT lprect)
   {

      return m_paxissession->get_monitor_rect(iMonitor,lprect);

   }

   
   ::visual::cursor * session_interface::get_cursor()
   {

      if(m_pplatformcomposite == NULL)
         return NULL;
      
      return m_pplatformcomposite->get_cursor();

   }


   ::visual::cursor * session_interface::get_default_cursor()
   {

      if(m_pplatformcomposite == NULL)
         return NULL;

      return m_pplatformcomposite->get_default_cursor();

   }



} // namespace aura
















