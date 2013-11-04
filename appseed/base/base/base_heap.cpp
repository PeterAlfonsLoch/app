#include "framework.h"

/*
#ifdef WINDOWS
CLASS_DECL_BASE void * (*g_pfnca2_alloc)(size_t size) = NULL;
CLASS_DECL_BASE void * (*g_pfnca2_alloc_dbg)(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine) = NULL;
CLASS_DECL_BASE void * (*g_pfnca2_realloc)(void * pvoid, size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine) = NULL;
CLASS_DECL_BASE void   (*g_pfnca2_free)(void * pvoid, int32_t iBlockType) = NULL;
CLASS_DECL_BASE size_t (*g_pfnca2_msize)(void * pvoid, int32_t iBlockType) = NULL;
#else
CLASS_DECL_BASE void * (*g_pfnca2_alloc)(size_t size) = &::memory_alloc;
CLASS_DECL_BASE void * (*g_pfnca2_alloc_dbg)(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine) = &::_ca_alloc_dbg;
CLASS_DECL_BASE void * (*g_pfnca2_realloc)(void * pvoid, size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine) = &::memory_realloc_dbg;
CLASS_DECL_BASE void   (*g_pfnca2_free)(void * pvoid, int32_t iBlockType) = &::memory_free_dbg;
CLASS_DECL_BASE size_t (*g_pfnca2_msize)(void * pvoid, int32_t iBlockType) = &::_ca_msize;
#endif
*/


void * base_memory_alloc(size_t size);
void * base_memory_alloc_dbg(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
void * base_memory_realloc_dbg(void * pvoid, size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
void   base_memory_free_dbg(void * pvoid, int32_t iBlockType);
size_t base_memory_size_dbg(void * pvoid, int32_t iBlockType);


BEGIN_EXTERN_C


void * memory_alloc(size_t size)
{
   return base_memory_alloc(size);
}

void * memory_calloc(size_t size, size_t bytes)
{
   return base_memory_alloc(size * bytes);
}

void * memory_alloc_dbg(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{
   return base_memory_alloc_dbg(nSize, nBlockUse, szFileName, nLine);
}

void * memory_realloc(void * pvoid, size_t nSize)
{
   return base_memory_realloc_dbg(pvoid, nSize, 0, NULL, -1);
}

void * memory_realloc_dbg(void * pvoid, size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{
   return base_memory_realloc_dbg(pvoid, nSize, nBlockUse, szFileName, nLine);
}

void memory_free(void * pvoid)
{
   return base_memory_free_dbg(pvoid, 0);
}

void memory_free_dbg(void * pvoid, int32_t iBlockType)
{
   return base_memory_free_dbg(pvoid, iBlockType);
}

size_t memory_size(void * pvoid)
{
   return base_memory_size_dbg(pvoid, 0);
}

size_t memory_size_dbg(void * pvoid, int32_t iBlockType)
{
   return base_memory_size_dbg(pvoid, iBlockType);
}


END_EXTERN_C

#undef new


/*
mutex & get_mutex_c_heap()
{

   static mutex * s_pmutex = NULL;

   if(s_pmutex == NULL)
   {

      s_pmutex = (mutex *) malloc(sizeof(mutex));

      new (s_pmutex) mutex;

   }

   return *s_pmutex;

}


void * memory_alloc(size_t size)
{
   synch_lock ml(&get_mutex_c_heap());
#ifdef WINDOWSEX
#if ZEROED_ALLOC
   byte * p = (byte *) HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, size + 4 + 32);
#else
   byte * p = (byte *) HeapAlloc(::GetProcessHeap(), 0, size + 4 + 32);
#endif
#else
   byte * p = (byte *) malloc(size + 4 + 32);
#if ZEROED_ALLOC
   memset_dup(p, 0, size);
#endif
#endif
   p[0] = 22;
   *((size_t *) &p[1]) = size;
   return p + 4 + 16;
}

void * _ca_alloc_dbg(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{
   synch_lock ml(&get_mutex_c_heap());
   return memory_alloc(nSize);
}


void * memory_realloc_dbg(void * pvoid, size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{
   synch_lock ml(&get_mutex_c_heap());
   byte * p = (byte *) pvoid;
   if(p == NULL)
      return memory_alloc(nSize);
   p -= (4 + 16);
   if(p[0] == 22)
   {
#ifdef WINDOWSEX
#if ZEROED_ALLOC
      p = (byte *) HeapReAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, p, nSize + 4 + 32);
#else
      p = (byte *) HeapAlloc(::GetProcessHeap(), 0, p, nSize + 4 + 32);
#endif
      //p = (byte *) HeapReAlloc(::GetProcessHeap(), 0, p, nSize + 4 + 32);
#else
      p = (byte *) realloc(p, nSize + 4 + 32);
#if ZEROED_ALLOC
      if(nSize > *((size_t *) &p[1]))
      {
         memset_dup(&p[4 + 16 + *((size_t *) &p[1])], 0, nSize - *((size_t *) &p[1]));
      }
#endif
#endif

   }
   *((size_t *) &p[1]) = nSize;
   return p + 4 + 16;
}

void memory_free_dbg(void * pvoid, int32_t iBlockType)
{
   synch_lock ml(&get_mutex_c_heap());
   byte * p = (byte *) pvoid;
   if(p == NULL)
      return;
   p -= (4 + 16);
   if(p[0] == 22)
   {
#ifdef WINDOWSEX
      HeapFree(::GetProcessHeap(), 0, p);
#else
      free(p);
#endif
   }
}

size_t _ca_msize(void * pvoid, int32_t iBlockType)
{
   synch_lock ml(&get_mutex_c_heap());
   byte * p = (byte *) pvoid;
   if(p == NULL)
      return 0;
   p -= (4 + 16);
   if(p[0] == 22)
   {
//#ifdef WINDOWS
//      return HeapSize(::GetProcessHeap(), 0, p)  - (4 + 16);
//#elif defined(MACOS)
//      return malloc_size(p);
//#else
      return *((size_t *) &p[1]);
      //return malloc_usable_size(p);
//#endif
   }
   return 0;
}
*/

extern string_manager * s_pstringmanager;

extern mutex * g_pmutexSystemHeap;

extern plex_heap_alloc_array * g_pheap;

extern mutex * g_pmutexTrace;

extern mutex * g_pmutgen;

void create_id_space();

void destroy_id_space();

extern string * g_pstrLastStatus;

extern string * g_pstrLastGlsStatus;






#if defined(LINUX) || defined(MACOS) || defined(METROWIN)

extern mutex * g_pmutexThreadIdHandleLock;

extern mutex * g_pmutexThreadIdLock;

extern mutex * g_pmutexPendingThreadsLock;

extern mutex * g_pmutexTlsData;

#endif // defined(LINUX) || defined(MACOS) || defined(METROWIN)


#if defined(LINUX) || defined(MACOS)

extern mutex * g_pmutexTz;

extern tiny_http * g_ptinyhttp;

extern map < HTHREAD, HTHREAD, PendingThreadInfo, PendingThreadInfo > * g_ppendingThreads;

extern mutex * g_pmutexThreadHandleLock;

#endif // defined(LINUX) || defined(MACOS)



#if defined(LINUX)



#endif





#if defined(MACOS)

#include "base/macos/macos_window_impl.h"

extern oswindow_dataptra * g_poswindowdataptra;

#endif




class base_static_start
{
public:

   base_static_start()
   {

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

      g_pstrLastStatus = new string();

      g_pstrLastGlsStatus = new string();

      g_pmutexSystemHeap = new mutex();

      g_pmutgen = new mutex();

      g_pmutexTrace = new mutex();



#if defined(LINUX) || defined(MACOS) || defined(METROWIN)

      g_pmutexThreadIdHandleLock = new mutex;

      g_pmutexThreadIdLock = new mutex;

      g_pmutexPendingThreadsLock = new mutex;

      g_pmutexTlsData = new mutex;

      os_thread::s_pmutex = new mutex();

      os_thread::s_pptra = new comparable_raw_array < os_thread * > ();

#endif // defined(LINUX) || defined(MACOS) || defined(METROWIN)

#if defined(LINUX) || defined(MACOS)

      g_pmutexTz = new mutex();

      g_ptinyhttp = new tiny_http;

      g_ppendingThreads = new map < HTHREAD, HTHREAD, PendingThreadInfo, PendingThreadInfo >();

      g_pmutexThreadHandleLock = new mutex;


#endif // defined(LINUX) || defined(MACOS)





#if defined(LINUX)

      oswindow_data::s_pdataptra = new oswindow_dataptra;

      oswindow_data::s_pmutex = new mutex;

      osdisplay_data::s_pdataptra = new osdisplay_dataptra;

      osdisplay_data::s_pmutex = new mutex;

#endif // defined(LINUX)



#if defined(MACOS)

      g_poswindowdataptra = new oswindow_dataptra;

#endif // defined(MACOS)


//      IMPLEMENT_BASE_FIXED_ALLOC_CONSTRUCTOR(var, 1024)
  //    IMPLEMENT_BASE_FIXED_ALLOC_CONSTRUCTOR(property, 1024)


   }

   ~base_static_start()
   {


    //  IMPLEMENT_BASE_FIXED_ALLOC_DESTRUCTOR(property)
//      IMPLEMENT_BASE_FIXED_ALLOC_DESTRUCTOR(var)



#if defined(LINUX) || defined(MACOS)




      delete g_pmutexThreadHandleLock;

      g_pmutexThreadHandleLock = NULL;


      delete g_ppendingThreads;

      g_ppendingThreads = NULL;

      delete g_pmutexTz;

      g_pmutexTz = NULL;

#endif // defined(LINUX) || defined(MACOS)


#if defined(LINUX) || defined(MACOS) || defined(METROWIN)

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

#endif  // defined(LINUX) || defined(MACOS) || defined(METROWIN)



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





#if defined(MACOS)

      delete g_poswindowdataptra;

      g_poswindowdataptra = NULL;

#endif // defined(MACOS)





      delete g_pmutexTrace;

      g_pmutexTrace = NULL;

      delete g_pmutgen;

      g_pmutgen = NULL;

      delete g_pmutexSystemHeap;

      g_pmutexSystemHeap = NULL;

      delete g_pstrLastGlsStatus;

      g_pstrLastGlsStatus = NULL;

      delete g_pstrLastStatus;

      g_pstrLastStatus = NULL;

      destroy_id_space();
      
      delete s_pstringmanager;
      
      s_pstringmanager = NULL;

      delete g_pheap;



   }

} g_basestaticstart;


void create_id_space()
{

   base_system::s_pidspace = new id_space();

}

void destroy_id_space()
{

   delete base_system::s_pidspace;

   base_system::s_pidspace = NULL;

}


/*
BEGIN_EXTERN_C

   CLASS_DECL_BASE void * c_alloc(size_t size)
{
   return memory_alloc(size);
}
   CLASS_DECL_BASE void * c_alloc_dbg(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{
   return memory_alloc_dbg(nSize, nBlockUse, szFileName, nLine);
}
   CLASS_DECL_BASE void * c_realloc(void * pvoid, size_t nSize)
{
   return memory_realloc(pvoid, nSize);
}
   CLASS_DECL_BASE void * c_realloc_dbg(void * pvoid, size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{
   return memory_realloc_dbg(pvoid, nSize, nBlockUse, szFileName, nLine);
}
   CLASS_DECL_BASE void   memory_free(void * pvoid)
{
   return memory_free(pvoid);
}
   CLASS_DECL_BASE void   c_free_dbg(void * pvoid, int32_t iBlockType)
   {
      return memory_free_dbg(pvoid, iBlockType);
   }
   CLASS_DECL_BASE size_t c_msize(void * p)
{
   return memory_size(p);
}
   CLASS_DECL_BASE size_t c_msize_dbg(void * p, int32_t iBlockType)
{
   return memory_size_dbg(p, iBlockType);
}

END_EXTERN_C

*/

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

