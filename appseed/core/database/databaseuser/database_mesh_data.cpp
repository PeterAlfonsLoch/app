#include "framework.h"
#include "core/user/user/user.h"


namespace databaseuser
{


   mesh_data::mesh_data(::aura::application * papp) :
      object(papp),
      ::user::mesh_data(papp)
   {
      m_iItemCount = 0;
   }

   mesh_data::~mesh_data()
   {

   }

   void mesh_data::_001GetItemText(::user::list_item * pitem)
   {

      ::database::id key1;
      ::database::id key2;

      if(Map(pitem->m_plist, key1, key2, pitem->m_iItem, pitem->m_iSubItem, pitem->m_iListItem))
      {
         if(data_get(key1.m_id + "." + key2.m_id, pitem->m_strText))
         {
            return_(pitem->m_bOk, true);
         }
      }

      return_(pitem->m_bOk, false);

   }

   bool mesh_data::Map(
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

   ::count mesh_data::_001GetItemCount()
   {

      return m_iItemCount;

   }


} // namespace guibase



