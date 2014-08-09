#pragma once




namespace base
{


	enum e_scheduling_priority
   {

      scheduling_priority_none    = -1,
		scheduling_priority_idle 	= 1,
		scheduling_priority_lowest 	= 48,
		scheduling_priority_below_normal,
		scheduling_priority_normal,
		scheduling_priority_above_normal,
		scheduling_priority_highest,
		scheduling_priority_time_critical = 99

	};

	CLASS_DECL_BASE bool set_thread_priority(int32_t priority);
	CLASS_DECL_BASE bool set_priority_class(int32_t priority);

	CLASS_DECL_BASE int32_t thread_priority();


} // namespace base


inline int32_t get_scheduling_priority_none()
{

      return ::base::scheduling_priority_none;

}


inline int32_t get_scheduling_priority_normal()
{

      return ::base::scheduling_priority_normal;

}



class CLASS_DECL_BASE os_thread :
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


CLASS_DECL_BASE HTHREAD start_thread(uint32_t (*)(void *), void * pv, int32_t iPriority = 0);

CLASS_DECL_BASE HTHREAD create_thread(LPSECURITY_ATTRIBUTES lpsa, uint_ptr cbStack, uint32_t (*)(void *), void * pv, uint32_t uiFlags, uint32_t * puiId);


class CLASS_DECL_BASE thread_layer
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




CLASS_DECL_BASE DWORD get_current_thread_id();




CLASS_DECL_BASE thread* __begin_thread(sp(::base::application) papp,__THREADPROC pfnThreadProc,LPVOID pParam,int32_t epriority = ::base::scheduling_priority_normal,UINT nStackSize = 0,uint32_t dwCreateFlags = 0,LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);
/* xxx CLASS_DECL_BASE thread* __begin_thread(sp(::coretype) pThreadClass,
int32_t nPriority = scheduling_priority_normal, UINT nStackSize = 0,
uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL); xxxx */


template < class THREAD_TYPE >
THREAD_TYPE * __begin_thread(sp(::base::application) papp,int32_t epriority = ::base::scheduling_priority_normal,UINT nStackSize = 0,uint32_t dwCreateFlags = 0,LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL)
{
   THREAD_TYPE * pthread = new THREAD_TYPE(papp);
   pthread->begin(epriority,nStackSize,dwCreateFlags,lpSecurityAttrs);
   return pthread;
}


CLASS_DECL_BASE HTHREAD get_current_thread();





CLASS_DECL_BASE bool on_init_thread();
CLASS_DECL_BASE bool on_term_thread();


CLASS_DECL_BASE void __init_thread();
CLASS_DECL_BASE void __term_thread();


CLASS_DECL_BASE bool __os_init_thread();
CLASS_DECL_BASE bool __os_term_thread();


CLASS_DECL_BASE bool __node_init_thread(::thread * pthread);
CLASS_DECL_BASE bool __node_term_thread(::thread * pthread);


CLASS_DECL_BASE void __init_threading_count();
CLASS_DECL_BASE void __term_threading_count();


CLASS_DECL_BASE void __inc_threading_count();
CLASS_DECL_BASE void __dec_threading_count();


class CLASS_DECL_BASE keep_threading_count
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



CLASS_DECL_BASE bool __wait_threading_count(::duration dur);
CLASS_DECL_BASE bool __wait_threading_count_except(::thread * pthread,::duration dur);


CLASS_DECL_BASE ::thread * get_thread();
CLASS_DECL_BASE void set_thread(::thread * pthread);


CLASS_DECL_BASE void __node_init_multithreading();
CLASS_DECL_BASE void __node_term_multithreading();



namespace multithreading
{


   CLASS_DECL_BASE void init_multithreading();
   CLASS_DECL_BASE void term_multithreading();

   CLASS_DECL_BASE void __node_on_init_thread(thread * pthread);
   CLASS_DECL_BASE void __node_on_term_thread(thread * pthread);

   CLASS_DECL_BASE uint32_t __on_thread_finally(thread * pthread);

   CLASS_DECL_BASE extern comparable_array < HTHREAD > * s_phaThread;
   CLASS_DECL_BASE extern comparable_array < thread * > * s_pthreadptra;
   CLASS_DECL_BASE extern mutex * s_pmutex;


} // namespace multithreading



CLASS_DECL_BASE void __end_thread(sp(::base::application) papp);

CLASS_DECL_BASE void __term_thread(sp(::base::application) papp);






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




CLASS_DECL_BASE void thread_alloc_ready(bool bReady);









CLASS_DECL_BASE mutex & user_mutex();
CLASS_DECL_BASE mutex & message_dispatch_mutex();


