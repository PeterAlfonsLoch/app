#include "StdAfx.h"

namespace user
{

   list_cache::list_cache()
   {
      m_bCaching = false;
      m_iCacheNextIndex = 0;
   }

   list_cache::~list_cache()
   {

   }

   void list_cache::_001CacheHint(
      ::user::list * plist,
      index iItemStart,
      index iItemCount)
   {
      keeper < bool > keepCaching(&m_bCaching, true, false, true);

      //static critical_section l_cs;
      //CSingleLock sl(&l_cs, TRUE);
      INT_PTR iIndex, i;
      stringa * pwstra;
      string str;

      int iItemEnd = iItemStart + iItemCount - 1;
      if(iItemCount > m_cacheArray.get_size())
      {
         
         while(iItemCount + 200> m_cacheArray.get_size())
         {
            //pwstra = new stringa();
            m_cacheArray.add(stringa());
         }
      }
      
   //   critical_section * pCs = &pSet->m_cs;
      i = 0;
      int iCacheIndex = m_iCacheNextIndex;
      for(iIndex = iItemStart; iIndex <= iItemEnd; iIndex++)
      {
         if(m_cacheMap.Lookup(iIndex, pwstra))
            continue;
         
         if(iCacheIndex >= m_cacheArray.get_size())
         {
            iCacheIndex = 0;
            if(iCacheIndex >= m_cacheArray.get_size())
               break;
         }
         pwstra = &m_cacheArray.element_at(iCacheIndex);
         m_cacheMap.remove_key(iIndex);
         iCacheIndex++;
         if(pwstra->get_size() < plist->m_columna.get_count())
         {
            pwstra->set_size(plist->m_columna.get_count());
         }
         for(i = 0; i < plist->m_columna.get_count(); i++)
         {
            plist->_001GetItemText(
               str,
               iIndex,
               plist->m_columna.GetByKey(i).m_iSubItem,
               -1);
            pwstra->set_at(i, str);
         }
   //      pCs->Unlock();
   //      pSong->m_iIndex = iIndex;      
         m_cacheMap.set_at(iIndex, pwstra);
         i++;
      }
      m_iCacheNextIndex = iCacheIndex;
   }

   bool list_cache::_001GetItemText(
      ::user::list * plist,
      string &str,
      INT_PTR iItem,
      INT_PTR iSubItem, 
      INT_PTR iListItem)
   {
      UNREFERENCED_PARAMETER(iListItem);
      if(m_bCaching)
         return false;
      if(iItem < 0)
         return false;
   //   if(m_wstr2a.get_size() <= 0)
     //    return false;
      INT_PTR iColumnKey = plist->m_columna.MapSubItemToKey(iSubItem);
      if(iColumnKey < 0)
         return false;
   //   if(iColumnKey > m_wstr2a.get_size())
     ///    return false;
      stringa * pwstra;
      if(!m_cacheMap.Lookup(iItem, pwstra))
      {
   //      TRACE("CAlbumSongList::OnGetdispinfo iKey=%d iItemIdx=%d\n", iKey, iItemIndx);
   //      TRACE("CAlbumSongList::OnGetdispinfo iItemIdx=%d\n", iItemIndx);
         _001CacheHint(plist, iItem, 1);
         if(!m_cacheMap.Lookup(iItem, pwstra))
            return false;
   //      TRACE("XXXXXXXXXXXXXXXXX CANNOT CACHE!!!! CAlbumSongList::OnGetdispinfo iKey=%d iItemIdx=%d\n", iKey, iItemIndx);
   //            TRACE("XXXXXXXXXXXXXXXXX CANNOT CACHE!!!! CAlbumSongList::OnGetdispinfo iItemIdx=%d\n", iItemIndx);
      }
      if(iColumnKey >= pwstra->get_size())
         return false;

      str = pwstra->element_at(iColumnKey);
      return true;
   }

   void list_cache::_001Invalidate()
   {
      m_cacheMap.remove_all();
   }

} // namespace user
