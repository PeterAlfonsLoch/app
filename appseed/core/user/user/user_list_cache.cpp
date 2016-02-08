//#include "framework.h"


namespace user
{


   list_cache::list_cache()
   {

      m_bCaching = false;

   }


   list_cache::~list_cache()
   {


   }


   void list_cache::_001CacheHint(      ::user::mesh * pmesh,      index iItemStart,      index iItemCount)
   {

      synch_lock sl(pmesh->m_pmutex);

      ::user::list * plist = pmesh->m_plist;

      keep < bool > keepCaching(&m_bCaching,true,false,true);

      if(iItemStart  < 0)
      {

         iItemStart = 0;

      }

      index iItem;

      index iColumn;

      string str;

      index iItemEnd = iItemStart + iItemCount - 1;

      draw_list_item item(plist);

      for(iItem = iItemStart; iItem <= iItemEnd; iItem++)
      {

         int_ptr_to_string & m = m_map[iItem];

         for(iColumn = 0; iColumn < plist->m_columna.get_count(); iColumn++)
         {

            item.m_iItem = iColumn;

            item.m_iSubItem = plist->m_columna._001GetByKey(iColumn)->m_iSubItem;

            item.m_iListItem = -1;

            item.m_strText.Empty();

            item.m_bOk = false;

            try
            {

               plist->_001GetItemText(&item);

            }
            catch(...)
            {

               item.m_bOk = false;

            }

            if(item.m_bOk)
            {

               m.set_at(item.m_iSubItem,item.m_strText);

            }

         }

      }

   }


   void list_cache::_001GetItemText(::user::mesh_item * pitem)
   {

      if(m_bCaching)
         return_(pitem->m_bOk,false);

      if(pitem->m_iItem < 0)
         return_(pitem->m_bOk,false);

      auto pmap = m_map.PLookup(pitem->m_iItem);

      if(pmap == NULL)
      {

         return_(pitem->m_bOk,false);

      }

      auto passoc = pmap->m_element2.PLookup(pitem->m_iItem);

      if(passoc == NULL)
      {

         return_(pitem->m_bOk,false);

      }

      pitem->m_strText = passoc->m_element2;

      pitem->m_bOk = true;

   }


   void list_cache::_001Invalidate()
   {

      m_map.remove_all();

   }


} // namespace user


