#pragma once

namespace user
{

   class list;

   class CLASS_DECL_ca list_data :
      virtual public ::ca::data
   {
   public:
      list_data(::ca::application * papp);
      virtual ~list_data();

      virtual bool _001GetItemText(
         list * plist,
         string &str,
         index iItem,
         index iSubItem, 
         index iListItem) = 0;

      virtual count _001GetItemCount() = 0;

   };

} // namespace user