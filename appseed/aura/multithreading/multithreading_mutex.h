#pragma once





class CLASS_DECL_AURA mutex :
   public sync_object
{
public:


#ifndef WINDOWS


   // thread mutex
   void *            m_pmutex; // pthread_mutex_t;



   // named process mutex
   string                  m_strName;

#ifdef ANDROID

   sem_t *                 m_psem;

#else

   key_t                   m_key;
   int32_t                 m_semid;

#endif




#endif

   bool                    m_bAlreadyExists;


   mutex(::aura::application * papp = NULL, bool bInitiallyOwn = FALSE, const char * lpszName = NULL, LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);


protected:

#ifdef WINDOWS

   mutex(::aura::application * papp, const char * pstrName, HANDLE h);

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


   bool already_exists();


   static mutex * open_mutex(::aura::application * papp, const char * pstrName);


};


CLASS_DECL_AURA void wait_until_mutex_does_not_exist(const char * pszName);



CLASS_DECL_AURA mutex * get_ui_destroyed_mutex();




#ifdef WINDOWSEX

class null_dacl_security_attributes
{
public:

   SECURITY_ATTRIBUTES m_securityattributes;

   SECURITY_DESCRIPTOR m_securitydescriptor;

   null_dacl_security_attributes();

};

#endif

class spaadmin_mutex:
#ifdef WINDOWSEX
   public null_dacl_security_attributes,
#endif
   public mutex
{
public:

   spaadmin_mutex();

};

