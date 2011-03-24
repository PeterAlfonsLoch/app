// vrecView.cpp : implementation of the VRecView class
//

#include "stdafx.h"
#include "vrec.h"

#include "vrecDoc.h"
#include "vrecView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// VRecView

IMPLEMENT_DYNCREATE(VRecView, BaseView)

BEGIN_MESSAGE_MAP(VRecView, BaseView)
	//{{AFX_MSG_MAP(VRecView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, BaseView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, BaseView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, BaseView::OnFilePrintPreview)
   ON_COMMAND(ID_EXECUTE_PLAY, OnExecutePlay)
   ON_COMMAND(ID_EXECUTE_RECORD, OnExecuteRecord)
   ON_COMMAND(ID_EXECUTE_STOP, OnExecuteStop)
   ON_UPDATE_COMMAND_UI(ID_EXECUTE_PLAY, OnUpdateExecutePlay)
   ON_UPDATE_COMMAND_UI(ID_EXECUTE_RECORD, OnUpdateExecuteRecord)
   ON_UPDATE_COMMAND_UI(ID_EXECUTE_STOP, OnUpdateExecuteStop)
   ON_MESSAGE(WM_APP + 119, OnPlayerEvent)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VRecView construction/destruction

VRecView::VRecView()
{
   m_estate = StateInitial;
	// TODO: add construction code here
   m_precorder = (audio::WaveRecorder *) AfxBeginThread(
      RUNTIME_CLASS(audio::WaveRecorder));
   m_pplayer = (audio::WavePlayer *) AfxBeginThread(
      RUNTIME_CLASS(audio::WavePlayer));

   


}

VRecView::~VRecView()
{
}

BOOL VRecView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return BaseView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// VRecView drawing

void VRecView::OnDraw(CDC* pDC)
{
	VRecDocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// VRecView printing

BOOL VRecView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void VRecView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void VRecView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// VRecView diagnostics

#ifdef _DEBUG
void VRecView::AssertValid() const
{
	BaseView::AssertValid();
}

void VRecView::Dump(CDumpContext& dc) const
{
	BaseView::Dump(dc);
}

VRecDocument* VRecView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(VRecDocument)));
	return (VRecDocument*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// VRecView message handlers


void VRecView::OnExecutePlay()
{


   m_estate = StatePlaying;

   m_pplayer->SetCallback(GetSafeHwnd());

   audio::WavePlayerCommand command;
   //m_file.Open("c:\\teste.wav", notsad::File::modeRead | Ex1File::typeBinary);
   //command.OpenWavFile(&m_file);
   m_file.Open("c:\\simph9.wma", notsad::File::modeRead | Ex1File::typeBinary);
   command.OpenWmFile(&m_file);
   m_pplayer->ExecuteCommand(command);
   command.Play();
   m_pplayer->ExecuteCommand(command);

}

void VRecView::OnExecuteRecord()
{
   m_estate = StateRecording;
   //m_precorder->SetCallback(GetSafeHwnd());

   audio::WaveRecorderCommand command;
   //m_file.Open("c:\\teste.wav", notsad::File::modeRead | Ex1File::typeBinary);
   //command.OpenWavFile(&m_file);
   m_file.Open("c:\\rec.wav", notsad::File::modeCreate | notsad::File::modeWrite | Ex1File::typeBinary);
   command.OpenWavFile(&m_file);
   m_precorder->ExecuteCommand(command);
   command.Record();
   m_precorder->ExecuteCommand(command);}

void VRecView::OnExecuteStop()
{
   if(m_estate == StatePlaying)
   {
      audio::WavePlayerCommand command;
      command.Stop();
      m_pplayer->ExecuteCommand(command);
   }
   else if(m_estate == StateRecording)
   {
      audio::WaveRecorderCommand command;
      command.Stop();
      m_precorder->ExecuteCommand(command);
   }
   m_estate = StateInitial;
}

void VRecView::OnUpdateExecutePlay(CCmdUI * pcmdui)
{
   pcmdui->Enable(m_estate == StateInitial);
   pcmdui->SetCheck(m_estate == StatePlaying ? 1 : 0);
}

void VRecView::OnUpdateExecuteRecord(CCmdUI * pcmdui)
{
   pcmdui->Enable(m_estate == StateInitial);
   pcmdui->SetCheck(m_estate == StateRecording ? 1 : 0);
}

void VRecView::OnUpdateExecuteStop(CCmdUI * pcmdui)
{
   pcmdui->Enable(m_estate == StatePlaying ||
      m_estate == StateRecording);
}


LRESULT VRecView::OnPlayerEvent(WPARAM wparam, LPARAM lparam)
{
   audio::WavePlayer::EEvent eevent = (audio::WavePlayer::EEvent) wparam;
   if(eevent == audio::WavePlayer::EventStopped)
   {
      m_file.Close();
      m_estate = StateInitial;
   }
   return 0;
}