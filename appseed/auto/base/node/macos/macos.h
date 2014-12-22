#pragma once


string get_error_message(DWORD dwError);

sp(::aura::application)     mac_instantiate_application(sp(::aura::application) pappSystem, const char * pszId);

/////////////////////////////////////////////////////////////////////////////
// explicit initialization for general purpose classes

//CLASS_DECL_BASE WINBOOL AfxInitialize(WINBOOL bDLL = FALSE, DWORD dwVersion = _MFC_VER);
CLASS_DECL_BASE WINBOOL AfxInitialize(WINBOOL bDLL = FALSE, DWORD dwVersion = 0);

/////////////////////////////////////////////////////////////////////////////
// stop on a specific primitive::memory request

// Debugger hook on specified allocation request - Obsolete
CLASS_DECL_BASE void AfxSetAllocStop(LONG lRequestNumber);

// Return TRUE if primitive::memory is sane or print out what is wrong
CLASS_DECL_BASE bool __check_memory();

// Return TRUE if valid primitive::memory block of nBytes
CLASS_DECL_BASE WINBOOL AfxIsMemoryBlock(const void * p, UINT nBytes,
                                        LONG* plRequestNumber = NULL);

// helper routines for non-C++ EH implementations
// for THROW_LAST auto-delete backward compatiblity
CLASS_DECL_BASE void AfxThrowLastCleanup();

// other out-of-line helper functions
CLASS_DECL_BASE void AfxTryCleanup();


/////////////////////////////////////////////////////////////////////////////
// Global implementation helpers

// window creation hooking
CLASS_DECL_BASE void AfxHookWindowCreate(::user::interaction * pWnd);
CLASS_DECL_BASE WINBOOL AfxUnhookWindowCreate();
CLASS_DECL_BASE void AfxResetMsgCache();

// for backward compatibility to previous versions
#define _AfxHookWindowCreate    AfxHookWindowCreate
#define _AfxUnhookWindowCreate  AfxUnhookWindowCreate


// from wincore.cpp
extern CLASS_DECL_BASE const char _afxWnd[];           // simple child windows/controls
extern CLASS_DECL_BASE const char _afxWndControlBar[]; // controls with gray backgrounds
extern CLASS_DECL_BASE const char _afxWndMDIFrame[];
extern CLASS_DECL_BASE const char _afxWndFrameOrView[];
extern CLASS_DECL_BASE const char _afxWndOleControl[];


/////////////////////////////////////////////////////////////////////////////
// Special helpers

CLASS_DECL_BASE void AfxCancelModes(oswindow hWndRcvr);
CLASS_DECL_BASE WINBOOL AfxHelpEnabled();  // determine if ID_HELP handler exists
CLASS_DECL_BASE WINBOOL AfxCustomLogFont(UINT nIDS,LOGFONT* pLogFont);
CLASS_DECL_BASE WINBOOL AfxGetPropSheetFont(string & strFace,WORD& wSize,WINBOOL bWizard);

CLASS_DECL_BASE WINBOOL _AfxIsComboBoxControl(oswindow hWnd,UINT nStyle);
CLASS_DECL_BASE WINBOOL _AfxCheckCenterDialog(const char * lpszResource);
CLASS_DECL_BASE WINBOOL _AfxCompareClassName(oswindow hWnd,const char * lpszClassName);
CLASS_DECL_BASE oswindow _AfxChildWindowFromPoint(oswindow,POINT);

// for determining version of COMCTL32.DLL
#define VERSION_WIN4    MAKELONG(0, 4)
#define VERSION_IE3             MAKELONG(70, 4)
#define VERSION_IE4             MAKELONG(71, 4)
#define VERSION_IE401   MAKELONG(72, 4)
#define VERSION_6      MAKELONG(0, 6)
extern int _afxComCtlVersion;
DWORD _AfxGetComCtlVersion();

#include "macos_dir.h"
#include "macos_factory_exchange.h"
#include "macos_port_forward.h"
#include "macos_crypto.h"
#include "macos_ip_enum.h"

#define NULL_REF(class) (*((class *) NULL))
// xxx CLASS_DECL_BASE WNDPROC AfxGetAfxWndProc();
#define AfxWndProc (*AfxGetAfxWndProc())

#define MAC_THREAD(pthread) (dynamic_cast < ::mac::thread * > (dynamic_cast < ::thread * >(pthread)))
#define MAC_WINDOW(pwnd) (dynamic_cast < ::mac::interaction_impl * > (dynamic_cast < ::user::interaction_impl * >(pwnd)))


CLASS_DECL_BASE void __trace_message(const char * lpszPrefix, signal_details * pobj);
CLASS_DECL_BASE void __trace_message(const char * lpszPrefix, LPMESSAGE lpmsg);

CLASS_DECL_BASE void AfxProcessWndProcException(::exception::base*, signal_details * pobj);
CLASS_DECL_BASE void __cdecl __pre_translate_message(signal_details * pobj);



WINBOOL PeekMessage(
                    LPMESSAGE lpMsg,
                    oswindow hWnd,
                    UINT wMsgFilterMin,
                    UINT wMsgFilterMax,
                    UINT wRemoveMsg);

WINBOOL GetMessage(
                   LPMESSAGE lpMsg,
                   oswindow hWnd,
                   UINT wMsgFilterMin,
                   UINT wMsgFilterMax);



int32_t CLASS_DECL_BASE __mac_main(int32_t argc, char * argv[]);


CLASS_DECL_BASE void vfxThrowFileException(sp(::aura::application) papp, int32_t cause, LONG lOsError, const char * lpszFileName = NULL);



#include "macos_dir.h"
#include "macos_file_system.h"
#include "macos_file_set.h"
