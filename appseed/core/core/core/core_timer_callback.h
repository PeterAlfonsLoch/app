#pragma once


namespace core
{


   class timer;

   class CLASS_DECL_CORE timer_callback
   {
   protected:


      timer     *    m_ptimer;
      bool              m_bQueueModel;
      // This flag must be set when the timer Callback object
      // wishes and is prepared for over
      // clocked synchronized timer messages and a lot of
      // overloaded processor generated assynchronous
      // delayed messages.

      bool              m_bTimerCallbackEnable;

      //event           m_evTimerWndDeleted;

   public:


      timer_callback();
      virtual ~timer_callback();


      bool IsEnabled();
      void Enable(bool bEnable = true);
      virtual void TimerProc(uint_ptr nID) = 0;
      bool WishesQueueModel();
      bool set_timer(timer * ptimerwnd);


   };


} // namespace core




