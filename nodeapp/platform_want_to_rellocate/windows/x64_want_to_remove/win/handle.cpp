#include "StdAfx.h"

void CLASS_DECL_VMSWIN AfxLockTempMaps()
{
	AFX_MODULE_THREAD_STATE* pState = AfxGetModuleThreadState();
	++pState->m_nTempMapLock;
}

BOOL CLASS_DECL_VMSWIN AfxUnlockTempMaps(BOOL bDeleteTemps)
{
	AFX_MODULE_THREAD_STATE* pState = AfxGetModuleThreadState();
	if (pState->m_nTempMapLock != 0 && --pState->m_nTempMapLock == 0)
	{
		if (bDeleteTemps)
		{
			// clean up temp objects
			pState->m_pmapHGDIOBJ->delete_temp();
			pState->m_pmapHDC->delete_temp();
			pState->m_pmapHWND->delete_temp();
		}

#ifndef _AFX_PORTABLE
		application* pApp = &Application;
		_AFX_THREAD_STATE* pThreadState = _afxThreadState.GetDataNA();
		if( pThreadState != NULL )
		{
			// restore safety pool after temp objects destroyed
			if (pApp != NULL &&
				 (pThreadState->m_pSafetyPoolBuffer == NULL ||
				 _msize(pThreadState->m_pSafetyPoolBuffer) < pApp->m_nSafetyPoolSize) &&
				pApp->m_nSafetyPoolSize != 0)
			{
				// attempt to restore the safety pool to its max size
				size_t nOldSize = 0;
				if (pThreadState->m_pSafetyPoolBuffer != NULL)
				{
					nOldSize = _msize(pThreadState->m_pSafetyPoolBuffer);
					free(pThreadState->m_pSafetyPoolBuffer);
				}

				// undo handler trap for the following allocation
				BOOL bEnable = AfxEnableMemoryTracking(FALSE);
				try
				{
					pThreadState->m_pSafetyPoolBuffer = malloc(pApp->m_nSafetyPoolSize);
					if (pThreadState->m_pSafetyPoolBuffer == NULL)
					{
						TRACE(traceAppMsg, 0, "Warning: failed to reclaim %d bytes for memory safety pool.\n",
							pApp->m_nSafetyPoolSize);
						// at least get the old buffer back
						if (nOldSize != 0)
						{
							//get it back
							pThreadState->m_pSafetyPoolBuffer = malloc(nOldSize);
							ASSERT(pThreadState->m_pSafetyPoolBuffer != NULL);
						}
					}
				}
				catch( base_exception * )
				{
					AfxEnableMemoryTracking(bEnable);
					throw;
				}
				AfxEnableMemoryTracking(bEnable);
			}
		}
#endif  // !_AFX_PORTABLE
	}

	// return TRUE if temp maps still locked
	return pState->m_nTempMapLock != 0;
}

namespace win
{
/////////////////////////////////////////////////////////////////////////////

void PASCAL window::DeleteTempMap()
{
	hwnd_map* pMap = AfxGetModuleThreadState()->m_pmapHWND;
	pMap->delete_temp();
}


void PASCAL graphics::DeleteTempMap()
{
	hdc_map* pMap = AfxGetModuleThreadState()->m_pmapHDC;
	pMap->delete_temp();
}

void PASCAL graphics_object::DeleteTempMap()
{
	hgdiobj_map* pMap = AfxGetModuleThreadState()->m_pmapHGDIOBJ;
	pMap->delete_temp();
}

} // namespace win
