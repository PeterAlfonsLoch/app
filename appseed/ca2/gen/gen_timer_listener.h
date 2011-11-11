// TimerListener.h: interface for the TimerListener class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMERLISTENER_H__8CB04176_6FFE_4A0A_9930_B475FDF15624__INCLUDED_)
#define AFX_TIMERLISTENER_H__8CB04176_6FFE_4A0A_9930_B475FDF15624__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace gen
{

class TimerListener  
{
public:
   TimerListener();
   virtual ~TimerListener();

   virtual void TimerProc(UINT nID) = 0;

};

} // namespace gen


#endif // !defined(AFX_TIMERLISTENER_H__8CB04176_6FFE_4A0A_9930_B475FDF15624__INCLUDED_)
