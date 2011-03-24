// AlbumView.cpp : implementation file
//

#include "stdafx.h"

#include "MediaLibraryDoc.h"
#include "MediaLibraryListView.h"
#include "MediaLibraryViewUpdateHint.h"

#include "mediamanager/AlbumBuild.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryListView

IMPLEMENT_DYNCREATE(MediaLibraryListView, SimpleListView)

MediaLibraryListView::MediaLibraryListView()
{
   m_bKickActive = false;

   SetCacheInterface(&m_cache);
   
   EnableBuffering(true);

   m_etranslucency = TranslucencyPresent;

   DISetSection("AlbumView");

   IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK        , this, this, &MediaLibraryListView::_001OnLButtonDblClk);
	IGUI_WIN_MSG_LINK(WM_TIMER                , this, this, &MediaLibraryListView::_001OnTimer);
	IGUI_WIN_MSG_LINK(WM_SIZE                 , this, this, &MediaLibraryListView::_001OnSize);
	IGUI_WIN_MSG_LINK(WM_CONTEXTMENU          , this, this, &MediaLibraryListView::_001OnContextMenu);
	IGUI_WIN_ON_COMMAND(ID_ALBUM_EXECUTE_PLAY , this, this, &MediaLibraryListView::_001OnAlbumExecutePlay);
	IGUI_WIN_UPD_CMD_UI(ID_ALBUM_EXECUTE_PLAY , this, this, &MediaLibraryListView::_001OnUpdateAlbumExecutePlay);
	IGUI_WIN_ON_COMMAND(ID_EXECUTE_PREVIOUS   , this, this, &MediaLibraryListView::_001OnExecutePrevious);
	IGUI_WIN_UPD_CMD_UI(ID_EXECUTE_PREVIOUS   , this, this, &MediaLibraryListView::_001OnUpdateExecutePrevious);
	IGUI_WIN_ON_COMMAND(ID_EXECUTE_NEXT       , this, this, &MediaLibraryListView::_001OnExecuteNext);
	IGUI_WIN_UPD_CMD_UI(ID_EXECUTE_NEXT       , this, this, &MediaLibraryListView::_001OnUpdateExecuteNext);
   IGUI_WIN_MSG_LINK(WM_USER + 1217          , this, this, &MediaLibraryListView::_001OnFillTaskResponse);

}

MediaLibraryListView::~MediaLibraryListView()
{
}


BEGIN_MESSAGE_MAP(MediaLibraryListView, SimpleListView)
	//{{AFX_MSG_MAP(MediaLibraryListView)
/*
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_ALBUM_EXECUTE_PLAY, OnAlbumExecutePlay)
	ON_UPDATE_COMMAND_UI(ID_ALBUM_EXECUTE_PLAY, OnUpdateAlbumExecutePlay)
	ON_COMMAND(ID_EXECUTE_PREVIOUS, OnExecutePrevious)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_PREVIOUS, OnUpdateExecutePrevious)
	ON_COMMAND(ID_EXECUTE_NEXT, OnExecuteNext)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_NEXT, OnUpdateExecuteNext)
	//}}AFX_MSG_MAP
   ON_MESSAGE(WM_USER + 1217, OnFillTaskResponse)
  */
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryListView diagnostics

#ifdef _DEBUG
void MediaLibraryListView::AssertValid() const
{
	SimpleListView::AssertValid();
}

void MediaLibraryListView::Dump(CDumpContext& dc) const
{
	SimpleListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryListView message handlers


void MediaLibraryListView::_001InsertColumns()
{

   DBCentralInterface * pDataCentral = DB();

	Column column;
		column.m_iWidth = 50;
//		column.m_uiText = IDS_PLAYLIST_CODE;
		column.m_iSubItem = SubItemId;
//		column.m_uiSmallBitmap = IDB_ALBUM_SMALL_256;
		column.m_iSmallImageWidth = 16;
		column.m_crSmallMask = RGB(255, 0, 255);
		_001AddColumn(column);

		column.m_iWidth = 170;
//		column.m_uiText = IDS_PLAYLIST_CODE;
		column.m_iSubItem = SubItemTitle;
//		column.m_uiSmallBitmap = IDB_ALBUM_SMALL_256;
		column.m_iSmallImageWidth = 16;
		column.m_crSmallMask = RGB(255, 0, 255);
		_001AddColumn(column);

//		column.m_uiText = IDS_PLAYLIST_SONG_NAME;
		column.m_iWidth = 200;
		column.m_iSubItem = SubItemArtist;
		_001AddColumn(column);

//		column.m_uiText = IDS_PLAYLIST_SONG_NAME;
		column.m_iWidth = 400;
		column.m_iSubItem = SubItemFileName;
		_001AddColumn(column);

		column.m_iWidth = 400;
		column.m_iSubItem = SubItemFilePath;
		_001AddColumn(column);


}


int MediaLibraryListView::_001GetItemImage(int iItem, int iSubItem, int iListItem)
{
	if(iSubItem == 0
		|| iSubItem == 1)
	{
		return -1;
	}
	else
		return -1;
}

bool MediaLibraryListView::_001GetItemText(CString &wstr, int iItem, int iSubItem, int iListItem)
{
   /*if(SimpleListView::_001GetItemText(
      wstr,
      iItem, 
      iSubItem, 
      iListItem))
   {
      return true;
   }*/
   
   MediaLibraryDoc * pdoc = GetDocument();
   CSingleLock sl(pdoc->m_pcsAlbum1, TRUE);
   _vmssqlite::Dataset * pds = pdoc->m_pdsAlbum1;
   //pds->seek(iItem);

   if((iSubItem != SubItemFileName &&
      iSubItem != SubItemFilePath) &&
      (mediamanager::GetMediaManager()->
      GetAlbumBuild().m_fileinfo.m_iaUpdate.GetSize() > 0
      || 
      mediamanager::GetMediaManager()->
      GetAlbumBuild().m_fileinfo.m_iaRemove.GetSize() > 0))
   {
      int iId;
      iId = pds->result.records[iItem][FieldIndexId].get_asInteger();
      int iFound;
      if((iFound = mediamanager::GetMediaManager()->GetAlbumBuild().m_fileinfo.m_iaUpdate.FindFirst(iId)) >= 0)
      {
         KickBuild();
         wstr.Empty();
         return false;
      }
      else if((iFound = mediamanager::GetMediaManager()->GetAlbumBuild().m_fileinfo.m_iaRemove.FindFirst(iId)) >= 0)
      {
         KickBuild();
         wstr.Empty();
         return false;
      }
   }

//   CString strSql;
//   strSql.Format("select title, filename, filepath from album where filepath = '%s';",
//      mediamanager::AlbumRecord::Prepare(pdoc->m_fileinfo.m_wstraNew[iItem]));

//   pdoc->m_pdsAlbumRecord->query(strSql);
//   if(pdoc->m_pdsAlbumRecord->num_rows() <= 0)
  // {
   //}
   //else*/
   {
      EFieldIndex eindex;
      switch(iSubItem)
      {
      case SubItemId:
         eindex = FieldIndexId;
         break;
      case SubItemTitle:
         eindex = FieldIndexTitle;
         break;
      case SubItemArtist:
         eindex = FieldIndexArtist;
         break;
      case SubItemFileName:
         eindex = FieldIndexFileName;
         break;;
      case SubItemFilePath:
         eindex = FieldIndexFilePath;
         break;
      default:
         ASSERT(FALSE);
         eindex = FieldIndexNone;
         break;
      }
      if(eindex == FieldIndexNone)
      {
         wstr.Empty();
         return true;
      }
      else if(eindex == FieldIndexId)
      {
         wstr.Format("%05d", pds->result.records[iItem][(int) eindex].get_asInteger());
         return true;
      }
      else
      {
         wstr = pds->result.records[iItem][(int) eindex].get_asString();
         return true;
      }
   }
   wstr.Empty();
   return false;
}

bool MediaLibraryListView::_001SearchGetItemText(CString &wstr, int iItem, int iSubItem, int iListItem)
{
   MediaLibraryDoc * pdoc = GetDocument();
   CSingleLock sl(pdoc->m_pcsAlbum1, TRUE);
   _vmssqlite::Dataset * pds = pdoc->m_pdsAlbum1;

   if((iSubItem != SubItemFileName &&
      iSubItem != SubItemFilePath) &&
      (mediamanager::GetMediaManager()->
      GetAlbumBuild().m_fileinfo.m_iaUpdate.GetSize() > 0
      || 
      mediamanager::GetMediaManager()->
      GetAlbumBuild().m_fileinfo.m_iaRemove.GetSize() > 0))
   {
      int iId;
      iId = pds->result.records[iItem][FieldIndexId].get_asInteger();
      int iFound;
      if((iFound = mediamanager::GetMediaManager()->GetAlbumBuild().m_fileinfo.m_iaUpdate.FindFirst(iId)) >= 0)
      {
         wstr.Empty();
         return false;
      }
      else if((iFound = mediamanager::GetMediaManager()->GetAlbumBuild().m_fileinfo.m_iaRemove.FindFirst(iId)) >= 0)
      {
         wstr.Empty();
         return false;
      }
   }

   EFieldIndex eindex;
   switch(iSubItem)
   {
   case SubItemId:
      eindex = FieldIndexId;
      break;
   case SubItemTitle:
      eindex = FieldIndexTitle;
      break;
   case SubItemArtist:
      eindex = FieldIndexArtist;
      break;
   case SubItemFileName:
      eindex = FieldIndexFileName;
      break;;
   case SubItemFilePath:
      eindex = FieldIndexFilePath;
      break;
   default:
      ASSERT(FALSE);
      eindex = FieldIndexNone;
      break;
   }
   if(eindex == FieldIndexNone)
   {
      wstr.Empty();
      return true;
   }
   else if(eindex == FieldIndexId)
   {
      wstr.Format("%05d",
         pds->result.records[iItem][(int) eindex].get_asInteger());
      return true;
   }
   else
   {
      wstr = pds->result.records[iItem][(int) eindex].get_asString();
      return true;
   }
   wstr.Empty();
   return false;
}

MediaLibraryDoc * MediaLibraryListView::GetDocument()
{
   return (MediaLibraryDoc *) m_pDocument;
}

void MediaLibraryListView::OnUpdate(BaseView* pSender, LPARAM lHint, CObject* phint) 
{
   if(phint == NULL)
   {
      _001UpdateColumns();
      _001OnUpdateItemCount();	
      mediamanager::GetMediaManager()->GetAlbumBuild().SetCallbackWnd(GetSafeHwnd());
   }
   else
   {
      if(phint->IsKindOf(RUNTIME_CLASS(MediaLibraryViewUpdateHint)))
      {
         MediaLibraryViewUpdateHint * puh = (MediaLibraryViewUpdateHint *) phint;
         if(puh->IsTypeOf(MediaLibraryViewUpdateHint::TypeFilter))
         {
            m_cache._001Invalidate();
            if(puh->m_strFilter.IsEmpty())
            {
               FilterClose();
            }
            else
            {
               FilterBegin();
               Filter1(puh->m_strFilter);
            }
         }
      }
   }

	
}

void MediaLibraryListView::_001OnLButtonDblClk(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj)
	int iItem;
   if(_001HitTest_(pmouse->m_pt, iItem))
	{
      CString wstr;
      GetSongPath(wstr, iItem);
      MusicalPlayerLightApp * papp = (MusicalPlayerLightApp *) AfxGetApp();
      PlaylistDoc * pdoc = papp->GetPlaylistCentral().GetCurrentPlaylist(true, false);
      if(pdoc != NULL)
      {
         pdoc->AddSong(
            wstr,
            PlaylistDoc::AddSongAndPlayIfNotPlaying, 
            false,
            true);
      }
	}
	
	pmouse->previous();
}

bool MediaLibraryListView::GetSongPath(CString &wstr, int iItem)
{
   return _001GetItemText(wstr, iItem, SubItemFilePath, -1);
}

void MediaLibraryListView::_001OnSort()
{
   CString strSql;

   strSql = "select id, title, artist, filename, filepath from album";

   if(m_sortinfo.m_itema.GetSize() > 0)
   {
      strSql += " order by ";

      for(int i = 0; i < m_sortinfo.m_itema.GetSize(); i++)
      {
         CSortInfoItem & item = m_sortinfo.m_itema[i];
         switch(item.m_iSubItem)
         {
         case SubItemId:
            strSql += "id";
            break;
         case SubItemTitle:
            strSql += "title";
            break;
         case SubItemArtist:
            strSql += "artist";
            break;
         case SubItemFileName:
            strSql += "filename";
            break;
         case SubItemFilePath:
            strSql += "filepath";
            break;
         }
         if(!item.m_bAscendent)
         {
            strSql += " desc";
         }
         if(i < m_sortinfo.m_itema.GetSize() - 1)
            strSql += ", ";
      }
   }
   strSql += ";";
   

   CSingleLock sl(GetDocument()->m_pcsAlbum1, TRUE);
   GetDocument()->m_pdsAlbum1->query(strSql);

   m_cache._001Invalidate();

   RedrawWindow();

}

void MediaLibraryListView::PostFillTask(CString &wstrFile, UINT uiTimer)
{
   ASSERT(FALSE);
//   FillTask * ptask = new FillTask(this, wstrFile);
  // ptask->m_uiTimer = uiTimer;
   //AfxBeginThread(
     // ThreadProcFillTask,
      //(LPVOID)  ptask);
}

UINT AFX_CDECL MediaLibraryListView::ThreadProcFillTask(LPVOID lpParameter)
{
   
   ASSERT(FALSE);

   /*FillTask * ptask = (FillTask *) lpParameter;

   ptask->m_pview->KillTimer(1123);

   WString & wstrPath = ptask->m_wstrFile;
   MediaLibraryDoc * pdoc = ptask->m_pview->GetDocument();
   _vmssqlite::Dataset * pds = pdoc->m_pdsAlbum;
   
   int iFind;
   if((iFind = pdoc->m_fileinfo.m_wstraAdd.FindFirst(wstrPath)) >= 0)
   {
      mediamanager::GetMediaManager()->GetAlbumBuild().Add(wstrPath, pdoc->m_fileinfo.m_timeaAdd[iFind]);
      pdoc->m_fileinfo.m_wstraAdd.RemoveAt(iFind);
      pdoc->m_fileinfo.m_timeaAdd.RemoveAt(iFind);
   }
   else if((iFind = pdoc->m_fileinfo.m_wstraUpdate.FindFirst(wstrPath)) >= 0)
   {
      mediamanager::GetMediaManager()->GetAlbumBuild().Update(wstrPath, pdoc->m_fileinfo.m_timeaUpdate[iFind]);
      pds->SetFieldValue("title", _vmssqlite::CFieldValue(mediamanager::GetMediaManager()->GetAlbumBuild().GetAlbumRecord().m_wstrTitle));
      pds->SetFieldValue("filename", _vmssqlite::CFieldValue(mediamanager::GetMediaManager()->GetAlbumBuild().GetAlbumRecord().m_wstrFileName));
      pdoc->m_fileinfo.m_iaUpdate.RemoveAt(iFind);
      pdoc->m_fileinfo.m_wstraUpdate.RemoveAt(iFind);
      pdoc->m_fileinfo.m_timeaUpdate.RemoveAt(iFind);
   }
   else if((iFind = pdoc->m_fileinfo.m_wstraRemove.FindFirst(wstrPath)) >= 0)
   {
      pdoc->m_fileinfo.m_iaRemove.RemoveAt(iFind);
      pdoc->m_fileinfo.m_wstraRemove.RemoveAt(iFind);
      pds->remove_row();
   }

   ptask->m_pview->PostMessage(WM_USER + 1217, 0, (LPARAM) ptask);*/


   

   return 0;
}

void MediaLibraryListView::_001OnTimer(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::timer, ptimer, pobj);
   if(ptimer->m_nIDEvent == 123654)
   {
      KillTimer(123654);
      m_bKickActive = false;
      
   }
/*   if(nIDEvent == 1123)
   {
      KillTimer(1123);
      MediaLibraryDoc * pdoc = GetDocument();
      if(pdoc->m_bBuilt == true)
      {
         KillTimer(nIDEvent);
      }
      else
      {
         KillTimer(1124);
         int iTopIndex = _001GetTopIndex();
         if(m_buildhelper.m_iTopIndex != iTopIndex)
         {
            m_buildhelper.m_iTopIndex = iTopIndex;
            m_buildhelper.m_iStep = 0;
         }
         int iItem;

      
         _vmssqlite::Dataset * pds = pdoc->m_pdsAlbum;

         int iRemove = max(30, m_buildhelper.m_iDisplayItemCount);

         BaseIntArray iaRemove;
         while(true)
         {
            iItem = m_buildhelper.m_iStep + m_buildhelper.m_iTopIndex;

            if(m_buildhelper.m_iStep >= m_buildhelper.m_iDisplayItemCount)
            {
               KillTimer(1123);
               SetTimer(1124, 50, NULL);
               m_buildhelper.m_bActive = false;
               break;
            }

            m_buildhelper.m_iStep++;

            pds->seek(iItem);

            WString wstrPath;
            wstrPath = pds->fv("filepath").get_asString();

            int iFind;
            if((iFind = pdoc->m_fileinfo.m_wstraAdd.FindFirst(wstrPath)) >= 0)
            {
               PostFillTask(wstrPath, nIDEvent);
               break;
            }
            else if((iFind = pdoc->m_fileinfo.m_wstraUpdate.FindFirst(wstrPath)) >= 0)
            {
               PostFillTask(wstrPath, nIDEvent);
               break;
            }
            else if((iFind = pdoc->m_fileinfo.m_wstraRemove.FindFirst(wstrPath)) >= 0)
            {
               iaRemove.Add(pdoc->m_fileinfo.m_iaRemove[iFind]);
               pdoc->m_fileinfo.m_iaRemove.RemoveAt(iFind);
               pdoc->m_fileinfo.m_wstraRemove.RemoveAt(iFind);
               pds->remove_row();
               iRemove--;
               m_buildhelper.m_iStep--;
               if(iRemove < 0)
                  break;
            }
         }
         mediamanager::GetMediaManager()->GetAlbumBuild().Remove(iaRemove);
      }

   }
   else if(nIDEvent == 1124)
   {
      KillTimer(1124);
      MediaLibraryDoc * pdoc = GetDocument();
      _vmssqlite::Dataset * pds = pdoc->m_pdsAlbum;

      int iRemove = max(30, m_buildhelper.m_iDisplayItemCount);

      BaseIntArray iaRemove;
      int iFind = 0;
      _vmssqlite::CFieldValue fv;
      while(true)
      {
         if(iFind < pdoc->m_fileinfo.m_iaUpdate.GetSize())
         {
            fv = pdoc->m_fileinfo.m_iaUpdate[iFind];
            if(pds->find_first("id", fv))
            {
               PostFillTask(pds->fv("filepath").get_asString(), nIDEvent);
               break;
            }
            else
            {
               ASSERT(FALSE);
            }

         }
         else if(iFind < pdoc->m_fileinfo.m_iaRemove.GetSize())
         {
            fv = pdoc->m_fileinfo.m_iaRemove[iFind];
            if(pds->find_first("id", fv))
            {
               iaRemove.Add(pdoc->m_fileinfo.m_iaRemove[iFind]);
               pdoc->m_fileinfo.m_iaRemove.RemoveAt(iFind);
               pdoc->m_fileinfo.m_wstraRemove.RemoveAt(iFind);
               pds->remove_row();
               iRemove--;
               m_buildhelper.m_iStep--;
               if(iRemove < 0)
                  break;
            }
            else
            {
               ASSERT(FALSE);
            }
         }
         else
         {
            pdoc->m_bBuilt = true;
            break;
         }
      }
   }*/
	ptimer->previous();
}


MediaLibraryListView::BuildHelper::BuildHelper()
{
   m_iTopIndex          = -1;
   m_bActive            = false;
   m_iStep              = -1;
   m_iDisplayItemCount  = -1;
}

void MediaLibraryListView::_001OnSize(gen::signal_object * pobj) 
{
	pobj->previous();
	
   //m_buildhelper.m_iDisplayItemCount = _001GetDisplayItemCount();
	
}

/*void MediaLibraryListView::KickBuildMachine(bool bDisplayOnly)
{
   if(bDisplayOnly)
   {
      m_buildhelper.m_bActive = true;
      SetTimer(1123, 50, NULL);
   }
   else
   {
      m_buildhelper.m_bActive = true;
      SetTimer(1124, 50, NULL);
   }
}*/

/*MediaLibraryListView::FillTask::FillTask(MediaLibraryListView * pview, LPWString lpcsz)         
:
m_pview(pview),m_wstrFile(lpcsz)
{
}*/

void MediaLibraryListView::_001OnFillTaskResponse(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::base, pbase, pobj)
   m_bKickActive = true;
   if(pbase->m_wparam == 0)
   {
      m_cache._001Invalidate();
      _001OnUpdateItemCount();
      Layout();
      RedrawWindow();
      //FillTask * ptask = (FillTask *) lparam;

      //if(ptask != NULL)
      {
        // SetTimer(ptask->m_uiTimer, 50, NULL);

         //delete ptask;
      }

   }
   else if(pbase->m_wparam == 1)
   {

      m_cache._001Invalidate();
      int iId = pbase->m_lparam;
      if(iId >= 0)
      {
         MediaLibraryDoc * pdoc = GetDocument();
         CSingleLock sl(pdoc->m_pcsAlbum1, TRUE);
         _vmssqlite::Dataset * pds = pdoc->m_pdsAlbum1;
         CRect rect;
         int iItemCount = _001GetDisplayItemCount();
         int iItemFirst = _001GetTopIndex();
         int iFound = -1;
         for(int iDisplayItem = iItemFirst;
            iDisplayItem < iItemFirst + iItemCount;
            iDisplayItem++)
         {
            int iItem = DisplayToStrict(iDisplayItem);
            if(iId == pds->result.records[iItem][FieldIndexId].get_asInteger())
            {
               iFound = iItem;
               break;
            }

         }

         if(iFound < 0)
         {
            _001RedrawWindow();
         }
         else
         {
            _001GetItemRect(-1, iFound, rect);
            _001RedrawWindow(rect);
         }
      }
      else
      {
         _001RedrawWindow();
      }
      //_001SetItemCountEx(GetDocument()->GetSongCount());
   }
   else if(pbase->m_wparam == 2)
   {
      //m_cache._001Invalidate();
      _001OnUpdateItemCount();
   }
   else if(pbase->m_wparam == 3)
   {
      m_cache._001Invalidate();
   }
}

void MediaLibraryListView::KickBuild(int iItem)
{

   int iTopIndex = _001GetTopIndex();
   int iDisplayItemCount = _001GetDisplayItemCount();

   if(m_bKickActive && 
      m_buildhelper.m_iTopIndex == iTopIndex && 
      m_buildhelper.m_iDisplayItemCount == iDisplayItemCount)
      return;

   m_buildhelper.m_iTopIndex = iTopIndex;
   m_buildhelper.m_iDisplayItemCount = iDisplayItemCount;

   m_bKickActive = true;

   MediaLibraryDoc * pdoc = GetDocument();

   BaseIntArray & ia = mediamanager::GetMediaManager()->GetAlbumBuild().GetPriorityArray();
   ia.RemoveAll();

   int iId;
   CSingleLock sl(pdoc->m_pcsAlbum1, TRUE);
   _vmssqlite::Dataset * pds = pdoc->m_pdsAlbum1;
   for(int i = 0; i < iDisplayItemCount; i++)
   {
      int iItem = DisplayToStrict(iTopIndex + i);
      if(iItem >= 0)
      {
         pds->seek(iItem);
         iId = pds->fv("id").get_asInteger();
         ia.Add(iId);
      }
   }


   //mediamanager::GetMediaManager()->KickBuildAlbum();
      
   SetTimer(123654, 700, NULL);

}

void MediaLibraryListView::_001OnContextMenu(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::context_menu, pcontextmenu, pobj)
   CPoint point = pcontextmenu->GetPoint();

   int iItem;
   CPoint ptClient = point;
   ScreenToClient(&ptClient);
  	if(_001HitTest_(ptClient, iItem))
	{
      SimpleMenu menu(BaseMenuCentral::GetMenuCentral());
      if (menu.LoadMenu(IDR_POPUP_ALBUM_ITEM))
      {
         SimpleMenu* pPopup = (SimpleMenu *) menu.GetSubMenu(0);
         ASSERT(pPopup != NULL);
         CFrameWnd * pframe = GetParentFrame()->GetParentFrame();
         pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
            point.x, point.y,
            (CWnd *) pframe);
      }
   }
   else
   {
      CMenu menu;
      if (menu.LoadMenu(IDR_POPUP_ALBUM))
      {
         CMenu* pPopup = menu.GetSubMenu(0);
         ASSERT(pPopup != NULL);
         CFrameWnd * pframe = GetParentFrame()->GetParentFrame();
         pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
            point.x, point.y,
            (CWnd *) pframe);
      }
   }
}

void MediaLibraryListView::_001OnAlbumExecutePlay(gen::signal_object * pobj) 
{
   Range range;
   _001GetSelection(range);
   CString wstr;
   for(int i = 0; i < range.GetItemCount(); i++)
   {
      ItemRange & item = range.ItemAt(i);
      for(int j = item.GetLBound(); j <= item.GetUBound(); j++)
      {
         GetSongPath(wstr, j);
         MusicalPlayerLightApp * papp = (MusicalPlayerLightApp *) AfxGetApp();
         PlaylistDoc * pdoc = papp->GetPlaylistCentral().GetCurrentPlaylist(true, false);
         if(pdoc != NULL)
         {
            pdoc->AddSong(
               wstr,
               PlaylistDoc::AddSongAndPlayIfNotPlaying, 
               false,
               true);
         }
      }
	}

	
}

void MediaLibraryListView::_001OnUpdateAlbumExecutePlay(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::update_cmd_ui, pupdatecmdui, pobj)
   Range range;
   _001GetSelection(range);
   pupdatecmdui->m_pcmdui->Enable(range.GetItemCount() > 0);
}

void MediaLibraryListView::_001OnExecutePrevious(gen::signal_object * pobj) 
{
	// TODO: Add your command handler code here
	
}

void MediaLibraryListView::_001OnUpdateExecutePrevious(gen::signal_object * pobj) 
{
	// TODO: Add your command update UI handler code here
	
}

void MediaLibraryListView::_001OnExecuteNext(gen::signal_object * pobj) 
{
	// TODO: Add your command handler code here
	
}

void MediaLibraryListView::_001OnUpdateExecuteNext(gen::signal_object * pobj) 
{
	// TODO: Add your command update UI handler code here
	
}

int MediaLibraryListView::_001GetItemCount() 
{
   if(GetDocument() != NULL)
      return GetDocument()->GetSongCount();
   else
      return 0;
}
