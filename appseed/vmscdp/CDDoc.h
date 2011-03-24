// xfplayerDoc.h : interface of the CCDDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDDOC_H__55F981F4_CA0D_4DC6_9ACB_A3D6BB12B752__INCLUDED_)
#define AFX_CDDOC_H__55F981F4_CA0D_4DC6_9ACB_A3D6BB12B752__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVmsGuiSingleDocTemplate;

#include "MidiPlayer.h"
#include "Midi.h"
#include "templ.h"
#include "XFInfoHeaders.h"
#include "XF.h"
#include "Keeper.h"
#include "VMSException.h"	// Added by ClassView
#include "MidiDocHelper.h"
#include "DBInterface.h"
#include "PointerListener.h"
#include "VmsGuiDocInterface.h"
#include "PlayerInterface.h"

class CXfplayerView;



class CXfplayerThreadV1;
class CXfplayerViewPlaylist;
class CXfplayerScoring;
class CMidiSequence;
class CXfplayerServerItem;
class CPlaylistDoc;
class CAudioSpectrumDoc;
class CLevelMeterDoc;
class CTransparentFrameWndV8;
class CLevelMeterView;
class CAudioSpectrumView;
class CPlayerDoc;
class CPlayerControlSetV19View;
class CPlayerControlSetV19Frame;
class CKaraokeUtil;
class CMidiPlayer;
typedef struct tag_midiDoneData MIDIDONEDATA, * LPMIDIDONEDATA;


class CCDDoc :
    public COleServerDoc,
    public CMidiDocHelper,
	public CDBInterface,
	public CVmsGuiDocInterface,
	public CPointerListener<CPlaylistDoc>,
	public CPointerListener<CAudioSpectrumDoc>,
	public CPointerListener<CLevelMeterDoc>,
	public CPointerListener<CPlayerDoc>,
	public CPlayerInterface
{
protected: // create from serialization only
	CCDDoc();
	DECLARE_DYNCREATE(CCDDoc)


    CXfplayerServerItem *  GetEmbeddedItem()
		{ return (CXfplayerServerItem*)COleServerDoc::GetEmbeddedItem(); }
	
    
	bool				m_bSettingNextSong;
    bool                m_bWaitingToPlay;
    int                 m_msPlayTimeOut;
    double              m_dProgressRate;

// Attributes
public:
    CCriticalSection    m_csSongData;
    CCriticalSection    m_csMidi;
	CEvent				m_evMMDone;
	double				m_CurrentTokenPlayedPercentage;
	//C2DStringPtrArray *	m_p2DTokens;
    bool				m_bPlay;
    MIDIFILEHDR         m_mfh;

	//C2DDWordArray 		m_2DTokensMillis;
	//CDWordArray			m_DisplayOffsetEvents;
	//CDWordArray			m_PrePlayOffsetEvents;
	
protected:
    bool                m_bOpening;
	CDWordArray         m_dwaSongsCodes;
    bool                m_bClosing;

	DWORD               m_dwCodePage;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCDDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	virtual void DeleteContents();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	protected:
    virtual COleServerItem* OnGetEmbeddedItem();
	virtual void OnDeactivate();
	//}}AFX_VIRTUAL

// Implementation
public:
	bool IsAudioSpectrumOpened();
	CLevelMeterDoc * GetLevelMeterDoc();
	CAudioSpectrumDoc * GetAudioSpectrumDoc();
	CLevelMeterDoc * OpenLevelMeterDoc(bool bMakeVisible);
	CAudioSpectrumDoc * OpenAudioSpectrumDoc(bool bMakeVisible);
	
protected:
	virtual COleIPFrameWnd* CreateInPlaceFrame(CWnd* pParentWnd);
	CSingleDocTemplate * GetLevelMeterDocTemplate();
	CSingleDocTemplate * GetAudioSpectrumDocTemplate();
public:
	bool OpenMidiPlayer();
	void SetCodePage(DWORD dwCodePage);
	DWORD GetCodePage();
	void OnMidiPlayerNotifyEvent(CMidiPlayer::CNotifyEventData * pdata);
	void MusicUpdateTransposeMinusTone(CCmdUI * pCmdUI);
	void MusicUpdateTransposePlusTone(CCmdUI * pCmdUI);
	void MusicUpdateTransposeReset(CCmdUI * pCmdUI);
	void MusicUpdateTransposePlus(CCmdUI * pCmdUI);
	void MusicUpdateTransposeMinus(CCmdUI * pCmdUI);
	void MusicTransposePlusTone();
	void MusicTransposeReset();
	void MusicTransposePlus();
	void MusicTransposeMinus();
	void MusicUpdateTempoMinus(CCmdUI * pCmdUI);
	void MusicUpdateTempoPlus(CCmdUI * pCmdUI);
	void MusicTempoPlus();
	void MusicUpdateTempoReset(CCmdUI * pCmdUI);
	void MusicTransposeMinusTone();
	void MusicTempoMinus();
	void MusicTempoReset();
	bool IsPlayerControlSetV19ViewOpened();
	bool IsPlayerDocOpened();
	CPlayerControlSetV19View * GetPlayerControlSetV19View();
	CPlayerControlSetV19Frame * GetPlayerControlSetV19Frame();
	void OnPointerClear(CPlayerDoc * pdoc);
	CPlayerDoc * OpenPlayerDoc(bool bMakeVisible);
	CPlayerDoc * GetPlayerDoc();
	void CloseAllLevelMeterDocuments();
	void CloseAllAudioSpectrumDocuments();
	virtual void OnPointerClear(CLevelMeterDoc * pdoc);
	virtual void OnPointerClear(CAudioSpectrumDoc * pdoc);
	CTransparentFrameWndV8 * GetLevelMeterFrame();
	CTransparentFrameWndV8 * GetAudioSpectrumFrame();
	CLevelMeterView * GetLevelMeterView();
	CAudioSpectrumView * GetAudioSpectrumView();
	bool IsLevelMeterOpened();

	void OnPointerClear(CPlaylistDoc * pdoc);
	CPlaylistDoc * DetachPlaylistDoc();
	CPlaylistDoc * GetPlaylistDoc();
	bool Attach(CPlaylistDoc * pplaylistdoc);
	bool IsPaused();
	bool IsScoringEnabled();
	VMSRESULT StartScoring(bool bStart);
	VMSRESULT EnableScoring(bool bEnable);
	bool IsClosing();
//	bool IsSaving();
    BOOL DoSave(LPCTSTR lpszPathName, BOOL bReplace);
	void OnUpdateProgress(CView * pView);
	void OnUpdateProgress(double dRate, CView * pView);
	void SetProgressRate(double dRate, CView * pView = NULL);
	double GetProgressRate();
	void UpdateProgress(CView * pView = NULL);
	int GetNextSong();
	//CXfplayerViewPlaylist * GetPlaylistView();
	bool IsOpening();
	bool GetPauseEnable();
	bool GetPlayEnable();
	void SetWaitingToPlay(bool bWaitingToPlay);
	bool IsWaitingToPlay();
	DWORD GetPlayTimeOut();

	void OnMmsgDone(CMidiSequence *pSeq, LPMIDIDONEDATA lpmdd);

	UINT GetMidiSequenceState();
//	inline CMidiSequence * GetMidiSequence();
	CArray
		<CXFInfoHeaderLS,
		CXFInfoHeaderLS &> * GetInfoHeadersLS();
	//CXFInfoHeader * GetInfoHeader();
	bool IsSettingNextSong();
	CXfplayerScoring * GetScoring();
	//void SetScoreRate(double dScoreRate);
	double GetScoreRate();
	CXfplayerView * GetLyricView();
	BOOL IsPlaying();
	
	void NextSong(bool bDoPlay,  bool bMakeVisible);
	void ClearTokens();
	//void SetApproximatePosition(double rate);
	void Pause();
	void Stop();
	void OnPositionCB();
	void PrepareLyrics();
	
	void Play(bool bMakeVisible);
	virtual ~CCDDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	virtual CDocObjectServer* GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite);

// Generated message map functions
protected:
	//{{AFX_MSG(CCDDoc)
	afx_msg void OnUpdatePlay(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePause(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStop(CCmdUI* pCmdUI);
	afx_msg void OnViewLyrics();
	afx_msg void OnUpdateViewLyrics(CCmdUI* pCmdUI);
	afx_msg void OnViewMidievents();
	afx_msg void OnUpdateViewMidievents(CCmdUI* pCmdUI);
	afx_msg void OnFileProperties();
	afx_msg void OnUpdateFileProperties(CCmdUI* pCmdUI);
	afx_msg void OnScoringEnable();
	afx_msg void OnUpdateScoringEnable(CCmdUI* pCmdUI);
	//}}AFX_MSG
    afx_msg LRESULT OnXfplayerDocMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
	DECLARE_OLECMD_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CCDDoc)
	afx_msg BOOL OpenDocumentFile(const VARIANT FAR& varwszFilePath);
	afx_msg BOOL OpenFile(LPCTSTR bstrFilePath, BOOL bMakeVisible);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


//inline CMidiSequence * CCDDoc::GetMidiSequence()
//{
//	return m_pSequence;
//}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDDOC_H__55F981F4_CA0D_4DC6_9ACB_A3D6BB12B752__INCLUDED_)
