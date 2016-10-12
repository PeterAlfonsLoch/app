#pragma once

#if defined(MCHECK) || defined(_VLD) || defined(__MCRTDBG) || MEMDLEAK

#error "Either MCHECK, _VLD, __MCRTDBG or MEMDLEAK were defined"

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


   inline void check_padding_after()
   {

      for(int i = 0; i < m_iPaddingAfter; i++)
      {

         if(((byte *)&m_paddingBefore[16])[m_size + i] != 0)
         {

//            ::output_debug_string("*&!@");

         }

      }

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
