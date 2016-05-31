#pragma once

#ifdef APPLEOS
#include <semaphore.h>
#endif



class CLASS_DECL_ACE mutex :
   virtual public sync_object
{
public:


#if !defined(WINDOWS)


   pthread_mutex_t         m_mutex;
   //string                  m_strName;

#if defined(ANDROID) || defined(APPLEOS)

   sem_t *                 m_psem;

#else

   key_t                   m_key;
   int32_t                 m_semid;

#endif


#endif


   bool                    m_bAlreadyExists;


   mutex(const mutex & m);
#ifdef WINDOWS
   mutex(::ace::application * papp,const char * pstrName,void * posdata, bool bOwner = true);
#elif defined(ANDROID) || defined(APPLEOS)
   mutex(::ace::application * papp,const char * pstrName,sem_t * psem,bool bOwner = true);
#else
   mutex(::ace::application * papp,const char * pstrName,key_t key, int32_t semid, bool bOwner = true);
#endif
   mutex(::ace::application * papp = NULL,bool bInitiallyOwn = FALSE,const char * lpszName = NULL,LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);



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


   static mutex * open_mutex(::ace::application * papp, const char * pstrName);


};


CLASS_DECL_ACE void wait_until_mutex_does_not_exist(const char * pszName);



CLASS_DECL_ACE mutex * get_ui_destroyed_mutex();




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

