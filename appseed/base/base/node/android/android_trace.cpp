#include "framework.h"



/////////////////////////////////////////////////////////////////////////////
// DDE special case

/*
static void TraceDDE(const char * lpszPrefix, const MESSAGE* pMsg)
{
   ENSURE_ARG(pMsg != NULL);
  if (pMsg->message == WM_DDE_EXECUTE)
   {
      uint_ptr nDummy;
      HGLOBAL hCommands;
      if (!UnpackDDElParam(WM_DDE_EXECUTE, pMsg->lParam,
         &nDummy, (uint_ptr*)&hCommands))
      {
//         ::OutputDebugString(::ca2::trace::category_AppMsg, 0, "Warning: Unable to unpack WM_DDE_EXECUTE lParam %08lX.\n",
  //          pMsg->lParam);
         return;
      }
      ASSERT(hCommands != NULL);

      const char * lpszCommands = (const char *)::GlobalLock(hCommands);
      ENSURE_THROW(lpszCommands != NULL, ::AfxThrowMemoryException() );
//      ::OutputDebugString(::ca2::trace::category_AppMsg, 0, "%s: Execute '%s'.\n", lpszPrefix, lpszCommands);
      ::GlobalUnlock(hCommands);
   }
   else if (pMsg->message == WM_DDE_ADVISE)
   {
      uint_ptr nItem;
      ATOM aItem;
      HGLOBAL hAdvise;
      if (!UnpackDDElParam(WM_DDE_ADVISE, pMsg->lParam,
         (uint_ptr*)&hAdvise, &nItem))
      {
//         ::OutputDebugString(::ca2::trace::category_AppMsg, 0, "Warning: Unable to unpack WM_DDE_ADVISE lParam %08lX.\n",
//            pMsg->lParam);
       return;
      }
      aItem = (ATOM)nItem;
      ASSERT(aItem != NULL);
      ASSERT(hAdvise != NULL);

      DDEADVISE* lpAdvise = (DDEADVISE*)::GlobalLock(hAdvise);
      ENSURE_THROW(lpAdvise != NULL, ::AfxThrowMemoryException() );
      char szItem[80];
      szItem[0] = '\0';

      if (aItem != 0)
         ::GlobalGetAtomName(aItem, szItem, _countof(szItem));

      char szFormat[80];
      szFormat[0] = '\0';
      if (((UINT)0xC000 <= (UINT)lpAdvise->cfFormat) &&
            ((UINT)lpAdvise->cfFormat <= (UINT)0xFFFF))
      {
         ::GetClipboardFormatName(lpAdvise->cfFormat,
            szFormat, _countof(szFormat));

         // User defined clipboard formats have a range of 0xC000->0xFFFF
         // System clipboard formats have other ranges, but no printable
         // format names.
      }

      AfxTrace(
         "%s: Advise item='%s', Format='%s', Ack=%d, Defer Update= %d\n",
          lpszPrefix, szItem, szFormat, lpAdvise->fAckReq,
         lpAdvise->fDeferUpd);
      ::GlobalUnlock(hAdvise);
   }
}
*/
/////////////////////////////////////////////////////////////////////////////

void __trace_message(const char * lpszPrefix, ::signal_details * pobj)
{
//   ENSURE_ARG(AfxIsValidString(lpszPrefix));
   ENSURE_ARG(pobj != NULL);
   SCAST_PTR(::message::base, pbase, pobj);

   if (pbase->m_uiMessage == WM_MOUSEMOVE || pbase->m_uiMessage == WM_NCMOUSEMOVE ||
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
   if (pbase->m_uiMessage >= 0xC000)
   {
      // Window message registered with 'RegisterWindowMessage'
      //  (actually a USER atom)
//      if (::GetClipboardFormatNameA(pbase->m_uiMessage, szBuf, _countof(szBuf)))
  //       lpszMsgName = szBuf;
   }
   else if (pbase->m_uiMessage >= WM_USER)
   {
      // User message
      sprintf(szBuf, "WM_USER+0x%04X", pbase->m_uiMessage - WM_USER);
      lpszMsgName = szBuf;
   }
   else
   {
      // a system windows message
      const __MAP_MESSAGE* pMapMsg = allMessages;
      for (/*null*/ ; pMapMsg->lpszMsg != NULL; pMapMsg++)
      {
         if (pMapMsg->nMsg == pbase->m_uiMessage)
         {
            lpszMsgName = pMapMsg->lpszMsg;
            break;
         }
      }
   }

   if (lpszMsgName != NULL)
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



void __trace_message(const char * lpszPrefix, LPMESSAGE lpmsg)
{
   //ENSURE_ARG(AfxIsValidString(lpszPrefix));
   ENSURE_ARG(lpmsg != NULL);

   if (lpmsg->message == WM_MOUSEMOVE || lpmsg->message == WM_NCMOUSEMOVE ||
      lpmsg->message == WM_NCHITTEST || lpmsg->message == WM_SETCURSOR ||
      lpmsg->message == WM_CTLCOLORBTN ||
      lpmsg->message == WM_CTLCOLORDLG ||
      lpmsg->message == WM_CTLCOLOREDIT ||
      lpmsg->message == WM_CTLCOLORLISTBOX ||
      lpmsg->message == WM_CTLCOLORMSGBOX ||
      lpmsg->message == WM_CTLCOLORSCROLLBAR ||
      lpmsg->message == WM_CTLCOLORSTATIC ||
      lpmsg->message == WM_ENTERIDLE || lpmsg->message == WM_CANCELMODE ||
      lpmsg->message == 0x0118)    // WM_SYSTIMER (caret blink)
   {
      // don't report very frequently sent messages
      return;
   }

   const char * lpszMsgName = NULL;
   char szBuf[80];

   // find message name
   if (lpmsg->message >= 0xC000)
   {
      // Window message registered with 'RegisterWindowMessage'
      //  (actually a USER atom)
//      if (::GetClipboardFormatNameA(lpmsg->message, szBuf, _countof(szBuf)))
  //       lpszMsgName = szBuf;
   }
   else if (lpmsg->message >= WM_USER)
   {
      // User message
      uint32_t uiValue = lpmsg->message - WM_USER;
      snprintf(szBuf, sizeof(szBuf), "WM_USER+0x%04X", uiValue);
      lpszMsgName = szBuf;
   }
   else
   {
      // a system windows message
      const __MAP_MESSAGE* pMapMsg = allMessages;
      for (/*null*/ ; pMapMsg->lpszMsg != NULL; pMapMsg++)
      {
         if (pMapMsg->nMsg == lpmsg->message)
         {
            lpszMsgName = pMapMsg->lpszMsg;
            break;
         }
      }
   }

   if (lpszMsgName != NULL)
   {
#ifdef WIN64
//      TRACE(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%p, msg = %hs (%p, %p)\n",
  //       lpszPrefix, pMsg->hwnd, lpszMsgName,
    //     pMsg->wParam, pMsg->lParam);
#else
//      ::OutputDebugString(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = %hs (0x%08X, 0x%08X)\n",
  //       lpszPrefix, lpmsg->hwnd, lpszMsgName,
    //     lpmsg->wParam, lpmsg->lParam);
#endif
   }
   else
   {
#ifdef WIN64
      //::OutputDebugString(::ca2::trace::category_WinMsg, 4, "%s: hwnd=%p, msg = 0x%04X (%p, %p)\n",
        // lpszPrefix, pMsg->hwnd, lpszMsgName,
         //pMsg->wParam, pMsg->lParam);
#else
      //::OutputDebugString(::ca2::trace::category_WinMsg, 4, "%s: hwnd=0x%08X, msg = 0x%04X (0x%08X, 0x%08X)\n",
        // lpszPrefix, lpmsg->hwnd, lpszMsgName,
         //lpmsg->wParam, lpmsg->lParam);
#endif
   }

/*   if (lpmsg->message >= WM_DDE_FIRST && lpmsg->message <= WM_DDE_LAST)
      TraceDDE(lpszPrefix, pMsg);*/
}


