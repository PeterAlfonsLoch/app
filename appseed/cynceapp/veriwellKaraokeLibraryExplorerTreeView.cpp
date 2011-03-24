// veriwellKaraokeLibraryExplorerTreeView.cpp : implementation file
//

#include "stdafx.h"
#include "veriwellKaraokeLibraryExplorerTreeView.h"
#include "veriwellKaraokeLibraryExplorerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// veriwellKaraokeLibraryExplorerTreeView

IMPLEMENT_DYNCREATE(veriwellKaraokeLibraryExplorerTreeView, BaseView)

veriwellKaraokeLibraryExplorerTreeView::veriwellKaraokeLibraryExplorerTreeView()
{

   m_pscrollbarVert  = &m_scrollbarVert;
   m_pscrollbarHorz  = &m_scrollbarHorz;

   m_etranslucency = TranslucencyPresent;


   m_wndrender.SetWindow(this);

   EnableBuffering(true);

   
   m_iIconFolderNormal = m_pimagelist->Add(
      (HICON) ::LoadImage(
         AfxGetApp()->m_hInstance,
         MAKEINTRESOURCE(IDI_VMSKARLIB_FOLDER_NORMAL),
         IMAGE_ICON,
         16, 16, 0));

   m_iIconFolderSelected = m_pimagelist->Add(
      (HICON) ::LoadImage(
         AfxGetApp()->m_hInstance,
         MAKEINTRESOURCE(IDI_VMSKARLIB_FOLDER_SELECTED),
         IMAGE_ICON,
         16, 16, 0));

   m_iIconArtistNormal = m_pimagelist->Add(
      (HICON) ::LoadImage(
         AfxGetApp()->m_hInstance,
         MAKEINTRESOURCE(IDI_VMSKARLIB_ARTIST_NORMAL),
         IMAGE_ICON,
         16, 16, 0));

   m_iIconArtistSelected = m_pimagelist->Add(
      (HICON) ::LoadImage(
         AfxGetApp()->m_hInstance,
         MAKEINTRESOURCE(IDI_VMSKARLIB_ARTIST_SELECTED),
         IMAGE_ICON,
         16, 16, 0));
}

veriwellKaraokeLibraryExplorerTreeView::~veriwellKaraokeLibraryExplorerTreeView()
{
}


BEGIN_MESSAGE_MAP(veriwellKaraokeLibraryExplorerTreeView, BaseView)
	//{{AFX_MSG_MAP(veriwellKaraokeLibraryExplorerTreeView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// veriwellKaraokeLibraryExplorerTreeView drawing

void veriwellKaraokeLibraryExplorerTreeView::OnDraw(CDC* pDC)
{
	Document* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// veriwellKaraokeLibraryExplorerTreeView diagnostics

#ifdef _DEBUG
void veriwellKaraokeLibraryExplorerTreeView::AssertValid() const
{
	BaseView::AssertValid();
}

void veriwellKaraokeLibraryExplorerTreeView::Dump(CDumpContext& dc) const
{
	BaseView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// veriwellKaraokeLibraryExplorerTreeView message handlers

void veriwellKaraokeLibraryExplorerTreeView::Parse(LPCTSTR lpszParentId, LPCTSTR lpszSource)
{
   CString str;
   XNode xml;
   if(xml.Load(lpszSource))
   {
      str  = xml.GetXML();
   }
   else
   {
      AfxMessageBox(_T("error")); // simple parsing error check
      return;
   }

   Ex1TreeDataItem * pdataitemParent;
   Ex1TreeDataItem * pdataitemChild;

   pdataitemParent = FindTreeItem(lpszParentId);
   if(pdataitemParent == NULL)
   {
      pdataitemParent = m_data._001GetBaseItem();
   }

   int i;
   XNodes childs;

   WString wstrType;
   _vmskar::Folder folder;
   // method 3: Selected Childs with GetChilds()
   // Result: Person, Person, Person
   childs = xml.GetChilds("folder");
   for( i = 0 ; i < childs.size(); i++)
   {
      wstrType = childs[i]->GetChildValue("type");
      folder.m_strId = childs[i]->GetChildValue("id");
      folder.m_strTitle = childs[i]->GetChildValue("title");

      if(wstrType == "normal")
      {
         folder.m_etype = _vmskar::FolderTypeNormal;
      }
      else if(wstrType == "artist")
      {
         folder.m_etype = _vmskar::FolderTypeArtist;
      }
      else 
      {
         // unknown folder type
         ASSERT(FALSE);
      }

      switch(folder.m_etype)
      {
      case _vmskar::FolderTypeNormal:
         folder.m_iImage = m_iIconFolderNormal;
         folder.m_iImageSelected = m_iIconFolderSelected;
         break;
      case _vmskar::FolderTypeArtist:
         folder.m_iImage = m_iIconArtistNormal;
         folder.m_iImageSelected = m_iIconArtistSelected;
         break;
      default:
         // unknown folder type
         break;
      }

      int iNewItem = m_foldera.FindAbsolute(folder.m_strId);
      if(iNewItem == -1)
      {
         iNewItem = m_foldera.GetSize();
			m_foldera.AddNew();
      }
      m_foldera.ElementAt(iNewItem) = folder;

      pdataitemChild = pdataitemParent->GetChildByUserData(iNewItem);

      if(pdataitemChild == NULL)
      {
         pdataitemChild = m_data._001InsertItem(
            pdataitemParent,
            RelativeLastChild);
      }

      pdataitemChild->m_str = folder.m_strTitle;
      pdataitemChild->m_dwUser = iNewItem;

//      else
  //    {
    //     ptraRemove.RemoveFirst(pdataitemChild);
      //}

      
      m_foldera.Add(folder);
   }

   _001SelectItem(FindTreeItem(lpszParentId));

}


Ex1TreeDataItem * veriwellKaraokeLibraryExplorerTreeView::FindTreeItem(
   LPCTSTR lpszId)
{
   int iUser;

   if(lpszId == NULL)
      return NULL;

   iUser = m_foldera.FindAbsolute(lpszId);
   if(iUser >= 0)
   {
      return m_data._001GetBaseItem()->FindNextByUserData(iUser);
   }
   else
      return NULL;
}

int _vmskar::FolderArray::FindAbsolute(LPCTSTR lpszId)
{
   for(int i = 0; i < GetSize(); i++)
   {
      if(ElementAt(i).m_strId == lpszId)
         return i;
   }
   return -1;
}


int veriwellKaraokeLibraryExplorerTreeView::_001GetItemImage(
   Ex1TreeDataItem * pitem,
   bool bSelected
   )
{
   if(bSelected)
   {
      return m_foldera.ElementAt(pitem->m_dwUser).m_iImageSelected;
   }
   else
   {
      return m_foldera.ElementAt(pitem->m_dwUser).m_iImage;
   }
}

void veriwellKaraokeLibraryExplorerTreeView::_001OnItemExpand(Ex1TreeDataItem *pitem)
{
   m_pserver->Request(m_foldera[pitem->m_dwUser].m_strId);
}


CWnd * veriwellKaraokeLibraryExplorerTreeView::OnDrawInterfaceGetWnd()
{
   return this;
}


WndRenderInterface * veriwellKaraokeLibraryExplorerTreeView::_GetWndRenderInterface()
{
   return &m_wndrender;
}


CWnd * veriwellKaraokeLibraryExplorerTreeView::_GetWnd()
{
   return this;
}


bool veriwellKaraokeLibraryExplorerTreeView::TwiHasTranslucency()
{
   return true;
}


void veriwellKaraokeLibraryExplorerTreeView::_001InstallMessageHandling(::igui::win::message::Dispatch * pdispatch)
{
   BaseView::_001InstallMessageHandling(pdispatch);
   //xxx
   BaseView::_001InstallMessageHandling(pdispatch);
   Ex1TreeInterface::_001InstallMessageHandling(pdispatch);

}
