#pragma once


class CLASS_DECL_ca event : 
   virtual public sync_object_base,
   virtual public event_base
{
public:


   event(BOOL bInitiallyOwn = FALSE, BOOL bManualReset = FALSE, LPCTSTR lpszNAme = NULL, LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);
   virtual ~event();


   virtual bool lock(const duration & durationTimeout = duration::infinite());

   using sync_object_base::unlock;
   virtual bool unlock();

   HANDLE get_os_data() const;

   BOOL SetEvent();
   BOOL PulseEvent();
   BOOL ResetEvent();

/**
* \brief	Platform independent waitables (windows version)
* \author	Thomas Hoefer
*/

	///  \brief		waits for an event forever
	virtual void wait ();

	///  \brief		waits for an event for a specified time
	///  \param		duration time period to wait for an event
	///  \return	waiting action result as WaitResult
   virtual wait_result wait (const duration & duration);

   bool is_signaled() const;
   
};

