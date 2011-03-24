// VmeView.cpp : implementation of the CVmeView class
//

#include "stdafx.h"
#include "VmeApp.h"

#include "vmeDoc.h"
#include "CntrItem.h"
#include "VmeTreeView.h"
#include "VmeView.h"
#include "VmeViewUpdateHint.h"

#include "MidiTracksEventsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVmeView

IMPLEMENT_DYNCREATE(CVmeView, CView)

BEGIN_MESSAGE_MAP(CVmeView, CView)
	//{{AFX_MSG_MAP(CVmeView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVmeView construction/destruction

CVmeView::CVmeView()
{
	m_pSelection = NULL;
    m_pmiditracksview = NULL;
    m_pviewCurrent = NULL;
	// TODO: add construction code here

}

CVmeView::~CVmeView()
{
}

BOOL CVmeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if(!CView::PreCreateWindow(cs))
    {
        return FALSE;
    }

    cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CVmeView drawing

void CVmeView::OnDraw(CDC* pDC)
{
	CVmeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
//	CListCtrl& refCtrl = GetListCtrl();
//	refCtrl.InsertItem(0, "Item!");
	// TODO: add draw code for native data here
}

void CVmeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().

	// TODO: remove this code when final selection model code is written
	m_pSelection = NULL;    // initialize selection

	//Active documents should always be activated
	COleDocument* pDoc = (COleDocument*) GetDocument();
	if (pDoc != NULL)
	{
		// activate the first one
		POSITION posItem = pDoc->GetStartPosition();
		if (posItem != NULL)
		{
			CDocItem* pItem = pDoc->GetNextItem(posItem);

			// only if it's an Active document
			COleDocObjectItem *pDocObjectItem =
				DYNAMIC_DOWNCAST(COleDocObjectItem, pItem);

			if (pDocObjectItem != NULL)
			{
				pDocObjectItem->DoVerb(OLEIVERB_SHOW, this);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CVmeView printing

BOOL CVmeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	if (!CView::DoPreparePrinting(pInfo))
		return FALSE;
	
	if (!COleDocObjectItem::OnPreparePrinting(this, pInfo))
		return FALSE;

	return TRUE;
}

void CVmeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVmeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CVmeView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add customized printing code here
	if(pInfo->m_bDocObject)
		COleDocObjectItem::OnPrint(this, pInfo, TRUE);
	else
		CView::OnPrint(pDC, pInfo);
}

void CVmeView::OnDestroy()
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

BOOL CVmeView::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CVmeCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void CVmeView::OnInsertObject()
{
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CVmeCntrItem object.
	COleInsertDialog dlg;
	if (dlg.DoModal(COleInsertDialog::DocObjectsOnly) != IDOK)
		return;

	BeginWaitCursor();

	CVmeCntrItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document.
		CVmeDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CVmeCntrItem(pDoc);
		ASSERT_VALID(pItem);

		// Initialize the item from the dialog data.
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // any exception will do
		ASSERT_VALID(pItem);
		
		pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);

		// As an arbitrary user interface design, this sets the selection
		//  to the last item inserted.

		// TODO: reimplement selection as appropriate for your application

		m_pSelection = pItem;   // set selection to last inserted item
		pDoc->UpdateAllViews(NULL);
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation.
void CVmeView::OnCancelEditCntr()
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
void CVmeView::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// need to set focus to this item if it is in the same view
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}

	CView::OnSetFocus(pOldWnd);
}

void CVmeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();
    Layout();
}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CVmeView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CVmeView diagnostics

#ifdef _DEBUG
void CVmeView::AssertValid() const
{
	CView::AssertValid();
}

void CVmeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVmeDoc* CVmeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVmeDoc)));
	return (CVmeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVmeView message handlers
void CVmeView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}

void CVmeView::View(CVmeView::EView view)
{
    m_view = view;
    switch(view)
    {
    case ViewMidiTracksEvents:
        {
            if(m_pmiditracksview == NULL)
            {
                CRuntimeClass * prc = RUNTIME_CLASS(CMidiTracksEventsView);
                CObject * pobject = prc->CreateObject();
                ASSERT_KINDOF(CMidiTracksEventsView, pobject);
                CView * pview = (CView *) pobject;
                CCreateContext cc;
                memset(&cc, 0, sizeof(cc));
                cc.m_pCurrentDoc = GetDocument();
                if (!pview->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		                CRect(0,0,0,0), this, IDV_MIDITRACKSEVENTS, &cc))
	                {
		                AfxMessageBox("Warning: could not create view for frame.\n");
		                return;        // can't continue without a view
	                }
                pview->OnInitialUpdate();
                    m_pmiditracksview = (CMidiTracksEventsView*) pview;
            }
            if(m_pmiditracksview != NULL)
            {
                ModifyStyle(WS_BORDER, 0);
                ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_SHOWWINDOW);      
                m_pviewCurrent = m_pmiditracksview;
                m_pmiditracksview->ShowWindow(SW_SHOW);
                Layout();
            }
        }
        break;
    }
}

void CVmeView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pSender != NULL && pSender->IsKindOf(RUNTIME_CLASS(CVmeTreeView)))
    {
        if(pHint != NULL && pHint->IsKindOf(RUNTIME_CLASS(CVmeViewUpdateHint)))
        {
            CVmeViewUpdateHint * pViewHint = (CVmeViewUpdateHint *) pHint;
            CVmeTreeView * pTreeView = (CVmeTreeView *) pSender;
            if(pViewHint->m_iType == 0)
            {
                if(pViewHint->m_htreeitem == pTreeView->m_tree.hMidiTracksEvents)
                {
                    View(ViewMidiTracksEvents);
                }
            }
        }
    }

	
}

void CVmeView::Layout()
{
    CRect rectClient;
    GetClientRect(rectClient);
    if(m_pviewCurrent != NULL)
    {
        m_pviewCurrent->MoveWindow(0, 0, rectClient.Width(), rectClient.Height());
    }
}
