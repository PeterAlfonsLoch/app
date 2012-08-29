#pragma once


#ifdef WINDOWS
typedef void *HANDLE;
#elif defined(MACOS)
#include <sys/sem.h>
#else
typedef __key_t key_t;
#include <pthread.h>
#endif



class CLASS_DECL_c simple_mutex
{
public:


   vsstring          m_strName;

#ifdef WINDOWS
   HANDLE            m_hMutex;
#else
   int               m_semid;
   key_t             m_key;
   pthread_mutex_t   m_mutex;
#endif



   simple_mutex(const char * pszName = NULL, bool bInitialLock = false);
   ~simple_mutex();


   void lock();
   void unlock();


};



CLASS_DECL_c void wait_until_mutex_does_not_exist(const char * pszName);
