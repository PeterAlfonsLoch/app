#pragma once


namespace user
{


   class list;


   class CLASS_DECL_ca list_cache_interface  
   {
   public:


      list_cache_interface();
      virtual ~list_cache_interface();


      virtual void _001CacheHint(list * plist, index iItemStart, count nItemCount) = 0;
      virtual void _001GetItemText(::user::list_item * pitem) = 0;
      virtual void _001GetGroupText(::user::list_item * pitem);


   };


} // namespace user

