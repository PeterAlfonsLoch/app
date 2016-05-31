#pragma once

#define AfxDeferRegisterClass(fClass) AfxEndDeferRegisterClass(fClass)

CLASS_DECL_ACE WINBOOL AfxEndDeferRegisterClass(LONG fToRegister, const char ** ppszClass);


// Temporary ::collection::map management (locks temp ::collection::map on current thread)
//CLASS_DECL_ACE void AfxLockTempMaps(::ace::application * papp);
//CLASS_DECL_ACE WINBOOL AfxUnlockTempMaps(::ace::application * papp, WINBOOL bDeleteTemps = TRUE);



// from wincore.cpp
extern CLASS_DECL_ACE const char _afxWnd[];           // simple child windows/controls
extern CLASS_DECL_ACE const char _afxWndControlBar[]; // controls with gray backgrounds
extern CLASS_DECL_ACE const char _afxWndMDIFrame[];
extern CLASS_DECL_ACE const char _afxWndFrameOrView[];
extern CLASS_DECL_ACE const char _afxWndOleControl[];


/////////////////////////////////////////////////////////////////////////////
// Special helpers

CLASS_DECL_ACE void AfxCancelModes(oswindow hWndRcvr);
CLASS_DECL_ACE WINBOOL AfxHelpEnabled();  // determine if ID_HELP handler exists
CLASS_DECL_ACE WINBOOL AfxCustomLogFont(UINT nIDS, LOGFONT* pLogFont);
CLASS_DECL_ACE WINBOOL AfxGetPropSheetFont(string & strFace, WORD& wSize, WINBOOL bWizard);

CLASS_DECL_ACE WINBOOL _AfxIsComboBoxControl(oswindow hWnd, UINT nStyle);
CLASS_DECL_ACE WINBOOL _AfxCheckCenterDialog(const char * lpszResource);
CLASS_DECL_ACE WINBOOL _AfxCompareClassName(oswindow hWnd, const char * lpszClassName);
CLASS_DECL_ACE oswindow _AfxChildWindowFromPoint(oswindow, POINT);

// for determining version of COMCTL32.DLL
#define VERSION_ANDROID4    MAKELONG(0, 4)
#define VERSION_IE3             MAKELONG(70, 4)
#define VERSION_IE4             MAKELONG(71, 4)
#define VERSION_IE401   MAKELONG(72, 4)
#define VERSION_6      MAKELONG(0, 6)
extern int _afxComCtlVersion;
DWORD _AfxGetComCtlVersion();
