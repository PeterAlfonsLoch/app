// VmsseThread.cpp : implementation file
//

#include "stdafx.h"
#include "VmsseApp.h"
#include "../vmsp/resource.h"
#include "vmsse.h"
#include "VmsseThread.h"

#include "OptionsDialog.h"

#include "TaskDialog.h"

#include "DataCentral.h"
#include "DBBuildAlbumThreadData.h"

#include "VmsseDll.h"
#include "VmsGuiDll.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVmsseThread

IMPLEMENT_DYNCREATE(CVmsseThread, CWinThread)

CVmsseThread::CVmsseThread()
{
    m_poptionsdlg = NULL;

}

CVmsseThread::~CVmsseThread()
{
}

BOOL CVmsseThread::InitInstance()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    CoInitialize(NULL);
    MenuV033CreateImageMap();
	AfxDebugBreak();
	if(!InitializeDataCentral())
	{
		CVmsseApp * papp = (CVmsseApp *) AfxGetApp();
		papp->m_evInit.SetEvent();
		return FALSE;
	}
    //m_pdbcentral = new CDBCentral();
    //CDataCentral::SetDBCentral(m_pdbcentral);
	//HRESULT hr;
	//if(FAILED(hr = m_pdbcentral->Initialize(AfxGetApp()->m_hInstance)))
	//{
	//	return FALSE;
	//}
    CVmsseDll::AlbumSongCreateImageList();
	CVmsseApp * papp = (CVmsseApp *) AfxGetApp();
	papp->m_evInit.SetEvent();
	return TRUE;
}

int CVmsseThread::ExitInstance()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
	// TODO:  perform any per-thread cleanup here
    

	SetThreadPriority(THREAD_PRIORITY_HIGHEST);
    
    if(DB() != NULL)
    {
		DB()->SetBuildAlbumThreadsCancelFlag();
        DB()->Close();
    }

    CoUninitialize();
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CVmsseThread, CWinThread)
	//{{AFX_MSG_MAP(CVmsseThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP

    ON_THREAD_MESSAGE(WM_USER, OnUserMessage)
    ON_THREAD_MESSAGE(VMSM_V001, OnVmsmV001)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVmsseThread message handlers

afx_msg void CVmsseThread::OnUserMessage(WPARAM wParam, LPARAM lParam )
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())


    CDBCentral * pdb = DB();

    switch(wParam)
    {
    
    case 21:
//                    ASSERT(FALSE);
//                  //ReserveSong_(pMsg->lParam);
        //GetPlayerDocTemplate()->ReserveSong(lParam, false, true);
        break;
    case 22:
        {
          //  CDWArray * pdwa = (CDWArray *) lParam;
            //GetPlayerDocTemplate()->ReserveSong((LPINT) &pdwa->GetData()[1], pdwa->GetAt(0), false, true);
            //delete pdwa;
        }
        break;
    case 23:
        {
            //CStrArray * pstra = (CStrArray *) lParam;
            //GetPlayerDocTemplate()->ReserveSong(pstra, false, true);
            //delete pstra;
        }
        break;
    case 543:
        {
            
            if(m_poptionsdlg == NULL)
            {
                m_poptionsdlg = new COptionsDialog();
                m_poptionsdlg->Create(NULL);
            }

            if(m_poptionsdlg != NULL)
            {
                m_poptionsdlg->ShowWindow(SW_SHOWNORMAL);
				m_poptionsdlg->BringWindowToTop();
            }
        
        }
        break;
        
    }
      if(wParam == 1)
    {
        if(lParam == 1)
        {
            pdb->OnSongsUpdated();
        }
        else if(lParam == 3)
        {
            pdb->OnSongsInfoV001Updated();
        }
    }

    switch(wParam)
    {
    case 131415:
       // ViewToolsAlbum();
        break;
    case 454647:
        {
         /*   CXfplayerSingleDocTemplate * pDocTemplate = GetPlayerDocTemplate();
            if(pDocTemplate != NULL)
            {
	            CXfplayerDoc * pDoc = (CXfplayerDoc *) pDocTemplate->GetOnlyDoc();
	            if(pDoc != NULL)
                {
	                CXfplayerView * pView = (CXfplayerView *) pDoc->GetLyricView();
	                if(pView != NULL)
                    {
                        //pView->PostMessage(WM_USER, 17, CXfplayerView::BkImageChangeEventLoadNow);
                        pView->BackgroundImageChangeStateMachine(pView->BkImageChangeEventLoadNow);
                        TRACE(_T("CDataCentral::OnImagesDirsModified Out"));
                    }
                }
            }*/
        }
        break;
    case 565758:
        {
            /*CDBBuildAlbumThreadData * lpdata = 
                (CDBBuildAlbumThreadData *)lParam;
            CSingleDocTemplate * pAlbumDocTemplate = NULL;
            if(GetAlbumThread())
            {
                pAlbumDocTemplate = GetAlbumThread()->GetAlbumDocTemplate();
            }
            bool bVisible = false;
            if(pAlbumDocTemplate != NULL)
            {
                bVisible = pAlbumDocTemplate->GetFirstDocPosition() != NULL;

                // avoid thread quit on close all documents
                GetAlbumThread()->m_pMainWnd = NULL;

                GetAlbumThread()->GetAlbumDocTemplate()->CloseAllDocuments(false);
            }
            //CAlbumFrameWnd * pAlbum = GetAlbumDocTemplate();
            //bool bVisible;
            //if(pAlbum != NULL)
            //{
              //  bVisible = (pAlbum->GetStyle() & WS_VISIBLE) != 0;
                //if(bVisible)
                  //  pAlbum->ShowWindow(SW_HIDE);
            //}
            lpdata->bVisible = bVisible;*/
        }
        break;
    case 676869:
        {
            //ASSERT(FALSE);
/*            CDBBuildAlbumThreadData * lpdata = 
                (CDBBuildAlbumThreadData *)lParam;
            if(!lpdata->m_ptaskdlg->Create(IDD_TASK))
            {
                AfxMessageBox(_T("Could not create task dialog"));
                return;
            }
    
            GetAlbumThread()->m_pMainWnd = lpdata->m_ptaskdlg;
        */
        }
    case 787970:
        {
            /*CDBBuildAlbumThreadData * lpdata = 
                (CDBBuildAlbumThreadData *)lParam;
            if(m_pAlbumDocTemplate != NULL)
            {
                if(lpdata->bVisible)
                {
                    lpdata->lpDataCentral->m_csBuildAlbumThreadData.Lock();
                    lpdata->m_evStarted.Lock();
                    //lpdata->m_ptaskdlg->m_pCloseWindow = pAlbum;
        //            lpdata->m_ptaskdlg->m_lparamClose = 10;
                    lpdata->lpDataCentral->m_csBuildAlbumThreadData.Unlock();
                }
            }*/
        }
        break;
    case 12342345:
        {
            /*if(m_pMainWnd == NULL)
            {
                return;
            }
            else if(!m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMainFrame)))
            {
                return;
            }
            //CMainFrame * pFrame = (CMainFrame *) pApp->m_pMainWnd;
            //if(pFrame->m_pAlbumDialog == NULL)
        //    CAlbumFrameWnd * pAlbum = pApp->GetAlbumFrameWnd();
          //  if(pAlbum == NULL)
            //{
              //  return;
            //}
            //pAlbum->GetAlbumView()->OnSongsUpdated();
            CSingleDocTemplate * pTempl = GetAlbumThread()->GetAlbumDocTemplate();
            POSITION pos = pTempl->GetFirstDocPosition();
            while(pos != NULL)
            {
                CDocument * pDoc = pTempl->GetNextDoc(pos);
                if(pDoc != NULL)
                {
                    pDoc->UpdateAllViews(NULL, 13);
                }
            }*/
        }
        break;
    case 23453456:
        {
            /*if(m_pMainWnd == NULL)
            {
                return;
            }
            else if(!m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMainFrame)))
            {
                return;
            }
        //    CMainFrame * pFrame = (CMainFrame *) pApp->m_pMainWnd;
          //  if(pFrame->m_pAlbumDialog == NULL)
            CSingleDocTemplate * pTempl = GetAlbumThread()->GetAlbumDocTemplate();
            POSITION pos = pTempl->GetFirstDocPosition();
            while(pos != NULL)
            {
                CDocument * pDoc = pTempl->GetNextDoc(pos);
                if(pDoc != NULL)
                {
                    pDoc->UpdateAllViews(NULL, 4);
                }
            }

        //    CAlbumFrameWnd * pAlbum = pApp->GetAlbumFrameWnd();
          //  if(pAlbum == NULL)
            //{
              //  return;
            //}
            //pAlbum->GetAlbumView()->OnSongsInfoV001Updated();
            */
        }
        break;
    case 345456:
        {
            bool bFullBuild = (lParam & 0x80000000) != 0;
            int eop = lParam & 0x7fffffff;
            DB()->SongsCreateBuildAlbumThread(
                (enum SongsAlbum::EBuildSongsAlbumOperation) eop,
                bFullBuild,
                this); //,
                //this);
         
            ShowBuildAlbumTaskDialog();
         

        }
        break;
    case 321432:
        {
            // On Task Dialog Stop
            //ASSERT(m_pdbcentral != NULL);
            //m_pdbcentral->SetBuildAlbumThreadsCancelFlag();
        }
        break;
    case 3214:
        {
            //OnChangeEconoMode();

        }
        break;
    case 534231:
        {
            //GetKarWnd()->SendMessageToDescendants(WM_USER, 534231);
        }
        break;
    default:;
        break;
    }
}

BOOL CVmsseThread::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
	// TODO: Add your specialized code here and/or call the base class
	return CWinThread::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL CVmsseThread::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if(m_poptionsdlg != NULL &&
        m_poptionsdlg->PreTranslateMessage(pMsg))
        return TRUE;
	return CWinThread::PreTranslateMessage(pMsg);
}

bool CVmsseThread::ShowBuildAlbumTaskDialog()
{
    CWaitCursor cwc;
    
    if(DB()->IsWorking())
    {

        CCriticalSection * pcs = NULL;
        CDBBuildAlbumThreadData * lpdata = DB()->GetActiveBuildAlbumThreadData(&pcs);
        if(lpdata == NULL)
        {
            AfxMessageBox("Could not show task dialog");
            return false;
        }
        lpdata->m_evStarted.Lock();
        pcs->Unlock();
            if(DB()->IsBuildingSongsAlbum())
            {
                CCriticalSection *pcs;
                CDBBuildAlbumThreadData * lpData =
                    DB()->GetActiveBuildAlbumThreadData(&pcs);
                if(lpData != NULL)
                {
                    //lpData->m_ptaskdlg->m_pCloseWindow = m_pAlbumFrameWnd;
					lpData->m_ptaskdlg->SendMessage(VMSM_V001, 123456789, true);
                    m_bTaskDialogPendingShowCommand = true;
                }
                pcs->Unlock();
            }
            else
            {
            }
        }
        else
        {
            AfxMessageBox(
                IDS_NODATABASESUPPORTERROR_RESOURCEUNAVAILABLE,
                MB_OK |
                MB_ICONINFORMATION);

        }
}

afx_msg void CVmsseThread::OnVmsmV001(WPARAM wParam, LPARAM lParam )
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    switch(wParam)
    {
    case NOTIFY_BUILDALBUMPROGRESSUPDATE:
    case NOTIFY_BUILDALBUMSTATUSUPDATE:
    case NOTIFY_BUILDALBUMTASKSUPDATE:
        {
            CDBCentral * pDataCentral = DB();
            if(pDataCentral->IsBuildingSongsAlbum())
            {
                CCriticalSection *pcs;
                CDBBuildAlbumThreadData * lpData =
                    pDataCentral->GetActiveBuildAlbumThreadData(&pcs);
                if(lpData != NULL)
                {
                    lpData->m_ptaskdlg->PostMessage(VMSM_V001, wParam, 0);
                }
                pcs->Unlock();
            }
            else
            {
            //    ASSERT(FALSE);
            }
        }
        break;
    case NOTIFY_BUILDALBUMDELETE:
    case NOTIFY_BUILDALBUMFINISHED:
        {
            CDBCentral* pdb = DB();
            pdb->OnFinishedBuildAlbum((CDBBuildAlbumThreadData *) lParam);
			SendMessageToWindows(VMSM_V001, wParam, lParam);
            
        }
        break;
    case NOTIFY_BUILDALBUMONHIDETASKDIALOG:
        {
//            PostMessageViewAlbum(true);
        }
        break;
    }
}


VMSRESULT CVmsseThread::MenuV033CreateImageMap()
{
    
    UINT uiaMenuV003Map [][2] =
    {
        {ID_FILE_NEW, 0},
        {ID_FILE_OPEN, 1},
        {ID_FILE_SAVE, 2},
        {ID_VIEW_FULL_SCREEN, 7},
        {ID_TOOLS_ALBUM, 8},
        {ID_VIEW_PLAYLIST, 9},
        {ID_VIEW_LYRICS, 10},
        {ID_TOOLS_MIXER, 11},
        {ID_PLAY, 12},
        {ID_STOP, 13},
        {ID_PAUSE, 14},
        {ID_NEXTSONG, 15},
//        {ID_VIEW_LYRICVIEW_SPECTRUM, 18},
//        {ID_PLAYER, 19},
        {ID_ALBUM_NAVIGATOR, 20},
        {ID_ALBUM_FULLLIST, 21},
        {ID_ALBUM_TREELIST, 22},
        {ID_ALBUM_SEARCHLIST, 23},
        {ID_ALBUM_RESERVESONG, 24},
        {-1, 25}, //ID_CHECK
        //{ID_SCORING_ENABLE, 26},
        {ID_ALBUM_DUPLICATESLIST, 27},
//        {ID_VIEW_BOUNCINGBALL, 28},
//        {ID_VIEW_GRADUALFILLING, 29}
    };
    CRelationV001<UINT, UINT, UINT, UINT> * prel;
    CVmsseThread::MenuV033GetImageMap(&prel);
    UINT uiSize = sizeof(uiaMenuV003Map) / (sizeof(UINT) * 2);
    for(UINT ui = 0; ui < uiSize; ui++)
    {
        prel->Add(uiaMenuV003Map[ui][0], uiaMenuV003Map[ui][1]);
    }
    return VMSR_SUCCESS;
}

VMSRESULT CVmsseThread::MenuV033GetImageMap(CRelationV001<UINT, UINT, UINT, UINT> ** pprel)
{
//    *pprel = &m_relMenuV033ImageMap;
    return CVmsGuiDll::AppGetDll()->MenuV033GetImageMap(pprel);
    return VMSR_SUCCESS;
}

CImageList * CVmsseThread::MenuV033GetImageList()
{
    //return m_pilMenuV033;
    return CVmsGuiDll::AppGetDll()->MenuV033GetImageList();
}

LRESULT CVmsseThread::SendMessageToWindows(UINT message, WPARAM wParam, LPARAM lParam)
{
	for(int i = 0; i < m_wndptra.GetSize(); i++)
	{
		m_wndptra.ElementAt(i)->SendMessage(message, wParam, lParam);
	}
	return 0;
}

bool CVmsseThread::InitializeDataCentral()
{
	CDBCentral * pdb = DB();
    CString strCompactDatabase = AfxGetApp()->GetProfileString(_T("Database"), _T("Compact"));
    if(!strCompactDatabase.IsEmpty())
    {
        pdb->CompactDatabase(strCompactDatabase);
        WriteProfileString(_T("Database"), _T("Compact"), _T(""));
    }

	if(!pdb->Initialize(AfxGetApp()->m_hInstance))
	{
		AfxMessageBox(
			IDS_NODATABASESUPPORTERROR_RESOURCEUNAVAILABLE, 
			MB_ICONINFORMATION);
		return false;
	}

	return false;
}
