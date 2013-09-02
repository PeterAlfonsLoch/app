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

_AFXMT_INLINE int_bool semaphore::Unlock()
   { return Unlock(1, NULL); }

_AFXMT_INLINE int_bool CEvent::SetEvent()
   { ASSERT(m_hObject != NULL); return ::SetEvent(m_hObject); }
_AFXMT_INLINE int_bool CEvent::PulseEvent()
   { ASSERT(m_hObject != NULL); return ::PulseEvent(m_hObject); }
_AFXMT_INLINE int_bool CEvent::ResetEvent()
   { ASSERT(m_hObject != NULL); return ::ResetEvent(m_hObject); }

_AFXMT_INLINE CSingleLock::~CSingleLock()
   { Unlock(); }
_AFXMT_INLINE int_bool CSingleLock::IsLocked()
   { return m_bAcquired; }

_AFXMT_INLINE int_bool CMultiLock::IsLocked(DWORD dwObject)
   { ASSERT(dwObject < m_dwCount);
       return m_bLockedArray[dwObject]; }

_AFXMT_INLINE int_bool critical_section::Init()
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
      int_bool bSuccess;

      bSuccess = Init();
      if (!bSuccess)
         throw memory_exception(get_app());
   }

_AFXMT_INLINE critical_section::operator CRITICAL_SECTION*()
   { return (CRITICAL_SECTION*) &m_sect; }
_AFXMT_INLINE critical_section::~critical_section()
   { ::DeleteCriticalSection(&m_sect); }
_AFXMT_INLINE int_bool critical_section::Lock()
   {   
      __try
      {
         ::EnterCriticalSection(&m_sect); 
      }
      __except(STATUS_NO_MEMORY == GetExceptionCode())
      {
         throw memory_exception(get_app());
      }
      return TRUE; 
   }
_AFXMT_INLINE int_bool critical_section::Lock(DWORD dwTimeout)
   { ASSERT(dwTimeout == INFINITE); (void)dwTimeout; return Lock(); }
_AFXMT_INLINE int_bool critical_section::Unlock()
   { ::LeaveCriticalSection(&m_sect); return TRUE; }

#endif //_AFXMT_INLINE
