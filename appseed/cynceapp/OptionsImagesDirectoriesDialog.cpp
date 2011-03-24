// OptionsImagesDirectoriesDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "resource.h"
#include "OptionsImagesDirectoriesDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsImagesDirectoriesDialog dialog

COptionsImagesDirectoriesDialog::COptionsImagesDirectoriesDialog()
	: BaseForm(COptionsImagesDirectoriesDialog::IDD)
{
	//{{AFX_DATA_INIT(COptionsImagesDirectoriesDialog)
	//}}AFX_DATA_INIT
    SetModifiedFlag(false);
}

COptionsImagesDirectoriesDialog::COptionsImagesDirectoriesDialog(CWnd* pParent /*=NULL*/)
	: BaseForm(COptionsImagesDirectoriesDialog::IDD, pParent)
{
	SetModifiedFlag(false);
}


void COptionsImagesDirectoriesDialog::DoDataExchange(CDataExchange* pDX)
{
	BaseForm::DoDataExchange(pDX);
//	CDDX::DDXListBox(pDX, IDC_LIST, m_ImagesDirs);
	//{{AFX_DATA_MAP(COptionsImagesDirectoriesDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsImagesDirectoriesDialog, BaseForm)
	//{{AFX_MSG_MAP(COptionsImagesDirectoriesDialog)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsImagesDirectoriesDialog message handlers




BOOL COptionsImagesDirectoriesDialog::Update(BOOL bSaveAndValidate)
{
	if(bSaveAndValidate)
	{
		if(IsModified())
		{
			if(!UpdateData())
				return FALSE;
			if(!UpdateDatabase())
				return FALSE;
		}
	}
	else
	{
		if(!UpdateDatabase(FALSE))
			return FALSE;
		if(!UpdateData(FALSE))
			return FALSE;
	}
	return TRUE;
}

BOOL COptionsImagesDirectoriesDialog::UpdateDatabase(BOOL bSaveAndValidate)
{
//	try
//	{
	/*CDBCentral *pDataCentral = (CDBCentral *) DB();
	CDBStringArraySet *pSet = pDataCentral->GetImageFolderSet();
	if(bSaveAndValidate)
	{
		pSet->SetData(m_ImagesDirs);
	    SetModifiedFlag(false);
	}
	else
	{
		if(m_ImagesDirs.GetSize())
			m_ImagesDirs.RemoveAll();
		pSet->GetData(m_ImagesDirs);*/
//	}
//	return TRUE;
  /*    return TRUE;
	
	} catch(COLEDBException *e)
	{
		CDBErrorDialog dlg;
		dlg.Init(e->m_spUnk, e->m_iid);
		dlg.DoModal();
		e->Delete();
	}*/

	return FALSE;
}

BOOL COptionsImagesDirectoriesDialog::OnInitDialog() 
{
	BaseForm::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionsImagesDirectoriesDialog::OnAdd() 
{
	// TODO: Add your control notification handler code here
	BROWSEINFO bi;
	
	CString str;

	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = NULL;
	str.LoadString(IDS_CHOOSE_IMAGE_DIRECTORY);
	bi.lpszTitle = str;
	bi.ulFlags = 0;
	//bi.lpfn = BrowseCallbackProc;
	bi.lpfn = NULL;
	bi.lParam = 1;
	bi.iImage = 0;

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	WString wstr;
	if(pidl)
	{
		WCHAR pszPath[MAX_PATH];
		if(WindowsShell::SHGetPathFromIDList(pidl, pszPath))
		{
         wstr = pszPath;

         WStrArray wstra;
         VmsDataGet(VMSDATAKEY(ImageDirectorySet), 0, 0, wstra);
         wstra.AddUnique(wstr);
         VmsDataSet(VMSDATAKEY(ImageDirectorySet), 0, 0, wstra);
		}
	}
}


void COptionsImagesDirectoriesDialog::OnRemove() 
{
   SimpleListCtrl::Range range;
   SimpleListCtrl * plist = (SimpleListCtrl *) _001GetWnd()->GetDlgItem(IDC_LIST);
	plist->_001GetSelection(range);
   if(range.GetItemCount() > 0)
   {
      AStrArray wstra;
      plist->RemoveItem(range);
      plist->GetData(wstra);
      VmsDataSet(VMSDATAKEY(ImageDirectorySet), 0, 0, wstra);
		UpdateData();
		SetModifiedFlag();
	}
	else
	{
		AfxMessageBox(IDS_NO_DIRECTORY_SELECTED,MB_ICONINFORMATION | MB_OK, 0);
	}	
	// TODO: Add your control notification handler code here
/*	CListBox *pList =  (CListBox *) GetDlgItem(IDC_LIST);
	int iSelCount = pList->GetSelCount();
	if(iSelCount)
	{
		LPINT lpInt = (LPINT) malloc(iSelCount * sizeof(INT));
		pList->GetSelItems(iSelCount, lpInt);
        CBaseSort::BubbleSort(lpInt, iSelCount);
		for(int i = 0; i < iSelCount; i++)
		{
			pList->DeleteString(*lpInt - i);
			lpInt++;
		}
		UpdateData();
		SetModifiedFlag();
	}
	else
	{
		AfxMessageBox(IDS_NO_DIRECTORY_SELECTED,MB_ICONINFORMATION | MB_OK, 0);
	}*/
}

bool COptionsImagesDirectoriesDialog::IsModified()
{
	return m_bModified;
}

BOOL COptionsImagesDirectoriesDialog::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if(BaseForm::DestroyWindow())
    {
	    delete this;
	    return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void COptionsImagesDirectoriesDialog::SetModifiedFlag(bool bModified)
{
    if(bModified)
    {
        m_bModified = true;
        GetParent()->PostMessage(WM_USER, 1000);
    }
    else
    {
        m_bModified = false;
    }
}

void COptionsImagesDirectoriesDialog::_001InitializeFormPreData()
{
	Ex1FormInterfaceControl control;

	control.SetType(Ex1FormInterfaceControl::TypeSimpleList);
	control.m_uiId = IDC_LIST;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleListCtrl);
	control.m_datakey = VMSDATAKEY(ImageDirectorySet);
   control.m_strPrivateDataSection = "OptionsImageDirectorySetialogGUI";
	_001AddControl(control);
}
