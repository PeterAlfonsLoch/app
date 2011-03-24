#pragma once

namespace databaseuser
{

   class CLASS_DECL_ca list_data :
      public ::user::list_data,
      public ::database::client
   {
   public:
      
      
      count m_iItemCount;


      list_data(::ca::application * papp);
      virtual ~list_data();

      virtual bool _001GetItemText(::user::list * plist, string &str, index iItem, index iSubItem, index iListItem);

      virtual count _001GetItemCount();

      virtual bool Map(::user::list * plist, ::database::id & key1, ::database::id & key2, index iItem, index iSubItem, index iListItem);

   };

} // namespace userbase

