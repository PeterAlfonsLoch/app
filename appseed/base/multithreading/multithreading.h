#pragma once

class waitable;
class sync_object;
class semaphore;
class mutex;
class event;
class critical_section;
class single_lock;
class multi_lock;






// Use instead of PostQuitMessage in OLE server applications
CLASS_DECL_BASE void __post_quit_message(int32_t nExitCode);


#include "multithreading_sync_object.h"
#include "multithreading_event_base.h"
#include "multithreading_event_collection.h"
#include "multithreading_semaphore.h"
#include "multithreading_mutex.h"
#include "multithreading_event.h"
#include "multithreading_set_event_on_exit.h"
#include "multithreading_condition.h"
#include "multithreading_file_change_event.h"
#include "multithreading_socket_event.h"
#include "multithreading_critical_section.h"
#include "multithreading_single_lock.h"
#include "multithreading_retry_single_lock.h"
#include "multithreading_initial_single_lock.h"
#include "multithreading_synch_lock.h"
#include "multithreading_multi_lock.h"
#include "multithreading_retry_multi_lock.h"


#ifdef ___ENABLE_INLINES
#define _AFXMT_INLINE inline
#include "multithreading.inl"
#undef _AFXMT_INLINE
#endif

#include "multithreading_manual_reset_event.h"

#ifdef WINDOWS
#include <Winsvc.h>
#endif

#include "multithreading_service_status.h"
#include "multithreading_service_base.h"
#include "multithreading_thread_os.h"

typedef UINT(c_cdecl *__THREADPROC)(LPVOID);


CLASS_DECL_BASE thread* __begin_thread(sp(::base::application) papp, __THREADPROC pfnThreadProc, LPVOID pParam, int32_t epriority = ::core::scheduling_priority_normal, UINT nStackSize = 0, uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);
/* xxx CLASS_DECL_BASE thread* __begin_thread(sp(::coretype) pThreadClass,
int32_t nPriority = scheduling_priority_normal, UINT nStackSize = 0,
uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL); xxxx */


template < class THREAD_TYPE >
THREAD_TYPE * __begin_thread(sp(::base::application) papp, int32_t epriority = ::core::scheduling_priority_normal, UINT nStackSize = 0, uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL)
{
   THREAD_TYPE * pthread = new THREAD_TYPE(papp);
   pthread->begin(epriority, nStackSize, dwCreateFlags, lpSecurityAttrs);
   return pthread;
}


CLASS_DECL_BASE HTHREAD get_current_thread();





CLASS_DECL_BASE void on_init_thread();
CLASS_DECL_BASE void on_term_thread();


CLASS_DECL_BASE void __node_init_thread();
CLASS_DECL_BASE void __node_term_thread();


CLASS_DECL_BASE void __init_threading_count();
CLASS_DECL_BASE void __term_threading_count();


CLASS_DECL_BASE void __inc_threading_count();
CLASS_DECL_BASE void __dec_threading_count();


CLASS_DECL_BASE bool __wait_threading_count(::duration dur);


CLASS_DECL_BASE ::thread * get_thread();
CLASS_DECL_BASE void set_thread(::thread * pthread);





namespace multithreading
{


   CLASS_DECL_BASE void init_multithreading();
   CLASS_DECL_BASE void term_multithreading();

   CLASS_DECL_BASE void __node_on_init_thread(HTHREAD hthread,thread * pthread);
   CLASS_DECL_BASE void __node_on_term_thread(HTHREAD hthread,thread * pthread, int nExitCode, bool bDelete = true);


   CLASS_DECL_BASE extern comparable_array < HTHREAD > * s_phaThread;
   CLASS_DECL_BASE extern comparable_array < thread * > * s_pthreadptra;
   CLASS_DECL_BASE extern mutex * s_pmutex;


} // namespace multithreading



CLASS_DECL_BASE void __init_thread();

CLASS_DECL_BASE void __end_thread(sp(::base::application) papp,UINT nExitCode,bool bDelete = TRUE);

CLASS_DECL_BASE void __term_thread(sp(::base::application) papp,HINSTANCE hInstTerm = NULL);






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




