#pragma once


#ifdef _WINDOWS
#if defined(__CA2__DLL) || defined(SPALIB_DLL)
   #define MUTEX_LOCK_DECL  _declspec(dllexport)
#else
   #define MUTEX_LOCK_DECL  _declspec(dllimport)
#endif
#else
   #define MUTEX_LOCK_DECL
#endif



class MUTEX_LOCK_DECL mutex_lock
{
public:

   
   simple_mutex *    m_pmutex;


   mutex_lock(simple_mutex * pmutex);
   ~mutex_lock();

   
};

