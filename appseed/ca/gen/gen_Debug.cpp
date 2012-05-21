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

#include "framework.h"

#include "gen_debug.h"

#ifdef DEBUG
void TRACELASTERROR()
   {
               DWORD dwMessageId = GetLastError();
         LPWSTR lpBuffer;
//         TRACE("Error Message Id: %d\n", dwMessageId);

#ifdef WINDOWS

         FormatMessageW(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            dwMessageId,
            0,
            (LPWSTR) &lpBuffer,
            1,
            NULL);
         //TRACE("Error Message :\n%s\n", gen::international::unicode_to_utf8(lpBuffer));
         LocalFree(lpBuffer);
#endif

   }
#endif

string FormatMessageFromSystem(DWORD dwError)
{
   string strError;
   LPWSTR pszError = NULL;

#ifdef WINDOWS

   FormatMessageW(
     FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
     NULL,
     dwError,
     0,
     (LPWSTR) &pszError,
     8,
     NULL);

   strError = gen::international::unicode_to_utf8(pszError);

   ::LocalFree(pszError);

#endif

   return strError;

}
