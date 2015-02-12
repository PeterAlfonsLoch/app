#pragma once


class CLASS_DECL_AURA critical_section
{
public:


#ifdef WINDOWS
   CRITICAL_SECTION     m_sect;
#else
   void *            m_pmutex; // pthread_mutex_t;
#endif

   critical_section();
   ~critical_section();


#ifdef WINDOWS
   operator CRITICAL_SECTION * ();
#else
   operator void * ();           // pthread_mutex_t
#endif

   inline void unlock();
   inline void lock();


private:
   bool Init();

};


#ifdef WINDOWS

inline void critical_section::lock()
{
   //try
   {
      ::EnterCriticalSection(&m_sect);
   }
   //catch(...)
   //{
     // throw resource_exception(get_app());
   //}
}


//inline bool critical_section::lock(const duration & durationTimeout)
//{
//   ASSERT(durationTimeout.is_pos_infinity());
//   (void)durationTimeout;
//   lock();
//   return true;
//}

inline void critical_section::unlock()
{
   ::LeaveCriticalSection(&m_sect);
   //return TRUE;
}

#endif


class CLASS_DECL_AURA cslock
{
public:

   critical_section * m_pcs;


   inline cslock(critical_section * pcs): m_pcs(pcs) { if(m_pcs != NULL) m_pcs->lock(); }
   inline ~cslock() { if(m_pcs != NULL) m_pcs->unlock(); }


};