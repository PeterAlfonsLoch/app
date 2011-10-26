#pragma once

class sync_object_base;
template < typename THANDLE >
class sync_object;
class semaphore;
class mutex;
class event;
class critical_section;
class single_lock;
class multi_lock;


#include "multithreading_wait_result.h"
#include "multithreading_waitable.h"
#include "multithreading_sync_object.h"
#include "multithreading_base_sync_object.h"
#include "multithreading_event_base.h"
#include "multithreading_event_collection.h"
#include "multithreading_semaphore.h"
#include "multithreading_mutex.h"
#include "multithreading_event.h"
#include "multithreading_file_change_event.h"
#include "multithreading_socket_event.h"
#include "multithreading_critical_section.h"
#include "multithreading_single_lock.h"
#include "multithreading_synch_lock.h"
#include "multithreading_multi_lock.h"


#ifdef _AFX_ENABLE_INLINES
#define _AFXMT_INLINE inline
#include "multithreading.inl"
#undef _AFXMT_INLINE
#endif

#include "multithreading_manual_reset_event.h"

#ifdef _WINDOWS
#include <Winsvc.h>
#endif

// services
#include "multithreading_service_status.h"
#include "multithreading_thread_pool.h"
#include "multithreading_service_base.h"
#include "multithreading_plain_service.h"
