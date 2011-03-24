// PlaylistListView.cpp : implementation file
//

#include "stdafx.h"
#include "PlaylistListView.h"
#include "resource.h"
#include "PaneView1.h"

// vmsgen
#include "gen/BSTR.h"

// vmsguibase
//#include "guibase/SimpleFrameWnd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PlaylistListView

IMPLEMENT_DYNCREATE(PlaylistListView, SimpleFormListView)

PlaylistListView::PlaylistListView()
{
   CDC dc;
   dc.CreateCompatibleDC(NULL);

   m_basecontrol.Create(this);

   m_imagelistSubItemHover.Create(16, 16, 0,  10, 10);


   m_imagelistSubItemHover.Add(
      (HICON) ::LoadImage(
         AfxGetApp()->m_hInstance,
         MAKEINTRESOURCE(IDI_EXECUTE_PLAY),
         IMAGE_ICON,
         16,
         16,
         LR_SHARED));

/*  CImaging::GetImaging()->CreateColorBlendImageList(
      &m_imagelistNormal,
      &m_imagelistHover,
      RGB(255, 255, 240),
      64);*/
   
   CImaging::GetImaging()->CreateHueImageList(
      &dc,
      &m_imagelistNormal,
      &m_imagelistSubItemHover,
      RGB(220, 220, 215),
      0.50);

   CImaging::GetImaging()->CreateColorBlendImageList(
      &m_imagelistItemHover,
      &m_imagelistSubItemHover,
      RGB(220, 220, 215),
      127);


   EnableBuffering(true);

   SetCacheInterface(&m_cache);
   m_gdibuffer.InstallMessageHandling(this);
 	m_enhmetafile = NULL;
   Ex1ListInterface::m_etranslucency = Ex1ListInterface::TranslucencyPresent;
	m_emode = ModeNormal;
   CRuntimeClass * prtc = RUNTIME_CLASS(PlaylistListView);
	DISetSection(prtc->m_lpszClassName);

   IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK           , this, this, &PlaylistListView::_001OnLButtonDblClk);
	IGUI_WIN_MSG_LINK(WM_CONTEXTMENU             , this, this, &PlaylistListView::_001OnContextMenu);
	IGUI_WIN_MSG_LINK(WM_SIZE                    , this, this, &PlaylistListView::_001OnSize);
	
   IGUI_WIN_ON_COMMAND(ID_EDIT_REMOVE           , this, this, &PlaylistListView::_001OnEditRemove);
	IGUI_WIN_UPD_CMD_UI(ID_EDIT_REMOVE           , this, this, &PlaylistListView::_001OnUpdateEditRemove);
	IGUI_WIN_ON_COMMAND(ID_PLAYLIST_EXECUTE_PLAY , this, this, &PlaylistListView::_001OnPlaylistExecutePlay);
	IGUI_WIN_UPD_CMD_UI(ID_PLAYLIST_EXECUTE_PLAY , this, this, &PlaylistListView::_001OnUpdatePlaylistExecutePlay);
}

PlaylistListView::~PlaylistListView()
{
}


BEGIN_MESSAGE_MAP(PlaylistListView, SimpleFormListView)
	//{{AFX_MSG_MAP(PlaylistListView)
   /*
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CONTEXTMENU()
	ON_WM_SIZE()
	ON_COMMAND(ID_EDIT_REMOVE, OnEditRemove)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REMOVE, OnUpdateEditRemove)
	ON_COMMAND(ID_PLAYLIST_EXECUTE_PLAY, OnPlaylistExecutePlay)
	ON_UPDATE_COMMAND_UI(ID_PLAYLIST_EXECUTE_PLAY, OnUpdatePlaylistExecutePlay)
   */
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// PlaylistListView diagnostics

#ifdef _DEBUG
void PlaylistListView::AssertValid() const
{
	SimpleFormListView::AssertValid();
}

void PlaylistListView::Dump(CDumpContext& dc) const
{
	SimpleFormListView::Dump(dc);
}

PlaylistDoc* PlaylistListView::GetDocument() const// non-debug version is inline
{
   if(m_pDocument == NULL)
      return NULL;
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(PlaylistDoc)));
	return (PlaylistDoc*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// PlaylistListView message handlers

BOOL PlaylistListView::PreCreateWindow(CREATESTRUCT& cs) 
{
//	cs.style |= LVS_REPORT;
//	cs.style |= LVS_OWNERDRAWFIXED;	
//	cs.style |= LVS_OWNERDATA;	
	
	return SimpleFormListView::PreCreateWindow(cs);
}


bool PlaylistListView::_001GetItemText(CString &wstr, INT_PTR iItem, INT_PTR iSubItem, INT_PTR iListItem)
{
   if(SimpleFormListView::_001GetItemText(
      wstr,
      iItem, 
      iSubItem, 
      iListItem))
   {
      return true;
   }
   
   ASSERT_VALID(this);
   PlaylistDoc * pdoc = GetDocument();
   //CWStrArray & wstraSongs = pDoc->GetSongs();
   DBCentral* pDataCentral = (DBCentral *) DB();
//    CString  str;
	CString wstrSongPath;
   
   if(pDataCentral->IsWorking()
	   &&	pdoc->GetSongPath(wstrSongPath, iItem))
   {
	   if(iSubItem == 0)
		{
         wstr.Format("?????");
      }
		else if(iSubItem == 1)
		{
         wstr.Format("?????");		
      }
		else if(iSubItem == 2)
		{
         int iFind1 = wstrSongPath.ReverseFind('\\');
         int iFind2 = wstrSongPath.ReverseFind('/');
         int iFind = 0;
         if(iFind1 >= 0)
         {
            if(iFind2 >= 0)
            {
               if(iFind1 >= iFind2)
               {
                  iFind = iFind1 + 1;
               }
               else
               {
                  iFind = iFind2 + 1;
               }
            }
            else
            {
               iFind = iFind1 + 1;
            }
         }
         else
         {
            if(iFind2 >= 0)
            {
               iFind = iFind2 + 1;
            }
         }

         wstr = wstrSongPath.Mid(iFind);

      }
		else if(iSubItem == 3)
		{
         wstr = wstrSongPath;
      }
	}
/*    else
    {
		if(iSubItem == 0)
		{
	        wstr.Format(L"?????");
		}
		else if(iSubItem == 1)
		{
	        wstr.Format(L"?????");
		}
		else if(iSubItem == 2)
		{
            wstr = wstrSongPath;
        }
    }*/
	return true;
/*    if(pDataCentral->IsWorking()
		&&	pdoc->GetSongPath(wstrSongPath, iItem)
		&&	pSongsSet->FindPath(wstrSongPath))
    {
		if(iSubItem == 0)
		{
			pSongsSet->GetData(1);
			wstr.Format(L"%d", pSongsSet->m_iCode);
		}
		else if(iSubItem == 1)
		{
			pSongsSet->GetData(1);
			wstr.Format(L"%d", pSongsSet->m_iCode);
		}
		else if(iSubItem == 2)
		{
           pSongsSet->GetData(2);
           wstr = pSongsSet->m_bstrName;
	    }
	}
    else*/
    {
		if(iSubItem == 0)
		{
	        wstr.Format("?????");
		}
		else if(iSubItem == 1)
		{
	        wstr.Format("?????");
		}
		else if(iSubItem == 2)
		{
            wstr = wstrSongPath;
        }
    }
	return true;
}

void PlaylistListView::SetMode(EMode emode)
{
    m_emode = emode;
//	CListCtrl & list = GetListCtrl();
//	while(list.DeleteColumn(0));
	_001UpdateColumns();
	RedrawWindow();

}


void PlaylistListView::_001InsertColumns()
{
   DBCentral * pDataCentral = (DBCentral *) DB();

  	Ex1FormInterfaceControl control;

	control.m_bTransparent = true;
	control.SetType(Ex1FormInterfaceControl::TypeButton);
   control.m_pruntimeclass = RUNTIME_CLASS(BaseButtonControl);
	control.m_uiId = 123; // Play Button
	control.AddFunction(Ex1FormInterfaceControl::FunctionAction);
	int iControl = _001AddControl(control);

 	Column column;

	column.m_iWidth               = 18;
	column.m_iSubItem             = 1;
   //column.m_bIcon                = true;
   //column.m_sizeIcon.cx          = 16;
   //column.m_sizeIcon.cy          = 16;
   column.m_iControl             = iControl;
   column.m_bCustomDraw          = true;
   column.m_bEditOnSecondClick   = true;
	_001AddColumn(column);




	EMode emode = m_emode;

    if(emode == ModeMinimum)
    {
		column.m_iWidth = 300;
//		column.m_uiText = IDS_PLAYLIST_CODE;
		column.m_iSubItem = 0;
//		column.m_uiSmallBitmap = IDB_ALBUM_SMALL_256;
		column.m_iSmallImageWidth = 16;
		column.m_crSmallMask = RGB(255, 0, 255);
		_001AddColumn(column);
    }
    else if(emode == ModeNormal)
    {
		column.m_iWidth = 170;
		column.m_uiText = IDS_PLAYLIST_HEADER_FILENAME;
		column.m_iSubItem = 2;
//		column.m_uiSmallBitmap = IDB_ALBUM_SMALL_256;
		column.m_iSmallImageWidth = 16;
		column.m_crSmallMask = RGB(255, 0, 255);
		_001AddColumn(column);

		column.m_uiText = IDS_PLAYLIST_HEADER_FILEPATH;
		column.m_iWidth = 400;
		column.m_iSubItem = 3;
		_001AddColumn(column);

    }



}

void PlaylistListView::OnUpdate(BaseView* pSender, LPARAM lHint, CObject* pHint) 
{
   if(lHint == 247)
   {  
      _001UpdateColumns();
   }
   PlaylistDoc * pdoc = GetDocument();
	CRuntimeClass * prtc = RUNTIME_CLASS(PlaylistListView);
	WString wstr;
	International::ACPToUnicode(wstr, prtc->m_lpszClassName);
	wstr += L".";
	wstr += GetDocument()->GetPathName();
   CString str;
   International::UnicodeToACP(str, wstr);
	DISetSection(str);
	
	if(lHint == PlaylistDoc::LHINT_FRAMEDOWN)
	{
		if(GetMode() == ModeNormal)
			SetMode(ModeMinimum);
		else
			SetMode(ModeNormal);
	}
	else if(lHint == PlaylistDoc::LHINT_FRAMEUP)
	{
		if(GetMode() == ModeMinimum)
			SetMode(ModeNormal);
		else
			SetMode(ModeMinimum);
	}

	ASSERT_VALID(this);
	PlaylistViewUpdateHint * ppluh = (PlaylistViewUpdateHint *) pHint;
   PlaylistViewUpdateHint * puh = (PlaylistViewUpdateHint *) pHint;
	bool bAllUpdates = pHint == NULL
		||
		(ppluh != NULL
		&& ppluh->GetHint() == PlaylistViewUpdateHint::HintFull);
    if(bAllUpdates ||
		ppluh != NULL)
    {
		if(bAllUpdates ||
			ppluh->GetHint() == PlaylistViewUpdateHint::HintFull)
	    {
			_001OnUpdateItemCount();
			_GetWndRenderInterface()->Redraw();
        }

		if(bAllUpdates ||
	        ppluh->GetHint() == PlaylistViewUpdateHint::HintCurrentSong)
		{
         Range range;
         ItemRange itemrange;
         itemrange.Set(pdoc->GetCurrentSong(),
            pdoc->GetCurrentSong(),
            0,
            m_columna.GetCount(),
            -1, -1);
			range.AddItem(itemrange);
			_001SetHighlightRange(range);
		    _GetWndRenderInterface()->Redraw();
		}
    }
	if(ppluh != NULL)
	{
		if(ppluh->GetHint() ==
			PlaylistViewUpdateHint::HintGetAttachableView)
		{
			ppluh->AddAttachableView(this);
		}
	}
   if(puh != NULL)
   {
      switch(puh->GetHint())
      {
      case PlaylistViewUpdateHint::HintPop:
         {
            SimpleFrameWnd * pframewnd = (SimpleFrameWnd *) Ex1ListInterface::_001GetParentFrame();
            OnActivateFrame(WA_INACTIVE, pframewnd);
            pframewnd->ActivateFrame(SW_SHOW);
            OnActivateView(TRUE, this, this);
            RedrawWindow();
         }
         break;
      case PlaylistViewUpdateHint::HintInitial:
         {
            _001UpdateColumns();
   			_001OnUpdateItemCount();
            _001OnInitialUpdate(NULL);
         }
         break;
      }
   }
   m_cache._001Invalidate();
	_001OnUpdateItemCount();
   
	
}

void PlaylistListView::_001OnInitialUpdate(gen::signal_object * pobj) 
{
	SimpleFormListView::_001OnInitialUpdate(NULL);

   //_001UpdateColumns();

   RedrawWindow();

   TRACE("PlaylistListView::OnInitialUpdate() HWND = %d\n", GetSafeHwnd());
	
/*	CTransparentFrameWndV4 * pframe = dynamic_cast < CTransparentFrameWndV4 * > (GetParentFrame());
	if(pframe != NULL)
	{
		pframe->GetWndFramework()->SetDownUpInterface(this);
		pframe->SetDownUpInterface(this);
	}*/
}

bool PlaylistListView::WndFrameworkDownUpGetUpEnable()
{
	return GetParentFrame()->GetParent() != NULL
		|| GetMode() == ModeMinimum;
}
bool PlaylistListView::WndFrameworkDownUpGetDownEnable()
{
	return GetParentFrame()->GetParent() == NULL
		|| GetMode() == ModeNormal;
}

bool PlaylistListView::TransparentFrameWndDownUpGetUpEnable()
{
	return GetParentFrame()->GetParent() != NULL &&
		GetMode() == ModeNormal;
}
bool PlaylistListView::TransparentFrameWndDownUpGetDownEnable()
{
	return GetParentFrame()->GetParent() == NULL &&
		GetMode() == ModeMinimum;
}

PlaylistListView::EMode PlaylistListView::GetMode()
{
	return m_emode;
}

void PlaylistListView::_001OnLButtonDblClk(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj)
   int iItem;
   if(_001HitTest_(pmouse->m_pt, iItem))
   {
      PlaylistDoc * pDoc = GetDocument();
      pDoc->SetCurrentSong(
         iItem, 
         _vmspl::SetCurrentSongHintDoPlay,
         true);
/*      PaneView * pview = GetParentPane();
      if(pview != NULL)
      {
         pview->SetPane(0);
      }*/
      
   }
}




int PlaylistListView::_001GetItemImage(int iItem, int iSubItem, int iListItem)
{
	if(iSubItem == 0
		|| iSubItem == 1)
	{
		return 0;
	}
	else
		return -1;
}

void PlaylistListView::_001OnContextMenu(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::context_menu, pcontextmenu, pobj)
   CPoint point = pcontextmenu->GetPoint();
   int iItem;
   CPoint ptClient = point;
   ScreenToClient(&ptClient);
  	if(_001HitTest_(ptClient, iItem))
	{
      SimpleMenu menu(BaseMenuCentral::GetMenuCentral());
      if (menu.LoadMenu(IDR_POPUP_PLAYLIST_ITEM))
      {
         SimpleMenu* pPopup = (SimpleMenu *) menu.GetSubMenu(0);
         ASSERT(pPopup != NULL);
         CFrameWnd * pframe = GetParentFrame();
         pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
            point.x, point.y,
            (CWnd *) pframe);
      }
   }
   else
   {
      CMenu menu;
      if (menu.LoadMenu(IDR_POPUP_PLAYLIST))
      {
         CMenu* pPopup = menu.GetSubMenu(0);
         ASSERT(pPopup != NULL);
         CFrameWnd * pframe = GetParentFrame();
         pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
            point.x, point.y,
            (CWnd *) pframe);
      }
   }
}

void PlaylistListView::_001OnSize(gen::signal_object * pobj) 
{
	pobj->previous();
	
   UpdateDrawingObjects();
}

void PlaylistListView::UpdateDrawingObjects()
{
   MusicalPlayerLightApp * papp = (MusicalPlayerLightApp *) AfxGetApp();
	ASSERT(papp != NULL);
	Savings & savings = Savings::AppGetSavings();
   m_enhmetafile = papp->LoadEnhMetaFile(IDR_MUSICALPLAYER);
	if(m_enhmetafile != NULL)
	{
        GetEnhMetaFileHeader(
            m_enhmetafile,
            sizeof(m_emh),
            &m_emh);
	}

}

void PlaylistListView::_001OnDraw(CDC *pdc)
{
   SimpleFormListView::_001OnDraw(pdc);
}

void PlaylistListView::_001OnEditRemove(gen::signal_object * pobj) 
{
   _001RemoveSelection();
}

void PlaylistListView::_001OnUpdateEditRemove(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::update_cmd_ui, pupdatecmdui, pobj)

	Range range;

	_001GetSelection(range);

	pupdatecmdui->m_pcmdui->Enable(range.GetItemCount() > 0);

}

bool PlaylistListView::_001OnRemoveItem(int iItem)
{
   PlaylistDoc * pdoc = GetDocument();
   return pdoc->RemoveSong(iItem);
}

PaneView * PlaylistListView::GetParentPane()
{
   CWnd * pwnd = GetParent();
   if(pwnd->IsKindOf(RUNTIME_CLASS(PaneView)))
   {
      return dynamic_cast < PaneView * > (pwnd);
   }
   return NULL;
}

void PlaylistListView::_001DrawBackground(CDC *pdc, LPRECT lprect)
{
   CRect rectThis;
   GetClientRect(rectThis);

   Ex1ListInterface::_001DrawBackground(pdc, lprect);
   
/*	if(m_enhmetafile != NULL)
	{
      CRect rectUpdate;
      pdc->GetClipBox(rectUpdate);
		CBaseRect rectMeta;

		rectMeta.left = 0;
		rectMeta.top = 0;
		rectMeta.right = m_emh.rclBounds.right - m_emh.rclBounds.left;
		rectMeta.bottom = m_emh.rclBounds.bottom - m_emh.rclBounds.top;
		rectMeta.FitOnCenterOf(rectThis);

		m_gdibuffer.GetBuffer()->PlayMetaFile(m_enhmetafile, rectMeta);

		CImaging * pimaging = CImaging::GetImaging();
		pimaging->BitmapBlend(
			pdc,
			rectUpdate.left,
			rectUpdate.top,
			rectUpdate.Width(),
			rectUpdate.Height(),
			m_gdibuffer.GetBuffer(),
			rectUpdate.left,
			rectUpdate.top,
			96);
	}*/

}

void PlaylistListView::_001OnPlaylistExecutePlay(gen::signal_object * pobj) 
{
   Range range;
   _001GetSelection(range);
   if(range.GetItemCount() > 0)
   {
      int iItem = range.ItemAt(0).GetLBound();
      PlaylistDoc * pDoc = GetDocument();
      pDoc->SetCurrentSong(
         iItem, 
         _vmspl::SetCurrentSongHintDoPlay,
         true);
   }

	
}

void PlaylistListView::_001OnUpdatePlaylistExecutePlay(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::update_cmd_ui, pupdatecmdui, pobj)
   Range range;
   _001GetSelection(range);
   pupdatecmdui->m_pcmdui->Enable(range.GetItemCount() > 0);
}


void PlaylistListView::_001OnInitializeForm(Ex1FormInterfaceControl &control)
{

   switch(control.m_uiId)
   {
   case 123: // PlayButton
      {
         BaseButtonControl * pbutton = (BaseButtonControl *) control.m_pwnd;
         pbutton->m_pimagelistNormal = &m_imagelistNormal;
         pbutton->m_iImageNormal = 0;
         pbutton->m_pimagelistItemHover = &m_imagelistItemHover;
         pbutton->m_iImageItemHover = 0;
         pbutton->m_pimagelistSubItemHover = &m_imagelistSubItemHover;
         pbutton->m_iImageSubItemHover = 0;
      }
   }

}

void PlaylistListView::_001OnButtonAction(
   Ex1FormInterfaceControl &control)
{
   if(control.m_uiId == 123) // Play Button
   {
      PlaylistDoc * pdoc = GetDocument();
      pdoc->SetCurrentSong(
         control.GetEditItem(), 
         _vmspl::SetCurrentSongHintDoPlay,
         true);
   }
}

int PlaylistListView::_001GetItemCount()
{
   if(GetDocument() != NULL)
      return GetDocument()->GetSongCount();
   else
      return -1;
}

