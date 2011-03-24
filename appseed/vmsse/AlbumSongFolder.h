// AlbumSongFolder.h : Declaration of the CAlbumSongFolder

#ifndef __ALBUMSONGFOLDER_H_
#define __ALBUMSONGFOLDER_H_

#include "resource.h"       // main symbols
#include <shlobj.h> 

/////////////////////////////////////////////////////////////////////////////
// CAlbumSongFolder
//class ATL_NO_VTABLE CAlbumSongFolder : 
class CAlbumSongFolder : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAlbumSongFolder, &CLSID_AlbumSongFolder>,
	public IDispatchImpl<IAlbumSongFolder, &IID_IAlbumSongFolder, &LIBID_VMSSELib>,
    public IShellFolder,
	public IExtractIcon,
    public IPersistFolder
{
public:
	CAlbumSongFolder();
    virtual ~CAlbumSongFolder();
//	{
        //LPUNKNOWN lpunk = NULL;
        //if(S_OK == OuterQueryInterface(IID_IUnknown, (void**)&lpunk))
        //{
//         HRESULT hr =   m_spShellFolder.CoCreateInstance(
  //              IID_IShellFolder,
    //            (LPUNKNOWN) (CComCoClass<CAlbumSongFolder, &CLSID_AlbumSongFolder> *) this );
        //}

//	}

    IShellLink * m_sv;

DECLARE_REGISTRY_RESOURCEID(IDR_VMSSE_ALBUMSONGFOLDER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAlbumSongFolder)
	COM_INTERFACE_ENTRY(IAlbumSongFolder)
	COM_INTERFACE_ENTRY(IDispatch)
//    COM_INTERFACE_ENTRY_IID(IID_IShellFolder, CAlbumSongFolder)
  //  COM_INTERFACE_ENTRY_IID(IID_IPersistFolder, CAlbumSongFolder)
    //COM_INTERFACE_ENTRY_IID(IID_IExtractIcon, CAlbumSongFolder)
    COM_INTERFACE_ENTRY(IShellFolder)
    COM_INTERFACE_ENTRY(IPersistFolder)
    COM_INTERFACE_ENTRY_AGGREGATE(IID_IShellLink, m_sv)
    COM_INTERFACE_ENTRY_IID(IID_IExtractIcon,IExtractIcon)
    
END_COM_MAP()

// IAlbumSongFolder
public:
// IDispatch
    virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(
        REFIID riid,
        LPOLESTR* rgszNames,
        UINT cNames,
        LCID lcid,
        DISPID* rgdispid );

	//STDMETHOD(ParseDisplayName)(HWND  hwnd, LPBC pbc, LPOLESTR pszDisplayName, ULONG * pchEaten, LPITEMIDLIST * ppidl, pdwAttributes);

// IPersistFolder
    virtual HRESULT STDMETHODCALLTYPE Initialize( 
    /* [in] */ LPCITEMIDLIST pidl);
    virtual HRESULT STDMETHODCALLTYPE GetClassID(struct _GUID *);

// IExtractIcon
    STDMETHOD(GetIconLocation)(
        UINT uFlags, 
        LPTSTR szIconFile, 
        UINT cchMax, 
        LPINT piIndex,   
        LPUINT puFlags) ;
    STDMETHOD (Extract)(
        LPCTSTR pszFile, 
        UINT nIconIndex, 
        HICON *phiconLarge,  
        HICON *phiconSmall,
        UINT nIconSize) ;
// IShellFolder
   virtual HRESULT STDMETHODCALLTYPE ParseDisplayName( 
        /* [in] */ HWND hwnd,
        /* [in] */ LPBC pbc,
        /* [string][in] */ LPOLESTR pszDisplayName,
        /* [out] */ ULONG *pchEaten,
        /* [out] */ LPITEMIDLIST *ppidl,
        /* [unique][out][in] */ ULONG *pdwAttributes);
    
    virtual HRESULT STDMETHODCALLTYPE EnumObjects( 
        /* [in] */ HWND hwnd,
        /* [in] */ SHCONTF grfFlags,
        /* [out] */ IEnumIDList **ppenumIDList);
    
    virtual HRESULT STDMETHODCALLTYPE BindToObject( 
        /* [in] */ LPCITEMIDLIST pidl,
        /* [in] */ LPBC pbc,
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ void **ppv);
    
    virtual HRESULT STDMETHODCALLTYPE BindToStorage( 
        /* [in] */ LPCITEMIDLIST pidl,
        /* [in] */ LPBC pbc,
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ void **ppv);
    
    virtual HRESULT STDMETHODCALLTYPE CompareIDs( 
        /* [in] */ LPARAM lParam,
        /* [in] */ LPCITEMIDLIST pidl1,
        /* [in] */ LPCITEMIDLIST pidl2);

    virtual HRESULT STDMETHODCALLTYPE CreateViewObject( 
        /* [in] */ HWND hwndOwner,
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ void **ppv);

    virtual HRESULT STDMETHODCALLTYPE GetAttributesOf( 
        /* [in] */ UINT cidl,
        /* [size_is][in] */ LPCITEMIDLIST *apidl,
        /* [out][in] */ SFGAOF *rgfInOut);
    
    virtual HRESULT STDMETHODCALLTYPE GetUIObjectOf( 
        /* [in] */ HWND hwndOwner,
        /* [in] */ UINT cidl,
        /* [size_is][in] */ LPCITEMIDLIST *apidl,
        /* [in] */ REFIID riid,
        /* [unique][out][in] */ UINT *rgfReserved,
        /* [iid_is][out] */ void **ppv);
    
    virtual HRESULT STDMETHODCALLTYPE GetDisplayNameOf( 
        /* [in] */ LPCITEMIDLIST pidl,
        /* [in] */ SHGDNF uFlags,
        /* [out] */ STRRET *pName);
    
    virtual HRESULT STDMETHODCALLTYPE SetNameOf( 
        /* [in] */ HWND hwnd,
        /* [in] */ LPCITEMIDLIST pidl,
        /* [string][in] */ LPCOLESTR pszName,
        /* [in] */ SHGDNF uFlags,
        /* [out] */ LPITEMIDLIST *ppidlOut);
        
    /*STDMETHOD(ParseDisplayName)(wireHWND hwnd, IBindCtx * pbc, LPWSTR pszDisplayName, ULONG * pchEaten, wirePIDL * ppidl, ULONG * pdwAttributes)
	{
		if (pchEaten == NULL)
			return E_POINTER;
			
		if (ppidl == NULL)
			return E_POINTER;
			
		if (pdwAttributes == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(EnumObjects)(wireHWND hwnd, ULONG grfFlags, IEnumIDList * * ppenumIDList)
	{
		if (ppenumIDList == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(BindToObject)(wirePIDL pidl, IBindCtx * pbc, GUID * riid, VOID * * ppv)
	{
		if (ppv == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(BindToStorage)(wirePIDL pidl, IBindCtx * pbc, GUID * riid, VOID * * ppv)
	{
		if (ppv == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(CompareIDs)(LONG_PTR lParam, wirePIDL pidl1, wirePIDL pidl2)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(CreateViewObject)(wireHWND hwndOwner, GUID * riid, VOID * * ppv);
	STDMETHOD(GetAttributesOf)(UINT cidl, wirePIDL * apidl, ULONG * rgfInOut)
	{
		if (rgfInOut == NULL)
			return E_POINTER;

//		ITEMIDLIST structures, each of which uniquely identifies a file object relative to the parent folder. Each ITEMIDLIST structure must contain exactly one SHITEMID
            
		return E_NOTIMPL;
	}
	STDMETHOD(GetUIObjectOf)(wireHWND hwndOwner, UINT cidl, wirePIDL * apidl, GUID * riid, UINT * rgfReserved, VOID * * ppv)
	{
		if (rgfReserved == NULL)
			return E_POINTER;
			
		if (ppv == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(GetDisplayNameOf)(wirePIDL pidl, ULONG uFlags, _STRRET * pName);
	STDMETHOD(SetNameOf)(wireHWND hwnd, wirePIDL pidl, LPWSTR pszName, ULONG uFlags, wirePIDL * ppidlOut)
	{
		if (ppidlOut == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}*/
// IShellFolder
// IShellFolder
        
};

#endif //__ALBUMSONGFOLDER_H_
