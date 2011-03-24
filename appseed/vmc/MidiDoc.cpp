#include "StdAfx.h"
#include "../vmsp/resource.h"
#include "VmcApp.h"
#include "MidiDoc.h"

#include "mus/MidiEventV007.h"
#include "mus/MidiException.h"
#include "mus/MidiFile.h"
#include "mus/MidiSequence.h"
#include "mus/MidiTrack.h"
#include "mus/MidiTracks.h"
#include "mus/MidiUtil.h"

#include "mus/Star350File.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMidiDoc

//IMPLEMENT_DYNCREATE(CMidiDoc, Document)

CMidiDoc::CMidiDoc(::ca::application * papp) :
   ::ca::ca(papp),
   MidiDocHelper(papp)
{
	m_bOpening = false;
}

/*BOOL CMidiDoc::OnNewDocument()
{
	if (!Document::OnNewDocument())
		return FALSE;
	return TRUE;
}*/

CMidiDoc::~CMidiDoc()
{
}

/*
BEGIN_MESSAGE_MAP(CMidiDoc, Document)
	//{{AFX_MSG_MAP(CMidiDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/

/////////////////////////////////////////////////////////////////////////////
// CMidiDoc diagnostics

#ifdef _DEBUG
void CMidiDoc::AssertValid() const
{
	Document::AssertValid();
}

void CMidiDoc::Dump(CDumpContext& dc) const
{
	Document::Dump(dc);
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
	CWaitCursor wait;

    CVmcApp * pApp = CVmcApp::app(get_app());

    if(!GetMidiPlayer())
    {
         m_pMidiPlayer = AfxBeginThread < MidiPlayer > (get_app());
         m_pMidiPlayer->Initialize((windows_thread *) pApp->GetThreadV1());
         m_pMidiPlayer->m_evInitialized.Lock();
    }

	if (IsModified())
		TRACE0("Warning: OnOpenDocument replaces an unsaved document.\n");



//	m_pMidiPlayer->SetView(GetLyricView());
//    m_pMidiPlayer->SetMessageWindow(GetLyricView()->GetSafeHwnd());
	MidiSequence * pSequence = &HelperGetMidiSequence();
    ASSERT(pSequence != NULL);

    if(m_pMidiPlayer->IsPlaying())
	{
//		Stop();
        pSequence->m_evMmsgDone.Lock();
	}

	DeleteContents();
//	if(GetMidiSequenceState() != MidiSequence::StatusNoFile)
//	{
//		pSequence->CloseFile();
//	}
//	SetModifiedFlag();  // dirty during de-serialize

    //if(!Document::OnOpenDocument(lpszPathName))
/*    if(m_pkaraokeutil->IsStar350File(lpszPathName))
    {
        
        
        CFile file(
            lpszPathName,
            CFile::modeRead |
            CFile::shareDenyWrite |
            CFile::typeBinary);
        
        CArchive ar(&file, CArchive::load);

        CStar350File starFile;
        starFile.OpenFile(ar, 0);
        m_pkaraokeutil->ConvertStar350ToXF(&starFile, GetMidiSequence(), MidiFile::OpenForPlaying);
    }
    else
    {
        if(!Document::OnOpenDocument(lpszPathName))
            return FALSE;
    }*/

    if(!HelperOnOpenDocument(lpszPathName))
    {
        AfxMessageBox(
			IDS_FILE_OPEN_ERROR, 
			MB_OK |
			MB_ICONEXCLAMATION);
		DeleteContents();
        return FALSE;
    }



    MidiFile * pMidiFile = &HelperGetMidiSequence().GetFile();
   m_iFileType = MidiUtil::GetFileType(HelperGetMidiSequence());

    

//    CVmsApp *pApp = (CVmsApp *) AfxGetApp();
//	pApp->SetActiveDocument(this);

//    memcpy(&m_mfh, pMidiFile->m_pFileHeader, sizeof(MIDIFILEHDR));

    // Expand Format 0 Midi file (XF is Format 0) to
    // prompt for readyness edit
    if(pMidiFile->m_pFileHeader->wFormat == 0)
    {
        pMidiFile->GetTracks().ExpandTrack(0);
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
	string newName = lpszPathName;
	if (newName.is_empty())
	{
		DocumentTemplate* pTemplate = GetDocTemplate();
		ASSERT(pTemplate != NULL);

		newName = m_strPathName;
		if (bReplace && newName.is_empty())
		{
			newName = m_strTitle;
			// check for dubious filename
			int iBad = newName.FindOneOf(_T(" #%;/\\"));
			if (iBad != -1)
				newName.ReleaseBuffer(iBad);

			// append the default suffix if there is one
			string strExt;
			if (pTemplate->GetDocString(strExt, DocumentTemplate::filterExt) &&
			  !strExt.is_empty())
			{
				ASSERT(strExt[0] == '.');

                int nSemi;                       //added
                if(nSemi = strExt.Find(';'))   //added
                strExt = strExt.Left(nSemi);     //added

				newName += strExt;
			}
		}

//         CFileDialog fd;
        
/*		if (!fd.DoPromptFileName(newName,
		  bReplace ? AFX_IDS_SAVEFILE : AFX_IDS_SAVEFILECOPY,
		  OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, FALSE, pTemplate, m_iTargetFileType))
			return FALSE;       // don't even attempt to save*/
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
//    CKeeper<bool> savingFlagKeeper(&m_bSaving, true, false, true);

    string strPathName(lpszPathName);
	CFileException fe;
	MidiTrack * pTrack;
	MidiSequence * pSequence = &HelperGetMidiSequence();
	MidiFile * pFile = &pSequence->GetFile(); 
	if(IsModified())
	{
		if(NULL != (pTrack = pFile->GetTracks().Seek(MidiFile::SeekXFInfoHeader)))
		{
			MidiEventV007 midiEvent(pFile, pTrack);
//			midiEvent.CreateXFInfoHeaderEvent(0, &m_xfInfoHeaders.m_xfInfoHeader);
			midiEvent.m_tkDelta = pTrack->GetEvent().m_tkDelta;
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
    for(int i = 0; i < pFile->GetTracks().GetTrackCount(); i++)
    {
        MidiTrackBase * pTrackBase = pFile->GetTracks().TrackAt(i);
        if(pTrackBase->IsType(MidiTrackBase::TypeMidi))
        {
            MidiTrack * pTrack = (MidiTrack *) pTrackBase;
            CHUNKHDR FAR * pCh = (CHUNKHDR FAR *)pTrack->GetAllocationImage();
            if (pCh->fourccType == FOURCC_MTrk)
			    iTrackCount++;

        }

    }
    fileHdr.wFormat = WORDSWAP(0);
//	fileHdr.wDivision = m_mfh.wDivision ;
    fileHdr.wTracks = WORDSWAP(iTrackCount) ;

    pFile->WorkMergeTracks();

    

    pFile->WriteHeader(&fileHdr);

    //pFile->RebuildIndex();
    

	MidiUtil midiutil(get_app());
    if(m_iTargetFileType == stdmidifile::TypeXF)
    {
        pFile->Format0();
        midiutil.ConvertToXF(HelperGetMidiSequence(), MidiFile::OpenForPlaying);
    }
    else if(strPathName.Right(4).CompareNoCase(_T(".kar")) != 0)
    {
        // DONT Forget to implement!!!!
        ASSERT(FALSE);
    }

	try
	{
		//m_pMidiPlayer->SaveFile(lpszPathName);
        //Document::OnSaveDocument(lpszPathName);
        Document::OnSaveDocument(lpszPathName);
	}
	catch(CMidiException *pe)
	{
		pe->Delete();
	}
	
//    memcpy(&m_mfh, pFile->m_pFileHeader, sizeof(MIDIFILEHDR));
    if(pFile->m_pFileHeader->wFormat == 0)
    {
        pFile->GetTracks().ExpandTrack(0);
    }
    pFile->ToWorkStorage();
	
	SetModifiedFlag(FALSE);     // back to unmodified

	return TRUE;        // success
}


