// OptionsSongsDirectoriesDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "resource.h"
#include "OptionsSongDirectoriesView.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(OptionsSongDirectoriesView, SimpleListView)

/////////////////////////////////////////////////////////////////////////////
// OptionsSongDirectoriesView dialog

//const int OptionsSongDirectoriesView::IDD = IDD_OPTIONS_SONGS_DIRECTORIES;

OptionsSongDirectoriesView::OptionsSongDirectoriesView()
//	: SimpleListView(OptionsSongDirectoriesView::IDD)
{
   
	//{{AFX_DATA_INIT(OptionsSongDirectoriesView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	SetModifiedFlag(false);

   IGUI_WIN_ON_CONTROL(BN_CLICKED, IDC_ADD      , this, this, &OptionsSongDirectoriesView::_001OnAdd);
   IGUI_WIN_ON_CONTROL(BN_CLICKED, IDC_REMOVE   , this, this, &OptionsSongDirectoriesView::_001OnRemove);

}


OptionsSongDirectoriesView::OptionsSongDirectoriesView(CWnd* pParent /*=NULL*/)
//	: SimpleListView(OptionsSongDirectoriesView::IDD, pParent)
{
//	SetModifiedFlag(false);
}

OptionsSongDirectoriesView::~OptionsSongDirectoriesView()
{
}

void OptionsSongDirectoriesView::DoDataExchange(CDataExchange* pDX)
{
	SimpleListView::DoDataExchange(pDX);
	//CDDX::DDXListBox(pDX, IDC_LIST, *m_psongsdirs);
	//{{AFX_DATA_MAP(OptionsSongDirectoriesView)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(OptionsSongDirectoriesView, SimpleListView)
	//{{AFX_MSG_MAP(OptionsSongDirectoriesView)
   /*
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
   */
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OptionsSongDirectoriesView message handlers

void OptionsSongDirectoriesView::_001OnAdd(gen::signal_object * pobj) 
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

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if(pidl)
	{
		WCHAR pszPath[MAX_PATH];
      if(WindowsShell::SHGetPathFromIDList(pidl, pszPath))
		{

         WStrArray wstra;
         VmsDataGet(VMSDATAKEY(SongDirectorySet), 0, 0, wstra);
         wstra.AddUnique(pszPath);
         VmsDataSet(VMSDATAKEY(SongDirectorySet), 0, 0, wstra);
   	}
	}
}

void OptionsSongDirectoriesView::_001OnRemove(gen::signal_object * pobj) 
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

BOOL OptionsSongDirectoriesView::OnInitDialog() 
{
   SimpleListCtrl::Column column;

//   SimpleListView::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL OptionsSongDirectoriesView::Update(BOOL bSaveAndValidate)
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

BOOL OptionsSongDirectoriesView::UpdateDatabase(BOOL bSaveAndValidate)
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

bool OptionsSongDirectoriesView::IsModified()
{
	return m_bModified;
}

BOOL OptionsSongDirectoriesView::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if(SimpleListView::DestroyWindow())
    {
	    delete this;
	    return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void OptionsSongDirectoriesView::SetModifiedFlag(bool bModified)
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

/*BOOL OptionsSongDirectoriesView::Create(CWnd *pwndParent)
{
    return SimpleListView::Create(IDD, pwndParent);
}*/

bool OptionsSongDirectoriesView::Apply()
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


void OptionsSongDirectoriesView::_001InitializeFormPreData()
{
/*	SimpleListViewInterfaceControl control;

	control.m_uiId = IDC_ADD;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleButton);
	_001AddControl(control);

   control.m_uiId = IDC_REMOVE;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleButton);
	_001AddControl(control);

	control.SetType(SimpleListViewInterfaceControl::TypeSimpleList);
	control.m_uiId = IDC_LIST;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleListCtrl);
	control.m_datakey = VMSDATAKEY(SongDirectorySet);
   control.m_strPrivateDataSection = "OptionsSongsDirectoriesDialogGUI";
	_001AddControl(control);*/

}
