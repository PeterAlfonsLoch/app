#include "framework.h"


#ifdef APPLEOS


#define ALIGN_BYTE_COUNT (sizeof(size_t) * 2)


#else


#define ALIGN_BYTE_COUNT (sizeof(size_t))


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


plex_heap_alloc_array * g_pheap = NULL;


extern string_manager * s_pstringmanager;


extern mutex * g_pmutexSystemHeap;


extern plex_heap_alloc_array * g_pheap;


//extern mutex * g_pmutexTrace;


extern mutex * g_pmutgen;


void create_id_space();


void destroy_id_space();


//extern string * g_pstrLastStatus;


//extern string * g_pstrLastGlsStatus;


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




BEGIN_EXTERN_C


#define BASE_MEMORY_MANAGEMENT TRUE


#if BASE_MEMORY_MANAGEMENT

void * aligned_memory_alloc(size_t size)
{

   if(g_pheap == NULL)
   {
   
       void * pbase = malloc(heap_memory::aligned_provision_get_size(size));
       
       if (pbase == NULL)
       {
           
           throw memory_exception(get_thread_app());
           
       }
       
       return heap_memory::aligned(pbase, size, 128);
 
   }
   else
   {
       
       void * pbase = g_pheap->alloc(heap_memory::aligned_provision_get_size(size));

       if (pbase == NULL)
       {

           throw memory_exception(get_thread_app());

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

      throw memory_exception(get_thread_app());

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
   //byte * p = (byte *) _malloc_dbg(nSize + ALIGN_BYTE_COUNT + 32, nBlockUse, szFileName, nLine);
    if(g_pheap == NULL)
    {
        
        void * pbase = malloc(heap_memory::aligned_provision_get_size(size));
        
        if (pbase == NULL)
        {
            
            throw memory_exception(get_thread_app());
            
        }
        
        return heap_memory::aligned(pbase, size, 129);
        
    }
    else
    {
   
        void * pbase = g_pheap->alloc_dbg(heap_memory::aligned_provision_get_size(size), nBlockUse, szFileName, nLine);

        if (pbase == NULL)
        {

            throw memory_exception(get_thread_app());

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
   //byte * p = (byte *) _malloc_dbg(nSize + ALIGN_BYTE_COUNT + 32, nBlockUse, szFileName, nLine);
   void * pbase = g_pheap->alloc_dbg(heap_memory::unaligned_provision_get_size(size), nBlockUse, szFileName, nLine);

   if (pbase == NULL)
   {

      throw memory_exception(get_thread_app());

   }

   return heap_memory::unaligned(pbase, size, 3);

#endif

}




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


void * memory_realloc_dbg(void * pmemory, size_t size, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{

   if (pmemory == NULL)
      return memory_alloc_dbg(size, nBlockUse, szFileName, nLine);

   byte blockuse = heap_memory::heap_get_block_use(pmemory);

   size_t sizeOld = heap_memory::heap_get_size(pmemory);

   void * pbase = NULL;

   if (blockuse == 0) // aligned
   {

      pbase = g_pheap->realloc(heap_memory::base_get(pmemory), heap_memory::aligned_provision_get_size(size), heap_memory::aligned_provision_get_size(sizeOld), ALIGN_BYTE_COUNT);

   }
   else if (blockuse == 1) // aligned
   {

      //TODO: to do the dbg version

      pbase = g_pheap->realloc_dbg(heap_memory::base_get(pmemory), heap_memory::aligned_provision_get_size(size), heap_memory::aligned_provision_get_size(sizeOld), ALIGN_BYTE_COUNT, nBlockUse, szFileName, nLine);

   }
    else if (blockuse == 128) // aligned
    {
        
        pbase = realloc(heap_memory::base_get(pmemory), heap_memory::aligned_provision_get_size(size));
        
    }
    else if (blockuse == 129) // aligned
    {
        
        //TODO: to do the dbg version
        
        pbase = realloc(heap_memory::base_get(pmemory), heap_memory::aligned_provision_get_size(size));
        
    }
   else if (blockuse == 2) // unaligned
   {

      pbase = g_pheap->realloc(heap_memory::base_get(pmemory), heap_memory::unaligned_provision_get_size(size), heap_memory::unaligned_provision_get_size(sizeOld), 0);

   }
   else if (blockuse == 3) // unaligned
   {

      //TODO: to do the dbg version

      pbase = g_pheap->realloc_dbg(heap_memory::base_get(pmemory), heap_memory::unaligned_provision_get_size(size), heap_memory::unaligned_provision_get_size(sizeOld), 0, nBlockUse, szFileName, nLine);

   }
   else
   {

      throw memory_exception(get_thread_app());

   }

   if (pbase == NULL)
   {

      throw memory_exception(get_thread_app());

   }

   if (blockuse == 0 || blockuse == 1 || blockuse == 128 || blockuse == 129) // aligned
   {

      return heap_memory::aligned(pbase, size, blockuse);

   }
   else
   {

      return heap_memory::unaligned(pbase, size, blockuse);

   }




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

   if (pmemory == NULL)
      return;

   byte blockuse = heap_memory::heap_get_block_use(pmemory);

   size_t sizeOld = heap_memory::heap_get_size(pmemory);

   if (blockuse == 0)
   {

      g_pheap->free(heap_memory::base_get(pmemory), heap_memory::aligned_provision_get_size(sizeOld));

   }
   else if (blockuse == 1)
   {

      //TODO: to do the dbg version

      g_pheap->free_dbg(heap_memory::base_get(pmemory), heap_memory::aligned_provision_get_size(sizeOld));

   }
   else if (blockuse == 128)
    {
        
        free(heap_memory::base_get(pmemory));
        
    }
    else if (blockuse == 129)
    {
        
        //TODO: to do the dbg version
        
        free(heap_memory::base_get(pmemory));
        
    }
   else if (blockuse == 2)
   {

      g_pheap->free(heap_memory::base_get(pmemory), heap_memory::unaligned_provision_get_size(sizeOld));

   }
   else if (blockuse == 3)
   {

      //TODO: to do the dbg version

      g_pheap->free_dbg(heap_memory::base_get(pmemory), heap_memory::unaligned_provision_get_size(sizeOld));

   }
   else
   {

      ::OutputDebugStringW(L"wrong free");

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

   return malloc(size);

}

void * unaligned_memory_alloc(size_t size)
{

   return malloc(size);

}


void * aligned_memory_alloc_dbg(size_t size, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{

   return malloc(size);

}

void * unaligned_memory_alloc_dbg(size_t size, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{

   return malloc(size);

}




void * memory_alloc(size_t size)
{

   return malloc(size);

}


void * memory_calloc(size_t size, size_t bytes)
{

   return calloc(size, bytes);

}


void * memory_alloc_dbg(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{

   return malloc(nSize);

}


void * memory_realloc(void * pvoid, size_t nSize)
{

   return realloc(pvoid, nSize);

}


void * memory_realloc_dbg(void * pvoid, size_t size, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{


   return realloc(pvoid, size);



}

void memory_free(void * pvoid)
{
   return free(pvoid);
}


size_t memory_size(void * pvoid)
{
#ifdef WINDOWS
   return _msize(pvoid);
#else
   return malloc_size(pvoid);
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

   return malloc_size(pvoid);
#endif
}


#endif

#undef new





#if defined(LINUX) || defined(APPLEOS) || defined(METROWIN)

extern mutex * g_pmutexThreadIdHandleLock;

extern mutex * g_pmutexThreadIdLock;

extern mutex * g_pmutexPendingThreadsLock;

extern mutex * g_pmutexTlsData;

#endif // defined(LINUX) || defined(APPLEOS) || defined(METROWIN)


#if defined(LINUX) || defined(APPLEOS)

extern mutex * g_pmutexTz;

extern map < HTHREAD, HTHREAD, PendingThreadInfo, PendingThreadInfo > * g_ppendingThreads;

extern mutex * g_pmutexThreadHandleLock;

#endif // defined(LINUX) || defined(APPLEOS)



#if defined(LINUX)



#endif





#if defined(APPLEOS)

#include "base/os/macos/macos_window_impl.h"

extern oswindow_dataptra * g_poswindowdataptra;

#elif defined(APPLE_IOS)

#include "base/os/ios/ios_window_impl.h"

extern oswindow_dataptra * g_poswindowdataptra;

#endif




class base_static_start
{
public:

   base_static_start()
   {
      xxdebug_box("base.dll base_static_start (0)", "box", MB_OK);
      /*
      if(g_pfnca2_alloc == NULL)
      {
         g_pfnca2_alloc       = memory_alloc;
      }
      if(g_pfnca2_alloc_dbg == NULL)
      {
         g_pfnca2_alloc_dbg   = _ca_alloc_dbg;
      }
      if(g_pfnca2_realloc == NULL)
      {
         g_pfnca2_realloc     = memory_realloc_dbg;
      }
      if(g_pfnca2_free == NULL)
      {
         g_pfnca2_free        = memory_free_dbg;
      }
      if(g_pfnca2_msize == NULL)
      {
         g_pfnca2_msize       = _ca_msize;
      }

      */

      new plex_heap_alloc_array();

      s_pstringmanager = new string_manager();

      create_id_space();

      //g_pstrLastStatus = new string();

      //g_pstrLastGlsStatus = new string();

      g_pmutexSystemHeap = new mutex();

      g_pmutgen = new mutex();

      //g_pmutexTrace = new mutex();

#ifdef BSD_STYLE_SOCKETS

     ::sockets::base_socket::s_pmutex = new mutex();

#endif

#if defined(WINDOWSEX)

      os_thread::s_pmutex = new mutex();

      os_thread::s_pptra = new comparable_raw_array < os_thread * >::type ();

#endif

#if defined(LINUX) || defined(APPLEOS) || defined(METROWIN)

      g_pmutexThreadIdHandleLock = new mutex;

      g_pmutexThreadIdLock = new mutex;

      g_pmutexPendingThreadsLock = new mutex;

      g_pmutexTlsData = new mutex;

      os_thread::s_pmutex = new mutex();

      os_thread::s_pptra = new comparable_raw_array < os_thread * >::type ();

#endif // defined(LINUX) || defined(APPLEOS) || defined(METROWIN)

#if defined(LINUX) || defined(APPLEOS)

      g_pmutexTz = new mutex();

      g_ppendingThreads = new map < HTHREAD, HTHREAD, PendingThreadInfo, PendingThreadInfo >();

      g_pmutexThreadHandleLock = new mutex;


#endif // defined(LINUX) || defined(APPLEOS)





#if defined(LINUX)

      oswindow_data::s_pdataptra = new oswindow_dataptra;

      oswindow_data::s_pmutex = new mutex;

      osdisplay_data::s_pdataptra = new osdisplay_dataptra;

      osdisplay_data::s_pmutex = new mutex;

#endif // defined(LINUX)



#if defined(APPLEOS)

      g_poswindowdataptra = new oswindow_dataptra;

#endif // defined(APPLEOS)


//      IMPLEMENT_BASE_FIXED_ALLOC_CONSTRUCTOR(var, 1024)
  //    IMPLEMENT_BASE_FIXED_ALLOC_CONSTRUCTOR(property, 1024)


   }

   ~base_static_start()
   {


    //  IMPLEMENT_BASE_FIXED_ALLOC_DESTRUCTOR(property)
//      IMPLEMENT_BASE_FIXED_ALLOC_DESTRUCTOR(var)



#if defined(LINUX) || defined(APPLEOS)




      delete g_pmutexThreadHandleLock;

      g_pmutexThreadHandleLock = NULL;


      delete g_ppendingThreads;

      g_ppendingThreads = NULL;

      delete g_pmutexTz;

      g_pmutexTz = NULL;

#endif // defined(LINUX) || defined(APPLEOS)


#if defined(LINUX) || defined(APPLEOS) || defined(METROWIN)

      delete os_thread::s_pptra;

      os_thread::s_pptra = NULL;

      delete os_thread::s_pmutex;

      os_thread::s_pmutex = NULL;

      delete g_pmutexTlsData;

      g_pmutexTlsData = NULL;

      delete g_pmutexPendingThreadsLock;

      g_pmutexPendingThreadsLock = NULL;

      delete g_pmutexThreadIdHandleLock;

      g_pmutexThreadIdHandleLock = NULL;

      delete g_pmutexThreadIdLock;

      g_pmutexThreadIdLock = NULL;

#endif  // defined(LINUX) || defined(APPLEOS) || defined(METROWIN)



#if defined(LINUX)

      delete osdisplay_data::s_pmutex;

      osdisplay_data::s_pmutex = NULL;

      delete osdisplay_data::s_pdataptra;

      osdisplay_data::s_pdataptra = NULL;

      delete oswindow_data::s_pmutex;

      oswindow_data::s_pmutex = NULL;

      delete oswindow_data::s_pdataptra;

      oswindow_data::s_pdataptra = NULL;

#endif // defined(LINUX)





#if defined(APPLEOS)

      delete g_poswindowdataptra;

      g_poswindowdataptra = NULL;

#endif // defined(APPLEOS)

#ifdef BSD_STYLE_SOCKETS

      delete ::sockets::base_socket::s_pmutex;

      ::sockets::base_socket::s_pmutex = NULL;

#endif




      //delete g_pmutexTrace;

      //g_pmutexTrace = NULL;

      delete g_pmutgen;

      g_pmutgen = NULL;

      delete g_pmutexSystemHeap;

      g_pmutexSystemHeap = NULL;

      //delete g_pstrLastGlsStatus;

      //g_pstrLastGlsStatus = NULL;

      //delete g_pstrLastStatus;

      //g_pstrLastStatus = NULL;

      destroy_id_space();

      delete s_pstringmanager;

      s_pstringmanager = NULL;

      delete g_pheap;



   }

} g_basestaticstart;






END_EXTERN_C



void create_id_space()
{

   base_system::s_pidspace = new id_space();

}

void destroy_id_space()
{

   delete base_system::s_pidspace;

   base_system::s_pidspace = NULL;

}






