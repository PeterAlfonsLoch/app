#pragma once


#ifdef SetWindowLongPtrA
#undef SetWindowLongPtrA
inline LONG_PTR SetWindowLongPtrA( HWND hWnd, int nIndex, LONG_PTR dwNewLong )
{
   return( ::SetWindowLongA( hWnd, nIndex, LONG( dwNewLong ) ) );
}
#endif

#ifdef SetWindowLongPtrW
#undef SetWindowLongPtrW
inline LONG_PTR SetWindowLongPtrW( HWND hWnd, int nIndex, LONG_PTR dwNewLong )
{
   return( ::SetWindowLongW( hWnd, nIndex, LONG( dwNewLong ) ) );
}
#endif

#ifdef GetWindowLongPtrA
#undef GetWindowLongPtrA
inline LONG_PTR GetWindowLongPtrA( HWND hWnd, int nIndex )
{
   return( ::GetWindowLongA( hWnd, nIndex ) );
}
#endif

#ifdef GetWindowLongPtrW
#undef GetWindowLongPtrW
inline LONG_PTR GetWindowLongPtrW( HWND hWnd, int nIndex )
{
   return( ::GetWindowLongW( hWnd, nIndex ) );
}
#endif

/////////////////////////////////////////////////////////////////////////////
// Auxiliary System/Screen metrics
/*
struct CLASS_DECL_ca AUX_DATA
{
   // system metrics
   int cxVScroll, cyHScroll;
   int cxIcon, cyIcon;

   int cxBorder2, cyBorder2;

   // device metrics for screen
   int cxPixelsPerInch, cyPixelsPerInch;

   // convenient system color
   HBRUSH hbrWindowFrame;
   HBRUSH hbrBtnFace;

   // color values of system colors used for simple_toolbar
   COLORREF clrBtnFace, clrBtnShadow, clrBtnHilite;
   COLORREF clrBtnText, clrWindowFrame;

   // standard cursors
   HCURSOR hcurWait;
   HCURSOR hcurArrow;
   HCURSOR hcurHelp;       // cursor used in Shift+F1 help

   // special GDI objects allocated on demand
   HFONT   hStatusFont;
   HFONT   hToolTipsFont;
   HBITMAP hbmMenuDot;

   // other system information
   BOOL    bWin95;         // TRUE if Windows 95 (not NT)
   BOOL    bWin4;

// Implementation
   AUX_DATA();
   ~AUX_DATA();
   void UpdateSysColors();
   void UpdateSysMetrics();
};

extern CLASS_DECL_ca AUX_DATA afxData;*/




// Note: afxData.cxBorder and afxData.cyBorder aren't used anymore
#define CX_BORDER   1
#define CY_BORDER   1

// states for Shift+F1 hep mode
#define HELP_INACTIVE   0   // not in Shift+F1 help mode (must be 0)
#define HELP_ACTIVE     1   // in Shift+F1 help mode (non-zero)
#define HELP_ENTERING   2   // entering Shift+F1 help mode (non-zero)

/////////////////////////////////////////////////////////////////////////////
// Window class names and other ::ca::window creation support


#define AFX_WND_REG                                             0x00001
#define AFX_WNDCONTROLBAR_REG                   0x00002
#define AFX_WNDMDIFRAME_REG                             0x00004
#define AFX_WNDFRAMEORVIEW_REG                  0x00008
#define AFX_WNDCOMMCTLS_REG                             0x00010 // means all original Win95
#define AFX_WNDOLECONTROL_REG                   0x00020
#define AFX_WNDCOMMCTL_UPDOWN_REG       0x00040 // these are original Win95
#define AFX_WNDCOMMCTL_TREEVIEW_REG     0x00080
#define AFX_WNDCOMMCTL_TAB_REG                  0x00100
#define AFX_WNDCOMMCTL_PROGRESS_REG             0x00200
#define AFX_WNDCOMMCTL_LISTVIEW_REG         0x00400
#define AFX_WNDCOMMCTL_HOTKEY_REG           0x00800
#define AFX_WNDCOMMCTL_BAR_REG              0x01000
#define AFX_WNDCOMMCTL_ANIMATE_REG              0x02000
#define AFX_WNDCOMMCTL_INTERNET_REG             0x04000 // these are new in IE4
#define AFX_WNDCOMMCTL_COOL_REG             0x08000
#define AFX_WNDCOMMCTL_USEREX_REG       0x10000
#define AFX_WNDCOMMCTL_DATE_REG             0x20000
#define AFX_WNDCOMMCTL_LINK_REG             0x40000      // new in IE6

#define AFX_WIN95CTLS_MASK                              0x03FC0 // UPDOWN -> ANIMATE
#define AFX_WNDCOMMCTLSALL_REG                  0x7C010 // COMMCTLS|INTERNET|COOL|USEREX|DATE|LINK
#define AFX_WNDCOMMCTLSNEW_REG                  0x7C000 // INTERNET|COOL|USEREX|DATE


// ca2 API has its own version of the TOOLINFO structure containing the
// the Win95 base version of the structure. Since ca2 API targets Win95 base,
// we need this structure so calls into that old library don't fail.

typedef struct tagAFX_OLDTOOLINFO {
   UINT cbSize;
   UINT uFlags;
   HWND hwnd;
   UINT uId;
   RECT rect;
   HINSTANCE hinst;
   LPTSTR lpszText;
} AFX_OLDTOOLINFO;

// special AFX ::ca::window class name mangling


#define AFX_WNDCLASS(s)    "ca2" _T(s)
#define AFX_WND             AFX_WNDCLASS("Wnd")
#define AFX_WNDCONTROLBAR   AFX_WNDCLASS("ControlBar")
#define AFX_WNDMDIFRAME     AFX_WNDCLASS("MDIFrame")
#define AFX_WNDFRAMEORVIEW  AFX_WNDCLASS("FrameOrView")
#define AFX_WNDOLECONTROL   AFX_WNDCLASS("OleControl")

// dialog/commdlg hook procs
CLASS_DECL_ca INT_PTR CALLBACK AfxDlgProc(HWND, UINT, WPARAM, LPARAM);
CLASS_DECL_ca UINT_PTR CALLBACK _AfxCommDlgProc(HWND hWnd, UINT, WPARAM, LPARAM);

// support for standard dialogs
extern UINT _afxMsgSETRGB;
typedef UINT_PTR (CALLBACK* COMMDLGPROC)(HWND, UINT, WPARAM, LPARAM);

// conversion helpers
//int AFX_CDECL _wcstombsz(char* mbstr, const wchar_t* wcstr, size_t count);
//int AFX_CDECL _mbstowcsz(wchar_t* wcstr, const char* mbstr, size_t count);

/////////////////////////////////////////////////////////////////////////////
// Extended dialog templates (new in Win95)

typedef struct
{
   WORD dlgVer;
   WORD signature;
   DWORD helpID;
   DWORD exStyle;
   DWORD style;
   WORD cDlgItems;
   short x;
   short y;
   short cx;
   short cy;
} DLGTEMPLATEEX;

typedef struct
{
   DWORD helpID;
   DWORD exStyle;
   DWORD style;
   short x;
   short y;
   short cx;
   short cy;
   DWORD id;
} DLGITEMTEMPLATEEX;

/////////////////////////////////////////////////////////////////////////////
// Special helpers

CLASS_DECL_ca ::user::interaction * AfxGetParentOwner(::user::interaction * hWnd);
CLASS_DECL_ca BOOL AfxIsDescendant(::user::interaction * hWndParent, ::user::interaction * hWndChild);


/*// UNICODE/MBCS abstractions
#ifdef _MBCS
   extern CLASS_DECL_ca const BOOL _afxDBCS;
#else
   #define _afxDBCS FALSE
#endif
   */
// determine number of elements in an base_array (not bytes)
#ifndef _countof
#define _countof(base_array) (sizeof(base_array)/sizeof(base_array[0]))
#endif

#ifndef _AFX_PORTABLE
int AFX_CDECL AfxCriticalNewHandler(size_t nSize);
#endif


/////////////////////////////////////////////////////////////////////////////
// locale-invariant comparison helpers till CRT gets that support
inline int AfxInvariantStrICmp(const char *pszLeft, const char *pszRight)
{
#ifdef WINDOWS
    return ::CompareStringA(MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT),
                            NORM_IGNORECASE,
                            pszLeft,
                            -1,
                            pszRight,
                            -1)-CSTR_EQUAL;
#else
   return stricmp_dup(pszLeft, pszRight);
#endif
}

inline int AfxInvariantStrICmp(const wchar_t *pwszLeft, const wchar_t *pwszRight)
{
#ifdef WINDOWS
    return ::CompareStringW(MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT),
                            NORM_IGNORECASE,
                            pwszLeft,
                            -1,
                            pwszRight,
                            -1)-CSTR_EQUAL;
#else
   return wcsicmp_dup(pwszLeft, pwszRight);
#endif
}


/////////////////////////////////////////////////////////////////////////////
// static exceptions

extern not_supported_exception   _simpleNotSupportedException;
extern memory_exception          _simpleMemoryException;
extern user_exception            _simpleUserException;
extern resource_exception _simpleResourceException;

/////////////////////////////////////////////////////////////////////////////
// useful message ranges

#define WM_SYSKEYFIRST  WM_SYSKEYDOWN
#define WM_SYSKEYLAST   WM_SYSDEADCHAR

#define WM_NCMOUSEFIRST WM_NCMOUSEMOVE
#define WM_NCMOUSELAST  WM_NCMBUTTONDBLCLK


/////////////////////////////////////////////////////////////////////////////
// Portability abstractions

#define _AfxSetDlgCtrlID(hWnd, nID)     SetWindowLong(hWnd, GWL_ID, nID)
#define _AfxSetDlgCtrlID_(hWnd, nID)     hWnd->SetWindowLong(GWL_ID, nID)
#define _AfxGetDlgCtrlID(hWnd)          ((UINT)(WORD)::GetDlgCtrlID(hWnd))
#define _AfxGetDlgCtrlID_(hWnd)          ((UINT)(WORD)hWnd->GetDlgCtrlId())

// misc helpers
CLASS_DECL_ca void AfxGetRoot(const char * lpszPath, string & strRoot);

#ifndef _AFX_NO_OLE_SUPPORT
class CLASS_DECL_ca AFX_COM
{
public:
   HRESULT CreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter,
      REFIID riid, LPVOID* ppv);
   HRESULT GetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv);
};

CLASS_DECL_ca string AfxStringFromCLSID(REFCLSID rclsid);
CLASS_DECL_ca BOOL AfxGetInProcServer(const char * lpszCLSID, string & str);
#endif // _AFX_NO_OLE_SUPPORT

#define NULL_TLS ((DWORD)-1)

/////////////////////////////////////////////////////////////////////////////
// Message ::collection::map and message dispatch



/////////////////////////////////////////////////////////////////////////////
// Debugging/Tracing helpers

#ifdef _DEBUG
   CLASS_DECL_ca BOOL _AfxCheckDialogTemplate(const char * lpszResource, BOOL bInvisibleChild);
#endif





