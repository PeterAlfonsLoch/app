#pragma once


#include "aura/node/ansios/ansios.h"


string get_error_message(DWORD dwError);

sp(::aura::application)     linux_instantiate_application(sp(::aura::application) pappSystem, const char * pszId);

/////////////////////////////////////////////////////////////////////////////
// explicit initialization for general purpose classes

//CLASS_DECL_AURA WINBOOL AfxInitialize(WINBOOL bDLL = FALSE, DWORD dwVersion = _MFC_VER);
CLASS_DECL_AURA WINBOOL AfxInitialize(WINBOOL bDLL = FALSE, DWORD dwVersion = 0);

/////////////////////////////////////////////////////////////////////////////
// stop on a specific primitive::memory request

// Debugger hook on specified allocation request - Obsolete
CLASS_DECL_AURA void AfxSetAllocStop(LONG lRequestNumber);

// Return TRUE if primitive::memory is sane or print out what is wrong
CLASS_DECL_AURA bool __check_memory();

// Return TRUE if valid primitive::memory block of nBytes
CLASS_DECL_AURA WINBOOL AfxIsMemoryBlock(const void * p, UINT nBytes,
   LONG* plRequestNumber = NULL);

// helper routines for non-C++ EH implementations
// for THROW_LAST auto-delete backward compatiblity
CLASS_DECL_AURA void AfxThrowLastCleanup();

// other out-of-line helper functions
CLASS_DECL_AURA void AfxTryCleanup();



#pragma once


namespace linux
{


   class thread;

   class linux
   {
      int32_t function();
   };



} // namespace linux



// Placed on frame for EXCEPTION linkage, or ::exception::aura cleanup
struct CLASS_DECL_AURA __exception_link
{
   __exception_link * m_pLinkPrev;    // previous top, next in handler chain
   ::exception::base * m_pException;   // current exception (NULL in try block)

   __exception_link();       // for initialization and linking
   ~__exception_link()       // for cleanup and unlinking
      {
          //__try_cleanup();
      };
};

// Exception global state - never Ķaccess directly
struct CLASS_DECL_AURA __EXCEPTION_CONTEXT
{
   __exception_link* m_pLinkTop;

   // Note: most of the exception context is now in the __exception_link
};


CLASS_DECL_AURA MESSAGE * __get_current_message();


CLASS_DECL_AURA sp(::aura::application)  __get_app();
CLASS_DECL_AURA sp(::user::interaction) __get_main_window();
//CLASS_DECL_AURA HINSTANCE CLASS_DECL_AURA System.m_hInstance;
CLASS_DECL_AURA const char * __get_app_name();





// from wincore.cpp
extern CLASS_DECL_AURA const char _afxWnd[];           // simple child windows/controls
extern CLASS_DECL_AURA const char _afxWndControlBar[]; // controls with gray backgrounds
extern CLASS_DECL_AURA const char _afxWndMDIFrame[];
extern CLASS_DECL_AURA const char _afxWndFrameOrView[];
extern CLASS_DECL_AURA const char _afxWndOleControl[];


/////////////////////////////////////////////////////////////////////////////
// Special helpers

CLASS_DECL_AURA void AfxcancelModes(oswindow hWndRcvr);
CLASS_DECL_AURA WINBOOL AfxHelpEnabled();  // determine if ID_HELP handler exists
CLASS_DECL_AURA WINBOOL AfxCustomLogFont(UINT nIDS, LOGFONT* pLogFont);
CLASS_DECL_AURA WINBOOL AfxGetPropSheetFont(string & strFace, WORD& wSize, WINBOOL bWizard);

CLASS_DECL_AURA WINBOOL _AfxIsComboBoxControl(oswindow hWnd, UINT nStyle);
CLASS_DECL_AURA WINBOOL _AfxCheckCenterDialog(const char * lpszResource);
CLASS_DECL_AURA WINBOOL _AfxCompareClassName(oswindow hWnd, const char * lpszClassName);
CLASS_DECL_AURA oswindow _AfxChildWindowFromPoint(oswindow, POINT);

// for determining version of COMCTL32.DLL
#define VERSION_WIN4    MAKELONG(0, 4)
#define VERSION_IE3             MAKELONG(70, 4)
#define VERSION_IE4             MAKELONG(71, 4)
#define VERSION_IE401   MAKELONG(72, 4)
#define VERSION_6      MAKELONG(0, 6)
extern int32_t _afxComCtlVersion;
DWORD _AfxGetComCtlVersion();
#include "linux_factory_exchange.h"
#include "linux_thread.h"
#include "linux_os.h"

#define NULL_REF(class) (*((class *) NULL))

#define LNX_THREAD(pthread) (dynamic_cast < ::linux::thread * > (dynamic_cast < ::thread * >(pthread)))

#include "linux_shell.h"




CLASS_DECL_AURA void AfxProcessWndProcException(::exception::base*, ::signal_details * pobj);
CLASS_DECL_AURA void __cdecl __pre_translate_message(::signal_details * pobj);


#include "linux_application.h"



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



int32_t CLASS_DECL_AURA __linux_main(int32_t argc, char * argv[]);


CLASS_DECL_AURA void vfxThrowFileException(sp(::aura::application) papp, int32_t cause, LONG lOsError, const char * lpszFileName = NULL);


#include "linux_internal.h"








CLASS_DECL_AURA MESSAGE * __get_current_message();


CLASS_DECL_AURA sp(::aura::application)  __get_app();
CLASS_DECL_AURA sp(::user::interaction) __get_main_window();
//CLASS_DECL_AURA HINSTANCE CLASS_DECL_AURA System.m_hInstance;
CLASS_DECL_AURA const char * __get_app_name();


