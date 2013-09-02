#pragma once


#ifdef WINDOWS
#elif defined(ANDROID) || defined(SOLARIS)
#include <fcntl.h>
#include <semaphore.h>
#elif defined(MACOS)
#include <sys/sem.h>
#else
typedef __key_t key_t;
#endif



class CLASS_DECL_ca mutex
{
public:


   vsstring          m_strName;

#ifdef WINDOWS
   HANDLE            m_hMutex;
#elif ANDROID
   vsstring          m_key;
   sem_t *           m_sem;
#else
   key_t             m_key;
   int32_t           m_semid;
   pthread_mutex_t   m_mutex;
#endif



   mutex(const char * pszName = NULL, bool bInitialLock = false);
   ~mutex();


   void lock();
   bool lock(uint32_t dwTimeout);
   void unlock();


};



CLASS_DECL_ca void wait_until_mutex_does_not_exist(const char * pszName);
