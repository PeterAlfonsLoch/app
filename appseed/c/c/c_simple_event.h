#pragma once


#ifdef WINDOWS
typedef void *HANDLE;
#else
#include <pthread.h>
#endif

class CLASS_DECL_c simple_event
{
public:

#ifdef WINDOWS
   HANDLE            m_hEvent;
#else
   pthread_cond_t    m_cond;
   simple_mutex      m_mutex;
#endif



   simple_event(bool bInitialWait = false);
   ~simple_event();


   void wait();
   void wait(DWORD dwTimeout);


};



