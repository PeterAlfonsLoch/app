#include "StdAfx.h"
#include "XfplayerThreadV2.h"
#include "VmpHighThread.h"
#include "xfplayerdoc.h"
#include "xfplayerview.h"

// Nesta mensagem o wParam é este valor e lParam é o tempo em que a amostra
// foi recebida

XfplayerThreadV2::XfplayerThreadV2(::ca::application * papp)
: thread(papp)
{
   m_pMainApp = dynamic_cast < vmsp::application * > (&System);
//   m_pSplash = NULL;
//   m_pSplash = NULL;
}

XfplayerThreadV2::~XfplayerThreadV2()
{

}

bool XfplayerThreadV2::initialize_instance()
{
   TRACE("XfplayerThreadV2::initialize_instance %X\n", get_os_int());
   SetMainWnd(NULL);
   ASSERT(GetMainWnd() == NULL);
   SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);
#if  (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) // DCOM
   HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
   CoInitialize(NULL);
#endif
   GdiSetBatchLimit(1);
   // TODO:  perform and per-thread initialization here
   return true;
}

int XfplayerThreadV2::exit_instance()
{
   // TODO:  perform any per-thread cleanup here
//   if(m_pSplash != NULL)
//   {
//      delete m_pSplash;
//      m_pSplash = NULL;
//   }
   return thread::exit_instance();
}

 // BEGIN_MESSAGE_MAP(XfplayerThreadV2, thread)
   //{{AFX_MSG_MAP(XfplayerThreadV1)
      // NOTE - the ClassWizard will add and remove mapping macros here.
   //}}AFX_MSG_MAP
//    ON_THREAD_MESSAGE(WM_USER, OnUserMessage)
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// XfplayerThreadV1 message handlers

void XfplayerThreadV2::pre_translate_message(gen::signal_object * pobj) 
{
   SCAST_PTR(user::win::message::base, pbase, pobj);
   ASSERT(GetMainWnd() == NULL);
   if(pbase->m_uiMessage == MM_WIM_OPEN ||
      pbase->m_uiMessage == MM_WIM_CLOSE ||
      pbase->m_uiMessage == MM_WIM_DATA)
   {
      TranslateWaveInMessage(pobj);
      if(pobj->m_bRet)
         return;
   }
//   else if(pMsg->message == WM_USER)
//   {
  //      return FALSE;
   //   if(TranslateUserMessage(pMsg))
   //      return TRUE;
//   }
   else if(pbase->m_uiMessage == WM_USER + 1)
   {
      ASSERT(0);
//      vmsp::application * pApp = m_pMainApp;
//      ASSERT(pApp != NULL);
//      m_pSplash = new CSplash();
//      m_pSplash->create(IDD_SPLASH);
//      GetMainWnd() = m_pSplash;
//      m_pSplash =  new CBitmapWindow(IDB_SPLASH);
//      m_pSplash->CreateEx(
//      WS_EX_TOOLWINDOW,
//      pApp->m_XFToolTipV1ClassName,
//      "XFPlayer.SplashScreen",
//      WS_POPUP,
//      0, 0,
//   0, 0,
//      NULL, 
//      NULL,
//      NULL);
//      m_pSplash->ShowWindow(SW_SHOWNORMAL);
   //m_evWait.Lock();

   }
   else if(pbase->m_uiMessage == WM_USER + 2)
   {
      ASSERT(0);
//      if(m_pSplash != NULL)
//      {
//         if(::IsWindow(m_pSplash->m_hWnd))
//         {
//            m_pSplash->SetParent(m_pMainApp->GetMainWnd());
//            m_pSplash->ShowWindow(SW_HIDE);
//            m_pMainApp->GetMainWnd()->ShowWindow(SW_SHOWNORMAL);
//            m_pMainApp->GetMainWnd()->SetFocus();
//            m_pMainApp->GetMainWnd()->SetActiveWindow();
//            SetWindowPos(m_pMainApp->GetMainWnd()->m_hWnd,
//               HWND_TOP,
//               0, 0,
//               0, 0,
//               SWP_NOMOVE |
//               SWP_NOSIZE);
//            
//            m_pMainApp->GetMainWnd()->ShowWindow(SW_HIDE);
//            m_pMainApp->GetMainWnd()->ShowWindow(SW_SHOWNORMAL);
//            m_pMainApp->GetMainWnd()->BringWindowToTop();
//         }
         //delete m_pSplash;
         //m_pSplash = NULL;
//         m_pSplash->SendMessage(WM_CLOSE);
//         System.PostThreadMessage(WM_USER + 1, 0, 0);
         //vmsp::application * pApp = m_pMainApp;
         //ASSERT(pApp != NULL);
         //Sleep(1000);
         //pApp->GetMainWnd()->ShowWindow(SW_SHOWNORMAL);
//      }
      
   }
   thread::pre_translate_message(pobj);
}

void XfplayerThreadV2::_001InstallMessageHandling(::user::win::message::dispatch * pinterface) 
{
   IGUI_WIN_MSG_LINK(WM_USER, pinterface, this, &XfplayerThreadV2::OnUserMessage);
}

void XfplayerThreadV2::OnUserMessage(gen::signal_object * pobj)
{

/*   if(wParam == WAVM_WAVE_PROC_DATA)
   {
//      TRACE("XfplayerThreadV1::TranslateUserMessage current thread %X\n", GetCurrentThreadId());
      _vmsaudio::LPWAVEPROCDATAMESSAGE lpwdm = (_vmsaudio::LPWAVEPROCDATAMESSAGE) lParam;
      ASSERT(lpwdm != NULL);
      LPWAVEHDR lpwavehdr= lpwdm->m_lpwavehdr;
      ASSERT(lpwavehdr != NULL);
      XfplayerDoc * pdoc = (XfplayerDoc *) lpwdm->m_pUserData;
      if(pdoc == NULL)
        //if(true) // cut processing
      {
         delete lpwdm;
         return;
      }
      ASSERT(pdoc != NULL);
      ::mus::midi::sequence & seq  = pdoc->HelperGetMidiSequence();
      ASSERT(!seq.IsNull());
      
      audWaveIn * pwavein = lpwdm->m_pwavein;
      ASSERT(pwavein != NULL);
        critical_section & csHandle = pwavein->GetHandleCriticalSection();
        CSingleLock  sl(&csHandle, true);
      if(!pwavein->IsResetting() &&
            pwavein->IsRecording())
      {
           if(MMSYSERR_NOERROR != waveInAddBuffer(
            pwavein->GetSafeHwavein(),  
            lpwdm->m_lpwavehdr,
            sizeof(WAVEHDR)))
         {
            TRACE("ERROR OPENING Adding INPUT DEVICE buffer");
         }
      }
      else
      {
         TRACE("\nDOES IT WORKS!!!!!!!!!!!!!!!??????????\n");
      }
        sl.Unlock();
        
      if(!m_bEnableWaveInMessageTranslation)
        //if(true)
      {
         delete lpwdm;
         return;
      }

      DWORD msPosition;
      DWORD dwPositionTime;
      DWORD dwSampleTime;
      if(seq.GetState() != ::mus::midi::sequence::StatusNoFile)      
      {
         dwSampleTime = lpwdm->m_msSampleTime;
         imedia::position tkPosition;
         seq.get_time(&tkPosition);
         dwPositionTime = timeGetTime();
         msPosition = seq.TicksToMillisecs(tkPosition);
         msPosition -= dwPositionTime - dwSampleTime;

         // Valor de Correção
         msPosition -= 100;
      }
      
      audWaveBuffer & buffer = pwavein->GetBuffer();
      buffer.FFTProcess(lpwavehdr);
      double dDeltaScore = -100.0;
      XfplayerScoring * pscoring = pdoc->GetScoring();
      if(seq.GetState() != ::mus::midi::sequence::StatusNoFile
         && pscoring->IsEnabled())      
      {
         ::mus::midi::file & file = seq.GetFile();
         ASSERT(!spfile->IsNull());
         EventsTracksV1 * peventsa = &spfile->m_eventsTracksForScoring;
         LyricEventsV2 * pevents;
//         if(pDoc->m_p2DTokens == NULL)
//            pEvents = NULL;
         //else if(pDoc->m_p2DTokens->get_size() <= 0)
         if(spfile->m_str2aRawTokens.get_size() <= 0)
            pevents = NULL;
         else if(peventsa->get_size() < spfile->m_str2aRawTokens.get_size())
            pevents = NULL;
         else
         {
            //pEvents = (LyricEventsV2 *) pEventsArray->operator [](pDoc->m_p2DTokens->get_size());
            pevents = (LyricEventsV2 *) peventsa->operator [](0);
            ASSERT(pevents != NULL);
            ASSERT(pevents->GetClassOrder() == 2);
         }

         
         
         if(pevents != NULL)
         {
            int i;
            m_iaNotes.remove_all();
            pevents->GetMillisIntervalNotes(
               m_iaNotes,
               msPosition  - pwavein->GetAnalysisMillis() - 100,
               msPosition);
//               msPosition - 100);
            dDeltaScore = 0;
            dword_array dwaNotes;
            for(i = 0; i < m_iaNotes.get_size(); i++)
            {
               dwaNotes.add(pevents->GetNotePitch(m_iaNotes.element_at(i)));
            }
            pscoring->Process(&dwaNotes, (double) msPosition / seq.m_msLength, &dDeltaScore );
         }
      }
      Scoring::UpdateMessage * lpsum = new Scoring::UpdateMessage();
      lpsum->m_dDeltaScore = dDeltaScore;
      lpsum->m_dScoreAddUp = pscoring->m_dScoreAddUp;
      vmsp::application * papp = dynamic_cast < vmsp::application * > (&System);
      papp->GetHighThread()->PostThreadMessage(WM_USER, 4, (LPARAM) lpsum);

//      XfplayerView * pview = pDoc->GetLyricView();
//      pview->PostMessage(WM_USER, 7788, 0);

      delete lpwdm;
      return;
   }*/
}

BOOL XfplayerThreadV2::TranslateUserMessage(MSG *pMsg)
{
   ASSERT(FALSE);
/*   ASSERT(pMsg->message == WM_USER);
   if(pMsg->wParam == WAVM_WAVE_PROC_DATA)
   {
//      TRACE("XfplayerThreadV1::TranslateUserMessage current thread %X\n", GetCurrentThreadId());
      LPWAVEPROCDATAMESSAGE lpwdm = (LPWAVEPROCDATAMESSAGE) pMsg->lParam;
      ASSERT(lpwdm != NULL);
      LPWAVEHDR lpWaveHdr= lpwdm->lpWaveHdr;
      ASSERT(lpWaveHdr != NULL);
      XfplayerDoc * pDoc = (XfplayerDoc *) musctrl::userbase::single_document_template::AppGetPlayerDocTemplate()->get_document(0);
      //if(pDoc == NULL)
            if(true)
      {
         delete lpwdm;
         return TRUE;
      }
      ASSERT(pDoc != NULL);
      ::mus::midi::sequence * pSeq  = pDoc->HelperGetMidiSequence();
      ASSERT(pSeq != NULL);
      
      vmsp::application * pApp = m_pMainApp;
      ASSERT(pApp != NULL);
      CWaveIn * pWaveIn = pApp->GetWaveIn();
      ASSERT(pWaveIn != NULL);
        critical_section & csHandle = pWaveIn->GetHandleCriticalSection();
        CSingleLock  sl(&csHandle, true);
      if(!pWaveIn->IsResetting())
      {
           if(MMSYSERR_NOERROR != waveInAddBuffer(
            pWaveIn->GetSafeHwavein(),  
            lpwdm->lpWaveHdr,
            sizeof(WAVEHDR)))
         {
            TRACE("ERROR OPENING Adding INPUT DEVICE buffer");
         }
      }
      else
      {
         TRACE("\nDOES IT WORKS!!!!!!!!!!!!!!!??????????\n");
      }
        csHandle.Unlock();
//      if(!m_bEnableWaveInMessageTranslation)
        if(true)
      {
         delete lpwdm;
         return TRUE;
      }

      DWORD msPosition;
      DWORD dwPositionTime;
      DWORD dwSampleTime;
      if(pSeq->GetState() != ::mus::midi::sequence::StatusNoFile)      
      {
         dwSampleTime = lpwdm->msSampleTime;
         imedia::position tkPosition;
         pSeq->get_time(&tkPosition);
         dwPositionTime = timeGetTime();
         msPosition = pSeq->TicksToMillisecs(tkPosition);
         msPosition -= dwPositionTime - dwSampleTime;

         // Valor de Correção
         msPosition -= 100;
      }
      
      CWaveBuffer * pWaveBuffer = pWaveIn->GetBuffer();
      ASSERT(pWaveBuffer != NULL);
        TRACE("XfplayerThreadV2::TranslateUserMessage Process In %d\n", timeGetTime());
      pWaveBuffer->Process(lpWaveHdr->dwUser);
        TRACE("XfplayerThreadV2::TranslateUserMessage Process Out %d\n", timeGetTime());
      double dDeltaScore = -100.0;
      XfplayerScoring * pScoring = pDoc->GetScoring();
      if(pSeq->GetState() != ::mus::midi::sequence::StatusNoFile)      
      {
         ::mus::midi::file * pFile = pSeq->GetFile();
         ASSERT(pFile != NULL);
         EventsTracksV1 * pEventsArray = &pFile->m_eventsTracksForScoring;
         LyricEventsV2 * pEvents;
//         if(pDoc->m_p2DTokens == NULL)
//            pEvents = NULL;
         //else if(pDoc->m_p2DTokens->get_size() <= 0)
//            if(pDoc->m_str2aRawTokens.get_size() <= 0)
//            pEvents = NULL;
//         else if(pEventsArray->get_size() < pDoc->m_str2aRawTokens.get_size())
//            pEvents = NULL;
//         else
//         {
            //pEvents = (LyricEventsV2 *) pEventsArray->operator [](pDoc->m_p2DTokens->get_size());
            pEvents = (LyricEventsV2 *) pEventsArray->operator [](0);
            ASSERT(pEvents != NULL);
            ASSERT(pEvents->GetClassOrder() == 2);
//         }

         
         
         if(pEvents != NULL)
         {
            int i;
            m_iaNotes.remove_all();
            pEvents->GetMillisIntervalNotes(
               m_piaNotes,
               msPosition  - pWaveIn->GetAnalysisMillis() - 100,
               msPosition);
//               msPosition - 100);
            dDeltaScore = 0;
            dword_array dwaNotes;
            for(i = 0; i < m_iaNotes.get_size(); i++)
            {
               dwaNotes.add(pEvents->GetNotePitch(m_iaNotes.get_at(i)));
            }
            pScoring->Process(&dwaNotes, (double) msPosition / pSeq->m_msLength, &dDeltaScore );
            //for(i = 0; i < m_iaNotes.get_size(); i++)
            //{
            //   //TRACE("dwPositionTime - dwSampleTime %d\n", dwPositionTime - dwSampleTime);
            //   pScoring->Process(pEvents->GetNotePitch(m_iaNotes.get_at(i)), (double) msPosition / pSeq->m_msLength, &dDeltaScore );
            //}

         }
      }
      LPSCOREUPDATEMESSAGE lpSum = new SCOREUPDATEMESSAGE();
      lpSum->dDeltaScore = dDeltaScore;
      lpSum->dScoreAddUp = pScoring->m_dScoreAddUp;
      vmsp::application * papp = dynamic_cast < vmsp::application * > (&System);
      papp->GetThreadV1()->PostThreadMessage(WM_USER, 4, (LPARAM) lpSum);

//      XfplayerView * pview = pDoc->GetLyricView();
//      pview->PostMessage(WM_USER, 7788, 0);

      delete lpwdm;
      return TRUE;
   }*/
   return FALSE;
}

BOOL XfplayerThreadV2::on_idle(LONG lCount) 
{
   // TODO: add your specialized code here and/or call the base class
   //TRACE("XfplayerThreadV1 Alive!!!\n");
   return thread::on_idle(lCount);
}

void XfplayerThreadV2::TranslateWaveInMessage(gen::signal_object * pobj)
{
   ASSERT(0);
   //return TRUE;
}

void XfplayerThreadV2::EnableWaveInMessageTranslation(bool bEnable)
{
   m_bEnableWaveInMessageTranslation = bEnable;
}
