// OleWnd.cpp : implementation file
//

#include "stdafx.h"
#include "npvmp.h"
#include "OleWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COleWnd

BEGIN_INTERFACE_MAP(COleWnd, CWnd)
	INTERFACE_PART(COleWnd, IID_IOleObject, OleObject)
END_INTERFACE_MAP()

COleWnd::COleWnd()
{
}

COleWnd::~COleWnd()
{
}


BEGIN_MESSAGE_MAP(COleWnd, CWnd)
	//{{AFX_MSG_MAP(COleWnd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// COleWnd message handlers

/////////////////////////////////////////////////////////////////////////////
// COleWnd::XOleObject

STDMETHODIMP_(ULONG) COleWnd::XOleObject::AddRef()
{
	METHOD_PROLOGUE_EX_(COleWnd, OleObject)
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) COleWnd::XOleObject::Release()
{
	METHOD_PROLOGUE_EX_(COleWnd, OleObject)
	return pThis->ExternalRelease();
}

STDMETHODIMP COleWnd::XOleObject::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX_(COleWnd, OleObject)
	return pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP COleWnd::XOleObject::SetClientSite(
	LPOLECLIENTSITE pClientSite)
{
	METHOD_PROLOGUE_EX_(COleWnd, OleObject)

	// maintain reference counts
	if (pClientSite != NULL)
		pClientSite->AddRef();
	RELEASE(pThis->m_lpClientSite);
	pThis->m_lpClientSite = pClientSite;

	// do we already have doc object support enabled?
	if (pThis->m_pDocObjectServer != NULL)
	{
		// If we currently have a document site pointer,
		// release it.
		pThis->m_pDocObjectServer->ReleaseDocSite();
	}

	if (pClientSite != NULL)
	{
		LPOLEDOCUMENTSITE pDocSite;

		if (SUCCEEDED(pClientSite->QueryInterface(IID_IOleDocumentSite,
			(LPVOID*) &pDocSite)))
		{
			if (pThis->m_pDocObjectServer != NULL)
				pThis->m_pDocObjectServer->SetDocSite(pDocSite);
			else
			{
				pThis->m_pDocObjectServer =
					pThis->GetDocObjectServer(pDocSite);
			}
		}
	}

	return S_OK;
}

STDMETHODIMP COleWnd::XOleObject::GetClientSite(
	LPOLECLIENTSITE* ppClientSite)
{
	METHOD_PROLOGUE_EX_(COleWnd, OleObject)

	if (pThis->m_lpClientSite == NULL)
	{
		*ppClientSite = NULL;
		return E_FAIL;
	}

	*ppClientSite = pThis->m_lpClientSite;
	pThis->m_lpClientSite->AddRef();
	return S_OK;
}

STDMETHODIMP COleWnd::XOleObject::SetHostNames(
	LPCOLESTR lpszContainerApp, LPCOLESTR lpszContainerObj)
{
	METHOD_PROLOGUE_EX(COleWnd, OleObject)
	ASSERT_VALID(pThis);

	USES_CONVERSION;

	TRY
	{
		pThis->OnSetHostNames(OLE2CT(lpszContainerApp),
			OLE2CT(lpszContainerObj));
	}
	END_TRY

	return S_OK;
}

STDMETHODIMP COleWnd::XOleObject::Close(DWORD dwSaveOption)
{
	METHOD_PROLOGUE_EX(COleWnd, OleObject)
	ASSERT_VALID(pThis);

	pThis->InternalAddRef();    // protect this object

	SCODE sc = S_OK;
	TRY
	{
		// delegate through document for most of the work
		pThis->OnClose((OLECLOSE)dwSaveOption);
	}
	CATCH_ALL(e)
	{
		sc = COleException::Process(e);
		DELETE_EXCEPTION(e);
	}
	END_CATCH_ALL

	pThis->InternalRelease();   // may 'delete this'

	return sc;
}

STDMETHODIMP COleWnd::XOleObject::SetMoniker(
	DWORD /*dwWhichMoniker*/, LPMONIKER /*pmk*/)
{
	METHOD_PROLOGUE_EX_(COleWnd, OleObject)

	if (pThis->m_lpClientSite == NULL)
		return E_FAIL;

	// get current full moniker from client-site
	LPMONIKER lpMoniker = NULL;
	if (pThis->m_lpClientSite->GetMoniker(OLEGETMONIKER_ONLYIFTHERE,
		OLEWHICHMK_OBJFULL, &lpMoniker) != S_OK)
	{
		// just to make sure -- always set moniker to NULL on failure
		lpMoniker = NULL;
	}

	// update all embedded items with new moniker
	POSITION pos = pThis->GetStartPosition();
	COleClientItem* pItem;
	while ((pItem = pThis->GetNextClientItem(pos)) != NULL)
	{
		if (pItem->m_bMoniker)
			pItem->m_lpObject->SetMoniker(OLEWHICHMK_CONTAINER, lpMoniker);
	}

	// send Rename advises
	pThis->NotifyAllItems(OLE_RENAMED, (DWORD)lpMoniker);
	RELEASE(lpMoniker);

	return S_OK;
}

STDMETHODIMP COleWnd::XOleObject::GetMoniker(
	DWORD dwAssign, DWORD /*dwWhichMoniker*/, LPMONIKER* ppMoniker)
{
	METHOD_PROLOGUE_EX_(COleWnd, OleObject)

	*ppMoniker = pThis->GetMoniker((OLEGETMONIKER)dwAssign);
	return *ppMoniker == NULL ? E_FAIL : S_OK;
}

STDMETHODIMP COleWnd::XOleObject::InitFromData(
	LPDATAOBJECT pDataObject, BOOL fCreation, DWORD /*dwReserved*/)
{
	METHOD_PROLOGUE_EX(COleWnd, OleObject)
	ASSERT_VALID(pThis);

	COleServerItem* pItem;
	SCODE sc;
	TRY
	{
		// delegate through item
		pItem = pThis->GetEmbeddedItem();
		ASSERT_VALID(pItem);
		ASSERT_KINDOF(COleServerItem, pItem);

		COleDataObject dataObject;
		dataObject.Attach(pDataObject,  FALSE);
		sc = pItem->OnInitFromData(&dataObject, fCreation) ? S_OK : S_FALSE;
	}
	CATCH_ALL(e)
	{
		sc = COleException::Process(e);
		DELETE_EXCEPTION(e);
	}
	END_CATCH_ALL

	return sc;
}

STDMETHODIMP COleWnd::XOleObject::GetClipboardData(
	DWORD /*dwReserved*/, LPDATAOBJECT* ppDataObject)
{
	METHOD_PROLOGUE_EX(COleWnd, OleObject)
	ASSERT_VALID(pThis);

	*ppDataObject = NULL;

	COleServerItem* pItem;
	SCODE sc = S_OK;
	TRY
	{
		// delegate through item
		pItem = pThis->GetEmbeddedItem();
		ASSERT_VALID(pItem);
		ASSERT_KINDOF(COleServerItem, pItem);

		COleDataSource* pDataSource =
			pItem->OnGetClipboardData(TRUE, NULL, NULL);
		ASSERT(pDataSource != NULL);

		*ppDataObject =
			(LPDATAOBJECT)pDataSource->GetInterface(&IID_IDataObject);
		ASSERT(*ppDataObject != NULL);
	}
	CATCH_ALL(e)
	{
		sc = COleException::Process(e);
		DELETE_EXCEPTION(e);
	}
	END_CATCH_ALL

	return sc;
}

STDMETHODIMP COleWnd::XOleObject::DoVerb(
	LONG iVerb, LPMSG /*lpmsg*/, LPOLECLIENTSITE /*pActiveSite*/, LONG /*lindex*/,
	HWND /*hwndParent*/, LPCRECT /*lpPosRect*/)
{
	METHOD_PROLOGUE_EX(COleWnd, OleObject)
	ASSERT_VALID(pThis);

	pThis->InternalAddRef();    // protect this object

	COleServerItem* pItem;
	SCODE sc = S_OK;
	TRY
	{
		// delegate through item
		pItem = pThis->GetEmbeddedItem();
		ASSERT_VALID(pItem);
		ASSERT_KINDOF(COleServerItem, pItem);
		pItem->OnDoVerb(iVerb);
	}
	CATCH_ALL(e)
	{
		sc = COleException::Process(e);
		DELETE_EXCEPTION(e);
	}
	END_CATCH_ALL
	pThis->InternalRelease();   // may 'delete this'

	return sc;
}

STDMETHODIMP COleWnd::XOleObject::EnumVerbs(
	IEnumOLEVERB** ppenumOleVerb)
{
	METHOD_PROLOGUE_EX_(COleWnd, OleObject)

	*ppenumOleVerb = NULL;

	LPOLEOBJECT lpObject = (LPOLEOBJECT)pThis->GetInterface(&IID_IOleObject);
	ASSERT(lpObject != NULL);
	CLSID clsid;
	lpObject->GetUserClassID(&clsid);

	return OleRegEnumVerbs(clsid, ppenumOleVerb);
}

STDMETHODIMP COleWnd::XOleObject::Update()
{
	METHOD_PROLOGUE_EX(COleWnd, OleObject)
	ASSERT_VALID(pThis);

	COleServerItem* pItem;
	SCODE sc = S_OK;
	TRY
	{
		// delegate through item
		pItem = pThis->GetEmbeddedItem();
		ASSERT_VALID(pItem);
		ASSERT_KINDOF(COleServerItem, pItem);
		pItem->OnUpdateItems();
	}
	CATCH_ALL(e)
	{
		sc = COleException::Process(e);
		DELETE_EXCEPTION(e);
	}
	END_CATCH_ALL

	return sc;
}

STDMETHODIMP COleWnd::XOleObject::IsUpToDate()
{
	METHOD_PROLOGUE_EX(COleWnd, OleObject)
	ASSERT_VALID(pThis);

	COleServerItem* pItem;
	SCODE sc;
	TRY
	{
		// delegate through item
		pItem = pThis->GetEmbeddedItem();
		ASSERT_VALID(pItem);
		ASSERT_KINDOF(COleServerItem, pItem);

		sc = pItem->OnQueryUpdateItems() ? S_FALSE : S_OK;
	}
	CATCH_ALL(e)
	{
		sc = COleException::Process(e);
		DELETE_EXCEPTION(e);
	}
	END_CATCH_ALL

	return sc;
}

STDMETHODIMP COleWnd::XOleObject::GetUserClassID(CLSID* lpClassID)
{
	METHOD_PROLOGUE_EX_(COleWnd, OleObject)

	LPPERSISTFILE lpPersistFile = (LPPERSISTFILE)
		pThis->GetInterface(&IID_IPersistFile);
	return lpPersistFile->GetClassID(lpClassID);
}

STDMETHODIMP COleWnd::XOleObject::GetUserType(
	DWORD dwFormOfType, LPOLESTR* ppszUserType)
{
	METHOD_PROLOGUE_EX_(COleWnd, OleObject)

	*ppszUserType = NULL;

	LPOLEOBJECT lpObject = (LPOLEOBJECT)pThis->GetInterface(&IID_IOleObject);
	ASSERT(lpObject != NULL);
	CLSID clsid;
	lpObject->GetUserClassID(&clsid);

	return OleRegGetUserType(clsid, dwFormOfType, ppszUserType);
}

STDMETHODIMP COleWnd::XOleObject::SetExtent(
	DWORD dwDrawAspect, LPSIZEL lpsizel)
{
	METHOD_PROLOGUE_EX(COleWnd, OleObject)
	ASSERT_VALID(pThis);

	COleServerItem* pItem;
	SCODE sc = E_FAIL;
	TRY
	{
		// convert rectangle to a CSize and call item OnSetExtent
		pItem = pThis->GetEmbeddedItem();
		ASSERT_VALID(pItem);
		ASSERT_KINDOF(COleServerItem, pItem);

		CSize size((int)lpsizel->cx, (int)lpsizel->cy);
		if (pItem->OnSetExtent((DVASPECT)dwDrawAspect, size))
			sc = S_OK;
	}
	CATCH_ALL(e)
	{
		sc = COleException::Process(e);
		DELETE_EXCEPTION(e);
	}
	END_CATCH_ALL

	return sc;
}

STDMETHODIMP COleWnd::XOleObject::GetExtent(
	DWORD dwDrawAspect, LPSIZEL lpsizel)
{
	METHOD_PROLOGUE_EX(COleWnd, OleObject)
	ASSERT_VALID(pThis);

	COleServerItem* pItem;
	SCODE sc = E_INVALIDARG;
	TRY
	{
		pItem = pThis->GetEmbeddedItem();
		ASSERT_VALID(pItem);
		ASSERT_KINDOF(COleServerItem, pItem);

		// call to get regular windows CSize
		CSize size;
		if (pItem->OnGetExtent((DVASPECT)dwDrawAspect, size))
		{
			if (size.cy < 0)
				size.cy = -size.cy; // extents are always positive
			lpsizel->cx = size.cx;
			lpsizel->cy = size.cy;

			sc = S_OK;
		}
	}
	CATCH_ALL(e)
	{
		sc = COleException::Process(e);
		DELETE_EXCEPTION(e);
	}
	END_CATCH_ALL

	return sc;
}

STDMETHODIMP COleWnd::XOleObject::Advise(
	IAdviseSink* pAdvSink, DWORD* pdwConnection)
{
	METHOD_PROLOGUE_EX(COleWnd, OleObject)

	COleServerItem* pItem = NULL;
	SCODE sc = E_OUTOFMEMORY;
	TRY
	{
		pItem = pThis->GetEmbeddedItem();
		ASSERT_VALID(pItem);
		ASSERT_KINDOF(COleServerItem, pItem);
		sc = S_OK;
	}
	END_TRY

	if (sc != S_OK)
		return sc;

	return pItem->GetOleObject()->Advise(pAdvSink, pdwConnection);
}

STDMETHODIMP COleWnd::XOleObject::Unadvise(DWORD dwConnection)
{
	METHOD_PROLOGUE_EX(COleWnd, OleObject)

	COleServerItem* pItem = NULL;
	SCODE sc = E_OUTOFMEMORY;
	TRY
	{
		pItem = pThis->GetEmbeddedItem();
		ASSERT_VALID(pItem);
		ASSERT_KINDOF(COleServerItem, pItem);
		sc = S_OK;
	}
	END_TRY

	if (sc != S_OK)
		return sc;

	return pItem->GetOleObject()->Unadvise(dwConnection);
}

STDMETHODIMP COleWnd::XOleObject::EnumAdvise(
	LPENUMSTATDATA* ppenumAdvise)
{
	METHOD_PROLOGUE_EX(COleWnd, OleObject)

	COleServerItem* pItem = NULL;
	SCODE sc = E_OUTOFMEMORY;
	TRY
	{
		pItem = pThis->GetEmbeddedItem();
		ASSERT_VALID(pItem);
		ASSERT_KINDOF(COleServerItem, pItem);
		sc = S_OK;
	}
	END_TRY

	if (sc != S_OK)
		return sc;

	return pItem->GetOleObject()->EnumAdvise(ppenumAdvise);
}

STDMETHODIMP COleWnd::XOleObject::GetMiscStatus(
	DWORD dwAspect, DWORD* pdwStatus)
{
	METHOD_PROLOGUE_EX_(COleWnd, OleObject)

	*pdwStatus = 0;

	LPOLEOBJECT lpObject = (LPOLEOBJECT)pThis->GetInterface(&IID_IOleObject);
	ASSERT(lpObject != NULL);
	CLSID clsid;
	lpObject->GetUserClassID(&clsid);

	return OleRegGetMiscStatus(clsid, dwAspect, pdwStatus);
}

STDMETHODIMP COleWnd::XOleObject::SetColorScheme(LPLOGPALETTE lpLogpal)
{
	METHOD_PROLOGUE_EX(COleWnd, OleObject)
	ASSERT_VALID(pThis);

	COleServerItem* pItem;
	SCODE sc = E_NOTIMPL;
	TRY
	{
		pItem = pThis->GetEmbeddedItem();
		ASSERT_VALID(pItem);
		ASSERT_KINDOF(COleServerItem, pItem);

		// delegate to embedded item
		if (pItem->OnSetColorScheme(lpLogpal))
			sc = S_OK;
	}
	END_TRY

	return sc;
}
