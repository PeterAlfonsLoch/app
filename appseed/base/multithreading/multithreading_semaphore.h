#pragma once


class CLASS_DECL_BASE semaphore :
   virtual public sync_object
{
public:


#if defined(LINUX) || defined(MACOS)

   LONG             m_lMaxCount;
   int32_t              m_object;

#endif

   semaphore(sp(base_application) papp, LONG lInitialCount = 1, LONG lMaxCount = 1, const char * pstrName=NULL, LPSECURITY_ATTRIBUTES lpsaAttributes = NULL);
   virtual ~semaphore();

   
#if defined(MACOS) || defined(LINUX) || defined(ANDROID) || defined(SOLARIS)
   using object::lock;
   virtual bool lock(const duration & durationTimeout);
#endif
   
   virtual bool unlock();
   virtual bool unlock(LONG lCount, LPLONG lprevCount = NULL);

};


