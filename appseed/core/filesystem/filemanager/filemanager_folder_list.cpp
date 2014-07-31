#include "framework.h"


namespace filemanager
{


   folder_list::folder_list(sp(::base::application) papp) :
      element(papp),
      ::user::scroll_view(papp),
      ::user::list(papp),
      m_headerctrl(papp)
      {

      m_pheaderctrl     = &m_headerctrl;

      m_pheaderctrl->SetBaseListCtrlInterface(this);

   }


   folder_list::~folder_list()
   {

   }


   void folder_list::install_message_handling(::message::dispatch * pinterface)
   {
      ::user::impact::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK, pinterface, this, &folder_list::_001OnLButtonDblClk);
      IGUI_WIN_MSG_LINK(WM_CANCELMODE, pinterface, this, &folder_list::_001OnCancelMode);
   }


   // BEGIN_MESSAGE_MAP(folder_list, ::user::impact)
   //{{__MSG_MAP(folder_list)
   /*
   ON_WM_LBUTTONDBLCLK()
   ON_WM_CANCELMODE()
   */
   //}}__MSG_MAP
   // END_MESSAGE_MAP()

   /////////////////////////////////////////////////////////////////////////////
   // folder_list drawing

   void folder_list::OnDraw(::draw2d::graphics * pgraphics)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      //sp(::user::document) pDoc = get_document();
      // TODO: add draw code here
   }

   /////////////////////////////////////////////////////////////////////////////
   // folder_list diagnostics

#ifdef DEBUG
   void folder_list::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void folder_list::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }
#endif //DEBUG

   void folder_list::on_update(sp(::user::impact) pSender, LPARAM lHint, object * phint) 
   {
      impact::on_update(pSender, lHint, phint);  
      if(phint != NULL)
      {
         if(base_class < update_hint > :: bases(phint))
         {
            update_hint * puh = (update_hint *) phint;
            if(puh->is_type_of(update_hint::TypeInitialize))
            {
               string str;
               str.Format("folder_list(%s)", get_filemanager_data()->m_strDISection);
               m_dataid = str;
               if(get_filemanager_data()->m_bPassBk)
               {
                  ::user::list::m_bBackgroundBypass = true;
               }
               _001UpdateColumns();
            }
         }
      }
   }

   void folder_list::_001OnLButtonDblClk(signal_details * pobj) 
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
         index iItem;
      if(_001HitTest_(pmouse->m_pt, iItem))
      {
         get_filemanager_data()->OnFileManagerOpenFolder(new::fs::item(m_foldera.GetFolder(iItem).m_strPath), ::action::source_user);
      }
   }

   void folder_list::_001OnCancelMode(signal_details * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      // trans   ::user::impact::OnCancelMode();

      // TODO: add your message handler code here

   }

   bool folder_list::pre_create_window(CREATESTRUCT& cs) 
   {

      cs.style |= WS_CLIPCHILDREN;

      return ::user::impact::pre_create_window(cs);
   }

   void folder_list::_001InsertColumns()
   {

      ::user::list_column column;

      column.m_iWidth = 200;
      column.m_iSubItem = 1;
      column.m_bIcon = true;
      column.m_sizeIcon.cx = 16;
      column.m_sizeIcon.cy = 16;
      _001AddColumn(column);

   }

   void folder_list::_001GetItemText(::user::list_item * pitem)
   {
      pitem->m_strText = m_foldera.GetFolder(pitem->m_iItem).m_wstrName;
      pitem->m_bOk = true;
   }



   void folder_list::browse_sync(::action::context actioncontext)
   {
      string strParent = get_filemanager_item().m_strPath;

      m_foldera.clear();

      //      m_foldera.clear(NULL, NULL);

      Folder folder;


      stringa straPath;
      stringa straTitle;

      Application.dir().ls(strParent, &straPath, &straTitle);

      for (int32_t i = 0; i < straPath.get_count(); i++)
      {
         folder.m_strPath = straPath[i];
         folder.m_wstrName = straTitle[i];
         m_foldera.AddFolder(folder);
      }

      _001OnUpdateItemCount();

      ::user::list_column * pcolumn = m_columna._001GetBySubItem(1);


      _001CreateImageList(pcolumn);

   }



   void folder_list::_001CreateImageList(::user::list_column * pcolumn)
   {
      //   HRESULT hr;
      if (pcolumn->m_iSubItem == 1)
      {
         //      char szPath[MAX_PATH * 4];
         //      UINT uiFlags;
         if (pcolumn->m_pil == NULL)
         {
            pcolumn->m_pil = new image_list(get_app());
         }
         sp(image_list) pil = pcolumn->m_pil;
         //if(pil->GetSafeHandle() != NULL)
         //pil->DeleteImageList();
         //if(pil->create(16, 16, ILC_COLOR32 | ILC_MASK, 0, 1))
#ifdef WINDOWSEX
         if (pil->create(16, 16, ILC_COLOR32, 0, 1))
#else
         if (pil->create(16, 16, 0, 0, 1))
#endif
         {

            string str;
            ::visual::icon * hicon = NULL;
            int32_t iIndex;
            for (POSITION pos = m_iconmap.get_start_position(); pos != NULL; m_iconmap.get_next_assoc(pos, hicon, iIndex))
            {
               delete hicon;
            }
            m_iconmap.remove_all();
            //         int32_t iIcon;
            //         int32_t iImage;
            //         IExtractIcon * lpiextracticon;
            for (int32_t i = 0; i < m_foldera.GetFolderCount(); i++)
            {
               /*            Folder & folder = m_foldera.GetFolder(i);
               if(FAILED(m_spshellfolder->GetUIObjectOf(
               GetSafeoswindow_(),
               1,
               (const ITEMIDLIST **) &folder.m_lpiidlRelative,
               IID_IExtractIcon,
               NULL,
               (void **) &lpiextracticon)))
               {
               continue;
               }
               hr = lpiextracticon->GetIconLocation(
               0,
               szPath,
               sizeof(szPath),
               &iIcon,
               &uiFlags);
               if(hr == S_OK)
               {
               HICON hicon = NULL;
               HICON hiconLarge = NULL;
               hr = lpiextracticon->Extract(
               szPath,
               iIcon,
               &hiconLarge,
               &hicon,
               0x00100000);
               if(hr == NOERROR)
               {
               if(!m_iconmap.Lookup(hicon, iImage))
               {
               iImage = pil->add(hicon);
               m_iconmap.set_at(hicon, iImage);
               pil->add(hicon);
               }
               folder.m_iImage = iImage;
               }
               else if(hr == S_FALSE)
               {
               HICON hicon = ExtractIcon(
               System.m_hInstance,
               szPath,
               iIcon);*/
               /*HINSTANCE hinstance = (HINSTANCE) ::LoadLibrary(
               szPath);
               HICON hicon = (HICON) ::LoadImage(
               hinstance,
               MAKEINTRESOURCE(iIcon),
               IMAGE_ICON,
               16, 16,
               LR_CREATEDIBSECTION);
               if(!m_iconmap.Lookup(hicon, iImage))
               {
               iImage = pil->add(hicon);
               m_iconmap.set_at(hicon, iImage);
               pil->add(hicon);
               }
               folder.m_iImage = iImage;
               }
               }
               else if(hr == S_FALSE)
               {
               // a default icon should be used
               }
               lpiextracticon->Release();*/
            }
         }
      }
      else
      {
         ::user::list::_001CreateImageList(pcolumn);
      }
   }


#ifdef WINDOWSEX
   void folder_list::FolderArray::clear(LPITEMIDLIST lpiidlPreserve1, LPITEMIDLIST lpiidlPreserve2)
   {
      UNREFERENCED_PARAMETER(lpiidlPreserve1);
      UNREFERENCED_PARAMETER(lpiidlPreserve2);
      //Folder folder;


      //for(int32_t i = 0; i < this->get_size(); i++)
      //{
      //Folder & folder = this->element_at(i);
      //}
      remove_all();


   }

#endif

   void folder_list::FolderArray::clear()
   {

      remove_all();

   }

   folder_list::Folder &
      folder_list::FolderArray::GetFolder(index i)
   {
         return this->element_at(i);
      }

   ::count folder_list::FolderArray::GetFolderCount()
   {
      return this->get_size();
   }

   void folder_list::FolderArray::AddFolder(Folder &folder)
   {
      add(folder);
   }

   void folder_list::_001GetItemImage(::user::list_item * pitem)
   {
      if (pitem->m_iSubItem == 1)
      {
         pitem->m_iImage = m_foldera.GetFolder(pitem->m_iItem).m_iImage;
         pitem->m_bOk = true;
      }
      else
      {
         ::user::list::_001GetItemImage(pitem);
      }
   }


   ::fs::item & folder_list::get_filemanager_item()
   {

      return get_filemanager_manager()->get_filemanager_item();

   }


   ::count folder_list::_001GetItemCount()
   {
      return m_foldera.GetFolderCount();
   }

   
   COLORREF folder_list::get_background_color()
   {
      if (get_filemanager_data()->is_saving())
      {
         return RGB(255, 177, 84);
      }
      else
      {
         return RGB(200, 255, 255);
      }
   }


} // namespace filemanager








