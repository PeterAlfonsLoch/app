#pragma once


class timer_callback;

class CLASS_DECL_CORE timer_window : 
   public window
{
public:


   timer_callback * m_pTimerCallback;
   timer_callback * m_pTimerCallbackFinal;
   event           m_evFree;
   bool            m_bEnable;


   timer_window();
   virtual ~timer_window();


   virtual bool DestroyWindow();

   bool IsEnabled();
   bool EnableTimer(bool bEnable = true);
   bool create(timer_callback * pCallback);

   void OnTimer(UINT nIDEvent);
   void OnDestroy();
   void OnClose();
   LRESULT OnUserMessage(WPARAM wparam, LPARAM lparam);
};

