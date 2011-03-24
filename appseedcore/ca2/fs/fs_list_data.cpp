#include "StdAfx.h"


namespace fs
{


   list_data::list_data(::ca::application * papp) :
      ::ca::ca(papp),
      ::ca::data(papp),
      ::user::list_data(papp),
      m_itema(papp)
   {
   }

   list_data::~list_data()
   {
   }

   bool list_data::_001GetItemText(
      ::user::list * plist,
	   string &str,
	   INT_PTR iItem,
	   INT_PTR iSubItem, 
	   INT_PTR iListItem)
   {

      UNREFERENCED_PARAMETER(iListItem);
      if(iSubItem == m_iNameSubItemText)
      {
         str = m_itema.get_item(iItem).m_strName;
         return true;
      }
      else if(iSubItem == m_iSizeSubItem)
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
         return true;
      }
      //else if(m_bStatic)
      //{
         // return ::user::list::_001GetItemText(str, iItem, iSubItem, iListItem);
      //}
      else
         return false;

   }

   count list_data::_001GetItemCount()
   {
      return m_itema.get_count();
   }


} // namespace fs


