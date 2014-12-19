#pragma once


class CLASS_DECL_AURA critical_section :
   virtual public waitable
{
public:


#ifdef WINDOWS
   CRITICAL_SECTION     m_sect;
#else
   void *            m_pmutex; // pthread_mutex_t;
#endif

   critical_section();
   virtual ~critical_section();


#ifdef WINDOWS
   operator CRITICAL_SECTION * ();
#else
   operator void * ();           // pthread_mutex_t
#endif

   bool unlock();
   void lock();
   bool lock(const duration & durationTimeout);


private:
   using waitable::unlock;
   bool Init();

};


#ifdef WINDOWS

inline void critical_section::lock()
{
   try
   {
      ::EnterCriticalSection(&m_sect);
   }
   catch(...)
   {
      throw resource_exception(get_app());
   }
}


inline bool critical_section::lock(const duration & durationTimeout)
{
   ASSERT(durationTimeout.is_pos_infinity());
   (void)durationTimeout;
   lock();
   return true;
}

inline bool critical_section::unlock()
{
   ::LeaveCriticalSection(&m_sect);
   return TRUE;
}

#endif
