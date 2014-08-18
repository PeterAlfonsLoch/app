#pragma once


class CLASS_DECL_BASE critical_section :
   virtual public waitable
{
public:


#ifdef WINDOWS
   CRITICAL_SECTION     m_sect;
#else
   pthread_mutex_t      m_mutex;           // Mutex
#endif

   critical_section();
   virtual ~critical_section();


#ifdef WINDOWS
   operator CRITICAL_SECTION * ();
#else
   operator pthread_mutex_t * ();           // Mutex
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
