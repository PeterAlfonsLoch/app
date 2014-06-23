#include "framework.h"


namespace core
{


   timer::timer()
   {

      EnableTimer();

   }

   timer::~timer()
   {

   }


   void timer::install_message_handling(::message::dispatch * pdispatch)
   {

      ::user::interaction::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_CREATE,pdispatch,this,&timer::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_DESTROY,pdispatch,this,&timer::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_CLOSE,pdispatch,this,&timer::_001OnClose);
      IGUI_WIN_MSG_LINK(WM_USER,pdispatch,this,&timer::_001OnUser);

   }


   bool timer::create(timer_callback * pcallback)
   {

      m_pcallback = pcallback;

      return create_message_queue("timer_window");

   }


   void timer::_001OnTimer(signal_details * pobj)
   {

      SCAST_PTR(::message::timer,ptimer,pobj);


      if(m_bEnable && m_pcallback != NULL)
      {

         if(m_pcallback->IsEnabled())
         {

            if(m_pcallback->WishesQueueModel())
            {

               post_message(WM_USER,ptimer->m_nIDEvent);

            }
            else
            {

               try
               {
                  m_pcallback->TimerProc(ptimer->m_nIDEvent);

               }
               catch(...)
               {

               }

            }

         }

      }

   }


   void timer::_001OnDestroy(signal_details * pobj)
   {

      m_pcallback = NULL;

   }


   void timer::_001OnClose(signal_details * pobj)
   {

      DestroyWindow();

   }


   bool timer::DestroyWindow()
   {

      ::user::interaction::DestroyWindow();
         
      delete this;

      return true;

   }


   bool timer::EnableTimer(bool bEnable)
   {
   
      bool b = m_bEnable;

      m_bEnable = bEnable;

      return b;

   }


   bool timer::IsEnabled()
   {

      return m_bEnable;

   }

   // Purpose:
   // Handle Queue Model Message Posts
   //
   void timer::_001OnUser(signal_details * pobj)
   {
      
      SCAST_PTR(::message::base,pbase,pobj);

      // processor saving remark but should not be a remark
      // ASSERT(m_pTimerCallback->WishesQueueModel());
      // END processor saving remark but should not be a remark

      try
      {

         m_pcallback->TimerProc(pbase->m_wparam); // ASSERT(wparam == nIDEvent)

      }
      catch(...)
      {

      }

      pbase->set_lresult(0);

   }


} // namespace core














