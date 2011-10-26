#pragma once


#include "get_platform.h"


#define IMPLEMENT_VISTA_TOOLS
#define DRAWDIB_INCLUDE_STRETCHDIB
#pragma pointers_to_members( full_generality, virtual_inheritance )
#include "win32_system.h"
#define _ApplicationFrameworkDLL


#if defined(_WIN64) && defined(_M_X64)


#define _AMD64_

#else


#define _X86_


#endif



#ifndef _DEBUG
#define _DEBUG // ca2 is in debug - bugs come and go, always
#endif


#include "c/types.h"


#include "c/natural.h"


#define if_then(p, q)  ((!(p))||(!(q)))


#pragma pointers_to_members( full_generality, virtual_inheritance )


#include "bare_operational_system.h"        // Target version control


// incorporation of sector8J src/lib/pal/windows/thread_windows.hpp on 07/09/2011
/**
* \file		src/lib/pal/windows/thread_windows.hpp
* \brief	Platform independent threads and synchronization objects (windows version)
* \author	Thomas Nass
*/

namespace ca
{

//namespace gen { namespace pal {
	/// An enum representing thread priorities.
	enum e_thread_priority
   {
		thread_priority_lowest = THREAD_PRIORITY_LOWEST,
		thread_priority_highest = THREAD_PRIORITY_HIGHEST,
		thread_priority_below_normal = THREAD_PRIORITY_BELOW_NORMAL,
		thread_priority_normal = THREAD_PRIORITY_NORMAL,
		thread_priority_above_normal = THREAD_PRIORITY_ABOVE_NORMAL,
		thread_priority_time_critical = THREAD_PRIORITY_TIME_CRITICAL,
		thread_priority_idle = THREAD_PRIORITY_IDLE
	};

	///  \brief		global function to set thread priority for current thread
	///  \param		new priority
	inline bool set_thread_priority(int priority)
	{
		return ( ::SetThreadPriority(::GetCurrentThread(), priority) != 0 );
	}

	///  \brief		global function to get thread priority for current thread
	///  \return	priority of current thread
	inline int thread_priority()
	{ return ::GetThreadPriority(::GetCurrentThread()); }

} // namespace ca

inline ::ca::e_thread_priority get_thread_priority_normal()
{
   return ::ca::thread_priority_normal;
}