// npvmpView.cpp : implementation of the CNpvmpView class
//

#include "stdafx.h"
#include "npvmpLight.h"

#include "npvmpLightCntrItem.h"
#include "npvmpLightView.h"

#include "vmsp.h"

const CLSID CLSID_IMidDocument = {0xF53B78E0,0xA6F5,0x41CF,{0xB4,0xFB,0x9F,0x9F,0xE4,0x9D,0xD4,0x16}};

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNpvmpView

IMPLEMENT_DYNCREATE(CNpvmpView, CView)

BEGIN_MESSAGE_MAP(CNpvmpView, CView)
	//{{AFX_MSG_MAP(CNpvmpView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNpvmpView construction/destruction

CNpvmpView::CNpvmpView()
{
	m_pSelection = NULL;
	// TODO: add construction code here

}

CNpvmpView::~CNpvmpView()
{
	if(m_pSelection != NULL)
		delete m_pSelection;
}

BOOL CNpvmpView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs


	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CNpvmpView drawing

void CNpvmpView::OnDraw(CDC* pDC)
{
//	CNpvmpDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CNpvmpView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

}

/////////////////////////////////////////////////////////////////////////////
// CNpvmpView printing

BOOL CNpvmpView::OnPreparePrinting(CPrintInfo* pInfo)
{
	if (!CView::DoPreparePrinting(pInfo))
		return FALSE;
	
	if (!COleDocObjectItem::OnPreparePrinting(this, pInfo))
		return FALSE;

	return TRUE;
}

void CNpvmpView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CNpvmpView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CNpvmpView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add customized printing code here
	if(pInfo->m_bDocObject)
		COleDocObjectItem::OnPrint(this, pInfo, TRUE);
	else
		CView::OnPrint(pDC, pInfo);
}

void CNpvmpView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}


/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL CNpvmpView::IsSelected(const base_object* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CNpvmpCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void CNpvmpView::InsertObject(LPCTSTR lpcsz)
{

	//BeginWaitCursor();

	CNpvmpCntrItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document.
		CNpvmpDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CNpvmpCntrItem(pDoc);
		ASSERT_VALID(pItem);

		// Initialize the item from the dialog data.
//		if(lpcsz == NULL)
		if(true)
		{
			if (!CreateItem(pItem))
				AfxThrowMemoryException();  // any exception will do
			ASSERT_VALID(pItem);
		}
		else
		{
			if (!CreateItemFromFile(pItem, lpcsz))
				AfxThrowMemoryException();  // any exception will do
			ASSERT_VALID(pItem);
		}

		
		pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);

		// As an arbitrary user interface design, this sets the selection
		//  to the last item inserted.

			// TODO: reimplement selection as appropriate for your application
		pItem->m_pView = this;

		m_pSelection = pItem;   // set selection to last inserted item
		pDoc->UpdateAllViews(NULL);
      Layout();
	}
	CATCH(base_exception, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

//	EndWaitCursor();
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation.
void CNpvmpView::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
void CNpvmpView::OnSetFocus(base_wnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// need to set focus to this item if it is in the same view
		base_wnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}

	CView::OnSetFocus(pOldWnd);
}

void CNpvmpView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

   Layout();
}

/////////////////////////////////////////////////////////////////////////////
// CNpvmpView diagnostics

#ifdef _DEBUG
void CNpvmpView::AssertValid() const
{
	CView::AssertValid();
}

void CNpvmpView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNpvmpDoc* CNpvmpView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNpvmpDoc)));
	return (CNpvmpDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNpvmpView message handlers


BOOL CNpvmpView::CreateItem(COleClientItem* pNewItem)
{
	ASSERT_VALID(pNewItem);

	BOOL bResult;

	bResult = pNewItem->CreateNewItem(CLSID_IMidDocument);

	return bResult;
}

BOOL CNpvmpView::CreateItemFromFile(COleClientItem* pNewItem, LPCTSTR lpcsz)
{
	ASSERT_VALID(pNewItem);

	BOOL bResult;

	bResult = pNewItem->CreateFromFile(lpcsz, CLSID_IMidDocument);

	return bResult;
}

void CNpvmpView::SetDocument(CDocument *pdoc)
{
	m_pDocument = pdoc;
}

void CNpvmpView::Layout()
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
   {
      CRect rect;
      GetClientRect(rect);
		pActiveItem->SetItemRects(rect, rect);
   }

}
