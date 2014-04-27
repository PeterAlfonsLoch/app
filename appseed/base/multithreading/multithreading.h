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


#include "multithreading_data.h"
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

// services
#include "multithreading_service_status.h"
#include "multithreading_service_base.h"
//#include "multithreading_plain_service.h"
//#include "multithreading_thread_pool.h"


#include "multithreading_thread_os.h"

typedef UINT(c_cdecl *__THREADPROC)(LPVOID);


CLASS_DECL_BASE thread* __begin_thread(sp(base_application) papp, __THREADPROC pfnThreadProc, LPVOID pParam, int32_t epriority = ::core::scheduling_priority_normal, UINT nStackSize = 0, uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);
/* xxx CLASS_DECL_BASE thread* __begin_thread(sp(::coretype) pThreadClass,
int32_t nPriority = scheduling_priority_normal, UINT nStackSize = 0,
uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL); xxxx */


template < class THREAD_TYPE >
THREAD_TYPE * __begin_thread(sp(base_application) papp, int32_t epriority = ::core::scheduling_priority_normal, UINT nStackSize = 0, uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL)
{
   THREAD_TYPE * pthread = new THREAD_TYPE(papp);
   pthread->begin(epriority, nStackSize, dwCreateFlags, lpSecurityAttrs);
   return pthread;
}


CLASS_DECL_BASE HTHREAD get_current_thread();








