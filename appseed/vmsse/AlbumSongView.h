// AlbumSongView.h : Declaration of the CAlbumSongView

#ifndef __ALBUMSONGVIEW_H_
#define __ALBUMSONGVIEW_H_

#include "resource.h"       // main symbols
#include "DWArray.h"
#include "..\vms\vms.h"
#include "DBClient.h"
/////////////////////////////////////////////////////////////////////////////
// CAlbumSongView

class CAlbumSongList;
class CAlbumSongMainWnd;
class CDBSongSet;

#define ID_RELATIVE_SONGS_OPTIONS 1024
#define ID_RELATIVE_SEARCH_FORM 1025

class ATL_NO_VTABLE CAlbumSongView : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAlbumSongView, &CLSID_AlbumSongView>,
	public IDispatchImpl<IAlbumSongView, &IID_IAlbumSongView, &LIBID_VMSSELib>,
    public IShellView,
    public IShellLinkW,
	public CDBClient

{
public:
	CAlbumSongView();
    virtual ~CAlbumSongView();
//    CComPtr<IShellView>     m_spShellView;
    CComPtr<IShellBrowser>  m_spshbrowser;
    CComPtr<IOleWindow>     m_spolewnd;
    CAlbumSongMainWnd *     m_pipwnd; //in place window
    
DECLARE_REGISTRY_RESOURCEID(IDR_VMSSE_ALBUMSONGVIEW)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAlbumSongView)
	COM_INTERFACE_ENTRY(IAlbumSongView)
	COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(IShellView)
    COM_INTERFACE_ENTRY(IShellLinkW)
END_COM_MAP()

// IAlbumSongView
public:
	bool InsertMenus();
	STDMETHOD(get_ShellBrowser)(/*[out, retval]*/ IShellBrowser ** pVal);
	STDMETHOD(put_ShellBrowser)(/*[in]*/ IShellBrowser * newVal);
	
	//void Populate(IDBAsynchStatus * pDbas = NULL);
	VMSRESULT UpdateList();
    // IOleWindow
    virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE GetWindow( 
        /* [out] */ HWND *phwnd);
    
    virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp( 
        /* [in] */ BOOL fEnterMode);

// IShellView
virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator( 
            /* [in] */ MSG *pmsg);
        
        virtual HRESULT STDMETHODCALLTYPE EnableModeless( 
            /* [in] */ BOOL fEnable);
        
        virtual HRESULT STDMETHODCALLTYPE UIActivate( 
            /* [in] */ UINT uState);
        
        virtual HRESULT STDMETHODCALLTYPE Refresh( void);
        
        virtual HRESULT STDMETHODCALLTYPE CreateViewWindow( 
            /* [in] */ IShellView *psvPrevious,
            /* [in] */ LPCFOLDERSETTINGS pfs,
            /* [in] */ IShellBrowser *psb,
            /* [out] */ RECT *prcView,
            /* [out] */ HWND *phWnd);
        
        virtual HRESULT STDMETHODCALLTYPE DestroyViewWindow( void);
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentInfo( 
            /* [out] */ LPFOLDERSETTINGS pfs);
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE AddPropertySheetPages( 
            /* [in] */ DWORD dwReserved,
            /* [in] */ LPFNSVADDPROPSHEETPAGE pfn,
            /* [in] */ LPARAM lparam);
        
        virtual HRESULT STDMETHODCALLTYPE SaveViewState( void);
        
        virtual HRESULT STDMETHODCALLTYPE SelectItem( 
            /* [in] */ LPCITEMIDLIST pidlItem,
            /* [in] */ SVSIF uFlags);
        
        virtual HRESULT STDMETHODCALLTYPE GetItemObject( 
            /* [in] */ UINT uItem,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);

            // IShellLinkW
        virtual HRESULT STDMETHODCALLTYPE GetPath( 
            /* [size_is][out] */ LPWSTR pszFile,
            /* [in] */ int cch,
            /* [full][out][in] */ WIN32_FIND_DATAW *pfd,
            /* [in] */ DWORD fFlags);
        
        virtual HRESULT STDMETHODCALLTYPE GetIDList( 
            /* [out] */ LPITEMIDLIST *ppidl);
        
        virtual HRESULT STDMETHODCALLTYPE SetIDList( 
            /* [in] */ LPCITEMIDLIST pidl);
        
        virtual HRESULT STDMETHODCALLTYPE GetDescription( 
            /* [size_is][out] */ LPWSTR pszName,
            int cch);
        
        virtual HRESULT STDMETHODCALLTYPE SetDescription( 
            /* [in] */ LPCWSTR pszName);
        
        virtual HRESULT STDMETHODCALLTYPE GetWorkingDirectory( 
            /* [size_is][out] */ LPWSTR pszDir,
            int cch);
        
        virtual HRESULT STDMETHODCALLTYPE SetWorkingDirectory( 
            /* [in] */ LPCWSTR pszDir);
        
        virtual HRESULT STDMETHODCALLTYPE GetArguments( 
            /* [size_is][out] */ LPWSTR pszArgs,
            int cch);
        
        virtual HRESULT STDMETHODCALLTYPE SetArguments( 
            /* [in] */ LPCWSTR pszArgs);
        
        virtual HRESULT STDMETHODCALLTYPE GetHotkey( 
            /* [out] */ WORD *pwHotkey);
        
        virtual HRESULT STDMETHODCALLTYPE SetHotkey( 
            /* [in] */ WORD wHotkey);
        
        virtual HRESULT STDMETHODCALLTYPE GetShowCmd( 
            /* [out] */ int *piShowCmd);
        
        virtual HRESULT STDMETHODCALLTYPE SetShowCmd( 
            /* [in] */ int iShowCmd);
        
        virtual HRESULT STDMETHODCALLTYPE GetIconLocation( 
            /* [size_is][out] */ LPWSTR pszIconPath,
            /* [in] */ int cch,
            /* [out] */ int *piIcon);
        
        virtual HRESULT STDMETHODCALLTYPE SetIconLocation( 
            /* [in] */ LPCWSTR pszIconPath,
            /* [in] */ int iIcon);
        
        virtual HRESULT STDMETHODCALLTYPE SetRelativePath( 
            /* [in] */ LPCWSTR pszPathRel,
            /* [in] */ DWORD dwReserved);
        
        virtual HRESULT STDMETHODCALLTYPE Resolve( 
            /* [in] */ HWND hwnd,
            /* [in] */ DWORD fFlags);
        
        virtual HRESULT STDMETHODCALLTYPE SetPath( 
            /* [in] */ LPCWSTR pszFile);


    };

#endif //__ALBUMSONGVIEW_H_
