#pragma once


class CLASS_DECL_ca semaphore :
   virtual public sync_object
{
public:


#if defined(LINUX) || defined(MACOS)

   LONG             m_lMaxCount;
   int32_t              m_object;

#endif

   semaphore(::ca::applicationsp papp, LONG lInitialCount = 1, LONG lMaxCount = 1, const char * pstrName=::null(), LPSECURITY_ATTRIBUTES lpsaAttributes = ::null());
   virtual ~semaphore();


   virtual bool unlock();
   virtual bool unlock(LONG lCount, LPLONG lprevCount = ::null());

};


