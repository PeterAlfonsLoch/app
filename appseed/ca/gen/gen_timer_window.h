#pragma once

namespace gen
{

   /////////////////////////////////////////////////////////////////////////////
   // TimerWnd ::ca::window
   class TimerCallback;

   class CLASS_DECL_ca TimerWnd : public ::ca::window
   {
   // Construction
   public:
      TimerWnd();

   // Attributes
   public:
       TimerCallback * m_pTimerCallback;
       TimerCallback * m_pTimerCallbackFinal;
       event           m_evFree;
   protected:
      bool            m_bEnable;
   //    bool             m_bSkipConcurrency;
   //    mutex          m_mutexSkipConcurrency;
   // Operations
   public:

   // Overrides
      // ClassWizard generated virtual function overrides
      //{{__VIRTUAL(TimerWnd)
      public:
      virtual bool DestroyWindow();
      //}}__VIRTUAL

   // Implementation
   public:
      bool IsEnabled();
      bool EnableTimer(bool bEnable = true);
      bool create(TimerCallback * pCallback);
      virtual ~TimerWnd();

      void OnTimer(UINT nIDEvent);
      void OnDestroy();
      void OnClose();
      LRESULT OnUserMessage(WPARAM wparam, LPARAM lparam);
   };

} // namespace gen

