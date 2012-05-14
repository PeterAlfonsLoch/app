#include "framework.h"


semaphore::semaphore(LONG lInitialCount, LONG lMaxCount, const char * pstrName, LPSECURITY_ATTRIBUTES lpsaAttributes) :
   sync_object(pstrName)
{

   ASSERT(lMaxCount > 0);
   ASSERT(lInitialCount <= lMaxCount);

#ifdef WINDOWS

   m_object = ::CreateSemaphore(lpsaAttributes, lInitialCount, lMaxCount, pstrName);
   if (m_object == NULL)
      throw resource_exception();
#else


   m_lMaxCount    = lMaxCount;

   if(pstrName != NULL && *pstrName != '\0')
   {

      string strPath = "/ca2/time/ftok/event/" + string(pstrName);

      m_object = semget(ftok(strPath, 0), 1, 0666 | IPC_CREAT);

   }
   else
   {

      m_object = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);

   }

   semun semctl_arg;

   if(bSet)
   {

      semctl_arg.val = lInitialCount;

   }
   else
   {

      semctl_arg.val = 0;

   }

   semctl(static_cast < int > (m_object), 0, SETVAL, semctl_arg);


#endif

}

semaphore::~semaphore()
{
}

bool semaphore::unlock(LONG lCount, LPLONG lpPrevCount /* =NULL */)
{

#ifdef WINDOWS

   return ::ReleaseSemaphore(m_object, lCount, lpPrevCount) != FALSE;

#else

   semun semctl_arg;

   semctl(static_cast < int > (m_object), 0, GETVAL, semctl_arg);

   if(lpPrevCount !=  NULL)
   {

      *lpPrevCount = semctl_arg.val;

   }

   if(lCount + semctl_arg.val > m_lMaxCount)
   {

      return false;

   }

   semctl_arg.val += lCount;

   semctl(static_cast < int > (m_object), 0, SETVAL, semctl_arg);

   return true;

#endif

}

bool semaphore::unlock()
{

   return unlock(1, NULL);

}

