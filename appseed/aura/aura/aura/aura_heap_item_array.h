#pragma once


class CLASS_DECL_AXIS heap_item_array:
   public array < heap_item,heap_item >
{
public:

#ifdef METROWIN
   DWORD64 m_dwLastCleanup;
#else
   uint32_t m_dwLastCleanup;
#endif

   inline void add_item(void * p,::primitive::memory_size iSize)
   {
#ifdef METROWIN
      add(heap_item(p,iSize,GetTickCount64()));
      if(GetTickCount64() > m_dwLastCleanup + 10000)
#else
      add(heap_item(p,iSize,get_tick_count()));
      if(get_tick_count() > m_dwLastCleanup + 10000)
#endif
      {
         cleanup();
      }
   }

   inline void cleanup()
   {
#ifdef METROWIN
      DWORD64 dwLimit = GetTickCount64() - 1000;
#else
      DWORD64 dwLimit = get_tick_count() - 1000;
#endif
      for(int32_t i = 0; i < this->get_count();)
      {
         if(dwLimit > m_pData[i].m_dwTickCount)
         {
            remove_at(i);
         }
         else
         {
            i++;
         }
      }
#ifdef METROWIN
      m_dwLastCleanup = GetTickCount64();
#else
      m_dwLastCleanup = get_tick_count();
#endif
   }

   inline bool find(void * p,bool bRemove)
   {
      UNREFERENCED_PARAMETER(bRemove);

      for(int32_t mi = 0; mi < this->get_count(); mi++)
      {
         if(m_pData[mi].contains(p))
         {
            remove_at(mi);
            return true;
         }
      }
      return false;
   }

   /*inline void set_heap_alloc(sp(element) pca)
   {
   if(find(pca, true))
   {
   pca->m_ulFlags |= element::flag_heap_alloc;
   }
   }*/

};


