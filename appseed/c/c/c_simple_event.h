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
   bool              m_bManualEvent;
   bool              m_bSignaled;  // meaningful only when m_bManualEvent
   int               m_iSignalId;  // meaningful only when m_bManualEvent
#endif



   simple_event(bool bInitialWait = false, bool bManualReset = false);
   ~simple_event();


   void set_event();

   void reset_event();

   void wait();
   void wait(DWORD dwTimeout);


};


