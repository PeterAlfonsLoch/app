// This is ca2 API library.
//
//
//
//
//
//
//
//

#include "StdAfx.h"
#include <malloc.h>



/////////////////////////////////////////////////////////////////////////////
// Cached system metrics, etc

__DATADEF AUX_DATA afxData;

// Initialization code
AUX_DATA::AUX_DATA()
{
   try
   {
   // Cache various target platform version information
   DWORD dwVersion = ::GetVersion();
   bWin95 = (dwVersion & 0x80000000) != 0;

   // Cached system metrics (updated in ::ca::window::OnWinIniChange)
   UpdateSysMetrics();

   // Cached system values (updated in ::ca::window::OnSysColorChange)
   hbrBtnFace = NULL;
   UpdateSysColors();

   // Standard cursors
   hcurWait = ::LoadCursor(NULL, IDC_WAIT);
   hcurArrow = ::LoadCursor(NULL, IDC_ARROW);
   ASSERT(hcurWait != NULL);
   ASSERT(hcurArrow != NULL);
   hcurHelp = NULL;    // loaded on demand

   // cxBorder2 and cyBorder are 2x borders for Win4
   cxBorder2 = CX_BORDER*2;
   cyBorder2 = CY_BORDER*2;

   // allocated on demand
   hbmMenuDot = NULL;
   hcurHelp = NULL;
   }
   catch(...)
   {
   }
}


// Termination code
AUX_DATA::~AUX_DATA()
{
   // clean up objects we don't actually create
   //AfxDeleteObject((HGDIOBJ*)&hbmMenuDot);
}


void AUX_DATA::UpdateSysColors()
{
   clrBtnFace = ::GetSysColor(COLOR_BTNFACE);
   clrBtnShadow = ::GetSysColor(COLOR_BTNSHADOW);
   clrBtnHilite = ::GetSysColor(COLOR_BTNHIGHLIGHT);
   clrBtnText = ::GetSysColor(COLOR_BTNTEXT);
   clrWindowFrame = ::GetSysColor(COLOR_WINDOWFRAME);

   hbrBtnFace = ::GetSysColorBrush(COLOR_BTNFACE);
   ASSERT(hbrBtnFace != NULL);
   hbrWindowFrame = ::GetSysColorBrush(COLOR_WINDOWFRAME);
   ASSERT(hbrWindowFrame != NULL);
}

void AUX_DATA::UpdateSysMetrics()
{
   // System metrics
   cxIcon = GetSystemMetrics(SM_CXICON);
   cyIcon = GetSystemMetrics(SM_CYICON);

   // System metrics which depend on subsystem version
   afxData.cxVScroll = GetSystemMetrics(SM_CXVSCROLL) + CX_BORDER;
   afxData.cyHScroll = GetSystemMetrics(SM_CYHSCROLL) + CY_BORDER;

   // Device metrics for screen
   HDC hDCScreen = GetDC(NULL);
   ASSERT(hDCScreen != NULL);
   cxPixelsPerInch = GetDeviceCaps(hDCScreen, LOGPIXELSX);
   cyPixelsPerInch = GetDeviceCaps(hDCScreen, LOGPIXELSY);
   ReleaseDC(NULL, hDCScreen);
}

/////////////////////////////////////////////////////////////////////////////
