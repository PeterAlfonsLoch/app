#pragma once


// from wincore.cpp
extern CLASS_DECL_AURA const char _afxWnd[];           // simple child windows/controls
extern CLASS_DECL_AURA const char _afxWndControlBar[]; // controls with gray backgrounds
extern CLASS_DECL_AURA const char _afxWndMDIFrame[];
extern CLASS_DECL_AURA const char _afxWndFrameOrView[];
extern CLASS_DECL_AURA const char _afxWndOleControl[];


/////////////////////////////////////////////////////////////////////////////
// Special helpers

CLASS_DECL_AURA void AfxCancelModes(oswindow hWndRcvr);
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
extern int _afxComCtlVersion;
DWORD _AfxGetComCtlVersion();
