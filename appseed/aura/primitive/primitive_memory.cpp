//#include "framework.h"



memory::memory(manager * pmanager)
{

   UNREFERENCED_PARAMETER(pmanager);
   m_pprimitivememory   = this;
   m_pbStorage          = NULL;
   m_pbComputed         = NULL;
   m_pcontainer         = NULL;
   m_iOffset            = 0;
   m_dwAllocation       = 0;
   m_cbStorage          = 0;
   m_bAligned = false;

}

memory::memory(const memory & s,manager * pmanager)
{

   UNREFERENCED_PARAMETER(pmanager);

   m_pprimitivememory   = this;
   m_pbStorage    = NULL;
   m_pbComputed   = NULL;
   m_iOffset      = 0;
   m_dwAllocation = 0;
   m_cbStorage    = 0;
   m_bAligned = false;
   memory_base::operator = (s);

}
   
   
memory::memory(const memory * ps,manager * pmanager)
{
      
   UNREFERENCED_PARAMETER(pmanager);
      
   m_pprimitivememory   = this;
   m_pbStorage    = NULL;
   m_pbComputed   = NULL;
   m_iOffset      = 0;
   m_dwAllocation = 0;
   m_cbStorage    = 0;
   m_bAligned = false;
   memory_base::operator = (*ps);
      
}
 
   
memory::memory(const byte * pchSrc,strsize nLength,manager * pmanager)
{

   UNREFERENCED_PARAMETER(pmanager);

   m_pprimitivememory   = this;
   m_pbStorage    = NULL;
   m_pbComputed   = NULL;
   m_iOffset      = 0;
   m_bAligned = false;
   allocate(nLength);
   ASSERT(__is_valid_address(pchSrc,nLength,FALSE));
   memcpy(m_pbStorage,pchSrc,nLength);


}


memory::memory(::aura::application * papp) :
   object(papp)
{

   m_pprimitivememory   = this;
   m_pbStorage          = NULL;
   m_pbComputed         = NULL;
   m_pcontainer         = NULL;
   m_iOffset            = 0;
   m_dwAllocation       = 0;
   m_cbStorage          = 0;
   m_bAligned = false;

}

memory::memory(::aura::application * papp, bool bAligned) :
   object(papp)
{

   m_pprimitivememory = this;
   m_pbStorage = NULL;
   m_pbComputed = NULL;
   m_pcontainer = NULL;
   m_iOffset = 0;
   m_dwAllocation = 0;
   m_cbStorage = 0;
   m_bAligned = bAligned;

}

memory::memory(const byte * pdata,memory_size_t iCount)
{
   m_pprimitivememory   = this;
   m_pbStorage    = NULL;
   m_pbComputed   = NULL;
   m_iOffset      = 0;
   m_bAligned = false;
   allocate(iCount);
   if(pdata != NULL)
   {
      ASSERT(__is_valid_address(pdata,iCount,FALSE));
      memcpy(m_pbStorage,pdata,iCount);
   }
}

memory::memory(const void * pdata, memory_size_t iCount)
{
   m_pprimitivememory   = this;
   m_pbStorage    = NULL;
   m_pbComputed   = NULL;
   m_iOffset      = 0;
   m_bAligned = false;
   allocate(iCount);
   ASSERT(__is_valid_address(pdata, iCount, FALSE));
   memcpy(m_pbStorage, pdata, iCount);
}

memory::memory(const memory_base & s)
{
   m_pprimitivememory   = this;
   m_pbStorage    = NULL;
   m_pbComputed   = NULL;
   m_iOffset      = 0;
   m_dwAllocation = 0;
   m_cbStorage    = 0;
   m_bAligned = false;
   memory_base::operator = (s);
}

memory::memory(const memory & s)
{
   m_pprimitivememory   = this;
   m_pbStorage    = NULL;
   m_pbComputed   = NULL;
   m_iOffset      = 0;
   m_dwAllocation = 0;
   m_cbStorage    = 0;
   m_bAligned = s.m_bAligned;
   memory_base::operator = (s);
}

memory::memory(const char * psz)
{
   m_pprimitivememory   = this;
   m_pbStorage    = NULL;
   m_pbComputed   = NULL;
   m_iOffset      = 0;
   m_dwAllocation = 0;
   m_cbStorage    = 0;
   m_bAligned = false;
   from_string(psz);
}

memory::memory(primitive::memory_container * pcontainer, memory_size_t dwAllocationAddUp, UINT nAllocFlags)
{
   UNREFERENCED_PARAMETER(nAllocFlags);
   m_pprimitivememory   = this;
   m_pbStorage          = NULL;
   m_pbComputed         = NULL;
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
   m_iOffset            = 0;
   m_dwAllocation       = 0;
   m_cbStorage          = 0;
   m_bAligned = false;
}

memory::memory(primitive::memory_container * pcontainer, void * pMemory, memory_size_t dwSize)
{
   m_pprimitivememory   = this;
   m_pbStorage          = NULL;
   m_pbComputed         = NULL;
   m_pcontainer         = pcontainer;
   m_iOffset            = 0;
   m_dwAllocation       = 0;
   m_cbStorage          = 0;
   m_bAligned = false;

   allocate(dwSize);
   ASSERT(__is_valid_address(pMemory, (uint_ptr) dwSize, FALSE));
   memcpy(m_pbStorage, pMemory, (size_t) dwSize);
}


memory::~memory()
{
   
   if(m_pbStorage != NULL)
   {

      impl_free(m_pbStorage);

   }

}


LPBYTE memory::impl_alloc(memory_size_t dwAllocation)
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

void memory::impl_free(void * pdata)
{

   memory_free(pdata);
   

}








