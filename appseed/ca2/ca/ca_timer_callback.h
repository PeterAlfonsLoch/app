// TimerCallback.h: interface for the TimerCallback class.
//
//////////////////////////////////////////////////////////////////////


#pragma once


namespace ca
{


   class TimerWnd;

   class CLASS_DECL_ca TimerCallback
   {
   protected:


      TimerWnd     *    m_ptimerwnd;
      bool              m_bQueueModel;
         // This flag must be set when the Timer Callback object
         // wishes and is prepared for over
         // clocked synchronized timer messages and a lot of
         // overloaded processor generated assynchronous
         // delayed messages.

      bool              m_bTimerCallbackEnable;

      //event           m_evTimerWndDeleted;
      
   public:


      TimerCallback();
      virtual ~TimerCallback();

      
      bool IsEnabled();
      void Enable(bool bEnable = true);
      virtual void TimerProc(uint_ptr nID) = 0;
      bool WishesQueueModel();
      bool SetTimerWindow(TimerWnd * ptimerwnd);
      

   };


} // namespace ca


