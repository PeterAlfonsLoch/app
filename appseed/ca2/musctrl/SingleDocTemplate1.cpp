// XfplayerSingleDocTemplate.cpp: implementation of the CXfplayerSingleDocTemplate class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SingleDocTemplate.h"

//#include "SplashWnd.h"

#include "PlayerCentral.h"
#include "XfplayerDoc.h"
#include "XfplayerView.h"
#include "../vms/VMS.h"

#include "MenuV033.h"

#include "PlaylistCentral.h"
#include "PlaylistDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CXfplayerSingleDocTemplate, CSingleDocTemplate)

CXfplayerSingleDocTemplate::CXfplayerSingleDocTemplate( UINT nIDResource, CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass )
: m_pActivePlaylistDoc(NULL),
    CVmsGuiSingleDocTemplate(nIDResource, pDocClass, pFrameClass, pViewClass )
{

//    m_hMenuShared = NULL;
  //  m_hAccelTable = NULL;

	LoadTemplate();


}

CXfplayerSingleDocTemplate::~CXfplayerSingleDocTemplate()
{
#ifdef _DEBUG
	if (GetOnlyDoc() != NULL)
		TRACE0("Warning: destroying CXfplayerSingleDocTemplate with live document.\n");
#endif
}


/////////////////////////////////////////////////////////////////////////////
// CXfplayerSingleDocTemplate attributes

POSITION CXfplayerSingleDocTemplate::GetFirstDocPosition() const
{
	return (GetOnlyDoc() == NULL) ? NULL : BEFORE_START_POSITION;
}

CDocument* CXfplayerSingleDocTemplate::GetNextDoc(POSITION& rPos) const
{
	CDocument* pDoc = NULL;
	if (rPos == BEFORE_START_POSITION)
	{
		// first time through, return a real document
		ASSERT(GetOnlyDoc() != NULL);
		pDoc = (CDocument *) GetOnlyDoc();
	}
	rPos = NULL;        // no more
	return pDoc;
}

/////////////////////////////////////////////////////////////////////////////
// CXfplayerSingleDocTemplate document management (a list of currently open documents)

void CXfplayerSingleDocTemplate::AddDocument(CDocument* pDoc)
{
	ASSERT(GetOnlyDoc() == NULL);     // one at a time please
	ASSERT_VALID(pDoc);

	CDocTemplate::AddDocument(pDoc);
	SetOnlyDoc((CXfplayerDoc *) pDoc);
}

void CXfplayerSingleDocTemplate::RemoveDocument(CDocument* pDoc)
{
	ASSERT(GetOnlyDoc() == (CXfplayerDoc *) pDoc);     // must be this one
	ASSERT_VALID(pDoc);

	CDocTemplate::RemoveDocument(pDoc);
	SetOnlyDoc(NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CXfplayerSingleDocTemplate commands

CDocument* CXfplayerSingleDocTemplate::OpenDocumentFile(LPCTSTR lpszPathName,
	BOOL bMakeVisible)
	// if lpszPathName == NULL => create new file of this type
{
    if(lpszPathName == NULL)
        return OpenDocumentFileNoReserve(lpszPathName, bMakeVisible != 0);

    ReserveSong(lpszPathName, true, bMakeVisible != 0);

    return GetOnlyDoc();


	CDocument* pDocument = NULL;
	CFrameWnd* pFrame = NULL;
	BOOL bCreated = FALSE;      // => doc and frame created
	BOOL bWasModified = FALSE;

	if (GetOnlyDoc() != NULL)
	{
		// already have a document - reinit it
		pDocument = (CDocument *) GetOnlyDoc();
		if (!pDocument->SaveModified())
			return NULL;        // leave the original one

		pFrame = ((CXfplayerDoc *)(CFrameWnd*)GetOnlyDoc())->GetLyricView()->GetParentFrame();
		ASSERT(pFrame != NULL);
		ASSERT_KINDOF(CFrameWnd, pFrame);
		ASSERT_VALID(pFrame);
	}
	else
	{
		// create a new document
		pDocument = CreateNewDocument();
		ASSERT(pFrame == NULL);     // will be created below
		bCreated = TRUE;
	}

	if (pDocument == NULL)
	{
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
		return NULL;
	}
	ASSERT((CXfplayerDoc *) pDocument == GetOnlyDoc());

	if (pFrame == NULL)
	{
		ASSERT(bCreated);

		// create frame - set as main document frame
		BOOL bAutoDelete = pDocument->m_bAutoDelete;
		pDocument->m_bAutoDelete = FALSE;
					// don't destroy if something goes wrong
		pFrame = CreateNewFrame(pDocument, NULL);
		pDocument->m_bAutoDelete = bAutoDelete;
		if (pFrame == NULL)
		{
			AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
			delete pDocument;       // explicit delete on error
			return NULL;
		}
	}

	if (lpszPathName == NULL)
	{
		// create a new document
		SetDefaultTitle(pDocument);

		// avoid creating temporary compound file when starting up invisible
		if (!bMakeVisible)
			pDocument->m_bEmbedded = TRUE;

		if (!pDocument->OnNewDocument())
		{
			// user has been alerted to what failed in OnNewDocument
			TRACE0("CDocument::OnNewDocument returned FALSE.\n");
			if (bCreated)
				pFrame->DestroyWindow();    // will destroy document
			return NULL;
		}
	}
	else
	{
		CWaitCursor wait;

		// open an existing document
		bWasModified = pDocument->IsModified();
		pDocument->SetModifiedFlag(FALSE);  // not dirty for open

		//if (!pDocument->OnOpenDocument(lpszPathName))
        if(VMS_FAILED(ReserveSong(lpszPathName, true, bMakeVisible != 0)))
		{
			// user has been alerted to what failed in OnOpenDocument
			TRACE0("CDocument::OnOpenDocument returned FALSE.\n");
			if (bCreated)
			{
				pFrame->DestroyWindow();    // will destroy document
			}
			else if (!pDocument->IsModified())
			{
				// original document is untouched
				pDocument->SetModifiedFlag(bWasModified);
			}
			else
			{
				// we corrupted the original document
				SetDefaultTitle(pDocument);

				if (!pDocument->OnNewDocument())
				{
					TRACE0("Error: OnNewDocument failed after trying to open a document - trying to continue.\n");
					// assume we can continue
				}
			}
			return NULL;        // open failed
		}
		pDocument->SetPathName(lpszPathName);
	}

	CWinThread* pThread = AfxGetThread();
	if (bCreated && pThread->m_pMainWnd == NULL)
	{
		// set as main frame (InitialUpdateFrame will show the window)
		pThread->m_pMainWnd = pFrame;
	}
	InitialUpdateFrame(pFrame, pDocument, bMakeVisible);

	return pDocument;
}
CDocument* CXfplayerSingleDocTemplate::OpenDocumentFileNoReserve(LPCTSTR lpszPathName,
	bool bMakeVisible)
	// if lpszPathName == NULL => create new file of this type
{
    int i2 = sizeof(CMidiPlayer);
    CString str2;
    str2.Format(_T("sizeof CMidiPlayer %d"), i2);

	CDocument* pDocument = NULL;
	CFrameWnd* pFrame = NULL;
	BOOL bCreated = FALSE;      // => doc and frame created
	BOOL bWasModified = FALSE;

	if (GetOnlyDoc() != NULL)
	{
		// already have a document - reinit it
		pDocument = (CDocument *) GetOnlyDoc();
		if (!pDocument->SaveModified())
			return NULL;        // leave the original one

        ASSERT(GetOnlyDoc()->IsKindOf(RUNTIME_CLASS(CXfplayerDoc)));

		pFrame = ((CXfplayerDoc *)GetOnlyDoc())->GetLyricView()->GetParentFrame();
		ASSERT(pFrame != NULL);
		ASSERT_KINDOF(CFrameWnd, pFrame);
		ASSERT_VALID(pFrame);
	}
	else
	{
		// create a new document
		pDocument = CreateNewDocument();
		ASSERT(pFrame == NULL);     // will be created below
		bCreated = TRUE;
	}

	if (pDocument == NULL)
	{
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
		return NULL;
	}

	ASSERT(pDocument == GetOnlyDoc());

	if (pFrame == NULL)
	{
		ASSERT(bCreated);

		// create frame - set as main document frame
		BOOL bAutoDelete = pDocument->m_bAutoDelete;
		pDocument->m_bAutoDelete = FALSE;
					// don't destroy if something goes wrong
		pFrame = CreateNewFrame(pDocument, NULL);
		pDocument->m_bAutoDelete = bAutoDelete;
		if (pFrame == NULL)
		{
			AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
			delete pDocument;       // explicit delete on error
			return NULL;
		}
	}

	if (lpszPathName == NULL)
	{
		// create a new document
		SetDefaultTitle(pDocument);

		// avoid creating temporary compound file when starting up invisible
		if (!bMakeVisible)
			pDocument->m_bEmbedded = TRUE;

		if (!pDocument->OnNewDocument())
		{
			// user has been alerted to what failed in OnNewDocument
			TRACE0("CDocument::OnNewDocument returned FALSE.\n");
			if (bCreated)
				pFrame->DestroyWindow();    // will destroy document
			return NULL;
		}
	}
	else
	{
		CWaitCursor wait;

		// open an existing document
		bWasModified = pDocument->IsModified();
		pDocument->SetModifiedFlag(FALSE);  // not dirty for open

		if (!pDocument->OnOpenDocument(lpszPathName))
        //if(VMS_FAILED(ReserveSong(lpszPathName, true)))
		{
			// user has been alerted to what failed in OnOpenDocument
			TRACE0("CDocument::OnOpenDocument returned FALSE.\n");
			if (bCreated)
			{
				pFrame->DestroyWindow();    // will destroy document
			}
			else if (!pDocument->IsModified())
			{
				// original document is untouched
				pDocument->SetModifiedFlag(bWasModified);
			}
			else
			{
				// we corrupted the original document
				SetDefaultTitle(pDocument);

				if (!pDocument->OnNewDocument())
				{
					TRACE0("Error: OnNewDocument failed after trying to open a document - trying to continue.\n");
					// assume we can continue
				}
			}
			return NULL;        // open failed
		}
		pDocument->SetPathName(lpszPathName);
	}

	CWinThread* pThread = AfxGetThread();
	if (bCreated && (pThread->m_pMainWnd == NULL ||
        (dynamic_cast<CFrameWnd*>(pThread->m_pMainWnd) == NULL)))
	{
		// set as main frame (InitialUpdateFrame will show the window)
		pThread->m_pMainWnd = pFrame;
	}
	InitialUpdateFrame(pFrame, pDocument, bMakeVisible);

	return pDocument;
}
void CXfplayerSingleDocTemplate::SetDefaultTitle(CDocument* pDocument)
{
 	CString strDocName;
	if (!GetDocString(strDocName, CDocTemplate::docName) ||
		strDocName.IsEmpty())
	{
		// use generic 'untitled'
		VERIFY(strDocName.LoadString(AFX_IDS_UNTITLED));
	}
	pDocument->SetTitle(strDocName);
}

/////////////////////////////////////////////////////////////////////////////
// CXfplayerSingleDocTemplate diagnostics

#ifdef _DEBUG
void CXfplayerSingleDocTemplate::Dump(CDumpContext& dc) const
{
	CDocTemplate::Dump(dc);

	if (GetOnlyDoc())
		dc << "with document: " << (void*)GetOnlyDoc();
	else
		dc << "with no document";

	dc << "\n";
}

void CXfplayerSingleDocTemplate::AssertValid() const
{
	CDocTemplate::AssertValid();
	if (GetOnlyDoc())
		ASSERT_VALID((CDocument *) GetOnlyDoc());
}
#endif //_DEBUG


CFrameWnd* CXfplayerSingleDocTemplate::CreateNewFrame(CDocument* pDoc, CFrameWnd* pOther)
{
	if (pDoc != NULL)
		ASSERT_VALID(pDoc);
	// create a frame wired to the specified document

	ASSERT(m_nIDResource != 0); // must have a resource ID to load from
	CCreateContext context;
	context.m_pCurrentFrame = pOther;
	context.m_pCurrentDoc = pDoc;
	context.m_pNewViewClass = m_pViewClass;
	context.m_pNewDocTemplate = this;

	if (m_pFrameClass == NULL)
	{
		TRACE0("Error: you must override CDocTemplate::CreateNewFrame.\n");
		ASSERT(FALSE);
		return NULL;
	}
	CFrameWnd* pFrame = (CFrameWnd*)m_pFrameClass->CreateObject();
	if (pFrame == NULL)
	{
		TRACE1("Warning: Dynamic create of frame %hs failed.\n",
			m_pFrameClass->m_lpszClassName);
		return NULL;
	}
	ASSERT_KINDOF(CFrameWnd, pFrame);

	if (context.m_pNewViewClass == NULL)
		TRACE0("Warning: creating frame with no default view.\n");

	// create new from resource
	//if (!pFrame->LoadFrame(m_nIDResource,
	if (!pFrame->LoadFrame(m_nIDResource,
			WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,   // default frame styles
			AfxGetMainWnd(), &context))
//			NULL, &context))
	{
		TRACE0("Warning: CDocTemplate couldn't create a frame.\n");
		// frame will be deleted in PostNcDestroy cleanup
		return NULL;
	}

	// it worked !
	return pFrame;
}

void CXfplayerSingleDocTemplate::LoadTemplate()
{
	CDocTemplate::LoadTemplate();

	//if (m_nIDResource != 0 && pApp->m_pmenuPlayerShared->m_hMenu == NULL)
    if (m_nIDResource != 0)
	{
		HINSTANCE hInst = AfxFindResourceHandle(
			MAKEINTRESOURCE(m_nIDResource), RT_MENU);
		//pApp->m_pmenuPlayerShared->Attach(::LoadMenu(hInst, MAKEINTRESOURCE(m_nIDResource)));
        m_hMenu = ::LoadMenu(hInst, MAKEINTRESOURCE(m_nIDResource));
		m_hAccel =
			::LoadAccelerators(hInst, MAKEINTRESOURCE(m_nIDResource));
        //pApp->m_pmenuPlayerShared->LoadMenu(m_nIDResource);
		//pApp->m_hPlayerAccelTable =
		//	::LoadAccelerators(hInst, MAKEINTRESOURCE(m_nIDResource));
	}

#ifdef _DEBUG
	// warnings about missing components (don't bother with accelerators)
	if (m_hMenu == NULL)
		TRACE1("Warning: no shared menu for document template #%d.\n",
			m_nIDResource);
#endif //_DEBUG
}

BOOL CXfplayerSingleDocTemplate::GetDocString(CString& rString,
                            enum DocStringIndex i) const
   {
        CString strTemp,strLeft,strRight;
        AfxExtractSubString(strTemp, m_strDocStrings, (int)i);

//        if(i == CDocTemplate::filterExt)  {
  //        nFindPos=strTemp.Find(';');
    //      if(-1 != nFindPos) {
      //      //string contains two extensions
        //    strLeft=strTemp.Left(nFindPos+1);
          //  strRight="*"+strTemp.Right(lstrlen((const
            //char*)strTemp)-nFindPos-1);
//            strTemp=strLeft+strRight;
  //        }
    //    }
    rString = strTemp;
    return TRUE;
   } 

CDocTemplate::Confidence CXfplayerSingleDocTemplate::MatchDocType(const
        LPCTSTR lpszPathName, CDocument*& rpDocMatch)
{
	ASSERT(lpszPathName != NULL);
	rpDocMatch = NULL;
	
	// go through all documents
	POSITION pos = GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = GetNextDoc(pos);
		if (pDoc->GetPathName() == lpszPathName) {
			// already open
			rpDocMatch = pDoc;
			return yesAlreadyOpen;
		}
	}  // end while
	
	// see if it matches either suffix
	CString strFilterExt;
	if (GetDocString(strFilterExt, CDocTemplate::filterExt) &&
		!strFilterExt.IsEmpty())
	{
		CStrArray stra;
		stra.AddTokens(strFilterExt, ";", FALSE);

		for(int i = 0; i < stra.GetSize(); i++)
		{
			strFilterExt = stra[i];
		
			// see if extension matches
			ASSERT(strFilterExt[0] == '.');
			LPCTSTR lpszDot = _tcsrchr(lpszPathName, '.');
			if (lpszDot != NULL && lstrcmpi(lpszDot, strFilterExt) == 0)
				return yesAttemptNative; // extension matches, looks like ours

		}
		return yesAttemptForeign; //unknown document type
	}
} 

void CXfplayerSingleDocTemplate::InitialUpdateFrame(CFrameWnd* pFrame, CDocument* pDoc,
		BOOL bMakeVisible)
{
    CSingleDocTemplate::InitialUpdateFrame(pFrame, pDoc, bMakeVisible);
/*    CFrameWnd * pMainFrame = pFrame->GetTopLevelFrame();
    if(pMainFrame != NULL && pMainFrame != pFrame)
    {
        pMainFrame->InitialUpdateFrame(NULL, bMakeVisible);
    }*/
}


CDocument * CXfplayerSingleDocTemplate::GetOnlyDoc() const
{
    return ((CVmpApp *) AfxGetApp())->GetXfplayerDoc();
}
void CXfplayerSingleDocTemplate::SetOnlyDoc(CDocument * pdoc)
{
    ((CVmpApp *) AfxGetApp())->SetXfplayerDoc((CXfplayerDoc *) pdoc);
}

/*VMSRESULT CVmpApp::ReserveSong(LPCTSTR lpcszPath, bool bDoPlay)
{
    ASSERT(FALSE);
    return VMSR_E_FAIL;
    CXfplayerDoc * pPlayerDoc  = (CXfplayerDoc *) GetPlayerDocTemplate()->GetOnlyDoc();

    if(pPlayerDoc == NULL)
    {
        pPlayerDoc = (CXfplayerDoc *) GetPlayerDocTemplate()->OpenDocumentFile(NULL);
    }

    if(pPlayerDoc != NULL)
    {
        CXfplayerView * pLyricView = pPlayerDoc->GetLyricView();
        if(pLyricView != NULL)
        {
            //CPlaylistView * pPlaylistView = pLyricView->GetPlaylistView();
            CPlaylistDoc * pPlaylistDoc = pLyricView->GetPlaylistDoc();
            //if(pPlaylistView == NULL)
            if(pPlaylistDoc == NULL)
            {
                CMultiDocTemplate * pPlaylistDocTemplate = GetPlaylistDocTemplate();
                pPlaylistDoc
                 = (CPlaylistDoc *) pPlaylistDocTemplate->OpenDocumentFile(NULL);
                pLyricView->AttachPlaylistDoc(pPlaylistDoc);
//                pPlaylistView = pPlaylistDoc->GetPlaylistView();
            }
//            else
  //          {
    //            pPlaylistDoc = pPlaylistView->GetDocument();
      //      }
            if(pPlaylistDoc != NULL)
            {
                pPlaylistDoc->AddSong(lpcszPath, bDoPlay);
            }
//            }

//          	CMainFrame *pFrame = (CMainFrame *) pApp->m_pMainWnd;
  //      	pFrame->UpdateReserveList();
        }
    }
    return VMSR_SUCCESS;
}*/


VMSRESULT CXfplayerSingleDocTemplate::ReserveSong(LPINT lpiaSongs, int iSongCount, bool bDoPlay, bool bMakeVisible)
{
    CXfplayerDoc * pPlayerDoc  = (CXfplayerDoc *) GetOnlyDoc();
    CVmpApp * pApp = (CVmpApp *) AfxGetApp();
    //if(pPlayerDoc == NULL)
    //{
//        pPlayerDoc = (CXfplayerDoc *) OpenDocumentFileNoReserve(NULL, bMakeVisible);
  //  }

    if(pPlayerDoc != NULL)
    {
        CXfplayerView * pLyricView = pPlayerDoc->GetLyricView();
        if(pLyricView != NULL)
        {
            CPlaylistDoc * pPlaylistDoc = pPlayerDoc->GetPlaylistDoc();
            if(pPlaylistDoc == NULL)
            {
                pPlaylistDoc = pApp->GetPlaylistCentral().OpenDefaultPlaylist();
                pPlayerDoc->Attach(pPlaylistDoc);
            }
//            else
  //          {
    //            pPlaylistDoc = pPlaylistView->GetDocument();
      //      }
            if(bMakeVisible)
            {
                pLyricView->GetTopLevelParent()->SetForegroundWindow();
                pLyricView->BringWindowToTop();
            }
            if(pPlaylistDoc != NULL)
            {
                pPlaylistDoc->AddSong(lpiaSongs, iSongCount, bDoPlay, bMakeVisible);
            }
//            }

//          	CMainFrame *pFrame = (CMainFrame *) pApp->m_pMainWnd;
  //      	pFrame->UpdateReserveList();
        }
    }
    return VMSR_SUCCESS;
}


VMSRESULT CXfplayerSingleDocTemplate::ReserveSong(int iSongCode, bool bDoPlay, bool bMakeVisible)
{
    CXfplayerDoc * pPlayerDoc  = (CXfplayerDoc * ) GetOnlyDoc();

    CVmpApp * pApp = (CVmpApp *) AfxGetApp();

    if(pPlayerDoc == NULL)
    {
        pPlayerDoc = (CXfplayerDoc *) OpenDocumentFileNoReserve(NULL);
    }

    if(pPlayerDoc != NULL)
    {
        CXfplayerView * pLyricView = pPlayerDoc->GetLyricView();
        if(pLyricView != NULL)
        {
            CPlaylistDoc * pPlaylistDoc = pPlayerDoc->GetPlaylistDoc();
            if(pPlaylistDoc == NULL)
            {
                pPlaylistDoc = pApp->GetPlaylistCentral().OpenDefaultPlaylist();
                pPlayerDoc->Attach(pPlaylistDoc);
            }
            if(bMakeVisible)
            {
                pLyricView->GetTopLevelParent()->SetForegroundWindow();
                pLyricView->BringWindowToTop();
            }
            if(pPlaylistDoc != NULL)
            {
                pPlaylistDoc->AddSong(iSongCode, bDoPlay, bMakeVisible, true);
            }

        }
    }
    return VMSR_SUCCESS;

}

VMSRESULT CXfplayerSingleDocTemplate::ReserveSong(LPCTSTR lpcszPath, bool bDoPlay, bool bMakeVisible)
{
    CXfplayerDoc * pPlayerDoc  = (CXfplayerDoc * ) GetOnlyDoc();

CVmpApp * pApp = (CVmpApp *) AfxGetApp();
    if(pPlayerDoc == NULL)
    {
        pPlayerDoc = (CXfplayerDoc *) OpenDocumentFileNoReserve(NULL);
    }

    if(pPlayerDoc != NULL)
    {
        CXfplayerView * pLyricView = pPlayerDoc->GetLyricView();
        if(pLyricView != NULL)
        {
            CPlaylistDoc * pPlaylistDoc = pPlayerDoc->GetPlaylistDoc();
            if(pPlaylistDoc == NULL)
            {
                pPlaylistDoc = pApp->GetPlaylistCentral().OpenDefaultPlaylist();
                pPlayerDoc->Attach(pPlaylistDoc);
            }
            if(bMakeVisible)
            {
                pLyricView->GetTopLevelParent()->SetForegroundWindow();
                pLyricView->BringWindowToTop();
            }
			CWStr wstr;
			wstr.SetOEM(lpcszPath);
            if(pPlaylistDoc != NULL)
            {
                pPlaylistDoc->AddSong(wstr, bDoPlay, bMakeVisible, true);
            }

//            }

//          	CMainFrame *pFrame = (CMainFrame *) pApp->m_pMainWnd;
  //      	pFrame->UpdateReserveList();
        }
    }
    return VMSR_SUCCESS;

}

CXfplayerSingleDocTemplate * CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate()
{
    CVmpApp * pApp = (CVmpApp *) AfxGetApp();
    return pApp->GetPlayerCentral().GetDocTemplate();
}

VMSRESULT CXfplayerSingleDocTemplate::ReserveSong(CWStrArray & wstra, bool bDoPlay, bool bMakeVisible)
{
    CXfplayerDoc * pPlayerDoc  = (CXfplayerDoc *) GetOnlyDoc();
CVmpApp * pApp = (CVmpApp *) AfxGetApp();
    if(pPlayerDoc == NULL)
    {
        pPlayerDoc = (CXfplayerDoc *) OpenDocumentFileNoReserve(NULL, bMakeVisible);
    }

    if(pPlayerDoc != NULL)
    {
        CXfplayerView * pLyricView = pPlayerDoc->GetLyricView();
        if(pLyricView != NULL)
        {
            //CPlaylistView * pPlaylistView = pLyricView->GetPlaylistView();
            CPlaylistDoc * pPlaylistDoc = pPlayerDoc->GetPlaylistDoc();
            //if(pPlaylistView == NULL)
            if(pPlaylistDoc == NULL)
            {
                pPlaylistDoc = pApp->GetPlaylistCentral().OpenDefaultPlaylist();
                pPlayerDoc->Attach(pPlaylistDoc);
            }
            if(bMakeVisible)
            {
                pLyricView->GetTopLevelParent()->SetForegroundWindow();
                pLyricView->BringWindowToTop();
            }
            if(pPlaylistDoc != NULL)
            {
                pPlaylistDoc->AddSong(wstra, bDoPlay, bMakeVisible);
            }
        }
    }
    return VMSR_SUCCESS;

}

CDocument* CXfplayerSingleDocTemplate::CreateNewDocument()
{

    CDocument * pdoc = CSingleDocTemplate::CreateNewDocument();
    return pdoc;

}
