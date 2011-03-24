// AtlVms.cpp : Implementation of CVmp
#include "stdafx.h"
#include "VmpApp.h"
#include "Vmp.h"

#include "DWArray.h"
#include "StrArray.h"

//extern CVmpApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CVmp

STDMETHODIMP CVmp::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IVmsPlayer
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
        if (::IsEqualGUIDBase((REFGUID) *arr[i], (REFGUID) riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CVmp::ReserveSongs(VARIANT * pvar)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState() )

    //AfxMessageBox("ReserveSongs");

	// TODO: Add your implementation code here
    //AfxDebugBreak();
    ASSERT(pvar->vt == (VT_ARRAY | VT_BSTR));

    CStrArray  * pstra=new CStrArray;

    pstra->Copy(pvar);
    
    CVmpApp * pApp = (CVmpApp *) AfxGetApp();
    ASSERT(pApp != NULL);

    pApp->m_evInitialized.Lock();

    pApp->PostThreadMessage(WM_USER, 23, (LPARAM) pstra);

	return S_OK;
}
