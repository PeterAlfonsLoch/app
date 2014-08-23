#include "framework.h"


namespace user
{


   bool timer_item::check(single_lock & sl)
   {

      if(::get_tick_count() >= (m_uiLastSent + m_uiElapse))
      {

         bool bWindow;

         try
         {
            // simple integrity check by calling "inoffensive" function
            // if it fails, most probably the object is damaged.
            bWindow = m_pui->IsWindow() != FALSE;
            if(bWindow)
               bWindow = m_pui != NULL;
         }
         catch(...)
         {
            return false;
         }

         if(!bWindow)
            return false;

         sl.unlock();

         try
         {
            m_pui->send_message(WM_TIMER,m_uiId);
         }
         catch(...)
         {
            return false;
         }

         sl.lock();

         m_uiLastSent = ::get_tick_count();

      }

      return true;

   }


} //  namespace user























