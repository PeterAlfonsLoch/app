#pragma once

class sync_object_base;
template < typename THANDLE >
class sync_object;
class semaphore;
class mutex;
class CEvent;
class critical_section;
class CSingleLock;
class CMultiLock;

#include "sync_object.h"

#include "semaphore.h"

#include "mutex.h"

#include "event.h"


class CLASS_DECL_ca critical_section : 
   public sync_object < HANDLE >
{
public:


   critical_section();


#if !core_level_1
   using sync_object < HANDLE > ::Unlock;
#endif

   operator CRITICAL_SECTION*();
   CRITICAL_SECTION m_sect;

   BOOL Unlock();
   BOOL Lock();
   BOOL Lock(DWORD dwTimeout);

   virtual ~critical_section();

private:
   BOOL Init();
};

class CLASS_DECL_ca CSingleLock
{
protected:
   
   
   sync_object_base* m_pObject;
   HANDLE  m_hObject;
   BOOL    m_bAcquired;


public:

   
   explicit CSingleLock(sync_object_base * pObject, BOOL bInitialLock = FALSE);
   ~CSingleLock();

   BOOL Lock(DWORD dwTimeOut = INFINITE);
   BOOL Unlock();
   BOOL Unlock(LONG lCount, LPLONG lPrevCount = NULL);
   BOOL IsLocked();


};

class CLASS_DECL_ca CMultiLock :
   virtual public ::radix::object
{
protected:


   HANDLE  m_hPreallocated[8];
   BOOL    m_bPreallocated[8];

   sync_object_base* const * m_ppObjectArray;
   HANDLE* m_pHandleArray;
   BOOL*   m_bLockedArray;
   DWORD   m_dwCount;


public:

   
   CMultiLock(sync_object_base* ppObjects[], DWORD dwCount, BOOL bInitialLock = FALSE);
   ~CMultiLock();

   DWORD Lock(DWORD dwTimeOut = INFINITE, BOOL bWaitForAll = TRUE, DWORD dwWakeMask = 0);
   BOOL Unlock();
   BOOL Unlock(LONG lCount, LPLONG lPrevCount = NULL);
   BOOL IsLocked(DWORD dwItem);

};

#ifdef _AFX_ENABLE_INLINES
#define _AFXMT_INLINE inline
#include "multithreading.inl"
#undef _AFXMT_INLINE
#endif

#include "manual_reset_event.h"

#include "ca/ca_lock.h"

#include <Winsvc.h>

// services
#include "service_status.h"
#include "thread_pool.h"
#include "service_base.h"
#include "plain_service.h"