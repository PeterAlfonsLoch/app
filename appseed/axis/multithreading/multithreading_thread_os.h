#pragma once




namespace axis
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

	CLASS_DECL_AXIS bool set_thread_priority(int32_t priority);
	CLASS_DECL_AXIS bool set_priority_class(int32_t priority);

	CLASS_DECL_AXIS int32_t thread_priority();


} // namespace axis


inline int32_t get_scheduling_priority_none()
{

      return ::axis::scheduling_priority_none;

}


inline int32_t get_scheduling_priority_normal()
{

      return ::axis::scheduling_priority_normal;

}



class CLASS_DECL_AXIS os_thread :
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

   static mutex *                         s_pmutex;
   static raw_array < os_thread * >       s_pptra;


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


CLASS_DECL_AXIS HTHREAD start_thread(uint32_t (*)(void *), void * pv, int32_t iPriority = 0);

CLASS_DECL_AXIS HTHREAD create_thread(LPSECURITY_ATTRIBUTES lpsa, uint_ptr cbStack, uint32_t (*)(void *), void * pv, uint32_t uiFlags, uint32_t * puiId);


class CLASS_DECL_AXIS thread_layer
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




CLASS_DECL_AXIS DWORD get_current_thread_id();




CLASS_DECL_AXIS thread* __begin_thread(sp(::axis::application) papp,__THREADPROC pfnThreadProc,LPVOID pParam,int32_t epriority = ::axis::scheduling_priority_normal,UINT nStackSize = 0,uint32_t dwCreateFlags = 0,LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);
/* xxx CLASS_DECL_AXIS thread* __begin_thread(sp(::coretype) pThreadClass,
int32_t nPriority = scheduling_priority_normal, UINT nStackSize = 0,
uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL); xxxx */


template < class THREAD_TYPE >
THREAD_TYPE * __begin_thread(sp(::axis::application) papp,int32_t epriority = ::axis::scheduling_priority_normal,UINT nStackSize = 0,uint32_t dwCreateFlags = 0,LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL)
{
   THREAD_TYPE * pthread = new THREAD_TYPE(papp);
   pthread->begin(epriority,nStackSize,dwCreateFlags,lpSecurityAttrs);
   return pthread;
}


CLASS_DECL_AXIS HTHREAD get_current_thread();





CLASS_DECL_AXIS bool on_init_thread();
CLASS_DECL_AXIS bool on_term_thread();


CLASS_DECL_AXIS void __init_thread();
CLASS_DECL_AXIS void __term_thread();


CLASS_DECL_AXIS bool __os_init_thread();
CLASS_DECL_AXIS bool __os_term_thread();


CLASS_DECL_AXIS bool __node_init_thread(::thread * pthread);
CLASS_DECL_AXIS bool __node_term_thread(::thread * pthread);


CLASS_DECL_AXIS void __init_threading_count();
CLASS_DECL_AXIS void __term_threading_count();


CLASS_DECL_AXIS void __inc_threading_count();
CLASS_DECL_AXIS void __dec_threading_count();


class CLASS_DECL_AXIS keep_threading_count
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



CLASS_DECL_AXIS bool __wait_threading_count(::duration dur);
CLASS_DECL_AXIS bool __wait_threading_count_except(::thread * pthread,::duration dur);


CLASS_DECL_AXIS ::thread * get_thread();
CLASS_DECL_AXIS void set_thread(::thread * pthread);


CLASS_DECL_AXIS void __node_init_multithreading();
CLASS_DECL_AXIS void __node_term_multithreading();



namespace multithreading
{


   CLASS_DECL_AXIS void init_multithreading();
   CLASS_DECL_AXIS void term_multithreading();

   CLASS_DECL_AXIS void __node_on_init_thread(thread * pthread);
   CLASS_DECL_AXIS void __node_on_term_thread(thread * pthread);

   CLASS_DECL_AXIS uint32_t __on_thread_finally(thread * pthread);

   CLASS_DECL_AXIS extern raw_array < HTHREAD > * s_phaThread;
   CLASS_DECL_AXIS extern raw_array < thread * > * s_pthreadptra;
   CLASS_DECL_AXIS extern mutex * s_pmutex;


} // namespace multithreading



CLASS_DECL_AXIS void __end_thread(sp(::axis::application) papp);

CLASS_DECL_AXIS void __term_thread(sp(::axis::application) papp);






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




CLASS_DECL_AXIS void thread_alloc_ready(bool bReady);









CLASS_DECL_AXIS mutex & user_mutex();
CLASS_DECL_AXIS mutex & message_dispatch_mutex();


