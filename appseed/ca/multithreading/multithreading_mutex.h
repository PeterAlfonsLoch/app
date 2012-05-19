#pragma once


class CLASS_DECL_ca mutex :
   public sync_object
{
public:


#ifndef WINDOWS
   pthread_mutex_t      m_mutex;
#endif


   mutex(bool bInitiallyOwn = FALSE, LPCTSTR lpszName = NULL, LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);
   virtual ~mutex();


#ifndef WINDOWS

   virtual bool lock(const duration & durationTimeout = ::duration::infinite());

   virtual wait_result wait(const duration & durationTimeout);

#endif

   virtual bool unlock();





};


