#pragma once

namespace user
{
   class list;

   class CLASS_DECL_ca list_cache_interface  
   {
   public:
      list_cache_interface();
      virtual ~list_cache_interface();

   public:

      virtual void _001CacheHint(
         list * plist,
         INT_PTR iItemStart,
         INT_PTR iItemCount) = 0;

      virtual bool _001GetItemText(
         list * plist,
         string &str,
         INT_PTR iItem,
         INT_PTR iSubItem, 
         INT_PTR iListItem) = 0;


   };

} // namespace user
