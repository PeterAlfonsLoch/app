#include "framework.h"

#ifdef WINDOWS

bool critical_section::Init()
{
   __try
   {
//      ::InitializeCriticalSection(&m_sect);
      ::InitializeCriticalSectionEx(&m_sect, 4000, 0);
   }
   __except(STATUS_NO_MEMORY == GetExceptionCode())
   {
      return FALSE;
   }

   return TRUE;
}

critical_section::critical_section()
{
   bool bSuccess;

   bSuccess = Init();
   if (!bSuccess)
      throw memory_exception(get_app());
}

critical_section::operator CRITICAL_SECTION*()
{
   return (CRITICAL_SECTION*) &m_sect;
}

critical_section::~critical_section()
{
   ::DeleteCriticalSection(&m_sect);
}



#else

bool critical_section::Init()
{
   try
   {

      pthread_mutexattr_t mutexattr;   // Mutex attribute variable

      pthread_mutexattr_init(&mutexattr);

      // set the mutex as a recursive mutex

#ifdef APPLEOS

      pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE);


#else

      pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE_NP);

#endif

      // create the mutex with the attributes set
      pthread_mutex_init(&m_mutex, &mutexattr);

      //After initializing the mutex, the thread attribute can be destroyed
      pthread_mutexattr_destroy(&mutexattr);

   }
   catch(...)
   {
      return FALSE;
   }

   return TRUE;
}

critical_section::critical_section()
{
   bool bSuccess;

   bSuccess = Init();
   if (!bSuccess)
      throw memory_exception(get_app());
}

critical_section::operator pthread_mutex_t*()
{
   return (pthread_mutex_t * ) &m_mutex;
}

critical_section::~critical_section()
{
   // Destroy / close the mutex
   pthread_mutex_destroy (&m_mutex);
}

void critical_section::lock()
{

   try
   {

      // Acquire the mutex to access the shared resource
      pthread_mutex_lock (&m_mutex);

   }
   catch(...)
   {

      throw memory_exception(get_app());

   }

}


bool critical_section::lock(const duration & durationTimeout)
{
   ASSERT(durationTimeout.is_pos_infinity());
   (void)durationTimeout;
   lock();
   return true;

}

bool critical_section::unlock()
{
   // Release the mutex  and release the access to shared resource
   pthread_mutex_unlock (&m_mutex);
   return TRUE;
}





#endif
