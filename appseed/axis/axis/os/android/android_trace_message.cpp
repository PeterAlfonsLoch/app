#include "framework.h"
#include "android.h"


void __trace_message(const char * lpszPrefix,::signal_details * pobj)
{
   //   ENSURE_ARG(AfxIsValidString(lpszPrefix));
   ENSURE_ARG(pobj != NULL);
   SCAST_PTR(::message::base,pbase,pobj);

   if(pbase->m_uiMessage == WM_MOUSEMOVE || pbase->m_uiMessage == WM_NCMOUSEMOVE ||
      pbase->m_uiMessage == WM_NCHITTEST || pbase->m_uiMessage == WM_SETCURSOR ||
      pbase->m_uiMessage == WM_CTLCOLORBTN ||
      pbase->m_uiMessage == WM_CTLCOLORDLG ||
      pbase->m_uiMessage == WM_CTLCOLOREDIT ||
      pbase->m_uiMessage == WM_CTLCOLORLISTBOX ||
      pbase->m_uiMessage == WM_CTLCOLORMSGBOX ||
      pbase->m_uiMessage == WM_CTLCOLORSCROLLBAR ||
      pbase->m_uiMessage == WM_CTLCOLORSTATIC ||
      pbase->m_uiMessage == WM_ENTERIDLE || pbase->m_uiMessage == WM_CANCELMODE ||
      pbase->m_uiMessage == 0x0118)    // WM_SYSTIMER (caret blink)
   {
      // don't report very frequently sent messages
      return;
   }

   const char * lpszMsgName = NULL;
   char szBuf[80];

   // find message name
   if(pbase->m_uiMessage >= 0xC000)
   {
      // Window message registered with 'RegisterWindowMessage'
      //  (actually a USER atom)
      //      if (::GetClipboardFormatNameA(pbase->m_uiMessage, szBuf, _countof(szBuf)))
      //       lpszMsgName = szBuf;
   }
   else if(pbase->m_uiMessage >= WM_USER)
   {
      // User message
      sprintf(szBuf,"WM_USER+0x%04X",pbase->m_uiMessage - WM_USER);
      lpszMsgName = szBuf;
   }
   else
   {
      // a system windows message
      const __MAP_MESSAGE* pMapMsg = allMessages;
      for(/*null*/ ; pMapMsg->lpszMsg != NULL; pMapMsg++)
      {
         if(pMapMsg->nMsg == pbase->m_uiMessage)
         {
            lpszMsgName = pMapMsg->lpszMsg;
            break;
         }
      }
   }

   if(lpszMsgName != NULL)
   {
#ifdef _WIN64
      //TRACE(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%p, msg = %s (%p, %p)\n",
      // lpszPrefix, pbase->m_hwnd, lpszMsgName,
      //pbase->m_wparam, pbase->m_lparam);
#else
      //  ::OutputDebugString(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = %s (0x%08X, 0x%08X)\n",
      //         lpszPrefix, pbase->m_hwnd, lpszMsgName,
      //       pbase->m_wparam, pbase->m_lparam);
#endif
   }
   else
   {
#ifdef _WIN64
      //      ::OutputDebugString(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%p, msg = 0x%04X (%p, %p)\n",
      //       lpszPrefix, pbase->m_hwnd, lpszMsgName,
      //     pbase->m_wparam, pbase->m_lparam);
#else
      //      ::OutputDebugString(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = 0x%04X (0x%08X, 0x%08X)\n",
      //       lpszPrefix, pbase->m_hwnd, lpszMsgName,
      //     pbase->m_wparam, pbase->m_lparam);
#endif
   }

   /*   if (pbase->m_uiMessage >= WM_DDE_FIRST && pbase->m_uiMessage <= WM_DDE_LAST)
   TraceDDE(lpszPrefix, pMsg);  */
}
