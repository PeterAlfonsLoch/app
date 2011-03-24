// SrvrItem.cpp : implementation of the MusicalPlayerLightServerItem class
//

#include "stdafx.h"
#include "vmpLightDoc.h"
#include "SrvrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MusicalPlayerLightServerItem implementation

IMPLEMENT_DYNAMIC(MusicalPlayerLightServerItem, OleServerItem)

MusicalPlayerLightServerItem::MusicalPlayerLightServerItem(MusicalPlayerLightDoc* pContainerDoc)
	: OleServerItem(pContainerDoc, TRUE)
{
	// TODO: add one-time construction code here
	//  (eg, adding additional clipboard formats to the item's data source)
}

MusicalPlayerLightServerItem::~MusicalPlayerLightServerItem()
{
	// TODO: add cleanup code here
}

void MusicalPlayerLightServerItem::Serialize(CArchive& ar)
{
	// MusicalPlayerLightServerItem::Serialize will be called by the framework if
	//  the item is copied to the clipboard.  This can happen automatically
	//  through the OLE callback OnGetClipboardData.  A good default for
	//  the embedded item is simply to delegate to the document's Serialize
	//  function.  If you support links, then you will want to serialize
	//  just a portion of the document.

	if (!IsLinkedItem())
	{
		MusicalPlayerLightDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->Serialize(ar);
	}
}

BOOL MusicalPlayerLightServerItem::OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize)
{
	// Most applications, like this one, only handle drawing the content
	//  aspect of the item.  If you wish to support other aspects, such
	//  as DVASPECT_THUMBNAIL (by overriding OnDrawEx), then this
	//  implementation of OnGetExtent should be modified to handle the
	//  additional aspect(s).

	if (dwDrawAspect != DVASPECT_CONTENT)
		return OleServerItem::OnGetExtent(dwDrawAspect, rSize);

	// MusicalPlayerLightServerItem::OnGetExtent is called to get the extent in
	//  HIMETRIC units of the entire item.  The default implementation
	//  here simply returns a hard-coded number of units.

	MusicalPlayerLightDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: replace this arbitrary size

	rSize = CSize(3000, 3000);   // 3000 x 3000 HIMETRIC units

	return TRUE;
}

BOOL MusicalPlayerLightServerItem::OnDraw(CDC* pDC, CSize& rSize)
{
	// Remove this if you use rSize
	UNREFERENCED_PARAMETER(rSize);

	MusicalPlayerLightDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: set mapping mode and extent
	//  (The extent is usually the same as the size returned from OnGetExtent)
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowOrg(0,0);
	pDC->SetWindowExt(3000, 3000);

	// TODO: add drawing code here.  Optionally, fill in the HIMETRIC extent.
	//  All drawing takes place in the metafile device context (pDC).

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// MusicalPlayerLightServerItem diagnostics

#ifdef _DEBUG
void MusicalPlayerLightServerItem::AssertValid() const
{
	OleServerItem::AssertValid();
}

void MusicalPlayerLightServerItem::Dump(CDumpContext& dc) const
{
	OleServerItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////

void MusicalPlayerLightServerItem::OnDoVerb(LONG iVerb)
{
	switch (iVerb)
	{
	// open - maps to OnOpen
	case OLEIVERB_OPEN:
	case -OLEIVERB_OPEN-1:  // allows positive OLEIVERB_OPEN-1 in registry
		OnOpen();
		break;

	// primary, show, and unknown map to OnShow
	case OLEIVERB_PRIMARY:  // OLEIVERB_PRIMARY is 0 and "Edit" in registry
	case OLEIVERB_SHOW:
		OnShow();
		break;

	// hide maps to OnHide
	case OLEIVERB_HIDE:
	case -OLEIVERB_HIDE-1:  // allows positive OLEIVERB_HIDE-1 in registry
		OnHide();
		break;
   case -4:
   case -5:
		OnShowInPlace();
      break;

	default:
		// negative verbs not understood should return E_NOTIMPL
		if (iVerb < 0)
			AfxThrowOleException(E_NOTIMPL);

		// positive verb not processed --
		//  according to OLE spec, primary verb should be executed
		//  instead.
		OnDoVerb(OLEIVERB_PRIMARY);

		// also, OLEOBJ_S_INVALIDVERB should be returned.
		AfxThrowOleException(OLEOBJ_S_INVALIDVERB);
	}
}


void MusicalPlayerLightServerItem::OnShowInPlace()
{
	ASSERT_VALID(this);

	// attempt in place activation (if not supported, fall back on "Open")
	OleServerDoc* pDoc = GetDocument();
	if (!pDoc->ActivateInPlace())
	{
		// by default OnShow() maps to OnOpen() if in-place activation
		//  not supported
		OnOpen();
	}
}
