#pragma once


class CLASS_DECL_AURA heap_item
{
public:


   byte *      m_pbStart;
   byte *      m_pbEnd;
#ifdef METROWIN
   DWORD64     m_dwTickCount;
#else
   uint32_t       m_dwTickCount;
#endif


   inline heap_item()
   {
      m_pbStart = NULL;
      m_pbEnd = NULL;
   }


#ifdef METROWIN
   inline heap_item(void * p,::primitive::memory_size iSize,DWORD64 dwTick)
#else
   inline heap_item(void * p,::primitive::memory_size iSize,uint32_t dwTick)
#endif
   {
      m_pbStart = (byte *)p;
      m_pbEnd = ((byte *)p) + MAX(iSize - 1,0);
      m_dwTickCount = dwTick;
   }


   inline char compare(void * p)
   {
      if(((byte *)p) <= m_pbStart)
         return 1;
      else if(((byte *)p) >= m_pbEnd)
         return -1;
      else
         return 0;
   }

   inline bool contains(void * p)
   {
      if(((byte *)p) <= m_pbStart)
         return false;
      else if(((byte *)p) >= m_pbEnd)
         return false;
      else
         return true;
   }

};





