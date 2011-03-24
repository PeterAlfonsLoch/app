#include "StdAfx.h"
#include "SimpleFolderListInterface.h"

namespace filemanager
{


   SimpleFolderListInterface::SimpleFolderListInterface(::ca::application * papp) :
      ca(papp),
      ::user::scroll_view(papp),
      ::user::list(papp)
   {
   }

   SimpleFolderListInterface::~SimpleFolderListInterface()
   {
   }


   void SimpleFolderListInterface::_001InsertColumns()
   {

      Column column;

      column.m_iWidth = 200;
      column.m_iSubItem = 1;
      column.m_bIcon = true;
      column.m_sizeIcon.cx = 16;
      column.m_sizeIcon.cy = 16;
      _001AddColumn(column);

   }

   bool SimpleFolderListInterface::_001GetItemText(string & str, index iItem, index iSubItem, index iListItem)
   {
      UNREFERENCED_PARAMETER(iSubItem);
      UNREFERENCED_PARAMETER(iListItem);
      str = m_foldera.GetFolder(iItem).m_wstrName;
      return true;
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


      m_foldera.clear(NULL, NULL);

      Folder folder;


      stringa straPath;
      stringa straTitle;

      System.dir().ls(strParent, &straPath, &straTitle);

      for(int i = 0; i < straPath.get_count(); i++)
      {
         folder.m_strPath     = straPath[i];
         folder.m_wstrName    = straTitle[i];
           m_foldera.AddFolder(folder);
      }

      _001OnUpdateItemCount();

      Column & column = m_columna.GetBySubItem(1);


      _001CreateImageList(column);

   }

   void SimpleFolderListInterface::_017UpdateList()
   {
   
      Folder folder;

   //   HRESULT hr;
      string strParent = GetFileManagerItem().m_strPath;

      if(strParent.is_empty())
      {

         m_foldera.clear(NULL, NULL);

         stringa stra;

         System.dir().root_ones(stra);

         Folder folder;

         for(int i = 0; i < stra.get_size(); i++)
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


   void SimpleFolderListInterface::_001CreateImageList(Column &column)
   {
   //   HRESULT hr;
      if(column.m_iSubItem == 1)
      {
   //      char szPath[MAX_PATH * 4];
   //      UINT uiFlags;
         if(column.m_pil == NULL)
         {
            column.m_pil = new image_list(get_app());
         }
         image_list * pil = column.m_pil;
         //if(pil->GetSafeHandle() != NULL)
            //pil->DeleteImageList();
         //if(pil->create(16, 16, ILC_COLOR32 | ILC_MASK, 0, 1))
         if(pil->create(16, 16, ILC_COLOR32, 0, 1))
         {
         
            string str;
            HICON hicon = NULL;
            int iIndex;
            for(POSITION pos = m_iconmap.get_start_position();
               pos != NULL;
               m_iconmap.get_next_assoc(pos, hicon, iIndex))
            {
               DestroyIcon(hicon);
            }
            m_iconmap.remove_all();
   //         int iIcon;
   //         int iImage;
   //         IExtractIcon * lpiextracticon;
            for(int i = 0; i < m_foldera.GetFolderCount(); i++)
            {
   /*            Folder & folder = m_foldera.GetFolder(i);
               if(FAILED(m_spshellfolder->GetUIObjectOf(
                  GetSafeHwnd(),
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
   /*               HICON hicon = ExtractIcon(
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
         ::user::list::_001CreateImageList(column);
      }
   }


   void SimpleFolderListInterface::FolderArray::clear(
      LPITEMIDLIST lpiidlPreserve1,
      LPITEMIDLIST lpiidlPreserve2)
   {
      UNREFERENCED_PARAMETER(lpiidlPreserve1);
      UNREFERENCED_PARAMETER(lpiidlPreserve2);
      //Folder folder;


      //for(int i = 0; i < get_size(); i++)
      //{
         //Folder & folder = element_at(i);
      //}
      remove_all();


   }

   SimpleFolderListInterface::Folder &
   SimpleFolderListInterface::FolderArray::GetFolder(int i)
   {
      return element_at(i);
   }

   int SimpleFolderListInterface::FolderArray::GetFolderCount()
   {
      return get_size();
   }

   void SimpleFolderListInterface::FolderArray::AddFolder(Folder &folder)
   {
      add(folder);
   }

   index SimpleFolderListInterface::_001GetItemImage(index iItem, index iSubItem, index iListItem)
   {
      if(iSubItem == 1)
      {
         return m_foldera.GetFolder(iItem).m_iImage;
      }
      else
         return ::user::list::_001GetItemImage(iItem, iSubItem, iListItem);
   }




   void SimpleFolderListInterface::_017Synchronize()
   {
      _017Browse(GetFileManagerItem().m_strPath);
   }

   ::fs::item & SimpleFolderListInterface::GetFileManagerItem()
   {
      return GetFileManager()->get_item();
   }

   count SimpleFolderListInterface::_001GetItemCount()
   {
      return m_foldera.GetFolderCount();
   }

   void SimpleFolderListInterface::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::user::list::_001InstallMessageHandling(pinterface);
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


