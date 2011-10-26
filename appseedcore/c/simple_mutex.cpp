#include "StdAfx.h"


#ifdef LINUX


#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>


union semun
{
  int val;
  struct semid_ds *buf;
  USHORT *array;
};


#endif


simple_mutex::simple_mutex(const char * pszName, bool bInitialLock)
{
   if(pszName != NULL && strlen_dup(pszName) > 0)
   {
      m_strName = pszName;
   }
#ifdef _WINDOWS
   if(m_strName.is_empty())
   {
      m_hMutex = ::CreateMutexW(NULL, bInitialLock ? TRUE : FALSE, NULL);
   }
   else
   {
      wchar_t * pwszName = utf8_to_16(m_strName);
      m_hMutex = ::CreateMutexW(NULL, bInitialLock ? TRUE : FALSE, pwszName);
      ca2_free(pwszName);
   }
#else
   if(m_strName.is_empty())
   {
      pthread_mutexattr_t  attr;
      pthread_mutexattr_init(&attr);
      pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
      int rc;
      if(rc = pthread_mutex_init(&m_mutex, &attr))
      {
         throw "RC_OBJECT_NOT_CREATED";
      }
   }
   else
   {
      vsstring str = _c_get_file_name(dir::path("/var/lib/ca2", pszName), true);

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

#ifdef _WINDOWS
   ::CloseHandle(m_hMutex);
#else
   if(m_strName.is_empty())
   {
      pthread_mutex_destroy(&m_mutex);
   }
   else
   {
      semun ignored_argument;
      int iRc = semctl(m_semid, 1, IPC_RMID , ignored_argument);
   }

#endif

}

void simple_mutex::lock()
{
#ifdef _WINDOWS
   WaitForSingleObject(m_hMutex, INFINITE);
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

      int ret = semop(m_semid, operation,1);
      if(ret < 0)
      {
      }
      else
      {
      }

   }
#endif
}

void simple_mutex::unlock()
{
#ifdef _WINDOWS
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

      int ret = semop(m_semid, operation, 1);
      if(ret < 0)
      {
      }
      else
      {
      }

   }
#endif
}




CLASS_DECL_____ void wait_until_mutex_does_not_exist(const char * pszName)
{
   simple_mutex * pmutex = new simple_mutex("Global\\ca2::fontopus::ccvotagus_ca2_spa::7807e510-5579-11dd-ae16-0800200c7784");
   if(::GetLastError() == ERROR_ALREADY_EXISTS)
   {
      while(::GetLastError() == ERROR_ALREADY_EXISTS)
      {
         delete pmutex;
         Sleep(1984 + 1977);
         pmutex = new simple_mutex("Global\\ca2::fontopus::ccvotagus_ca2_spa::7807e510-5579-11dd-ae16-0800200c7784");
      }
   }
   delete pmutex;
}
