// vmsaudioprofileView.cpp : implementation of the AudioProfileView class
//

#include "stdafx.h"
#include "vmsaudioprofile.h"

#include "vmsaudioprofileDoc.h"
#include "vmsaudioprofileView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AudioProfileView

IMPLEMENT_DYNCREATE(AudioProfileView, CListView)

BEGIN_MESSAGE_MAP(AudioProfileView, CListView)
	//{{AFX_MSG_MAP(AudioProfileView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AudioProfileView construction/destruction

AudioProfileView::AudioProfileView()
{
	// TODO: add construction code here

}

AudioProfileView::~AudioProfileView()
{
}

BOOL AudioProfileView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// AudioProfileView drawing

void AudioProfileView::OnDraw(CDC* pDC)
{
	AudioProfileDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CListCtrl& refCtrl = GetListCtrl();
	refCtrl.InsertItem(0, "Item!");
	// TODO: add draw code for native data here
}

void AudioProfileView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// AudioProfileView printing

BOOL AudioProfileView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void AudioProfileView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void AudioProfileView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// AudioProfileView diagnostics

#ifdef _DEBUG
void AudioProfileView::AssertValid() const
{
	CListView::AssertValid();
}

void AudioProfileView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

AudioProfileDoc* AudioProfileView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(AudioProfileDoc)));
	return (AudioProfileDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// AudioProfileView message handlers
void AudioProfileView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}
