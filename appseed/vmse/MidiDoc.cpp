// MidiDoc.cpp : implementation file
//

#include "stdafx.h"
#include "VmeApp.h"
#include "MidiDoc.h"

#include "MidiEventV007.h"
#include "MidiException.h"
#include "MidiFileDialog.h"
#include "MidiFile.h"
#include "MidiSequence.h"
#include "MidiTrack.h"
#include "MidiTracks.h"
#include "MidiUtil.h"
#include "MidiCentral.h"

//#include "XfplayerView.h"

#include "KaraokeUtil.h"

#include "Star350File.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMidiDoc

IMPLEMENT_DYNCREATE(CMidiDoc, CDocument)

CMidiDoc::CMidiDoc()
{
}

/*BOOL CMidiDoc::OnNewDocument()
{
	if (!CXfplayerDoc::OnNewDocument())
		return FALSE;
	return TRUE;
}*/

CMidiDoc::~CMidiDoc()
{
}


BEGIN_MESSAGE_MAP(CMidiDoc, CXfplayerDoc)
	//{{AFX_MSG_MAP(CMidiDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMidiDoc diagnostics

#ifdef _DEBUG
void CMidiDoc::AssertValid() const
{
	CXfplayerDoc::AssertValid();
}

void CMidiDoc::Dump(CDumpContext& dc) const
{
	CXfplayerDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMidiDoc serialization

/*void CMidiDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}*/

/////////////////////////////////////////////////////////////////////////////
// CMidiDoc commands

BOOL CMidiDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
    CKeeper<bool> openingFlagKeeper(&m_bOpening, true, false, true);
    CSingleLock slSongData(&m_csSongData, true);
	CWaitCursor wait;

    CWinApp * pApp = (CWinApp *) AfxGetApp();

    if(!GetMidiPlayer())
    {
   	    CRuntimeClass* pRuntimeClass = RUNTIME_CLASS(CMidiPlayer);
	    CObject* pObject = pRuntimeClass->CreateObject();
	    ASSERT(pObject->IsKindOf(RUNTIME_CLASS(CMidiPlayer)));
	    m_pMidiPlayer = (CMidiPlayer *) pObject;
        m_pMidiPlayer->Initialize(NULL, HelperGetMidiSequence(), CMidiCentral::GetMidiCentral()->m_uiMidiOutDevice);
	    m_pMidiPlayer->CreateThread();
        m_pMidiPlayer->m_evInitialized.Lock();
    }

	if (IsModified())
		TRACE0("Warning: OnOpenDocument replaces an unsaved document.\n");



//	m_pMidiPlayer->SetView(GetLyricView());
    m_pMidiPlayer->SetMessageWindow(NULL);
	CMidiSequence * pSequence = HelperGetMidiSequence();
    ASSERT(pSequence != NULL);

    if(m_pMidiPlayer->IsPlaying())
	{
		Stop();
        pSequence->m_evMmsgDone.Lock();
	}

	DeleteContents();
	if(GetMidiSequenceState() != CMidiSequence::StatusNoFile)
	{
		pSequence->CloseFile();
	}
//	SetModifiedFlag();  // dirty during de-serialize

    //if(!COleServerDoc::OnOpenDocument(lpszPathName))
    if(m_pkaraokeutilHelper->IsStar350File(lpszPathName))
    {
        
        
        CFile file(
            lpszPathName,
            CFile::modeRead |
            CFile::shareDenyWrite |
            CFile::typeBinary);
        
        CArchive ar(&file, CArchive::load);

        CStar350File starFile;
        starFile.OpenFile(ar, 0);
        m_pkaraokeutilHelper->ConvertStar350ToXF(&starFile, HelperGetMidiSequence(), CMidiFile::OpenForPlaying);
    }
    else
    {
        if(!CDocument::OnOpenDocument(lpszPathName))
            return FALSE;
    }


    CMidiFile * pMidiFile = this->HelperGetMidiSequence()->GetFile();
    m_iFileType = CMidiUtil::GetFileType(*HelperGetMidiSequence());

    

//    CVmsApp *pApp = (CVmsApp *) AfxGetApp();
//	pApp->SetActiveDocument(this);

    memcpy(&m_mfh, pMidiFile->m_pFileHeader, sizeof(MIDIFILEHDR));

    // Expand Format 0 Midi file (XF is Format 0) to
    // prompt for readyness edit
    if(pMidiFile->m_pFileHeader->wFormat == 0)
    {
        pMidiFile->m_ptracks->ExpandTrack(0);
    }

    pMidiFile->ToWorkStorage();

	return TRUE;

}

BOOL CMidiDoc::DoSave(LPCTSTR lpszPathName, BOOL bReplace)
	// Save the document data to a file
	// lpszPathName = path name where to save document file
	// if lpszPathName is NULL then the user will be prompted (SaveAs)
	// note: lpszPathName can be different than 'm_strPathName'
	// if 'bReplace' is TRUE will change file name if successful (SaveAs)
	// if 'bReplace' is FALSE will not change path name (SaveCopyAs)
{
    int iTargetFileType = m_iFileType;
	CString newName = lpszPathName;
	if (newName.IsEmpty())
	{
		CDocTemplate* pTemplate = GetDocTemplate();
		ASSERT(pTemplate != NULL);

		newName = m_strPathName;
		if (bReplace && newName.IsEmpty())
		{
			newName = m_strTitle;
			// check for dubious filename
			int iBad = newName.FindOneOf(_T(" #%;/\\"));
			if (iBad != -1)
				newName.ReleaseBuffer(iBad);

			// append the default suffix if there is one
			CString strExt;
			if (pTemplate->GetDocString(strExt, CDocTemplate::filterExt) &&
			  !strExt.IsEmpty())
			{
				ASSERT(strExt[0] == '.');

                int nSemi;                       //added
                if(nSemi = strExt.Find(';'))   //added
                strExt = strExt.Left(nSemi);     //added

				newName += strExt;
			}
		}

        CMidiFileDialog mfd;
        
		if (!mfd.DoPromptFileName(newName,
		  bReplace ? AFX_IDS_SAVEFILE : AFX_IDS_SAVEFILECOPY,
		  OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, FALSE, pTemplate, m_iTargetFileType))
			return FALSE;       // don't even attempt to save
	}

	CWaitCursor wait;

	if (!OnSaveDocument(newName))
	{
		if (lpszPathName == NULL)
		{
			// be sure to delete the file
			TRY
			{
				CFile::Remove(newName);
			}
			CATCH_ALL(e)
			{
				TRACE0("Warning: failed to delete file after failed SaveAs.\n");
				 e->Delete();
			}
			END_CATCH_ALL
		}
		return FALSE;
	}

	// reset the title and change the document name
	if (bReplace)
		SetPathName(newName);

	return TRUE;        // success
}



BOOL CMidiDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
    CKeeper<bool> savingFlagKeeper(&m_bSavingHelper, true, false, true);

    CString strPathName(lpszPathName);
	CFileException fe;
	CMidiTrack * pTrack;
	CMidiSequence * pSequence = HelperGetMidiSequence();
	CMidiFile * pFile = pSequence->GetFile(); 
	if(IsModified())
	{
		if(NULL != (pTrack = pFile->m_ptracks->Seek(CMidiFile::SeekXFInfoHeader)))
		{
			CMidiEventV007 midiEvent(pFile, pTrack);
			midiEvent.CreateXFInfoHeaderEvent(0, &m_xfInfoHeaders.m_xfInfoHeader);
			midiEvent.m_tkDelta = pTrack->GetEvent()->m_tkDelta;
            //pFile->ToWorkStorage();
			pFile->ReplaceSameDeltaEvent(midiEvent);
//            pFile->WorkMergeTracks();
  //          pFile->WriteHeader(&mfh);
    //        pFile->Format0();
            
		}
        else
        {
            ASSERT(FALSE);
        }
		
	}

    MIDIFILEHDR fileHdr;
    
    int iTrackCount = 0;
    for(int i = 0; i < pFile->m_ptracks->GetSize(); i++)
    {
        CMidiTrackBase * pTrackBase = pFile->m_ptracks->ElementAt(i);
        if(pTrackBase->IsKindOf(RUNTIME_CLASS(CMidiTrack)))
        {
            CMidiTrack * pTrack = (CMidiTrack *) pTrackBase;
            CHUNKHDR FAR * pCh = (CHUNKHDR FAR *)pTrack->GetImage();
            if (pCh->fourccType == FOURCC_MTrk)
			    iTrackCount++;

        }

    }
    fileHdr.wFormat = WORDSWAP(0);
	fileHdr.wDivision = m_mfh.wDivision ;
    fileHdr.wTracks = WORDSWAP(iTrackCount) ;

    pFile->WorkMergeTracks();

    

    pFile->WriteHeader(&fileHdr);

    pFile->BuildIndex();
    

    if(m_iTargetFileType == CMidiFile::FileTypeXF)
    {
        pFile->Format0();
        CMidiUtil::ConvertToXF(*HelperGetMidiSequence(), CMidiFile::OpenForPlaying);
    }
    else if(strPathName.Right(4).CompareNoCase(_T(".kar")) != 0)
    {
        // DONT Forget to implement!!!!
        ASSERT(FALSE);
    }

	try
	{
		//m_pMidiPlayer->SaveFile(lpszPathName);
        //COleServerDoc::OnSaveDocument(lpszPathName);
        CDocument::OnSaveDocument(lpszPathName);
	}
	catch(CMidiException *pe)
	{
		pe->Delete();
	}
	
    memcpy(&m_mfh, pFile->m_pFileHeader, sizeof(MIDIFILEHDR));
    if(pFile->m_pFileHeader->wFormat == 0)
    {
        pFile->m_ptracks->ExpandTrack(0);
    }
    pFile->ToWorkStorage();
	
	SetModifiedFlag(FALSE);     // back to unmodified

	return TRUE;        // success
}


