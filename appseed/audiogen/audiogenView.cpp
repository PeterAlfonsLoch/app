// audiogenView.cpp : implementation of the CAudiogenView class
//

#include "stdafx.h"

#include "audiogenDoc.h"
#include "audiogenView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAudiogenView

IMPLEMENT_DYNCREATE(CAudiogenView, CView)

BEGIN_MESSAGE_MAP(CAudiogenView, CView)
	//{{AFX_MSG_MAP(CAudiogenView)
	ON_COMMAND(ID_EXECUTE_PLAY, OnExecutePlay)
	ON_COMMAND(ID_EXECUTE_STOP, OnExecuteStop)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAudiogenView construction/destruction

CAudiogenView::CAudiogenView()
{
	// TODO: add construction code here
   m_pwaveout = _vmsaudio::WaveOut::BeginThread();
   m_paudiogen = (AudioGen *) AfxBeginThread(RUNTIME_CLASS(AudioGen));
   m_paudiogen->m_pwaveout = m_pwaveout;
   m_pwaveout->Open(m_paudiogen, 4, 8 * 1024);

}

CAudiogenView::~CAudiogenView()
{
}

BOOL CAudiogenView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAudiogenView drawing

void CAudiogenView::OnDraw(CDC* pDC)
{
	CAudiogenDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CAudiogenView printing

BOOL CAudiogenView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAudiogenView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAudiogenView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAudiogenView diagnostics

#ifdef _DEBUG
void CAudiogenView::AssertValid() const
{
	CView::AssertValid();
}

void CAudiogenView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAudiogenDoc* CAudiogenView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAudiogenDoc)));
	return (CAudiogenDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAudiogenView message handlers

void CAudiogenView::OnExecutePlay() 
{
	m_pwaveout->Start();
}

void CAudiogenView::OnExecuteStop() 
{
	m_pwaveout->Stop();
}
