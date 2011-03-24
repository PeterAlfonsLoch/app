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
* Debug.C
*
* Debug output routines
*
*****************************************************************************/

/*#include <windows.h>
#include <mmsystem.h>  */

#include "StdAfx.h"

#include "gen_debug.h"

#ifdef _DEBUG
void TRACELASTERROR()
   {
               DWORD dwMessageId = GetLastError();
         LPTSTR lpBuffer;
//         TRACE("Error Message Id: %d\n", dwMessageId);
         _AFX_FUNCNAME(FormatMessage)(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            dwMessageId,
            0,
            (LPTSTR) &lpBuffer,
            1,
            NULL);
         //TRACE("Error Message :\n%s\n", lpBuffer);
         LocalFree(lpBuffer);
   }
#endif

string FormatMessageFromSystem(DWORD dwError)
{
   string strError;
   LPTSTR pszError = NULL;
   _AFX_FUNCNAME(FormatMessage)(
     FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
     NULL,
     dwError,
     0,
     (LPTSTR) &pszError,
     8,
     NULL);

   strError = pszError;
   ::LocalFree(pszError);
   return strError;
}
