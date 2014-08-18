#pragma once

#if defined(LINUX) || defined(APPLEOS)
#include <sys/types.h>
#include <sys/sem.h>
#endif

class CLASS_DECL_AXIS event :
   virtual public event_base
{
public:

#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)
   bool              m_bManualEvent;
   bool              m_bSignaled;  // meaningful only when m_bManualEvent
   int32_t           m_iSignalId;  // meaningful only when m_bManualEvent
   pthread_cond_t    m_cond;
   pthread_mutex_t   m_mutex;
#endif


   event(sp(::axis::application) papp, bool bInitiallyOwn = FALSE, bool bManualReset = FALSE, const char * lpszNAme = NULL, LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);
   virtual ~event()
#ifdef METROWIN
       { }
#else
      ;
#endif

   using event_base::lock;
   virtual bool lock(const duration & durationTimeout = duration::infinite());

   using waitable::unlock;
   virtual bool unlock();

   virtual void * get_os_data() const;

   bool SetEvent();
   bool set_event() {return SetEvent(); }
   //bool PulseEvent();
   bool ResetEvent();

/**
* \brief	Platform independent waitables (windows version)
*/

	///  \brief		waits for an event forever
	virtual void wait ();

	///  \brief		waits for an event for a specified time
	///  \param		duration time period to wait for an event
	///  \return	waiting action result as WaitResult
   virtual wait_result wait (const duration & duration);

   bool is_signaled() const;

};

