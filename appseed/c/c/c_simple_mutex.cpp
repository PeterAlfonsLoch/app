#include "framework.h"


#if defined(LINUX) || defined(MACOS)


#include <sys/ipc.h>
#include <sys/sem.h>


#ifdef MACOS


BEGIN_EXTERN_C

int32_t flock(int32_t, int32_t);

END_EXTERN_C


#endif


#endif





simple_mutex::simple_mutex(const char * pszName, bool bInitialLock)
{
   if(pszName != NULL && strlen_dup(pszName) > 0)
   {
      m_strName = pszName;
   }
#ifdef WINDOWSEX
   if(m_strName.is_empty())
   {
      m_hMutex = ::CreateMutexW(NULL, bInitialLock ? TRUE : FALSE, NULL);
   }
   else
   {
      wchar_t * pwszName = utf8_to_16(m_strName);
      m_hMutex = ::CreateMutexW(NULL, bInitialLock ? TRUE : FALSE, pwszName);
      _ca_free(pwszName, 0);
   }
#elif defined(METROWIN)
   if(m_strName.is_empty())
   {
      m_hMutex = ::CreateMutexEx(NULL, NULL, bInitialLock ?  CREATE_MUTEX_INITIAL_OWNER : 0, SYNCHRONIZE);
   }
   else
   {
      wchar_t * pwszName = utf8_to_16(m_strName);
      m_hMutex = ::CreateMutexEx(NULL, pwszName, bInitialLock ?  CREATE_MUTEX_INITIAL_OWNER : 0, SYNCHRONIZE);
      _ca_free(pwszName, 0);
   }
#else
   if(m_strName.is_empty())
   {
      pthread_mutexattr_t  attr;
      pthread_mutexattr_init(&attr);
      pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
      int32_t rc;
      if((rc = pthread_mutex_init(&m_mutex, &attr)))
      {
         throw "RC_OBJECT_NOT_CREATED";
      }
   }
   else
   {
      vsstring str = _c_get_file_name(dir::path("/var/lib/ca", pszName), true);

      m_key = ftok(".", 'c');

      m_semid = semget(m_key,       // a unique identifier to identify semaphore set
                  1,                // number of semaphore in the semaphore set
                  0666 | IPC_CREAT  // permissions (rwxrwxrwx) on the new
                                    //    semaphore set and creation flag
                  );

      if(m_semid < 0)
      {
         throw "RC_OBJECT_NOT_CREATED";
      }


      semun semctl_arg;

      //Set Initial value for the resource
      semctl_arg.val = bInitialLock ? 1 : 0; //Setting semval to 1


      semctl(m_semid, 0, SETVAL, semctl_arg);


   }
#endif
}


simple_mutex::~simple_mutex()
{

#ifdef WINDOWS
   ::CloseHandle(m_hMutex);
#else
   if(m_strName.is_empty())
   {
      pthread_mutex_destroy(&m_mutex);
   }
   else
   {
      semun ignored_argument;
//      int32_t iRc = semctl(m_semid, 1, IPC_RMID , ignored_argument);
      semctl(m_semid, 1, IPC_RMID , ignored_argument);
   }

#endif

}

void simple_mutex::lock()
{
#ifdef WINDOWSEX
   WaitForSingleObject(m_hMutex, INFINITE);
#elif defined(METROWIN)
   WaitForSingleObjectEx(m_hMutex, INFINITE, FALSE);
#else
   if(m_strName.is_empty())
   {
      pthread_mutex_lock(&m_mutex);
   }
   else
   {

      struct sembuf operation[1];

      operation[0].sem_op     = 0;
      operation[0].sem_num    = 0;
      operation[0].sem_flg    = 0;

      int32_t ret = semop(m_semid, operation,1);
      if(ret < 0)
      {
      }
      else
      {
      }

   }
#endif
}



#ifdef MACOS


int pthread_mutex_timedlock(pthread_mutex_t * mutex, const struct timespec * abs_timeout)
{
   
   if(abs_timeout == NULL || (abs_timeout->tv_sec == 0 && abs_timeout->tv_nsec == 0))
   {
      
      return pthread_mutex_lock(mutex);
      
   }
   else
   {
      uint64_t uiTimeout = abs_timeout->tv_sec * 1000 + (abs_timeout->tv_nsec / (1000 * 1000));
      uint64_t ui = get_tick_count();
      int result;
   do
   {
      result = pthread_mutex_trylock(mutex);
      if(result == EBUSY)
      {
         timespec ts;
         ts.tv_sec = 0;
         ts.tv_sec = 10000000;
         
         /* Sleep for 10,000,000 nanoseconds before trying again. */
         int status = -1;
         while (status == -1)
            status = nanosleep(&ts, &ts);
      }
      else
         return result;
   }
   while(get_tick_count() - ui < uiTimeout);
   
      return ETIMEDOUT;
   }
}


#endif


bool simple_mutex::lock(uint32_t uiTimeout)
{
#ifdef WINDOWSEX
   return WaitForSingleObject(m_hMutex, uiTimeout) == WAIT_OBJECT_0;
#elif defined(METROWIN)
   return WaitForSingleObjectEx(m_hMutex, uiTimeout, FALSE) == WAIT_OBJECT_0;
#else
   if(m_strName.is_empty())
   {

      timespec spec;

      spec.tv_sec = uiTimeout / 1000;

      spec.tv_nsec = (uiTimeout % 1000) * 1000 * 1000;

      int32_t ret = pthread_mutex_timedlock(&m_mutex, &spec);

      if(ret < 0)
      {
         return false;
      }
      else
      {
         return true;
      }


   }
   else
   {

      struct sembuf operation[1];

      operation[0].sem_op     = 0;
      operation[0].sem_num    = 0;
      operation[0].sem_flg    = 0;

      int32_t ret = semop(m_semid, operation,1);
      if(ret < 0)
      {
         return false;
      }
      else
      {
         return true;
      }

   }
#endif
}


void simple_mutex::unlock()
{
#ifdef WINDOWS
   ReleaseMutex(m_hMutex);
#else
   if(m_strName.is_empty())
   {
      pthread_mutex_unlock(&m_mutex);
   }
   else
   {

      struct sembuf operation[1];

      operation[0].sem_op     = -1;
      operation[0].sem_num    = 0;
      operation[0].sem_flg    = 0;

      int32_t ret = semop(m_semid, operation, 1);
      if(ret < 0)
      {
      }
      else
      {
      }

   }
#endif
}




CLASS_DECL_c void wait_until_mutex_does_not_exist(const char * pszName)
{
   simple_mutex * pmutex = new simple_mutex("Global\\::ca::fontopus::ca2_spa::7807e510-5579-11dd-ae16-0800200c7784");
   if(::GetLastError() == ERROR_ALREADY_EXISTS)
   {
      while(::GetLastError() == ERROR_ALREADY_EXISTS)
      {
         delete pmutex;
         Sleep(184);
         pmutex = new simple_mutex("Global\\::ca::fontopus::ca2_spa::7807e510-5579-11dd-ae16-0800200c7784");
      }
   }
   delete pmutex;
}
