#pragma once


#include "ansios_file.h"
#include "ansios_thread.h"
#include "ansios_multithreading.h"


extern int_bool (* g_messageboxa)(oswindow window, const char * psz, const char * pszTitle, uint32_t uiFlags);


#ifdef cplusplus

template < class T >
class thread_pointer
{
public:


   pthread_key_t           key;

   thread_pointer(const char * pszName)
   {

      UNREFERENCED_PARAMETER(pszName);

      pthread_key_create(&key, NULL);

   }


   operator T *()
   {

      return (T *)pthread_getspecific(key);

   }

   T * operator ->()
   {
      return operator T *();
   }

   thread_pointer & operator = (T * pt)
   {

      pthread_setspecific(key, pt);

      return *this;

   }

};


template < class T >
class thread_var
{
public:

   pthread_key_t           key;

   thread_pointer(const char * pszName)
   {

      UNREFERENCED_PARAMETER(pszName);

      pthread_key_create(&key, NULL);

   }


   operator T ()
   {

      return (T)pthread_getspecific(threadSpecificKey)(key);

   }

   thread_var & operator = (T t)
   {

      pthread_setspecific(threadSpecificKey, (void *) (int_ptr) t);

      return *this;

   }


};


#endif



