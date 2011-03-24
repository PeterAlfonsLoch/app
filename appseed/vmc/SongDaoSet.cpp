// SongDaoSet.cpp : implementation file
//

#include "stdafx.h"
#include "xfplayer.h"
#include "SongDaoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSongDaoSet

IMPLEMENT_DYNAMIC(CSongDaoSet, CDaoRecordset)

CSongDaoSet::CSongDaoSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSongDaoSet)
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenSnapshot;
}


CString CSongDaoSet::GetDefaultDBName()
{
	return _T("D:\Arquivos\prg\vc\Áudio\vms\2001-08-24\vms\Debug\database351.mdb");
}

CString CSongDaoSet::GetDefaultSQL()
{
	return _T("");
}

void CSongDaoSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSongDaoSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSongDaoSet diagnostics

#ifdef _DEBUG
void CSongDaoSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CSongDaoSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
