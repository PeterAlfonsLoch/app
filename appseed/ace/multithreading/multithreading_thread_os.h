#pragma once


//struct CLASS_DECL_ACE hthread :
//   virtual public object
//{
//public:
//
//
//   uint32_t (*                            m_pfn)(void *);
//   LPVOID                                 m_pv;
//   bool                                   m_bRun;
//   //HTHREAD                              m_hthread;
//   string                                 m_strDebug;
//   int32_t                                m_iSleepiness;
//   int32_t                                m_iResult;
//   //HTHREAD                              m_hthread;
//   UINT                                   m_nId;
//   //bool                                 m_bRun;
//   event *                                m_pevent;
//   ::thread *                             m_pthread;
//
//#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID) || defined(SOLARIS)
//
//   void *                                 m_pthread;
//
//#endif
//
//   static mutex *                  s_pmutex;
//   static ref_array <  hthread > *  s_pptra;
//
//
//   hthread(uint32_t ( * pfn)(void *) = NULL, void * pv = NULL);
//   virtual ~hthread();
//
//
//#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)
//
//   static void * thread_proc(void * pparam);
//
//#else
//
//   static DWORD WINAPI thread_proc(void * pparam);
//
//#endif
//
//   //uint32_t run();
//
//
//   virtual bool begin(LPSECURITY_ATTRIBUTES lpsa = NULL,uint32_t cbStack = 0,uint32_t uiFlags = 0,uint32_t * lpuiId = NULL,uint32_t(* pfn)(void *) = NULL,void * pv = NULL);
//
//
//   static uint32_t proc(void * lp);
//
//   virtual int32_t run();
//   virtual bool on_idle();
//
//   virtual void wait_thread(uint32_t dwMillis = INFINITE);
//
//   static HTHREAD get();
//   static void set(HTHREAD hthread);
//   static bool get_run();
//   static void stop_all(uint32_t millisMaxWait);
//
//
//};


#ifdef WINDOWS

typedef uint32_t IDTHREAD;

inline int id_thread_equals(IDTHREAD a, IDTHREAD b) {return a==b;}

#else

#ifdef LINUX
typedef HTHREAD IDTHREAD;
#else
typedef pthread_t IDTHREAD;
#endif // LINUX

inline int id_thread_equals(IDTHREAD a, IDTHREAD b) {return pthread_equal(a, b);}


#endif

CLASS_DECL_ACE HTHREAD start_thread(uint32_t (*)(void *), void * pv, int32_t iPriority = 0);

CLASS_DECL_ACE HTHREAD create_thread(LPSECURITY_ATTRIBUTES lpsa, uint_ptr cbStack, uint32_t (*)(void *), void * pv, uint32_t uiFlags, IDTHREAD * puiId);


//class CLASS_DECL_ACE thread_layer
//{
//public:
//
//
//   int32_t              m_iSleepiness;
//   int32_t              m_iResult;
//   HTHREAD              m_hthread;
//   UINT                 m_nId;
//   bool                 m_bRun;
//
//
//   thread_layer();
//   virtual ~thread_layer();
//
//
//   void begin();
//
//
//   static uint32_t proc(void * lp);
//
//   virtual int32_t run();
//   virtual bool on_idle();
//
//   virtual void wait_thread(uint32_t dwMillis = INFINITE);
//
//};
//
//


CLASS_DECL_ACE IDTHREAD get_current_thread_id();




CLASS_DECL_ACE thread* __begin_thread(::ace::application * papp,__THREADPROC pfnThreadProc,LPVOID pParam,int32_t epriority = ::multithreading::priority_normal,UINT nStackSize = 0,uint32_t dwCreateFlags = 0,LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);
/* xxx CLASS_DECL_ACE thread* __begin_thread(sp(::coretype) pThreadClass,
int32_t nPriority = scheduling_priority_normal, UINT nStackSize = 0,
uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL); xxxx */

template < class T >
T * c_new(T * p)
{
   p->m_ulFlags |= (uint64_t) ::object::flag_heap_alloc;
   return p;
}

#define cnew(x) c_new(new x)

template < class THREAD_TYPE >
THREAD_TYPE * __begin_thread(::ace::application * papp,int32_t epriority = ::multithreading::priority_normal,UINT nStackSize = 0,uint32_t dwCreateFlags = 0,LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL)
{
   THREAD_TYPE * pthread = cnew(THREAD_TYPE(papp));
   pthread->begin(epriority,nStackSize,dwCreateFlags,lpSecurityAttrs);
   return pthread;
}


CLASS_DECL_ACE HTHREAD get_current_thread();





CLASS_DECL_ACE bool on_init_thread();
CLASS_DECL_ACE bool on_term_thread();


CLASS_DECL_ACE void __init_thread();
CLASS_DECL_ACE void __term_thread();


CLASS_DECL_ACE bool __os_init_thread();
CLASS_DECL_ACE bool __os_term_thread();


CLASS_DECL_ACE bool __node_init_thread(::thread * pthread);
CLASS_DECL_ACE bool __node_term_thread(::thread * pthread);


CLASS_DECL_ACE void __init_threading_count();
CLASS_DECL_ACE void __term_threading_count();


CLASS_DECL_ACE void __inc_threading_count();
CLASS_DECL_ACE void __dec_threading_count();


class CLASS_DECL_ACE keep_threading_count
{
public:


   keep_threading_count()
   {

      __inc_threading_count();

   }


   ~keep_threading_count()
   {

      __dec_threading_count();

   }


};



CLASS_DECL_ACE bool __wait_threading_count(::duration dur);
CLASS_DECL_ACE bool __wait_threading_count_except(::thread * pthread,::duration dur);


CLASS_DECL_ACE ::thread * get_thread();
CLASS_DECL_ACE void set_thread(::thread * pthread);


CLASS_DECL_ACE void __node_init_multithreading();
CLASS_DECL_ACE void __node_term_multithreading();



namespace multithreading
{


   CLASS_DECL_ACE void init_multithreading();
   CLASS_DECL_ACE void term_multithreading();

   CLASS_DECL_ACE void __node_on_init_thread(thread * pthread);
   CLASS_DECL_ACE void __node_on_term_thread(thread * pthread);

   CLASS_DECL_ACE uint32_t __on_thread_finally(thread * pthread);

   CLASS_DECL_ACE extern comparable_eq_array <IDTHREAD> * s_piaThread;
   CLASS_DECL_ACE extern ref_array < thread > * s_pthreadptra;
   CLASS_DECL_ACE extern mutex * s_pmutex;


} // namespace multithreading



CLASS_DECL_ACE void __end_thread(::ace::application * papp);

CLASS_DECL_ACE void __term_thread(::ace::application * papp);






#ifdef WINDOWS

///  \brief		global function to wait on a object item for a specified time
///  \param		waitableItem item to wait for (can be event, socket, file, semaphore, ...)
///  \param		duration time period to wait for item (default: infinite)
///  \return	result of waiting action as defined in wait_result
inline wait_result wait(event_base & waitableItem,const duration & duration = duration::infinite())
{
   return waitableItem.wait(duration);
}

///  \brief		global function to wait on a object item for a specified time
///  \param		waitableItem item to wait for (item can be thread, event, socket, file, semaphore, ...)
///  \param		duration time period to wait for item (default: infinite)
///  \return	result of waiting action as defined in wait_result
wait_result wait(size_t numberOfItems,event_base * waitableItems[],const duration & duration = duration::infinite(),bool waitForAll = false);

#else

///  \brief		global function to wait on a object item for a specified time
///  \param		waitableItem item to wait for (can be event, socket, file, semaphore, ...)
///  \param		duration time period to wait for item (default: infinite)
///  \return	result of waiting action as defined in wait_result
wait_result wait(event_base & waitableItem,const duration & duration = duration::infinite());

///  \brief		global function to wait on a object item for a specified time
///  \param		waitableItem item to wait for (item can be thread, event, socket, file, semaphore, ...)
///  \param		duration time period to wait for item (default: infinite)
///  \return	result of waiting action as defined in wait_result
wait_result wait(size_t numberOfItems,event_base * waitableItems[],const duration& duration = duration::infinite(),bool waitForAll = false);

#endif




CLASS_DECL_ACE void thread_alloc_ready(bool bReady);









//CLASS_DECL_ACE mutex & user_mutex();
CLASS_DECL_ACE mutex & message_dispatch_mutex();


