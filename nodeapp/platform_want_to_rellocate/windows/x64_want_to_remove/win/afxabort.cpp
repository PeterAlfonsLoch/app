#include "StdAfx.h"


// Note: in separate module so it can be replaced if needed

void CLASS_DECL_VMSWIN AfxAbort()
{
	TRACE(traceAppMsg, 0, "AfxAbort called.\n");

	AfxWinTerm();
	abort();
}

/////////////////////////////////////////////////////////////////////////////
