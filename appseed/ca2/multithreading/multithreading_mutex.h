#pragma once


class CLASS_DECL_ca2 mutex :
   public sync_object
{
public:


#ifndef WINDOWS


   // thread mutex
   pthread_mutex_t      m_mutex;


   // named process mutex
   string               m_strName;
   key_t                m_key;
   int32_t                  m_semid;

#endif


   mutex(sp(::ca::application) papp, bool bInitiallyOwn = FALSE, const char * lpszName = ::null(), LPSECURITY_ATTRIBUTES lpsaAttribute = ::null());


protected:

#ifdef WINDOWS

   mutex(sp(::ca::application) pappp, const char * pstrName, HANDLE h);

#else

   mutex(const char * pstrName, key_t key, int32_t semid);

#endif


public:


   virtual ~mutex();


#ifndef WINDOWS

   using sync_object::lock;

   virtual bool lock(const duration & durationTimeout);

   using sync_object::wait;

   virtual wait_result wait(const duration & durationTimeout);

#endif

   virtual bool unlock();


   static mutex * open_mutex(sp(::ca::application) papp, const char * pstrName);


};


