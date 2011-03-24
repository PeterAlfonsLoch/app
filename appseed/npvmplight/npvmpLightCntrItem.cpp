// CntrItem.cpp : implementation of the CNpvmpCntrItem class
//

#include "stdafx.h"
#include "npvmpLight.h"

#include "npvmpLightDoc.h"
#include "npvmpLightView.h"
#include "npvmpLightCntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNpvmpCntrItem implementation

IMPLEMENT_SERIAL(CNpvmpCntrItem, COleDocObjectItem, 0)

CNpvmpCntrItem::CNpvmpCntrItem(CNpvmpDoc* pContainer)
	: COleDocObjectItem(pContainer)
{
	// TODO: add one-time construction code here
	
}

CNpvmpCntrItem::~CNpvmpCntrItem()
{
	// TODO: add cleanup code here
	
}

void CNpvmpCntrItem::OnChange(OLE_NOTIFICATION nCode, DWORD dwParam)
{
	ASSERT_VALID(this);

	COleDocObjectItem::OnChange(nCode, dwParam);

	// When an item is being edited (either in-place or fully open)
	//  it sends OnChange notifications for changes in the state of the
	//  item or visual appearance of its content.

	// TODO: invalidate the item by calling UpdateAllViews
	//  (with hints appropriate to your application)

	GetDocument()->UpdateAllViews(NULL);
		// for now just update ALL views/no hints
}

BOOL CNpvmpCntrItem::OnChangeItemPosition(const CRect& rectPos)
{
	ASSERT_VALID(this);

	// During in-place activation CNpvmpCntrItem::OnChangeItemPosition
	//  is called by the server to change the position of the in-place
	//  window.  Usually, this is a result of the data in the server
	//  document changing such that the extent has changed or as a result
	//  of in-place resizing.
	//
	// The default here is to call the base class, which will call
	//  COleDocObjectItem::SetItemRects to move the item
	//  to the new position.

	if (!COleDocObjectItem::OnChangeItemPosition(rectPos))
		return FALSE;

	// TODO: update any cache you may have of the item's rectangle/extent

	return TRUE;
}


void CNpvmpCntrItem::OnActivate()
{
}

void CNpvmpCntrItem::OnDeactivateUI(BOOL bUndoable)
{
	COleDocObjectItem::OnDeactivateUI(bUndoable);

    // Hide the object if it is not an outside-in object
    DWORD dwMisc = 0;
    m_lpObject->GetMiscStatus(GetDrawAspect(), &dwMisc);
    if (dwMisc & OLEMISC_INSIDEOUT)
        DoVerb(OLEIVERB_HIDE, NULL);
}

void CNpvmpCntrItem::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	// Call base class first to read in COleDocObjectItem data.
	// Since this sets up the m_pDocument pointer returned from
	//  CNpvmpCntrItem::GetDocument, it is a good idea to call
	//  the base class Serialize first.
	COleDocObjectItem::Serialize(ar);

	// now store/retrieve data specific to CNpvmpCntrItem
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CNpvmpCntrItem diagnostics

#ifdef _DEBUG
void CNpvmpCntrItem::AssertValid() const
{
	COleDocObjectItem::AssertValid();
}

void CNpvmpCntrItem::Dump(CDumpContext& dc) const
{
	COleDocObjectItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// IUnknown client helpers

typedef LPVOID* LPLP;
LPUNKNOWN AFXAPI _AfxQueryInterface(LPUNKNOWN lpUnknown, REFIID iid)
{
	ASSERT(lpUnknown != NULL);

	LPUNKNOWN lpW = NULL;
	if (lpUnknown->QueryInterface(iid, (LPLP)&lpW) != S_OK)
		return NULL;

	return lpW;
}
#define DELETE_EXCEPTION(e) do { e->Delete(); } while (0)
#define QUERYINTERFACE(lpUnknown, iface) \
	(iface*)_AfxQueryInterface(lpUnknown, IID_##iface)

BOOL CNpvmpCntrItem::FinishCreate(SCODE sc)
{
	USES_CONVERSION;

	ASSERT_VALID(this);
	ASSERT(m_pView == NULL);

	TRY
	{
		// m_lpObject is currently an IUnknown, convert to IOleObject
		if (m_lpObject != NULL)
		{
			LPUNKNOWN lpUnk = m_lpObject;
			m_lpObject = QUERYINTERFACE(lpUnk, IOleObject);
			lpUnk->Release();
			if (m_lpObject == NULL)
				AfxThrowOleException(E_OUTOFMEMORY);
		}

		// check return code from create function
		CheckGeneral(sc);

		UpdateItemType();

		// cache the IViewObject interface
		m_lpViewObject = QUERYINTERFACE(m_lpObject, IViewObject2);
		if (m_lpViewObject == NULL)
			CheckGeneral(E_NOINTERFACE);
		ASSERT(m_lpViewObject != NULL);

		if (GetType() != OT_STATIC)
		{
			// setup for advises; we assume that OLE cleans them up properly
			LPADVISESINK lpAdviseSink =
				(LPADVISESINK)GetInterface(&IID_IAdviseSink);
			ASSERT(lpAdviseSink != NULL);
			CheckGeneral(m_lpObject->Advise(lpAdviseSink, &m_dwConnection));
			ASSERT(m_dwConnection != 0);

			// set up view advise
			VERIFY(m_lpViewObject->SetAdvise(DVASPECT_CONTENT, 0, lpAdviseSink)
				== S_OK);

			// the server shows these in its user-interface
			//  (as document title and in File Exit menu)
			//m_lpObject->SetHostNames(T2COLE(AfxGetAppName()),
			//	T2COLE(m_pDocument->GetTitle()));
			m_lpObject->SetHostNames(T2COLE(_T("Veriwell Musical Player")),
				T2COLE(m_pDocument->GetTitle()));
		}

		// all items are "contained" -- this makes our reference to this object
		//  weak -- which is needed for links to embedding silent update.
		OleSetContainedObject(m_lpObject, TRUE);

		// considered loaded at this point
		m_nItemState = loadedState;
	}
	CATCH_ALL(e)
	{
		Release();  // release the object just in case
		ASSERT_VALID(this);
		DELETE_EXCEPTION(e);
		return FALSE;
	}
	END_CATCH_ALL

	// set state to loaded
	ASSERT(m_nItemState != emptyState);

	// otherwise no errors, return success!
	ASSERT_VALID(this);
	return TRUE;
}
