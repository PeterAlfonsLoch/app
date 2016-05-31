//#include "framework.h" // previously ace/user/user.h


namespace ace
{


   timer_item::timer_item(::ace::application * papp):
      object(papp)
   {

   }


   timer_item::~timer_item()
   {

   }


   bool timer_item::check(single_lock & sl)
   {

      if(::get_tick_count() >= (m_uiLastSent + m_uiElapse))
      {

         bool bWindow;

         try
         {
            // simple integrity check by calling "inoffensive" function
            // if it fails, most probably the object is damaged.
            bWindow = m_paceapp->is_window(m_pui) != FALSE;
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
            Application.send_message(m_pui,WM_TIMER,m_uiId);
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























