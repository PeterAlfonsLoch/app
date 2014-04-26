#include "framework.h"


#if defined(LINUX) || defined(APPLEOS)
#include <sys/ipc.h>
#include <sys/sem.h>
#elif defined(ANDROID)
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
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

#elif defined(ANDROID)


   m_lMaxCount    = lMaxCount;

   if(pstrName != NULL && *pstrName != '\0')
   {

      m_strName = "/core/time/ftok/event/" + string(pstrName);


      if ((m_psem = sem_open(m_strName, O_CREAT | O_EXCL, 0666, lInitialCount)) != SEM_FAILED)
      {

         // We got here first

      }
      else
      {

         if (errno != EEXIST)
            throw resource_exception(get_app());

         // We're not first.  Try again

         m_psem = sem_open(m_strName, 0);

         if (m_psem == SEM_FAILED)
            throw resource_exception(get_app());;

      }

   }
   else
   {

      m_psem = new sem_t;

      sem_init(m_psem, 0, lInitialCount);

   }

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


#if defined(ANDROID) 

bool semaphore::lock(const duration & durationTimeout)
{

   timespec ts;

   ((duration &)durationTimeout).normalize();

   ts.tv_nsec = durationTimeout.m_iNanoseconds;
   ts.tv_sec = durationTimeout.m_iSeconds;

   sem_timedwait(m_psem, &ts);

   return true;


}

#elif defined(APPLEOS) || defined(LINUX) || defined(SOLARIS)

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

#elif ANDROID

   int val;;

   if (sem_getvalue(m_psem, &val) != 0)
   {

      return false;

   }

   if(lpPrevCount !=  NULL)
   {

      *lpPrevCount = val;

   }

   if(lCount + val > m_lMaxCount)
   {

      return false;

   }

   while (lCount > 0)
   {

      sem_post(m_psem);

      lCount--;

   }

   

   return true;

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

