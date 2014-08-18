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
CLASS_DECL_AXIS void __post_quit_message(int32_t nExitCode);

typedef UINT(c_cdecl *__THREADPROC)(LPVOID);


CLASS_DECL_AXIS void do_events();
CLASS_DECL_AXIS void do_events(const duration & duration);


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

#include "multithreading_synch_index_ptr_array.h"
#include "multithreading_synch_index_iterator.h"
#include "multithreading_synch_ptr_array.h"

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


