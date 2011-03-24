	
// AtlVms.h : Declaration of the CVms

#ifndef __VMC_H_
#define __VMC_H_


#include "resource.h"       // main symbols
//#include "vmc_i.h"
//#include "vmc_i.c"

/////////////////////////////////////////////////////////////////////////////
// CVms
class ATL_NO_VTABLE CVmc : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVmc, &CLSID_VmsComposer>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CVmc>,
	public IDispatchImpl<IVmsComposer, &IID_IVmsComposer, &LIBID_VmsComposer>
{
public:
	CVmc()
	{
		m_pUnkMarshaler = NULL;
	};

DECLARE_REGISTRY_RESOURCEID(IDR_VMC)
DECLARE_GET_CONTROLLING_UNKNOWN()

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVmc)
	COM_INTERFACE_ENTRY(IVmsComposer)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CVmc)
END_CONNECTION_POINT_MAP()


	HRESULT FinalConstruct()
	{
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	};

	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
	};

	CComPtr<IUnknown> m_pUnkMarshaler;

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IVms
public:
	STDMETHOD(ReserveSongs)(VARIANT * var);
};

#endif //__VMC_H_
