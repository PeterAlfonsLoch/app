#pragma once


class CLASS_DECL_ca mutex :
   public sync_object
{
public:


#ifndef WINDOWS


   // thread mutex
   pthread_mutex_t      m_mutex;


   // named process mutex
   string               m_strName;
   key_t                m_key;
   int                  m_semid;

#endif


   mutex(::ca::application * papp, bool bInitiallyOwn = FALSE, const char * lpszName = NULL, LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);


protected:

#ifdef WINDOWS

   mutex(::ca::application * pappp, const char * pstrName, HANDLE h);

#else

   mutex(const char * pstrName, key_t key, int semid);

#endif


public:


   virtual ~mutex();


#ifndef WINDOWS

   using sync_object::lock;

   virtual bool lock(const duration & durationTimeout = ::duration::infinite());

   using sync_object::wait;

   virtual wait_result wait(const duration & durationTimeout);

#endif

   virtual bool unlock();


   static mutex * open_mutex(::ca::application * papp, const char * pstrName);


};


