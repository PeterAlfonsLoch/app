#include "framework.h"


#if defined(LINUX) || defined(MACOS)
#include <sys/ipc.h>
#include <sys/sem.h>
#endif


semaphore::semaphore(sp(base_application) papp, LONG lInitialCount, LONG lMaxCount, const char * pstrName, LPSECURITY_ATTRIBUTES lpsaAttributes) :
   element(papp),
   sync_object(pstrName)
{

   ASSERT(lMaxCount > 0);
   ASSERT(lInitialCount <= lMaxCount);

#ifdef WINDOWS

   m_object = ::CreateSemaphoreExW(lpsaAttributes, lInitialCount, lMaxCount, ::str::international::utf8_to_unicode(pstrName), 0, SEMAPHORE_MODIFY_STATE | DELETE | SYNCHRONIZE);
   if (m_object == NULL)
      throw resource_exception(papp);
#else


   m_lMaxCount    = lMaxCount;

   if(pstrName != NULL && *pstrName != '\0')
   {

      string strPath = "/core/time/ftok/event/" + string(pstrName);

      m_object = semget(ftok(strPath, 0), 1, 0666 | IPC_CREAT);

   }
   else
   {

      m_object = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);

   }

   semun semctl_arg;

   semctl_arg.val = lInitialCount;

   semctl(static_cast < int32_t > (m_object), 0, SETVAL, semctl_arg);


#endif

}

semaphore::~semaphore()
{
}


#if defined(MACOS) || defined(LINUX) || defined(ANDROID) || defined(SOLARIS)

bool semaphore:: lock(const duration & durationTimeout)
{
   
   struct sembuf sb;
   
   sb.sem_num  = 0;
   sb.sem_op   = 0;
   sb.sem_flg  = 0;
   
   semop(static_cast < int32_t > (m_object), &sb, 1);
   
   return true;
   
   
}



#endif



bool semaphore::unlock(LONG lCount, LPLONG lpPrevCount /* =NULL */)
{

#ifdef WINDOWS

   return ::ReleaseSemaphore(m_object, lCount, lpPrevCount) != FALSE;

#else

   semun semctl_arg;

   semctl(static_cast < int32_t > (m_object), 0, GETVAL, semctl_arg);

   if(lpPrevCount !=  NULL)
   {

      *lpPrevCount = semctl_arg.val;

   }

   if(lCount + semctl_arg.val > m_lMaxCount)
   {

      return false;

   }

   semctl_arg.val += lCount;

   semctl(static_cast < int32_t > (m_object), 0, SETVAL, semctl_arg);

   return true;

#endif

}

bool semaphore::unlock()
{

   return unlock(1, NULL);

}

