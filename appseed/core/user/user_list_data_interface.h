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
         int_ptr iItem,
         int_ptr iSubItem, 
         int_ptr iListItem) = 0;

      virtual int_ptr _001GetItemCount() = 0;

   };

} // namespace user