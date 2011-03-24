// VmsTextDoc.cpp : implementation file
//

#include "stdafx.h"
//#include "vmsp.h"
#include "VmsTextDoc.h"
#include "WArchive.h"
#include "International.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVmsTextDoc

IMPLEMENT_DYNCREATE(CVmsTextDoc, CRichEditDoc)

CVmsTextDoc::CVmsTextDoc()
{
}

BOOL CVmsTextDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;
	return TRUE;
}

CVmsTextDoc::~CVmsTextDoc()
{
}


BEGIN_MESSAGE_MAP(CVmsTextDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CVmsTextDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVmsTextDoc diagnostics

#ifdef _DEBUG
void CVmsTextDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CVmsTextDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVmsTextDoc serialization

void CVmsTextDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		CWArchive & war  = (CWArchive &) ar;
		CWStr wstr;
		CWStr wstrText;
		while(war.ReadString(wstr))
		{
			wstrText += wstr;
			wstrText += L"\n";
		}
		CString strText;
		CInternational::UnicodeToOEM(strText, wstrText);
		GetView()->GetRichEditCtrl().ReplaceSel(strText);
		GetView()->GetRichEditCtrl().SetSel(0, 0);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CVmsTextDoc commands

CRichEditCntrItem* CVmsTextDoc::CreateClientItem(REOBJECT* preo) const
{
	return NULL;
}