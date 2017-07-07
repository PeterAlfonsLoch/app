#pragma once



class single_lock;





#ifdef WINDOWS

typedef uint32_t IDTHREAD;

#else
#define QS_ALLEVENTS 0xffff

void __clear_mq();

typedef HTHREAD IDTHREAD;

template <  >
inline bool EqualElements<IDTHREAD>(IDTHREAD r1, IDTHREAD r2)
{
   return id_thread_equals(r1, r2) != 0;
}
template <  >
inline UINT HashKey(IDTHREAD key)
{
   return 0;
}

#endif



#ifdef APPLEOS
#include <semaphore.h>
#endif


#if defined(ANDROID)


#define MUTEX_COND_TIMED
#undef MUTEX_NAMED_POSIX // as of 2016-11-26
// not implemented (err=38) on android-19 (POSIX semaphore)
#define MUTEX_NAMED_FD
#undef MUTEX_NAMED_VSEM

#elif defined(APPLEOS)

#define MUTEX_COND_TIMED
#undef MUTEX_NAMED_POSIX
#define MUTEX_NAMED_FD // File Descriptor "Semaphore"
#undef MUTEX_NAMED_VSEM

#elif defined(LINUX)

#define MUTEX_COND_TIMED
#undef MUTEX_NAMED_POSIX
#undef MUTEX_NAMED_FD
#define MUTEX_NAMED_FD // File Descriptor "Semaphore"
//#define MUTEX_NAMED_VSEM // System V Semaphore
#undef MUTEX_NAMED_VSEM

#endif



class sync_object;
class semaphore;
class mutex;
class event;
class critical_section;
class manual_reset_event;
class single_lock;
class multi_lock;





typedef UINT(c_cdecl *__THREADPROC)(LPVOID);


CLASS_DECL_AURA void do_events();
CLASS_DECL_AURA void do_events(const duration & duration);



namespace multithreading
{


   enum e_priority
   {

      priority_none = -1,
      priority_idle = 1,
      priority_lowest = 48,
      priority_below_normal,
      priority_normal,
      priority_above_normal,
      priority_highest,
      priority_time_critical = 99

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







namespace user
{


   class frame_array;


} // namespace user




class pred_holder_base :
   virtual public object
{
public:

   sp(object) m_pholdref;

   pred_holder_base(::aura::application * papp, sp(object) pholdref = NULL) :
      object(papp),
      m_pholdref(pholdref)
   {

   }

   virtual void run() {}

};

template < typename PRED >
class pred_holder :
   virtual public pred_holder_base
{
public:

   PRED m_pred;

   pred_holder(::aura::application * papp, PRED pred) :
      object(papp),
      pred_holder_base(papp),
      m_pred(pred)
   {

   }

   pred_holder(::aura::application * papp, sp(object) pholdref, PRED pred) :
      object(papp),
      pred_holder_base(papp, pholdref),
      m_pred(pred)
   {

   }

   virtual void run() { m_pred(); }

};
//class replace_thread;

class user_interaction_ptr_array;

class thread_startup;

namespace primitive
{ 
   
   class command; 

} // namespace primitive


namespace exception
{

   
   class exception;
   class base;


} // namespace exception



CLASS_DECL_AURA thread* __begin_thread(::aura::application * papp, __THREADPROC pfnThreadProc, LPVOID pParam, int32_t epriority = ::multithreading::priority_normal, UINT nStackSize = 0, uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL, IDTHREAD * puiId = NULL);