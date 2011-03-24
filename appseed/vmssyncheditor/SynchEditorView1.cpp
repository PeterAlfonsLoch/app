// SynchEditorView1.cpp : implementation file
//

#include "stdafx.h"
#include "FrameWnd.h"

#include "vmssyncheditor.h"
#include "SynchEditorView1.h"
#include "_vmssyncheditorDoc.h"
#include "_vmssyncheditorView.h"
#include "SynchEditorTokenListView.h"
#include "SynchEditorMediaView.h"

#include "XView.h"

#include "International.h"

#include "XfplayerOpenFileDialog.h"

#include "MidiUtil.h"
#include "Star350File.h"

#include "LyricEventsV2.h"

#include "LyricEventsV2.h"

// vmsmediaplay
#include "_vmsmediaplayMediaViewData.h"

#include "KaraokeData.h"
#include "KaraokeStaticData.h"

#include "MidiTrackSelectDDX.h"
#include "MidiTrackSelectDoc.h"
#include "MidiTrackSelectFrame.h"
#include "MidiTrackSelectView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSynchEditorView1

IMPLEMENT_DYNCREATE(CSynchEditorView1, BaseSplitView)

CSynchEditorView1::CSynchEditorView1()
{
}

CSynchEditorView1::~CSynchEditorView1()
{
}


BEGIN_MESSAGE_MAP(CSynchEditorView1, BaseSplitView)
	//{{AFX_MSG_MAP(CSynchEditorView1)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_INSERT, OnFileInsert)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSynchEditorView1 drawing

void CSynchEditorView1::OnDraw(CDC* pDC)
{
	Document* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CSynchEditorView1 diagnostics

#ifdef _DEBUG
void CSynchEditorView1::AssertValid() const
{
	BaseSplitView::AssertValid();
}

void CSynchEditorView1::Dump(CDumpContext& dc) const
{
	BaseSplitView::Dump(dc);
}
_vmssyncheditorDoc* CSynchEditorView1::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(_vmssyncheditorDoc)));
	return (_vmssyncheditorDoc*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSynchEditorView1 message handlers

int CSynchEditorView1::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (BaseSplitView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pdoctemplateMidiTrackSelect = new CMultiDocTemplate(
		IDR_MIDISELECTTRACK,
		RUNTIME_CLASS(CMidiTrackSelectDoc),
		RUNTIME_CLASS(CMidiTrackSelectFrame), // custom MDI child frame
		RUNTIME_CLASS(CMidiTrackSelectView));

   
   SetPaneCount(2);

   SetSplitOrientation(OrientationHorizontal);
  
   SetPosition(0, 200);

   

   CreateContext cc;
   cc.m_pCurrentDoc = GetDocument();
   cc.m_pNewViewClass =  RUNTIME_CLASS(CSynchEditorTokenListView);

   CSynchEditorTokenListView * plist = (CSynchEditorTokenListView *) CreateView(&cc, 100);


   

   SetPane(0, plist, false);

   cc.m_pCurrentDoc = GetDocument();
   cc.m_pNewViewClass =  RUNTIME_CLASS(SynchEditorMediaView);

   SynchEditorMediaView * pmediaview = (SynchEditorMediaView *) CreateView(&cc, 101);
   //CXView * pmediaview = (CXView*)RUNTIME_CLASS(CXView)->CreateObject();
   //SynchEditorMediaView * pmediaview = (SynchEditorMediaView *) RUNTIME_CLASS(SynchEditorMediaView)->CreateObject();
   //delete pmediaview;
   

   SetPane(1, pmediaview, false);

   Layout();
	
	return 0;
}

CWnd* CSynchEditorView1::CreateView(CreateContext* pContext, UINT nID)
{
	ASSERT(m_hWnd != NULL);
	ASSERT(::IsWindow(m_hWnd));
	ASSERT(pContext != NULL);
	ASSERT(pContext->m_pNewViewClass != NULL);

	// Note: can be a CWnd with PostNcDestroy self cleanup
	CWnd* pView = (CWnd*)pContext->m_pNewViewClass->CreateObject();
	if (pView == NULL)
	{
		TRACE1("Warning: Dynamic create of view type %hs failed.\n",
			pContext->m_pNewViewClass->m_lpszClassName);
		return NULL;
	}
	ASSERT_KINDOF(CWnd, pView);

	// views are always created with a border!
	if (!pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0,0,0,0), this, nID, (CCreateContext *) pContext))
	{
		TRACE0("Warning: could not create view for frame.\n");
		return NULL;        // can't continue without a view
	}

   ((CView *) pView)->OnInitialUpdate();
/*	if (afxData.bWin4 && (pView->GetExStyle() & WS_EX_CLIENTEDGE))
	{
		// remove the 3d style from the frame, since the view is
		//  providing it.
		// make sure to recalc the non-client area
		ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
	}*/
	return pView;
}

void CSynchEditorView1::OnFileInsert() 
{

   CXfplayerOpenFileDialog dlgFile;
	
	dlgFile.DoPrompt(IDS_XFPLAYER_OPENFILETITLE,
		OFN_HIDEREADONLY
		| OFN_FILEMUSTEXIST
		| OFN_EXPLORER);

   AStrArray & stra = dlgFile.m_straFile;

   CString str = stra[0];

	OpenDocument(str);

   GetDocument()->m_iLyricTrack = -1;

   CEventsTracksV1 * peventsarray
      = &GetDocument()->GetMediaViewData()->GetKaraokeData().GetStaticData().m_eventsTracksForPositionCB;

   LyricEventsV2 * pevents;
   if(peventsarray == NULL ||
      peventsarray->GetSize() <= 0)
      pevents = NULL;
   else
   {
//      pevents = (LyricEventsV2 *) peventsarray->operator [](staticdata.m_str2aRawTokens.GetSize());
      pevents = (LyricEventsV2 *) peventsarray->ElementAt(0);
      ASSERT(pevents != NULL);
      ASSERT(pevents->GetClassOrder() == 2);
   }

   m_pdocMidiTrackSelect = (CMidiTrackSelectDoc *) m_pdoctemplateMidiTrackSelect->OpenDocumentFile(NULL);
   MidiTrackSelectDDX * pddx = new MidiTrackSelectDDX();
   pddx->m_pcontrol = GetDocument();
   pddx->m_pselect = m_pdocMidiTrackSelect;
   m_pdocMidiTrackSelect->m_pddx = pddx;
   GetDocument()->m_pddx = pddx;
   pddx->m_pselect->Initialize(&GetDocument()->GetMediaViewData()->GetMidiSequence(), true);

   GetDocument()->UpdateAllViews(NULL, 100, 0);

}

bool CSynchEditorView1::OpenDocument(LPCTSTR lpszPathName)
{
	if(lpszPathName == NULL)
	{
        return true;
	}

   WString wstr;

   International::ACPToUnicode(wstr, lpszPathName);

   GetDocument()->GetMediaViewData()->OnOpenDocument(wstr);

   GetDocument()->UpdateAllViews(NULL, 100);

/*   CMidiFile & midifile = GetMidiSequence().GetFile();
	CMidiUtil midiutil;
   if(m_microke1.IsMicroke1File(lpszPathName))
   {
      CMidiSequence seqKar;
      CMemoryStorage storage;
      if(!m_microke1.GetFile(lpszPathName, storage))
         return false;
      seqKar.OpenFile(&storage, CMidiFile::OpenForPlaying, false);
      midiutil.ConvertKarToXF(seqKar, GetMidiSequence(), CMidiFile::OpenForPlaying);
   }
   else if(m_karaokeutil.IsStar350File(lpszPathName))
   {
      CFile file(
         lpszPathName,
         CFile::modeRead |
         CFile::shareDenyWrite |
         CFile::typeBinary);
        
      CArchive ar(&file, CArchive::load);
      CStar350File starFile;
      starFile.OpenFile(ar, 0);
      m_karaokeutil.ConvertStar350ToXF(&starFile, &GetMidiSequence(), CMidiFile::OpenForPlaying);
      GetMidiSequence().GetFile().ToWorkStorage();
    }
   else
   {
      CFile file(
         lpszPathName,
         CFile::modeRead |
         CFile::shareDenyWrite |
         CFile::typeBinary);
        
      CArchive ar(&file, CArchive::load);
      GetMidiSequence().OpenFile(ar, CMidiFile::OpenForPlaying);
      midiutil.ConvertToXF(GetMidiSequence(), CMidiFile::OpenForPlaying);
   }
	GetMidiSequence().GetFile().GetTracks().GetXFInfoHeaders(&m_xfInfoHeaders);
   PrepareMidiLyrics();*/
   return TRUE;
}

MidiSequence & CSynchEditorView1::GetMidiSequence()
{
   return GetDocument()->GetMediaViewData()->GetMidiSequence();
}

void CSynchEditorView1::PrepareMidiLyrics()
{
/*   CMidiTracks & tracks = GetDocument()->GetMidiSequence().GetFile().GetTracks();

   CBaseArray <CStrArray, CStrArray &> & str2aTokens = GetDocument()->m_str2aRawTokens;
   _vmsmediai::CPosition2DArray & tk2aTokensTicks = GetDocument()->m_tk2aTokensTicks;

   tracks.WorkSeekBegin();
   tracks.WorkGetXFTokens(
      str2aTokens,
      tk2aTokensTicks,
      NULL);

   GetDocument()->UpdateAllViews(NULL, 0, NULL);*/
   
}
