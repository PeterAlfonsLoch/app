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
       CEvent           m_evFree;
   protected:
      bool            m_bEnable;
   //    bool             m_bSkipConcurrency;
   //    mutex          m_mutexSkipConcurrency;
   // Operations
   public:

   // Overrides
      // ClassWizard generated virtual function overrides
      //{{AFX_VIRTUAL(TimerWnd)
      public:
      virtual BOOL DestroyWindow();
      //}}AFX_VIRTUAL

   // Implementation
   public:
      bool IsEnabled();
      bool EnableTimer(bool bEnable = true);
      BOOL create(TimerCallback * pCallback);
      virtual ~TimerWnd();

      afx_msg void OnTimer(UINT nIDEvent);
      afx_msg void OnDestroy();
      afx_msg void OnClose();
      afx_msg LRESULT OnUserMessage(WPARAM wparam, LPARAM lparam);
   };

} // namespace gen

