#include "framework.h"


namespace userfs
{


   list_data::list_data(sp(::base::application) papp) :
      element(papp),
      ::user::list_data(papp),
      m_itema(papp)
   {
   }

   list_data::~list_data()
   {
   }

   void list_data::_001GetItemText(::user::list_item * pitem)
   {
      if(pitem->m_iSubItem == m_iNameSubItemText)
      {
         pitem->m_strText = m_itema.get_item(pitem->m_iItem).m_strName;
         pitem->m_bOk = true;
         return;
      }
      else if(pitem->m_iSubItem == m_iSizeSubItem)
      {
   /*      bool bPendingSize = false;

         bool bGet;
         bGet = System.get_fs_size(str, m_itema.get_item(iItem).m_strPath, bPendingSize);
         if(bGet)
         {
            m_straFileSize.set_at_grow(iItem, str);
         }
         else
         {
            if(iItem < m_straFileSize.get_size())
            {
               str = m_straFileSize[iItem];
            }
         }
         if(bPendingSize)
         {
            schedule_file_size(m_itema.get_item(iItem).m_strPath);
            m_bPendingSize = true;
         }*/
         pitem->m_bOk = false;
         return;
      }
      //else if(m_bStatic)
      //{
         // return ::user::list::_001GetItemText(str, iItem, iSubItem, iListItem);
      //}
      else
         return_(pitem->m_bOk, false);

   }

   ::count list_data::_001GetItemCount()
   {
      return m_itema.get_count();
   }



   void list_data::_001GetItemImage(::user::list_item * pitem)
   {

      if(pitem->m_iSubItem == m_iNameSubItemText)
      {
         pitem->m_iImage = m_itema.get_item(pitem->m_iItem).m_iImage;
         pitem->m_bOk = true;
         return;
      }
      else
      {
         return_(pitem->m_bOk, false);
      }

   }


} // namespace userfs


