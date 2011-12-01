#pragma once


#ifdef _WINDOWS
typedef void *HANDLE;
#else
#include <pthread.h>
#endif

class CLASS_DECL_c simple_event
{
public:

#ifdef _WINDOWS
   HANDLE            m_hEvent;
#else
   pthread_cond_t    m_cond;
   simple_mutex      m_mutex;
#endif



   simple_event(bool bInitialWait = false);
   ~simple_event();


   void wait();


};



