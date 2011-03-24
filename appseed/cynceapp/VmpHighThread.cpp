// XfplayerThreadV1.cpp : implementation file
//

#include "StdAfx.h"
#include "resource.h"
#include "VmpHighThread.h"
#include "VmpLightDoc.h"
#include "MPLightView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Nesta mensagem o wParam é este valor e lParam é o tempo em que a amostra
// foi recebida

/////////////////////////////////////////////////////////////////////////////
// CVmpHighThread

CVmpHighThread::CVmpHighThread()
{
}


CVmpHighThread::~CVmpHighThread()
{
}

BOOL CVmpHighThread::InitInstance()
{
    TRACE(_T("CVmpHighThread::InitInstance %X\n"), m_nThreadID);
    m_pMainWnd = NULL;
    ASSERT(m_pMainWnd == NULL);
	SetThreadPriority(THREAD_PRIORITY_HIGHEST);
    //SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);
#if  (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) // DCOM
	HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
	CoInitialize(NULL);
#endif
//	InitializeImageLoader();
	GdiSetBatchLimit(1);
    
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CVmpHighThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
//	if(m_pfiBitmap != NULL)
//	{
//		FreeImage_Free(m_pfiBitmap);
		//DeleteObject(m_hBitmap);
//	}
	DeleteTimersWindows();
	return Thread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CVmpHighThread, Thread)
	//{{AFX_MSG_MAP(CVmpHighThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_THREAD_MESSAGE(VMSM_V001, OnVmsmV001)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVmpHighThread message handlers

BOOL CVmpHighThread::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->hwnd == NULL)
	{
		if(pMsg->message == WM_APP + 3388)
		{
			MSG msg3388 = *pMsg;
			MSG msg;
		
			while(PeekMessage(
				&msg,
				(HWND) INVALID_HANDLE_VALUE,
				WM_APP + 3388,
				WM_APP + 3388,
				PM_REMOVE))
			{
				if(msg3388.wParam == 3388)
				{
					delete (BaseArray<LyricEventV1, LyricEventV1&> * ) msg3388.lParam;
				}
				msg3388 = msg;
			}
			return TranslateApp3388Message(&msg3388);
		}
	}

		
	if(pMsg->message == WM_APP + 114)
	{
		ASSERT(FALSE);
//		CXfplayerView * pview = (CXfplayerView *) pMsg->wParam;
//		_vmsgcom::CBackViewInterface::CImageChange::EEvent eevent = (_vmsgcom::CBackViewInterface::CImageChange::EEvent) pMsg->lParam;
//		pview->GetBackViewInterface().BackViewGetImageChange().PulseEvent(eevent);
	}
    else if(pMsg->message == WM_TIMER)
    {
            
    }
	if(pMsg->message == WM_USER)
	{
		BOOL b = TranslateUserMessage(pMsg);
		if(b)
			return TRUE;
	}
	else if(pMsg->message == WM_USER + 1)
	{
//		CVMSApp * pApp = m_pMainApp;
//		ASSERT(pApp != NULL);
//		m_pSplash = new CSplash();
//		m_pSplash->Create(IDD_SPLASH);
//		m_pMainWnd = m_pSplash;
//		m_pSplash =  new CBitmapWindow(IDB_SPLASH);
//		m_pSplash->CreateEx(
//		WS_EX_TOOLWINDOW,
//		pApp->m_XFToolTipV1ClassName,
//		_T("XFPlayer.SplashScreen"),
//		WS_POPUP,
//		0, 0,
//	0, 0,
//		NULL, 
//		NULL,
//		NULL);
//		m_pSplash->ShowWindow(SW_SHOWNORMAL);
	//m_evWait.Lock();

	}
	else if(pMsg->message == WM_USER + 2)
	{
//		if(m_pSplash != NULL)
//		{
//			if(::IsWindow(m_pSplash->m_hWnd))
//			{
//				m_pSplash->SetParent(m_pMainApp->m_pMainWnd);
//				m_pSplash->ShowWindow(SW_HIDE);
//				m_pMainApp->m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
//				m_pMainApp->m_pMainWnd->SetFocus();
//				m_pMainApp->m_pMainWnd->SetActiveWindow();
//				SetWindowPos(m_pMainApp->m_pMainWnd->m_hWnd,
//					HWND_TOP,
//					0, 0,
//					0, 0,
//					SWP_NOMOVE |
//					SWP_NOSIZE);
//				
//				m_pMainApp->m_pMainWnd->ShowWindow(SW_HIDE);
//				m_pMainApp->m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
//				m_pMainApp->m_pMainWnd->BringWindowToTop();
//			}
			//delete m_pSplash;
			//m_pSplash = NULL;
//			m_pSplash->SendMessage(WM_CLOSE);
//			AfxGetApp()->PostThreadMessage(WM_USER + 1, 0, 0);
			//CVMSApp * pApp = m_pMainApp;
			//ASSERT(pApp != NULL);
			//Sleep(1000);
			//pApp->m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
//		}
		
	}
    else if(pMsg->message == VMSM_V001)
    {
    }
//    TRACE(_T("CVmpHighThread PreTranslateMessage!!!\n"));
    BOOL b = Thread::PreTranslateMessage(pMsg);
  //  TRACE(_T("CVmpHighThread PreTranslateMessage Returned!!!\n"));
    return b;
}

BOOL CVmpHighThread::TranslateUserMessage(MSG *pMsg)
{
/*	musctrl::CMusicalPlayerCentral & playercentral =
		musctrl::CMusicalPlayerCentral::AppGetMusicalPlayerCentral();
	musctrl::CSingleDocTemplate * pdoctemplate =
		playercentral.GetDocTemplate();
	ASSERT(pMsg->message == WM_USER);*/
	if(pMsg->wParam == 1) //&& m_pImageLoader != NULL)
	{
		ASSERT(FALSE);
//		_bstr_t * pBstr = (_bstr_t *) pMsg->lParam;
//		m_pImageLoader->LoadImage(*pBstr, (int) NULL);
//		delete pBstr;
	}
	else if(pMsg->wParam == 2)
	{
		ASSERT(0);
//		OnLyricViewSize(pMsg->lParam);
	}
	else if(pMsg->wParam == 3)
	{
//		if((QS_POSTMESSAGE & GetQueueStatus(QS_POSTMESSAGE)) > 0)
//		{
//			return;
//		}
		ASSERT(FALSE);
//		CVMSApp * pApp = (CVMSApp *) AfxGetApp();
/*		CXfplayerDoc * pDoc = (CXfplayerDoc *) pdoctemplate->GetOnlyDoc();
		CXfplayerView * pView = pDoc->GetLyricView();
        pView->SendMessage(WM_USER, 3389);*/
		//pView->PostMessage(WM_USER, pMsg->lParam, 0);
       /* TRACE(_T("CVmpHighThread::TranslateUserMessage 1 slGdi.Lock\n"));
		CSingleLock slGdi(&pView->m_csGdi, TRUE);
		pView->m_voiceSpectrum.Render(pApp->GetWaveIn()->GetFormatEx(), 0.0, 0.0);
		RECT rect;
		pView->m_voiceSpectrum.GetPlacement(&rect);
		//InvalidateRect(&rect, FALSE);
        TRACE(_T("CVmpHighThread::TranslateUserMessage 1 slGdi.UnLock\n"));
        slGdi.Unlock();
//        pView->RedrawWindow(&rect, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE | RDW_ALLCHILDREN);
        pView->Render(&rect);*/
		//pView->Render(&rect, TRUE);
		

	}
	else if(pMsg->wParam == 4)
	{
//		if((QS_POSTMESSAGE & GetQueueStatus(QS_POSTMESSAGE)) > 0)
//		{
//			return;
//		}
/*		CScoring::CUpdateMessage * lpsum = (CScoring::CUpdateMessage *) pMsg->lParam ;
		CVmpApp * papp = (CVmpApp *) AfxGetApp();
		papp->GetMessageWindow()->SendMessage(
			WM_APP,
			178,
			(LPARAM) lpsum); TODO*/ 
/*		papp->PostThreadMessage(
			WM_APP,
			178,
			(LPARAM) lpsum);*/

/*		CXfplayerDoc * pdoc = (CXfplayerDoc *) musctrl::CSingleDocTemplate::AppGetPlayerDocTemplate()->GetOnlyDoc();
        if(pdoc == NULL)
            return TRUE;
		CAudioSpectrumViewUpdateHint uh;
		uh.m_lpwaveformatex = papp->WaveCentralGetWaveIn()->GetFormatEx();			
		uh.m_dDeltaScore = lpSum->dDeltaScore;
		uh.m_dScoreAddUp = lpSum->dScoreAddUp;
		delete lpSum;
		lpSum = NULL;
		CDocTemplate * pdoctemplate = pdoc->GetAudioSpectrumDocTemplate();
		POSITION pos = pdoctemplate->GetFirstDocPosition();
		if(pos != NULL)
		{
			CDocument * pdoctarget = pdoctemplate->GetNextDoc(pos);
			if(pdoctarget != NULL)
			{
				pdoctarget->UpdateAllViews(NULL, 0, &uh);
			}
		}*/
		

/*		CXfplayerView * pView = pDoc->GetLyricView();
		//pView->PostMessage(WM_USER, pMsg->lParam, 0);
        if(pView == NULL)
        {
            delete lpSum;
            return TRUE;
        }
        pView->SendMessage(WM_USER, 4, (LPARAM) lpSum);*/

		
        return TRUE;

	}
	else if(pMsg->wParam == 5)
	{
		ASSERT(FALSE);
        //TRACE(_T("\nCVmpHighThread::TranslateUserMessage 5\n"));
/*		LPONLOADIMAGESTRUCTURE lpoli = (LPONLOADIMAGESTRUCTURE) pMsg->lParam;
        if(lpoli == NULL)
        {
//            OnImageLoaded(NULL);
        }
        else
        {
//		    OnImageLoaded(lpoli->m_hbitmap);
        }
		delete lpoli;*/
	}
	else if(pMsg->wParam == 6)
	{
		ASSERT(FALSE);
//		LPONSTRETCHIMAGESTRUCTURE lposi = (LPONSTRETCHIMAGESTRUCTURE) pMsg->lParam;
//		OnImageStretched(lposi->m_hbitmap, lposi->m_cx, lposi->m_cy, lposi->m_iUserData);
//		delete lposi;
	}
    else if(pMsg->wParam == 3388)
    {
		ASSERT(FALSE);
    }

	return FALSE;
}

bool CVmpHighThread::TranslateApp3388Message(LPMSG lpmsg)
{
/*	musctrl::CMusicalPlayerCentral & playercentral =
		musctrl::CMusicalPlayerCentral::AppGetMusicalPlayerCentral();
	musctrl::CSingleDocTemplate * pdoctemplate =
		playercentral.GetDocTemplate();
	if(lpmsg->wParam == 3388)
	{
		// Lyric View Event
		CVMSApp * pApp = (CVMSApp *) AfxGetApp();
		if(pApp != NULL)
		{
			CXfplayerDoc * pDoc = (CXfplayerDoc *) pdoctemplate->GetOnlyDoc();
			if(pDoc != NULL)
			{
				CXfplayerView * pView = pDoc->GetLyricView();
				if(pView != NULL)
				{
					pView->SendMessage(WM_USER, 3388, lpmsg->lParam);
				}
			}
		}
		delete (CBaseArray<LyricEventV1, LyricEventV1&> * ) lpmsg->lParam;
		return true;
	}*/
	return false;
}

BOOL CVmpHighThread::OnIdle(LONG lCount) 
{
	// TODO: Add your specialized code here and/or call the base class
	//TRACE(_T("CVmpHighThread Alive!!!\n"));
	return Thread::OnIdle(lCount);
}



//void CVmpHighThread::OnLyricViewSize(int iType, int cx, int cy)
/*void CVmpHighThread::OnLyricViewSize(int iType)
{
	CVMSApp * pApp = (CVMSApp *) AfxGetApp();
	CXfplayerDoc * pDoc = pApp->GetOnlyDocument();
	CXfplayerView * pView = pDoc->GetLyricView();
	CRect rect;
	pView->GetClientRect(&rect);
	int cx = rect.right;
	int cy = rect.bottom;

	if(cx <= 0)
		cx = 1;
	if(cy <= 0)
		cy = 1;
	if(pView->m_pfiBitmap == NULL)
		 return;
	double horizRate, vertRate, rate;
	if(FreeImage_GetWidth(pView->m_pfiBitmap))
		horizRate = ((double) cx) / FreeImage_GetWidth(pView->m_pfiBitmap);
	else
		horizRate = 1.0;
	if(FreeImage_GetHeight(pView->m_pfiBitmap))
		vertRate = ((double) cy) / FreeImage_GetHeight(pView->m_pfiBitmap);
	else
		vertRate = 1.0;
	if(horizRate < vertRate)
		rate = horizRate;
	else
		rate = vertRate;
	int finalWidth, finalHeight; //, finalX, finalY;
	finalWidth = (int) ((double) FreeImage_GetWidth(pView->m_pfiBitmap) * rate);
	finalHeight = (int) ((double) FreeImage_GetHeight(pView->m_pfiBitmap) * rate);

	LPSTRETCHIMAGESTRUCTURE lpSi = new STRETCHIMAGESTRUCTURE;
	lpSi->m_pfiBitmap = pView->m_pfiBitmap;
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

BOOL CVmpHighThread::ProcessMessageFilter(int code, LPMSG lpMsg)
{
    if(lpMsg->message == WM_TIMER)
    {
        if(m_bEnableTimers)
            return Thread::ProcessMessageFilter(code, lpMsg);
        else
            return TRUE;
            
    }
    return Thread::ProcessMessageFilter(code, lpMsg);

}

/*long CVmpHighThread::OnImageLoaded(
	HBITMAP  hbitmap)
//void CVmpHighThread::OnImageLoaded(
//	VARIANT * pVarInfoHeader,
//	VARIANT * bmBits)
{
    ASSERT(m_pMainWnd == NULL);
	CVMSApp * pApp = (CVMSApp *) AfxGetApp();
	CXfplayerDoc * pDoc = (CXfplayerDoc *) musctrl::CSingleDocTemplate::AppGetPlayerDocTemplate()->GetOnlyDoc();
	if(pDoc == NULL) // may be null
		return S_OK;      // on programa shutdown
	CXfplayerView * pView = pDoc->GetLyricView();
    if(pView == NULL)
        return S_OK;
    TRACE(_T("\nCVmpHighThread::OnImageLoaded before lock %X\n"), m_nThreadID);
    //TRACE(_T("CVmpHighThread::TranslateUserMessage 3 slGdi.Lock\n"));
    CSingleLock slGdi(&pView->m_csGdi, true);
    //TRACE(_T("\nCVmpHighThread::OnImageLoaded after lock %X\n"), m_nThreadID);
	HBITMAP hBitmapOld = (HBITMAP) pView->m_bmpBackViewSource.Detach();
	pView->m_bmpBackViewSource.Attach(hbitmap);
	CSavings & savings = CSavings::AppGetSavings();
//    if(iEconoMode != CVMSApp::SaveMemory)
  //  {
	CBitmap * pbmpOld = pView->m_dcBackViewSource.SelectObject(&pView->m_bmpBackViewSource);
    if(pbmpOld != NULL)
    {
        if(hBitmapOld != NULL)
        {
           // ASSERT(pbmpOld->GetSafeHandle() == hBitmapOld);
        }
    }
    else
    {
		pView->m_bmpBackViewSource.DeleteObject();
        TRACE(_T("CVmpHighThread::OnImageLoaded:Bitmap not selected\n"));
    }
    //}
    if(hBitmapOld != NULL)
    {
        if(hBitmapOld != pView->m_bmpBackViewSourceOld.GetSafeHandle())
        {
	        if(!DeleteObject(hBitmapOld))
            {
                ASSERT(FALSE);
                TRACE(_T("CVmpHighThread::OnImageLoaded : Atenção! Bitmap não deletado\n"));
            }
        }
    }
	slGdi.Unlock();

	if(pbmpOld == NULL)
	{
		DeleteObject(hbitmap);
        pView->PostMessage(WM_USER, 17, CXfplayerView::CImageChange::EventLoadFailed);
		return S_OK;
	}
    //TRACE(_T("CVmpHighThread::TranslateUserMessage 3 slGdi.UnLock\n"));
	
    if(pView == NULL)
        return E_FAIL;
	if(hbitmap != NULL)
		//pView->PostMessage(WM_USER, 17, pView->BkImageChangeEventLoaded);
        pView->PostMessage(WM_USER, 17, CXfplayerView::CImageChange::EventLoaded);
        //pView->BackgroundImageChangeStateMachine(pView->BkImageChangeEventLoaded);
	else
		//pView->BackgroundImageChangeStateMachine(pView->BkImageChangeEventLoadFailed);
        pView->PostMessage(WM_USER, 17, CXfplayerView::CImageChange::EventLoadFailed);
    return S_OK;
}*/

//void CVmpHighThread::OnImageStretched(
//	VARIANT * pVarInfoHeader,
//	VARIANT * pVarBits,
//	VARIANT * pVarUserData,
//	int cx,
//	int cy)
/*long CVmpHighThread::OnImageStretched(
	HBITMAP hbitmap,
	long cx,
	long cy,
	long iUserData)
{
    ASSERT(m_pMainWnd == NULL);
try
{
	CVMSApp * pApp = (CVMSApp *) AfxGetApp();
	CXfplayerDoc * pDoc = (CXfplayerDoc *) musctrl::CSingleDocTemplate::AppGetPlayerDocTemplate()->GetOnlyDoc();
	if(pDoc == NULL) // may be null
		return false;      // on programa shutdown
	CXfplayerView * pView = pDoc->GetLyricView();
try
{

	RECT rect;
	pView->GetClientRect(&rect);
    TRACE(_T("CVmpHighThread::OnImageStretched slGdi.Lock\n"));
    CSingleLock slGdi(&pView->m_csGdi, true);
//	HGDIOBJ hBitmapOld = pView->m_bmpScaled.Detach();
//	pView->m_bmpScaled.Attach(hbitmap);
//	pView->m_dcScaled.SelectObject(&pView->m_bmpScaled);
//	DeleteObject(hBitmapOld);
    TRACE(_T("CVmpHighThread::OnImageStretched slGdi.UnLock\n"));
	slGdi.Unlock();


	pView->BackViewUpdateBuffer(false);
    pView->UpdateScreen(&rect);
	if(iUserData == 2)
	{
		pView->m_dwBackgroundLastUpdateTime = timeGetTime();
		pView->BackViewGetImageChange().m_estate = CXfplayerView::CImageChange::StateTiming;
	}
    }
catch(...)
{
}
	if(iUserData == 2)
	{
		pView->m_dwBackgroundLastUpdateTime = timeGetTime();
		pView->BackViewGetImageChange().m_estate = CXfplayerView::CImageChange::StateTiming;
	}
}
catch(...)
{
}
   return true;
 }*/

HBITMAP CVmpHighThread::LoadImageSync(LPCTSTR lpcszImageFilePath)
{
//    return CImaging::LoadImageSync(lpcszImageFilePath);
   return NULL;

}

/*int CVmpHighThread::DeleteTimerWnd(CTimerWnd *ptimerwnd)
{
    return TRUE;
}

bool CVmpHighThread::CreateTimer(CTimerCallback *ptc, UINT uiElapse, UINT uiIDEvent)
{
    LPTIMERCALLBACKCREATETIMER lptcct = new TIMERCALLBACKCREATETIMER;
    lptcct->m_pTimerCallback = ptc;
    lptcct->m_uiElapse = 2;
    lptcct->m_uiIDEvent = 1;
    PostThreadMessage(
        VMSM_V001,
        NOTIFY_TIMERCALLBACKCREATETIMER,
        (LPARAM) lptcct);

	return true;

}*/

int CVmpHighThread::Run() 
{
	ASSERT_VALID(this);

	// for tracking the idle time state
	BOOL bIdle = TRUE;
	LONG lIdleCount = 0;

	// acquire and dispatch messages until a WM_QUIT message is received.
	for (;;)
	{
		// phase1: check to see if we can do idle work
		while (bIdle &&
			!::PeekMessage(AfxGetCurrentMessage(), NULL, NULL, NULL, PM_NOREMOVE))
		{
			// call OnIdle while in bIdle state
			if (!OnIdle(lIdleCount++))
				bIdle = FALSE; // assume "no idle" state
		}

		// phase2: pump messages while available
		do
		{
			// pump message, but quit on WM_QUIT
			if (!PumpMessage())
				return ExitInstance();

			// reset "no idle" state after pumping "normal" message
			if (IsIdleMessage(AfxGetCurrentMessage()))
			{
				bIdle = TRUE;
				lIdleCount = 0;
			}

		} while (::PeekMessage(AfxGetCurrentMessage(), NULL, NULL, NULL, PM_NOREMOVE));
	}

	ASSERT(FALSE);  // not reachable










	// TODO: Add your specialized code here and/or call the base class
	
//	return Thread::Run();
}

afx_msg void CVmpHighThread::OnVmsmV001(WPARAM wparam, LPARAM lparam)
{
   if(wparam == NOTIFY_TIMERCALLBACKCREATETIMER)
   {
      CSingleLock sl(&m_csTimersWindows, TRUE);
      LPTIMERCALLBACKCREATETIMER lptcct = (LPTIMERCALLBACKCREATETIMER) lparam;
      delete lptcct;
   }
   else if(wparam == NOTIFY_TIMERCALLBACKDELETETIMER)
   {
      CSingleLock sl(&m_csTimersWindows, TRUE);
   }
}

CVmpHighThread * CVmpHighThread::AppGetHighThread()
{
	return (CVmpHighThread *) &((MusicalPlayerLightApp *) AfxGetApp())->GetHighThread();
}
