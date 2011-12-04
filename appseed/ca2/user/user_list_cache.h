#pragma once


namespace user
{


   class CLASS_DECL_ca2 list_cache  :
      public list_cache_interface
   {
   protected:

      
      bool                                                              m_bCaching;
      int                                                               m_iCacheNextIndex;
      string2a                                                          m_cacheArray;
      ::collection::map < INT_PTR, INT_PTR, stringa *, stringa *>       m_cacheMap;


   public:


      list_cache();
      virtual ~list_cache();


      void _001Invalidate();
      
      virtual void _001CacheHint(list * plist, INT_PTR iItemStart, INT_PTR iItemCount);

      virtual void _001GetItemText(::user::list_item * pitem);


   };


} // namespace user

