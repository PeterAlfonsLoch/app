// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "vmsp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// IXfplayer properties

/////////////////////////////////////////////////////////////////////////////
// IXfplayer operations

BOOL IXfplayer::OpenFile(LPCTSTR bstrFilePath, BOOL bMakeVisible)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bstrFilePath, bMakeVisible);
	return result;
}
