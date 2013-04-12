// TimerListener.h: interface for the TimerListener class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__TIMERLISTENER_H__8CB04176_6FFE_4A0A_9930_B475FDF15624__INCLUDED_)
#define __TIMERLISTENER_H__8CB04176_6FFE_4A0A_9930_B475FDF15624__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace ca
{

class TimerListener  
{
public:
   TimerListener();
   virtual ~TimerListener();

   virtual void TimerProc(UINT nID) = 0;

};

} // namespace ca


#endif // !defined(__TIMERLISTENER_H__8CB04176_6FFE_4A0A_9930_B475FDF15624__INCLUDED_)
