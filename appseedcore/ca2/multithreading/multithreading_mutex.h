#pragma once


class CLASS_DECL_ca mutex :
#ifdef _WIN32
   public base_sync_object
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
   virtual bool lock(const duration & durationTimeout = ::duration::infinite());
#endif
   bool unlock();


   bool is_locked();


};


