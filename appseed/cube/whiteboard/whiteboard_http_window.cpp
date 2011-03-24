#include "StdAfx.h"
#include "whiteboard.h"
#include "http_thread.h"
#include "http_window.h"

namespace whiteboard
{

   http_window::http_window(::ca::application * papp) :
      ca(papp)
   {
      m_pthread = NULL;
   }

   http_window::~http_window()
   {
   }

   void http_window::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &http_window::_001OnTimer);
   }

   BOOL http_window::create(::radix::thread * pthread)
   {
      m_pthread = pthread;
      if(!::user::interaction::CreateEx(0, NULL, NULL, 0, rect(0, 0, 0, 0), NULL, id()))
         return FALSE;
      return TRUE;
      
   }

   void http_window::_001OnTimer(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj);
      m_pthread->PostThreadMessage(http_thread::MessageTimer, ptimer->m_nIDEvent, 0);
   }

   BOOL http_window::PreCreateWindow(CREATESTRUCT& cs) 
   {
      if (cs.lpszClass == NULL)
      {
         // const char* System.RegisterWndClass(UINT nClassStyle, HCURSOR hCursor,    HBRUSH hbrBackground, HICON hIcon);
         cs.lpszClass = System.RegisterWndClass(0, 0, 0, 0);
      }
      return TRUE;
   }

} // namespace whiteboard