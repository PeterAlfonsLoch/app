//
//  base_static_start.cpp
//  aura
//
//
//

#include "framework.h"

namespace str
{


   namespace international
   {
      extern ::map < ::id,const ::id &,::id,const ::id & > * g_pmapRTL;
   } // namespace international

} // namespace str

extern string_map < INT_PTR,INT_PTR > * g_pmapLibrary;

extern plex_heap_alloc_array * g_pheap;

extern string_manager * s_pstringmanager;

extern mutex * g_pmutexSystemHeap;

extern plex_heap_alloc_array * g_pheap;

//extern mutex * g_pmutexTrace;

extern mutex * g_pmutgen;

void create_id_space();

void destroy_id_space();

extern mutex * g_pmutexFactory;

//extern string * g_pstrLastStatus;

//extern string * g_pstrLastGlsStatus;

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

#include "aura/os/macos/macos_window_impl.h"

extern oswindow_dataptra * g_poswindowdataptra;

#elif defined(APPLE_IOS)

#include "aura/os/ios/ios_window_impl.h"

extern oswindow_dataptra * g_poswindowdataptra;

#endif

#ifdef APPLEOS

extern mutex * g_pmutexCvt;

#endif

#undef new


namespace aura
{
   
   
   namespace static_start
   {

      
      CLASS_DECL_AURA void init()
      {
   
         xxdebug_box("aura.dll base_static_start (0)", "box", MB_OK);
         
   
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
         
#ifdef APPLEOS
         
         g_pmutexCvt = new mutex(NULL);
         
#endif

         //g_pstrLastStatus = new string();
   
         //g_pstrLastGlsStatus = new string();
   
         g_pmutexSystemHeap = new mutex();
   
         g_pmutgen = new mutex();
   
         //g_pmutexTrace = new mutex();
   
   
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
   
         // IMPLEMENT_AXIS_FIXED_ALLOC_CONSTRUCTOR(var, 1024)
         // IMPLEMENT_AXIS_FIXED_ALLOC_CONSTRUCTOR(property, 1024)

         ::str::international::g_pmapRTL = new ::map < ::id,const ::id &,::id,const ::id & >();

         g_pmapLibrary = new string_map < INT_PTR,INT_PTR >();

         g_pmutexFactory = new mutex;
   
      }
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      

      
      CLASS_DECL_AURA void term()
      {

         delete g_pmutexFactory;

         g_pmutexFactory = NULL;

         delete g_pmapLibrary;

         g_pmapLibrary = NULL;
   
         delete ::str::international::g_pmapRTL;

         ::str::international::g_pmapRTL = NULL;
   
         // IMPLEMENT_AXIS_FIXED_ALLOC_DESTRUCTOR(property)
         // IMPLEMENT_AXIS_FIXED_ALLOC_DESTRUCTOR(var)

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
   
         //delete g_pmutexTrace;
   
         //g_pmutexTrace = NULL;
   
         delete g_pmutgen;
   
         g_pmutgen = NULL;
   
         delete g_pmutexSystemHeap;
   
         g_pmutexSystemHeap = NULL;
   
         // delete g_pstrLastGlsStatus;
   
         // g_pstrLastGlsStatus = NULL;
   
         // delete g_pstrLastStatus;
   
         // g_pstrLastStatus = NULL;
         
#ifdef APPLEOS
         
         delete g_pmutexCvt;
         
         g_pmutexCvt = NULL;
         
#endif
   
         destroy_id_space();
   
         delete s_pstringmanager;
   
         s_pstringmanager = NULL;
   
         delete g_pheap;
   
         
      }


   } // namespace static_start

   
} // namespace aura





