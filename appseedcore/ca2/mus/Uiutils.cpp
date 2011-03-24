/*****************************************************************************
*
*  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
*  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
*  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR
*  A PARTICULAR PURPOSE.
*
*  Copyright (C) 1993 - 1997 ca2. 
*
******************************************************************************
*
* UiUtils.C
*
* UI utility routines
*
*****************************************************************************/

//#pragma warning(disable:4756)

/*#define _INC_SHELLAPI
#include <windows.h>
#undef _INC_SHELLAPI

#include <shellapi.h>
#include <windowsx.h>
#include <mmsystem.h>*/
#include <stdafx.h> 
//#include "midiplyr.h"
#include <commdlg.h>
#include <commctrl.h>
#include <ctype.h>


//#include "MIDIPlyr.H"

//static char BCODE           gszErrFmt[]             = "%s:\n%s";
static char           gszErrFmt[]             = "%s:\n%s";
//static char BCODE           gszFace[]               = "arial";
//static char                 gszErrDescTxt[256];
static char                 gszErrDescTxt[256];
//static char                 gszErrCodeTxt[256];
static char                 gszErrCodeTxt[256];
//static char                 gszErrStr[512];
static char                 gszErrStr[512];

/*****************************************************************************
*
* Error
*
* Puts up a general error dialog
*
* hWnd                      - Handle of the owner ::ca::window
* nErrDesc                  - id into the string table of the message
* mmrc                      - Return code from MMSYSTEM or lower layer
*                             which caused the error.
*
* Just formats and puts up an error dialog.
*
* For convenience, all of the sequencer functions return MMSYSERR_ or
* MCIERR_ codes, so we can use mciGetErrorString instead of inventing
* our own error messages again.
*
*****************************************************************************/
/*
VOID Error(
    HWND                    hWnd,                             
    int                     nErrDesc,
    MMRESULT                mmrc)
{
    //load_string(System.m_hInstance, nErrDesc, gszErrDescTxt, sizeof(gszErrDescTxt));
    ::get_app()->load_string(nErrDesc, gszErrDescTxt, sizeof(gszErrDescTxt));
    mciGetErrorString(mmrc, gszErrCodeTxt, sizeof(gszErrCodeTxt));
    
    wsprintf(gszErrStr, gszErrFmt, (char *)gszErrDescTxt, (char *)gszErrCodeTxt);
    MessageBox(hWnd, gszErrStr, System.m_strAppName, MB_ICONEXCLAMATION|MB_OK);
}
*/

/*****************************************************************************
*
* MessagePump
*
* Process messages
*
* This function is called when, in certain cases, we need to wait for a
* ::ca::window callback to complete. Since callbacks are posted, not sent, we
* need to process messages while waiting.
*
* Note that some documentation refers to this operation as a 'directed
* yield' if messages are being processed for a particular ::ca::window. This
* is misleading; Yield() merely allows other tasks in the system to run
* and does absolutely nothing to the message queue.
*
*****************************************************************************/
VOID  MessagePump(
    VOID)
{
    MSG                     msg;

    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg); 
    }
}

