#pragma once


class CLASS_DECL_AXIS mutex :
   public sync_object
{
public:


#ifndef WINDOWS


   // thread mutex
   pthread_mutex_t         m_mutex;

   // named process mutex
   string                  m_strName;

#ifdef ANDROID

   sem_t *                 m_psem;

#else

   key_t                   m_key;
   int32_t                 m_semid;

#endif




#endif


   mutex(sp(::axis::application) papp = NULL, bool bInitiallyOwn = FALSE, const char * lpszName = NULL, LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);


protected:

#ifdef WINDOWS

   mutex(sp(::axis::application) pappp, const char * pstrName, HANDLE h);

#elif defined(ANDROID)

   mutex(const char * pstrName, sem_t * psem);

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
   
   using sync_object::unlock;
   virtual bool unlock();


   static mutex * open_mutex(sp(::axis::application) papp, const char * pstrName);


};


CLASS_DECL_AXIS void wait_until_mutex_does_not_exist(const char * pszName);



