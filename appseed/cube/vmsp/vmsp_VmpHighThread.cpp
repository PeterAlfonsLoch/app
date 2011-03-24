#include "StdAfx.h"
#include "VmpHighThread.h"
#include "xfplayerdoc.h"
#include "xfplayerview.h"

// Nesta mensagem o wParam é este valor e lParam é o tempo em que a amostra
// foi recebida

CVmpHighThread::CVmpHighThread(::ca::application * papp)
: thread(papp)
{
   m_pMainApp = NULL;
   EnableTimers();
}


CVmpHighThread::~CVmpHighThread()
{
}

bool CVmpHighThread::initialize_instance()
{
   TRACE("CVmpHighThread::initialize_instance %X\n", get_os_data());
   SetMainWnd(NULL);
   ASSERT(GetMainWnd() == NULL);
   SetThreadPriority(THREAD_PRIORITY_HIGHEST);
   //SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);
#if  (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) // DCOM
   HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
   CoInitialize(NULL);
#endif
//   InitializeImageLoader();
   GdiSetBatchLimit(1);
    
   return true;
}

int CVmpHighThread::exit_instance()
{
   // TODO:  perform any per-thread cleanup here
//   if(m_pfiBitmap != NULL)
//   {
//      FreeImage_Free(m_pfiBitmap);
      //delete_object(m_hBitmap);
//   }
   DeleteTimersWindows();
   return thread::exit_instance();
}

 // BEGIN_MESSAGE_MAP(CVmpHighThread, thread)
   //{{AFX_MSG_MAP(CVmpHighThread)
      // NOTE - the ClassWizard will add and remove mapping macros here.
   //}}AFX_MSG_MAP
//   ON_THREAD_MESSAGE(VMSM_V001, OnVmsmV001)
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVmpHighThread message handlers

void CVmpHighThread::pre_translate_message(gen::signal_object * pobj) 
{
   SCAST_PTR(user::win::message::base, pbase, pobj);
   if(pbase->m_hwnd == NULL)
   {
      if(pbase->m_uiMessage == WM_APP + 3388)
      {
//         MSG msg3388 = *pMsg;
   //      MSG msg;
      
         /*while(pbase = peek_message(
            (HWND) INVALID_HANDLE_VALUE,
            WM_APP + 3388,
            WM_APP + 3388,
            PM_REMOVE))
         {
            //if(msg3388.wParam == 3388)
            //{
               //delete (base_array<LyricEventV1, LyricEventV1&> * ) msg3388.lParam;
            //}
            //msg3388 = msg;
         }
         TranslateApp3388Message(pbase);*/
         return;
      }
   }

      
   if(pbase->m_uiMessage == WM_APP + 114)
   {
      ASSERT(FALSE);
//      XfplayerView * pview = (XfplayerView *) pMsg->wParam;
//      _vmsgcom::CBackViewInterface::CImageChange::e_event eevent = (_vmsgcom::CBackViewInterface::CImageChange::e_event) pMsg->lParam;
//      pview->GetBackViewInterface().BackViewGetImageChange().PulseEvent(eevent);
   }
   else if(pbase->m_uiMessage == WM_TIMER)
   {
            
   }
   else if(pbase->m_uiMessage == WM_USER)
   {
      TranslateUserMessage(pobj);
      if(pobj->m_bRet)
         return;
   }
   else if(pbase->m_uiMessage == WM_USER + 1)
   {
//      CVMSApp * pApp = m_pMainApp;
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
         //CVMSApp * pApp = m_pMainApp;
         //ASSERT(pApp != NULL);
         //Sleep(1000);
         //pApp->GetMainWnd()->ShowWindow(SW_SHOWNORMAL);
//      }
      
   }
/*    else if(pMsg->message == VMSM_V001)
    {
    }*/
//    TRACE("CVmpHighThread pre_translate_message!!!\n");
    thread::pre_translate_message(pobj);
  //  TRACE("CVmpHighThread pre_translate_message Returned!!!\n");
    //return b;
}

void CVmpHighThread::TranslateUserMessage(gen::signal_object * pobj)
{
   SCAST_PTR(user::win::message::base, pbase, pobj);
   musctrl::MusicalPlayerCentral & playercentral = musctrl::MusicalPlayerCentral::AppGetMusicalPlayerCentral(get_app());
   musctrl::single_document_template * pdoctemplate = playercentral.get_document_template();
   ASSERT(pbase->m_uiMessage == WM_USER);
   if(pbase->m_wparam == 1) //&& m_pImageLoader != NULL)
   {
      ASSERT(FALSE);
//      _bstr_t * pBstr = (_bstr_t *) pMsg->lParam;
//      m_pImageLoader->LoadImage(*pBstr, (int) NULL);
//      delete pBstr;
   }
   else if(pbase->m_wparam == 2)
   {
      ASSERT(0);
//      OnLyricViewSize(pMsg->lParam);
   }
   else if(pbase->m_wparam == 3)
   {
//      if((QS_POSTMESSAGE & GetQueueStatus(QS_POSTMESSAGE)) > 0)
//      {
//         return;
//      }
      ASSERT(FALSE);
      CVMSApp * pApp = (CVMSApp *) &System;
      XfplayerDoc * pDoc = dynamic_cast < XfplayerDoc * > (pdoctemplate->get_document(0));
      XfplayerView * pview = pDoc->GetLyricView();
      pview->SendMessage(WM_USER, 3389);
      //pview->PostMessage(WM_USER, pMsg->lParam, 0);
       /* TRACE("CVmpHighThread::TranslateUserMessage 1 slGdi.Lock\n");
      CSingleLock slGdi(&pview->m_csGdi, TRUE);
      pview->m_voiceSpectrum.to(pApp->GetWaveIn()->GetFormatEx(), 0.0, 0.0);
      RECT rect;
      pview->m_voiceSpectrum.GetPlacement(&rect);
      //InvalidateRect(&rect, FALSE);
        TRACE("CVmpHighThread::TranslateUserMessage 1 slGdi.UnLock\n");
        slGdi.Unlock();
//        pview->RedrawWindow(&rect, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE | RDW_ALLCHILDREN);
        pview->to(&rect);*/
      //pview->to(&rect, TRUE);
      

   }
   else if(pbase->m_wparam == 4)
   {
//      if((QS_POSTMESSAGE & GetQueueStatus(QS_POSTMESSAGE)) > 0)
//      {
//         return;
//      }
      Scoring::UpdateMessage * lpsum = (Scoring::UpdateMessage *) pbase->m_lparam ;
      vmsp::application * papp = dynamic_cast < vmsp::application * > (&System);
/*      papp->GetMessageWindow()->SendMessage(
         WM_APP,
         178,
         (LPARAM) lpsum);*/
/*      papp->PostThreadMessage(
         WM_APP,
         178,
         (LPARAM) lpsum);*/

/*      XfplayerDoc * pdoc = (XfplayerDoc *) musctrl::userbase::single_document_template::AppGetPlayerDocTemplate()->get_document(0);
        if(pdoc == NULL)
            return TRUE;
      CAudioSpectrumViewUpdateHint uh;
      uh.m_lpwaveformatex = papp->WaveCentralGetWaveIn()->GetFormatEx();         
      uh.m_dDeltaScore = lpSum->dDeltaScore;
      uh.m_dScoreAddUp = lpSum->dScoreAddUp;
      delete lpSum;
      lpSum = NULL;
      ::userbase::document_template * pdoctemplate = pdoc->GetAudioSpectrumDocTemplate();
      POSITION pos = pdoctemplate->get_document_count();
      if(pos != NULL)
      {
         ::userbase::document * pdoctarget = pdoctemplate->get_document(index);
         if(pdoctarget != NULL)
         {
            pdoctarget->update_all_views(NULL, 0, &uh);
         }
      }*/
      

/*      XfplayerView * pview = pDoc->GetLyricView();
      //pview->PostMessage(WM_USER, pMsg->lParam, 0);
        if(pview == NULL)
        {
            delete lpSum;
            return TRUE;
        }
        pview->SendMessage(WM_USER, 4, (LPARAM) lpSum);*/

      pbase->m_bRet = true;      
   }
   else if(pbase->m_wparam == 5)
   {
      ASSERT(FALSE);
        //TRACE("\nCVmpHighThread::TranslateUserMessage 5\n");
/*      LPONLOADIMAGESTRUCTURE lpoli = (LPONLOADIMAGESTRUCTURE) pMsg->lParam;
        if(lpoli == NULL)
        {
//            OnImageLoaded(NULL);
        }
        else
        {
//          OnImageLoaded(lpoli->m_hbitmap);
        }
      delete lpoli;*/
   }
   else if(pbase->m_wparam == 6)
   {
      ASSERT(FALSE);
//      LPONSTRETCHIMAGESTRUCTURE lposi = (LPONSTRETCHIMAGESTRUCTURE) pMsg->lParam;
//      OnImageStretched(lposi->m_hbitmap, lposi->m_cx, lposi->m_cy, lposi->m_iUserData);
//      delete lposi;
   }
   else if(pbase->m_wparam == 3388)
   {
      ASSERT(FALSE);
   }

}

void CVmpHighThread::TranslateApp3388Message(gen::signal_object * pobj)
{
   SCAST_PTR(user::win::message::base, pbase, pobj);
   musctrl::MusicalPlayerCentral & playercentral = musctrl::MusicalPlayerCentral::AppGetMusicalPlayerCentral(get_app());
   musctrl::single_document_template * pdoctemplate = playercentral.get_document_template();
   if(pbase->m_wparam == 3388)
   {
      // Lyric ::view Event
/*      CVMSApp * pApp = (CVMSApp *) &System;
      if(pApp != NULL)
      {
         XfplayerDoc * pDoc = (XfplayerDoc *) pdoctemplate->get_document(0);
         if(pDoc != NULL)
         {
            XfplayerView * pview = pDoc->GetLyricView();
            if(pview != NULL)
            {
               pview->SendMessage(WM_USER, 3388, lpmsg->lParam);
            }
         }
      }
      delete (base_array<LyricEventV1, LyricEventV1&> * ) lpmsg->lParam;*/
      pbase->m_bRet = true;
      return;
   }
}

BOOL CVmpHighThread::on_idle(LONG lCount) 
{
   // TODO: add your specialized code here and/or call the base class
   //TRACE("CVmpHighThread Alive!!!\n");
   return thread::on_idle(lCount);
}



//void CVmpHighThread::OnLyricViewSize(int iType, int cx, int cy)
/*void CVmpHighThread::OnLyricViewSize(int iType)
{
   CVMSApp * pApp = (CVMSApp *) &System;
   XfplayerDoc * pDoc = pApp->GetOnlyDocument();
   XfplayerView * pview = pDoc->GetLyricView();
   rect rect;
   pview->GetClientRect(&rect);
   int cx = rect.right;
   int cy = rect.bottom;

   if(cx <= 0)
      cx = 1;
   if(cy <= 0)
      cy = 1;
   if(pview->m_pfiBitmap == NULL)
       return;
   double horizRate, vertRate, rate;
   if(FreeImage_GetWidth(pview->m_pfiBitmap))
      horizRate = ((double) cx) / FreeImage_GetWidth(pview->m_pfiBitmap);
   else
      horizRate = 1.0;
   if(FreeImage_GetHeight(pview->m_pfiBitmap))
      vertRate = ((double) cy) / FreeImage_GetHeight(pview->m_pfiBitmap);
   else
      vertRate = 1.0;
   if(horizRate < vertRate)
      rate = horizRate;
   else
      rate = vertRate;
   int finalWidth, finalHeight; //, finalX, finalY;
   finalWidth = (int) ((double) FreeImage_GetWidth(pview->m_pfiBitmap) * rate);
   finalHeight = (int) ((double) FreeImage_GetHeight(pview->m_pfiBitmap) * rate);

   LPSTRETCHIMAGESTRUCTURE lpSi = new STRETCHIMAGESTRUCTURE;
   lpSi->m_pfiBitmap = pview->m_pfiBitmap;
   lpSi->cx = finalWidth;
   lpSi->cy = finalHeight;
   lpSi->iUserData = iType;
   pApp->GetThreadV3()->PostThreadMessage(WM_USER, 6, (LPARAM) lpSi);
}*/


void CVmpHighThread::DeleteTimersWindows()
{

}

void CVmpHighThread::EnableTimers(bool bEnable)
{
    m_bEnableTimers = bEnable;
}

void CVmpHighThread::ProcessMessageFilter(int code, gen::signal_object * pobj)
{
   SCAST_PTR(user::win::message::base, pbase, pobj);
   if(pbase->m_uiMessage == WM_TIMER)
   {
      if(m_bEnableTimers)
      {
         thread::ProcessMessageFilter(code, pobj);
         return;
      }
      else
      {
         pobj->m_bRet = true;
         return;
      }
   }
   thread::ProcessMessageFilter(code, pobj);
}

/*long CVmpHighThread::OnImageLoaded(
   HBITMAP  hbitmap)
//void CVmpHighThread::OnImageLoaded(
//   VARIANT * pVarInfoHeader,
//   VARIANT * bmBits)
{
    ASSERT(GetMainWnd() == NULL);
   CVMSApp * pApp = (CVMSApp *) &System;
   XfplayerDoc * pDoc = (XfplayerDoc *) musctrl::userbase::single_document_template::AppGetPlayerDocTemplate()->get_document(0);
   if(pDoc == NULL) // may be null
      return S_OK;      // on programa shutdown
   XfplayerView * pview = pDoc->GetLyricView();
    if(pview == NULL)
        return S_OK;
    TRACE("\nCVmpHighThread::OnImageLoaded before lock %X\n", get_os_int());
    //TRACE("CVmpHighThread::TranslateUserMessage 3 slGdi.Lock\n");
    CSingleLock slGdi(&pview->m_csGdi, true);
    //TRACE("\nCVmpHighThread::OnImageLoaded after lock %X\n", get_os_int());
   HBITMAP hBitmapOld = (HBITMAP) pview->m_bmpBackViewSource.Detach();
   pview->m_bmpBackViewSource.Attach(hbitmap);
   gen::savings & savings = System.savings();
//    if(iEconoMode != CVMSApp::SaveMemory)
  //  {
   ::ca::bitmap * pbmpOld = pview->m_dcBackViewSource.SelectObject(pview->m_bmpBackViewSource);
    if(pbmpOld != NULL)
    {
        if(hBitmapOld != NULL)
        {
           // ASSERT(pbmpOld->GetSafeHandle() == hBitmapOld);
        }
    }
    else
    {
      pview->m_bmpBackViewSource.delete_object();
        TRACE("CVmpHighThread::OnImageLoaded:Bitmap not selected\n");
    }
    //}
    if(hBitmapOld != NULL)
    {
        if(hBitmapOld != pview->m_bmpBackViewSourceOld.GetSafeHandle())
        {
           if(!delete_object(hBitmapOld))
            {
                ASSERT(FALSE);
                TRACE("CVmpHighThread::OnImageLoaded : Atenção! Bitmap não deletado\n");
            }
        }
    }
   slGdi.Unlock();

   if(pbmpOld == NULL)
   {
      delete_object(hbitmap);
        pview->PostMessage(WM_USER, 17, XfplayerView::CImageChange::EventLoadFailed);
      return S_OK;
   }
    //TRACE("CVmpHighThread::TranslateUserMessage 3 slGdi.UnLock\n");
   
    if(pview == NULL)
        return E_FAIL;
   if(hbitmap != NULL)
      //pview->PostMessage(WM_USER, 17, pview->BkImageChangeEventLoaded);
        pview->PostMessage(WM_USER, 17, XfplayerView::CImageChange::EventLoaded);
        //pview->BackgroundImageChangeStateMachine(pview->BkImageChangeEventLoaded);
   else
      //pview->BackgroundImageChangeStateMachine(pview->BkImageChangeEventLoadFailed);
        pview->PostMessage(WM_USER, 17, XfplayerView::CImageChange::EventLoadFailed);
    return S_OK;
}*/

//void CVmpHighThread::OnImageStretched(
//   VARIANT * pVarInfoHeader,
//   VARIANT * pVarBits,
//   VARIANT * pVarUserData,
//   int cx,
//   int cy)
/*long CVmpHighThread::OnImageStretched(
   HBITMAP hbitmap,
   long cx,
   long cy,
   long iUserData)
{
    ASSERT(GetMainWnd() == NULL);
try
{
   CVMSApp * pApp = (CVMSApp *) &System;
   XfplayerDoc * pDoc = (XfplayerDoc *) musctrl::userbase::single_document_template::AppGetPlayerDocTemplate()->get_document(0);
   if(pDoc == NULL) // may be null
      return false;      // on programa shutdown
   XfplayerView * pview = pDoc->GetLyricView();
try
{

   RECT rect;
   pview->GetClientRect(&rect);
    TRACE("CVmpHighThread::OnImageStretched slGdi.Lock\n");
    CSingleLock slGdi(&pview->m_csGdi, true);
//   HGDIOBJ hBitmapOld = pview->m_bmpScaled.Detach();
//   pview->m_bmpScaled.Attach(hbitmap);
//   pview->m_dcScaled.SelectObject(pview->m_bmpScaled);
//   delete_object(hBitmapOld);
    TRACE("CVmpHighThread::OnImageStretched slGdi.UnLock\n");
   slGdi.Unlock();


   pview->BackViewUpdateBuffer(false);
    pview->UpdateScreen(&rect);
   if(iUserData == 2)
   {
      pview->m_dwBackgroundLastUpdateTime = timeGetTime();
      pview->BackViewGetImageChange().m_estate = XfplayerView::CImageChange::StateTiming;
   }
    }
catch(...)
{
}
   if(iUserData == 2)
   {
      pview->m_dwBackgroundLastUpdateTime = timeGetTime();
      pview->BackViewGetImageChange().m_estate = XfplayerView::CImageChange::StateTiming;
   }
}
catch(...)
{
}
   return true;
 }*/

::ca::bitmap * CVmpHighThread::LoadImageSync(const char * lpcszImageFilePath)
{
   return System.imaging().LoadImageSync(lpcszImageFilePath, get_app());

}

int CVmpHighThread::DeleteTimerWnd(CTimerWnd *ptimerwnd)
{
    return TRUE;
}

bool CVmpHighThread::CreateTimer(gen::TimerCallback *ptc, UINT uiElapse, UINT uiIDEvent)
{
    /*LPTIMERCALLBACKCREATETIMER lptcct = new TIMERCALLBACKCREATETIMER;
    lptcct->m_pTimerCallback = ptc;
    lptcct->m_uiElapse = 2;
    lptcct->m_uiIDEvent = 1;*/
/*    PostThreadMessage(
        VMSM_V001,
        NOTIFY_TIMERCALLBACKCREATETIMER,
        (LPARAM) lptcct);*/

   return true;

}

int CVmpHighThread::run() 
{

   return thread::run();
   ASSERT_VALID(this);

   // for tracking the idle time state
/*   BOOL bIdle = TRUE;
   LONG lIdleCount = 0;

   // acquire and dispatch messages until a WM_QUIT message is received.
   for (;;)
   {
      // phase1: check to see if we can do idle work
      while (bIdle &&
         !::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE))
      {
         // call on_idle while in bIdle state
         if (!on_idle(lIdleCount++))
            bIdle = FALSE; // assume "no idle" state
      }

      // phase2: pump messages while available
      do
      {
         // pump message, but quit on WM_QUIT
         if (!pump_message())
            return exit_instance();

         // reset "no idle" state after pumping "normal" message
         if (is_idle_message(&m_msgCur))
         {
            bIdle = TRUE;
            lIdleCount = 0;
         }

      } while (::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE));
   }
*/
   ASSERT(FALSE);  // not reachable










   // TODO: add your specialized code here and/or call the base class
   
//   return thread::run();
}

LRESULT CVmpHighThread::OnVmsmV001(WPARAM wparam, LPARAM lparam)
{
/*   if(wparam == NOTIFY_TIMERCALLBACKCREATETIMER)
    {
        CSingleLock sl(&m_csTimersWindows, TRUE);
        LPTIMERCALLBACKCREATETIMER lptcct = (LPTIMERCALLBACKCREATETIMER) lparam;
        delete lptcct;
        return TRUE;
    }
    else if(wparam == NOTIFY_TIMERCALLBACKDELETETIMER)
    {
        CSingleLock sl(&m_csTimersWindows, TRUE);
        return TRUE;
        
    }
   else
   {
      return FALSE;
   }*/
   return FALSE;
}

/*CVmpHighThread * CVmpHighThread::AppGetHighThread()
{
   return (dynamic_cast < vmsp::application * >(&System))->GetHighThread();
}*/
