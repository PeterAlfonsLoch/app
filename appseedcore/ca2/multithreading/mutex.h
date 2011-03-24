#pragma once

/////////////////////////////////////////////////////////////////////////////
// mutex

class CLASS_DECL_ca mutex : 
#ifdef _WIN32
   public sync_object < HANDLE >
#else
   public sync_object < pthread_mutex_t >
#endif

{
public:
   /* explicit */ mutex(BOOL bInitiallyOwn = FALSE, LPCTSTR lpszName = NULL,
      LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);

// Implementation
public:
   virtual ~mutex();
#ifndef _WIN32
   virtual BOOL Lock(DWORD dwTimeout = INFINITE);
#endif
   BOOL Unlock();
};


CLASS_DECL_ca void set_heap_mutex(mutex * pmutex);
CLASS_DECL_ca mutex * get_heap_mutex();