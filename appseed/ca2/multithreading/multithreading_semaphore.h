#pragma once


class CLASS_DECL_ca semaphore : 
   virtual public base_sync_object
{
public:


   semaphore(LONG lInitialCount = 1, LONG lMaxCount = 1, LPCTSTR pstrName=NULL, LPSECURITY_ATTRIBUTES lpsaAttributes = NULL);
   virtual ~semaphore();


   virtual bool unlock();
   virtual bool unlock(LONG lCount, LPLONG lprevCount = NULL);

};


