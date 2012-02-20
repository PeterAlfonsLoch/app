#include "StdAfx.h"

command_target::command_target()
{
   CommonConstruct();
}

command_target::command_target(::ca::application * papp)
: ca(papp)
{
   CommonConstruct();
}

void command_target::CommonConstruct()
{
}

command_target::~command_target()
{
}

bool command_target::handle(BaseCmdMsg * pcmdmsg)
{
   return pcmdmsg->handle(this);
}

/////////////////////////////////////////////////////////////////////////////
// command_target windows message dispatching

/*
AFX_STATIC BOOL _AfxDispatchCmdMsg(command_target* pTarget, UINT nID, int nCode,
   AFX_PMSG pfn, void * pExtra, UINT_PTR nSig, 
      // return TRUE to stop routing
{
   ENSURE_VALID(pTarget);
   UNUSED(nCode);   // unused in release builds

   union MessageMapFunctions mmf;
   mmf.pfn = pfn;
   BOOL bResult = TRUE; // default is ok

   if (pHandlerInfo != NULL)
   {
      // just fill in the information, don't do it
      pHandlerInfo->pTarget = pTarget;
      pHandlerInfo->pmf = mmf.pfn;
      return TRUE;
   }

   switch (nSig)
   {
   default:    // illegal
      ASSERT(FALSE);
      return 0;
      break;

   case AfxSigCmd_v:
      // normal command or control notification
      ASSERT(CN_COMMAND == 0);        // CN_COMMAND same as BN_CLICKED
      ASSERT(pExtra == NULL);
      (pTarget->*mmf.pfnCmd_v_v)();
      break;

   case AfxSigCmd_b:
      // normal command or control notification
      ASSERT(CN_COMMAND == 0);        // CN_COMMAND same as BN_CLICKED
      ASSERT(pExtra == NULL);
      bResult = (pTarget->*mmf.pfnCmd_b_v)();
      break;

   case AfxSigCmd_RANGE:
      // normal command or control notification in a range
      ASSERT(CN_COMMAND == 0);        // CN_COMMAND same as BN_CLICKED
      ASSERT(pExtra == NULL);
      (pTarget->*mmf.pfnCmd_v_u)(nID);
      break;

   case AfxSigCmd_EX:
      // extended command (passed ID, returns bContinue)
      ASSERT(pExtra == NULL);
      bResult = (pTarget->*mmf.pfnCmd_b_u)(nID);
      break;

   case AfxSigNotify_v:
      {
         AFX_NOTIFY* pNotify = (AFX_NOTIFY*)pExtra;
         ENSURE(pNotify != NULL);
         ASSERT(pNotify->pResult != NULL);
         ASSERT(pNotify->pNMHDR != NULL);
         (pTarget->*mmf.pfnNotify_v_NMHDR_pl)(pNotify->pNMHDR, pNotify->pResult);
      }
      break;

   case AfxSigNotify_b:
      {
         AFX_NOTIFY* pNotify = (AFX_NOTIFY*)pExtra;
         ENSURE(pNotify != NULL);
         ASSERT(pNotify->pResult != NULL);
         ASSERT(pNotify->pNMHDR != NULL);
         bResult = (pTarget->*mmf.pfnNotify_b_NMHDR_pl)(pNotify->pNMHDR, pNotify->pResult);
      }
      break;

   case AfxSigNotify_RANGE:
      {
         AFX_NOTIFY* pNotify = (AFX_NOTIFY*)pExtra;
         ENSURE(pNotify != NULL);
         ASSERT(pNotify->pResult != NULL);
         ASSERT(pNotify->pNMHDR != NULL);
         (pTarget->*mmf.pfnNotify_v_u_NMHDR_pl)(nID, pNotify->pNMHDR,
            pNotify->pResult);
      }
      break;

   case AfxSigNotify_EX:
      {
         AFX_NOTIFY* pNotify = (AFX_NOTIFY*)pExtra;
         ENSURE(pNotify != NULL);
         ASSERT(pNotify->pResult != NULL);
         ASSERT(pNotify->pNMHDR != NULL);
         bResult = (pTarget->*mmf.pfnNotify_b_u_NMHDR_pl)(nID, pNotify->pNMHDR,
            pNotify->pResult);
      }
      break;

   case AfxSigCmdUI:
      {
         // ON_UPDATE_COMMAND_UI or ON_UPDATE_COMMAND_UI_REFLECT case
         ASSERT(CN_UPDATE_COMMAND_UI == (UINT)-1);
         ASSERT(nCode == CN_UPDATE_COMMAND_UI || nCode == 0xFFFF);
         ENSURE_ARG(pExtra != NULL);
         cmd_ui* pCmdUI = (cmd_ui*)pExtra;
         ASSERT(!pCmdUI->m_bContinueRouting);    // idle - not set
         (pTarget->*mmf.pfnCmdUI_v_C)(pCmdUI);
         bResult = !pCmdUI->m_bContinueRouting;
         pCmdUI->m_bContinueRouting = FALSE;     // go back to idle
      }
      break;

   case AfxSigCmdUI_RANGE:
      {
         // ON_UPDATE_COMMAND_UI case
         ASSERT(nCode == CN_UPDATE_COMMAND_UI);
         ENSURE_ARG(pExtra != NULL);
         cmd_ui* pCmdUI = (cmd_ui*)pExtra;
         ASSERT(pCmdUI->m_nID == nID);           // sanity assert
         ASSERT(!pCmdUI->m_bContinueRouting);    // idle - not set
         (pTarget->*mmf.pfnCmdUI_v_C_u)(pCmdUI, nID);
         bResult = !pCmdUI->m_bContinueRouting;
         pCmdUI->m_bContinueRouting = FALSE;     // go back to idle
      }
      break;

   // general extensibility hooks
   case AfxSigCmd_v_pv:
      (pTarget->*mmf.pfnCmd_v_pv)(pExtra);
      break;
   case AfxSigCmd_b_pv:
      bResult = (pTarget->*mmf.pfnCmd_b_pv)(pExtra);
      break;
   /*
   case AfxSig_vv:
      // normal command or control notification
      ASSERT(CN_COMMAND == 0);        // CN_COMMAND same as BN_CLICKED
      ASSERT(pExtra == NULL);
      (pTarget->*mmf.pfn_COMMAND)();
      break;

   case AfxSig_bv:
      // normal command or control notification
      ASSERT(CN_COMMAND == 0);        // CN_COMMAND same as BN_CLICKED
      ASSERT(pExtra == NULL);
      bResult = (pTarget->*mmf.pfn_bCOMMAND)();
      break;

   case AfxSig_vw:
      // normal command or control notification in a range
      ASSERT(CN_COMMAND == 0);        // CN_COMMAND same as BN_CLICKED
      ASSERT(pExtra == NULL);
      (pTarget->*mmf.pfn_COMMAND_RANGE)(nID);
      break;

   case AfxSig_bw:
      // extended command (passed ID, returns bContinue)
      ASSERT(pExtra == NULL);
      bResult = (pTarget->*mmf.pfn_COMMAND_EX)(nID);
      break;

   case AfxSig_vNMHDRpl:
      {
         AFX_NOTIFY* pNotify = (AFX_NOTIFY*)pExtra;
         ENSURE(pNotify != NULL);
         ASSERT(pNotify->pResult != NULL);
         ASSERT(pNotify->pNMHDR != NULL);
         (pTarget->*mmf.pfn_NOTIFY)(pNotify->pNMHDR, pNotify->pResult);
      }
      break;
   case AfxSig_bNMHDRpl:
      {
         AFX_NOTIFY* pNotify = (AFX_NOTIFY*)pExtra;
         ENSURE(pNotify != NULL);
         ASSERT(pNotify->pResult != NULL);
         ASSERT(pNotify->pNMHDR != NULL);
         bResult = (pTarget->*mmf.pfn_bNOTIFY)(pNotify->pNMHDR, pNotify->pResult);
      }
      break;
   case AfxSig_vwNMHDRpl:
      {
         AFX_NOTIFY* pNotify = (AFX_NOTIFY*)pExtra;
         ENSURE(pNotify != NULL);
         ASSERT(pNotify->pResult != NULL);
         ASSERT(pNotify->pNMHDR != NULL);
         (pTarget->*mmf.pfn_NOTIFY_RANGE)(nID, pNotify->pNMHDR,
            pNotify->pResult);
      }
      break;
   case AfxSig_bwNMHDRpl:
      {
         AFX_NOTIFY* pNotify = (AFX_NOTIFY*)pExtra;
         ENSURE(pNotify != NULL);
         ASSERT(pNotify->pResult != NULL);
         ASSERT(pNotify->pNMHDR != NULL);
         bResult = (pTarget->*mmf.pfn_NOTIFY_EX)(nID, pNotify->pNMHDR,
            pNotify->pResult);
      }
      break;
   case AfxSig_cmdui:
      {
         // ON_UPDATE_COMMAND_UI or ON_UPDATE_COMMAND_UI_REFLECT case
         ASSERT(CN_UPDATE_COMMAND_UI == (UINT)-1);
         ASSERT(nCode == CN_UPDATE_COMMAND_UI || nCode == 0xFFFF);
         ENSURE_ARG(pExtra != NULL);
         cmd_ui* pCmdUI = (cmd_ui*)pExtra;
         ASSERT(!pCmdUI->m_bContinueRouting);    // idle - not set
         (pTarget->*mmf.pfn_UPDATE_COMMAND_UI)(pCmdUI);
         bResult = !pCmdUI->m_bContinueRouting;
         pCmdUI->m_bContinueRouting = FALSE;     // go back to idle
      }
      break;

   case AfxSig_cmduiw:
      {
         // ON_UPDATE_COMMAND_UI case
         ASSERT(nCode == CN_UPDATE_COMMAND_UI);
         ENSURE_ARG(pExtra != NULL);
         cmd_ui* pCmdUI = (cmd_ui*)pExtra;
         ASSERT(pCmdUI->m_nID == nID);           // sanity assert
         ASSERT(!pCmdUI->m_bContinueRouting);    // idle - not set
         (pTarget->*mmf.pfn_UPDATE_COMMAND_UI_RANGE)(pCmdUI, nID);
         bResult = !pCmdUI->m_bContinueRouting;
         pCmdUI->m_bContinueRouting = FALSE;     // go back to idle
      }
      break;

   // general extensibility hooks
   case AfxSig_vpv:
      (pTarget->*mmf.pfn_OTHER)(pExtra);
      break;
   case AfxSig_bpv:
      bResult = (pTarget->*mmf.pfn_OTHER_EX)(pExtra);
      break;
   */
/*
   }
   return bResult;
}
*/

// compare two pointers to GUIDs -- TRUE if both pointers are NULL
// or both pointers point to same GUID; FALSE otherwise

#define IsEqualNULLGuid(pGuid1, pGuid2) \
   (((pGuid1) == NULL && (pGuid2) == NULL) || \
    ((pGuid1) != NULL && (pGuid2) != NULL && \
      IsEqualGUID(*(pGuid1), *(pGuid2))))

/*
bool command_target::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)

{

   // determine the message number and code (packed into nCode)
   const AFX_MSGMAP* pMessageMap;
   const AFX_MSGMAP_ENTRY* lpEntry;
   UINT nMsg = 0;


   if (nCode != CN_UPDATE_COMMAND_UI)
   {
      nMsg = HIWORD(nCode);
      nCode = LOWORD(nCode);
   }

   // for backward compatibility HIWORD(nCode)==0 is WM_COMMAND
   if (nMsg == 0)
      nMsg = WM_COMMAND;

   // look through message ::collection::map to see if it applies to us

   for (pMessageMap = GetMessageMap(); pMessageMap->pfnGetBaseMap != NULL;
     pMessageMap = (*pMessageMap->pfnGetBaseMap)())
   {
      // Note: catches  // BEGIN_MESSAGE_MAP(CMyClass, CMyClass)!
      ASSERT(pMessageMap != (*pMessageMap->pfnGetBaseMap)());
      lpEntry = AfxFindMessageEntry(pMessageMap->lpEntries, nMsg, nCode, nID);
      if (lpEntry != NULL)
      {
         // found it
#ifdef _DEBUG
         if (nCode == CN_COMMAND)
            TRACE(traceCmdRouting, 1, "SENDING command id 0x%04X to %hs target.\n", nID,
               typeid(*this).name());
         else if (nCode > CN_COMMAND)
            TRACE(traceCmdRouting, 1, "SENDING control notification %d from control id 0x%04X to %hs ::ca::window.\n",
               nCode, nID, typeid(*this).name());
#endif //_DEBUG
         return _AfxDispatchCmdMsg(this, nID, nCode,
            lpEntry->pfn, pExtra, lpEntry->nSig, pHandlerInfo);
      }
   }
   return FALSE;   // not handled
}
*/

/////////////////////////////////////////////////////////////////////////////
// command_target routines that delegate to the WinApp

void command_target::BeginWaitCursor()
   { System.DoWaitCursor(1); }
void command_target::EndWaitCursor()
   { System.DoWaitCursor(-1); }
void command_target::RestoreWaitCursor()
   { System.DoWaitCursor(0); }

/////////////////////////////////////////////////////////////////////////////
// Root of message maps


//const AFX_MSGMAP* command_target::GetMessageMap() const
//{
//   return GetThisMessageMap();
//}

/*
const AFX_MSGMAP* command_target::GetThisMessageMap()
{
   static const AFX_MSGMAP_ENTRY _messageEntries[] =
   {
      { 0, 0, AfxSig_end, 0 }     // nothing here
   };
   static const AFX_MSGMAP messageMap =
   {
      NULL,
      &_messageEntries[0]
   };
   return &messageMap;   
}
*/

/////////////////////////////////////////////////////////////////////////////
// cmd_ui - User Interface for a command

// cmd_ui is a protocol class for all command handler variants
//      cmd_ui is an implementation class for menus and general dialog
//        controls (usually buttons)

cmd_ui::cmd_ui(::ca::application * papp)  :
   ca(papp)
{

   m_iIndex             = 0;
   m_iCount             = 0;
   m_pMenu              = NULL;
   m_pSubMenu           = NULL;
   m_pParentMenu        = NULL;
   m_pOther             = NULL;
   m_bEnableChanged     = FALSE;
   m_bContinueRouting   = FALSE;

}

// default cmd_ui implementation only works for Menu Items
void cmd_ui::Enable(BOOL bOn)
{
   if (m_pMenu != NULL)
   {
      if (m_pSubMenu != NULL)
         return; // don't change popup menus indirectly

      ENSURE(m_iIndex < m_iCount);
   }
   else
   {
      // enable/disable a control (i.e. child ::ca::window)
      ENSURE(m_pOther != NULL);

      // if control has the focus, move the focus before disabling
      if (!bOn && (System.get_focus_guie() == m_pOther))
         m_pOther->GetParent()->SendMessage(WM_NEXTDLGCTL, 0, FALSE);
      m_pOther->EnableWindow(bOn);
   }
   m_bEnableChanged = TRUE;
}



void cmd_ui::_001SetCheck(check::e_check nCheck)
{
   if (m_pMenu != NULL)
   {
      if (m_pSubMenu != NULL)
         return; // don't change popup menus indirectly

      // place checkmark next to menu item
      ENSURE(m_iIndex < m_iCount);
   }
   else
   {
      // we can only check buttons or controls acting like buttons
      ENSURE(m_pOther != NULL);
      if (m_pOther->SendMessage(WM_GETDLGCODE) & DLGC_BUTTON)
         m_pOther->SendMessage(BM_SETCHECK, nCheck);
      // otherwise ignore it
   }
}

AFX_STATIC void _AfxLoadDotBitmap(); // for swap tuning

void cmd_ui::SetRadio(BOOL bOn)
{
   _001SetCheck(bOn != FALSE); // this default works for most things as well
   if (m_pMenu != NULL)
   {
      if (m_pSubMenu != NULL)
         return; // don't change popup menus indirectly

      // for menu item - use dot instead of checkmark
      ENSURE(m_iIndex < m_iCount);

      if (afxData.hbmMenuDot == NULL)
         _AfxLoadDotBitmap();    // in INIT segment

   }
}

void cmd_ui::SetText(const char * lpszText)
{
   ENSURE_ARG(lpszText != NULL);
   ASSERT(AfxIsValidString(lpszText));

   {
      ENSURE(m_pOther != NULL);
      m_pOther->SetWindowText(lpszText);
   }
}

BOOL cmd_ui::DoUpdate(command_target* pTarget, BOOL bDisableIfNoHndler)
{
   UNREFERENCED_PARAMETER(bDisableIfNoHndler);
   if(m_id.is_empty())
      return TRUE;     // ignore invalid IDs

   ENSURE_VALID(pTarget);

   m_bEnableChanged = FALSE;
   BOOL bResult = pTarget->_001SendUpdateCmdUi(this);
   // can have m_bEnableChanged but gave the chance for others
   // to change without returning (bResult = FALSE)
   //if (!bResult)
   //   ASSERT(!m_bEnableChanged); // not routed

   return bResult;
}

/////////////////////////////////////////////////////////////////////////////
// Special init


AFX_STATIC_DATA const BYTE _afxDot[] =
   { 0x6, 0xF, 0xF, 0xF, 0x6 }; // simple byte bitmap, 1=> bit on
#define DOT_WIDTH   4
#define DOT_HEIGHT  5

AFX_STATIC void _AfxLoadDotBitmap()
{
   ASSERT(afxData.hbmMenuDot == NULL);
   // attempt to load special bitmap, else default to arrow
   size size = ::GetMenuCheckMarkDimensions();
   ENSURE(size.cx > 4 && size.cy > 5); // not too small please
   if (size.cx > 32)
      size.cx = 32;
   int iwRow = (size.cx + 15) >> 4;    // # of WORDs per raster line
   int nShift = (size.cx - DOT_WIDTH) / 2;     // # of bits to shift over
   nShift += ((iwRow * 16) - size.cx); // padding for word alignment
   if (nShift > 16 - DOT_WIDTH)
      nShift = 16 - DOT_WIDTH;    // maximum shift for 1 word

   if (size.cy > 32)
      size.cy = 32;

   // bitmap 2/4/4/4/2 pixels wide - centered (0 => black)
   BYTE rgbBitmap[32 * 2 * sizeof(WORD)];
   memset(rgbBitmap, 0xff, sizeof(rgbBitmap));

   BYTE* pbOut = &rgbBitmap[iwRow * sizeof(WORD) *
                     ((size.cy - (DOT_HEIGHT+1)) >> 1)];
   const BYTE* pbIn = _afxDot;
   for (int y = 0; y < DOT_HEIGHT; y++)
   {
      WORD w = (WORD)~(((DWORD)*pbIn++) << nShift);
      // bitmaps are always hi-lo
      pbOut[0] = HIBYTE(w);
      pbOut[1] = LOBYTE(w);
      pbOut += iwRow * sizeof(WORD);
   }

   afxData.hbmMenuDot = ::CreateBitmap(size.cx, size.cy, 1, 1,
         (LPVOID)rgbBitmap);
   if (afxData.hbmMenuDot == NULL)
   {
//      TRACE(::radix::trace::category_AppMsg, 0, "Warning: using system arrow bitmap instead of dot.\n");
      #define OBM_MNARROW         32739
      afxData.hbmMenuDot = ::LoadBitmap(NULL, MAKEINTRESOURCE(OBM_MNARROW));
   }
}


