#pragma once


class CLASS_DECL_AURA os_thread :
   virtual public object
{
public:


   uint32_t (*                            m_pfn)(void *);
   LPVOID                                 m_pv;
   bool                                   m_bRun;
   HTHREAD                                m_hthread;
   string                                 m_strDebug;

#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID) || defined(SOLARIS)

   pthread_t                              m_pthread;

#endif

   static mutex *                  s_pmutex;
   static comparable_raw_array < os_thread * >::type *  s_pptra;


   os_thread(uint32_t ( * pfn)(void *), void * pv);
   virtual ~os_thread();


#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

   //static void * thread_proc(void * pparam);

#else

   static unsigned int WINAPI thread_proc(void * pparam);

#endif

   uint32_t run();

   static os_thread * get();
   static void set(os_thread * posthread);

   static bool get_run();

   static void stop_all(uint32_t millisMaxWait);

};


CLASS_DECL_AURA HTHREAD start_thread(uint32_t (*)(void *), void * pv, int32_t iPriority = 0);

CLASS_DECL_AURA HTHREAD create_thread(LPSECURITY_ATTRIBUTES lpsa, uint_ptr cbStack, uint32_t (*)(void *), void * pv, uint32_t uiFlags, uint32_t * puiId);


class CLASS_DECL_AURA thread_layer
{
public:


   int32_t              m_iSleepiness;
   int32_t              m_iResult;
   HTHREAD              m_hthread;
   UINT                 m_nId;
   bool                 m_bRun;


   thread_layer();
   virtual ~thread_layer();


   void begin();


   static uint32_t proc(void * lp);

   virtual int32_t run();
   virtual bool on_idle();

   virtual void wait_thread(uint32_t dwMillis = INFINITE);

};




CLASS_DECL_AURA DWORD get_current_thread_id();




CLASS_DECL_AURA thread* __begin_thread(sp(::aura::application) papp,__THREADPROC pfnThreadProc,LPVOID pParam,int32_t epriority = ::multithreading::priority_normal,UINT nStackSize = 0,uint32_t dwCreateFlags = 0,LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);
/* xxx CLASS_DECL_AURA thread* __begin_thread(sp(::coretype) pThreadClass,
int32_t nPriority = scheduling_priority_normal, UINT nStackSize = 0,
uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL); xxxx */

template < class T >
T * c_new(T * p)
{
   p->m_bHeap = true;
   return p;
}

#define cnew(x) c_new(new x)

template < class THREAD_TYPE >
THREAD_TYPE * __begin_thread(sp(::aura::application) papp,int32_t epriority = ::multithreading::priority_normal,UINT nStackSize = 0,uint32_t dwCreateFlags = 0,LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL)
{
   THREAD_TYPE * pthread = cnew(THREAD_TYPE(papp));
   pthread->begin(epriority,nStackSize,dwCreateFlags,lpSecurityAttrs);
   return pthread;
}


CLASS_DECL_AURA HTHREAD get_current_thread();





CLASS_DECL_AURA bool on_init_thread();
CLASS_DECL_AURA bool on_term_thread();


CLASS_DECL_AURA void __init_thread();
CLASS_DECL_AURA void __term_thread();


CLASS_DECL_AURA bool __os_init_thread();
CLASS_DECL_AURA bool __os_term_thread();


CLASS_DECL_AURA bool __node_init_thread(::thread * pthread);
CLASS_DECL_AURA bool __node_term_thread(::thread * pthread);


CLASS_DECL_AURA void __init_threading_count();
CLASS_DECL_AURA void __term_threading_count();


CLASS_DECL_AURA void __inc_threading_count();
CLASS_DECL_AURA void __dec_threading_count();


class CLASS_DECL_AURA keep_threading_count
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



CLASS_DECL_AURA bool __wait_threading_count(::duration dur);
CLASS_DECL_AURA bool __wait_threading_count_except(::thread * pthread,::duration dur);


CLASS_DECL_AURA ::thread * get_thread();
CLASS_DECL_AURA void set_thread(::thread * pthread);


CLASS_DECL_AURA void __node_init_multithreading();
CLASS_DECL_AURA void __node_term_multithreading();



namespace multithreading
{


   CLASS_DECL_AURA void init_multithreading();
   CLASS_DECL_AURA void term_multithreading();

   CLASS_DECL_AURA void __node_on_init_thread(thread * pthread);
   CLASS_DECL_AURA void __node_on_term_thread(thread * pthread);

   CLASS_DECL_AURA uint32_t __on_thread_finally(thread * pthread);

   CLASS_DECL_AURA extern comparable_array < HTHREAD > * s_phaThread;
   CLASS_DECL_AURA extern comparable_array < thread * > * s_pthreadptra;
   CLASS_DECL_AURA extern mutex * s_pmutex;


} // namespace multithreading



CLASS_DECL_AURA void __end_thread(sp(::aura::application) papp);

CLASS_DECL_AURA void __term_thread(sp(::aura::application) papp);






#ifdef WINDOWS

///  \brief		global function to wait on a waitable item for a specified time
///  \param		waitableItem item to wait for (can be event, socket, file, semaphore, ...)
///  \param		duration time period to wait for item (default: infinite)
///  \return	result of waiting action as defined in wait_result
inline wait_result wait(event_base & waitableItem,const duration & duration = duration::infinite())
{
   return waitableItem.wait(duration);
}

///  \brief		global function to wait on a waitable item for a specified time
///  \param		waitableItem item to wait for (item can be thread, event, socket, file, semaphore, ...)
///  \param		duration time period to wait for item (default: infinite)
///  \return	result of waiting action as defined in wait_result
wait_result wait(size_t numberOfItems,event_base * waitableItems[],const duration & duration = duration::infinite(),bool waitForAll = false);

#else

///  \brief		global function to wait on a waitable item for a specified time
///  \param		waitableItem item to wait for (can be event, socket, file, semaphore, ...)
///  \param		duration time period to wait for item (default: infinite)
///  \return	result of waiting action as defined in wait_result
wait_result wait(event_base & waitableItem,const duration & duration = duration::infinite());

///  \brief		global function to wait on a waitable item for a specified time
///  \param		waitableItem item to wait for (item can be thread, event, socket, file, semaphore, ...)
///  \param		duration time period to wait for item (default: infinite)
///  \return	result of waiting action as defined in wait_result
wait_result wait(size_t numberOfItems,event_base * waitableItems[],const duration& duration = duration::infinite(),bool waitForAll = false);

#endif




CLASS_DECL_AURA void thread_alloc_ready(bool bReady);









CLASS_DECL_AURA mutex & user_mutex();
CLASS_DECL_AURA mutex & message_dispatch_mutex();


