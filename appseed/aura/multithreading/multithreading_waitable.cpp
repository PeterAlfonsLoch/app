/**
* \brief	Platform independent waitables
* \author	Thomas Hoefer
*/

#include "framework.h"


//object::object()
//{
//
//   m_pmutex = NULL;
//
//}
//
//object::object(const object & objectSrc)
//{
//
//   UNREFERENCED_PARAMETER(objectSrc);
//
//   m_pmutex = NULL;
//
//}
//
//
/////  \brief		destructor
//object::~object()
//{
//
//   if(m_pmutex != NULL)
//   {
//
//      delete m_pmutex;
//
//      m_pmutex = NULL;
//
//   }
//
//}
//
/////  \brief		abstract function to initialize a waiting action without a timeout
//void object::wait()
//{
//
//   wait(duration::infinite());
//
//}
//
//	///  \brief		abstract function to initialize a waiting action with a timeout
//	///  \param		duration time period to wait for item
//	///  \return	waiting action result as wait_result
//wait_result object::wait(const duration & duration )
//{
//
//
//   if(m_pmutex == NULL)
//   {
//
//      ((object *)this)->m_pmutex = new mutex();
//
//   }
//
//   try
//   {
//      return m_pmutex->wait(duration);
//   }
//   catch(...)
//   {
//   }
//
//   return wait_result(wait_result::Failure);
//
//}
//
//
//
//
//// forward declaration
////class event_base;
//
///// This class represents a virtual interface for a callback method for WaitableItems in a
///// event_collection.
//
//waitable_callback::~waitable_callback()
//{
//}
//
//	/// called on signalization of a event_base
//	/// \param signaling event_base
////	virtual void callback(const event_base& waitItem) = 0;
////};
//
//
/////  \brief		pauses object for specified time
/////  \param		duration sleeping time of object
///*CLASS_DECL_AURA void sleep(const duration & duration)
//{
//   Sleep((uint32_t)duration.total_milliseconds());
//}*/
//
//CLASS_DECL_AURA void sleep(const duration & duration)
//{
//   ::Sleep(static_cast<uint32_t>(duration.total_milliseconds()));
//}
//
//
//
//
//
//void * object::get_os_data() const
//{
//
//   if(m_pmutex == NULL)
//   {
//
//      ((object *)this)->m_pmutex = new mutex();
//
//   }
//
//   return m_pmutex;
//
//}
//
//void object::lock()
//{
//
//   if(!lock(duration::infinite()))
//      if(!lock(duration::infinite()))
//         throw "failure to lock object";
//
//}
//
//bool object::lock(const duration & duration)
//{
//
//   if(m_pmutex == NULL)
//   {
//
//      ((object *)this)->m_pmutex = new mutex();
//
//   }
//
//   bool bLocked = false;
//
//   try
//   {
//
//      bLocked = m_pmutex->lock(duration);
//
//   }
//   catch(...)
//   {
//
//      bLocked = false;
//
//   }
//
//   if(!bLocked)
//      return false;
//
//   return true;
//
//}
//
//
//bool object::unlock()
//{
//
//   if(m_pmutex == NULL)
//      return false;
//
//   bool bUnlocked = false;
//
//   try
//   {
//
//      bUnlocked = m_pmutex->unlock();
//
//   }
//   catch(...)
//   {
//
//      bUnlocked = false;
//
//   }
//
//   if(!bUnlocked)
//      return false;
//
//   return true;
//
//}
//
//bool object::unlock(LONG lCount, LPLONG lpPrevCount)
//{
//   UNREFERENCED_PARAMETER(lCount);
//   UNREFERENCED_PARAMETER(lpPrevCount);
//   return true;
//}
//
//
//bool object::is_locked() const
//{
//
//   // CRITICAL SECTIONS does *NOT* support is locked and timed locks
//   ASSERT(dynamic_cast < critical_section * > ( const_cast < object * > (this)) == NULL);
//
//   single_lock sl(const_cast < object * > (this));
//
//   bool bWasLocked = !sl.lock(duration::zero());
//
//   if(!bWasLocked)
//      sl.unlock();
//
//   return bWasLocked;
//
//}
//
