// This is ca2 API library.
//
//
//
//
//
//
//
//

#include "framework.h"



#pragma warning(disable: 4706) // assignment within conditional

/////////////////////////////////////////////////////////////////////////////
// global thread protection

#ifdef _MT

__STATIC_DATA WINBOOL _afxCriticalInit = 0;   // set _afxGlobalLock, _afxTempLock init

// _afxResourceLock and _afxLockInit are used to lock each ca2 API global resource
__STATIC_DATA CRITICAL_SECTION _afxResourceLock[CRIT_MAX] = { { 0 } };
__STATIC_DATA CRITICAL_SECTION _afxLockInitLock = { 0 };
__STATIC_DATA WINBOOL _afxLockInit[CRIT_MAX] = { 0 };
#ifdef DEBUG
__STATIC_DATA WINBOOL _afxResourceLocked[CRIT_MAX] = { 0 };
#endif

WINBOOL AfxCriticalInit()
{
   // Note: this must be initialized with only one thread running
   if (!_afxCriticalInit)
   {
      // now we are about to be initialized
      VERIFY(++_afxCriticalInit);
      InitializeCriticalSection(&_afxLockInitLock);
   }
   return _afxCriticalInit;
}

void AfxCriticalTerm()
{
   if (_afxCriticalInit)
   {
      VERIFY(!--_afxCriticalInit);

      // delete helper critical sections
      DeleteCriticalSection(&_afxLockInitLock);

      // delete specific resource critical sections
      for (int32_t i = 0; i < CRIT_MAX; i++)
      {
#ifdef DEBUG
         ASSERT(!_afxResourceLocked[i]);
#endif
         if (_afxLockInit[i])
         {
            DeleteCriticalSection(&_afxResourceLock[i]);
            VERIFY(!--_afxLockInit[i]);
         }
      }
   }
}

void AfxLockGlobals(int32_t nLockType)
{
   ENSURE((UINT)nLockType < CRIT_MAX);

   // intialize global state, if necessary
   if (!_afxCriticalInit)
   {
      AfxCriticalInit();
      ASSERT(_afxCriticalInit);
   }

   // initialize specific resource if necessary
   if (!_afxLockInit[nLockType])
   {
      EnterCriticalSection(&_afxLockInitLock);
      if (!_afxLockInit[nLockType])
      {
         InitializeCriticalSection(&_afxResourceLock[nLockType]);
         VERIFY(++_afxLockInit[nLockType]);
      }
      LeaveCriticalSection(&_afxLockInitLock);
   }

   // lock specific resource
   EnterCriticalSection(&_afxResourceLock[nLockType]);
#ifdef DEBUG
   ASSERT(++_afxResourceLocked[nLockType] > 0);
#endif
}

void AfxUnlockGlobals(int32_t nLockType)
{
   ASSERT(_afxCriticalInit);
   ENSURE((UINT)nLockType < CRIT_MAX);

   // unlock specific resource
   ASSERT(_afxLockInit[nLockType]);
#ifdef DEBUG
   ASSERT(--_afxResourceLocked[nLockType] >= 0);
#endif
   LeaveCriticalSection(&_afxResourceLock[nLockType]);
}

#endif

/////////////////////////////////////////////////////////////////////////////
