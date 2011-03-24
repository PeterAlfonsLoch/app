#pragma once

namespace user
{

   class CLASS_DECL_ca list_cache  :
      public list_cache_interface
   {
   public:
      list_cache();
      virtual ~list_cache();
   protected:
      bool     m_bCaching;
      int      m_iCacheNextIndex;
      string2a m_cacheArray;
        ::collection::map < INT_PTR, INT_PTR, stringa *, stringa *> m_cacheMap;

      //Carray < Carray < bool, bool & >, Carray < bool, bool & > & > m_b2aCache;
   public:
      void _001Invalidate();
      virtual void _001CacheHint(
         list * plist,
         INT_PTR iItemStart,
         INT_PTR iItemCount);

      virtual bool _001GetItemText(
         list * plist,
         string &str,
         INT_PTR iItem,
         INT_PTR iSubItem, 
         INT_PTR iListItem);

   };

} // namespace user