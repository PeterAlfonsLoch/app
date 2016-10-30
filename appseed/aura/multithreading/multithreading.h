#pragma once

class sync_object;
class semaphore;
class mutex;
class event;
class critical_section;
class single_lock;
class multi_lock;





// Use instead of PostQuitMessage in OLE server applications
CLASS_DECL_AURA void __post_quit_message(int32_t nExitCode);

typedef UINT(c_cdecl *__THREADPROC)(LPVOID);


CLASS_DECL_AURA void do_events();
CLASS_DECL_AURA void do_events(const duration & duration);



namespace multithreading
{


   enum e_priority
   {

      priority_none              = -1,
      priority_idle 	            = 1,
      priority_lowest 	         = 48,
      priority_below_normal,
      priority_normal,
      priority_above_normal,
      priority_highest,
      priority_time_critical     = 99

   };

   CLASS_DECL_AURA bool set_priority(int32_t priority);

   CLASS_DECL_AURA int32_t riority();


   inline int32_t get_priority_none()
   {

      return priority_none;

   }


   inline int32_t get_priority_normal()
   {

      return priority_normal;

   }


} // namespace multithreading





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


#include "service/service_thread_pool.h"
#include "service/service_plain_service.h"


//
//
//namespace detail
//{
//
//   // quick-and-dirty optional-like brick type
//   template <typename T>
//   struct value
//   {
//   public:
//   
//      value() = default;
//         
//      value(value&&) = delete;
//      value & operator=(value&&) = delete;
//         
//      ~value()
//      {
//         if(m_bInitialized)
//            ptr()->~T();
//         
//      }
//         
//      template <typename... Args>
//      void initialize(Args&&... args)
//      {
//         
//         ::new(ptr()) T(move<Args>(args)...);
//         
//         m_bInitialized = true;
//      
//      }
//         
//      explicit operator bool() const { return m_bInitialized; }
//         
//      T& operator*() { return *ptr(); }
//      T const& operator*() const { return ptr(); }
//      T* operator->() { return *ptr(); }
//      T const* operator->() const { return ptr(); }
//         
//      T* ptr() { return static_cast<T*>(static_cast<void*>(&m_t)); }
//      T const* ptr() const { return static_cast<T*>(static_cast<void*>(&m_t)); }
//         
//      bool m_bInitialized = false;
//      
//      T m_t;
//      
//   };
//      
//      
//   template <typename T>
//   struct state
//   {
//   public:
//      
//      manual_reset_event   m_evReady;
//      value < T >          m_value;
//      ::exception::base *  m_pexception;
//
//      
//      void wait()
//      {
//      
//         m_evReady.wait();
//         
//      }
//         
//      T & get()
//      {
//        
//         if(m_value) return *m_value;
//         
//         if(m_pexception) throw m_pexception;
//      
//         throw ::simple_exception(::get_thread_app(), "WTF");
//         
//      }
//         
//      template <typename U>
//      void set_value(U&& value)
//      {
//         
//         m_value.initialize(::move(value));
//         
//         
//         
//      }
//      
//      void set_exception(exception::base * pe)
//      {
//      
//         m_pexception = pe;
//         
//         m_evReady.SetEvent();
//         
//      }
//      
//   };
//   
//} // namespace detail
//
//template <typename T> class hold;
//   
//template <typename T>
//struct fill
//{
//public:
//   
//   fill() noexcept = default;
//   fill(fill&&) noexcept = default;
//   fill(fill const& other) = delete;
//      
//   ~fill() = default;
//      
//   fill& operator=(fill&& other) noexcept = default;
//   fill& operator=(fill const& other) = delete;
//      
//   T get()
//   {
//   
//      m_pstate->wait();
//      
//      return ::move(m_pstate->get());
//
//   }
//      
//   bool valid() const noexcept
//   {
//    
//      return m_pstate != NULL;
//      
//   }
//      
//   
//   ::detail::state < T > * m_pstate = NULL;
//      
// };
//   
//   
// template <typename T>
// struct hold
//{
//public:
//   
//   ::detail::state < T >  * m_pstate;
//   
//
//   
//   hold()
//      : m_pstate(NULL)
//   {
//   
//   }
//   
//   hold(hold&& other) noexcept = default;
//   hold(hold const& other) = delete;
//      
//   ~hold() = default;
//      
//   hold& operator=(hold&& other) noexcept = default;
//   hold& operator=(hold const& rhs) = delete;
//      
//   fill < T > filling()
//   {
//   
//      return m_pstate;
//   }
//      
//   void set_value(T const& value)
//   {
//      m_pstate->set_value(value);
//   }
//   
//   void set_value(T&& value)
//   {
//      
//      m_pstate->set_value(::move(value));
//      
//   }
//      
//   void set_exception(::exception::base * pe)
//   {
//      
//      m_pstate->set_exception(pe);
//   
//   }
//
//};
//   






