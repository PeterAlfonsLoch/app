#pragma once


#ifdef WINDOWS
#elif defined(MACOS)
#include <sys/sem.h>
#else
typedef __key_t key_t;
#endif



class CLASS_DECL_ca simple_mutex
{
public:


   vsstring          m_strName;

#ifdef WINDOWS
   HANDLE            m_hMutex;
#else
   int32_t               m_semid;
   key_t             m_key;
   pthread_mutex_t   m_mutex;
#endif



   simple_mutex(const char * pszName = NULL, bool bInitialLock = false);
   ~simple_mutex();


   void lock();
   bool lock(uint32_t dwTimeout);
   void unlock();


};



CLASS_DECL_ca void wait_until_mutex_does_not_exist(const char * pszName);
