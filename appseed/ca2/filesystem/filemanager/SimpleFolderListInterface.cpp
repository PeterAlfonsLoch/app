#include "framework.h"
#include "SimpleFolderListInterface.h"


namespace filemanager
{


   SimpleFolderListInterface::SimpleFolderListInterface(sp(::ca2::application) papp) :
      ca2(papp),
      
      ::user::scroll_view(papp),
      ::user::list(papp)
   {

   }


   SimpleFolderListInterface::~SimpleFolderListInterface()
   {
   
   }


   void SimpleFolderListInterface::_001InsertColumns()
   {

      ::user::list_column column;

      column.m_iWidth = 200;
      column.m_iSubItem = 1;
      column.m_bIcon = true;
      column.m_sizeIcon.cx = 16;
      column.m_sizeIcon.cy = 16;
      _001AddColumn(column);

   }

   void SimpleFolderListInterface::_001GetItemText(::user::list_item * pitem)
   {
      pitem->m_strText = m_foldera.GetFolder(pitem->m_iItem).m_wstrName;
      pitem->m_bOk = true;
   }


   void SimpleFolderListInterface::_017Browse(const wchar_t * lpcsz)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      _017UpdateList();
   }

   void SimpleFolderListInterface::_017Browse(const char * lpcsz)
   {

      _017UpdateList(lpcsz);

      _017UpdateList();

   }

   void SimpleFolderListInterface::_017UpdateList(const char * lpcsz)
   {
      string strParent = lpcsz;

      m_foldera.clear();

//      m_foldera.clear(NULL, NULL);

      Folder folder;


      stringa straPath;
      stringa straTitle;

      Application.dir().ls(strParent, &straPath, &straTitle);

      for(int32_t i = 0; i < straPath.get_count(); i++)
      {
         folder.m_strPath     = straPath[i];
         folder.m_wstrName    = straTitle[i];
           m_foldera.AddFolder(folder);
      }

      _001OnUpdateItemCount();

      ::user::list_column * pcolumn = m_columna._001GetBySubItem(1);


      _001CreateImageList(pcolumn);

   }

   void SimpleFolderListInterface::_017UpdateList()
   {

      Folder folder;

   //   HRESULT hr;
      string strParent = GetFileManagerItem().m_strPath;

      if(strParent.is_empty())
      {

         m_foldera.clear();

         stringa stra;

         Application.dir().root_ones(stra);

         Folder folder;

         for(int32_t i = 0; i < stra.get_size(); i++)
         {
            folder.m_strPath = stra[i];
            folder.m_wstrName = stra[i];
            m_foldera.AddFolder(folder);
         }

      }
      else
      {
         _017UpdateList(strParent);
      }
   }


   void SimpleFolderListInterface::_001CreateImageList(::user::list_column * pcolumn)
   {
   //   HRESULT hr;
      if(pcolumn->m_iSubItem == 1)
      {
   //      char szPath[MAX_PATH * 4];
   //      UINT uiFlags;
         if(pcolumn->m_pil == NULL)
         {
            pcolumn->m_pil = new image_list(get_app());
         }
         sp(image_list) pil = pcolumn->m_pil;
         //if(pil->GetSafeHandle() != NULL)
            //pil->DeleteImageList();
         //if(pil->create(16, 16, ILC_COLOR32 | ILC_MASK, 0, 1))
#ifdef WINDOWSEX
         if(pil->create(16, 16, ILC_COLOR32, 0, 1))
#else
         if(pil->create(16, 16, 0, 0, 1))
#endif
         {

#ifdef WINDOWSEX
            string str;
            HICON hicon = NULL;
            int32_t iIndex;
            for(POSITION pos = m_iconmap.get_start_position();
               pos != NULL;
               m_iconmap.get_next_assoc(pos, hicon, iIndex))
            {
               DestroyIcon(hicon);
            }
#else
            throw todo(get_app());
#endif
            m_iconmap.remove_all();
   //         int32_t iIcon;
   //         int32_t iImage;
   //         IExtractIcon * lpiextracticon;
            for(int32_t i = 0; i < m_foldera.GetFolderCount(); i++)
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
   void SimpleFolderListInterface::FolderArray::clear(LPITEMIDLIST lpiidlPreserve1, LPITEMIDLIST lpiidlPreserve2)
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

   void SimpleFolderListInterface::FolderArray::clear()
   {

      remove_all();

   }

   SimpleFolderListInterface::Folder &
   SimpleFolderListInterface::FolderArray::GetFolder(index i)
   {
      return this->element_at(i);
   }

   ::count SimpleFolderListInterface::FolderArray::GetFolderCount()
   {
      return this->get_size();
   }

   void SimpleFolderListInterface::FolderArray::AddFolder(Folder &folder)
   {
      add(folder);
   }

   void SimpleFolderListInterface::_001GetItemImage(::user::list_item * pitem)
   {
      if(pitem->m_iSubItem == 1)
      {
         pitem->m_iImage = m_foldera.GetFolder(pitem->m_iItem).m_iImage;
         pitem->m_bOk = true;
      }
      else
      {
         ::user::list::_001GetItemImage(pitem);
      }
   }

   void SimpleFolderListInterface::_017Synchronize()
   {
      _017Browse(GetFileManagerItem().m_strPath);
   }

   ::fs::item & SimpleFolderListInterface::GetFileManagerItem()
   {
      return GetFileManager()->get_item();
   }

   ::count SimpleFolderListInterface::_001GetItemCount()
   {
      return m_foldera.GetFolderCount();
   }

   void SimpleFolderListInterface::install_message_handling(::ca2::message::dispatch * pinterface)
   {
      ::user::list::install_message_handling(pinterface);
   }

   COLORREF SimpleFolderListInterface::get_background_color()
   {
      if(GetFileManager()->get_filemanager_data()->is_saving())
      {
         return RGB(255, 177, 84);
      }
      else
      {
         return RGB(200, 255, 255);
      }
   }


} // namespace filemanager


