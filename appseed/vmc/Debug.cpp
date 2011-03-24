/*****************************************************************************
*
*  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
*  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
*  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR
*  A PARTICULAR PURPOSE.
*
*  Copyright (C) 1993 - 1997 Microsoft Corporation. All Rights Reserved.
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

#include "stdafx.h"
#include "debug.h"
#ifdef _DEBUG
void TRACELASTERROR()
	{
					DWORD dwMessageId = GetLastError();
			LPTSTR lpBuffer;
			TRACE(_T("Error Message Id: %d\n"), dwMessageId);
			FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM,
				NULL,
				dwMessageId,
				0,
				(LPTSTR) &lpBuffer,
				1,
				NULL);
			TRACE(_T("Error Message :\n%s\n"), lpBuffer);
			LocalFree(lpBuffer);
	}
#endif