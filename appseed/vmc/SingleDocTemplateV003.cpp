// SingleDocTemplateV003.cpp: implementation of the CSingleDocTemplateV003 class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "VmcApp.h"
#include "SingleDocTemplateV003.h"

#include "XfplayerDoc.h"
#include "XfplayerView.h"

#include "MenuV033.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CSingleDocTemplateV003, CDocTemplate)

CSingleDocTemplateV003::CSingleDocTemplateV003( UINT nIDResource, CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass )
:CSingleDocTemplate(nIDResource, pDocClass, pFrameClass, pViewClass )
{
//    m_hMenuShared = NULL;
  //  m_hAccelTable = NULL;

	LoadTemplate();


}

CSingleDocTemplateV003::~CSingleDocTemplateV003()
{
#ifdef _DEBUG
	CVmcApp *pApp = (CVmcApp *) AfxGetApp();
	ASSERT(pApp != NULL);
	if (pApp->m_pPlayerDoc != NULL)
		TRACE0("Warning: destroying CSingleDocTemplateV003 with live document.\n");
#endif
}


/////////////////////////////////////////////////////////////////////////////
// CSingleDocTemplateV003 attributes

POSITION CSingleDocTemplateV003::GetFirstDocPosition() const
{
	CVmcApp *pApp = (CVmcApp *) AfxGetApp();
	ASSERT(pApp != NULL);
	return (pApp->m_pPlayerDoc == NULL) ? NULL : BEFORE_START_POSITION;
}

CDocument* CSingleDocTemplateV003::GetNextDoc(POSITION& rPos) const
{
	CVmcApp *pApp = (CVmcApp *) AfxGetApp();
	ASSERT(pApp != NULL);
	CDocument* pDoc = NULL;
	if (rPos == BEFORE_START_POSITION)
	{
		// first time through, return a real document
		ASSERT(pApp->m_pPlayerDoc != NULL);
		pDoc = (CDocument *) pApp->m_pPlayerDoc;
	}
	rPos = NULL;        // no more
	return pDoc;
}

/////////////////////////////////////////////////////////////////////////////
// CSingleDocTemplateV003 document management (a list of currently open documents)

void CSingleDocTemplateV003::AddDocument(CDocument* pDoc)
{
	CVmcApp *pApp = (CVmcApp *) AfxGetApp();
	ASSERT(pApp != NULL);
	ASSERT(pApp->m_pPlayerDoc == NULL);     // one at a time please
	ASSERT_VALID(pDoc);

	CDocTemplate::AddDocument(pDoc);
	pApp->m_pPlayerDoc = (CXfplayerDoc *) pDoc;
}

void CSingleDocTemplateV003::RemoveDocument(CDocument* pDoc)
{
	CVmcApp *pApp = (CVmcApp *) AfxGetApp();
	ASSERT(pApp != NULL);
	ASSERT(pApp->m_pPlayerDoc == (CXfplayerDoc *) pDoc);     // must be this one
	ASSERT_VALID(pDoc);

	CDocTemplate::RemoveDocument(pDoc);
	pApp->m_pPlayerDoc = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CSingleDocTemplateV003 commands

CDocument* CSingleDocTemplateV003::OpenDocumentFile(LPCTSTR lpszPathName,
	BOOL bMakeVisible)
	// if lpszPathName == NULL => create new file of this type
{
	CVmcApp *pApp = (CVmcApp *) AfxGetApp();
	ASSERT(pApp != NULL);
	CDocument* pDocument = NULL;
	CFrameWnd* pFrame = NULL;
	BOOL bCreated = FALSE;      // => doc and frame created
	BOOL bWasModified = FALSE;

	if (pApp->m_pPlayerDoc != NULL)
	{
		// already have a document - reinit it
		pDocument = (CDocument *) pApp->m_pPlayerDoc;
		if (!pDocument->SaveModified())
			return NULL;        // leave the original one

		pFrame = (CFrameWnd*)pApp->m_pPlayerDoc->GetLyricView()->GetParentFrame();
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
	ASSERT((CXfplayerDoc *) pDocument == pApp->m_pPlayerDoc);

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

void CSingleDocTemplateV003::SetDefaultTitle(CDocument* pDocument)
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
// CSingleDocTemplateV003 diagnostics

#ifdef _DEBUG
void CSingleDocTemplateV003::Dump(CDumpContext& dc) const
{
	CVmcApp *pApp = (CVmcApp *) AfxGetApp();
	ASSERT(pApp != NULL);
	CDocTemplate::Dump(dc);

	if (pApp->m_pPlayerDoc)
		dc << "with document: " << (void*)pApp->m_pPlayerDoc;
	else
		dc << "with no document";

	dc << "\n";
}

void CSingleDocTemplateV003::AssertValid() const
{
	CVmcApp *pApp = (CVmcApp *) AfxGetApp();
	ASSERT(pApp != NULL);
	CDocTemplate::AssertValid();
	if (pApp->m_pPlayerDoc)
		ASSERT_VALID((CDocument *) pApp->m_pPlayerDoc);
}
#endif //_DEBUG


CFrameWnd* CSingleDocTemplateV003::CreateNewFrame(CDocument* pDoc, CFrameWnd* pOther)
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
//			AfxGetMainWnd(), &context))
			NULL, &context))
	{
		TRACE0("Warning: CDocTemplate couldn't create a frame.\n");
		// frame will be deleted in PostNcDestroy cleanup
		return NULL;
	}

	// it worked !
	return pFrame;
}

void CSingleDocTemplateV003::LoadTemplate()
{
	CDocTemplate::LoadTemplate();

    CVmcApp * pApp = (CVmcApp *) AfxGetApp();


	if (m_nIDResource != 0 && pApp->m_pmenuPlayerShared->m_hMenu == NULL)
	{
		HINSTANCE hInst = AfxFindResourceHandle(
			MAKEINTRESOURCE(m_nIDResource), RT_MENU);
		//pApp->m_pmenuPlayerShared->Attach(::LoadMenu(hInst, MAKEINTRESOURCE(m_nIDResource)));
        pApp->m_pmenuPlayerShared->LoadMenu(m_nIDResource);
		pApp->m_hPlayerAccelTable =
			::LoadAccelerators(hInst, MAKEINTRESOURCE(m_nIDResource));
	}

#ifdef _DEBUG
	// warnings about missing components (don't bother with accelerators)
	if (pApp->m_pmenuPlayerShared->m_hMenu == NULL)
		TRACE1("Warning: no shared menu for document template #%d.\n",
			m_nIDResource);
#endif //_DEBUG
}

BOOL CSingleDocTemplateV003::GetDocString(CString& rString,
                            enum DocStringIndex i) const
   {
        CString strTemp,strLeft,strRight;
        int nFindPos;
        AfxExtractSubString(strTemp, m_strDocStrings, (int)i);

        if(i == CDocTemplate::filterExt)  {
          nFindPos=strTemp.Find(';');
          if(-1 != nFindPos) {
            //string contains two extensions
            strLeft=strTemp.Left(nFindPos+1);
            strRight="*"+strTemp.Right(lstrlen((const
            char*)strTemp)-nFindPos-1);
            strTemp=strLeft+strRight;
          }
        }
    rString = strTemp;
    return TRUE;
   } 

CDocTemplate::Confidence CSingleDocTemplateV003::MatchDocType(const
        char* pszPathName, CDocument*& rpDocMatch)
   {
        ASSERT(pszPathName != NULL);
        rpDocMatch = NULL;

        // go through all documents
        POSITION pos = GetFirstDocPosition();
        while (pos != NULL)
        {
           CDocument* pDoc = GetNextDoc(pos);
           if (pDoc->GetPathName() == pszPathName) {
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
           // see if extension matches
           ASSERT(strFilterExt[0] == '.');
           CString ext1,ext2;
           int nDot = CString(pszPathName).ReverseFind('.');
           const char* pszDot = nDot < 0 ? NULL : pszPathName + nDot;

           int nSemi = strFilterExt.Find(';');
           if(-1 != nSemi)   {
             // string contains two extensions
             ext1=strFilterExt.Left(nSemi);
             ext2=strFilterExt.Mid(nSemi+2);
             // check for a match against either extension
             if (nDot >= 0 && (lstrcmpi(pszPathName+nDot, ext1) == 0
                 || lstrcmpi(pszPathName+nDot,ext2) ==0))
               return yesAttemptNative; // extension matches
           }
           else
           { // string contains a single extension
             if (nDot >= 0 && (lstrcmpi(pszPathName+nDot,
                 strFilterExt)==0))
             return yesAttemptNative;  // extension matches
           }
        }
        return yesAttemptForeign; //unknown document type
   } 