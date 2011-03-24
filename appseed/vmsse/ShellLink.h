// ShellLink.h : Declaration of the CShellLink

#ifndef __SHELLLINK_H_
#define __SHELLLINK_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CShellLink
class ATL_NO_VTABLE CShellLink : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CShellLink, &CLSID_ShellLink>,
	public IDispatchImpl<IShellLink, &IID_IShellLink, &LIBID_VMSSELib>
{
public:
	CShellLink()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SHELLLINK)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CShellLink)
	COM_INTERFACE_ENTRY(IShellLink)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IShellLink
public:
};

#endif //__SHELLLINK_H_
