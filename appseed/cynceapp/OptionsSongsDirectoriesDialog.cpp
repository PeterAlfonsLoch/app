// OptionsSongsDirectoriesDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "resource.h"
#include "OptionsSongsDirectoriesDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsSongsDirectoriesDialog dialog

//const int COptionsSongsDirectoriesDialog::IDD = IDD_OPTIONS_SONGS_DIRECTORIES;

COptionsSongsDirectoriesDialog::COptionsSongsDirectoriesDialog()
	: BaseForm(COptionsSongsDirectoriesDialog::IDD)
{
   
	//{{AFX_DATA_INIT(COptionsSongsDirectoriesDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	SetModifiedFlag(false);
}


COptionsSongsDirectoriesDialog::COptionsSongsDirectoriesDialog(CWnd* pParent /*=NULL*/)
	: BaseForm(COptionsSongsDirectoriesDialog::IDD, pParent)
{
	SetModifiedFlag(false);
}

COptionsSongsDirectoriesDialog::~COptionsSongsDirectoriesDialog()
{
}

void COptionsSongsDirectoriesDialog::DoDataExchange(CDataExchange* pDX)
{
	BaseForm::DoDataExchange(pDX);
	//CDDX::DDXListBox(pDX, IDC_LIST, *m_psongsdirs);
	//{{AFX_DATA_MAP(COptionsSongsDirectoriesDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsSongsDirectoriesDialog, BaseForm)
	//{{AFX_MSG_MAP(COptionsSongsDirectoriesDialog)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsSongsDirectoriesDialog message handlers

void COptionsSongsDirectoriesDialog::OnAdd() 
{

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

	WString wstr;
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if(pidl)
	{
		WCHAR pszPath[MAX_PATH];
      if(WindowsShell::SHGetPathFromIDList(pidl, pszPath))
		{
         wstr = pszPath;

         WStrArray wstra;
         VmsDataGet(VMSDATAKEY(SongDirectorySet), 0, 0, wstra);
         wstra.AddUnique(wstr);
         VmsDataSet(VMSDATAKEY(SongDirectorySet), 0, 0, wstra);
   	}
	}
}

void COptionsSongsDirectoriesDialog::OnRemove() 
{
   SimpleListCtrl::Range range;
   SimpleListCtrl * plist = (SimpleListCtrl *) _001GetWnd()->GetDlgItem(IDC_LIST);
	plist->_001GetSelection(range);
   if(range.GetItemCount() > 0)
   {
      AStrArray wstra;
      plist->RemoveItem(range);
      plist->GetData(wstra);
      VmsDataSet(VMSDATAKEY(SongDirectorySet), 0, 0, wstra);
		UpdateData();
		SetModifiedFlag();
	}
	else
	{
		AfxMessageBox(IDS_NO_DIRECTORY_SELECTED,MB_ICONINFORMATION | MB_OK, 0);
	}	
}

BOOL COptionsSongsDirectoriesDialog::OnInitDialog() 
{
   SimpleListCtrl::Column column;

   BaseForm::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL COptionsSongsDirectoriesDialog::Update(BOOL bSaveAndValidate)
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

BOOL COptionsSongsDirectoriesDialog::UpdateDatabase(BOOL bSaveAndValidate)
{
/*	try
	{
	
	} catch(COLEDBException *e)
	{
		CDBErrorDialog dlg;
		dlg.Init(e->m_spUnk, e->m_iid);
		dlg.DoModal();
		e->Delete();
	}*/
	return FALSE;

}

bool COptionsSongsDirectoriesDialog::IsModified()
{
	return m_bModified;
}

BOOL COptionsSongsDirectoriesDialog::DestroyWindow() 
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

void COptionsSongsDirectoriesDialog::SetModifiedFlag(bool bModified)
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

BOOL COptionsSongsDirectoriesDialog::Create(CWnd *pwndParent)
{
    return BaseForm::Create(IDD, pwndParent);
}

bool COptionsSongsDirectoriesDialog::Apply()
{
	bool bModified = IsModified();
	if(bModified)
	{
		if(!Update())
			return false;
		m_bModified = false;
	}
	if(bModified)
	{
//		DB()->OnSongsDirsModified(AfxGetApp());
	}
	
	return true;
}


void COptionsSongsDirectoriesDialog::_001InitializeFormPreData()
{
	Ex1FormInterfaceControl control;

	control.m_uiId = IDC_ADD;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleButton);
	_001AddControl(control);

   control.m_uiId = IDC_REMOVE;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleButton);
	_001AddControl(control);

	control.SetType(Ex1FormInterfaceControl::TypeSimpleList);
	control.m_uiId = IDC_LIST;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleListCtrl);
	control.m_datakey = VMSDATAKEY(SongDirectorySet);
   control.m_strPrivateDataSection = "OptionsSongsDirectoriesDialogGUI";
	_001AddControl(control);

}
