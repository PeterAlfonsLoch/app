#pragma once


/**
* \file		src/lib/pal/linux/thread_linux.hpp
* \brief	Platform independent threads and synchronization objects (linux version)
* \author	Thomas Nass
*/

namespace ca
{


//namespace gen { namespace pal {


	/// An enum representing thread priorities.
	enum e_thread_priority {
		thread_priority_idle 	= 1,
		thread_priority_lowest 	= 48,
		thread_priority_below_normal,
		thread_priority_normal,
		thread_priority_above_normal,
		thread_priority_highest,
		thread_priority_time_critical = 99
	};

	///  \brief		global function to set thread priority for current thread
	///  \param		new priority
	inline bool set_thread_priority(int32_t priority)
	{

#ifdef WINDOWS

      return ( ::SetThreadPriority(::GetCurrentThread(), priority) != 0 );

#else

		return setpriority(PRIO_PROCESS, getpid(), priority) == 0;

#endif

	}

	///  \brief		global function to get thread priority for current thread
	///  \return	priority of current thread
	inline int32_t thread_priority()
	{

#ifdef WINDOWS

      return ::GetThreadPriority(::GetCurrentThread());

#else

	   return getpriority(PRIO_PROCESS, getpid());

#endif

   }


} // namespace ca


inline ::ca::e_thread_priority get_thread_priority_normal()
{

      return ::ca::thread_priority_normal;

}



class CLASS_DECL_c os_thread
{
public:


   DWORD (WINAPI * m_pfn)(LPVOID);
   LPVOID           m_pv;

#if defined(LINUX) || defined(MACOS)
   simple_event *    m_peventThread;
#endif


   os_thread(DWORD (WINAPI * lpStartAddr)(LPVOID), LPVOID);



};


#ifdef WINDOWS

CLASS_DECL_c HANDLE start_thread(LPTHREAD_START_ROUTINE, LPVOID pv, int32_t iPriority = 0);

CLASS_DECL_c HANDLE create_thread(LPSECURITY_ATTRIBUTES lpsa, DWORD cbStack, LPTHREAD_START_ROUTINE, LPVOID pv, DWORD f, LPDWORD lpdwId);

#else

CLASS_DECL_c simple_event * start_thread(LPTHREAD_START_ROUTINE, LPVOID pv, int32_t iPriority = 0);

CLASS_DECL_c simple_event * create_thread(LPSECURITY_ATTRIBUTES lpsa, DWORD cbStack, LPTHREAD_START_ROUTINE, LPVOID pv, DWORD f, LPDWORD lpdwId);

#endif



class CLASS_DECL_c thread_layer
{
public:


   int32_t               m_iSleepiness;
   int32_t               m_iResult;

#ifdef WINDOWS
   HANDLE            m_hthread;
#else
   simple_event *    m_peventThread;
#endif
   UINT              m_nId;


   thread_layer();
   virtual ~thread_layer();


   void begin();


   static DWORD WINAPI proc(LPVOID lp);

   virtual int32_t run();
   virtual bool on_idle();

   virtual void wait_thread(DWORD dwMillis = INFINITE);

};


