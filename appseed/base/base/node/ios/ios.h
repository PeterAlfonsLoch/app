#pragma once


#include "app/appseed/axis/axis/axis/axis.h"

#include "app/appseed/axis/axis/node/ios/ios.h"


////#define CLASS_DECL_AURA

//struct plane_system
//{
//   
//   ::plane::system *    m_psystem;
//   
//   plane_system(const char * pszId);
//   
//   UIWindow * init_part_2ex(CGRect rect);
//   
//   void begin();
//   
//};


string get_error_message(DWORD dwError);

::aura::application *     ios_instantiate_application(::aura::application * pappSystem, const char * pszId);

/////////////////////////////////////////////////////////////////////////////
// explicit initialization for general purpose classes

////CLASS_DECL_AURA WINBOOL AfxInitialize(WINBOOL bDLL = FALSE, DWORD dwVersion = _MFC_VER);
//CLASS_DECL_AURA WINBOOL AfxInitialize(WINBOOL bDLL = FALSE, DWORD dwVersion = 0);

/////////////////////////////////////////////////////////////////////////////
// stop on a specific memory request

// Debugger hook on specified allocation request - Obsolete
CLASS_DECL_AURA void AfxSetAllocStop(LONG lRequestNumber);

// Return TRUE if memory is sane or print out what is wrong
CLASS_DECL_AURA bool __check_memory();

// Return TRUE if valid memory block of nBytes
//CLASS_DECL_AURA WINBOOL AfxIsMemoryBlock(const void * p, UINT nBytes,
//                                        LONG* plRequestNumber = NULL);

// helper routines for non-C++ EH implementations
// for THROW_LAST auto-delete backward compatiblity
CLASS_DECL_AURA void AfxThrowLastCleanup();

// other out-of-line helper functions
CLASS_DECL_AURA void AfxTryCleanup();


/////////////////////////////////////////////////////////////////////////////
// Global implementation helpers

// window creation hooking
CLASS_DECL_AURA void AfxHookWindowCreate(::user::interaction * pWnd);
CLASS_DECL_AURA WINBOOL AfxUnhookWindowCreate();
CLASS_DECL_AURA void AfxResetMsgCache();

// for backward compatibility to previous versions
#define _AfxHookWindowCreate    AfxHookWindowCreate
#define _AfxUnhookWindowCreate  AfxUnhookWindowCreate

#include "ios_implementation.h"
//#include "ios_dir.h"
#include "ios_factory_exchange.h"
#include "ios_window_draw.h"
//#include "ios_thread.h"
#include "ios_interaction_impl.h"
//#include "ios_os.h"
//#include "ios_port_forward.h"
//#include "ios_copydesk.h"
//#include "ios_crypto.h"
//#include "ios_ip_enum.h"

#define NULL_REF(class) (*((class *) NULL))
// xxx CLASS_DECL_AURA WNDPROC AfxGetAfxWndProc();
#define AfxWndProc (*AfxGetAfxWndProc())

#define IOS_WINDOW(pwnd) (dynamic_cast < ::ios::interaction_impl * > (dynamic_cast < ::user::interaction_impl * >(pwnd)))


CLASS_DECL_BASE void AfxProcessWndProcException(::exception::base*, signal_details * pobj);
CLASS_DECL_BASE void __cdecl __pre_translate_message(signal_details * pobj);

//#include "ios_printer.h"

//#include "ios_application.h"



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

