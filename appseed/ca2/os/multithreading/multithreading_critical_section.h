#pragma once


class CLASS_DECL_ca2 critical_section :
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

