#pragma once


#ifdef WINDOWS

#define HTHREAD HANDLE

#else

#define HTHREAD simple_event *

#endif


/**
* \file		src/lib/pal/linux/thread_linux.hpp
*/

namespace ca
{


//namespace ca { namespace pal {


	/// An enum representing thread priorities.
	enum e_thread_priority
   {

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


   uint32_t (*       m_pfn)(void *);
   LPVOID            m_pv;

#if defined(LINUX) || defined(MACOS)

   HTHREAD           m_hthread;

#endif


   os_thread(uint32_t (* pfn)(void *), void * pv);


};




CLASS_DECL_c HTHREAD start_thread(uint32_t (*)(void *), void * pv, int32_t iPriority = 0);

CLASS_DECL_c HTHREAD create_thread(LPSECURITY_ATTRIBUTES lpsa, uint_ptr cbStack, uint32_t (*)(void *), void * pv, uint32_t uiFlags, uint32_t * puiId);


class CLASS_DECL_c thread_layer
{
public:


   int32_t              m_iSleepiness;
   int32_t              m_iResult;
   HTHREAD              m_hthread;
   UINT                 m_nId;


   thread_layer();
   virtual ~thread_layer();


   void begin();


   static uint32_t proc(void * lp);

   virtual int32_t run();
   virtual bool on_idle();

   virtual void wait_thread(uint32_t dwMillis = INFINITE);

};


