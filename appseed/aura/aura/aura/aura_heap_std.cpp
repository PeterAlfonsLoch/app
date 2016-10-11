#if defined(MCHECK) || defined(_VLD) || defined(__MCRTDBG) || defined(MEMDLEAK)

#error "Either MCHECK, _VLD, __MCRTDBG or MEMDLEAK were defined"

#endif


#include "aura_heap_memory.h"


BEGIN_EXTERN_C



void * aligned_memory_alloc(size_t size)
{

   void * p;

   if(g_pheap == NULL)
   {

       void * pbase = system_heap_alloc(heap_memory::aligned_provision_get_size(size));

       if (pbase == NULL)
       {

          return NULL;

       }

      p = heap_memory::aligned(pbase, size, 128);

   }
   else
   {

      if (heap_memory::aligned_provision_get_size(size) == 831
         && heap_memory::aligned_provision_get_size(size) < 1024)
      {
         output_debug_string("*");
      }

       void * pbase = g_pheap->_alloc(heap_memory::aligned_provision_get_size(size));

       if (pbase == NULL)
       {

          return NULL;

       }

       p = heap_memory::aligned(pbase, size, 0);

   }

   return p;

}


void * unaligned_memory_alloc(size_t size)
{

   void * p;

#if defined(APPLEOS) || defined(LINUX)

   p = aligned_memory_alloc(size);

#else

   void * pbase = g_pheap->_alloc(heap_memory::unaligned_provision_get_size(size));

   if (pbase == NULL)
   {

       return NULL;

   }
   else
   {

      p = heap_memory::unaligned(pbase, size, 2);

   }

#endif

   return p;

}


void * aligned_memory_alloc_dbg(size_t size, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{

   void * p;


   UNREFERENCED_PARAMETER(nBlockUse);
   UNREFERENCED_PARAMETER(szFileName);
   UNREFERENCED_PARAMETER(nLine);

   //TODO: to do the dbg version
   //byte * p = (byte *) _system_heap_alloc_dbg(nSize + ALIGN_BYTE_COUNT + 32, nBlockUse, szFileName, nLine);
    if(g_pheap == NULL)
    {

        void * pbase = system_heap_alloc(heap_memory::aligned_provision_get_size(size));

        if (pbase == NULL)
        {

            return NULL;

        }

        p = heap_memory::aligned(pbase, size, 129);

    }
    else
    {

        void * pbase = g_pheap->alloc_dbg(heap_memory::aligned_provision_get_size(size), nBlockUse, szFileName, nLine);

        if (pbase == NULL)
        {

           return NULL;

        }

        p = heap_memory::aligned(pbase, size, 1);

    }

    //zero(p, size);

    return p;

}


void * unaligned_memory_alloc_dbg(size_t size, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{

   void * p;

#ifdef APPLEOS

   p = aligned_memory_alloc(size);

#else

   UNREFERENCED_PARAMETER(nBlockUse);
   UNREFERENCED_PARAMETER(szFileName);
   UNREFERENCED_PARAMETER(nLine);

   //TODO: to do the dbg version
   //byte * p = (byte *) _system_heap_alloc_dbg(nSize + ALIGN_BYTE_COUNT + 32, nBlockUse, szFileName, nLine);
   void * pbase = g_pheap->alloc_dbg(heap_memory::unaligned_provision_get_size(size), nBlockUse, szFileName, nLine);

   if (pbase == NULL)
   {

      return NULL;

   }

   p = heap_memory::unaligned(pbase, size, 3);

#endif

   //zero(p, size);

   return p;

}


#undef memory_alloc

void * memory_alloc(size_t size)
{

#if defined(APPLEOS)

   return aligned_memory_alloc(size);

#else

   return unaligned_memory_alloc(size);

#endif

}


void * memory_alloc_no_track(size_t size)
{

#if defined(APPLEOS)

   return aligned_memory_alloc(size);

#else

   return unaligned_memory_alloc(size);

#endif

}




void * memory_calloc(size_t size, size_t bytes)
{

   return memory_alloc(size * bytes);

}


void * memory_alloc_dbg(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{

   return unaligned_memory_alloc_dbg(nSize, nBlockUse, szFileName, nLine);

}


void * memory_realloc(void * pmemory, size_t nSize)
{

   return memory_realloc_dbg(pmemory, nSize, 0, NULL, -1);

}



void * memory_realloc_dbg(void * pmemory, size_t size, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{

   if (pmemory == NULL)
      return memory_alloc_dbg(size, nBlockUse, szFileName, nLine);

   byte blockuse = heap_memory::heap_get_block_use(pmemory);

   size_t sizeOld = heap_memory::heap_get_size(pmemory);

   void * pbase = NULL;

   if(blockuse == 0) // aligned
   {

      pbase = g_pheap->_realloc(heap_memory::base_get(pmemory),heap_memory::aligned_provision_get_size(size),heap_memory::aligned_provision_get_size(sizeOld),ALIGN_BYTE_COUNT);

   }
   else if(blockuse == 1) // aligned
   {

      //TODO: to do the dbg version

      pbase = g_pheap->realloc_dbg(heap_memory::base_get(pmemory),heap_memory::aligned_provision_get_size(size),heap_memory::aligned_provision_get_size(sizeOld),ALIGN_BYTE_COUNT,nBlockUse,szFileName,nLine);

   }
   else if(blockuse == 128) // aligned
   {

      pbase = realloc(heap_memory::base_get(pmemory),heap_memory::aligned_provision_get_size(size));

   }
   else if(blockuse == 129) // aligned
   {

      //TODO: to do the dbg version

      pbase = realloc(heap_memory::base_get(pmemory),heap_memory::aligned_provision_get_size(size));

   }
   else if(blockuse == 2) // unaligned
   {

      pbase = g_pheap->_realloc(heap_memory::base_get(pmemory),heap_memory::unaligned_provision_get_size(size),heap_memory::unaligned_provision_get_size(sizeOld),0);

   }
   else if(blockuse == 3) // unaligned
   {

      //TODO: to do the dbg version

      pbase = g_pheap->realloc_dbg(heap_memory::base_get(pmemory),heap_memory::unaligned_provision_get_size(size),heap_memory::unaligned_provision_get_size(sizeOld),0,nBlockUse,szFileName,nLine);

   }
   else
   {

      return NULL;

   }

   if(pbase == NULL)
   {

      return NULL;

   }

   if(blockuse == 0 || blockuse == 1 || blockuse == 128 || blockuse == 129) // aligned
   {

      return heap_memory::aligned(pbase,size,blockuse);

   }
   else
   {

      return heap_memory::unaligned(pbase,size,blockuse);

   }

   return NULL;


}

void memory_free(void * pmemory)
{

   return memory_free_dbg(pmemory, 0);

}





void memory_free_dbg(void * pmemory, int32_t iBlockType)
{

   if((int_ptr) pmemory < 1024)
   {

      return;

   }


   heap_memory * pheap =  ::heap_memory::heap_get(pmemory);

   void * pbase = (void *)(((int_ptr)pmemory) - pheap->m_back);


   pheap->check_padding_after();


   if(pheap->m_blockuse == 0)
   {

      g_pheap->_free(pbase,heap_memory::aligned_provision_get_size(pheap->m_size));

   }
   else if(pheap->m_blockuse == 1)
   {

      //TODO: to do the dbg version

      g_pheap->free_dbg(pbase,heap_memory::aligned_provision_get_size(pheap->m_size));

   }
   else if(pheap->m_blockuse == 128)
   {

      system_heap_free(pbase);

   }
   else if(pheap->m_blockuse == 129)
   {

      //TODO: to do the dbg version

      system_heap_free(pbase);

   }
   else if(pheap->m_blockuse == 2)
   {

      g_pheap->_free(pbase,heap_memory::unaligned_provision_get_size(pheap->m_size));

   }
   else if(pheap->m_blockuse == 3)
   {

      //TODO: to do the dbg version

      g_pheap->free_dbg(pbase,heap_memory::unaligned_provision_get_size(pheap->m_size));

   }
   else
   {

      ::output_debug_string("wrong free");

   }

}



size_t memory_size(void * pmemory)
{

   return memory_size_dbg(pmemory, _NORMAL_BLOCK);

}

size_t memory_size_dbg(void * pmemory, int32_t iBlockType)
{


   if (pmemory == NULL)
      return 0;

   return heap_memory::heap_get_size(pmemory);


}




END_EXTERN_C






