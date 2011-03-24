#include "StdAfx.h"
#include "MediaLibraryDoc.h"
#include "mplite_library_list_view.h"
#include "mplite_library_view.h"
#include "MediaLibraryViewUpdateHint.h"
#include "mediamanager/AlbumBuild.h"

namespace mplite
{

   namespace library
   {

      list_view::list_view(::ca::application * papp) :
         ca(papp),
         ::user::scroll_view(papp),
         ::user::list(papp),
         ::user::form(papp),
         ::user::form_list(papp),
         ::userbase::view(papp),
         ::userbase::form_list(papp),
         simple_list_view(papp)
      {
         m_bKickActive = false;

         SetCacheInterface(&m_cache);
         

         m_etranslucency = TranslucencyPresent;

         m_dataid = "AlbumView";

         m_pil = new image_list(get_app());

         m_pil->create(16, 16, 0, 0, 0);

         m_iIconFolder = m_pil->add_matter_icon("mplite/vmskarlib_folder_normal.ico");

         m_iIconArtist = m_pil->add_matter_icon("mplite/vmskarlib_artist_normal.ico");

         m_iIconSong = m_pil->add_matter_icon("mplite/vmskarlib_song_normal.ico");

      }

      list_view::~list_view()
      {
      }

      void list_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
      {
         simple_list_view::_001InstallMessageHandling(pinterface);
         InstallBuffering(pinterface);
         IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK, pinterface, this, &list_view::_001OnLButtonDblClk);
         IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &list_view::_001OnTimer);
         IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &list_view::_001OnSize);
         IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &list_view::_001OnContextMenu);
         IGUI_WIN_MSG_LINK(WM_ERASEBKGND, pinterface, this, &list_view::_001OnEraseBkgnd);
         IGUI_WIN_MSG_LINK(WM_USER + 1217    , pinterface, this, &list_view::_001OnFillTaskResponse);

         connect_command(        "ID_ALBUM_EXECUTE_PLAY"   , &list_view::_001OnAlbumExecutePlay);
         connect_update_cmd_ui(  "ID_ALBUM_EXECUTE_PLAY"   , &list_view::_001OnUpdateAlbumExecutePlay);
         connect_command(        "ID_EXECUTE_PREVIOUS"     , &list_view::_001OnExecutePrevious);
         connect_update_cmd_ui(  "ID_EXECUTE_PREVIOUS"     , &list_view::_001OnUpdateExecutePrevious);
         connect_command(        "ID_EXECUTE_NEXT"         , &list_view::_001OnExecuteNext);
         connect_update_cmd_ui(  "ID_EXECUTE_NEXT"         , &list_view::_001OnUpdateExecuteNext);
      }



      #ifdef _DEBUG
      void list_view::assert_valid() const
      {
         simple_list_view::assert_valid();
      }

      void list_view::dump(dump_context & dumpcontext) const
      {
         simple_list_view::dump(dumpcontext);
      }
      #endif //_DEBUG


      void list_view::_001InsertColumns()
      {

      // dbbreak  DBCentralInterface * pDataCentral = db();

         Column column;
      /*
         
            column.m_iWidth = 50;
      //      column.m_uiText = IDS_PLAYLIST_CODE;
            column.m_iSubItem = SubItemId;
      //      column.m_uiSmallBitmap = IDB_ALBUM_SMALL_256;
            column.m_iSmallImageWidth = 16;
            column.m_crSmallMask = RGB(255, 0, 255);
            column.m_pil = m_pil;
            _001AddColumn(column);
      */
         column.m_iWidth = 170;
         //      column.m_uiText = IDS_PLAYLIST_CODE;
         column.m_iSubItem = SubItemTitle;
         //      column.m_uiSmallBitmap = IDB_ALBUM_SMALL_256;
         column.m_iSmallImageWidth = 16;
         column.m_crSmallMask = RGB(255, 0, 255);
         column.m_pil = m_pil;
         _001AddColumn(column);

      //      column.m_uiText = IDS_PLAYLIST_SONG_NAME;
            column.m_iWidth = 200;
            column.m_iSubItem = SubItemArtist;
            _001AddColumn(column);

      //      column.m_uiText = IDS_PLAYLIST_SONG_NAME;
            column.m_iWidth = 400;
            column.m_iSubItem = SubItemFileName;
            _001AddColumn(column);

            column.m_iWidth = 400;
            column.m_iSubItem = SubItemFilePath;
            _001AddColumn(column);


      }


      index list_view::_001GetItemImage(index iItem, index iSubItem, index iListItem)
      {
         UNREFERENCED_PARAMETER(iListItem);
         if(iItem < 0 || iItem >= m_itema.get_size())
            return -1;
         if(iSubItem == SubItemTitle)
         {
            switch(m_itema[iItem].m_etype)
            {
            case ItemTypeFolder:
               return m_iIconFolder;
            case ItemTypeArtist:
               return m_iIconArtist;
            case ItemTypeSong:
               return m_iIconSong;
            default:
               ASSERT(FALSE);
               return -1;
            }
         }
         else
         {
            return -1;
         }
         
      }

      bool list_view::_001GetItemText(string &str, index iItem, index iSubItem, index iListItem)
      {
         UNREFERENCED_PARAMETER(iListItem);
         if(iItem < 0 || iItem >= m_itema.get_size())
            return false;
         switch(iSubItem)
         {
         case SubItemId:
            str.Empty();
            break;
         case SubItemTitle:
            str = m_itema[iItem].m_strTitle;
            break;
         case SubItemArtist:
            str.Empty();
            break;
         case SubItemFileName:
            str.Empty();
            break;;
         case SubItemFilePath:
            str.Empty();
            break;
         default:
            ASSERT(FALSE);
            str.Empty();
            break;
         }

         return true;
      }

      bool list_view::_001SearchGetItemText(string &str, index iItem, index iSubItem, index iListItem)
      {
         UNREFERENCED_PARAMETER(iListItem);
         MediaLibraryDoc * pdoc = get_document();
         CSingleLock sl(pdoc->m_pcsAlbum1, TRUE);
         ::sqlite::set * pds = pdoc->m_pdsAlbum1;

         if((iSubItem != SubItemFileName &&
            iSubItem != SubItemFilePath) &&
            (mediamanager::get(get_app())->
            GetAlbumBuild().m_fileinfo.m_iaUpdate.get_size() > 0
            || 
            mediamanager::get(get_app())->
            GetAlbumBuild().m_fileinfo.m_iaRemove.get_size() > 0))
         {
            int iId;
            iId = pds->result.records[iItem][FieldIndexId].get_integer();
            int iFound;
            if((iFound = mediamanager::get(get_app())->GetAlbumBuild().m_fileinfo.m_iaUpdate.find_first(iId)) >= 0)
            {
               str.Empty();
               return false;
            }
            else if((iFound = mediamanager::get(get_app())->GetAlbumBuild().m_fileinfo.m_iaRemove.find_first(iId)) >= 0)
            {
               str.Empty();
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
            str.Empty();
            return true;
         }
         else if(eindex == FieldIndexId)
         {
            str.Format("%05d",
               pds->result.records[iItem][(int) eindex].get_integer());
            return true;
         }
         else
         {
            str = pds->result.records[iItem][(int) eindex].get_string();
            return true;
         }
         str.Empty();
         return false;
      }

      MediaLibraryDoc * list_view::get_document()
      {
         return dynamic_cast < MediaLibraryDoc * > (::view::get_document());
      }

      void list_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint) 
      {
         UNREFERENCED_PARAMETER(pSender);
         UNREFERENCED_PARAMETER(lHint);
         if(phint == NULL)
         {
            _001UpdateColumns();
            //_001SetItemCountEx(get_document()->GetSongCount());   
            mediamanager::get(get_app())->GetAlbumBuild().SetCallbackWnd(this);
         }
         else
         {
            /*if(base < MediaLibraryViewUpdateHint >::bases(phint))
            {
               MediaLibraryViewUpdateHint * puh = (MediaLibraryViewUpdateHint *) phint;
               if(puh->is_type_of(MediaLibraryViewUpdateHint::TypeFilter))
               {
                  m_cache._001Invalidate();
                  if(puh->m_wstrFilter.is_empty())
                  {
                     FilterClose();
                  }
                  else
                  {
                     FilterBegin();
                     Filter1(puh->m_wstrFilter);
                  }
               }
            }*/
         }

         
      }

      void list_view::_001OnLButtonDblClk(gen::signal_object * pobj) 
      {
         SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
         index iItem;

         if(_001HitTest_(pmouse->m_pt, iItem))
         {
            if(m_itema[iItem].IsFolder())
            {
               m_pserver->Request(m_itema[iItem].m_id);
            }
            else
            {
               m_pserver->OpenSongFile(
                  m_itema[iItem].m_iId,
                  m_itema[iItem].m_strFileName);
            }
         }
      }

   void list_view::_001OnClick(UINT nFlags, point point) 
   {
      UNREFERENCED_PARAMETER(nFlags);
      index iItem;
      index iSubItem;
      if(_001HitTest_(point, iItem, iSubItem))
      {
         if(m_itema[iItem].IsFolder())
         {
            m_pserver->Request(m_itema[iItem].m_id);
         }
         else
         {
            m_pserver->OpenSongFile(m_itema[iItem].m_iId, m_itema[iItem].m_strFileName);
         }      
      }
   }

      bool list_view::GetSongPath(string &str, int iItem)
      {
         return _001GetItemText(str, iItem, SubItemFilePath, -1);
      }

      void list_view::_001OnSort()
      {
         string strSql;

         strSql = "select id, title, artist, filename, filepath from album";

         if(m_sortinfo.m_itema.get_size() > 0)
         {
            strSql += " order by ";

            for(int i = 0; i < m_sortinfo.m_itema.get_size(); i++)
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
               if(i < m_sortinfo.m_itema.get_size() - 1)
                  strSql += ", ";
            }
         }
         strSql += ";";
         

         CSingleLock sl(get_document()->m_pcsAlbum1, TRUE);
         get_document()->m_pdsAlbum1->query(strSql);

         m_cache._001Invalidate();

         RedrawWindow();

      }

      void list_view::PostFillTask(string & wstrFile, UINT uiTimer)
      {
         UNREFERENCED_PARAMETER(wstrFile);
         UNREFERENCED_PARAMETER(uiTimer);
         ASSERT(FALSE);
      //   FillTask * ptask = new FillTask(this, wstrFile);
        // ptask->m_uiTimer = uiTimer;
         //AfxBeginThread(
           // ThreadProcFillTask,
            //(LPVOID)  ptask);
      }

      UINT AFX_CDECL list_view::ThreadProcFillTask(LPVOID lpParameter)
      {
         UNREFERENCED_PARAMETER(lpParameter);
         ASSERT(FALSE);

         /*FillTask * ptask = (FillTask *) lpParameter;

         ptask->m_pview->KillTimer(1123);

         string & wstrPath = ptask->m_wstrFile;
         MediaLibraryDoc * pdoc = ptask->m_pview->get_document();
         ::sqlite::set * pds = pdoc->m_pdsAlbum;
         
         int iFind;
         if((iFind = pdoc->m_fileinfo.m_wstraAdd.FindFirst(wstrPath)) >= 0)
         {
            mediamanager::GetMediaManager()->GetAlbumBuild().add(wstrPath, pdoc->m_fileinfo.m_timeaAdd[iFind]);
            pdoc->m_fileinfo.m_wstraAdd.remove_at(iFind);
            pdoc->m_fileinfo.m_timeaAdd.remove_at(iFind);
         }
         else if((iFind = pdoc->m_fileinfo.m_wstraUpdate.FindFirst(wstrPath)) >= 0)
         {
            mediamanager::GetMediaManager()->GetAlbumBuild().Update(wstrPath, pdoc->m_fileinfo.m_timeaUpdate[iFind]);
            pds->SetFieldValue("title", sqlite::CFieldValue(mediamanager::GetMediaManager()->GetAlbumBuild().GetAlbumRecord().m_wstrTitle));
            pds->SetFieldValue("filename", sqlite::CFieldValue(mediamanager::GetMediaManager()->GetAlbumBuild().GetAlbumRecord().m_wstrFileName));
            pdoc->m_fileinfo.m_iaUpdate.remove_at(iFind);
            pdoc->m_fileinfo.m_wstraUpdate.remove_at(iFind);
            pdoc->m_fileinfo.m_timeaUpdate.remove_at(iFind);
         }
         else if((iFind = pdoc->m_fileinfo.m_wstraRemove.FindFirst(wstrPath)) >= 0)
         {
            pdoc->m_fileinfo.m_iaRemove.remove_at(iFind);
            pdoc->m_fileinfo.m_wstraRemove.remove_at(iFind);
            pds->remove_row();
         }

         ptask->m_pview->PostMessage(WM_USER + 1217, 0, (LPARAM) ptask);*/


         

         return 0;
      }

      void list_view::_001OnTimer(gen::signal_object * pobj) 
      {
         SCAST_PTR(::user::win::message::timer, ptimer, pobj)
         if(ptimer->m_nIDEvent == 123654)
         {
            KillTimer(123654);
            m_bKickActive = false;
            
         }
      /*   if(nIDEvent == 1123)
         {
            KillTimer(1123);
            MediaLibraryDoc * pdoc = get_document();
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

            
               ::sqlite::set * pds = pdoc->m_pdsAlbum;

               int iRemove = max(30, m_buildhelper.m_iDisplayItemCount);

               int_array iaRemove;
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

                  string wstrPath;
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
                     iaRemove.add(pdoc->m_fileinfo.m_iaRemove[iFind]);
                     pdoc->m_fileinfo.m_iaRemove.remove_at(iFind);
                     pdoc->m_fileinfo.m_wstraRemove.remove_at(iFind);
                     pds->remove_row();
                     iRemove--;
                     m_buildhelper.m_iStep--;
                     if(iRemove < 0)
                        break;
                  }
               }
               mediamanager::GetMediaManager()->GetAlbumBuild().remove(iaRemove);
            }

         }
         else if(nIDEvent == 1124)
         {
            KillTimer(1124);
            MediaLibraryDoc * pdoc = get_document();
            ::sqlite::set * pds = pdoc->m_pdsAlbum;

            int iRemove = max(30, m_buildhelper.m_iDisplayItemCount);

            int_array iaRemove;
            int iFind = 0;
            sqlite::CFieldValue fv;
            while(true)
            {
               if(iFind < pdoc->m_fileinfo.m_iaUpdate.get_size())
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
               else if(iFind < pdoc->m_fileinfo.m_iaRemove.get_size())
               {
                  fv = pdoc->m_fileinfo.m_iaRemove[iFind];
                  if(pds->find_first("id", fv))
                  {
                     iaRemove.add(pdoc->m_fileinfo.m_iaRemove[iFind]);
                     pdoc->m_fileinfo.m_iaRemove.remove_at(iFind);
                     pdoc->m_fileinfo.m_wstraRemove.remove_at(iFind);
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
      }


      list_view::BuildHelper::BuildHelper()
      {
         m_iTopIndex          = -1;
         m_bActive            = false;
         m_iStep              = -1;
         m_iDisplayItemCount  = -1;
      }

      void list_view::_001OnSize(gen::signal_object * pobj) 
      {
         UNREFERENCED_PARAMETER(pobj);
         //m_buildhelper.m_iDisplayItemCount = _001GetDisplayItemCount();
         
      }

      /*void list_view::KickBuildMachine(bool bDisplayOnly)
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

      /*list_view::FillTask::FillTask(list_view * pview, LPWString lpcsz)         
      :
      m_pview(pview),m_wstrFile(lpcsz)
      {
      }*/

      void list_view::_001OnFillTaskResponse(gen::signal_object * pobj)
      {
         SCAST_PTR(::user::win::message::base, pbase, pobj)
         m_bKickActive = true;
         if(pbase->m_wparam == 0)
         {
            m_cache._001Invalidate();
            _001OnUpdateItemCount();
            layout();
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
            _001RedrawWindow();
         }
         else if(pbase->m_wparam == 2)
         {
            _001OnUpdateItemCount();
         }
         else if(pbase->m_wparam == 3)
         {
            m_cache._001Invalidate();
         }
      }

      void list_view::KickBuild(int iItem)
      {
         UNREFERENCED_PARAMETER(iItem);
         int iTopIndex = _001GetTopIndex();
         int iDisplayItemCount = _001GetDisplayItemCount();

         if(m_bKickActive && 
            m_buildhelper.m_iTopIndex == iTopIndex && 
            m_buildhelper.m_iDisplayItemCount == iDisplayItemCount)
            return;

         m_buildhelper.m_iTopIndex = iTopIndex;
         m_buildhelper.m_iDisplayItemCount = iDisplayItemCount;

         m_bKickActive = true;

         MediaLibraryDoc * pdoc = get_document();

         int_array & ia = mediamanager::get(get_app())->GetAlbumBuild().GetPriorityArray();
         ia.remove_all();

         int iId;
         CSingleLock sl(pdoc->m_pcsAlbum1, TRUE);
         ::sqlite::set * pds = pdoc->m_pdsAlbum1;
         for(int i = 0; i < iDisplayItemCount; i++)
         {
            int iItem = DisplayToStrict(iTopIndex + i);
            if(iItem >= 0)
            {
               pds->seek(iItem);
               iId = pds->fv("id").get_integer();
               ia.add(iId);
            }
         }

         mediamanager::get(get_app())->KickBuildAlbum();
            
         SetTimer(123654, 700, NULL);

      }

      void list_view::_001OnContextMenu(gen::signal_object * pobj) 
      {

         SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
         //int iItem;
         point point = pcontextmenu->GetPoint();
         class point ptClient = point;
         ScreenToClient(&ptClient);
       /*    if(_001HitTest_(ptClient, iItem))
         {
            SimpleMenu menu(BaseMenuCentral::GetMenuCentral(get_app()));
            if (menu.LoadMenu(IDR_POPUP_ALBUM_ITEM))
            {
               SimpleMenu* pPopup = (SimpleMenu *) menu.GetSubMenu(0);
               ASSERT(pPopup != NULL);
               frame_window * pframe = GetParentFrame()->GetParentFrame();
               pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                  point.x, point.y,
                  (::ca::window *) pframe);
            }
         }
         else
         {
            ::userbase::menu menu;
            if (menu.LoadMenu(IDR_POPUP_ALBUM))
            {
               ::userbase::menu* pPopup = menu.GetSubMenu(0);
               ASSERT(pPopup != NULL);
               frame_window * pframe = GetParentFrame()->GetParentFrame();
               pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                  point.x, point.y,
                  (::ca::window *) pframe);
            }
         }*/
      }

      void list_view::_001OnAlbumExecutePlay(gen::signal_object * pobj) 
      {
         UNREFERENCED_PARAMETER(pobj);
         Range range;
         _001GetSelection(range);
         string str;
         for(int i = 0; i < range.get_item_count(); i++)
         {
            ItemRange & item = range.ItemAt(i);
            for(int j = item.GetLBound(); j <= item.GetUBound(); j++)
            {
               GetSongPath(str, j);
               PlaylistDoc * pdoc = System.GetPlaylistCentral().GetCurrentPlaylist(true, false);
               if(pdoc != NULL)
               {
                  pdoc->AddSong(
                     str,
                     PlaylistDoc::AddSongAndPlayIfNotPlaying, 
                     false,
                     true);
               }
            }
         }

         
      }

      void list_view::_001OnUpdateAlbumExecutePlay(gen::signal_object * pobj) 
      {
         SCAST_PTR(::user::win::message::update_cmd_ui, pupdatecmdui, pobj)
         Range range;
         _001GetSelection(range);
         pupdatecmdui->m_pcmdui->Enable(range.get_item_count() > 0);
         pupdatecmdui->m_bRet = true;
      }

      void list_view::_001OnExecutePrevious(gen::signal_object * pobj) 
      {
         UNREFERENCED_PARAMETER(pobj);
      }

      void list_view::_001OnUpdateExecutePrevious(gen::signal_object * pobj) 
      {
         UNREFERENCED_PARAMETER(pobj);
      }

      void list_view::_001OnExecuteNext(gen::signal_object * pobj) 
      {
         UNREFERENCED_PARAMETER(pobj);
      }

      void list_view::_001OnUpdateExecuteNext(gen::signal_object * pobj) 
      {
         UNREFERENCED_PARAMETER(pobj);
      }

      void list_view::Parse(const char * lpszSource)
      {
         m_itema.remove_all();
         _001OnUpdateItemCount(0);

         string str;
         xml::node xml(get_app());
         if(xml.load(lpszSource))
         {
            str  = xml.get_xml();
         }
         else
         {
            System.simple_message_box(NULL, "error"); // simple parsing error check
            return;
         }


         xml::node::base_array childs(get_app());

         string wstrType;
         Item item;
         // method 3: Selected Childs with GetChilds()
         // Result: Person, Person, Person
         index iNode = 0;
         xml::node * pnode;
         while((pnode = xml.get_child("folder", iNode)) != NULL)
         {
            wstrType = pnode->get_child_value("type");
            item.m_id = pnode->get_child_value("id");
            item.m_strTitle = pnode->get_child_value("title");

            if(wstrType == "normal")
            {
               item.m_etype = ItemTypeFolder;
            }
            else if(wstrType == "artist")
            {
               item.m_etype = ItemTypeArtist;
            }
            else 
            {
               // unknown item type
               ASSERT(FALSE);
            }

            switch(item.m_etype)
            {
            case ItemTypeFolder:
               item.m_iImage = m_iIconFolder;
               break;
            case ItemTypeArtist:
               item.m_iImage = m_iIconArtist;
               break;
            default:
               // unknown item type
               break;
            }

            
            m_itema.add(item);
            iNode++;
         }

         iNode = 0;
         while((pnode = xml.get_child("song", iNode)) != NULL)
         {
            wstrType = pnode->get_child_value("type");
            item.m_id = pnode->get_child_value("id");
            item.m_iId = atoi(pnode->get_child_value("songfileid"));
            item.m_strTitle = pnode->get_child_value("title");
            item.m_strFileName = pnode->get_child_value("filename");

            item.m_etype = ItemTypeSong;
            item.m_iImage = m_iIconSong;

            
            m_itema.add(item);
            iNode++;
         }


         _001OnUpdateItemCount();
         iNode++;
      }


      int ItemArray::FindAbsolute(const char * lpszId)
      {
         for(int i = 0; i < get_size(); i++)
         {
            if(element_at(i).m_id == lpszId)
               return i;
         }
         return -1;
      }


      bool Item::IsFolder()
      {
         return m_etype == ItemTypeFolder || 
                m_etype == ItemTypeArtist;  
      }

      void list_view::_001OnEraseBkgnd(gen::signal_object * pobj) 
      {
         SCAST_PTR(::user::win::message::erase_bkgnd, perasebkgnd, pobj)
         perasebkgnd->m_bRet = true;
         perasebkgnd->set_result(TRUE);
      }

      count list_view::_001GetItemCount()
      {
         /*if(get_document() != NULL)
         {
            return get_document()->GetSongCount();
         }
         else
            return 0;*/

         return m_itema.get_size();
      }

   }  // namespace library

}  // namespace mplite