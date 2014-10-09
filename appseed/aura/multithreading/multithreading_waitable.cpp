/**
* \brief	Platform independent waitables
* \author	Thomas Hoefer
*/

#include "framework.h"


waitable::waitable()
{

   m_pmutex = NULL;

}

waitable::waitable(const waitable & objectSrc)
{

   UNREFERENCED_PARAMETER(objectSrc);

   m_pmutex = NULL;

}


///  \brief		destructor
waitable::~waitable()
{

   if(m_pmutex != NULL)
   {

      delete m_pmutex;

      m_pmutex = NULL;

   }

}

///  \brief		abstract function to initialize a waiting action without a timeout
void waitable::wait()
{

   wait(duration::infinite());

}

	///  \brief		abstract function to initialize a waiting action with a timeout
	///  \param		duration time period to wait for item
	///  \return	waiting action result as wait_result
wait_result waitable::wait(const duration & duration )
{


   if(m_pmutex == NULL)
   {

      ((waitable *)this)->m_pmutex = new mutex();

   }

   try
   {
      return m_pmutex->wait(duration);
   }
   catch(...)
   {
   }

   return wait_result(wait_result::Failure);

}




// forward declaration
//class event_base;

/// This class represents a virtual interface for a callback method for WaitableItems in a
/// event_collection.

waitable_callback::~waitable_callback()
{
}

	/// called on signalization of a event_base
	/// \param signaling event_base
//	virtual void callback(const event_base& waitItem) = 0;
//};


///  \brief		pauses waitable for specified time
///  \param		duration sleeping time of waitable
/*CLASS_DECL_AURA void sleep(const duration & duration)
{
   Sleep((uint32_t)duration.total_milliseconds());
}*/

CLASS_DECL_AURA void sleep(const duration & duration)
{
   ::Sleep(static_cast<uint32_t>(duration.total_milliseconds()));
}





void * waitable::get_os_data() const
{

   if(m_pmutex == NULL)
   {

      ((waitable *)this)->m_pmutex = new mutex();

   }

   return m_pmutex;

}

void waitable::lock()
{

   if(!lock(duration::infinite()))
      if(!lock(duration::infinite()))
         throw "failure to lock waitable";

}

bool waitable::lock(const duration & duration)
{

   if(m_pmutex == NULL)
   {

      ((waitable *)this)->m_pmutex = new mutex();

   }

   bool bLocked = false;

   try
   {

      bLocked = m_pmutex->lock(duration);

   }
   catch(...)
   {

      bLocked = false;

   }

   if(!bLocked)
      return false;

   return true;

}


bool waitable::unlock()
{

   if(m_pmutex == NULL)
      return false;

   bool bUnlocked = false;

   try
   {

      bUnlocked = m_pmutex->unlock();

   }
   catch(...)
   {

      bUnlocked = false;

   }

   if(!bUnlocked)
      return false;

   return true;

}

bool waitable::unlock(LONG lCount, LPLONG lpPrevCount)
{
   UNREFERENCED_PARAMETER(lCount);
   UNREFERENCED_PARAMETER(lpPrevCount);
   return true;
}


bool waitable::is_locked() const
{

   // CRITICAL SECTIONS does *NOT* support is locked and timed locks
   ASSERT(dynamic_cast < critical_section * > ( const_cast < waitable * > (this)) == NULL);

   single_lock sl(const_cast < waitable * > (this));

   bool bWasLocked = !sl.lock(duration::zero());

   if(!bWasLocked)
      sl.unlock();

   return bWasLocked;

}

