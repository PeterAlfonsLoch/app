// OptionsImagesDirectoriesDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "resource.h"
#include "VmpLight.h"

#include "DBImageDirectory.h"


// vmpLight
#include "OptionsFolderView.h"
#include "OptionsViewUpdateHint.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(OptionsFolderView, SimpleListView)
/////////////////////////////////////////////////////////////////////////////
// OptionsFolderView dialog

OptionsFolderView::OptionsFolderView()
{
	//{{AFX_DATA_INIT(OptionsFolderView)
	//}}AFX_DATA_INIT
   SetModifiedFlag(false);
   SetDataInterface(&m_listctrldata);
   Ex1ListInterface::m_etranslucency = Ex1ListInterface::TranslucencyPresent;
}

OptionsFolderView::OptionsFolderView(CWnd* pParent /*=NULL*/)
{
	SetModifiedFlag(false);
}


void OptionsFolderView::DoDataExchange(CDataExchange* pDX)
{
	SimpleListView::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(OptionsFolderView, SimpleListView)
	//{{AFX_MSG_MAP(OptionsFolderView)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_COMMAND(ID_EDIT_ADD, OnEditAdd)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ADD, OnUpdateEditAdd)
	ON_COMMAND(ID_EDIT_REMOVE, OnEditRemove)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REMOVE, OnUpdateEditRemove)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OptionsFolderView message handlers

BOOL OptionsFolderView::Update(BOOL bSaveAndValidate)
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

BOOL OptionsFolderView::UpdateDatabase(BOOL bSaveAndValidate)
{
	try
	{
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
      return TRUE;
	
	} catch(COLEDBException *e)
	{
		CDBErrorDialog dlg;
		dlg.Init(e->m_spUnk, e->m_iid);
		dlg.DoModal();
		e->Delete();
	}
	return FALSE;
}

BOOL OptionsFolderView::OnInitDialog() 
{
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void OptionsFolderView::OnAdd() 
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
         VmsDataGet(m_datakey, 0, 0, wstra);
         wstra.AddUnique(wstr);
         VmsDataSet(m_datakey, 0, 0, wstra);
		}
	}
}


void OptionsFolderView::OnRemove() 
{
   SimpleListCtrl::Range range;
   SimpleListCtrl * plist = (SimpleListCtrl *) _001GetWnd()->GetDlgItem(IDC_LIST);
	plist->_001GetSelection(range);
   if(range.GetItemCount() > 0)
   {
      WStrArray wstra;
      plist->RemoveItem(range);
      plist->GetData(wstra);
      VmsDataSet(m_datakey, 0, 0, wstra);
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

bool OptionsFolderView::IsModified()
{
	return m_bModified;
}

BOOL OptionsFolderView::DestroyWindow() 
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

void OptionsFolderView::SetModifiedFlag(bool bModified)
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

void OptionsFolderView::_001InitializeFormPreData()
{
/*	SimpleListViewInterfaceControl control;

	control.SetType(SimpleListViewInterfaceControl::TypeSimpleList);
	control.m_uiId = IDC_LIST;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleListCtrl);
	control.m_datakey = m_datakey;
   control.m_strPrivateDataSection = "OptionsImageDirectorySetialogGUI";
	_001AddControl(control);*/
}

void OptionsFolderView::OnEditAdd() 
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
         VmsDataGet(m_datakey, 0, 0, wstra);
         wstra.AddUnique(wstr);
         VmsDataSet(m_datakey, 0, 0, wstra);
		}
	}
}

void OptionsFolderView::OnUpdateEditAdd(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void OptionsFolderView::OnEditRemove() 
{
   SimpleListCtrl::Range range;
	_001GetSelection(range);
   if(range.GetItemCount() > 0)
   {
      WStrArray wstra;
      RemoveItem(range);
      GetData(wstra);
      VmsDataSet(m_datakey, 0, 0, wstra);
		UpdateData();
		SetModifiedFlag();
	}
	else
	{
		AfxMessageBox(IDS_NO_DIRECTORY_SELECTED,MB_ICONINFORMATION | MB_OK, 0);
	}	
}

void OptionsFolderView::OnUpdateEditRemove(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}


bool OptionsFolderView::RemoveItem(Range & range)
{
   bool bOk = true;
   BaseIntArray iaRemove;
   for(int iRange = 0; iRange < range.GetItemCount(); iRange++)
   {
      ItemRange & itemrange = range.ItemAt(iRange);
      for(int iItem = itemrange.GetLBound(); iItem <= itemrange.GetUBound(); iItem++)
      {
         iaRemove.AddUnique(iItem);
      }
   }
   Sort::QuickSort(iaRemove, false);
   for(int i = 0; i < iaRemove.GetSize(); i++)
   {
      if(!m_listctrldata.RemoveItem(iaRemove[i]))
         bOk = false;
   }
   _001SetItemCountEx(m_listctrldata.m_array.GetSize());
   return bOk;
}


void OptionsFolderView::GetData(WStrArray &wstra)
{
   m_listctrldata.GetData(wstra);
}

void OptionsFolderView::SetData(WStrArray &wstra)
{
   m_listctrldata.SetData(this, wstra);
}


void OptionsFolderView::VmsDataOnAfterChange(
   const VmsDataKeyInterface & key, int iLine, int iColumn, 
   VmsDataUpdateHint * puh)
{
   if(m_datakey == key)
   {
      _001UpdateList();
   }
}

void OptionsFolderView::_001UpdateList()
{
   WStrArray wstra;
   VmsDataGet(m_datakey, 0, 0, wstra);
   SetData(wstra);
}

int OptionsFolderView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (SimpleListView::OnCreate(lpCreateStruct) == -1)
		return -1;


	
	return 0;
}

void OptionsFolderView::OnUpdate(BaseView* pSender, LPARAM lHint, CObject* pHint) 
{
   if(pHint != NULL)
   {
      if(pHint->IsKindOf(RUNTIME_CLASS(OptionsViewUpdateHint)))
      {
         OptionsViewUpdateHint * puh = (OptionsViewUpdateHint *) pHint;
         if(puh->IsTypeOf(OptionsViewUpdateHint::TypeSetViewVmsDataKey)
            && this == puh->m_pview)
         {
            
            m_datakey = puh->m_datakey;
            CString str;
            str.Format("OptionsFolderView%d.%d", m_datakey.GetValue());
            DISetSection(str);
         
            _001SetSingleColumnMode(true);

            _001UpdateList();
         }
      }
   }
}


void OptionsFolderView::CreateViews()
{

}