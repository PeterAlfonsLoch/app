#pragma once

namespace user
{

   class list;

   class CLASS_DECL_ca2 list_data  
   {
   public:
      ::user::list_data();
      virtual ~::user::list_data();

      virtual bool _001GetItemText(
         ::user::list * plist,
         string &str,
         INT_PTR iItem,
         INT_PTR iSubItem, 
         INT_PTR iListItem) = 0;

      virtual INT_PTR _001GetItemCount() = 0;

   };

} // namespace user