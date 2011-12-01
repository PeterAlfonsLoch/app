// TimerCallback.h: interface for the TimerCallback class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMERCALLBACK_H__EB76FCF2_95E1_4FA9_8B2F_845DE7F293D1__INCLUDED_)
#define AFX_TIMERCALLBACK_H__EB76FCF2_95E1_4FA9_8B2F_845DE7F293D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


namespace gen
{

class TimerWnd;

class CLASS_DECL_ca TimerCallback
{
   // Attributes
protected:
   TimerWnd     * m_ptimerwnd;
   bool            m_bQueueModel;
      // This flag must be set when the Timer Callback object
      // wishes and is prepared for over
      // clocked synchronized timer messages and a lot of
      // overloaded processor generated assynchronous
      // delayed messages.

   // Construction / Destruction
public:
   TimerCallback();
   virtual ~TimerCallback();

   // Attributes
public:
   bool IsEnabled();
   void Enable(bool bEnable = true);
   virtual void TimerProc(UINT nID) = 0;
public:
   bool WishesQueueModel();
//   bool _000BeforeWndProc(UINT message, WPARAM wparam, LPARAM lparam, LRESULT & lresult);
//   bool InstallTimerCallbackHook();
   bool SetTimerWindow(TimerWnd * ptimerwnd);
    //event                    m_evTimerWndDeleted;
protected:
    bool        m_bTimerCallbackEnable;
};

} // namespace gen

#endif // !defined(AFX_TIMERCALLBACK_H__EB76FCF2_95E1_4FA9_8B2F_845DE7F293D1__INCLUDED_)
