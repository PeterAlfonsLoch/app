#pragma once


#ifdef _WINDOWS
#if defined(__CA2__DLL) || defined(SPALIB_DLL)
   #define MUTEX_LOCK_DECL  _declspec(dllexport)
#else
   #define MUTEX_LOCK_DECL  _declspec(dllimport)
#endif
#else
   #define MUTEX_LOCK_DECL
#endif


#ifdef _WINDOWS
typedef void *HANDLE;
#else
#include <pthread.h>
#endif

class MUTEX_LOCK_DECL simple_mutex
{
public:

#ifdef _WINDOWS
   HANDLE            m_hMutex;
#else
   pthread_mutex_t   m_mutex;
#endif



   simple_mutex();
   ~simple_mutex();


   void lock();
   void unlock();

   
};

