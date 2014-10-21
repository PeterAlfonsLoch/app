#include "framework.h"

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
      keep < bool > keepCaching(&m_bCaching, true, false, true);

      //static critical_section l_cs;
      //single_lock sl(&l_cs, TRUE);
      int_ptr iIndex, i;
      stringa * pwstra;
      string str;

      index iItemEnd = iItemStart + iItemCount - 1;
      if(iItemCount > m_cacheArray.get_size())
      {

         m_cacheArray.set_size(iItemCount + 200);

      }

   //   critical_section * pCs = &pSet->m_cs;
      draw_list_item item(plist);
      i = 0;
      int32_t iCacheIndex = m_iCacheNextIndex;
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
         pwstra = &m_cacheArray[iCacheIndex];
         m_cacheMap.remove_key(iIndex);
         iCacheIndex++;
         if(pwstra->get_size() < plist->m_columna.get_count())
         {
            pwstra->set_size(plist->m_columna.get_count());
         }
         for(i = 0; i < plist->m_columna.get_count(); i++)
         {
            item.m_iItem = iIndex;
            item.m_iSubItem = plist->m_columna._001GetByKey(i)->m_iSubItem;
            item.m_iListItem = -1;
            try
            {
               plist->_001GetItemText(&item);
            }
            catch(...)
            {
            }
            pwstra->set_at(i, item.m_strText);
         }
   //      pCs->unlock();
   //      pSong->m_iIndex = iIndex;
         m_cacheMap.set_at(iIndex, pwstra);
         i++;
      }
      m_iCacheNextIndex = iCacheIndex;
   }

   void list_cache::_001GetItemText(::user::list_item * pitem)
   {

      if(m_bCaching)
         return_(pitem->m_bOk, false);

      if(pitem->m_iItem < 0)
         return_(pitem->m_bOk, false);

      if(pitem->m_iColumnKey < 0)
      {
         if(pitem->m_pcolumn == NULL)
         {
            pitem->m_pcolumn = pitem->m_plist->m_columna._001GetBySubItem(pitem->m_iSubItem);
         }
         pitem->m_iColumnKey = pitem->m_pcolumn->m_iKey;
         if(pitem->m_iColumnKey < 0)
            return_(pitem->m_bOk, false);
      }

      stringa * pwstra;
      if(!m_cacheMap.Lookup(pitem->m_iItem, pwstra))
      {
         _001CacheHint(pitem->m_plist, pitem->m_iItem, 1);
         if(!m_cacheMap.Lookup(pitem->m_iItem, pwstra))
            return_(pitem->m_bOk, false);
      }
      if(pitem->m_iColumnKey >= pwstra->get_size())
         return_(pitem->m_bOk, false);

      pitem->m_strText = pwstra->element_at(pitem->m_iColumnKey);

      pitem->m_bOk = true;
   }

   void list_cache::_001Invalidate()
   {
      m_cacheMap.remove_all();
   }

} // namespace user
