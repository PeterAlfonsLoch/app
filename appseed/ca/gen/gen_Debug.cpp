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
      string strErrorMessage = ::get_system_error_message(::GetLastError())
      APPTRACE(::ca::get_thread_app())("Error Message :\n%s\n", strErrorMessage);
}
#endif


string FormatMessageFromSystem(DWORD dwError)
{


   return ::get_system_error_message(dwError);


}
