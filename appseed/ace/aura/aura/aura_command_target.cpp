//#include "framework.h"

















command_target::command_target()
{
   CommonConstruct();
}

command_target::command_target(::aura::application * papp)
   : object(papp)
{
   CommonConstruct();
}

void command_target::CommonConstruct()
{
}

command_target::~command_target()
{
}

bool command_target::handle(::aura::cmd_msg * pcmdmsg)
{
   return pcmdmsg->handle(this);
}

/////////////////////////////////////////////////////////////////////////////
// command_target windows message dispatching

/*
__STATIC bool _::core::DispatchCmdMsg(command_target* pTarget, UINT nID, int32_t nCode,
__PMSG pfn, void * pExtra, uint_ptr nSig,
// return TRUE to stop routing
{
ENSURE_VALID(pTarget);
UNUSED(nCode);   // unused in release builds

union MessageMapFunctions mmf;
mmf.pfn = pfn;
bool bResult = TRUE; // default is ok

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

case ::core::SigCmd_v:
// normal command or control notification
ASSERT(CN_COMMAND == 0);        // CN_COMMAND same as BN_CLICKED
ASSERT(pExtra == NULL);
(pTarget->*mmf.pfnCmd_v_v)();
break;

case ::core::SigCmd_b:
// normal command or control notification
ASSERT(CN_COMMAND == 0);        // CN_COMMAND same as BN_CLICKED
ASSERT(pExtra == NULL);
bResult = (pTarget->*mmf.pfnCmd_b_v)();
break;

case ::core::SigCmd_RANGE:
// normal command or control notification in a range
ASSERT(CN_COMMAND == 0);        // CN_COMMAND same as BN_CLICKED
ASSERT(pExtra == NULL);
(pTarget->*mmf.pfnCmd_v_u)(nID);
break;

case ::core::SigCmd_EX:
// extended command (passed ID, returns bContinue)
ASSERT(pExtra == NULL);
bResult = (pTarget->*mmf.pfnCmd_b_u)(nID);
break;

case ::core::SigNotify_v:
{
__NOTIFY* pNotify = (__NOTIFY*)pExtra;
ENSURE(pNotify != NULL);
ASSERT(pNotify->pResult != NULL);
ASSERT(pNotify->pNMHDR != NULL);
(pTarget->*mmf.pfnNotify_v_NMHDR_pl)(pNotify->pNMHDR, pNotify->pResult);
}
break;

case ::core::SigNotify_b:
{
__NOTIFY* pNotify = (__NOTIFY*)pExtra;
ENSURE(pNotify != NULL);
ASSERT(pNotify->pResult != NULL);
ASSERT(pNotify->pNMHDR != NULL);
bResult = (pTarget->*mmf.pfnNotify_b_NMHDR_pl)(pNotify->pNMHDR, pNotify->pResult);
}
break;

case ::core::SigNotify_RANGE:
{
__NOTIFY* pNotify = (__NOTIFY*)pExtra;
ENSURE(pNotify != NULL);
ASSERT(pNotify->pResult != NULL);
ASSERT(pNotify->pNMHDR != NULL);
(pTarget->*mmf.pfnNotify_v_u_NMHDR_pl)(nID, pNotify->pNMHDR,
pNotify->pResult);
}
break;

case ::core::SigNotify_EX:
{
__NOTIFY* pNotify = (__NOTIFY*)pExtra;
ENSURE(pNotify != NULL);
ASSERT(pNotify->pResult != NULL);
ASSERT(pNotify->pNMHDR != NULL);
bResult = (pTarget->*mmf.pfnNotify_b_u_NMHDR_pl)(nID, pNotify->pNMHDR,
pNotify->pResult);
}
break;

case ::core::SigCmdUI:
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

case ::core::SigCmdUI_RANGE:
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
case ::core::SigCmd_v_pv:
(pTarget->*mmf.pfnCmd_v_pv)(pExtra);
break;
case ::core::SigCmd_b_pv:
bResult = (pTarget->*mmf.pfnCmd_b_pv)(pExtra);
break;
/*
case ::core::Sig_vv:
// normal command or control notification
ASSERT(CN_COMMAND == 0);        // CN_COMMAND same as BN_CLICKED
ASSERT(pExtra == NULL);
(pTarget->*mmf.pfn_COMMAND)();
break;

case ::core::Sig_bv:
// normal command or control notification
ASSERT(CN_COMMAND == 0);        // CN_COMMAND same as BN_CLICKED
ASSERT(pExtra == NULL);
bResult = (pTarget->*mmf.pfn_bCOMMAND)();
break;

case ::core::Sig_vw:
// normal command or control notification in a range
ASSERT(CN_COMMAND == 0);        // CN_COMMAND same as BN_CLICKED
ASSERT(pExtra == NULL);
(pTarget->*mmf.pfn_COMMAND_RANGE)(nID);
break;

case ::core::Sig_bw:
// extended command (passed ID, returns bContinue)
ASSERT(pExtra == NULL);
bResult = (pTarget->*mmf.pfn_COMMAND_EX)(nID);
break;

case ::core::Sig_vNMHDRpl:
{
__NOTIFY* pNotify = (__NOTIFY*)pExtra;
ENSURE(pNotify != NULL);
ASSERT(pNotify->pResult != NULL);
ASSERT(pNotify->pNMHDR != NULL);
(pTarget->*mmf.pfn_NOTIFY)(pNotify->pNMHDR, pNotify->pResult);
}
break;
case ::core::Sig_bNMHDRpl:
{
__NOTIFY* pNotify = (__NOTIFY*)pExtra;
ENSURE(pNotify != NULL);
ASSERT(pNotify->pResult != NULL);
ASSERT(pNotify->pNMHDR != NULL);
bResult = (pTarget->*mmf.pfn_bNOTIFY)(pNotify->pNMHDR, pNotify->pResult);
}
break;
case ::core::Sig_vwNMHDRpl:
{
__NOTIFY* pNotify = (__NOTIFY*)pExtra;
ENSURE(pNotify != NULL);
ASSERT(pNotify->pResult != NULL);
ASSERT(pNotify->pNMHDR != NULL);
(pTarget->*mmf.pfn_NOTIFY_RANGE)(nID, pNotify->pNMHDR,
pNotify->pResult);
}
break;
case ::core::Sig_bwNMHDRpl:
{
__NOTIFY* pNotify = (__NOTIFY*)pExtra;
ENSURE(pNotify != NULL);
ASSERT(pNotify->pResult != NULL);
ASSERT(pNotify->pNMHDR != NULL);
bResult = (pTarget->*mmf.pfn_NOTIFY_EX)(nID, pNotify->pNMHDR,
pNotify->pResult);
}
break;
case ::core::Sig_cmdui:
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

case ::core::Sig_cmduiw:
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
case ::core::Sig_vpv:
(pTarget->*mmf.pfn_OTHER)(pExtra);
break;
case ::core::Sig_bpv:
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
bool command_target::_001OnCmdMsg(::aura::cmd_msg * pcmdmsg)

{

// determine the message number and code (packed into nCode)
const __MSGMAP* pMessageMap;
const __MSGMAP_ENTRY* lpEntry;
UINT nMsg = 0;


if (nCode != CN_UPDATE_COMMAND_UI)
{
nMsg = HIWORD(nCode);
nCode = LOWORD(nCode);
}

// for backward compatibility HIWORD(nCode)==0 is WM_COMMAND
if (nMsg == 0)
nMsg = WM_COMMAND;

// look through message map to see if it applies to us

for (pMessageMap = GetMessageMap(); pMessageMap->pfnGetBaseMap != NULL;
pMessageMap = (*pMessageMap->pfnGetBaseMap)())
{
// Note: catches  // BEGIN_MESSAGE_MAP(CMyClass, CMyClass)!
ASSERT(pMessageMap != (*pMessageMap->pfnGetBaseMap)());
lpEntry = ::core::FindMessageEntry(pMessageMap->lpEntries, nMsg, nCode, nID);
if (lpEntry != NULL)
{
// found it
#ifdef DEBUG
if (nCode == CN_COMMAND)
TRACE(traceCmdRouting, 1, "SENDING command id 0x%04X to %hs target.\n", nID,
typeid(*this).name());
else if (nCode > CN_COMMAND)
TRACE(traceCmdRouting, 1, "SENDING control notification %d from control id 0x%04X to %hs interaction_impl.\n",
nCode, nID, typeid(*this).name());
#endif //DEBUG
return _::core::DispatchCmdMsg(this, nID, nCode,
lpEntry->pfn, pExtra, lpEntry->nSig, pHandlerInfo);
}
}
return FALSE;   // not handled
}
*/

/////////////////////////////////////////////////////////////////////////////
// command_target routines that delegate to the WinApp

void command_target::BeginWaitCursor()
{
   Session.DoWaitCursor(1);
}
void command_target::EndWaitCursor()
{
   Session.DoWaitCursor(-1);
}
void command_target::RestoreWaitCursor()
{
   Session.DoWaitCursor(0);
}

/////////////////////////////////////////////////////////////////////////////
// Root of message maps


//const __MSGMAP* command_target::GetMessageMap() const
//{
//   return GetThisMessageMap();
//}

/*
const __MSGMAP* command_target::GetThisMessageMap()
{
static const __MSGMAP_ENTRY _messageEntries[] =
{
{ 0, 0, ::core::Sig_end, 0 }     // nothing here
};
static const __MSGMAP messageMap =
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


/////////////////////////////////////////////////////////////////////////////
// Special init


//static const BYTE gen_Dot[] = { 0x6, 0xF, 0xF, 0xF, 0x6 }; // simple byte bitmap, 1=> bit on
#define DOT_WIDTH   4
#define DOT_HEIGHT  5

/*
__STATIC void __load_dot_bitmap()
{
ASSERT(afxData.hbmMenuDot == NULL);
// attempt to load special bitmap, else default to arrow
size size = ::GetMenuCheckMarkDimensions();
ENSURE(size.cx > 4 && size.cy > 5); // not too small please
if (size.cx > 32)
size.cx = 32;
int32_t iwRow = (size.cx + 15) >> 4;    // # of WORDs per raster line
int32_t nShift = (size.cx - DOT_WIDTH) / 2;     // # of bits to shift over
nShift += ((iwRow * 16) - size.cx); // padding for uint16_t alignment
if (nShift > 16 - DOT_WIDTH)
nShift = 16 - DOT_WIDTH;    // maximum shift for 1 uint16_t

if (size.cy > 32)
size.cy = 32;

// bitmap 2/4/4/4/2 pixels wide - centered (0 => black)
BYTE rgbBitmap[32 * 2 * sizeof(WORD)];
memset(rgbBitmap, 0xff, sizeof(rgbBitmap));

BYTE* pbOut = &rgbBitmap[iwRow * sizeof(WORD) *
((size.cy - (DOT_HEIGHT+1)) >> 1)];
const BYTE* pbIn = gen_Dot;
for (int32_t y = 0; y < DOT_HEIGHT; y++)
{
WORD w = (WORD)~(((uint32_t)*pbIn++) << nShift);
// bitmaps are always hi-lo
pbOut[0] = HIBYTE(w);
pbOut[1] = LOBYTE(w);
pbOut += iwRow * sizeof(WORD);
}

afxData.hbmMenuDot = ::CreateBitmap(size.cx, size.cy, 1, 1,
(LPVOID)rgbBitmap);
if (afxData.hbmMenuDot == NULL)
{
//      TRACE(::aura::trace::category_AppMsg, 0, "Warning: using system arrow bitmap instead of dot.\n");
#define OBM_MNARROW         32739
afxData.hbmMenuDot = ::LoadBitmap(NULL, MAKEINTRESOURCE(OBM_MNARROW));
}
}


*/


























