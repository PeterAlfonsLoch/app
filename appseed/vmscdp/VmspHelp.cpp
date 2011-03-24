// VmspHelp.cpp: implementation of the CVmspHelp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "helpid.h"
#include "VmspHelp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVmspHelp::CVmspHelp()
{

}

CVmspHelp::~CVmspHelp()
{

}

namespace VmspHelp
{
	CHelpCentral::CCsRow rowaContextSensitive[] =
		{
			CHelpCentral::CCsRow(
				IDH_CS_TOOLS_ALBUM,
				_T("usingalbum.html")),
			CHelpCentral::CCsRow(
				IDH_CS_VIEW_LYRICS,
				_T("songlyrics.html")),
			CHelpCentral::CCsRow(
				0,
				0)
		};

}