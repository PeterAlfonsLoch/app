#pragma once

class CLASS_DECL_ca semaphore : 
   public sync_object < HANDLE >
{
public:


   semaphore(LONG lInitialCount = 1, LONG lMaxCount = 1, LPCTSTR pstrName=NULL, LPSECURITY_ATTRIBUTES lpsaAttributes = NULL);

   virtual ~semaphore();
   virtual BOOL Unlock();
   virtual BOOL Unlock(LONG lCount, LPLONG lprevCount = NULL);

};
