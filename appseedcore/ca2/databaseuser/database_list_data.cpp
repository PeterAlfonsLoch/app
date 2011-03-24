#include "StdAfx.h"

namespace databaseuser
{

   list_data::list_data(::ca::application * papp) :
      ca(papp),
      ::ca::data(papp),
      ::user::list_data(papp)
   {
      m_iItemCount = 0;
   }

   list_data::~list_data()
   {

   }

   bool list_data::_001GetItemText(
      ::user::list * plist,
      string &str,
      index iItem,
      index iSubItem, 
      index iListItem)
   {

      ::database::id key1;
      ::database::id key2;

      if(Map(plist, key1, key2, iItem, iSubItem, iListItem))
      {
         if(data_get(key1, key2, str))
            return true;
      }

      return false;

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

   count list_data::_001GetItemCount()
   {
      return m_iItemCount;
   }

} // namespace guibase

