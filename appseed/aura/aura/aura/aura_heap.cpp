//#include "framework.h"


#ifdef APPLEOS


#define ALIGN_BYTE_COUNT (sizeof(size_t) * 2)


#else


//#define ALIGN_BYTE_COUNT (sizeof(size_t))

#define ALIGN_BYTE_COUNT 16


#endif


struct heap_memory
{


   int32_t              m_back;
   int32_t              m_blockuse;
   size_t               m_size;
   char                 m_paddingBefore[16];
   static const int     m_iPaddingAfter;


   inline static size_t aligned_provision_get_size(size_t size)
   {

      return size + sizeof(heap_memory) + m_iPaddingAfter + ALIGN_BYTE_COUNT - 1;

   }

   inline static size_t unaligned_provision_get_size(size_t size)
   {

      return size + sizeof(heap_memory) + m_iPaddingAfter;

   }

   inline static void * unaligned(void * pbase, size_t size, int32_t blockuse)
   {

      void * pmemory = (void *)((int_ptr)pbase + sizeof(heap_memory));

      heap_memory * pheap = heap_get(pmemory);

      pheap->m_back = (int32_t)(((int_ptr)pmemory) - ((int_ptr)pbase));

      pheap->m_blockuse = blockuse;

      pheap->m_size = size;

      return pmemory;

   }


   inline static void * aligned(void * pbase, size_t size, int32_t blockuse)
   {

      void * pmemory = (void *)((((int_ptr)pbase) + sizeof(heap_memory) + ALIGN_BYTE_COUNT - 1) & ((~((int_ptr)ALIGN_BYTE_COUNT - 1))));

      heap_memory * pheap = heap_get(pmemory);

      pheap->m_back = (int32_t)(((int_ptr)pmemory) - ((int_ptr)pbase));

      pheap->m_blockuse = blockuse;

      pheap->m_size = size;

      return pmemory;

   }


   inline static heap_memory * heap_get(void * pmemory)
   {

      return (heap_memory *)(((int_ptr)pmemory) - sizeof(heap_memory));

   }


   inline static void * base_get(void * pmemory)
   {

      return (void *)(((int_ptr)pmemory) - heap_get(pmemory)->m_back);

   }

   inline static int32_t heap_get_block_use(void * pmemory)
   {

      return heap_get(pmemory)->m_blockuse;

   }


   inline static size_t heap_get_size(void * pmemory)
   {

      return heap_get(pmemory)->m_size;

   }


};


const int heap_memory::m_iPaddingAfter = 16;





c_class c_class::s_cclass;


c_class::c_class()
{
}

c_class::c_class(const c_class &)
{
}

c_class::~c_class()
{
}


plex_heap_alloc_array * g_pheap = NULL;


BEGIN_EXTERN_C


#define AXIS_MEMORY_MANAGEMENT TRUE


#if AXIS_MEMORY_MANAGEMENT

void * aligned_memory_alloc(size_t size)
{

   if(g_pheap == NULL)
   {

       void * pbase = system_heap_alloc(heap_memory::aligned_provision_get_size(size));

       if (pbase == NULL)
       {

          return NULL;

       }

       return heap_memory::aligned(pbase, size, 128);

   }
   else
   {

   if(heap_memory::aligned_provision_get_size(size) ==831
   && heap_memory::aligned_provision_get_size(size)< 1024)
   {
   output_debug_string("*");
   }

       void * pbase = g_pheap->alloc(heap_memory::aligned_provision_get_size(size));

       if (pbase == NULL)
       {

          return NULL;

       }

       return heap_memory::aligned(pbase, size, 0);

   }

}

void * unaligned_memory_alloc(size_t size)
{

#if defined(APPLEOS) || defined(LINUX)

   return aligned_memory_alloc(size);

#else

   void * pbase = g_pheap->alloc(heap_memory::unaligned_provision_get_size(size));

   if (pbase == NULL)
   {

      return NULL;

   }

   return heap_memory::unaligned(pbase, size, 2);

#endif

}


void * aligned_memory_alloc_dbg(size_t size, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{

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

        return heap_memory::aligned(pbase, size, 129);

    }
    else
    {

        void * pbase = g_pheap->alloc_dbg(heap_memory::aligned_provision_get_size(size), nBlockUse, szFileName, nLine);

        if (pbase == NULL)
        {

           return NULL;

        }

        return heap_memory::aligned(pbase, size, 1);

    }

}

void * unaligned_memory_alloc_dbg(size_t size, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{

#ifdef APPLEOS

   return aligned_memory_alloc(size);

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

   return heap_memory::unaligned(pbase, size, 3);

#endif

}


BEGIN_EXTERN_C

void * memory_alloc(size_t size)
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

END_EXTERN_C

void * memory_realloc_dbg(void * pmemory, size_t size, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{

   if (pmemory == NULL)
      return memory_alloc_dbg(size, nBlockUse, szFileName, nLine);

   byte blockuse = heap_memory::heap_get_block_use(pmemory);

   size_t sizeOld = heap_memory::heap_get_size(pmemory);

   void * pbase = NULL;

   if(blockuse == 0) // aligned
   {

      pbase = g_pheap->realloc(heap_memory::base_get(pmemory),heap_memory::aligned_provision_get_size(size),heap_memory::aligned_provision_get_size(sizeOld),ALIGN_BYTE_COUNT);

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

      pbase = g_pheap->realloc(heap_memory::base_get(pmemory),heap_memory::unaligned_provision_get_size(size),heap_memory::unaligned_provision_get_size(sizeOld),0);

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


size_t memory_size(void * pmemory)
{

   return memory_size_dbg(pmemory, 0);

}




void memory_free_dbg(void * pmemory, int32_t iBlockType)
{

   heap_memory * pheap =  ::heap_memory::heap_get(pmemory);


   void * pbase = (void *)(((int_ptr)pmemory) - pheap->m_back);

   for(int i = 0; i < pheap->m_iPaddingAfter; i++)
   {

      if(((byte *)&pheap->m_paddingBefore[16])[pheap->m_size + i] != 0)
      {
         ::OutputDebugString("*&!@");
      }

   }

   if(pheap->m_blockuse == 0)
   {

      g_pheap->free(pbase,heap_memory::aligned_provision_get_size(pheap->m_size));

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

      g_pheap->free(pbase,heap_memory::unaligned_provision_get_size(pheap->m_size));

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


size_t memory_size_dbg(void * pmemory, int32_t iBlockType)
{

   if (pmemory == NULL)
      return 0;

   return heap_memory::heap_get_size(pmemory);

}


#else



void * aligned_memory_alloc(size_t size)
{

   return system_heap_alloc(size);

}

void * unaligned_memory_alloc(size_t size)
{

   return system_heap_alloc(size);

}


void * aligned_memory_alloc_dbg(size_t size, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{

   return system_heap_alloc(size);

}

void * unaligned_memory_alloc_dbg(size_t size, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{

   return system_heap_alloc(size);

}




void * memory_alloc(size_t size)
{

   return system_heap_alloc(size);

}


void * memory_calloc(size_t size, size_t bytes)
{

   return calloc(size, bytes);

}


void * memory_alloc_dbg(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{

   return system_heap_alloc(nSize);

}


void * memory_realloc(void * pvoid, size_t nSize)
{

   return system_heap_realloc(pvoid, nSize);

}


void * memory_realloc_dbg(void * pvoid, size_t size, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{


   return system_heap_realloc(pvoid, size);



}

void memory_free(void * pvoid)
{
   return system_heap_free(pvoid);
}


size_t memory_size_t(void * pvoid)
{
#ifdef WINDOWS
   return _msize(pvoid);
#else
   return system_heap_alloc_size(pvoid);
#endif
}


void memory_free_dbg(void * pvoid, int32_t iBlockType)
{

   memory_free(pvoid);

}


size_t memory_size_dbg(void * pvoid, int32_t iBlockType)
{
#ifdef WINDOWS
   return _msize(pvoid);
#else

   return system_heap_alloc_size(pvoid);
#endif
}


#endif



END_EXTERN_C



id_space * create_id_space()
{

   return new id_space();

}

/*
void destroy_id_space() // let it go with the ({"eco}system") processs
{

   delete ::aura::system::s_pidspace;

   ::aura::system::s_pidspace = NULL;

}
*/





