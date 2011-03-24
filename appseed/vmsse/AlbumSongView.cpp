// AlbumSongView.cpp : Implementation of CAlbumSongView
#include "stdafx.h"
#include "../vmsp/resource.h"
#include "Vmsse.h"
#include "AlbumSongView.h"
#include "AlbumSongList.h"
#include "AlbumSongMainWnd.h"

#include "DataCentral.h"
#include "DBLong.h"

#include "VmsseDLL.h" 

/////////////////////////////////////////////////////////////////////////////
// CAlbumSongView

CAlbumSongView::CAlbumSongView()
{
    InternalAddRef();
    m_pipwnd = NULL;
    //AFX_MANAGE_STATE(AfxGetStaticModuleState())
    
    //UpdateList();
    
    //        LPUNKNOWN lpunk = NULL;
//      if(S_OK == OuterQueryInterface(IID_IUnknown, (void**)&lpunk))
//    {
  //      m_spShellView.CoCreateInstance(IID_IShellView, lpunk );
    //}
}

CAlbumSongView::~CAlbumSongView()
{
    InternalRelease();
}

HRESULT STDMETHODCALLTYPE CAlbumSongView::GetWindow( 
        /* [out] */ HWND *phwnd)
{
     AFX_MANAGE_STATE(AfxGetStaticModuleState())
     *phwnd = m_pipwnd->GetSafeHwnd();
     return S_OK;
}
    
HRESULT STDMETHODCALLTYPE CAlbumSongView::ContextSensitiveHelp( 
        /* [in] */ BOOL fEnterMode)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CAlbumSongView::TranslateAccelerator(tagMSG * pmsg)
{
	return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE CAlbumSongView::EnableModeless(BOOL fEnable)
{
	return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE CAlbumSongView::UIActivate(UINT uState)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    if(uState == SVUIA_ACTIVATE_FOCUS)
    {
        m_pipwnd->SetFocus();
		m_pipwnd->Layout();
    }
    else if(uState == SVUIA_DEACTIVATE )
    {
        if(m_pipwnd->m_pmenuShared != NULL)
        {
            m_spshbrowser->RemoveMenusSB(m_pipwnd->m_pmenuShared->GetSafeHmenu());
        }

    }
	return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE CAlbumSongView::Refresh()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    m_pipwnd->m_pfulllist->UpdateList();
    //return E_NOTIMPL;
	return S_OK;
}
HRESULT STDMETHODCALLTYPE CAlbumSongView::CreateViewWindow(IShellView * psvPrevious, LPCFOLDERSETTINGS pfs, IShellBrowser * psb, RECT * prcView, HWND * phwnd)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (prcView == NULL)
		return E_POINTER;
		
	if (phwnd == NULL)
		return E_POINTER;

    m_spshbrowser.Attach(psb);
    //m_spshbrowser->AddRef();

    
    m_spshbrowser->QueryInterface(IID_IOleWindow, (void**) &m_spolewnd);

    HWND hwnd = NULL;
    m_spolewnd->GetWindow(&hwnd);

    CWnd * pwnd = CWnd::FromHandle(hwnd);

    CRect clientRect = prcView;

    pwnd->GetClientRect(clientRect);
    
    m_pipwnd = new CAlbumSongMainWnd(this);


    m_pipwnd->Create(
        WS_VISIBLE | WS_CHILD,
        clientRect,
        pwnd,
        IDC_LIST_FULL,
        NULL);

  //  m_pfulllist->Create(WS_CHILD | WS_VISIBLE, *prcView, pwnd, 12);
	CDBCentral *pdb = DB();


    *phwnd = (HWND) m_pipwnd->GetSafeHwnd();
	
    m_pipwnd->SetWindowPos(&CWnd::wndTop, prcView->left, prcView->top,
                 prcView->right-prcView->left, prcView->bottom-prcView->top,
                 SWP_NOZORDER|SWP_SHOWWINDOW);

	m_pipwnd->Layout();

	InsertMenus();
    
//    m_pfulllist->UpdateList();

	return S_OK;
}
HRESULT STDMETHODCALLTYPE CAlbumSongView::DestroyViewWindow ()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    if(m_pipwnd != NULL)
    {
        if(::IsWindow(m_pipwnd->GetSafeHwnd()))
            m_pipwnd->DestroyWindow();
        //delete m_pfulllist;
        m_pipwnd = NULL;
        m_spolewnd.Release();
    }

	return S_OK;
}
HRESULT STDMETHODCALLTYPE CAlbumSongView::GetCurrentInfo (FOLDERSETTINGS * pfs)
{
	if (pfs == NULL)
		return E_POINTER;
		
	return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE CAlbumSongView::AddPropertySheetPages(DWORD dwReserved, LPFNSVADDPROPSHEETPAGE pfn, LPARAM lParam)
{
	return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE CAlbumSongView::SaveViewState()
{
	return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE CAlbumSongView::SelectItem(LPCITEMIDLIST pidlItem, SVSIF uFlags)
{
	return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE CAlbumSongView::GetItemObject(UINT uItem, REFIID riid, void ** ppv)
{
	if (ppv == NULL)
		return E_POINTER;
		
	return E_NOTIMPL;
}

	HRESULT STDMETHODCALLTYPE CAlbumSongView::GetPath(LPWSTR pszFile, INT cch,  WIN32_FIND_DATAW  * pfd, DWORD fFlags)
	{
		if (pszFile == NULL)
			return E_POINTER;
			
		if (pfd == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE CAlbumSongView::GetIDList(LPITEMIDLIST * ppidl)
	{
        AFX_MANAGE_STATE(AfxGetStaticModuleState())
		if (ppidl == NULL)
			return E_POINTER;
        HRESULT hr;
        CComPtr<IMalloc> spMalloc;
        if(FAILED(hr = SHGetMalloc(&spMalloc)))
            return hr;
        SHITEMID shii;
        ULONG cbID = sizeof(shii.cb) + sizeof(DWORD);
        ULONG cb = cbID * m_pipwnd->m_pfulllist->m_dwaQueryKeys.GetSize();
        LPITEMIDLIST lpidl = (LPITEMIDLIST) spMalloc->Alloc(cb);
        LPITEMIDLIST lpidli = lpidl;
        int i = 0;
        while(i <  m_pipwnd->m_pfulllist->m_dwaQueryKeys.GetSize())
        {
            lpidli->mkid.cb = 4;
            memcpy(lpidli->mkid.abID, & m_pipwnd->m_pfulllist->m_dwaQueryKeys.ElementAt(i), sizeof(DWORD));
            lpidli = (LPITEMIDLIST) (((LPBYTE) lpidli) + cbID);
            i++;
        }

        *ppidl = lpidl;
			
		return S_OK;
	}
	HRESULT STDMETHODCALLTYPE CAlbumSongView::SetIDList(LPCITEMIDLIST pidl)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE CAlbumSongView::GetDescription(LPWSTR pszName, INT cch)
	{
		if (pszName == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE CAlbumSongView::SetDescription(LPCWSTR pszName)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE CAlbumSongView::GetWorkingDirectory(LPWSTR pszDir, INT cch)
	{
		if (pszDir == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE CAlbumSongView::SetWorkingDirectory(LPCWSTR pszDir)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE CAlbumSongView::GetArguments(LPWSTR pszArgs, INT cch)
	{
		if (pszArgs == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE CAlbumSongView::SetArguments(LPCWSTR pszArgs)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE CAlbumSongView::GetHotkey(USHORT * pwHotkey)
	{
		if (pwHotkey == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE CAlbumSongView::SetHotkey(USHORT wHotkey)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE CAlbumSongView::GetShowCmd(INT * piShowCmd)
	{
		if (piShowCmd == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE CAlbumSongView::SetShowCmd(INT iShowCmd)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE CAlbumSongView::GetIconLocation(LPWSTR pszIconPath, INT cch, INT * piIcon)
	{
		if (pszIconPath == NULL)
			return E_POINTER;
			
		if (piIcon == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE CAlbumSongView::SetIconLocation(LPCWSTR pszIconPath, INT iIcon)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE CAlbumSongView::SetRelativePath(LPCWSTR pszPathRel, DWORD dwReserved)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE CAlbumSongView::Resolve(HWND hwnd, DWORD fFlags)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE CAlbumSongView::SetPath(LPCWSTR pszFile)
	{
		return E_NOTIMPL;
	}

VMSRESULT CAlbumSongView::UpdateList()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return m_pipwnd->UpdateList();
}


STDMETHODIMP CAlbumSongView::get_ShellBrowser(IShellBrowser ** pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

    *pVal = m_spshbrowser;
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CAlbumSongView::put_ShellBrowser(IShellBrowser * newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

    m_spshbrowser.Attach(newVal);
	// TODO: Add your implementation code here

	return S_OK;
}

bool CAlbumSongView::InsertMenus()
{
return 	m_pipwnd->InsertMenus();

}
