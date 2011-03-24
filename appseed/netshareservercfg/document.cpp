#include "StdAfx.h"

namespace netshareservercfg
{

document::document()
{
}

BOOL document::OnNewDocument()
{
	if (!BaseDocument::OnNewDocument())
		return FALSE;

   UpdateAllViews(NULL, 0);

	return TRUE;
}

document::~document()
{
}



#ifdef _DEBUG
void document::AssertValid() const
{
	BaseDocument::AssertValid();
}

void document::Dump(CDumpContext& dc) const
{
	BaseDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// document serialization

/*
void document::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}
*/

} // namespace netshareservercfg
