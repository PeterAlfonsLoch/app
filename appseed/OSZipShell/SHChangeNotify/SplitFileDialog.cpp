// SplitFileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SHChangeNotify.h"
#include "SplitFileDialog.h"


// SplitFileDialog dialog

IMPLEMENT_DYNAMIC(SplitFileDialog, CDialog)

SplitFileDialog::SplitFileDialog(CWnd* pParent /*=NULL*/)
	: CDialog(SplitFileDialog::IDD, pParent)
{

}

SplitFileDialog::~SplitFileDialog()
{
}

void SplitFileDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SplitFileDialog, CDialog)
END_MESSAGE_MAP()


// SplitFileDialog message handlers
