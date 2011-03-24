// This is ca2 API library.
// 
// 
//
// 
// 
// 
// 
// 

// Note: This header file contains useful classes that are documented only
//  in the ca2 API Technical Notes.  These classes may change from version to
//  version, so be prepared to change your code accordingly if you utilize
//  this header.  In the future, commonly used portions of this header
//  may be moved and officially documented.

#ifndef __AFXPRIV_H__
#define __AFXPRIV_H__

#pragma once

#ifdef _DEBUG
// Special _CLIENT_BLOCK type to identifiy CObjects.
#define _AFX_CLIENT_BLOCK (_CLIENT_BLOCK|(0xc0<<16))
#endif

#ifndef __AFXADV_H__
   #include "adv.h"
#endif

#ifndef _INC_MALLOC
   #include <malloc.h>
#endif


#ifdef _AFX_MINREBUILD
#pragma component(minrebuild, off)
#endif
#ifndef _AFX_FULLTYPEINFO
#pragma component(mintypeinfo, on)
#endif

#ifdef _AFX_PACKING
#pragma pack(push, _AFX_PACKING)
#endif

/////////////////////////////////////////////////////////////////////////////
// AFXPRIV - ca2 API Private Classes

// Implementation structures
struct AFX_SIZEPARENTPARAMS;    // control bar implementation
struct CAFX_CMDHANDLERINFO;      // Command routing implementation

// Classes declared in this file

   //::ca::graphics_sp
      class CPreviewDC;               // Virtual DC for print preview

   //command_target
      //base_wnd
         //::view
            class CPreviewView;     // Print preview ::view
      //frame_window
         class COleCntrFrameWnd;
         //CMiniFrameWnd
            class mini_dock_frame_window;

class CDockContext;                     // for dragging control bars

/////////////////////////////////////////////////////////////////////////////
// Global ID ranges (see Technical note TN020 for more details)

// 8000 -> FFFF command IDs (used for menu items, accelerators and controls)
#define IS_COMMAND_ID(nID)  ((nID) & 0x8000)

// 8000 -> DFFF : ::fontopus::user commands
// E000 -> EFFF : AFX commands and other things
// F000 -> FFFF : standard windows commands and other things etc
   // E000 -> E7FF standard commands
   // E800 -> E8FF control bars (first 32 are special)
   // E900 -> EEFF standard ::ca::window controls/components
   // EF00 -> EFFF SC_ menu help
   // F000 -> FFFF standard strings
#define ID_COMMAND_FROM_SC(sc)  (((sc - 0xF000) >> 4) + AFX_IDS_SCFIRST)

// 0000 -> 7FFF IDR range
// 0000 -> 6FFF : ::fontopus::user resources
// 7000 -> 7FFF : AFX (and standard windows) resources
// IDR ranges (NOTE: IDR_ values must be <32768)
#define ASSERT_VALID_IDR(nIDR) ASSERT((nIDR) != 0 && (nIDR) < 0x8000)

/////////////////////////////////////////////////////////////////////////////
// Context sensitive help support (see Technical note TN028 for more details)

// Help ID bases
#define HID_BASE_COMMAND    0x00010000UL        // ID and IDM
#define HID_BASE_RESOURCE   0x00020000UL        // IDR and IDD
#define HID_BASE_PROMPT     0x00030000UL        // IDP
#define HID_BASE_NCAREAS    0x00040000UL
#define HID_BASE_CONTROL    0x00050000UL        // IDC
#define HID_BASE_DISPATCH   0x00060000UL        // IDispatch help codes

/////////////////////////////////////////////////////////////////////////////
// Internal AFX Windows messages (see Technical note TN024 for more details)
// (0x0360 - 0x037F are reserved for ca2 API)

#define WM_QUERYAFXWNDPROC  0x0360  // lResult = 1 if processed by AfxWndProc
#define WM_SIZEPARENT       0x0361  // lParam = &AFX_SIZEPARENTPARAMS
#define WM_SETMESSAGESTRING 0x0362  // wParam = nIDS (or 0),
                           // lParam = lpszOther (or NULL)
#define WM_IDLEUPDATECMDUI  0x0363  // wParam == bDisableIfNoHandler
#define WM_INITIALUPDATE    0x0364  // (params unused) - sent to children
#define WM_COMMANDHELP      0x0365  // lResult = TRUE/FALSE,
                           // lParam = dwContext
#define WM_HELPHITTEST      0x0366  // lResult = dwContext,
                           // lParam = MAKELONG(x,y)
#define WM_EXITHELPMODE     0x0367  // (params unused)
#define WM_RECALCPARENT     0x0368  // force layout on frame ::ca::window
                           //  (only for inplace frame windows)
#define WM_SIZECHILD        0x0369  // special notify from COleResizeBar
                           // wParam = ID of child ::ca::window
                           // lParam = lpRectNew (new position/size)
#define WM_KICKIDLE         0x036A  // (params unused) causes idles to kick in
#define WM_QUERYCENTERWND   0x036B  // lParam = HWND to use as centering parent
#define WM_DISABLEMODAL     0x036C  // lResult = 0, disable during modal state
                           // lResult = 1, don't disable
#define WM_FLOATSTATUS      0x036D  // wParam combination of FS_* flags below

// WM_ACTIVATETOPLEVEL is like WM_ACTIVATEAPP but works with hierarchies
//   of mixed processes (as is the case with OLE in-place activation)
#define WM_ACTIVATETOPLEVEL 0x036E  // wParam = nState (like WM_ACTIVATE)
                           // lParam = pointer to HWND[2]
                           //  lParam[0] = hWnd getting WM_ACTIVATE
                           //  lParam[1] = hWndOther

#define WM_RESERVED_036F   0x036F  // was WM_QUERY3DCONTROLS (now not used)

// Note: Messages 0x0370, 0x0371, and 0x372 were incorrectly used by
//  some versions of Windows.  To remain compatible, ca2 API does not
//  use messages in that range.
#define WM_RESERVED_0370    0x0370
#define WM_RESERVED_0371    0x0371
#define WM_RESERVED_0372    0x0372

// WM_SOCKET_NOTIFY and WM_SOCKET_DEAD are used internally by ca2 API's
// Windows sockets implementation.  For more information, see sockcore.cpp
#define WM_SOCKET_NOTIFY    0x0373
#define WM_SOCKET_DEAD      0x0374

// same as WM_SETMESSAGESTRING except not popped if IsTracking()
#define WM_POPMESSAGESTRING 0x0375

// WM_HELPPROMPTADDR is used internally to get the address of 
//   m_dwPromptContext from the associated frame ::ca::window. This is used
//   during message boxes to setup for F1 help while that msg box is
//   displayed. lResult is the address of m_dwPromptContext.
#define WM_HELPPROMPTADDR   0x0376

// Constants used in DLGINIT resources for OLE control containers
// NOTE: These are NOT real Windows messages they are simply tags
// used in the control resource and are never used as 'messages'
#define WM_OCC_LOADFROMSTREAM           0x0376
#define WM_OCC_LOADFROMSTORAGE          0x0377
#define WM_OCC_INITNEW                  0x0378
#define WM_OCC_LOADFROMSTREAM_EX        0x037A
#define WM_OCC_LOADFROMSTORAGE_EX       0x037B

// Marker used while rearranging the message queue
#define WM_QUEUE_SENTINEL   0x0379

// Note: Messages 0x037C - 0x37E reserved for future ca2 API use.
#define WM_RESERVED_037C    0x037C
#define WM_RESERVED_037D    0x037D
#define WM_RESERVED_037E    0x037E

// WM_FORWARDMSG - used by _template to forward a message to another ::ca::window for processing
//   WPARAM - DWORD dwUserData - defined by ::fontopus::user
//   LPARAM - LPMSG pMsg - a pointer to the MSG structure
//   return value - 0 if the message was not processed, nonzero if it was
#define WM_FORWARDMSG      0x037F

// like ON_MESSAGE but no return value
#define ON_MESSAGE_VOID(message, memberFxn) \
   { message, 0, 0, 0, AfxSig_vv, \
      (AFX_PMSG)(AFX_PMSGW)(void (AFX_MSG_CALL base_wnd::*)(void))&memberFxn },

// special struct for WM_SIZEPARENT
struct AFX_SIZEPARENTPARAMS
{
   HDWP hDWP;       // handle for DeferWindowPos
   RECT rect;       // parent client rectangle (trim as appropriate)
   SIZE sizeTotal;  // total size on each side as layout proceeds
   BOOL bStretch;   // should stretch to fill all space
};

// flags for wParam in the WM_FLOATSTATUS message
enum {  FS_SHOW = 0x01, FS_HIDE = 0x02,
      FS_ACTIVATE = 0x04, FS_DEACTIVATE = 0x08,
      FS_ENABLE = 0x10, FS_DISABLE = 0x20,
      FS_SYNCACTIVE = 0x40 };

CLASS_DECL_ca2api00000001 void AfxRepositionWindow(AFX_SIZEPARENTPARAMS* lpLayout,
   Ex1VirtualGuie * hWnd, LPCRECT lpRect);

/////////////////////////////////////////////////////////////////////////////
// Implementation of command routing

struct CAFX_CMDHANDLERINFO
{
   command_target* pTarget;
   void (AFX_MSG_CALL command_target::*pmf)(void);
};

/////////////////////////////////////////////////////////////////////////////
// Robust file save support
// opens a temp file if mode_create specified and enough free space
// renaming, etc occurs automatically if everything succeeds

class CMirrorFile : public ex1::filesp
{
// Implementation
public:
   virtual void Abort();
   virtual void close();
   virtual BOOL open(LPCTSTR lpszFileName, UINT nOpenFlags,
      ex1::file_exception_sp* pError = NULL);

protected:
   string m_strMirrorName;
};

/////////////////////////////////////////////////////////////////////////////
// Implementation of PrintPreview

class CLASS_DECL_ca2api00000001 CPreviewDC : public ::ca::graphics_sp
{
   

public:
   virtual void SetAttribDC(HDC hDC);  // Set the Attribute DC
   virtual void SetOutputDC(HDC hDC);

   virtual void ReleaseOutputDC();

// Constructors
   CPreviewDC();

// Implementation
public:
   virtual ~CPreviewDC();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   void SetScaleRatio(int nNumerator, int nDenominator);
   void SetTopLeftOffset(size top_left);
   void ClipToPage();

   // These conversion functions can be used without an output DC

   void PrinterDPtoScreenDP(LPPOINT lpPoint) const;

// Device-Context Functions
   virtual int SaveDC();
   virtual BOOL RestoreDC(int nSavedDC);

public:
   virtual ::ca::graphics_object* SelectStockObject(int nIndex);
   virtual ::ca::font* SelectObject(::ca::font* pFont);

// Drawing-Attribute Functions
   virtual COLORREF SetBkColor(COLORREF crColor);
   virtual COLORREF SetTextColor(COLORREF crColor);

// Mapping Functions
   virtual int SetMapMode(int nMapMode);
   virtual point SetViewportOrg(int x, int y);
   virtual point OffsetViewportOrg(int nWidth, int nHeight);
   virtual size SetViewportExt(int x, int y);
   virtual size ScaleViewportExt(int xNum, int xDenom, int yNum, int yDenom);
   virtual size SetWindowExt(int x, int y);
   virtual size ScaleWindowExt(int xNum, int xDenom, int yNum, int yDenom);

// Text Functions
   virtual BOOL TextOut(int x, int y, LPCTSTR lpszString, int nCount);
   virtual BOOL ExtTextOut(int x, int y, UINT nOptions, LPCRECT lpRect,
            LPCTSTR lpszString, UINT nCount, LPINT lpDxWidths);
   virtual size TabbedTextOut(int x, int y, LPCTSTR lpszString, int nCount,
            int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);
   virtual int _AFX_FUNCNAME(DrawText)(LPCTSTR lpszString, int nCount, LPRECT lpRect,
            UINT nFormat);
   virtual int _AFX_FUNCNAME(DrawTextEx)(LPTSTR lpszString, int nCount, LPRECT lpRect,
            UINT nFormat, LPDRAWTEXTPARAMS lpDTParams);
#pragma push_macro("DrawText")
#pragma push_macro("DrawTextEx")
#undef DrawText
#undef DrawTextEx
   int DrawText(LPCTSTR lpszString, int nCount, LPRECT lpRect,
            UINT nFormat)
   {
      return _AFX_FUNCNAME(DrawText)(lpszString, nCount, lpRect, nFormat);
   }
   int DrawTextEx(LPTSTR lpszString, int nCount, LPRECT lpRect,
            UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
   {
      return _AFX_FUNCNAME(DrawTextEx)(lpszString, nCount, lpRect, nFormat, lpDTParams);
   }
#pragma pop_macro("DrawText")
#pragma pop_macro("DrawTextEx")
   virtual BOOL GrayString(::ca::brush* pBrush,
            BOOL (CALLBACK* lpfnOutput)(HDC, LPARAM, int),
               LPARAM lpData, int nCount,
               int x, int y, int nWidth, int nHeight);

// Printer Escape Functions
   virtual int Escape(int nEscape, int nCount, LPCSTR lpszInData, LPVOID lpOutData);

// Implementation
protected:
   void MirrorMappingMode(BOOL bCompute);
   void MirrorViewportOrg();
   void MirrorFont();
   void MirrorAttributes();

   size ComputeDeltas(int& x, __in_z LPCTSTR lpszString, UINT& nCount, __in BOOL bTabbed,
               __in UINT nTabStops, __in_ecount(nTabStops) LPINT lpnTabStops, __in int nTabOrigin,
               __out_z LPTSTR lpszOutputString, int* pnDxWidths, int& nRightFixup);

protected:
   int m_nScaleNum;    // Scale ratio Numerator
   int m_nScaleDen;    // Scale ratio Denominator
   int m_nSaveDCIndex; // DC Save index when Screen DC Attached
   int m_nSaveDCDelta; // delta between Attrib and output restore indices
   size m_sizeTopLeft;// Offset for top left corner of page
   HFONT m_hFont;      // font selected into the screen DC (NULL if none)
   HFONT m_hPrinterFont; // font selected into the print DC

   size m_sizeWinExt; // cached ::ca::window extents computed for screen
   size m_sizeVpExt;  // cached viewport extents computed for screen
};


// Zoom States
#define ZOOM_OUT    0
#define ZOOM_MIDDLE 1
#define ZOOM_IN     2

/////////////////////////////////////////////////////////////////////////////
// mirroring support

// some mirroring stuff will be in wingdi.h someday
#ifndef LAYOUT_LTR
#define LAYOUT_LTR                         0x00000000   
#endif


struct AFX_NOTIFY
{
   LRESULT* pResult;
   NMHDR* pNMHDR;
};


////////////////////////////////////////////////////////////////////////////
// other global state
class CPushRoutingFrame
{
protected:
   frame_window* pOldRoutingFrame;
   _AFX_THREAD_STATE* pThreadState;
   CPushRoutingFrame* pOldPushRoutingFrame;

public:
   explicit CPushRoutingFrame(frame_window* pNewRoutingFrame)
   { 
      pThreadState = AfxGetThreadState();
     pOldPushRoutingFrame = pThreadState->m_pPushRoutingFrame;
      pOldRoutingFrame = pThreadState->m_pRoutingFrame;
      pThreadState->m_pRoutingFrame = pNewRoutingFrame;
     pThreadState->m_pPushRoutingFrame = this;
   }
   ~CPushRoutingFrame()
   { 
     if (pThreadState != NULL)
     {
       ASSERT( pThreadState->m_pPushRoutingFrame == this );
       pThreadState->m_pRoutingFrame = pOldRoutingFrame;
       pThreadState->m_pPushRoutingFrame = pOldPushRoutingFrame;
     }
   }
   void Pop()
   {
     ENSURE( pThreadState != NULL );
     ASSERT( pThreadState->m_pPushRoutingFrame == this );
     pThreadState->m_pRoutingFrame = pOldRoutingFrame;
     pThreadState->m_pPushRoutingFrame = pOldPushRoutingFrame;
     pThreadState = NULL;
   }
};

/////////////////////////////////////////////////////////////////////////////
// Global implementation helpers

// ::ca::window creation hooking
CLASS_DECL_ca2api00000001 void AfxHookWindowCreate(Ex1VirtualGuie * pWnd);
CLASS_DECL_ca2api00000001 BOOL AfxUnhookWindowCreate();
CLASS_DECL_ca2api00000001 void AfxResetMsgCache();

// for backward compatibility to previous versions
#define _AfxHookWindowCreate    AfxHookWindowCreate
#define _AfxUnhookWindowCreate  AfxUnhookWindowCreate

// string helpers
//CLASS_DECL_ca2api00000001 void AfxSetWindowText(Ex1VirtualGuie * hWndCtrl, LPCTSTR lpszNew);
//CLASS_DECL_ca2api00000001 int AfxLoadString(__in UINT nIDS, __out_ecount_part_z(nMaxBuf, return + 1) LPSTR lpszBuf, __in UINT nMaxBuf = 256);
//CLASS_DECL_ca2api00000001 int AfxLoadString(__in UINT nIDS, __out_ecount_part_z(nMaxBuf, return + 1) LPWSTR lpszBuf, __in UINT nMaxBuf = 256);

HDC AfxCreateDC(HGLOBAL hDevNames, HGLOBAL hDevMode);

//CLASS_DECL_ca2api00000001 void AfxGetModuleShortFileName(HINSTANCE hInst, string & strShortName);

// Failure dialog helpers
CLASS_DECL_ca2api00000001 void AfxFailMaxChars(CDataExchange* pDX, int nChars);
CLASS_DECL_ca2api00000001 void AfxFailRadio(CDataExchange* pDX);

#ifndef __AFXCONV_H__
#include "conv.h"
#endif

/////////////////////////////////////////////////////////////////////////////

#ifdef _AFX_PACKING
#pragma pack(pop)
#endif

#ifdef _AFX_MINREBUILD
#pragma component(minrebuild, on)
#endif
#ifndef _AFX_FULLTYPEINFO
#pragma component(mintypeinfo, off)
#endif

#endif // __AFXPRIV_H__

/////////////////////////////////////////////////////////////////////////////

#ifndef __AFXPRIV2_H__
#include "priv2.h"
#endif
