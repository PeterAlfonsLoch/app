#include "framework.h"


#if defined(LINUX) || defined(SOLARIS) || defined(APPLEOS)
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>
#elif defined(ANDROID)
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#endif


static int g_iMutex = 0;

string str_md5_dup(const char * psz);

mutex::mutex(::aura::application * papp, bool bInitiallyOwn, const char * pstrName, LPSECURITY_ATTRIBUTES lpsaAttribute /* = NULL */) :
   sync_object(pstrName)
{

   m_bOwner = true;

   m_bAlreadyExists = false;

#ifdef WINDOWS

    m_object = ::CreateMutexExW(lpsaAttribute,pstrName == NULL ? NULL : (const unichar *) ::str::international::utf8_to_unicode(pstrName),bInitiallyOwn ?  CREATE_MUTEX_INITIAL_OWNER : 0,MUTEX_ALL_ACCESS);

    DWORD dwLastError = ::GetLastError();

    m_bAlreadyExists = dwLastError == ERROR_ALREADY_EXISTS;

   if(m_object == NULL)
   {

      DWORD dwError1 = ::GetLastError();



      if(pstrName != NULL)
      {

         m_object = ::OpenMutexW(SYNCHRONIZE,FALSE,::str::international::utf8_to_unicode(pstrName));

      }

      if(m_object == NULL)
      {

         DWORD dwError2 = ::GetLastError();

         throw resource_exception(papp);

      }

   }

#else

#if defined(ANDROID)

    m_psem = SEM_FAILED;

    if(pstrName != NULL && *pstrName != '\0')
    {

       m_pmutex = NULL;

       m_psem = NULL;

       return;

       //string strName(pstrName);

       ////if(str::begins_ci(pstrName, "Global"))
       ////{

       ////   m_strName = ::file::path(::aura::system::g_p->m_pandroidinitdata->m_pszCacheDir) / "var" / "tmp"/ strName;

       ////   ::dir::mk(::file::path(m_strName).folder());

       ////}
       ////else
       ////{

       ////   m_strName = ::file::path(getenv("HOME")) / strName;

       ////}

       //s

       //m_strName.replace("/", "_");
       //m_strName.replace(":", "_");
       //m_strName.replace("/", "_");

       ////::file_put_contents_dup(m_strName, m_strName);

       ////string strTest = file_as_string_dup(m_strName);

       ////int isCreator = 0;

       //if ((m_psem = sem_open(m_strName, O_CREAT|O_EXCL, 0644, 1)) != SEM_FAILED)
       //{

       //   // We got here first

       //   //isCreator = 1;

       //}
       //else
       //{

       //   int err = errno;

       //   if (err != EEXIST)
       //      throw resource_exception(get_app());

       //   // We're not first.  Try again

       //   m_psem = sem_open(m_strName, 0);

       //   if (m_psem == SEM_FAILED)
       //      throw resource_exception(get_app());;

       //}

    }

#elif defined(APPLEOS)

   m_psem = SEM_FAILED;

   if(pstrName != NULL && *pstrName != '\0')
   {

      m_pmutex = NULL;

      SetLastError(0);

      m_pszName = strdup(string("/") + str_md5_dup(pstrName).Left(24-1));

      if ((m_psem = sem_open(m_pszName, O_CREAT|O_EXCL, 0644, 1)) != SEM_FAILED)
      {

         m_bOwner = true;

      }
      else
      {

         int err = errno;

         if (err != EEXIST)
            throw resource_exception(get_app());


         SetLastError(ERROR_ALREADY_EXISTS);

         m_bOwner = false;

         // We're not first.  Try again

         m_psem = sem_open(m_pszName, 0);

         if (m_psem == SEM_FAILED)
            throw resource_exception(get_app());;

      }

   }

#else

   m_key = 0;

   m_semid = -1;

   if(pstrName != NULL && *pstrName != '\0')
   {

      m_pmutex = NULL;

      if(str::begins_ci(pstrName, "Global"))
      {

         m_pszName = strdup(::file::path("/var/tmp") / pstrName);

      }
      else
      {

         m_pszName = strdup(::file::path(getenv("HOME")) / pstrName);

      }

      ::dir::mk(::dir::name(m_pszName));

      ::file_put_contents_dup(m_pszName, m_pszName);

      m_key = ftok(m_pszName, 1); //Generate a unique key or supply a value

      bool bAlreadyExists;

      get_existing:

      SetLastError(0);

      m_semid = semget(
                  m_key, // a unique identifier to identify semaphore set
                  1,  // number of semaphore in the semaphore set
                  0// permissions (rwxrwxrwx) on the new
                       //semaphore set and creation flag
                  );

      if(m_semid >= 0)
      {

         m_bOwner = false;

         bAlreadyExists = true;

         if(bAlreadyExists)
         {
                  SetLastError(ERROR_ALREADY_EXISTS);

         }

      }
      else
      {

         bAlreadyExists = false;

         m_semid = semget(
                     m_key, // a unique identifier to identify semaphore set
                     1,  // number of semaphore in the semaphore set
                     0777 | IPC_CREAT | IPC_EXCL// permissions (rwxrwxrwx) on the new
                          //semaphore set and creation flag
                     );

         if(m_semid == -1 && errno == EEXIST)
         {

            goto get_existing;

         }

      }

      if(m_semid < 0)
         throw resource_exception(get_app());

      semun semctl_arg;

      //set Initial value for the resource
      semctl_arg.val = 1; //Setting semval to 1

      semctl(m_semid, 0, SETVAL, semctl_arg);


   }

#endif

   else
   {

      pthread_mutexattr_t attr;

      pthread_mutexattr_init(&attr);

      pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

      pthread_mutex_init(&m_mutex, &attr);
      
#ifdef APPLEOS
      
      pthread_cond_init(&m_cond, NULL);
      
      m_count = 0;
      
      m_thread = 0;
      
#endif

   }

#endif

}


#ifdef WINDOWS

mutex::mutex(::aura::application * papp, const char * pstrName, void * h, bool bOwner) :
   object(papp),
   sync_object(pstrName)
{
   m_bOwner = bOwner;
   m_object = h;

}

mutex::mutex(const mutex & m):
object(m.get_app()),
sync_object(m.m_pszName)
{
   m_bOwner = false;
   m_object = m.m_object;

}

#else

#if defined(ANDROID) || defined(APPLEOS)

mutex::mutex(::aura::application * papp, const char * pstrName, sem_t * psem, bool bOwner) :
   object(papp),
   sync_object(pstrName)
{

   m_bOwner       = bOwner;
   m_pszName      = strdup(pstrName);
   m_psem         = psem;

}

mutex::mutex(const mutex & m):
   object(m.get_app()),
   sync_object(m.m_pszName)
{

   m_bOwner       = false;
   m_psem         = m.m_psem;
   m_mutex        = m.m_mutex;

}


#else

mutex::mutex(::aura::application * papp,const char * pstrName,key_t key,int32_t semid,bool bOwner):
   object(papp),
   sync_object(pstrName)
{

   m_bOwner       = bOwner;
   m_key          = key;
   m_semid        = semid;

}


mutex::mutex(const mutex & m):
   object(m.get_app()),
   sync_object(m.m_pszName)
{

   m_bOwner       = false;
   m_semid        = m.m_semid;
   m_mutex        = m.m_mutex;

}

#endif

#endif



mutex::~mutex()
{

#ifndef WINDOWS

#if defined(ANDROID) || defined(APPLEOS)

   if(m_psem != SEM_FAILED)
   {

      //if(m_bOwner)
      {
         sem_close(m_psem);
         sem_unlink(m_pszName);

      }

   }

#else

   if(m_semid >= 0)
   {

      if(m_bOwner)
      {

         semun ignored_argument;

         semctl(m_semid, 1, IPC_RMID , ignored_argument);

      }

   }

#endif

   else
   {

      pthread_mutex_destroy(&m_mutex);
      
#ifdef APPLEOS
      
      pthread_cond_destroy(&m_cond);
      
#endif

   }

#endif

}


bool mutex::already_exists()
{

   return m_bAlreadyExists;

}

//      ANDROID
//      int irc = pthread_mutex_lock_timeout_np(&m_mutex, duration.get_total_milliseconds());
//
//      if (!irc)
//      {
//
//         return wait_result(wait_result::Event0);
//
//      }
//      else if (irc != EBUSY)
//      {
//
//         return wait_result(wait_result::Failure);
//
//      }
//




#if !defined(WINDOWS)

wait_result mutex::wait(const duration & duration)
{

   if(duration.is_pos_infinity())
   {

      return wait();

   }

#if defined(APPLEOS)
   
   if(m_psem != SEM_FAILED)
   {
      
      uint32_t uiTimeout = duration.get_total_milliseconds();
      
      uint32_t uiStart = get_tick_count();
   
      while(true)
      {
         
         int rc = sem_trywait(m_psem);
         
         if(!rc)
         {
            
            return wait_result(wait_result::Event0);
            
         }
         else
         {
            
            int iError = errno;
            
            if(iError != EAGAIN)
            {
               
               return wait_result(wait_result::Failure);
               
            }
            
         }
         
         uint32_t uiElapsed = get_tick_count() - uiStart;
         
         if(uiElapsed >= uiTimeout)
         {
            
            return wait_result(wait_result::Timeout);
            
         }
         
         Sleep(MAX(1, MIN(1000, (uiTimeout - uiElapsed) / 50)));
         
      }
      
      return wait_result(wait_result::Failure);
      
   }
   else

#elif defined(ANDROID)

   if (m_psem != SEM_FAILED)
   {

      timespec delay;

      delay.tv_sec = duration.m_iSeconds;

      delay.tv_nsec = duration.m_iNanoseconds;

      int32_t ret = sem_timedwait(m_psem, &delay);

      if(ret == 0)
      {

         return wait_result(wait_result::Event0);

      }
      else
      {

         if (errno == ETIMEDOUT)
         {

            return wait_result(wait_result::Timeout);

         }

      }

      return wait_result(wait_result::Failure);


   }
   else

#else

   if(m_semid >= 0)
   {

      timespec timeout;

      timeout.tv_sec = duration.m_iSeconds;

      timeout.tv_nsec = duration.m_iNanoseconds;

      struct sembuf operation[1] ;

      operation[0].sem_op = -1; // Wait
      operation[0].sem_num = 0;
      operation[0].sem_flg = 0;

      int32_t ret = semtimedop(m_semid, operation, 1, &timeout);

      if(ret == 0)
      {

         return wait_result(wait_result::Event0);

      }
      else if(ret == -1)
      {

         if(errno == EAGAIN)
         {

            return wait_result(wait_result::Timeout);

         }

      }

      return wait_result(wait_result::Failure);

   }
   else

#endif
      
#ifdef APPLEOS
   {
   
      pthread_mutex_lock(&m_mutex);
      
      bool bFirst = true;
      
      while((m_thread != 0) && !pthread_equal(m_thread, pthread_self()))
      {
      
         timespec abs_time;
         
         if (bFirst)
         {
         
            clock_gettime(CLOCK_REALTIME, &abs_time);
            
            ::duration d;
            
            d.m_iSeconds = abs_time.tv_sec + duration.m_iSeconds;
            
            d.m_iNanoseconds = abs_time.tv_nsec + duration.m_iNanoseconds;
            
            d.normalize();
            
            abs_time.tv_sec = d.m_iSeconds;
            
            abs_time.tv_nsec = d.m_iNanoseconds;
            
            bFirst = false;
            
         }
         
         int rc = pthread_cond_timedwait(&m_cond, &m_mutex, &abs_time);
         
         if(rc == ETIMEDOUT)
         {
            
            pthread_mutex_unlock(&m_mutex);
            
            return wait_result(wait_result::Timeout);
            
         }
         else if(rc != 0)
         {
            
            return wait_result(wait_result::Failure);
            
         }

      }
      
      if (m_count++ == 0)
      {
      
         m_thread = pthread_self();
         
      }
      
      pthread_mutex_unlock(&m_mutex);
      
      return wait_result(wait_result::Event0);
      
   }
   
#else
   
   {

      timespec abs_time;

      clock_gettime(CLOCK_REALTIME, &abs_time);

      ::duration d;

      d.m_iSeconds = abs_time.tv_sec + duration.m_iSeconds;

      d.m_iNanoseconds = abs_time.tv_nsec + duration.m_iNanoseconds;

      d.normalize();
      
      abs_time.tv_sec = d.m_iSeconds;

      abs_time.tv_nsec = d.m_iNanoseconds;

      int rc = pthread_mutex_timedlock (&m_mutex, &abs_time);

      if (!rc)
      {

         return wait_result(wait_result::Event0);

      }
      else if(rc == ETIMEDOUT)
      {

         return wait_result(wait_result::Timeout);

      }
      else
      {

         return wait_result(wait_result::Failure);

      }

   }

#endif

}


bool mutex::lock()
{

#if defined(ANDROID) || defined(APPLEOS)

   if(m_psem != SEM_FAILED)
   {

      int32_t ret = sem_wait(m_psem);

      if(ret < 0)
      {

         return false;

      }

   }

#else

   if(m_semid >= 0)
   {

      struct sembuf operation[1] ;

      operation[0].sem_op = -1; // Wait
      operation[0].sem_num = 0;
      operation[0].sem_flg = 0;

      int32_t ret = semop(m_semid, operation, 1);

      if(ret < 0)
      {

         return false;

      }

   }

#endif
   
#ifdef APPLEOS
   
   else
   {
   
      pthread_mutex_lock(&m_mutex);
   
      while ((m_thread != 0) && !pthread_equal(m_thread, pthread_self()))
      {
         
         pthread_cond_wait(&m_cond, &m_mutex);
         
      }
      
      if(m_count++==0)
      {
         
         m_thread = pthread_self();
         
      }
      
      pthread_mutex_unlock(&m_mutex);
      
   }
   
#else

   else
   {

      int irc = pthread_mutex_lock(&m_mutex);

      if (irc)
      {

         return false;

      }

   }

#endif
   
   return true;

}


bool mutex::lock(const duration & duration)
{

   wait_result result = wait(duration);

   if (!result.signaled())
      return false;

   return true;

}


wait_result mutex::wait()
{

   if (!lock())
   {

      return wait_result(wait_result::Failure);

   }

   return wait_result(wait_result::Event0);

}

#endif


bool mutex::unlock()
{

#ifdef WINDOWS

   return ::ReleaseMutex(m_object) != FALSE;

#else

#if defined(ANDROID) || defined(APPLEOS)

   if(m_psem != SEM_FAILED)
   {

      return sem_post(m_psem) == 0;

   }

#else

   if(m_semid >= 0)
   {

      struct sembuf operation[1] ;

      operation[0].sem_op = 1; //Release the resource
      operation[0].sem_num = 0;
      operation[0].sem_flg = SEM_UNDO;

      return semop(m_semid, operation, 1) == 0;

   }

#endif
   
#ifdef APPLEOS
   
   else
   {
      
      pthread_mutex_lock(&m_mutex);
      
#ifdef _DEBUG
      
      ASSERT(pthread_equal(m_thread, pthread_self()));
      
#endif
      
      if (--m_count == 0)
      {
         
         m_thread = 0;
         
         pthread_cond_signal(&m_cond);
         
      }
      
      pthread_mutex_unlock(&m_mutex);
      
   }
   
#else

   else
   {

      return pthread_mutex_unlock(&m_mutex) == 0;

   }
   
#endif

#endif // _WIN32

}



mutex * mutex::open_mutex(::aura::application * papp,  const char * pstrName)
{

#ifdef WINDOWS

   HANDLE h = ::OpenMutexW(SYNCHRONIZE, FALSE, ::str::international::utf8_to_unicode(pstrName));

   if(h == NULL || h == INVALID_HANDLE_VALUE)
      return NULL;

   mutex * pmutex = canew(mutex(papp, pstrName, h));

   return pmutex;

#else

#if defined(ANDROID) || defined(APPLEOS)

   string strName = pstrName;

   sem_t * psem;

   int isCreator = 0;

   if((psem = sem_open(strName,O_CREAT | O_EXCL,0666,1)) != SEM_FAILED)
   {

      isCreator = 1;

   }
   else
   {

      psem = sem_open(strName,0);

      if(psem == SEM_FAILED)
      {

         //throw resource_exception(papp,"failed to create named mutex");
         throw resource_exception(papp);

      }

   }


   mutex * pmutex = new mutex(papp,strName, psem, isCreator);

   return pmutex;

#else

   if(pstrName == NULL || *pstrName == '\0')
      return NULL;

   string strName = pstrName;

   key_t key = ftok(strName, 0); //Generate a unique key or supply a value

   int32_t semid = semget(
               key, // a unique identifier to identify semaphore set
               1,  // number of semaphore in the semaphore set
               0666 // permissions (rwxrwxrwx) on the new
                    //semaphore set and creation flag
                  );
   if(semid < 0)
   {
      return NULL;
   }

   mutex * pmutex = new mutex(papp, strName, key, semid);

   return pmutex;

#endif

#endif

}


void wait_until_mutex_does_not_exist(const char * pszName)
{
   mutex * pmutex = new mutex(get_thread_app(), false, "Global\\::ca::fontopus::ca2_spa::7807e510-5579-11dd-ae16-0800200c7784");
   if(::GetLastError() == ERROR_ALREADY_EXISTS)
   {
      while(::GetLastError() == ERROR_ALREADY_EXISTS)
      {
         delete pmutex;
         Sleep(184);
         pmutex = new mutex(get_thread_app(), false, "Global\\::ca::fontopus::ca2_spa::7807e510-5579-11dd-ae16-0800200c7784");
      }
   }
   delete pmutex;
}


mutex * g_pmutexUiDestroyed = NULL;


CLASS_DECL_AURA mutex * get_ui_destroyed_mutex()
{

  return g_pmutexUiDestroyed;

}


#ifdef WINDOWSEX
null_dacl_security_attributes::null_dacl_security_attributes()
{


   ZERO(m_securityattributes);

   m_securityattributes.nLength = sizeof(m_securityattributes);

   m_securityattributes.bInheritHandle = FALSE; // object uninheritable

   // declare and initialize a security descriptor
   ZERO(m_securitydescriptor);

   bool bInitOk = InitializeSecurityDescriptor(&m_securitydescriptor,SECURITY_DESCRIPTOR_REVISION) != FALSE;

   if(bInitOk)
   {
      // give the security descriptor a Null Dacl
      // done using the  "TRUE, (PACL)NULL" here
      bool bSetOk = SetSecurityDescriptorDacl(&m_securitydescriptor,TRUE,(PACL)NULL,FALSE) != FALSE;

      if(bSetOk)
      {

         m_securityattributes.lpSecurityDescriptor = &m_securitydescriptor;

      }

   }

}
#endif


spaadmin_mutex::spaadmin_mutex(string strSuffix) :
#ifdef WINDOWSEX
mutex(NULL,false,"Global\\::ca2::fontopus::ccvotagus::" + process_platform_dir_name() + "::198411151951042219770204-11dd-ae16-0800200c7784" + strSuffix,&m_securityattributes)
, sync_object("Global\\::ca2::fontopus::ccvotagus::" + process_platform_dir_name() + "::198411151951042219770204-11dd-ae16-0800200c7784" + strSuffix)
#else
mutex(NULL,false,"Global\\::ca2::fontopus::ccvotagus::" + process_platform_dir_name() + "::198411151951042219770204-11dd-ae16-0800200c7784" + strSuffix)
, sync_object("Global\\::ca2::fontopus::ccvotagus::" + process_platform_dir_name() + "::198411151951042219770204-11dd-ae16-0800200c7784" + strSuffix)
#endif

{
}



spa_mutex::spa_mutex(string strSuffix) :
#ifdef WINDOWSEX
   mutex(NULL, false, "Global\\::ca2::fontopus::ccvotagus::spa::" + process_platform_dir_name() + "::198411151951042219770204-11dd-ae16-0800200c7784" + strSuffix, &m_securityattributes)
   , sync_object("Global\\::ca2::fontopus::ccvotagus::spa::" + process_platform_dir_name() + "::198411151951042219770204-11dd-ae16-0800200c7784" + strSuffix)
#else
   mutex(NULL, false, "Global\\::ca2::fontopus::ccvotagus::spa::" + process_platform_dir_name() + "::198411151951042219770204-11dd-ae16-0800200c7784" + strSuffix)
   , sync_object("Global\\::ca2::fontopus::ccvotagus::spa::" + process_platform_dir_name() + "::198411151951042219770204-11dd-ae16-0800200c7784" + strSuffix)
#endif

{
}
