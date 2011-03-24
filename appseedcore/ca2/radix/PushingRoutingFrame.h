// PushingRoutingFrame.h: interface for the CPushingRoutingFrame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUSHINGROUTINGFRAME_H__433F3EE7_B3E3_4BCD_A6F3_4A501740B0F1__INCLUDED_)
#define AFX_PUSHINGROUTINGFRAME_H__433F3EE7_B3E3_4BCD_A6F3_4A501740B0F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

::userbase::menu* FindPopupMenuFromID(::userbase::menu* pMenu, UINT nID, UINT nData);

/*class CLASS_DECL_ca push_routing_frame  
{
protected:
   frame_window* pOldRoutingFrame;
   _AFX_THREAD_STATE* pThreadState;

public:
   push_routing_frame(frame_window* pNewRoutingFrame)
   {
      pThreadState = AfxGetThreadState();
      pOldRoutingFrame = pThreadState->m_pRoutingFrame;
      pThreadState->m_pRoutingFrame = pNewRoutingFrame;
   }
   
    ~push_routing_frame()
   { pThreadState->m_pRoutingFrame = pOldRoutingFrame;}

};*/

#endif // !defined(AFX_PUSHINGROUTINGFRAME_H__433F3EE7_B3E3_4BCD_A6F3_4A501740B0F1__INCLUDED_)
