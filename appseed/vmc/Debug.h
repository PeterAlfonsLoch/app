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
* Debug.H
*
* Public include file for debug output
*
*****************************************************************************/

#ifndef _INC_DEBUG
#define _INC_DEBUG

#ifdef _DEBUG
	void TRACELASTERROR();
#else
	#define TRACELASTERROR() ((void)0)
#endif

#endif