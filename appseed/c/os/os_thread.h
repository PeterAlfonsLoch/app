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
	enum thread_priority {
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
	inline bool set_thread_priority(int priority)
	{

		return setpriority(PRIO_PROCESS, getpid(), priority) == 0;

	}

	///  \brief		global function to get thread priority for current thread
	///  \return	priority of current thread
	inline int thread_priority()
	{

	   return getpriority(PRIO_PROCESS, getpid());

   }

} // namespace ca

inline enum ::ca::thread_priority get_thread_priority_normal()
{

      return ::ca::thread_priority_normal;

}



class CLASS_DECL_c os_thread
{
public:


   DWORD (WINAPI * m_pfn)(LPVOID);
   LPVOID           m_pv;


   os_thread(DWORD (WINAPI * lpStartAddr)(LPVOID), LPVOID);



};


CLASS_DECL_c HANDLE start_thread(DWORD (WINAPI * pfn)(LPVOID), LPVOID pv, int iPriority = 0);


CLASS_DECL_c HANDLE create_thread(LPSECURITY_ATTRIBUTES lpsa, DWORD cbStack, DWORD (WINAPI * pfn)(LPVOID), LPVOID pv, DWORD f, LPDWORD lpdwId);



class CLASS_DECL_c thread_layer
{
public:


   int m_iSleepiness;
   int m_iResult;


   thread_layer();
   virtual ~thread_layer();


   void begin();


   static DWORD WINAPI proc(LPVOID lp);

   virtual int run();
   virtual bool on_idle();

};


