// MSDoc.cpp : implementation file
//

#include "StdAfx.h"
#include "../vmsp/resource.h"
#include "resource.h"
#include "../vms/vms.h"
#include "MSDoc.h"

#include "MSTrack.h"
#include "MSHeader.h"
#include "MSEventMidi.h"
#include "MSEventSymbol.h"
#include "MSPositions.h"
#include "MSTrackV001Set.h"

#include "mus/MidiTrackBase.h"
#include "mus/MidiTrack.h"
#include "mus/MidiUtil.h"
#include "mus/MidiFile.h" 
#include "mus/MidiSequence.h" 
#include "mus/MidiEventV001.h"
#include "mus/MidiTracks.h"
#include "gen/Thread.h"

extern UINT grbChanMsgLen[];

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMSDoc

CMSDoc::CMSDoc(::ca::application * papp) :
   MidiDocHelper(papp)
{
    m_lpbData = NULL;
    m_iSize = 0;
    m_iAllocation = 0;
    m_iAllocationAddUp = 65536;
    m_lpHeader = NULL;
}

BOOL CMSDoc::OnNewDocument()
{
	if (!Document::OnNewDocument())
		return FALSE;
	return TRUE;
}

CMSDoc::~CMSDoc()
{
}

/*
BEGIN_MESSAGE_MAP(CMSDoc, Document)
	//{{AFX_MSG_MAP(CMSDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()*/


/////////////////////////////////////////////////////////////////////////////
// CMSDoc diagnostics

#ifdef _DEBUG
void CMSDoc::AssertValid() const
{
	Document::AssertValid();
}

void CMSDoc::Dump(CDumpContext& dc) const
{
	Document::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMSDoc serialization

void CMSDoc::Serialize(Ex1Archive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMSDoc commands

VMSRESULT CMSDoc::Allocate(int iNewSize)
{
    ASSERT(iNewSize > 0);
    if(m_lpbData == NULL)
    {
        LPBYTE lpbData = (LPBYTE) malloc(iNewSize);
        if(lpbData == NULL)
            return VMSR_E_NOMEMORY;
        m_lpbData = lpbData;
        m_iAllocation = iNewSize;
    }
    else
    {
        if(iNewSize > m_iAllocation)
        {
            LPBYTE lpbData = (LPBYTE) realloc(m_lpbData, iNewSize);
            if(lpbData == NULL)
                return VMSR_E_NOMEMORY;
            m_lpbData = lpbData;
            m_iAllocation = iNewSize;
        }
    }
    return VMSR_SUCCESS;
}

VMSRESULT CMSDoc::SetSize(int iNewSize)
{
    VMSRESULT vmsr;
    if(iNewSize > m_iAllocation)
    {
        if(VMS_FAILED(vmsr = Allocate(iNewSize + m_iAllocationAddUp)))
            return vmsr;
    }
    
    m_iSize = iNewSize;

    return true;
}

VMSRESULT CMSDoc::CreateFromMidiFile(MidiFile *lpFile)
{

	// primeiro faz uma cópia todas as trilhas do arquivo

	MidiTracks & tracks = lpFile->GetTracks();


	// então faz a quantização de todas as trilhas conforme
	// elas serão representadas na partitura

//	tracks.DoQuantizationVR();


    VMSRESULT vmsr;
    SetSize(0);
    SetHeader(lpFile);
    int iCurrentChunk = 1;
	MidiEventBase * pevent;
    for(int i = 0; i < lpFile->GetTracks().GetTrackCount(); i++)
    {
        MidiTrack * lpMidiTrack = (MidiTrack *) lpFile->GetTracks().TrackAt(i);
        if(!lpMidiTrack->IsType(MidiTrackBase::TypeMidi))
            continue;
        CMSTrack * lpMsTrack = new CMSTrack(this);
        lpMsTrack->SetChunk(iCurrentChunk);
        if(VMS_FAILED(vmsr =GetChunk(iCurrentChunk, &lpMsTrack->m_lpHeader, NULL)))
            return vmsr;
        lpMsTrack->SeekBegin();
        if(lpMidiTrack->WorkSeekBegin() == stdmidifile::Success)
        {
           do
           {
              lpMidiTrack->WorkGetEvent(pevent, 0xffffffff, TRUE);
//xxxx              lpMsTrack->GetEvents()->Add(pevent);
           }
           while(stdmidifile::Success == lpMidiTrack->WorkMoveNext());
        }
        iCurrentChunk++;
        m_lpaTracks.Add(lpMsTrack);
    }   
    ReadTracks();
    DoDefaultNotesCreation(m_lpHeader->m_midiFileHeader.GetQuarterNoteTicks() / 16);
    DoDefaultNotesSpacing();
    return VMSR_SUCCESS;
}

VMSRESULT CMSDoc::SetHeader(MidiFile *lpFile)
{
    VMSRESULT vmsr;

    if(m_lpHeader == NULL)
    {
        m_lpHeader = new CMSHeader(this);
    }
    m_lpHeader->m_iVersion = VMS_DOC_VERSION_1;
    m_lpHeader->m_midiFileHeader = *lpFile->m_pFileHeader;
    if(VMS_FAILED(vmsr = m_lpHeader->Write()))
        return vmsr;
    return VMSR_SUCCESS;
}

VMSRESULT CMSDoc::GetChunkCount(LPINT lpiCount)
{
    ASSERT(lpiCount != NULL);
    if(m_lpbData == NULL)
    {
        return 0;
    }
    LPBYTE lpbData = m_lpbData;
    LPBYTE lpbDataEnd = m_lpbData + m_iSize;
    int iChunkCount = 0;
    LPMSDOCCHUNKHEADER lpChunkHeader;
    while(true)
    {
        lpChunkHeader = (LPMSDOCCHUNKHEADER) lpbData;
        lpbData += sizeof(MSDOCCHUNKHEADER);
        if(lpbData > lpbDataEnd)
            break;
        lpbData += lpChunkHeader->m_dwLength;
        if(lpbData > lpbDataEnd)
            break;
        iChunkCount++;
        if(lpbData >= lpbDataEnd)
            break;
    }
    *lpiCount = iChunkCount;
    return VMSR_SUCCESS;
}

//VMSRESULT CMSDoc::Write(BYTE byte, bool bInsert)
//{
  //  return Write(&byte, sizeof(byte), bInsert);
//}

VMSRESULT CMSDoc::Write(void *lpData, int iSize, bool bInsert)
{
    if(bInsert)
    {
        memmove(m_lpbData + m_iPosition, m_lpbData + m_iPosition + iSize, iSize);
    }
    memcpy(m_lpbData + m_iPosition, lpData, iSize);
    return VMSR_SUCCESS;
}

VMSRESULT CMSDoc::SizeUp(int iAddUp)
{
    ASSERT(iAddUp > 0);
    return SetSize(m_iSize + iAddUp);
}

VMSRESULT CMSDoc::GetChunk(int iIndex, LPMSDOCCHUNKHEADER * lppChunkHeader, LPVOID * lppChunkData)
{
    ASSERT(lppChunkHeader != NULL ||
        lppChunkData != NULL);
    if(m_lpbData == NULL)
    {
        return 0;
    }
    LPBYTE lpbData = m_lpbData;
    LPBYTE lpbDataEnd = m_lpbData + m_iSize;
    int iChunkCount = 0;
    LPMSDOCCHUNKHEADER lpChunkHeader;
    while(true)
    {
        lpChunkHeader = (LPMSDOCCHUNKHEADER) lpbData;
        lpbData += sizeof(MSDOCCHUNKHEADER);
        if(lpbData > lpbDataEnd)
            break;
        lpbData += lpChunkHeader->m_dwLength;
        if(lpbData > lpbDataEnd + 1)
            break;
        if(iIndex == iChunkCount)
        {
            if(lppChunkData != NULL)
                *lppChunkData = (LPBYTE) lpChunkHeader + sizeof(MSDOCCHUNKHEADER);
            if(lppChunkHeader != NULL)
                *lppChunkHeader  = lpChunkHeader;
        }
        iChunkCount++;
        if(lpbData >= lpbDataEnd)
            break;
    }
    return VMSR_S_NOTFOUND;

}

VMSRESULT CMSDoc::Seek(int iPosition)
{
    m_iPosition = iPosition;
    return VMSR_SUCCESS;
}

VMSRESULT CMSDoc::InsertSpace(int iChunkIndex, int iSize)
{
    VMSRESULT vmsr;
    ASSERT(iSize > 0);
    if(VMS_FAILED(vmsr = SizeUp(iSize)))
        return vmsr;
    LPBYTE lpData;
    if(VMS_FAILED(vmsr = GetChunk(iChunkIndex, (LPMSDOCCHUNKHEADER*) &lpData, NULL)))
        return vmsr;
    if(lpData == NULL)
    {
        lpData = m_lpbData + m_iSize;
    }
    memmove(lpData, lpData + iSize, m_lpbData - lpData + m_iSize - iSize);
    return VMSR_SUCCESS;
}


VMSRESULT CMSDoc::DoDefaultNotesCreation(DWORD tkDelta)
{

    /*CMSTrack * lpTrack;
    for(int i = 0; i < m_lpaTracks.GetSize(); i++)
    {
        lpTrack = m_lpaTracks.ElementAt(i);
        lpTrack->DoDefaultNotesCreation(tkDelta);
    }
    return VMSR_SUCCESS;*/
   return VMSR_SUCCESS;
}

VMSRESULT CMSDoc::DoDefaultNotesSpacing()
{
    CMSEventMidi    eventMidiNoteOn;
    CMSEventMidi    eventMidiNoteOnNext;
    CMSEventMidi    eventMidiNoteOff;
    CMSEventMidi    eventMidiNoteOffNext;
  //  CMSEvent *      lpEventMidiNoteOn;
    CMSEvent *      lpEventMidiNoteOnNext;
//    CMSEvent *      lpEventMidiNoteOff;
   CMSEvent *      lpEventMidiNoteOffNext;
    CMSEventSymbol  eventSymbol;
    CMSEvents evaSymbols;
    CMSNotes aNotes;
    CMSTrackV001Set trackSeek;
    DWORD               tkPosition = 0;
    DWORD               tkNoteOffPosition;
    DWORD               tkQuantizedPosition = 0;
    DWORD               tkLastQuantizedPosition = 0;
    CMSPositions        positions;
    CMSPosition         position;
    CMSPosition *       lpPosition;
    int iNoteOnIndex = 0;
    int iNoteOnTrack = 0;
    int iNoteOnNextIndex;
    int iNoteOnNextTrack = 0;
    int iNoteOffIndex = 0;
    int iNoteOffNextIndex;
    int iNoteOffNextTrack;
    int iSymbolNextIndex;
    DWORD tkNoteOnDelta = 0;
    DWORD tkNoteOffDelta = 0;
    DWORD tkSymbolPosition;
    DWORD tkDuration;
    DWORD tkNoteDuration;
    
//    DWORD tkQuantizedDuration;
    DWORD tkQuarterNote =  m_lpHeader->m_midiFileHeader.GetQuarterNoteTicks();
    VMSRESULT vmsr;
    bool bFirst = false;
    trackSeek.OpenDoc(this);
    while(true)
    {
        evaSymbols.RemoveAll();
        tkNoteOnDelta = 0;
        if(VMS_FAILED(vmsr = trackSeek.GetNextEventMidi(
            Midi::NoteOn,
            &lpEventMidiNoteOnNext,
            &iNoteOnNextTrack,
            &iNoteOnNextIndex,
            &tkPosition,
            &evaSymbols)) ||
            vmsr == VMSR_S_NOTFOUND)
            break;
        eventMidiNoteOnNext = *lpEventMidiNoteOnNext;
        tkNoteOffDelta = tkNoteOnDelta;
        iNoteOffIndex = iNoteOnNextIndex;
//        GetTracks()->ElementAt(iNoteOnNextTrack)->GetEvents()->GetNextEventMidi(
  //          
    //        Midi::NoteOff,
      //      eventMidiNoteOnNext.GetNoteVelocity(),
        //    &lpEventMidiNoteOffNext,
          //  &iNoteOffNextTrack,
            //&iNoteOffNextIndex,
//            &tkNoteOffPosition,
  //          NULL);
        if(bFirst)
        {
            
            tkSymbolPosition = tkPosition;
            tkNoteDuration = 0;
            for(int i = 0; i < evaSymbols.GetSize(); i++)
            {
                CMSEvent *lpEvent = &evaSymbols.ElementAt(i);
                lpEvent->GetEventSymbol(eventSymbol);
                DWORD tkDuration = eventSymbol.GetSpacingDuration(tkQuarterNote, tkNoteDuration, &tkNoteDuration);
                tkSymbolPosition += tkDuration;
                positions.AddPosition(lpEvent, tkSymbolPosition);
            }
            if(evaSymbols.HasNotes())
            {
                iNoteOnIndex = iNoteOnNextIndex - iNoteOnIndex + iSymbolNextIndex;
            }
            else
            {
                iNoteOnIndex = iNoteOnNextIndex;
            }
            tkLastQuantizedPosition = tkQuantizedPosition;
            
        }
        else
        {
            iNoteOnIndex = iNoteOnNextIndex;
        }
        eventMidiNoteOn = eventMidiNoteOnNext;
        eventMidiNoteOff = eventMidiNoteOffNext;
        
        bFirst = true;
    }
    eventMidiNoteOn.SetParam(NULL, 0);
    eventMidiNoteOff.SetParam(NULL, 0);
    eventMidiNoteOnNext.SetParam(NULL, 0);
    eventMidiNoteOffNext.SetParam(NULL, 0);
    return VMSR_SUCCESS;
}

VMSRESULT CMSDoc::MergeChunks()
{
    VMSRESULT vmsr;

    if(VMS_FAILED(vmsr = SetSize(0)))
        return vmsr;
    
    CMSTrack * lpTrack;
    m_lpHeader->Write();
    m_lpHeader->Flush();
    Write(m_lpHeader, true);
    for(int i = 0; i < m_lpaTracks.GetSize(); i++)
    {
        lpTrack = m_lpaTracks.ElementAt(i);
        lpTrack->Write();
        lpTrack->Flush();
        Write(lpTrack, true);
    }
    return VMSR_SUCCESS;
}

VMSRESULT CMSDoc::Write(CMSChunk *lpChunk, bool bInsert)
{
    VMSRESULT vmsr;
    LPBYTE lpData;

    if(VMS_FAILED(vmsr = lpChunk->GetData(&lpData)))
        return vmsr;
    
    int iSize;

    if(VMS_FAILED(vmsr = lpChunk->GetSize(&iSize)))
        return vmsr;
    Write(lpData, iSize, true);
    return VMSR_SUCCESS;
}

int CMSDoc::GetMaxTracksPixelsSizeX()
{
    CMSTrack * lpTrack;
    int iSizeX;
    int iMaxSizeX = 0;
    for(int i = 0; i < m_lpaTracks.GetSize(); i++)
    {
        lpTrack = m_lpaTracks.ElementAt(i);
        if((iSizeX = lpTrack->GetPixelsSizeX()) > iMaxSizeX)
        {
            iMaxSizeX = iSizeX;
        }
    }
    return iMaxSizeX;
}

BOOL CMSDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
//	CKeeper<bool> openingFlagKeeper(&m_bOpening, true, false, true);
	CWaitCursor wait;
	if (IsModified())
		TRACE0("Warning: OnOpenDocument replaces an unsaved document.\n");

	DeleteContents();
//	SetModifiedFlag();  // dirty during de-serialize
    

    if(!MidiDocHelper::HelperOnOpenDocument(lpszPathName))
       return FALSE;


    CreateFromMidiFile(&GetMidiSequence().GetFile());

//	SetModifiedFlag(FALSE);     // start off with unmodified

//	CVMSApp *pApp = (CVMSApp *) AfxGetApp();
//	ASSERT(pApp != NULL);




	return TRUE;
}

VMSRESULT CMSDoc::ReadTracks()
{
    CMSTrack * lpTrack;
    for(int i = 0; i < m_lpaTracks.GetSize(); i++)
    {
        lpTrack = m_lpaTracks.ElementAt(i);
        lpTrack->Read();
    }
    return VMSR_SUCCESS;
}

VMSRESULT CMSDoc::UpdateSymbolsDelta()
{
    CMSTrack * lpTrack;
    for(int i = 0; i < m_lpaTracks.GetSize(); i++)
    {
        lpTrack = m_lpaTracks.ElementAt(i);
        lpTrack->GetEvents()->UpdateSymbolsDelta();
    }
    return VMSR_SUCCESS;
}


windows_thread * CMSDoc::HelperGetMidiPlayerCallbackThread()
{
   return &gen::ThreadContainer::AppGetHighThread();
}
