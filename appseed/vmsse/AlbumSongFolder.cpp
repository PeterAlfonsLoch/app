// AlbumSongFolder.cpp : Implementation of CAlbumSongFolder
#include "stdafx.h"
#include "Vmsse.h"
#include "VmsseApp.h"
#include "AlbumSongFolder.h"

#include "AlbumSongView.h"

/////////////////////////////////////////////////////////////////////////////
// CAlbumSongFolder

CAlbumSongFolder::CAlbumSongFolder()
{
    InternalAddRef();

}

CAlbumSongFolder::~CAlbumSongFolder()
{
    InternalRelease();
}


HRESULT STDMETHODCALLTYPE CAlbumSongFolder::CreateViewObject( 
    /* [in] */ HWND hwndOwner,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv)
{
	if (ppv == NULL)
		return E_POINTER;
	CVmsseApp * papp = (CVmsseApp *) AfxGetApp();
	papp->m_evInit.Lock();
	if(!papp->AppGetDB()->IsWorking())
		return E_FAIL;
    CComPtr<IAlbumSongView> spasv;
    HRESULT hr;
    if (riid == IID_IShellView)
    {
        hr = spasv.CoCreateInstance(CLSID_AlbumSongView, NULL, CLSCTX_INPROC_SERVER);
        if(FAILED(hr))
            return hr;
    }
    else
    {
        return(E_NOINTERFACE);
    }
    if (!spasv)
    {
        return(E_OUTOFMEMORY);
    }
    
    hr = spasv->QueryInterface(riid, ppv);
    spasv.Release();

    return hr;
}
//HRESULT STDMETHODCALLTYPE CAlbumSongFolder::GetDisplayNameOf(wirePIDL pidl, ULONG uFlags, STRRET * pNameRet)
HRESULT STDMETHODCALLTYPE CAlbumSongFolder::GetDisplayNameOf( 
        /* [in] */ LPCITEMIDLIST pidl,
        /* [in] */ SHGDNF uFlags,
        /* [out] */ STRRET *pName)
{
	if (pName == NULL)
		return E_POINTER;

//            uFlags = SHGDN_NORMAL;
//          uFlags |= 
    
    //int cb = strlen(lpsz) + sizeof(pidl->mkid.cb);
    //*pidl = malloc(cb);
    //pidl->mkid.cb = cb;
    //strcpy(&pidl->mkid.abID, lpsz);

    //char lpsz[] = "Meus Karaokês";

    strcpy(pName->cStr, "Meus Karaokês");
    pName->uType = STRRET_CSTR;
		
	return NOERROR;
}


STDMETHODIMP CAlbumSongFolder::GetIconLocation( 
    UINT uFlags,
    LPTSTR szIconFile,
    UINT cchMax,
    LPINT piIndex,
    LPUINT puFlags)
{
    return S_OK;
}

STDMETHODIMP CAlbumSongFolder::Extract(
    LPCTSTR pszFile, 
    UINT nIconIndex, 
    HICON *phiconLarge,  
    HICON *phiconSmall,
    UINT nIconSize)
{
    HINSTANCE hinst = GetModuleHandle(pszFile);
    
    if(hinst == NULL)
        return E_FAIL;

    HICON hIcon = (HICON) LoadImage(hinst,
        MAKEINTRESOURCE(nIconIndex),
        IMAGE_ICON,
        16, 16,
        0);

    *phiconSmall = hIcon;


    hIcon = (HICON) LoadImage(hinst,
        MAKEINTRESOURCE(nIconIndex),
        IMAGE_ICON,
        0, 0,
        LR_DEFAULTSIZE);

    *phiconLarge = hIcon;

    return S_OK;
}

HRESULT STDMETHODCALLTYPE CAlbumSongFolder::ParseDisplayName( 
    /* [in] */ HWND hwnd,
    /* [in] */ LPBC pbc,
    /* [string][in] */ LPOLESTR pszDisplayName,
    /* [out] */ ULONG *pchEaten,
    /* [out] */ LPITEMIDLIST *ppidl,
    /* [unique][out][in] */ ULONG *pdwAttributes)
{
   		if (pchEaten == NULL)
			return E_POINTER;
			
		if (ppidl == NULL)
			return E_POINTER;
			
		if (pdwAttributes == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;

}

HRESULT STDMETHODCALLTYPE CAlbumSongFolder::EnumObjects( 
    /* [in] */ HWND hwnd,
    /* [in] */ SHCONTF grfFlags,
    /* [out] */ IEnumIDList **ppenumIDList) 
	{
		if (ppenumIDList == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}

HRESULT STDMETHODCALLTYPE CAlbumSongFolder::BindToObject( 
    /* [in] */ LPCITEMIDLIST pidl,
    /* [in] */ LPBC pbc,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv) 
	{
		if (ppv == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}

HRESULT STDMETHODCALLTYPE CAlbumSongFolder::BindToStorage( 
    /* [in] */ LPCITEMIDLIST pidl,
    /* [in] */ LPBC pbc,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv) 
	{
		if (ppv == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}

HRESULT STDMETHODCALLTYPE CAlbumSongFolder::CompareIDs( 
    /* [in] */ LPARAM lParam,
    /* [in] */ LPCITEMIDLIST pidl1,
    /* [in] */ LPCITEMIDLIST pidl2) 
	{
		return E_NOTIMPL;
	}

//HRESULT STDMETHODCALLTYPE CAlbumSongFolder::CreateViewObject( 
  //  /* [in] */ HWND hwndOwner,
    ///* [in] */ REFIID riid,
    ///* [iid_is][out] */ void **ppv) 

HRESULT STDMETHODCALLTYPE CAlbumSongFolder::GetAttributesOf( 
    /* [in] */ UINT cidl,
    /* [size_is][in] */ LPCITEMIDLIST *apidl,
    /* [out][in] */ SFGAOF *rgfInOut) 
	{
		if (rgfInOut == NULL)
			return E_POINTER;

//		ITEMIDLIST structures, each of which uniquely identifies a file object relative to the parent folder. Each ITEMIDLIST structure must contain exactly one SHITEMID
            
		return E_NOTIMPL;
	}

HRESULT STDMETHODCALLTYPE CAlbumSongFolder::GetUIObjectOf( 
    /* [in] */ HWND hwndOwner,
    /* [in] */ UINT cidl,
    /* [size_is][in] */ LPCITEMIDLIST *apidl,
    /* [in] */ REFIID riid,
    /* [unique][out][in] */ UINT *rgfReserved,
    /* [iid_is][out] */ void **ppv) 
	{
		if (rgfReserved == NULL)
			return E_POINTER;
			
		if (ppv == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}



HRESULT STDMETHODCALLTYPE CAlbumSongFolder::SetNameOf( 
    /* [in] */ HWND hwnd,
    /* [in] */ LPCITEMIDLIST pidl,
    /* [string][in] */ LPCOLESTR pszName,
    /* [in] */ SHGDNF uFlags,
    /* [out] */ LPITEMIDLIST *ppidlOut) 
	{
		if (ppidlOut == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}

HRESULT STDMETHODCALLTYPE CAlbumSongFolder::Initialize( 
    /* [in] */ LPCITEMIDLIST pidl)
{
    return NOERROR;
}

HRESULT STDMETHODCALLTYPE CAlbumSongFolder::GetClassID(struct _GUID * guid)
{
    *guid = CLSID_AlbumSongFolder;
    return S_OK;
}

/*STDMETHODIMP CAlbumSongFolder::ParseDisplayName(HWND hwnd, LPBC pbc, LPOLESTR pszDisplayName, ULONG *pchEaten, LPITEMIDLIST *ppidl, pdwAttributes)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return S_OK;
}*/

HRESULT STDMETHODCALLTYPE CAlbumSongFolder::GetIDsOfNames(
    REFIID riid,
    LPOLESTR* rgszNames,
    UINT cNames,
    LCID lcid,
    DISPID* rgdispid )
{
    if(rgszNames == NULL)
    {
        return E_NOTIMPL;
    }
    else
    {
        return IDispatchImpl<IAlbumSongFolder, &IID_IAlbumSongFolder, &LIBID_VMSSELib>
            ::GetIDsOfNames(
            riid,
            rgszNames,
            cNames,
            lcid,
            rgdispid );
    }
}


