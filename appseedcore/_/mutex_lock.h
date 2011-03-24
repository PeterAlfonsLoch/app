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



typedef void *HANDLE;


class MUTEX_LOCK_DECL mutex_lock
{
protected:

   
   HANDLE m_hmutex;


public:


   mutex_lock(HANDLE hmutex);
   ~mutex_lock();

   
};

