#pragma once


class CLASS_DECL_ca semaphore :
   virtual public sync_object
{
public:


#if defined(LINUX)

   LONG             m_lMaxCount;
   int              m_object;

#endif

   semaphore(LONG lInitialCount = 1, LONG lMaxCount = 1, LPCTSTR pstrName=NULL, LPSECURITY_ATTRIBUTES lpsaAttributes = NULL);
   virtual ~semaphore();


   virtual bool unlock();
   virtual bool unlock(LONG lCount, LPLONG lprevCount = NULL);

};


