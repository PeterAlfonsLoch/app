#pragma once


class CLASS_DECL_AXIS condition :
   virtual public waitable
{
public:

#if defined(LINUX) || defined(APPLEOS) || defined(SOLARIS)

   int_ptr           m_object;
   bool              m_bManualEvent;
   bool              m_bSignaled;  // meaningful only when m_bManualEvent
   int32_t           m_iSignalId;  // meaningful only when m_bManualEvent

#elif defined(ANDROID)

   sem_t                m_sem;

#else

   CRITICAL_SECTION     m_sect;
   CONDITION_VARIABLE   m_var;

#endif


   condition(sp(::axis::application) papp);
   virtual ~condition();


   using waitable::lock;
   virtual bool lock(const duration & durationTimeout = duration::infinite());

   using waitable::unlock;
   virtual bool unlock();

   virtual void * get_os_data() const;

   bool pulse();

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

