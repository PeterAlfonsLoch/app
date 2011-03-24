// xfplayerDoc.cpp : implementation of the CCDDoc class
//

#include "StdAfx.h"
#include "..\vmsp\resource.h"
#include "CDDoc.h"
#include "VmsGuiSingleDocTemplate.h"

#include "MidiCentral.h"
#include "MidiEventV007.h"
#include "MidiFile.h"
#include "MidiTrack.h"
#include "MidiTracks.h"
#include "LyricTrack.h"

#include "PlaylistDoc.h"
#include "PlaylistListView.h"


#include "midiplyr.h"
#include "midi.h"
#include "MidiPlayer.h"
#include "MidiSequence.h"
#include "MidiEventv001.h"
#include "MidiEventsv1.h"
#include "MidiUtil.h"
#include "MidiException.h"
#include "XF.h"
#include "Lyriceventsv1.h"
#include "Lyriceventsv2.h"

#include "DBSongSet.h"
#include "DBLong.h"

#include "KaraokeUtil.h"


#include "WaveCentral.h"
#include "WaveIn.h"

#include "datacentral.h"

#include "BSTR.h"




#include "TransparentFrameWndV8.h"
#include "GenericViewUpdateHint.h"

#include "SliderV017.h"

#include "Star350File.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//extern CVmpApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCDDoc

IMPLEMENT_DYNCREATE(CCDDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(CCDDoc, COleServerDoc)
	//{{AFX_MSG_MAP(CCDDoc)
	ON_UPDATE_COMMAND_UI(ID_PLAY, OnUpdatePlay)
	ON_UPDATE_COMMAND_UI(ID_PAUSE, OnUpdatePause)
	ON_UPDATE_COMMAND_UI(ID_STOP, OnUpdateStop)
	ON_COMMAND(ID_VIEW_LYRICS, OnViewLyrics)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LYRICS, OnUpdateViewLyrics)
	ON_COMMAND(ID_VIEW_MIDIEVENTS, OnViewMidievents)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MIDIEVENTS, OnUpdateViewMidievents)
	ON_COMMAND(ID_FILE_PROPERTIES, OnFileProperties)
	ON_UPDATE_COMMAND_UI(ID_FILE_PROPERTIES, OnUpdateFileProperties)
	ON_COMMAND(ID_SCORING_ENABLE, OnScoringEnable)
	ON_UPDATE_COMMAND_UI(ID_SCORING_ENABLE, OnUpdateScoringEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCDDoc, COleServerDoc)
	//{{AFX_DISPATCH_MAP(CCDDoc)
	DISP_FUNCTION(CCDDoc, "OpenFile", OpenFile, VT_BOOL, VTS_BSTR VTS_BOOL)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_OLECMD_MAP(CCDDoc, COleServerDoc)
	ON_OLECMD_PAGESETUP()
	ON_OLECMD_PRINT()
END_OLECMD_MAP()


// Note: we add support for IID_IXfplayer to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {93535E2A-F1A0-4FD6-A54C-DADADF314C93}
static const IID IID_IXfplayer =
{ 0x93535e2a, 0xf1a0, 0x4fd6, { 0xa5, 0x4c, 0xda, 0xda, 0xdf, 0x31, 0x4c, 0x93 } };

BEGIN_INTERFACE_MAP(CCDDoc, COleServerDoc)
	INTERFACE_PART(CCDDoc, IID_IXfplayer, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDDoc construction/destruction

CCDDoc::CCDDoc()
{
	m_bPlay = false;

	// TODO: add one-time construction code here
    m_bWaitingToPlay = false;
    m_pmidiplayer = NULL;
    m_dProgressRate = 0.0;
// Use OLE compound files
	EnableCompoundFile();

    EnableAutomation();

	AfxOleLockApp();


    m_bOpening = false;
    m_bSavingHelper = false;
    m_bClosing = false;
    m_efiletype = StdMidiFile::TypeNull;



	int i = CP_OEMCP;
	DBLoad("LyricsCodePage", i);
	m_dwCodePage = i;
}

CCDDoc::~CCDDoc()
{
	AfxOleUnlockApp();
}

BOOL CCDDoc::OnNewDocument()
{
	int i = 1;
	CDBLongSet * plongset = DB()->GetDBLongSet();
	DBLoad(_T("ScoringEnable"), i);
    EnableScoring(i != 0);

	CWinApp * pApp = (CWinApp *) AfxGetApp();
//	pApp->SetActiveDocument(this);
	if (!COleServerDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCDDoc serialization

void CCDDoc::Serialize(CArchive& ar)
{
	MMRESULT mmr;
	if (ar.IsStoring())
	{
        HelperGetMidiSequence()->SaveFile(ar);
		// TODO: add storing code here
	}
	else
	{
		
		mmr = HelperGetMidiSequence()->OpenFile(ar, CMidiFile::OpenForPlaying);
		if(mmr != MMSYSERR_NOERROR)
		{
			CMidiException * pe = new CMidiException();
			pe->SetMMResult(mmr);
			throw pe;
		}
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCDDoc diagnostics

#ifdef _DEBUG
void CCDDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}

void CCDDoc::Dump(CDumpContext& dc) const
{
	COleServerDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCDDoc commands

BOOL CCDDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	int i = 1;
	CDBLongSet * plongset = DB()->GetDBLongSet();
	DBLoad(_T("Scoring"), i);
    EnableScoring(i != 0);

    int i2 = sizeof(CMidiPlayer);
    CString str2;
    str2.Format(_T("sizeof CMidiPlayer %d"), i2);

    CKeeper<bool> openingFlagKeeper(&m_bOpening, true, false, true);
    CSingleLock slSongData(&m_csSongData, true);
	CWaitCursor wait;
    
    CWinApp * pApp = (CWinApp *) AfxGetApp();

    if(!GetMidiPlayer())
		if(!OpenMidiPlayer())
			return FALSE;

	if (IsModified())
		TRACE0("Warning: OnOpenDocument replaces an unsaved document.\n");

	CMidiSequence * pSequence = HelperGetMidiSequence();
    ASSERT(pSequence != NULL);


    if(m_pmidiplayer->IsPlaying())
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
    CMidiFile * pMidiFile = HelperGetMidiSequence()->GetFile();

    if(!HelperOnOpenDocument(lpszPathName))
    {
        AfxMessageBox(
			IDS_FILE_OPEN_ERROR, 
			MB_OK |
			MB_ICONEXCLAMATION);
		DeleteContents();
        return FALSE;
    }

	uh.SetType(CXfplayerViewUpdateHint::PreparePhaseB);
	UpdateAllViews(NULL, 0L, &uh);
    
	
	PrepareLyrics();

	
	uh.SetType(CXfplayerViewUpdateHint::Prepare);
	UpdateAllViews(NULL, 0L, &uh);

	return TRUE;
	
}

void CCDDoc::Play(bool bMakeVisible)
{
    int i2 = sizeof(CMidiPlayer);
    CString str2;
    str2.Format(_T("sizeof CMidiPlayer %d"), i2);

	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	ASSERT(pApp != NULL);

	CMidiSequence * pMidiSequence = HelperGetMidiSequence();
	ASSERT(pMidiSequence != NULL);
	CXfplayerView *pView = GetLyricView();
	ASSERT(pView != NULL);

	if (pMidiSequence->GetState() == CMidiSequence::StatusNoFile)
	{
        CPlaylistDoc * pPlaylistDoc = GetPlaylistDoc();
		CDocument * pDoc = NULL;
        CString str;

        int i3 = sizeof(CMidiPlayer);
        CString str3;
        str3.Format(_T("sizeof CMidiPlayer %d"), i3);

        while(pDoc == NULL &&
            pPlaylistDoc->GetNextSongPath(str))
        {
            int i4 = sizeof(CMidiPlayer);
            CString str4;
            str4.Format(_T("sizeof CMidiPlayer %d"), i4);

			pDoc = CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate()->OpenDocumentFileNoReserve(str, bMakeVisible);
			pView->UpdateReserveList();
		}
        if(pDoc == NULL)
            return;

	}

	m_iPlayingTokenIndex = -1;
	m_iBufferingTokenIndex = 0;
	//m_iBufferingTokenIndex = 0;
	//m_iBufferingOffsetTokenIndex = 0;
//	pApp->SetPlayingDocument(this);
	
	GetMidiPlayer()->SetMidiOutDevice(CMidiCentral::GetMidiCentral()->m_uiMidiOutDevice);

	if(HelperGetMidiSequence()->GetState() == CMidiSequence::StatusOpened)
	{
		m_bPlay = true;
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

void CCDDoc::NextSong(bool bDoPlay, bool bMakeVisible)
{
    CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	ASSERT(pApp != NULL);
//	CMainFrame * pMainFrame = (CMainFrame *) pApp->m_pMainWnd;
//	ASSERT(pMainFrame != NULL);
	CDBCentral * pDataCentral = DB();
	ASSERT(pDataCentral != NULL);
	CDBSongSet * pSongsSet = pDataCentral->GetSongsSet();
	ASSERT(pSongsSet != NULL);
//	CMidiSequence * pMidiSequence = m_pmidiplayer->GetSequence();
//	ASSERT(pMidiSequence != NULL);
	CXfplayerView *pView = GetLyricView();
	ASSERT(pView != NULL);
    //CPlaylistView * pPlaylistView = pView->GetPlaylistView();
    //if(pPlaylistView == NULL)
      // return;
    CPlaylistDoc * pPlaylistDoc = GetPlaylistDoc();
    if(!pPlaylistDoc->HasNextSong())
		return;


	if((GetMidiPlayer() && m_pmidiplayer->IsPlaying()) || bDoPlay)
	{
//		CVmpApp *pApp = (CVmpApp *) AfxGetApp();
//		ASSERT(pApp != NULL);	
//		CWaveIn * pWaveIn = pApp->GetWaveIn();
//		pWaveIn->Reset();
//		pWaveIn->Close();
		
		if(GetMidiPlayer() && m_pmidiplayer->IsPlaying())
		{
			m_bSettingNextSong = true;
//			m_evMMDone.ResetEvent();
			m_pmidiplayer->PostThreadMessage(MIDIPLAYERMESSAGE_COMMAND, m_pmidiplayer->CommandStop, 0);
//			m_evMMDone.Lock();
//			while(!m_evMMDone.Lock(0))
//				Sleep(0);
//			m_evMMDone.Unlock();
//			CSingleLock sl(&m_evMMDone, TRUE);
		}
		else
		{
			if(GetMidiPlayer())
                m_pmidiplayer->CloseFile();
            //if(
			//pView->PostPlayMessage();
            pView->SendMessage(WM_USER, 5, bMakeVisible);
		}
	}
	else
	{
//        if (pMidiSequence->GetState() == CMidiSequence::StatusNoFile)
//	    {
//		CDocument * pDoc = NULL;
  //      CString str;
    //    while(pDoc == NULL &&
      //      pPlaylistDoc->GetNextSongPath(str))
        //{
		//	pDoc = CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate()->OpenDocumentFile(str);
		//	pView->UpdateReserveList();
		//}
//	    }
	}

}


void CCDDoc::OnUpdatePlay(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
                   
	pCmdUI->Enable(GetPlayEnable());
}

void CCDDoc::PrepareLyrics()
{
	//if(!PrerollAndWait())
	//{
	//	TRACE0("Could not parse midi file.");
	//	return;
	//}
	CMidiSequence * pSequence = HelperGetMidiSequence();
	CMidiFile * pFile = pSequence->GetFile();

	ASSERT(pFile != NULL);
	pFile->m_ptracks->SeekBegin();
//    if (pFile->m_fdwSMF & SMF_F_EOF)
//    {
//        return SMF_END_OF_FILE;
//		return;
//    }
//    CMidiEvent                   event;
	TICKS					tkMax = pFile->m_tkLength;
//	SMFRESULT               smfrc;
	TICKS					tkLastPosition = 0;
	
//	CUDWordBytes udwb;
//	udwb.dw = 0x1FF1F101L;
//	udwb.dw <<= 8;
//	udwb.ToVL();
//	CMidiTrack mt;
///	mt.m_hpbImage = new BYTE[16];
//	mt.SetAutoAllocation(TRUE);
//	mt.WriteVDWord(0x00);
//	mt.WriteVDWord(0x40);
//	mt.WriteVDWord(0x7f);
//	mt.WriteVDWord(0x80);
//	mt.WriteVDWord(0x2000);
//	mt.WriteVDWord(0x3fff);
//	mt.WriteVDWord(0x4000);
//	mt.WriteVDWord(0x100000);
//	mt.WriteVDWord(0x1FFFFF);
//	mt.WriteVDWord(0x200000);
//	mt.WriteVDWord(0x8000000);
//	mt.WriteVDWord(0xFFFFFFF);
//	mt.WriteVDWord(0x10000000);


	if(m_LyricsDisplayOffset < 480)
	{
		m_LyricsDisplayOffset = 480;
	}
	if(m_LyricsDisplayOffset > 720)
	{
		m_LyricsDisplayOffset = 720;
	}
	m_LyricsDisplay = 30;
	//C2DTickArray * p2DTokensTicks = NULL;
    C2DTickArray tka2DTokensTicks;
	C2DTickArray tk2DNoteOnPositions;
	C2DTickArray tk2DNoteOffPositions;
	C2DTickArray tk2DBegPositions;
	C2DTickArray tk2DEndPositions;
	C2DDWordArray ms2DTokensMillis;
	C2DDWordArray ms2DNoteOnMillis;
	C2DDWordArray ms2DNoteOffMillis;
	C2DDWordArray ms2DBegMillis;
	C2DDWordArray ms2DEndMillis;
	CMidiEventsV1 midiEvents;
	
	
	// Note on and off events
	// and maximum and minimum 
	// pitch bend peaks.
	CMidiEventsV1 midiEventsLevel2;

	CMidiEventsV1 noteOnEvents;
	CMidiEventsV1 noteOffEvents;

	CMidiEventsV1 eventsLevel2Beg;
	CMidiEventsV1 eventsLevel2End;
//	CMidiEventsV1 eventsNoteOnN;
//	CMidiEventsV1 eventsNoteOffN;
	CEventsTracksV1 lyricEventsForPositionCB;
	CEventsTracksV1 lyricEventsForBouncingBall;
	CEventsTracksV1 lyricEventsForScoring;
    //CEventsTracksV1 lyriceventsNormal;
    CBaseArray <CStrArray, CStrArray &> * lpstra2DTokens = &pFile->m_str2aRawTokens;

//    if(m_p2DTokens == NULL)
  //      m_p2DTokens = new 

    //m_str2aRawTokens.RemoveAll();

	pSequence->GetFile()->m_ptracks->SeekBegin();
	pSequence->GetFile()->m_ptracks->GetXFInfoHeaders(
		&m_xfInfoHeaders);


	pSequence->GetFile()->m_ptracks->WorkSeekBegin();
	pSequence->GetFile()->m_ptracks->WorkGetXFTokens(
		*lpstra2DTokens,
		&tka2DTokensTicks,
		&m_xflha);

	pSequence->GetFile()->TicksToMillisecs(
		&ms2DTokensMillis,
		&tka2DTokensTicks,
		0);

	CLyricEventsV2 *pLyricEventsV2;
	CLyricEventsV2 *pLyricEventsV2B;
    CLyricEventsV2 *pLyricEventsV2C;
    //CLyricEventsV2 *plyriceventsv2N; // Normalized
	CMidiEventsV1 *pMidiEventsV1;
	tk2DNoteOnPositions.SetSize(tka2DTokensTicks.GetSize());
	tk2DNoteOffPositions.SetSize(tka2DTokensTicks.GetSize());
	tk2DBegPositions.SetSize(tka2DTokensTicks.GetSize());
	tk2DEndPositions.SetSize(tka2DTokensTicks.GetSize());
	int i, j;
	for(i = 0; i < tka2DTokensTicks.GetSize(); i++)
	{
		pLyricEventsV2 = new CLyricEventsV2();
		pLyricEventsV2B = new CLyricEventsV2();
        pLyricEventsV2C = new CLyricEventsV2();
//        pLyricEventsV2N = new CLyricEventsV2();
		lyricEventsForScoring.Add(pLyricEventsV2);
		lyricEventsForPositionCB.Add(pLyricEventsV2B);
        lyricEventsForBouncingBall.Add(pLyricEventsV2C);
  //      lyriceventsNormal.Add(plyriceventsv2N);
		pLyricEventsV2->m_iType = 2;
		pLyricEventsV2->m_iOrder = i;
		pLyricEventsV2B->m_iType = 2;
		pLyricEventsV2B->m_iOrder = i;
		pLyricEventsV2C->m_iType = 4;
		pLyricEventsV2C->m_iOrder = i;
//        plyriceventsv2N->m_iType = 2;
  //      plyriceventsv2N->m_iOrder = i;
		pMidiEventsV1 = NULL;
		pLyricEventsV2->m_iTrack =
			pSequence->GetFile()->CalcMelodyTrack(
			&pMidiEventsV1,
			tka2DTokensTicks.operator[](i));
		pLyricEventsV2B->m_iTrack = pLyricEventsV2->m_iTrack;
        pLyricEventsV2C->m_iTrack = pLyricEventsV2->m_iTrack;
		if(pLyricEventsV2->m_iTrack < 0)
		{
			pLyricEventsV2->m_iTrack = pSequence->GetFile()->m_ptracks->m_iMelodyTrackTipA;
			pLyricEventsV2B->m_iTrack = pSequence->GetFile()->m_ptracks->m_iMelodyTrackTipA;
            pLyricEventsV2C->m_iTrack = pSequence->GetFile()->m_ptracks->m_iMelodyTrackTipA;
		}
		if(pLyricEventsV2->m_iTrack >= 0)
		{
            if(WORDSWAP(pSequence->GetFile()->m_pFileHeader->wFormat) == 0)
            {
                pSequence->GetFile()->m_ptracks->ElementAt(0)->WorkSeekBegin();
    			((CMidiTrack *)pSequence->GetFile()->m_ptracks->ElementAt(0))->WorkGetNoteOnOffEventsV1(
				    &midiEvents, 
				    pLyricEventsV2->m_iTrack,
				    pSequence->GetFile()->GetFormat() == 1);
                pSequence->GetFile()->m_ptracks->ElementAt(0)->WorkSeekBegin();
    			((CMidiTrack *)pSequence->GetFile()->m_ptracks->ElementAt(0))->WorkGetLevel2Events(
				    &midiEventsLevel2, 
				    pLyricEventsV2->m_iTrack,
				    pSequence->GetFile()->GetFormat() == 1);
            }
            else
            {
			    pSequence->GetFile()->m_ptracks->ElementAt(pLyricEventsV2->m_iTrack)->SeekBegin();
			    ((CMidiTrack *)pSequence->GetFile()->m_ptracks->ElementAt(pLyricEventsV2->m_iTrack))->GetLevel2Events(
				    &midiEvents, 
				    pLyricEventsV2->m_iTrack,
				    pSequence->GetFile()->GetFormat() == 1);
			    pSequence->GetFile()->m_ptracks->ElementAt(pLyricEventsV2->m_iTrack)->SeekBegin();
			    ((CMidiTrack *)pSequence->GetFile()->m_ptracks->ElementAt(pLyricEventsV2->m_iTrack))->GetLevel2Events(
				    &midiEventsLevel2, 
				    pLyricEventsV2->m_iTrack,
				    pSequence->GetFile()->GetFormat() == 1);
            }
//			pSequence->GetFile()->m_tracks[pLyricEventsV2B->m_iTrack]->SeekBegin(pFile);
//			pSequence->GetFile()->m_tracks[pLyricEventsV2B->m_iTrack]->GetNoteOnOffEventsV1(
//				&midiEvents, 
//				pLyricEventsV2B->m_iTrack,
//				pSequence->GetFile()->GetFormat() == 1);
		}
        
//        eventsNoteOnN.Copy(noteOnEvents);
  //      eventsNoteOffN.Copy(noteOffEvents);

//        CMidiUtil::NormalizeNotesV001(
  //          &eventsNoteOnN,
    //        &eventsNoteOffN,
      //      tka2DTokensTicks.operator[](i));

		CMidiUtil::PrepareNoteOnOffEvents(
			&noteOnEvents,
			&noteOffEvents,
			pLyricEventsV2->m_iTrack,
			pSequence->GetFile()->GetFormat(),
			&midiEvents,
			tka2DTokensTicks.operator[](i));

   		CMidiUtil::PrepareLevel2Events(
			&eventsLevel2Beg,
			&eventsLevel2End,
			pLyricEventsV2->m_iTrack,
			pSequence->GetFile()->GetFormat(),
			&midiEventsLevel2,
			tka2DTokensTicks.operator[](i));

//		CMidiUtil::PrepareNoteOnOffEvents(
//			&noteOnEvents,
//			&noteOffEvents,
//			pLyricEventsV2B->m_iTrack,
//			pSequence->GetFile()->GetFormat(),
//			&midiEvents,
//			tka2DTokensTicksoperator[](i));

		tk2DNoteOnPositions.GetAt(i)->Copy(noteOnEvents.m_tkaEventsPosition);
		tk2DNoteOffPositions.GetAt(i)->Copy(noteOffEvents.m_tkaEventsPosition);
		tk2DBegPositions.GetAt(i)->Copy(eventsLevel2Beg.m_tkaEventsPosition);
		tk2DEndPositions.GetAt(i)->Copy(eventsLevel2End.m_tkaEventsPosition);
		pLyricEventsV2->m_dwaNotesData.Copy(noteOnEvents.m_dwaEventsData);
		pLyricEventsV2B->m_dwaNotesData.Copy(eventsLevel2Beg.m_dwaEventsData);
        pLyricEventsV2C->m_dwaNotesData.Copy(eventsLevel2Beg.m_dwaEventsData);
		midiEvents.RemoveAll();
		noteOnEvents.RemoveAll();
		noteOffEvents.RemoveAll();
		midiEventsLevel2.RemoveAll();
		eventsLevel2Beg.RemoveAll();
		eventsLevel2End.RemoveAll();
		delete pMidiEventsV1;
	}

	pSequence->GetFile()->TicksToMillisecs(
		&ms2DNoteOnMillis,
		&tk2DNoteOnPositions,
		0);
	pSequence->GetFile()->TicksToMillisecs(
		&ms2DNoteOffMillis,
		&tk2DNoteOffPositions,
		0);

	pSequence->GetFile()->TicksToMillisecs(
		&ms2DBegMillis,
		&tk2DBegPositions,
		0);
	pSequence->GetFile()->TicksToMillisecs(
		&ms2DEndMillis,
		&tk2DEndPositions,
		0);

	//dw2DMillis.SetSize(p2DTicks->GetSize());
	CLyricEventsV1 *pLyricEventsV1;
	for(i = 0; i < tka2DTokensTicks.GetSize(); i++)
	{
		pLyricEventsV1 = new CLyricEventsV1();
		pLyricEventsV1->m_iType = 1;
		pLyricEventsV1->m_iOrder = i;
		pFile->m_eventsTracksForPositionCB.Add(pLyricEventsV1);
		pSequence->GetFile()->MillisecsToTicks(
			&pLyricEventsV1->m_tkaTokensPosition,
			ms2DTokensMillis[i],
			-1000);
        CMidiLyricTrack * pLyricTrk = pFile->m_ptracks->CreateLyricTrack();
        pLyricTrk->Prepare(*pLyricEventsV1);
        //pFile->m_ptracks->Add(pLyricTrk);
	}
//	CLyricEventsV2 *pLyricEventsV2;
//	CMidiEventsV1 *pMidiEventsV1;
	C1DDWordArray * p1DMillis;
	C1DDWordArray * p1DNoteOnMillis;
	C1DDWordArray * p1DNoteOffMillis;
	DWORD dwMillis;
	DWORD dwLastMillis;
//	DWORD dwLastMillis;
	for(i = 0; i < tka2DTokensTicks.GetSize(); i++)
	{
		pLyricEventsV2 = (CLyricEventsV2 *) lyricEventsForScoring.GetAt(i);
		pFile->m_eventsTracksForScoring.Add(pLyricEventsV2);
		pSequence->GetFile()->MillisecsToTicks(
			&pLyricEventsV2->m_tkaTokensPosition,
			ms2DTokensMillis[i],
			0);
		pSequence->GetFile()->MillisecsToTicks(
			&pLyricEventsV2->m_tkaNotesPosition,
			ms2DNoteOnMillis[i],
			0);
		for(j = 0; j < ms2DTokensMillis[i]->GetSize(); j++)
		{
            if(ms2DTokensMillis[i]->GetAt(j) <= 100)
                pLyricEventsV2->m_msaTokensPosition.Add(
				    0);
            else
                pLyricEventsV2->m_msaTokensPosition.Add(
				    ms2DTokensMillis[i]->GetAt(j) - 100);
		}
		p1DNoteOnMillis = ms2DNoteOnMillis[i];
		p1DNoteOffMillis = ms2DNoteOffMillis[i];
		ASSERT(p1DNoteOnMillis->GetSize() ==
			p1DNoteOffMillis->GetSize());
		for(j = 0; j < p1DNoteOnMillis->GetSize(); j++)
		{
			pLyricEventsV2->m_msaNotesDuration.Add(
				p1DNoteOffMillis->GetAt(j) -
				p1DNoteOnMillis->GetAt(j));
		}
		for(j = 0; j < p1DNoteOnMillis->GetSize(); j++)
		{
			if(p1DNoteOnMillis->GetAt(j) <= 100)
				pLyricEventsV2->m_msaNotesPosition.Add(
					0);
			else
				pLyricEventsV2->m_msaNotesPosition.Add(
					p1DNoteOnMillis->GetAt(j) - 100);
		}
		
		p1DMillis = ms2DTokensMillis[i];
		if(p1DMillis->GetSize() > 0)
		{
			dwLastMillis = p1DMillis->operator [](0);
			for(j = 1; j < p1DMillis->GetSize(); j++)
			{
				dwMillis = p1DMillis->operator [](j);
				pLyricEventsV2->m_msaTokensDuration.Add(dwMillis - dwLastMillis);
				dwLastMillis = dwMillis;
			}
			pLyricEventsV2->m_msaTokensDuration.Add(0xffffffff - dwLastMillis);

		}
		pLyricEventsV2->PrepareForScoring(pSequence->GetFile());
//		pMidiEvents = NULL;
//		pLyricEventsV2->m_iTrack = pSequence->GetFile()->GetMelodyTrack(
//			&pMidiEvents,
//			p2DTicks[i]);
//		pLyricEventsV2->m_
	}
	for(i = 0; i < tka2DTokensTicks.GetSize(); i++)
	{
		pLyricEventsV2 = (CLyricEventsV2 *) lyricEventsForPositionCB.GetAt(i);
		pFile->m_eventsTracksForPositionCB.Add(pLyricEventsV2);

        pFile->m_eventstracksV002.Add(pLyricEventsV2);

		pSequence->GetFile()->MillisecsToTicks(
			&pLyricEventsV2->m_tkaTokensPosition,
			ms2DTokensMillis[i],
			-100);
		pSequence->GetFile()->MillisecsToTicks(
			&pLyricEventsV2->m_tkaNotesPosition,
			ms2DBegMillis[i],
			-100);
		for(j = 0; j < ms2DTokensMillis[i]->GetSize(); j++)
		{
			if(ms2DTokensMillis[i]->GetAt(j) <= 100)
		        pLyricEventsV2->m_msaTokensPosition.Add(
			        0);
            else
			    pLyricEventsV2->m_msaTokensPosition.Add(
				    ms2DTokensMillis[i]->GetAt(j) - 100);
		}
		p1DNoteOnMillis = ms2DBegMillis[i];
		p1DNoteOffMillis = ms2DEndMillis[i];
		ASSERT(p1DNoteOnMillis->GetSize() ==
			p1DNoteOffMillis->GetSize());
		for(j = 0; j < p1DNoteOnMillis->GetSize(); j++)
		{
			pLyricEventsV2->m_msaNotesDuration.Add(
				p1DNoteOffMillis->GetAt(j) -
				p1DNoteOnMillis->GetAt(j));
		}
		for(j = 0; j < p1DNoteOnMillis->GetSize(); j++)
		{
			if(p1DNoteOnMillis->GetAt(j) <= 100)
				pLyricEventsV2->m_msaNotesPosition.Add(
					0);
			else
				pLyricEventsV2->m_msaNotesPosition.Add(
					p1DNoteOnMillis->GetAt(j) - 100);
		}
		
		p1DMillis = ms2DTokensMillis[i];
		if(p1DMillis->GetSize() > 0)
		{
			dwLastMillis = p1DMillis->operator [](0);
			for(j = 1; j < p1DMillis->GetSize(); j++)
			{
				dwMillis = p1DMillis->operator [](j);
				pLyricEventsV2->m_msaTokensDuration.Add(dwMillis - dwLastMillis);
				dwLastMillis = dwMillis;
			}
			pLyricEventsV2->m_msaTokensDuration.Add(0xffffffff - dwLastMillis);

		}
		pLyricEventsV2->PrepareForLyricsDisplay(pSequence->GetFile());
        CMidiLyricTrack * pLyricTrk = pFile->m_ptracks->CreateLyricTrack();
        pLyricTrk->Prepare(*pLyricEventsV2);
        //pFile->m_ptracks->Add(pLyricTrk);
//		pMidiEvents = NULL;
//		pLyricEventsV2->m_iTrack = pSequence->GetFile()->GetMelodyTrack(
//			&pMidiEvents,
//			p2DTicks[i]);
//		pLyricEventsV2->m_
	}

   	for(i = 0; i < tka2DTokensTicks.GetSize(); i++)
	{
		pLyricEventsV2 = (CLyricEventsV2 *) lyricEventsForBouncingBall.GetAt(i);
		pFile->m_eventsTracksForBouncingBall.Add(pLyricEventsV2);

        //pFile->m_eventstracksV002.Add(pLyricEventsV2);

		pSequence->GetFile()->MillisecsToTicks(
			&pLyricEventsV2->m_tkaTokensPosition,
			ms2DTokensMillis[i],
			-100);
		pSequence->GetFile()->MillisecsToTicks(
			&pLyricEventsV2->m_tkaNotesPosition,
			ms2DBegMillis[i],
			-100);
		for(j = 0; j < ms2DTokensMillis[i]->GetSize(); j++)
		{
			if(ms2DTokensMillis[i]->GetAt(j) <= 100)
		        pLyricEventsV2->m_msaTokensPosition.Add(
			        0);
            else
			    pLyricEventsV2->m_msaTokensPosition.Add(
				    ms2DTokensMillis[i]->GetAt(j) - 100);
		}
		p1DNoteOnMillis = ms2DBegMillis[i];
		p1DNoteOffMillis = ms2DEndMillis[i];
		ASSERT(p1DNoteOnMillis->GetSize() ==
			p1DNoteOffMillis->GetSize());
		for(j = 0; j < p1DNoteOnMillis->GetSize(); j++)
		{
			pLyricEventsV2->m_msaNotesDuration.Add(
				p1DNoteOffMillis->GetAt(j) -
				p1DNoteOnMillis->GetAt(j));
		}
		for(j = 0; j < p1DNoteOnMillis->GetSize(); j++)
		{
			if(p1DNoteOnMillis->GetAt(j) <= 100)
				pLyricEventsV2->m_msaNotesPosition.Add(
					0);
			else
				pLyricEventsV2->m_msaNotesPosition.Add(
					p1DNoteOnMillis->GetAt(j) - 100);
		}
		
		p1DMillis = ms2DTokensMillis[i];
		if(p1DMillis->GetSize() > 0)
		{
			dwLastMillis = p1DMillis->operator [](0);
			for(j = 1; j < p1DMillis->GetSize(); j++)
			{
				dwMillis = p1DMillis->operator [](j);
				pLyricEventsV2->m_msaTokensDuration.Add(dwMillis - dwLastMillis);
				dwLastMillis = dwMillis;
			}
			pLyricEventsV2->m_msaTokensDuration.Add(0xffffffff - dwLastMillis);

		}
		pLyricEventsV2->PrepareForBouncingBall(pSequence->GetFile());
        //CMidiLyricTrack * pLyricTrk = new CMidiLyricTrack(pSequence->GetFile());
        //pLyricTrk->Prepare(*pLyricEventsV2);
        //pFile->m_ptracks->Add(pLyricTrk);
//		pMidiEvents = NULL;
//		pLyricEventsV2->m_iTrack = pSequence->GetFile()->GetMelodyTrack(
//			&pMidiEvents,
//			p2DTicks[i]);
//		pLyricEventsV2->m_
	}

	
//	for(i = 0; i < dw2DMillis.GetSize(); i++)
//	{
//		p1DMillis = dw2DMillis[i];
//		m_2DTokensMillis.InsertAt(i, new C1DDWordArray());
//		dwLastMillis = 0;
//		for(j = 0; j < p1DMillis->GetSize(); j++)
//		{
//			dwMillis = p1DMillis->operator [](j);
//			m_2DTokensMillis[i]->Add(dwMillis - dwLastMillis);
//			dwLastMillis = dwMillis;
//		}
//	}

	TRACE(_T("\n"));
	/*for(i = 0; i < m_str2aRawTokens.GetSize(); i++)
	{
		for(j = 0; j < m_str2aRawTokens.GetAt(i)->GetSize(); j++)
		{
			TRACE(_T("%04d   "), i);
			TRACE(_T("%04d   "), j);
			TRACE(_T("%07d   "), tka2DTokensTicks.GetAt(i)->GetAt(j));
			TRACE(_T("%07d   "), pFile->m_eventsTracksForPositionCB[i]->m_tkaTokensPosition[j]);
			TRACE(_T("%07d   "), pFile->m_eventsTracksForPositionCB[i +  m_str2aRawTokens.GetSize()]->m_tkaTokensPosition[j]);
			TRACE(_T("%s\n"), m_str2aRawTokens.GetAt(i)->GetAt(j));
		}
	}*/
	//POSITION pos = GetFirstViewPosition();
	//ASSERT(pos != NULL);
	//CXfplayerView *pView = (CXfplayerView *) GetNextView(pos);
    CXfplayerView *pView = GetLyricView();
    if(pView != NULL)
    {
	    ASSERT(pView != NULL);
//	    pView->XFUpdateFonts(lpstra2DTokens);
    }

    //return (pFile->fdwSMF & SMF_F_EOF) ? SMF_END_OF_FILE : CMidiFile::Success;
//	pSequence->GetState() = CMidiSequence::StatusOpened;

	return;
}

void CCDDoc::OnPositionCB()
{
	
//	SetModifiedFlag(TRUE);
//	POSITION pos = GetFirstViewPosition();
//	if(pos != NULL)
//	{
//		CXfplayerView* pView = (CXfplayerView* ) GetNextView(pos);
//		pView->OnPositionCB();
//	}
//	m_iPlayingTokenIndex++;

}

void CCDDoc::Stop()
{
    if(IsWaitingToPlay())
    {
        SetWaitingToPlay(false);
    }
    else
    {
	    CVmpApp *pApp = (CVmpApp *) AfxGetApp();
	    ASSERT(pApp != NULL);	
	    //CWaveIn * pWaveIn = pApp->GetWaveIn();
	    //m_pmidiplayer->PostThreadMessage(MIDIPLAYERMESSAGE_STOP, 0, 0);
		m_pmidiplayer->PostThreadMessage(MIDIPLAYERMESSAGE_COMMAND, m_pmidiplayer->CommandStop, 0);
    }
}

void CCDDoc::Pause()
{
	m_pmidiplayer->Pause();
}

void CCDDoc::OnUpdateStop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(GetMidiPlayer() &&
        (GetMidiSequenceState() == CMidiSequence::StatusPaused ||
		GetMidiSequenceState() == CMidiSequence::StatusPlaying ||
        IsWaitingToPlay()));
}

void CCDDoc::OnUpdatePause(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(GetPauseEnable());
	pCmdUI->SetCheck(IsPaused() ? 1 : 0);
}

void CCDDoc::OnCloseDocument() 
{
    CKeeper<bool> closingFlagKeeper(&m_bClosing, true, false, true);
    CSingleLock slSongData(&m_csSongData, true);
	CWaitCursor wait;

	DetachPlaylistDoc();

	// TODO: Add your specialized code here and/or call the base class
   	CVmpApp * papp = (CVmpApp *) AfxGetApp();
	ASSERT(papp != NULL);

	CWinThread * pThreadV2  = papp->GetThreadV2();
    ASSERT(pThreadV2 != NULL);

	CWaveIn * pwavein = papp->WaveCentralGetWaveIn();
    ASSERT(pwavein != NULL);
    
    CMidiSequence * pSequence = NULL;
    if(GetMidiPlayer())
    {
        pSequence = HelperGetMidiSequence();
    }
	
    if(IsPlaying())
	{
		Stop();
        pSequence->m_evMmsgDone.Lock();
	}

   	((CXfplayerThreadV2 *)pThreadV2)->EnableWaveInMessageTranslation(false);
	if(m_bScoring)
	{
		pwavein->Release();
		m_bScoring = false;
	}
	DeleteContents();
//    GetMidiSequence()->CloseFile();
    if(GetMidiPlayer())
    {
        //CMidiSequence * pSequence = GetMidiSequence();
        m_pmidiplayer->PostThreadMessage(WM_QUIT, 0, 0);
        m_pmidiplayer = NULL;

    }
    slSongData.Unlock();
    closingFlagKeeper.KeepAway();
	COleServerDoc::OnCloseDocument();
}

void CCDDoc::DeleteContents() 
{
//    while(m_str2aRawTokens.GetSize() > 0)
  //  {
    //    delete m_str2aRawTokens[0];
      //  m_str2aRawTokens.RemoveAt(0);
    //}
	// TODO: Add your specialized code here and/or call the base class
//	int nIndex, nSize;
//	nSize = m_Tokens.GetSize();
//	for(nIndex = 0; nIndex < nSize; nIndex++)
//	{
//		delete &m_Tokens.GetAt(nIndex);
//	}
//	m_Tokens.RemoveAll();
//	m_TokensMillis.RemoveAll();
//	m_csObjects.Lock();
//	if(m_pInfoHeader != NULL)
//	{
//		delete m_pInfoHeader;
//		m_pInfoHeader = NULL;
//	}
//	if(m_pInfoHeaderLS != NULL)
//	{
//		delete m_pInfoHeaderLS;
//		m_pInfoHeaderLS = NULL;
//	}
//	if(m_lpSongName != NULL)
//	{
//		free(m_lpSongName);
//		m_lpSongName = NULL;
//	}
	m_xfInfoHeaders.Empty();
	m_xflha.RemoveAll();
	m_bHasTitle = false;
//	m_csObjects.Unlock();
	ClearTokens();

	CXfplayerView *pView = GetLyricView();
	if(pView != NULL)
		pView->ClearLyricLines(true);
//	int i, iSize;
//	iSize = m_midiSequence.m_File.m_eventsTracksV1.GetSize();
//	for(i = 0; i < iSize; i++)
//	{
//		CLyricEventsV1 *pEvents = m_midiSequence.m_File.m_eventsTracksV1[i];
//		pEvents->Reset();
//	}
    //pSequence->SendReset_();
	//CVmpApp * pApp = (CVmpApp *) AfxGetApp();


	COleServerDoc::DeleteContents();
    CXfplayerViewUpdateHint hint;
    hint.SetType(CXfplayerViewUpdateHint::UpdateFull);
    UpdateAllViews(NULL, 0L, &hint);
}

/*void CCDDoc::SetApproximatePosition(double rate)
{
    m_csMidi.Lock();
	m_pmidiplayer->PostThreadMessage(WM_USER + 100, (WPARAM) rate, 0);

    CXfplayerView * pView =  GetLyricView();
    if(pView != NULL)
        pView->SetPlayingPosition(rate);
    m_csMidi.Unlock();

}*/

void CCDDoc::ClearTokens()
{
//	CStringArray *pTokens;
//	int i;//, j;
//	m_csObjects.Lock()
//	for(i = 0; i < m_str2aRawTokens.GetSize(); i++)
//	{
//        delete m_str2aRawTokens.ElementAt(i);
//		pTokens->RemoveAll();
//	}
//    m_str2aRawTokens.RemoveAll();
    
//    if(GetMidiPlayer())
  //  {
    HelperDeleteContents();
    //}
//	m_csObjects.Unlock();
//	m_2DTokensMillis.RemoveAll();
//	pFile->m_eventsTracksV1.Add(new CLyricEventsV1());
//	pFile->m_eventsTracksV1.Add(new CLyricEventsV1());
//	pFile->m_eventsTracksV1.GetAt(0)->m_nEventType = 1;

}

/*    while(pFile->m_ptracks->m_tkPosition == 0)
    {
        smfrc = pFile->GetNextEvent((CMidiEvent *)&event, tkMax);
        if (CMidiFile::Success != smfrc)
        {
            /* smfGetNextEvent doesn't set this because smfSeek uses it
            ** as well and needs to distinguish between reaching the
            ** seek point and reaching end-of-file.
            **
            ** To the user, however, we present the selection between
            ** their given tkBase and tkEnd as the entire file, therefore
            ** we want to translate this into EOF.
            */
/*            if (SMF_REACHED_TKMAX == smfrc)
            {
                pFile->m_fdwSMF |= SMF_F_EOF;
            }
            
            TRACE1("smfReadEvents: smfGetNextEvent() -> %u", (UINT)smfrc);
            break;
        }

        
	    if ((MIDI_META == EVENT_TYPE(event)) &&
		    (MIDI_META_XF_LYRICS_HEADER == EVENT_META_TYPE(event)))
        {
			CString str((LPCSTR) event.hpbParm, event.cbParm);
			if(str.Mid(0, 5) == "$Lyrc")
			{
				int iLo;
				int iHi;
				iLo = str.Find(_T(":"), 0);
				if(iLo < 0)
					goto XF_Lyrics_Parse_End;
				iHi = str.Find(_T(":"), iLo + 1);
				if(iHi < 0)
					goto XF_Lyrics_Parse_End;
				iLo = iHi;
				iHi = str.Find(_T(":"), iLo + 1);
				if(iHi < 0)
					goto XF_Lyrics_Parse_End;
				m_LyricsDisplayOffset = _ttoi(str.Mid(iLo + 1, iHi - iLo - 1));
			XF_Lyrics_Parse_End:;

			}
        }
    }*/


void CCDDoc::OnMidiPlayerNotifyEvent(CMidiPlayer::CNotifyEventData * pdata)
{
	CMidiSequence * pseq = pdata->m_pplayer->GetSequence();
	ASSERT(pseq == HelperGetMidiSequence());

	CVmpApp * papp = (CVmpApp *) AfxGetApp();
	ASSERT(papp != NULL);


	CWinThread * pThreadV2  = papp->GetThreadV2();
    ASSERT(pThreadV2 != NULL);

	CWaveIn * pwavein = papp->WaveCentralGetWaveIn();
    ASSERT(pwavein != NULL);
	if(pdata->m_enotifyevent == CMidiPlayer::NotifyEventGenericMmsgDone
		&& m_bPlay)
	{
		CXfplayerView *pView = GetLyricView();
		ASSERT(pView != NULL);

		double dRate =	pView->GetProgressSlider()->GetRate();
		if(dRate == 0.0)
		{
			//Show Title
			pView->SetTitleVisible(true);
			pView->UpdateTitle();

			// Time to let the title be visible
			m_msPlayTimeOut = timeGetTime() + 3000;

	//	    Sleep(3000);
		}
		else
		{
			m_msPlayTimeOut = timeGetTime();
		}
		m_bWaitingToPlay = true;
		m_bPlay = false;
	}
//	else if(lpmdd->SequenceWasInSpecialModeV001())
  //  {
    //    TRACE(_T("CCDDoc::OnMmsgDone lpmdd->SequenceWasInSpecialModeV001()\n"));
    //}
    else if(IsSettingNextSong())
	{
        TRACE(_T("CCDDoc::OnMmsgDone IsSettingNextSong()\n"));
		((CXfplayerThreadV2*)pThreadV2)->EnableWaveInMessageTranslation(false);
		if(pwavein->IsRecording())
		{
			pwavein->Reset();
		}
		pseq->CloseFile();
        m_dProgressRate = 0.0;
		Play(true);
		m_bSettingNextSong = false;
	}
	else if(pdata->m_enotifyevent
		== CMidiPlayer::NotifyEventPlaybackEnd)
	{
		StartScoring(false);
		m_dProgressRate = 0.0;
		UpdateProgress();
		if(GetLyricView()->HasNextSong())
		{
			NextSong(true, true);
		}
		TRACE(_T("CCDDoc::OnMmsgDone NotifyEventPlaybackEnd \n"));
	}
    else if(pdata->m_enotifyevent
		== CMidiPlayer::NotifyEventStop)
    {
        TRACE(_T("CCDDoc::OnMmsgDone Else if Stopping\n"));
        StartScoring(false);
        m_dProgressRate = 0.0;
        GetLyricView()->SetProgressRate(GetProgressRate());
        UpdateProgress();
        
    }
	else 
	{
		int i = 0;
        i++;
	}

	m_evMMDone.SetEvent();
}

void CCDDoc::OnMmsgDone(CMidiSequence *pseq, LPMIDIDONEDATA lpmdd)
{
	ASSERT(pseq == HelperGetMidiSequence());

	CVmpApp * papp = (CVmpApp *) AfxGetApp();
	ASSERT(papp != NULL);

//	CMainFrame *pFrame = (CMainFrame *) pApp->GetMainWnd();
//	ASSERT(pFrame != NULL);

	CWinThread * pThreadV2  = papp->GetThreadV2();
    ASSERT(pThreadV2 != NULL);

	CWaveIn * pwavein = papp->WaveCentralGetWaveIn();
    ASSERT(pwavein != NULL);
	if(m_bPlay)
	{
		CXfplayerView *pView = GetLyricView();
		ASSERT(pView != NULL);

		double dRate =	pView->GetProgressSlider()->GetRate();
		if(dRate == 0.0)
		{
			//Show Title
			pView->SetTitleVisible(true);
			pView->UpdateTitle();

			// Time to let the title be visible
			m_msPlayTimeOut = timeGetTime() + 3000;

	//	    Sleep(3000);
		}
		else
		{
			m_msPlayTimeOut = timeGetTime();
		}
		m_bWaitingToPlay = true;
		m_bPlay = false;
	}
	else if(pseq->IsChangingTempo())
	{
		TRACE(_T("CCDDoc::OnMmsgDone pSeq->IsChangingSettingPosition()\n"));
	}
	else if(lpmdd->SequenceWasInSpecialModeV001())
    {
        TRACE(_T("CCDDoc::OnMmsgDone lpmdd->SequenceWasInSpecialModeV001()\n"));
    }
    else if(IsSettingNextSong())
	{
        TRACE(_T("CCDDoc::OnMmsgDone IsSettingNextSong()\n"));
		((CXfplayerThreadV2*)pThreadV2)->EnableWaveInMessageTranslation(false);
		if(pwavein->IsRecording())
		{
			pwavein->Reset();
		}
		pseq->CloseFile();
        m_dProgressRate = 0.0;
		Play(true);
		m_bSettingNextSong = false;
	}
	else if(lpmdd->SequenceGetPreviousState() != CMidiSequence::StatusStopping
		&& GetLyricView()->HasNextSong()
        && !pseq->IsSettingPosition())
	{
        TRACE(_T("CCDDoc::OnMmsgDone \n"));
        StartScoring(false);
        m_dProgressRate = 0.0;
        UpdateProgress();
        NextSong(true, true);
	}
    else if(pseq->IsSettingPosition() ||
		pseq->WasInSpecialModeV001())
    {
    }
    else if(lpmdd->SequenceGetPreviousState() == CMidiSequence::StatusStopping)
    {
        TRACE(_T("CCDDoc::OnMmsgDone Else if Stopping\n"));
        StartScoring(false);
        m_dProgressRate = 0.0;
        GetLyricView()->SetProgressRate(GetProgressRate());
        UpdateProgress();
        
    }
	else //if(uPreviousState != CMidiSequence::StatusStopping)
	{
        TRACE(_T("CCDDoc::OnMmsgDone Else\n"));
        StartScoring(false);
        m_dProgressRate = 0.0;
        GetLyricView()->SetProgressRate(m_dProgressRate);
        UpdateProgress();
        
	}


	m_evMMDone.SetEvent();

}

BOOL CCDDoc::IsPlaying()
{
	return GetMidiPlayer() && HelperGetMidiSequence()->IsPlaying();
}

CXfplayerView * CCDDoc::GetLyricView()
{
	
	POSITION pos = GetFirstViewPosition();
	while(pos != NULL)
	{
		CView * pView = GetNextView(pos);
		if(pView->IsKindOf(RUNTIME_CLASS(CXfplayerView)))
			return (CXfplayerView *) pView;
	}
	return NULL;
	
}

double CCDDoc::GetScoreRate()
{
	return m_pscoring->GetScore();
}

//void CCDDoc::SetScoreRate(double dScoreRate)
//{
//	m_dScoreRate = dScoreRate;
//}

CXfplayerScoring * CCDDoc::GetScoring()
{
	return m_pscoring;
}




CArray<
	CXFInfoHeaderLS,
	CXFInfoHeaderLS &> * CCDDoc::GetInfoHeadersLS()
{
	return &m_xfInfoHeaders.m_xfaInfoHeaderLS;
}

BOOL CCDDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	if(lpszPathName == NULL)
		return TRUE;
    CKeeper<bool> savingFlagKeeper(&m_bSavingHelper, true, false, true);
	
    CString strPathName(lpszPathName);
    if(strPathName.Right(4).CompareNoCase(_T(".mid")) != 0)
    {
        AfxMessageBox(IDS_ERROR_SAVEASXFONLY);
        return FALSE;
    }
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
            CHUNKHDR FAR * pCh = (CHUNKHDR FAR *)pTrack->GetTrackImage();
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
    pFile->Format0();


	try
	{
		//m_pmidiplayer->SaveFile(lpszPathName);
        //COleServerDoc::OnSaveDocument(lpszPathName);
        CDocument::OnSaveDocument(lpszPathName);
	}
	catch(CMidiException *pe)
	{
		pe->Delete();
	}
	
    memcpy(&m_mfh, pFile->m_pFileHeader, sizeof(MIDIFILEHDR));
    pFile->m_ptracks->ExpandTrack(0);
    pFile->ToWorkStorage();
	
	SetModifiedFlag(FALSE);     // back to unmodified

	return TRUE;        // success
}


UINT CCDDoc::GetMidiSequenceState()
{
//	ASSERT(m_pmidiplayer != NULL);
//	return m_pmidiplayer->GetSequenceState();
    return HelperGetMidiSequence()->GetState();
}


bool CCDDoc::IsSettingNextSong()
{
	return m_bSettingNextSong;
}

DWORD CCDDoc::GetPlayTimeOut()
{
    return m_msPlayTimeOut;
}

bool CCDDoc::IsWaitingToPlay()
{
    return m_bWaitingToPlay;
}

void CCDDoc::SetWaitingToPlay(bool bWaitingToPlay)
{
    m_bWaitingToPlay = bWaitingToPlay;
}

void CCDDoc::OnViewLyrics() 
{
	// TODO: Add your command handler code here
	TCHAR lpszModuleFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);
	TCHAR lpszModuleFolder[MAX_PATH + 1];
	LPTSTR lpszModuleFileName;
	GetFullPathName(lpszModuleFilePath, MAX_PATH + 1, lpszModuleFolder, &lpszModuleFileName);
	CString strModuleFolder(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);
	CString strFolder;
	strFolder = strModuleFolder;
    CString str;
    str.LoadString(IDS_FOLDER_LYRICS);
	strFolder += str;
    CFileFind fileFind;
    if(fileFind.FindFile(strFolder))
    {
        
        if(!fileFind.FindNextFile())
        {
            if(!fileFind.IsDirectory())
            {
                if(DeleteFile(strFolder))
                {
                    if(!CreateDirectory(strFolder, NULL))
                    {
                        AfxMessageBox(_T("Não foi possível criar diretório de letras de músicas"));
                        return;
                    }
                }
                else
                {
                    AfxMessageBox(_T("Não foi possível criar diretório de letras de músicas. Existe um outro arquivo com mesmo nome que não pôde ser apagado."));
                    return;
                }
            }
        }
    }
    else
    {
        if(!CreateDirectory(strFolder, NULL))
        {
            AfxMessageBox(_T("Não foi possível criar diretório de letras de músicas"));
            return;
        }
    }
    
    CString strPath;
    CString strFile;
    //if(GetMidiSequence()->m_strFile.IsEmpty())
    if(GetPathName().IsEmpty())
    {
        strFile = "Sem Título";
    }
    else
    {
	    TCHAR lpszFolder[MAX_PATH + 1];
	    LPTSTR lpszFileName;
	    GetFullPathName(GetPathName(), MAX_PATH + 1, lpszFolder, &lpszFileName);
        strFile = lpszFileName;
    }
    int i = 1;
    strPath.Format(_T("%s\\%s.txt"), strFolder, strFile);
    while(true)
    {
        if(!fileFind.FindFile(strPath))
            break;
        strPath.Format(_T("%s\\%s[%d].txt"), strFolder, strFile, i);
        i++;
    }
    CFile file(
        strPath,
        CFile::modeCreate |
        CFile::modeWrite |
        CFile::shareDenyWrite);
    
	CWStr wstrText = GetLyricView()->GetPlainTextV001();
	WCHAR wchBom = 0xFEFF;
	file.Write(&wchBom, sizeof(wchBom));
	file.Write((LPCWSTR) wstrText, wstrText.GetLength() * sizeof(WCHAR));
    file.Flush();
    file.Close();

	CVmpApp * papp = (CVmpApp *) AfxGetApp();

	papp->OpenTextFile(strPath);

/*    ShellExecute(
        GetLyricView()->m_hWnd,
        _T("open"),
        strPath,
        NULL,
        strFolder,
        SW_SHOWNORMAL);*/
    
}

void CCDDoc::OnUpdateViewLyrics(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	pCmdUI->Enable(GetMidiPlayer() &&
        HelperGetMidiSequence()->IsOpened());
}

bool CCDDoc::GetPlayEnable()
{
	CVmpApp *pApp = (CVmpApp *) AfxGetApp();
    ASSERT(pApp != NULL);
    bool bEnable;
    
    if(pApp->m_pMainWnd == NULL)
    {
        bEnable = GetMidiPlayer() &&
            !IsWaitingToPlay();
    }
    else if(pApp->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CKaraokeSDIFrame)))
    {
//        bEnable = GetMidiPlayer() &&
  //          (GetMidiSequenceState() == CMidiSequence::StatusOpened ||
	//	   (GetLyricView()->HasNextSong() && 
	//	   pApp->GetPlayingDocument() == NULL)) &&
      //     !IsWaitingToPlay();
        bEnable = GetMidiPlayer()
			&& (GetMidiSequenceState() == CMidiSequence::StatusOpened)
			&& !IsWaitingToPlay();
    }
    else
    {
        bEnable = GetMidiPlayer()
			&& GetMidiSequenceState() == CMidiSequence::StatusOpened
			&& !IsWaitingToPlay();
    }

    return bEnable;
}

bool CCDDoc::GetPauseEnable()
{
    return GetMidiPlayer() &&
        (GetMidiSequenceState() == CMidiSequence::StatusPaused ||
		GetMidiSequenceState() == CMidiSequence::StatusPlaying);
}

bool CCDDoc::IsOpening()
{
    return m_bOpening;
}

/////////////////////////////////////////////////////////////////////////////
// CMdiDoc server implementation

COleServerItem* CCDDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CXfplayerServerItem* pItem = new CXfplayerServerItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}

/////////////////////////////////////////////////////////////////////////////
// CMdiDoc Active Document server implementation

CDocObjectServer *CCDDoc::GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite)
{
	return new CDocObjectServer(this, pDocSite);
}




int CCDDoc::GetNextSong()
{
	if(m_dwaSongsCodes.GetSize() <= 0)
		return -1;
	else
	{
		int i = m_dwaSongsCodes.GetAt(0);
		m_dwaSongsCodes.RemoveAt(0);
		return i;
	}
}

void CCDDoc::UpdateProgress(CView * pView)
{
    CXfplayerViewUpdateHint uh;
    uh.SetType(CXfplayerViewUpdateHint::UpdateProgress);
    UpdateAllViews(pView, 0L, &uh);

}

double CCDDoc::GetProgressRate()
{
    return m_dProgressRate;
}

void CCDDoc::SetProgressRate(double dRate, CView * pView)
{
    
    

    if(IsPlaying())
//    if(m_pmidiplayer == NULL)
  //  {
    //    GetLyricView()->SetPlayingPosition((TICKS) dRate);
      //  //m_dProgressRate = 0.0;
//    }
  //  else
    {
        m_csMidi.Lock();
        LPDOUBLESTRUCT lpds = new DOUBLESTRUCT;
        lpds->d = dRate;
	    m_pmidiplayer->PostThreadMessage(WM_USER + 100, (WPARAM) lpds, 0);
        m_csMidi.Unlock();
    }
    else
    {
        m_dProgressRate = dRate;
    }
//    else
  //  {
    //    UpdateProgress();
    //}

    UpdateProgress(pView);

}

void CCDDoc::OnUpdateProgress(double dRate, CView * pView)
{
    m_dProgressRate = dRate;

    UpdateProgress(pView);
}

void CCDDoc::OnUpdateProgress(CView *pView)
{
    if(GetMidiPlayer())
    {
        CMidiSequence * pSeq = HelperGetMidiSequence();
        TICKS tkTime;
        if(MMSYSERR_NOERROR == pSeq->GetTime(&tkTime))
        {
            double dRate = ((double) tkTime) / pSeq->GetFile()->m_tkLength;
            OnUpdateProgress(dRate, pView);
        }
    }
    else
    {
        OnUpdateProgress(0.0, pView);
    }

}

BOOL CCDDoc::DoSave(LPCTSTR lpszPathName, BOOL bReplace)
	// Save the document data to a file
	// lpszPathName = path name where to save document file
	// if lpszPathName is NULL then the user will be prompted (SaveAs)
	// note: lpszPathName can be different than 'm_strPathName'
	// if 'bReplace' is TRUE will change file name if successful (SaveAs)
	// if 'bReplace' is FALSE will not change path name (SaveCopyAs)
{
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

        CXfplayerSaveFileDialog sfd;
        
		if (!sfd.DoPromptFileName(newName,
		  bReplace ? AFX_IDS_SAVEFILE : AFX_IDS_SAVEFILECOPY,
		  OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, FALSE, pTemplate))
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

void CCDDoc::OnViewMidievents() 
{
	// TODO: Add your command handler code here
	// create frame - set as main document frame
//	BOOL bAutoDelete = pDocument->m_bAutoDelete;

    CVmpApp * pApp = (CVmpApp * ) AfxGetApp();
    pApp->GetMidiDocTemplate()->OpenDocumentFile(GetPathName());

//    CXfplayerFrame * pFrame = new CXfplayerFrame();
  //  CCreateContext context;
    //context.m_pCurrentDoc = this;
//    context.m_pCurrentFrame = pFrame;
  //  context.m_pLastView = GetLyricView();
    //context.m_pNewDocTemplate = NULL;
//    context.m_pNewViewClass = RUNTIME_CLASS(CMidiEventsView);
  //  pFrame->LoadFrame(IDR_MIDIEVENTS, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
    //    AfxGetMainWnd(), &context);
}

void CCDDoc::OnUpdateViewMidievents(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

//bool CCDDoc::IsSaving()
//{
  //  return m_bSaving;
//}

bool CCDDoc::IsClosing()
{
    return m_bClosing;
}

void CCDDoc::OnFileProperties() 
{
	// TODO: Add your command handler code here
	
  	CXfPropertiesDialog propertiesDialog(this);
	propertiesDialog.DoModal();

}

void CCDDoc::OnUpdateFileProperties(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
//	ASSERT(pApp != NULL);
//	CCDDoc * pDoc = pApp->GetPlayerDocument();
  //  if(pDoc == NULL)
    //{
      //  pCmdUI->Enable(FALSE);
        //return;
    //}
//	ASSERT(pDoc != NULL);
//	pCmdUI->Enable(
//		pDoc->GetMidiSequenceState() !=
//		CMidiSequence::StatusNoFile &&
  //      !pDoc->IsPlaying());
	
	ASSERT(this != NULL);
	pCmdUI->Enable(
		GetMidiSequenceState() !=
		CMidiSequence::StatusNoFile &&
        !IsPlaying());
}

void CCDDoc::OnScoringEnable() 
{
	// TODO: Add your command handler code here

    if(m_bScoring)
    {
        EnableScoring(false);
    }
    else
    {
        EnableScoring(true);

    }

}

void CCDDoc::OnUpdateScoringEnable(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//CWaveCentral * pcentral = CWaveCentral::AppGetWaveCentral();
	//CWaveIn * pwavein = pcentral->WaveCentralGetWaveIn();
	pCmdUI->Enable();
    pCmdUI->SetCheck(IsScoringEnabled() ? 1 : 0);
}

VMSRESULT CCDDoc::EnableScoring(bool bEnable)
{
	CVmpApp * papp = (CVmpApp *) AfxGetApp();
	CWaveIn * pwavein = papp->WaveCentralGetWaveIn();
    if(bEnable)
    {
		DBSave(_T("Scoring"), 1);
		
		if(!m_bScoring)
		{
			m_bScoring = true;
			pwavein->AddRef();
		}
        if(IsPlaying())
        {
            StartScoring(true);
        }
    }
    else
    {
		DBSave(_T("Scoring"), 0);
		if(m_bScoring)
		{
			m_bScoring = false;
			pwavein->Release();
		}
        if(IsPlaying())
        {
            StartScoring(false);
        }
    }
	if(GetLyricView() != NULL)
	{
		GetLyricView()->OnScoringEnable(bEnable);
	}
    return VMSR_SUCCESS;

}

VMSRESULT CCDDoc::StartScoring(bool bStart)
{
   	CVmpApp *papp = (CVmpApp *) AfxGetApp();
	ASSERT(papp != NULL);
	
    CWaveIn * pwavein = papp->WaveCentralGetWaveIn();
	if(pwavein == NULL)
		return VMSR_SUCCESS;

	CWaveBuffer * pbuffer = pwavein->GetBuffer();
	ASSERT(pbuffer != NULL);

	LPWAVEFORMATEX lpformatex = pwavein->GetFormatEx();
	ASSERT(lpformatex != NULL);

	CXfplayerThreadV2 * pthreadv2  = (CXfplayerThreadV2 *) papp->GetThreadV2();
		
    if(IsScoringEnabled() && bStart)
    {
	    if(pwavein->Open() == MMSYSERR_NOERROR)
	    {
		    pwavein->Start();
		    pthreadv2->EnableWaveInMessageTranslation();
		    GetScoring()->Initialize(
			    440.0,
			    lpformatex->nSamplesPerSec / pbuffer->m_uiSkippedSamplesCount,
			    pbuffer);
		    CEventsTracksV1 * peventsa = &HelperGetMidiSequence()->GetFile()->m_eventsTracksForScoring;
		    ASSERT(peventsa != NULL);
		    CLyricEventsV2 * pevents;
            CBaseArray<CStrArray, CStrArray & > * p2DTokens = &HelperGetMidiSequence()->GetFile()->m_str2aRawTokens;
		    if(p2DTokens == NULL)
			    pevents = NULL;
		    else if(p2DTokens->GetSize() <= 0)
			    pevents = NULL;
		    else if(peventsa->GetSize() < p2DTokens->GetSize())
			    pevents = NULL;
		    else
		    {
			    //pEvents = (CLyricEventsV2 *) pEventsArray->operator [](m_p2DTokens->GetSize());
			    pevents = (CLyricEventsV2 *) peventsa->operator [](0);
			    ASSERT(pevents != NULL);
			    ASSERT(pevents->GetClassOrder() == 2);
		    }
		    if(pevents != NULL)
		    {
			    m_pscoring->Start(pevents->GetTotalNotesMillis());
		    }
		    else
		    {
			    m_pscoring->Start(0);
		    }
	    }
    }
    else if(!bStart)
    {
   		pthreadv2->EnableWaveInMessageTranslation(false);
		if(pwavein->IsRecording())
		{
            pwavein->Stop();
			pwavein->Reset();
		}
		if(pwavein->IsOpened())
		{
			pwavein->Close();
		}
    }
    return VMSR_SUCCESS;
}

bool CCDDoc::IsScoringEnabled()
{
    return m_bScoring;
}

afx_msg LRESULT CCDDoc::OnXfplayerDocMessage(WPARAM wParam, LPARAM lParam)
{
    if(wParam == 1)
    {
        LPXFPLAYERDOCINIT lpdocinit = (LPXFPLAYERDOCINIT) lParam;
        m_pthreadV1 = lpdocinit->pthreadV1;
    }

    return 0;
}

bool CCDDoc::IsPaused()
{
    return GetMidiPlayer() &&
        GetMidiSequenceState() == CMidiSequence::StatusPaused;
}


bool CCDDoc::Attach(CPlaylistDoc *pplaylistdoc)
{
    if(m_pplaylistdoc != NULL)
    {
        DetachPlaylistDoc();
    }
	m_pplaylistdoc = pplaylistdoc;
	CPointerListener<CPlaylistDoc>::AddPointer(pplaylistdoc);
	return GetLyricView()->OnAttachPlaylistDoc();
}

CPlaylistDoc * CCDDoc::DetachPlaylistDoc()
{
    CPlaylistDoc * lpPlaylistDoc = m_pplaylistdoc;
    if(m_pplaylistdoc != NULL)
    {
        GetLyricView()->OnDetachPlaylistDoc();
		CPointerListener<CPlaylistDoc>::RemovePointer(m_pplaylistdoc);
        m_pplaylistdoc = NULL;
    }
    return lpPlaylistDoc;
}


CPlaylistDoc * CCDDoc::GetPlaylistDoc()
{
	return m_pplaylistdoc;
}

void CCDDoc::OnPointerClear(CPlaylistDoc *pdoc)
{
	if(pdoc == m_pplaylistdoc)
	{
		DetachPlaylistDoc();
	}

}


void CCDDoc::OnDeactivate() 
{
	m_pInPlaceFrame->SendMessage(WM_USER, 173, 0);	
	COleServerDoc::OnDeactivate();
}

CSingleDocTemplate * CCDDoc::GetAudioSpectrumDocTemplate()
{
	return m_pdoctemplateAudioSpectrum;
}

CSingleDocTemplate * CCDDoc::GetLevelMeterDocTemplate()
{
	return m_pdoctemplateLevelMeter;
}

CAudioSpectrumDoc * CCDDoc::OpenAudioSpectrumDoc(bool bMakeVisible)
{
	if(m_paudiospectrumdoc != NULL)
	{
		return m_paudiospectrumdoc;
	}
	else
	{
		ASSERT(m_pdoctemplateAudioSpectrum!= NULL);
		m_paudiospectrumdoc = (CAudioSpectrumDoc *) m_pdoctemplateAudioSpectrum->OpenDocumentFile(NULL, bMakeVisible);
		if(m_paudiospectrumdoc == NULL)
			return NULL;
		CPointerListener<CAudioSpectrumDoc>::AddPointer(m_paudiospectrumdoc);
		CVmpApp * papp = (CVmpApp *) AfxGetApp();
		CGenericViewUpdateHint uh(8792, 0, papp->WaveCentralGetWaveIn()->GetBuffer());
		m_paudiospectrumdoc->UpdateAllViews(NULL, 0, &uh);
		return m_paudiospectrumdoc;
	}
}

CLevelMeterDoc * CCDDoc::OpenLevelMeterDoc(bool bMakeVisible)
{
	if(m_plevelmeterdoc != NULL)
	{
		return m_plevelmeterdoc;
	}
	else
	{
		ASSERT(m_pdoctemplateLevelMeter!= NULL);
		m_plevelmeterdoc = (CLevelMeterDoc *) m_pdoctemplateLevelMeter->OpenDocumentFile(NULL, bMakeVisible);
		CPointerListener<CLevelMeterDoc>::AddPointer(m_plevelmeterdoc);
		CGenericViewUpdateHint uh(8791, 0, HelperGetMidiSequence());
		m_plevelmeterdoc->UpdateAllViews(NULL, 0, &uh);
		return m_plevelmeterdoc;
	}

}

CAudioSpectrumDoc * CCDDoc::GetAudioSpectrumDoc()
{
	return m_paudiospectrumdoc;
}

CLevelMeterDoc * CCDDoc::GetLevelMeterDoc()
{
	return m_plevelmeterdoc;
}

bool CCDDoc::IsAudioSpectrumOpened()
{
	return m_paudiospectrumdoc != NULL;
}

bool CCDDoc::IsLevelMeterOpened()
{
	return m_plevelmeterdoc != NULL;
}

CView * GetDocumentFirstView(CDocument * pdoc, CRuntimeClass * prtcView)
{
	if(pdoc == NULL)
		return NULL;
	else
	{
		POSITION pos = pdoc->GetFirstViewPosition();
		while(pos != NULL)
		{
			CView * pview = pdoc->GetNextView(pos);
			if(pview->IsKindOf(prtcView))
				return pview;
		}
		return NULL;
	}
}

CAudioSpectrumView * CCDDoc::GetAudioSpectrumView()
{
	return (CAudioSpectrumView *) 
				GetDocumentFirstView(
					m_paudiospectrumdoc,
					RUNTIME_CLASS(CAudioSpectrumView));
}

CLevelMeterView * CCDDoc::GetLevelMeterView()
{
	return (CLevelMeterView *) 
				GetDocumentFirstView(
					m_plevelmeterdoc,
					RUNTIME_CLASS(CLevelMeterView));

}

CTransparentFrameWndV8 * CCDDoc::GetAudioSpectrumFrame()
{
	CView * pview = GetAudioSpectrumView();
	if(pview == NULL)
		return NULL;
	else
	{
		CFrameWnd * pframe = pview->GetParentFrame();
		if(pframe != NULL
			&& pframe->IsKindOf(RUNTIME_CLASS(CTransparentFrameWndV8)))
		{
			return (CTransparentFrameWndV8 *) pframe;
		}
		else
			return NULL;
	}

}

CTransparentFrameWndV8 * CCDDoc::GetLevelMeterFrame()
{
	CView * pview = GetLevelMeterView();
	if(pview == NULL)
		return NULL;
	else
	{
		CFrameWnd * pframe = pview->GetParentFrame();
		if(pframe != NULL
			&& pframe->IsKindOf(RUNTIME_CLASS(CTransparentFrameWndV8)))
		{
			return (CTransparentFrameWndV8 *) pframe;
		}
		else
			return NULL;
	}
}

void CCDDoc::OnPointerClear(CAudioSpectrumDoc *pdoc)
{
	ASSERT(pdoc == m_paudiospectrumdoc);
	m_paudiospectrumdoc = NULL;

}

void CCDDoc::OnPointerClear(CLevelMeterDoc *pdoc)
{
	ASSERT(pdoc == m_plevelmeterdoc);
	m_plevelmeterdoc = NULL;

}

void CCDDoc::CloseAllAudioSpectrumDocuments()
{
	m_pdoctemplateAudioSpectrum->CloseAllDocuments(FALSE);
}

void CCDDoc::CloseAllLevelMeterDocuments()
{
	m_pdoctemplateLevelMeter->CloseAllDocuments(FALSE);
}

COleIPFrameWnd* CCDDoc::CreateInPlaceFrame(CWnd* pParentWnd)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pParentWnd);

	// get runtime class from the doc template
	CDocTemplate* pTemplate = GetDocTemplate();
	ASSERT_VALID(pTemplate);

	// use existing view if possible
	CWnd* pViewParent = NULL;
	CView* pView = NULL;
	//CFrameWnd* pFrame = GetFirstFrame();
	CKaraokeSDIFrame* pFrame = dynamic_cast<CKaraokeSDIFrame *> (GetFirstFrame());
	if (pFrame != NULL)
	{
	//	pView = (CView*)pFrame->GetDescendantWindow(AFX_IDW_PANE_FIRST, TRUE);
		pView = (CView*)pFrame->GetLyricView();
		if (pView != NULL)
		{
			ASSERT_KINDOF(CView, pView);
			pViewParent = pView->GetParent();
			m_dwOrigStyle = pView->GetStyle();
			m_dwOrigStyleEx = pView->GetExStyle();
		}
	}

	// create the frame from the template
	COleIPFrameWnd* pFrameWnd = (COleIPFrameWnd*)
		pTemplate->CreateOleFrame(pParentWnd, this, pView == NULL);
	if (pFrameWnd == NULL)
		return NULL;

	// connect the view to the frame window, if necessary
	if (pView != NULL)
	{
		ConnectView(pFrameWnd, pView);
		pView->ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_DRAWFRAME);
	}

	// remember original parent window for deactivate
	m_pOrigParent = pViewParent;

	// send OnInitialUpdate if new view was created
	if (pView == NULL)
		pTemplate->InitialUpdateFrame(pFrameWnd, this, FALSE);

	// verify the type
	ASSERT_VALID(pFrameWnd);
	ASSERT_KINDOF(COleIPFrameWnd, pFrameWnd);
	return pFrameWnd;
}

BOOL CCDDoc::OpenDocumentFile(const VARIANT FAR& varwszFilePath) 
{
	CString str;
	ASSERT(varwszFilePath.vt == VT_BSTR);
	str = varwszFilePath.bstrVal;
	return GetDocTemplate()->OpenDocumentFile(str, true) != NULL;

	//return TRUE;
}

BOOL CCDDoc::OpenFile(LPCTSTR bstrFilePath, BOOL bMakeVisible) 
{
	CString str;
	str = bstrFilePath;
	return GetDocTemplate()->OpenDocumentFile(str, true) != NULL;
}

CPlayerDoc * CCDDoc::GetPlayerDoc()
{
	return m_pplayerdoc;
}

CPlayerDoc * CCDDoc::OpenPlayerDoc(bool bMakeVisible)
{
	if(m_pplayerdoc != NULL)
	{
		return m_pplayerdoc;
	}
	else
	{
		ASSERT(m_pdoctemplateLevelMeter!= NULL);
		m_pplayerdoc = (CPlayerDoc *) m_pdoctemplatePlayer->OpenDocumentFile(NULL, bMakeVisible);
		if(m_pplayerdoc != NULL)
		{
			m_pplayerdoc->SetXfplayerDoc(this);
			CPointerListener<CPlayerDoc>::AddPointer(m_pplayerdoc);
		}
		return m_pplayerdoc;
	}
}

void CCDDoc::OnPointerClear(CPlayerDoc *pdoc)
{
	ASSERT(m_pplayerdoc == pdoc);
	m_pplayerdoc = NULL;
}

CPlayerControlSetV19Frame * CCDDoc::GetPlayerControlSetV19Frame()
{
	CView * pview = GetPlayerControlSetV19View();
	if(pview == NULL)
		return NULL;
	else
	{
		CFrameWnd * pframe = pview->GetParentFrame();
		if(pframe != NULL
			&& pframe->IsKindOf(RUNTIME_CLASS(CPlayerControlSetV19Frame)))
		{
			return (CPlayerControlSetV19Frame *) pframe;
		}
		else
			return NULL;
	}

}

CPlayerControlSetV19View * CCDDoc::GetPlayerControlSetV19View()
{
	return (CPlayerControlSetV19View *) 
				GetDocumentFirstView(
					m_pplayerdoc,
					RUNTIME_CLASS(CPlayerControlSetV19View));

}

bool CCDDoc::IsPlayerDocOpened()
{
	return m_pplayerdoc != NULL;
}

bool CCDDoc::IsPlayerControlSetV19ViewOpened()
{
	return GetPlayerControlSetV19View() != NULL;
}

void CCDDoc::MusicTempoReset()
{
	CMidiPlayer * pplayer = GetMidiPlayer();
	pplayer->SetTempoShift(0);
	GetPlayerDoc()->UpdateAllViews(NULL);
}

void CCDDoc::MusicTempoMinus()
{
	CMidiPlayer * pplayer = GetMidiPlayer();
    CMidiSequence * psequence = HelperGetMidiSequence();
    int iTempoShift = psequence->GetTempoShift() - 1;
    if(iTempoShift >= -10 || iTempoShift <= 10)
    {
		pplayer->SetTempoShift(iTempoShift);
		GetPlayerDoc()->UpdateAllViews(NULL);
    }
}

void CCDDoc::MusicTransposeMinusTone()
{
    CMidiSequence * psequence = HelperGetMidiSequence();
    int iKeyShift = psequence->GetKeyShift() - 2;
    if(iKeyShift >= -12 || iKeyShift <= 12)
    {
        psequence->SetKeyShift(iKeyShift);
		GetPlayerDoc()->UpdateAllViews(NULL);
    }
}

void CCDDoc::MusicUpdateTempoReset(CCmdUI *pCmdUI)
{
    if(GetMidiPlayer())
    {
        CMidiSequence * psequence = HelperGetMidiSequence();
        pCmdUI->Enable(psequence->GetTempoShift() != 0);
        pCmdUI->SetCheck(psequence->GetTempoShift() == 0 ? 1 : 0);
    }
    else
    {
        pCmdUI->Enable(false);
        pCmdUI->SetCheck(0);
    }
}

void CCDDoc::MusicTempoPlus()
{
	CMidiPlayer * pplayer = GetMidiPlayer();
    CMidiSequence * psequence = HelperGetMidiSequence();
    int iTempoShift = psequence->GetTempoShift() + 1;
    if(iTempoShift >= -10 || iTempoShift <= 10)
    {
		pplayer->SetTempoShift(iTempoShift);
		GetPlayerDoc()->UpdateAllViews(NULL);
    }
}

void CCDDoc::MusicUpdateTempoPlus(CCmdUI *pCmdUI)
{
    if(GetMidiPlayer())
    {
        CMidiSequence * psequence = HelperGetMidiSequence();
        int iTempoShift = psequence->GetTempoShift() + 1;
        pCmdUI->Enable(iTempoShift <= 10);
    }
    else
    {
        pCmdUI->Enable(false);
    }
}

void CCDDoc::MusicUpdateTempoMinus(CCmdUI *pCmdUI)
{
    if(GetMidiPlayer())
    {
        CMidiSequence * psequence = HelperGetMidiSequence();
        int iTempoShift = psequence->GetTempoShift() - 1;
        pCmdUI->Enable(iTempoShift >= -10);
    }
    else
    {
        pCmdUI->Enable(false);
    }

}

void CCDDoc::MusicTransposeMinus()
{
    CMidiSequence * psequence = HelperGetMidiSequence();
    int iKeyShift = psequence->GetKeyShift() - 1;
    if(iKeyShift >= -12 || iKeyShift <= 12)
    {
        psequence->SetKeyShift(iKeyShift);
		GetPlayerDoc()->UpdateAllViews(NULL);
    }

}

void CCDDoc::MusicTransposePlus()
{
    CMidiSequence * psequence = HelperGetMidiSequence();
    int iKeyShift = psequence->GetKeyShift() + 1;
    if(iKeyShift >= -12 || iKeyShift <= 12)
    {
        psequence->SetKeyShift(iKeyShift);
		GetPlayerDoc()->UpdateAllViews(NULL);
    }
}

void CCDDoc::MusicTransposeReset()
{
    CMidiSequence * psequence = HelperGetMidiSequence();
    psequence->SetKeyShift(0);
	GetPlayerDoc()->UpdateAllViews(NULL);
}

void CCDDoc::MusicTransposePlusTone()
{
    CMidiSequence * psequence = HelperGetMidiSequence();
    int iKeyShift = psequence->GetKeyShift() + 2;
    if(iKeyShift >= -12 || iKeyShift <= 12)
    {
        psequence->SetKeyShift(iKeyShift);
		GetPlayerDoc()->UpdateAllViews(NULL);
    }
}

void CCDDoc::MusicUpdateTransposeMinus(CCmdUI *pCmdUI)
{
    if(GetMidiPlayer())
    {
        CMidiSequence * psequence = HelperGetMidiSequence();
        int iKeyShift = psequence->GetKeyShift() - 1;
        pCmdUI->Enable(iKeyShift >= -12);
    }
    else
    {
        pCmdUI->Enable(false);
    }
}

void CCDDoc::MusicUpdateTransposePlus(CCmdUI *pCmdUI)
{
    if(GetMidiPlayer())
    {
        CMidiSequence * psequence = HelperGetMidiSequence();
        int iKeyShift = psequence->GetKeyShift() + 1;
        pCmdUI->Enable(iKeyShift <= 12);
    }
    else
    {
        pCmdUI->Enable(false);
    }
}

void CCDDoc::MusicUpdateTransposeReset(CCmdUI *pCmdUI)
{
    if(GetMidiPlayer())
    {
        CMidiSequence * psequence = HelperGetMidiSequence();
        pCmdUI->Enable(psequence->GetKeyShift() != 0);
        pCmdUI->SetCheck(psequence->GetKeyShift() == 0 ? 1 : 0);
    }
    else
    {
        pCmdUI->Enable(false);
    }
}

void CCDDoc::MusicUpdateTransposePlusTone(CCmdUI *pCmdUI)
{
    if(GetMidiPlayer())
    {
        CMidiSequence * psequence = HelperGetMidiSequence();
        int iKeyShift = psequence->GetKeyShift() + 1;
        pCmdUI->Enable(iKeyShift <= 12);
    }
    else
    {
        pCmdUI->Enable(false);
    }

}

void CCDDoc::MusicUpdateTransposeMinusTone(CCmdUI *pCmdUI)
{
    if(GetMidiPlayer())
    {
        CMidiSequence * psequence = HelperGetMidiSequence();
        int iKeyShift = psequence->GetKeyShift() - 2;
        pCmdUI->Enable(iKeyShift >= -12);
    }
    else
    {
        pCmdUI->Enable(false);
    }
}


DWORD CCDDoc::GetCodePage()
{
	return m_dwCodePage;
}

void CCDDoc::SetCodePage(DWORD dwCodePage)
{

	m_dwCodePage = dwCodePage;
	DBSave("LyricsCodePage", dwCodePage);
	UpdateAllViews(NULL, 1314151617);
}

bool CCDDoc::OpenMidiPlayer()
{
    try
    {
        m_pmidiplayer = (CMidiPlayer *) AfxBeginThread(
            RUNTIME_CLASS(CMidiPlayer),
            THREAD_PRIORITY_NORMAL,
            0,
            CREATE_SUSPENDED);
    }
    catch(CMemoryException *pe)
    {
        AfxMessageBox(_T("No memory to perform this operation." ));
		pe->Delete();
        return false;        
    }
        
    CMidiCentral * pmc = CMidiCentral::GetMidiCentral();
    if(VMS_FAILED(m_pmidiplayer->Initialize(m_pthreadV1, HelperGetMidiSequence(), pmc->m_uiMidiOutDevice)))
	{
		return false;
	}
    m_pmidiplayer->ResumeThread();
    m_pmidiplayer->m_evInitialized.Lock();
	return true;
}