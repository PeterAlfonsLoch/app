#pragma once


#include "aura/aura/node/macos/macos.h"


string get_error_message(DWORD dwError);

::aura::application *     mac_instantiate_application(::aura::application * pappSystem, const char * pszId);

// window creation hooking
CLASS_DECL_AXIS void AfxHookWindowCreate(::user::interaction * pWnd);
CLASS_DECL_AXIS WINBOOL AfxUnhookWindowCreate();
CLASS_DECL_AXIS void AfxResetMsgCache();

// for backward compatibility to previous versions
#define _AfxHookWindowCreate    AfxHookWindowCreate
#define _AfxUnhookWindowCreate  AfxUnhookWindowCreate

#include "macos_factory_exchange.h"
#include "macos_window_draw.h"
#include "macos_interaction_impl.h"
#include "macos_copydesk.h"



// xxx CLASS_DECL_AXIS WNDPROC AfxGetAfxWndProc();
#define AfxWndProc (*AfxGetAfxWndProc())

#define MAC_WINDOW(pwnd) (dynamic_cast < ::macos::interaction_impl * > (dynamic_cast < ::user::interaction_impl * >(pwnd)))


CLASS_DECL_AXIS void AfxProcessWndProcException(::exception::base*, signal_details * pobj);
CLASS_DECL_AXIS void __cdecl __pre_translate_message(signal_details * pobj);
#include "macos_printer.h"
#include "macos_message_queue.h"



int32_t CLASS_DECL_AXIS __mac_main(int32_t argc, char * argv[]);




#include "round_window.h"




