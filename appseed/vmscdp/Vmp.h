	
// AtlVms.h : Declaration of the CVmp

#ifndef __VMS_H_
#define __VMS_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVmp
class ATL_NO_VTABLE CVmp : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVmp, &CLSID_VmsPlayer>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CVmp>,
	public IDispatchImpl<IVmsPlayer, &IID_IVmsPlayer, &LIBID_VmsPlayer>
{
public:
	CVmp()
	{
		m_pUnkMarshaler = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_VMS)
DECLARE_GET_CONTROLLING_UNKNOWN()

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVmp)
	COM_INTERFACE_ENTRY(IVmsPlayer)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CVmp)
END_CONNECTION_POINT_MAP()


	HRESULT FinalConstruct()
	{
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
	}

	CComPtr<IUnknown> m_pUnkMarshaler;

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IVms
public:
	STDMETHOD(ReserveSongs)(VARIANT * var);
};

#endif //__VMS_H_
