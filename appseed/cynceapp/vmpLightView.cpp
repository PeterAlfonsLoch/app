// vmpLightView.cpp : implementation of the CVmpLightView class
//

#include "stdafx.h"
#include "vmpLight.h"

#include "vmpLightDoc.h"
#include "vmpLightView.h"

#include "_vmsgenHighThread.h"
#include "_vmsgenHighThreadContainer.h"

#include "KaraokeData.h"
#include "KaraokeDynamicData.h"
#include "KaraokeStaticData.h"

#include "MidiException.h"

#include "ErrorDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVmpLightView

IMPLEMENT_DYNCREATE(CVmpLightView, CView)

BEGIN_MESSAGE_MAP(CVmpLightView, CView)
	//{{AFX_MSG_MAP(CVmpLightView)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_COMMAND(ID_EXECUTE_PLAY, OnExecutePlay)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_PLAY, OnUpdateExecutePlay)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVmpLightView construction/destruction

CVmpLightView::CVmpLightView()
{
	// TODO: add construction code here

}

CVmpLightView::~CVmpLightView()
{
}

BOOL CVmpLightView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CVmpLightView drawing

void CVmpLightView::OnDraw(CDC* pDC)
{
	CVmpLightDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CVmpLightView printing

BOOL CVmpLightView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVmpLightView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVmpLightView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CVmpLightView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CVmpLightView diagnostics

#ifdef _DEBUG
void CVmpLightView::AssertValid() const
{
	CView::AssertValid();
}

void CVmpLightView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVmpLightDoc* CVmpLightView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVmpLightDoc)));
	return (CVmpLightDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVmpLightView message handlers


CWinThread * CVmpLightView::GetMidiPlayerCallbackThread()
{
   return &_vmsgen::CHighThreadContainer::AppGetHighThread();
}

CMidiSequence & CVmpLightView::GetMidiSequence()
{
   return GetDocument()->GetMidiSequence();
}

void CVmpLightView::ExecutePlay(bool bMakeVisible)
{
   CVmpLightDoc * pdoc = GetDocument();
   if(pdoc->GetMode() == CVmpLightDoc::ModeWave)
   {
//      _vmsaudio::CWavePlayer::CCommand command;
  //    command.OpenDevice();
    //  m_pwaveplayer->ExecuteCommand(command);
      //command.Play();
      //m_pwaveplayer->ExecuteCommand(command);
      return;
   }
   
   
   CMidiSequence & midisequence = GetMidiSequence();
   ASSERT(&midisequence != NULL);
   
   CKaraokeData & data = GetKaraokeData();
   CKaraokeStaticData & staticdata = data.GetStaticData();
   CKaraokeDynamicData & dynamicdata = data.GetDynamicData();

   ASSERT(midisequence.GetState() == CMidiSequence::StatusNoFile);
/*   if (midisequence.GetState() == CMidiSequence::StatusNoFile)
   {
      CString str;
      CWStr wstr;
      
      int i3 = sizeof(CMidiPlayer);
      CString str3;
      str3.Format(_T("sizeof CMidiPlayer %d"), i3);
      
      COleVariant var;
      
      while(pplaylistdoc->PeekNextSongPath(wstr))
      {
         CInternational::UnicodeToOEM(str, wstr);
         int i4 = sizeof(CMidiPlayer);
         CString str4;
         str4.Format(_T("sizeof CMidiPlayer %d"), i4);
         
         var = wstr.AllocSysString();
         
         if(pdoc->OpenDocumentFile(var))
            break;
         UpdateReserveList();
      }
      
   }*/
   
   dynamicdata.m_iPlayingTokenIndex = -1;
   dynamicdata.m_iBufferTokenIndex = 0;
   //m_iBufferingTokenIndex = 0;
   //m_iBufferingOffsetTokenIndex = 0;
   //	pApp->SetPlayingDocument(this);
   
   //GetMidiPlayer()->SetMidiOutDevice(CMidiCentral::GetMidiCentral()->m_uiMidiOutDevice);
   
   if(GetMidiSequence().GetState() == CMidiSequence::StatusOpened)
   {
      pdoc->m_bPlay = true;
      try
      {
         GetMidiPlayer()->PostGMReset();
      }
      catch(CMidiException * pe)
      {
         CErrorDialog ed;
         ed.Initialize(pe);
         ed.DoModal();
         pe->Delete();
         return;
      }
      // execution continues in OnMmmsgDone
   }

}

void CVmpLightView::OnExecutePlay() 
{
	// TODO: Add your command handler code here
	
}

void CVmpLightView::OnUpdateExecutePlay(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(ExecuteGetPlayEnable());
}

bool CVmpLightView::ExecuteGetPlayEnable()
{
   CVmpLightDoc * pdoc = GetDocument();
   switch(pdoc->GetMode())
   {
   case CVmpLightDoc::ModeNone:
      return false;
   case CVmpLightDoc::ModeMidi:
      return GetMidiPlayer()
         && (pdoc->GetMidiSequence().GetState() == CMidiSequence::StatusOpened)
         && !ExecuteIsWaitingToPlay();
   case CVmpLightDoc::ModeWave:
//      return m_pwaveplayer->DecoderIsOpened()
//         && ! m_pwaveplayer->IsPlaying();
   default:
      ASSERT(FALSE);
      return false;
   }
}

void CVmpLightView::OnMidiPlayerNotifyEvent(CMidiPlayer::CNotifyEventPostData * pdata)
{
   CMidiPlayerInterface::OnMidiPlayerNotifyEvent(pdata);
   CMidiSequence & seq = pdata->m_pplayer->GetSequence();
   ASSERT(&seq == &GetMidiSequence());
   CVmpLightDoc * pdoc = GetDocument();
   
   if(pdata->m_enotifyevent
   == CMidiPlayer::NotifyEventPostPositionSet)
   {
//      OnProgressRateChange(); TODO
   }

//   CVmpApp * papp = (CVmpApp *) AfxGetApp();
//   ASSERT(papp != NULL);
   
   
//   CWinThread * pThreadV2  = papp->GetThreadV2();
//   ASSERT(pThreadV2 != NULL);
   
//   _vmsaudio::CWaveIn * pwavein = papp->GetAudioWaveCentral().GetWaveIn();
//   ASSERT(pwavein != NULL);
   if(pdata->m_enotifyevent == CMidiPlayer::NotifyEventPostGenericMmsgDone
      && pdoc->m_bPlay)
   {
      
      double dRate =	GetProgressSlider()->GetRate();
      if(dRate == 0.0)
      {
         //Show Title
  //       ShowTitle();
         
         // Time to let the title be visible
    //     m_msPlayTimeOut = timeGetTime() + 3000;
         
         //	    Sleep(3000);
      }
      else
      {
//         m_msPlayTimeOut = timeGetTime();
      }
      m_bWaitingToPlay = true;
      pdoc->m_bPlay = false;
   }
   //	else if(lpmdd->SequenceWasInSpecialModeV001())
   //  {
   //    TRACE(_T("CVmpLightDoc::OnMmsgDone lpmdd->SequenceWasInSpecialModeV001()\n"));
   //}
   else if(ExecuteIsSettingNextSong())
   {
      TRACE(_T("CVmpLightDoc::OnMmsgDone IsSettingNextSong()\n"));
      ((CXfplayerThreadV2*)pThreadV2)->EnableWaveInMessageTranslation(false);
      if(pwavein->IsRecording())
      {
         pwavein->Reset();
      }
      seq.CloseFile();
      m_dProgressRate = 0.0;
      ExecutePlay(true);
      m_bSettingNextSong = false;
   }
   else if(pdata->m_enotifyevent
      == CMidiPlayer::NotifyEventPostPlaybackEnd)
   {
      pdoc->DBSaveSongEncoding(pdoc->GetPathName());
      pdoc->StartScoring(false);
      m_dProgressRate = 0.0;
      CXfplayerViewUpdateHint uh;
      uh.AddType(CXfplayerViewUpdateHint::TypeProgressRateChange);
      pdoc->UpdateAllViews(NULL, 0, &uh);
      if(ExecuteHasNextSong())
      {
         ExecuteNextSong(true, true);
      }
      TRACE(_T("CVmpLightDoc::OnMmsgDone NotifyEventPlaybackEnd \n"));
   }
   else if(pdata->m_enotifyevent
      == CMidiPlayer::NotifyEventPostStop)
   {
      TRACE(_T("CVmpLightDoc::OnMmsgDone Else if Stopping\n"));
      pdoc->StartScoring(false);
      m_dProgressRate = 0.0;
      CXfplayerViewUpdateHint uh;
      uh.AddType(CXfplayerViewUpdateHint::TypeProgressRateChange);
      pdoc->UpdateAllViews(NULL, 0, &uh);
      
   }
   else 
   {
      int i = 0;
      i++;
   }
   pdoc->OnMidiPlayerNotifyEvent(pdata);
   
}

bool CVmpLightView::ExecuteIsWaitingToPlay()
{
   return m_bWaitingToPlay;
}

void CVmpLightView::OnTimer(UINT nIDEvent) 
{
      if(ExecuteIsWaitingToPlay())
      {
         if(timeGetTime() > GetPlayTimeOut())
         {
            StartMusicRendering();
            
         }
      }
	
	CView::OnTimer(nIDEvent);
}



void CVmpLightView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
}
