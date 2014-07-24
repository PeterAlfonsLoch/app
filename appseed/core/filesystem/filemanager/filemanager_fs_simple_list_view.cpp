#include "framework.h"


namespace filemanager
{

   namespace fs
   {

      namespace simple
      {

         list_view::list_view(sp(::base::application) papp) :
         element(papp),
            ::user::scroll_view(papp),
            ::user::list(papp),
            ::user::form(papp),
            ::user::form_list(papp),
            
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

         void list_view::install_message_handling(::message::dispatch * pinterface)
         {
            simple_list_view::install_message_handling(pinterface);
            IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK, pinterface, this, &list_view::_001OnLButtonDblClk);
            IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &list_view::_001OnTimer);
            IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &list_view::_001OnSize);
            IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &list_view::_001OnContextMenu);
            IGUI_WIN_MSG_LINK(WM_ERASEBKGND, pinterface, this, &list_view::_001OnEraseBkgnd);
            IGUI_WIN_MSG_LINK(WM_USER + 1217    , pinterface, this, &list_view::_001OnFillTaskResponse);

         }



      #ifdef DEBUG
         void list_view::assert_valid() const
         {
            simple_list_view::assert_valid();
         }

         void list_view::dump(dump_context & dumpcontext) const
         {
            simple_list_view::dump(dumpcontext);
         }
      #endif //DEBUG


         void list_view::_001InsertColumns()
         {

            ::user::list_column column;
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


         void list_view::_001GetItemImage(::user::list_item * pitem)
         {
            if(pitem->m_iItem < 0 || pitem->m_iItem >= m_itema.get_size())
            {
               pitem->m_bOk = false;
               return;
            }
            if(pitem->m_iSubItem == SubItemTitle)
            {
               pitem->m_bOk = true;
               switch(m_itema[pitem->m_iItem].m_etype)
               {
               case ItemTypeFolder:
                  pitem->m_iImage = m_iIconFolder;
                  break;
               case ItemTypeArtist:
                  pitem->m_iImage = m_iIconArtist;
                  break;
               case ItemTypeSong:
                  pitem->m_iImage = m_iIconSong;
                  break;
               default:
                  pitem->m_bOk = false;
                  break;
               }
               return;
            }
            else
            {
               pitem->m_bOk = false;
               return;
            }

         }

         void list_view::_001GetItemText(::user::list_item * pitem)
         {
            if(pitem->m_iItem < 0 || pitem->m_iItem >= m_itema.get_size())
            {
               pitem->m_bOk = false;
               return;
            }
            switch(pitem->m_iSubItem)
            {
            case SubItemId:
               pitem->m_strText.Empty();
               break;
            case SubItemTitle:
               pitem->m_strText = m_itema[pitem->m_iItem].m_strTitle;
               break;
            case SubItemArtist:
               pitem->m_strText.Empty();
               break;
            case SubItemFileName:
               pitem->m_strText.Empty();
               break;;
            case SubItemFilePath:
               pitem->m_strText.Empty();
               break;
            default:
               //ASSERT(FALSE);
               pitem->m_strText.Empty();
               break;
            }
            pitem->m_bOk = true;
         }

         void list_view::_001SearchGetItemText(::user::list_item * pitem)
         {
            return_(pitem->m_bOk, false);
         }


         void list_view::on_update(sp(::user::impact) pSender, LPARAM lHint, object* phint)
         {
            UNREFERENCED_PARAMETER(pSender);
            UNREFERENCED_PARAMETER(lHint);
            if(phint == NULL)
            {
               _001UpdateColumns();
            }
            else
            {
            }


         }

         void list_view::_001OnLButtonDblClk(signal_details * pobj)
         {
            SCAST_PTR(::message::mouse, pmouse, pobj)
               index iItem;

            if(_001HitTest_(pmouse->m_pt, iItem))
            {
               if(m_itema[iItem].IsFolder())
               {
                  m_pserver->open_folder(m_itema[iItem].m_iFolder);
               }
               else
               {
                  m_pserver->open_file(m_iParentFolder, m_itema[iItem].m_strFileName, m_itema[iItem].m_strExtension);
               }
            }
         }

         void list_view::_001OnClick(uint_ptr nFlags, point point)
         {
            UNREFERENCED_PARAMETER(nFlags);
            index iItem;
            index iSubItem;
            if(_001HitTest_(point, iItem, iSubItem))
            {
               if(m_itema[iItem].IsFolder())
               {
                  m_pserver->open_folder(m_itema[iItem].m_iFolder);
               }
               else
               {
                  m_pserver->open_file(m_iParentFolder, m_itema[iItem].m_strFileName, m_itema[iItem].m_strExtension);
               }
            }
         }

         bool list_view::GetSongPath(string &str, index iItem)
         {
            ::user::list_item item(this);
            item.m_iItem = iItem;
            item.m_iSubItem = SubItemFilePath;
            item.m_iListItem = -1;
            _001GetItemText(&item);
            if(!item.m_bOk)
               return false;
            str = item.m_strText;
            return true;
         }

         void list_view::_001OnSort()
         {
            string strSql;

            strSql = "select id, title, artist, filename, filepath from album";

            if(m_sortinfo.m_itema.get_size() > 0)
            {
               strSql += " order by ";

               for(int32_t i = 0; i < m_sortinfo.m_itema.get_size(); i++)
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


/*            single_lock sl(get_document()->m_pcsAlbum1, TRUE);
            get_document()->m_pdsAlbum1->query(strSql);*/

            m_cache._001Invalidate();

            RedrawWindow();

         }

         void list_view::PostFillTask(string & wstrFile, uint_ptr uiTimer)
         {
            UNREFERENCED_PARAMETER(wstrFile);
            UNREFERENCED_PARAMETER(uiTimer);
            ASSERT(FALSE);
            //   FillTask * ptask = new FillTask(this, wstrFile);
            // ptask->m_uiTimer = uiTimer;
            //__begin_thread(
            // ThreadProcFillTask,
            //(LPVOID)  ptask);
         }

         UINT c_cdecl list_view::ThreadProcFillTask(LPVOID lpParameter)
         {
            UNREFERENCED_PARAMETER(lpParameter);
            ASSERT(FALSE);

            /*FillTask * ptask = (FillTask *) lpParameter;

            ptask->m_pview->KillTimer(1123);

            string & wstrPath = ptask->m_wstrFile;
            MediaLibraryDoc * pdoc = ptask->m_pview->get_document();
            sp(::sqlite::set) pds = pdoc->m_pdsAlbum;

            int32_t iFind;
            if((iFind = pdoc->m_fileinfo.m_wstraAdd.FindFirst(wstrPath)) >= 0)
            {
            mediamanager::GetMediaManager()->album_build().add(wstrPath, pdoc->m_fileinfo.m_timeaAdd[iFind]);
            pdoc->m_fileinfo.m_wstraAdd.remove_at(iFind);
            pdoc->m_fileinfo.m_timeaAdd.remove_at(iFind);
            }
            else if((iFind = pdoc->m_fileinfo.m_wstraUpdate.FindFirst(wstrPath)) >= 0)
            {
            mediamanager::GetMediaManager()->album_build().Update(wstrPath, pdoc->m_fileinfo.m_timeaUpdate[iFind]);
            pds->SetFieldValue("title", sqlite::CFieldValue(mediamanager::GetMediaManager()->album_build().album_record().m_wstrTitle));
            pds->SetFieldValue("filename", sqlite::CFieldValue(mediamanager::GetMediaManager()->album_build().album_record().m_wstrFileName));
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

         void list_view::_001OnTimer(signal_details * pobj)
         {
            SCAST_PTR(::message::timer, ptimer, pobj)
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
               int32_t iTopIndex = _001GetTopIndex();
               if(m_buildhelper.m_iTopIndex != iTopIndex)
               {
               m_buildhelper.m_iTopIndex = iTopIndex;
               m_buildhelper.m_iStep = 0;
               }
               int32_t iItem;


               sp(::sqlite::set) pds = pdoc->m_pdsAlbum;

               int32_t iRemove = max(30, m_buildhelper.m_iDisplayItemCount);

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

               int32_t iFind;
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
               mediamanager::GetMediaManager()->album_build().remove(iaRemove);
               }

               }
               else if(nIDEvent == 1124)
               {
               KillTimer(1124);
               MediaLibraryDoc * pdoc = get_document();
               sp(::sqlite::set) pds = pdoc->m_pdsAlbum;

               int32_t iRemove = max(30, m_buildhelper.m_iDisplayItemCount);

               int_array iaRemove;
               int32_t iFind = 0;
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

         void list_view::_001OnSize(signal_details * pobj)
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

         /*list_view::FillTask::FillTask(sp(list_view) pview, LPWString lpcsz)
         :
         m_pview(pview),m_wstrFile(lpcsz)
         {
         }*/

         void list_view::_001OnFillTaskResponse(signal_details * pobj)
         {
            SCAST_PTR(::message::base, pbase, pobj)
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

         void list_view::start_build(int32_t iItem)
         {
            UNREFERENCED_PARAMETER(iItem);
            index iTopIndex = m_iTopIndex;
            ::count iDisplayItemCount = m_nDisplayCount;

            if(m_bKickActive &&
               m_buildhelper.m_iTopIndex == iTopIndex &&
               m_buildhelper.m_iDisplayItemCount == iDisplayItemCount)
               return;

            m_buildhelper.m_iTopIndex = iTopIndex;
            m_buildhelper.m_iDisplayItemCount = iDisplayItemCount;

            m_bKickActive = true;


            SetTimer(123654, 700, NULL);

         }

         void list_view::_001OnContextMenu(signal_details * pobj)
         {

            SCAST_PTR(::message::context_menu, pcontextmenu, pobj)
               //int32_t iItem;
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
            sp(::user::frame_window) pframe = GetParentFrame()->GetParentFrame();
            pPopup->TrackPopupMenu(point.x, point.y,
            (::window_sp) pframe);
            }
            }
            else
            {
            ::user::menu menu;
            if (menu.LoadMenu(IDR_POPUP_ALBUM))
            {
            ::user::menu* pPopup = menu.GetSubMenu(0);
            ASSERT(pPopup != NULL);
            sp(::user::frame_window) pframe = GetParentFrame()->GetParentFrame();
            pPopup->TrackPopupMenu(
            point.x, point.y,
            (::window_sp) pframe);
            }
            }*/
         }

         void list_view::parse(const char * lpszSource)
         {
            m_itema.remove_all();
            _001OnUpdateItemCount(0);

            string str;
            xml::manager doc(get_app());
            if(doc.load(lpszSource))
            {
               str  = doc.get_xml();
            }
            else
            {
               System.simple_message_box(NULL, "error"); // simple parsing error check
               return;
            }


            m_iParentFolder = doc.attr("id");

            sp(::xml::node) pnodeFolder = doc.get_root()->get_child("folder");


            xml::node::array childs(get_app());

            string wstrType;
            Item item;
            // method 3: Selected Childs with GetChilds()
            // Result: Person, Person, Person
            index iNode = 0;
            for(int32_t i = 0 ; i < pnodeFolder->get_children_count(); i++)
            {
               sp(::xml::node) pnodeItem = pnodeFolder->child_at(i);
               if(pnodeItem->get_name() == "folder")
               {
                  item.m_iParent = m_iParentFolder;
                  item.m_iFolder = pnodeItem->attr("id");
                  item.m_strTitle = pnodeItem->attr("name");

      /*            if(wstrType == "normal")
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

                  */
                  m_itema.add(new Item(item));
                  iNode++;
               }
            }

            sp(::xml::node) pnodeFile = doc.get_root()->get_child("file");

            for(int32_t i = 0; i < pnodeFile->get_children_count(); i++)
            {
               sp(::xml::node) pnodeItem = pnodeFile->child_at(i);
               if(pnodeItem->get_name() == "file")
               {
                  wstrType = pnodeItem->attr("type");
                  item.m_iParent = m_iParentFolder;
                  item.m_iFolder = -1;
   //               item.m_iId = atoi(pnode->get_child_value("songfileid"));
                  item.m_strTitle = pnodeItem->attr("name");
                  item.m_strFileName = pnodeItem->attr("name");
                  item.m_strExtension = pnodeItem->attr("extension");

                  item.m_etype = ItemTypeSong;
                  item.m_iImage = m_iIconSong;


                  m_itema.add(new Item(item));
                  iNode++;
               }
            }


            _001OnUpdateItemCount();
            iNode++;
         }


         /*int32_t ItemArray::FindAbsolute(const char * lpszId)
         {
            for(int32_t i = 0; i < this->get_size(); i++)
            {
               if(this->element_at(i).m_id == lpszId)
                  return i;
            }
            return -1;
         }*/


         bool Item::IsFolder()
         {
            return m_iFolder >= 0;
            return m_etype == ItemTypeFolder ||
               m_etype == ItemTypeArtist;
         }

         void list_view::_001OnEraseBkgnd(signal_details * pobj)
         {
            SCAST_PTR(::message::erase_bkgnd, perasebkgnd, pobj)
               perasebkgnd->m_bRet = true;
            perasebkgnd->set_result(TRUE);
         }

         ::count list_view::_001GetItemCount()
         {
            /*if(get_document() != NULL)
            {
            return get_document()->GetSongCount();
            }
            else
            return 0;*/

            return m_itema.get_size();
         }

      } // namespace simple

   }  // namespace fs

}  // namespace filemanager
