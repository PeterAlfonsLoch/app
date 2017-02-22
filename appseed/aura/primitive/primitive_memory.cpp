//#include "framework.h"



memory::memory(manager * pmanager)
{

   UNREFERENCED_PARAMETER(pmanager);
   m_pprimitivememory      = this;
   m_bAligned              = false;

}


memory::memory(const memory & s, manager * pmanager)
{

   UNREFERENCED_PARAMETER(pmanager);
   m_pprimitivememory      = this;
   m_bAligned              = false;
   memory_base::operator   = (s);

}


memory::memory(const memory * ps, manager * pmanager)
{

   UNREFERENCED_PARAMETER(pmanager);
   m_pprimitivememory      = this;
   m_bAligned              = false;
   memory_base::operator   = (*ps);

}


memory::memory(const byte * pchSrc, strsize nLength, manager * pmanager)
{

   UNREFERENCED_PARAMETER(pmanager);
   m_pprimitivememory      = this;
   m_bAligned              = false;
   allocate(nLength);
   ASSERT(__is_valid_address(pchSrc,nLength,FALSE));
   memcpy(m_pbStorage,pchSrc,nLength);
}


memory::memory(::aura::application * papp) :
   object(papp)
{

   m_pprimitivememory      = this;
   m_bAligned              = false;

}


memory::memory(::aura::application * papp, bool bAligned) :
   object(papp)
{

   m_pprimitivememory      = this;
   m_bAligned              = bAligned;

}


memory::memory(const byte * pdata, memory_size_t iCount)
{

   m_pprimitivememory      = this;
   m_pbStorage             = (LPBYTE)pdata;
   m_pbComputed            = m_pbComputed;
   m_bAligned              = false;
   m_cbStorage             = iCount;
   m_dwAllocation          = m_cbStorage;

}


memory::memory(const void * pdata, memory_size_t iCount)
{

   m_pprimitivememory      = this;
   m_pbStorage             = (LPBYTE) pdata;
   m_pbComputed            = m_pbStorage;
   m_bAligned              = false;
   m_cbStorage             = iCount;
   m_dwAllocation          = m_cbStorage;

}

memory::memory(const memory_base & s)
{

   m_pprimitivememory      = this;
   m_bAligned              = false;
   memory_base::operator   = (s);

}


memory::memory(const memory & s)
{
   
   m_pprimitivememory      = this;
   m_bAligned              = s.m_bAligned;
   memory_base::operator   = (s);

}


memory::memory(const char * psz)
{

   m_pprimitivememory   = this;
   m_pbStorage          = (LPBYTE) psz;
   m_pbComputed         = m_pbStorage;
   m_cbStorage          = strlen(psz);
   m_dwAllocation       = m_cbStorage;
   m_bAligned           = false;

}


memory::memory(primitive::memory_container * pcontainer, memory_size_t dwAllocationAddUp, UINT nAllocFlags)
{

   UNREFERENCED_PARAMETER(nAllocFlags);
   m_pprimitivememory   = this;
   m_pcontainer         = pcontainer;
   if(dwAllocationAddUp == 0)
   {
#ifdef DEBUG
      dwAllocationAddUp = 16 * 1024; // 16k
#else
      dwAllocationAddUp = 4 * 1024; // 4k
#endif
   }
   m_dAllocationRateUp  = m_dAllocationRateUp;
   m_bAligned           = false;

}


memory::memory(primitive::memory_container * pcontainer, void * pMemory, memory_size_t dwSize)
{
   
   m_pprimitivememory   = this;
   m_pbStorage          = (LPBYTE) pMemory;
   m_pbComputed         = m_pbStorage;
   m_pcontainer         = pcontainer;
   m_cbStorage          = dwSize;
   m_dwAllocation       = m_cbStorage;
   m_bAligned           = false;

}



























memory::~memory()
{

   if(m_pbStorage != NULL)
   {

      impl_free(m_pbStorage);

      m_pbStorage = NULL;

   }

}


LPBYTE memory::impl_alloc(memory_size_t dwAllocation)
{
#if !MEMDLEAK
   if(m_bAligned)
   {
      return (LPBYTE)aligned_memory_alloc((size_t)dwAllocation);
   }
   else
   {
      return (LPBYTE)memory_alloc((size_t)dwAllocation);
   }

   #else
   if(m_strTag.has_char() && ::get_thread() != NULL)
   {
      if(::get_thread()->m_strDebug.has_char())
      {
         if(m_bAligned)
         {
            return (LPBYTE)aligned_memory_alloc_dbg((size_t)dwAllocation, 723, "thread://" + demangle(typeid(*::get_thread()).name()) + "="+ ::get_thread()->m_strDebug + ", memory://" + m_strTag, m_iLine);
         }
         else
         {
            return (LPBYTE)memory_alloc_dbg((size_t)dwAllocation, 723, "thread://" + demangle(typeid(*::get_thread()).name()) + "="+ ::get_thread()->m_strDebug + ", memory://"+m_strTag, m_iLine);
         }
      }
      else
      {
         if(m_bAligned)
         {
            return (LPBYTE)aligned_memory_alloc_dbg((size_t)dwAllocation, 723, "thread://" + demangle(typeid(*::get_thread()).name()) + ", memory://" + m_strTag, m_iLine);
         }
         else
         {
            return (LPBYTE)memory_alloc_dbg((size_t)dwAllocation, 723, "thread://" + demangle(typeid(*::get_thread()).name()) + ", memory://"+m_strTag, m_iLine);
         }
      }
   }
   else if(m_strTag.has_char())
   {
      if(m_bAligned)
      {
         return (LPBYTE)aligned_memory_alloc_dbg((size_t)dwAllocation, 723, m_strTag, m_iLine);
      }
      else
      {
         return (LPBYTE)memory_alloc_dbg((size_t)dwAllocation, 723, m_strTag, m_iLine);
      }
   }
   else
   {
      if(m_bAligned)
      {
         return (LPBYTE)aligned_memory_alloc((size_t)dwAllocation);
      }
      else
      {
         return (LPBYTE)memory_alloc((size_t)dwAllocation);
      }
   }

   #endif

}

LPBYTE memory::impl_realloc(void * pdata, memory_size_t dwAllocation)
{
   if(m_bAligned)
   {
      return NULL;
   }
   else
   {
      return (LPBYTE)memory_realloc(pdata, (size_t)dwAllocation);
   }

}

void memory::impl_free(LPBYTE pdata)
{

   if (m_bOwn)
   {

      memory_free(pdata);

   }

}








