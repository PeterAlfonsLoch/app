// ContextMenuHandler.h : Declaration of the CContextMenuHandler

#ifndef __CONTEXTMENUHANDLER_H_
#define __CONTEXTMENUHANDLER_H_

#include "resource.h"       // main symbols
#import "C:\WINDOWS\system32\SHELL32.dll" raw_interfaces_only, raw_native_types, no_namespace, named_guids 

/////////////////////////////////////////////////////////////////////////////
// CContextMenuHandler
class ATL_NO_VTABLE CContextMenuHandler : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CContextMenuHandler, &CLSID_ContextMenuHandler>,
	public IDispatchImpl<IContextMenu, &IID_IContextMenu, &LIBID_Oszip_shell>,
	public IDispatchImpl<IShellDispatch, &IID_IShellDispatch, &LIBID_Shell32>
{
public:
	CContextMenuHandler();

DECLARE_REGISTRY_RESOURCEID(IDR_CONTEXTMENUHANDLER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CContextMenuHandler)
	COM_INTERFACE_ENTRY(IContextMenu)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY2(IDispatch, IContextMenu)
	COM_INTERFACE_ENTRY(IShellDispatch)
END_COM_MAP()

// IContextMenu
public:
	STDMETHOD(QueryContextMenu)(HMENU hmenu, UINT uiIndexMenu, 
                                                   UINT uiFirstCmdId, UINT uiLastCmdId,
                                                   UINT uiFlags);
// IShellDispatch
	STDMETHOD(get_Application)(IDispatch * * ppid)
	{
		if (ppid == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(get_Parent)(IDispatch * * ppid)
	{
		if (ppid == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(NameSpace)(VARIANT vDir, Folder * * ppsdf)
	{
		if (ppsdf == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(BrowseForFolder)(LONG Hwnd, BSTR Title, LONG Options, VARIANT RootFolder, Folder * * ppsdf)
	{
		if (ppsdf == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(Windows)(IDispatch * * ppid)
	{
		if (ppid == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(Open)(VARIANT vDir)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(Explore)(VARIANT vDir)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(MinimizeAll)()
	{
		return E_NOTIMPL;
	}
	STDMETHOD(UndoMinimizeALL)()
	{
		return E_NOTIMPL;
	}
	STDMETHOD(FileRun)()
	{
		return E_NOTIMPL;
	}
	STDMETHOD(CascadeWindows)()
	{
		return E_NOTIMPL;
	}
	STDMETHOD(TileVertically)()
	{
		return E_NOTIMPL;
	}
	STDMETHOD(TileHorizontally)()
	{
		return E_NOTIMPL;
	}
	STDMETHOD(ShutdownWindows)()
	{
		return E_NOTIMPL;
	}
	STDMETHOD(Suspend)()
	{
		return E_NOTIMPL;
	}
	STDMETHOD(EjectPC)()
	{
		return E_NOTIMPL;
	}
	STDMETHOD(SetTime)()
	{
		return E_NOTIMPL;
	}
	STDMETHOD(TrayProperties)()
	{
		return E_NOTIMPL;
	}
	STDMETHOD(Help)()
	{
		return E_NOTIMPL;
	}
	STDMETHOD(FindFiles)()
	{
		return E_NOTIMPL;
	}
	STDMETHOD(FindComputer)()
	{
		return E_NOTIMPL;
	}
	STDMETHOD(RefreshMenu)()
	{
		return E_NOTIMPL;
	}
	STDMETHOD(ControlPanelItem)(BSTR szDir)
	{
		return E_NOTIMPL;
	}
};

#endif //__CONTEXTMENUHANDLER_H_
