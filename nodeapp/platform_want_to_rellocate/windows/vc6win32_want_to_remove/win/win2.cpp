#include "StdAfx.h"

// Global helper functions
 CLASS_DECL_VMSWIN application * AfxGetApp()
{ return dynamic_cast < application * > (afxCurrentWinApp); }

 CLASS_DECL_VMSWIN HINSTANCE AfxGetInstanceHandle()
	{ ASSERT(afxCurrentInstanceHandle != NULL);
		return afxCurrentInstanceHandle; }
 CLASS_DECL_VMSWIN HINSTANCE AfxGetResourceHandle()
	{ ASSERT(afxCurrentResourceHandle != NULL);
		return afxCurrentResourceHandle; }
 CLASS_DECL_VMSWIN void AfxSetResourceHandle(HINSTANCE hInstResource)
	{ ASSERT(hInstResource != NULL); afxCurrentResourceHandle = hInstResource; }
 CLASS_DECL_VMSWIN const char * AfxGetAppName()
	{ ASSERT(afxCurrentAppName != NULL); return afxCurrentAppName; }
 CLASS_DECL_VMSWIN ::user::interaction * AfxGetMainWnd()
{ thread* pThread = Application.GetThread();
		return pThread != NULL ? pThread->GetMainWnd() : NULL; }

 CLASS_DECL_VMSWIN BOOL AfxGetAmbientActCtx()
	{ 	return afxAmbientActCtx; }
 CLASS_DECL_VMSWIN void AfxSetAmbientActCtx(BOOL bSet)
	{  afxAmbientActCtx = bSet; }



#ifdef _ApplicationFrameworkDLL
// AFX_MAINTAIN_STATE functions
 AFX_MAINTAIN_STATE::AFX_MAINTAIN_STATE(AFX_MODULE_STATE* pNewState)
	{  m_pPrevModuleState = AfxSetModuleState(pNewState); }
#endif

// AFX_MAINTAIN_STATE2 functions
 AFX_MAINTAIN_STATE2::~AFX_MAINTAIN_STATE2()
{
#ifdef _ApplicationFrameworkDLL
	// Not a good place to report errors here, so just be safe
	if(m_pThreadState)
	{
		m_pThreadState->m_pModuleState = m_pPrevModuleState;
	}
#endif

/*	if (m_bValidActCtxCookie)
	{
		BOOL bRet;
		bRet = AfxDeactivateActCtx(0, m_ulActCtxCookie);
		ASSERT(bRet == TRUE);
	}*/
}

