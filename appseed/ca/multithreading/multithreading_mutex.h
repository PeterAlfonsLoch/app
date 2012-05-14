#pragma once


class CLASS_DECL_ca mutex :
#ifdef WINDOWS
   public sync_object
#else
   public ::radix::object
#endif
{
public:


#ifndef WINDOWS
   pthread_mutex_t      m_mutex;
#endif


   mutex(BOOL bInitiallyOwn = FALSE, LPCTSTR lpszName = NULL, LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);
   virtual ~mutex();


#ifndef WINDOWS
   virtual bool lock(const duration & durationTimeout = ::duration::infinite());
#endif
   bool unlock();


   bool is_locked() const;


};


