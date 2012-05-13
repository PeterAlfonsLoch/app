// This is ca2 API library.
// 
// 
//
// 
// 
// 
// 
// 

// Inlines for AFXMT.H

#pragma once

#ifdef _AFXMT_INLINE

_AFXMT_INLINE BOOL semaphore::Unlock()
   { return Unlock(1, NULL); }

_AFXMT_INLINE BOOL CEvent::SetEvent()
   { ASSERT(m_hObject != NULL); return ::SetEvent(m_hObject); }
_AFXMT_INLINE BOOL CEvent::PulseEvent()
   { ASSERT(m_hObject != NULL); return ::PulseEvent(m_hObject); }
_AFXMT_INLINE BOOL CEvent::ResetEvent()
   { ASSERT(m_hObject != NULL); return ::ResetEvent(m_hObject); }

_AFXMT_INLINE CSingleLock::~CSingleLock()
   { Unlock(); }
_AFXMT_INLINE BOOL CSingleLock::IsLocked()
   { return m_bAcquired; }

_AFXMT_INLINE BOOL CMultiLock::IsLocked(DWORD dwObject)
   { ASSERT(dwObject < m_dwCount);
       return m_bLockedArray[dwObject]; }

_AFXMT_INLINE BOOL critical_section::Init()
{
   __try
   {
      ::InitializeCriticalSection(&m_sect);
   }
   __except(STATUS_NO_MEMORY == GetExceptionCode())
   {
      return FALSE;
   }

   return TRUE;
}

_AFXMT_INLINE critical_section::critical_section() : sync_object < HANDLE > (NULL)
   {    
      BOOL bSuccess;

      bSuccess = Init();
      if (!bSuccess)
         throw memory_exception();
   }

_AFXMT_INLINE critical_section::operator CRITICAL_SECTION*()
   { return (CRITICAL_SECTION*) &m_sect; }
_AFXMT_INLINE critical_section::~critical_section()
   { ::DeleteCriticalSection(&m_sect); }
_AFXMT_INLINE BOOL critical_section::Lock()
   {   
      __try
      {
         ::EnterCriticalSection(&m_sect); 
      }
      __except(STATUS_NO_MEMORY == GetExceptionCode())
      {
         throw memory_exception();
      }
      return TRUE; 
   }
_AFXMT_INLINE BOOL critical_section::Lock(DWORD dwTimeout)
   { ASSERT(dwTimeout == INFINITE); (void)dwTimeout; return Lock(); }
_AFXMT_INLINE BOOL critical_section::Unlock()
   { ::LeaveCriticalSection(&m_sect); return TRUE; }

#endif //_AFXMT_INLINE
