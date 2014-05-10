#include "framework.h"



namespace databaseuser
{


   list_data::list_data(sp(::base::application) papp) :
      element(papp),
      ::user::list_data(papp)
   {
      m_iItemCount = 0;
   }

   list_data::~list_data()
   {

   }

   void list_data::_001GetItemText(::user::list_item * pitem)
   {

      ::database::id key1;
      ::database::id key2;

      if(Map(pitem->m_plist, key1, key2, pitem->m_iItem, pitem->m_iSubItem, pitem->m_iListItem))
      {
         if(data_get(key1, key2, pitem->m_strText))
         {
            return_(pitem->m_bOk, true);
         }
      }

      return_(pitem->m_bOk, false);

   }

   bool list_data::Map(
      ::user::list * plist,
      ::database::id & key1,
      ::database::id & key2,
      index iItem,
      index iSubItem, 
      index iListItem)
   {

      UNREFERENCED_PARAMETER(plist);
      // default implementation
      string str;
      str.Format("%d", iSubItem);
      key1 = str;
      str.Format("%d.%d", iItem, iListItem);
      key2 = str;
      return true;

   }

   ::count list_data::_001GetItemCount()
   {

      return m_iItemCount;

   }


} // namespace guibase



