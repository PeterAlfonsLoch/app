#pragma once


class CLASS_DECL_AURA semaphore :
   virtual public sync_object
{
public:

   string            m_strName;

#if defined(ANDROID)

   LONG              m_lMaxCount;
   sem_t *           m_psem;

#elif defined(LINUX) || defined(APPLEOS)

   LONG              m_lMaxCount;
   int32_t           m_object;

#endif

   semaphore(sp(::aura::application) papp, LONG lInitialCount = 1, LONG lMaxCount = 1, const char * pstrName=NULL, LPSECURITY_ATTRIBUTES lpsaAttributes = NULL);
   virtual ~semaphore();

   
#if defined(APPLEOS) || defined(LINUX) || defined(ANDROID) || defined(SOLARIS)
   using object::lock;
   virtual bool lock(const duration & durationTimeout);
#endif
   
   virtual bool unlock();
   virtual bool unlock(LONG lCount, LPLONG lprevCount = NULL);

};


