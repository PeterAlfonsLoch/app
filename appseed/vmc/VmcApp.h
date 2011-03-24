#pragma once

#include "resource.h"


//class CXfplayerSingleDocTemplate;
class CSingleDocTemplateV003;
class CMSMultiDocTemplate;
class CWaveIn;
class CXfplayerThreadV1;
class CXfplayerThreadV2;
class CXfplayerThreadV3;
class CSplashThread;
class CXfplayerFont;
class CDBCentral;
class CImaging;
class CMenuV033;
class CKaraokeSDIFrame;
class CAlbumThread;
class CMenuBarV033;
class CMixerCentral;
class CSavings;
class CFontCentral;
class CWelcomeDialog;
class CMessageFilterMainHook;
//class CSplash;
//typedef struct IDirect3D8 *LPDIRECT3D8, *PDIRECT3D8;







int AppMsgBox
(
    HWND                    hwnd,
    UINT                    fuStyle,
    PTSTR                  pszFormat,
    ...
);


/////////////////////////////////////////////////////////////////////////////
// CVmcApp:
// See vmc.cpp for the implementation of this class
//


class CVmcApp :
   public ca77::application
{
//    friend CXfplayerSingleDocTemplate;
    friend CSingleDocTemplateV003;
    friend CMenuBarV033;
    friend CImaging;
    friend CSavings;
    friend CFontCentral;
public:
	CVmcApp();
// Attributes
//	BOOL m_bATLInited;
//	BOOL InitATL();
protected:
    CMessageFilterMainHook *        m_pmfmh;
    //int m_iEconoMode;
//	CXfplayerDoc*					m_pPlayingDocument;
//	CXfplayerDoc*					m_pActiveDocument;
	CMSMultiDocTemplate*		    m_pMainDocTemplate;
    MultipleDocumentTemplate *             m_pPlaylistDocTemplate;
    MultipleDocumentTemplate *             m_pMidiDocTemplate;
//    CXfplayerSingleDocTemplate *    m_pPlayerDocTemplate;
//	CXfplayerDoc	*               m_pPlayerDoc;
	
    CDBCentral *				    m_pdbcentral;

    CMixerCentral *                 m_pMixerCentral;

	CWaveIn	*						m_pWaveIn;
	CXfplayerThreadV1 *				m_pThreadV1;
	CXfplayerThreadV2 *				m_pThreadV2;
	CXfplayerThreadV3 *				m_pThreadV3;
//    CFont *                          m_pfontMenu;
//	CFont *                         m_pfontStandard;
	CSplashThread *					m_pSplashThread;
    CImaging *                      m_pImaging;
//    CRelationV001<UINT, UINT, UINT, UINT> m_relMenuV033ImageMap;
//    CImageList    *                 m_pilMenuV033;

    CKaraokeSDIFrame *              m_pKarWnd;
    //CAlbumFrameWnd *                  m_pAlbumFrameWnd;
    //CSingleDocTemplate *            m_pAlbumDocTemplate;
    //CAlbumThread *                  m_pAlbumThread;
//	LPDIRECTDRAW					m_lpDirectDraw;
//    CComPtr<IDirect3D8>             m_spDirectDraw;
    CSavings *                      m_psavings;
    CFontCentral *                  m_pfontcentral;
    CWelcomeDialog *                m_pwelcomedlg;
public:
    
    CEvent                          m_evInitialized;
protected:
    afx_msg void OnUserMessage(WPARAM wParam, LPARAM lParam );
	CFontCentral * GetFontCentral();
	VMSRESULT OpenToolsAlbum();
	VMSRESULT CreateAlbumThread();
    CImaging * GetImaging();
	int       GetEconoMode_();
//    CXfplayerSingleDocTemplate * GetPlayerDocTemplate();
public:
	//bool InitializeDataCentral();
	void SetWelcomeDialog(CWelcomeDialog*pdlg);
	CWelcomeDialog* GetWelcomeDialog();
	void RegisterShellExtension();
	CSavings * GetSavings();

   
//	VMSRESULT ReserveSong(LPCTSTR lpcszPath, bool bDoPlay);
//	VMSRESULT ReserveSongs(LPINT lpiaSongs, int iSongCount);
//    VMSRESULT ReserveSong_(int iCode);
	string GetAppFolder();
	VMSRESULT SetAlbumThread(CAlbumThread * pAlbumThread);

	virtual bool MessageWindowListener(
	UINT message,
	WPARAM wparam,
	LPARAM lparam);

   static CVmcApp * app(::ca::application * papp) { return dynamic_cast < CVmcApp * > (papp); }

	//CFont * GetStandartFont();
	MultipleDocumentTemplate * GetMidiDocTemplate();
    CMessageFilterMainHook * GetMessageFilterMainHook();
	//CSingleDocTemplate * GetAlbumDocTemplate();
    CAlbumThread * GetAlbumThread();
	VMSRESULT ViewToolsAlbum();
	CKaraokeSDIFrame * GetKarWnd();
	//CImageList * MenuV033GetImageList();
	//VMSRESULT MenuV033GetImageMap(CRelationV001<UINT, UINT, UINT, UINT> ** pprel);
	//VMSRESULT MenuV033CreateImageMap();
	//void SetEconoMode(int iNewEconoMode);
	void OnChangeEconoMode();

	
	MultipleDocumentTemplate * GetPlaylistDocTemplate();
//	void SetPlayerDocument(CXfplayerDoc * lpDoc);
	
    CMenuV033  * m_pmenuPlayerShared;
	HACCEL m_hPlayerAccelTable;
	//CXfplayerDoc * GetPlayerDocument();
//    inline LPDIRECT3D8 GetDirectDraw()
//    {
//        return m_spDirectDraw;
//    }
//	bool InitDirectDraw();
	void RegisterShellFileTypes( BOOL bCompat = FALSE );
    CDBCentral * GetDBCentral();
    inline CMixerCentral * GetMixerCentral();
	CSplashThread * GetSplashThread();
	CCriticalSection				m_csLyricViewFonts;
	CCriticalSection				m_csTitleFonts;
	CCriticalSection				m_csSubTitleFonts;
	CEvent							m_evWait;
//	CSplash *						m_pSplash;
	//PROCESS_INFORMATION				m_piImageLoader;
//	LPDIRECTDRAW GetDirectDraw();
	inline CXfplayerThreadV1 * GetThreadV1();
	inline CXfplayerThreadV2 * GetThreadV2();
	inline CXfplayerThreadV3 * GetThreadV3();
	CWaveIn * GetWaveIn();
//	CXfplayerDoc * GetOnlyDocument();
	
	void Exit();
	string m_XFToolTipV1ClassName;
	string m_XFViewClassName;
    string m_strMessageWndClassName;
	void LoadAppSettings();

	UINT			m_uiMidiOutDevice;
    UINT            m_uiWaveInDevice;
	//CFont			m_font;
//	CXfplayerDoc	*GetPlayingDocument()
//	{
//		return m_pPlayingDocument;
//	};
//	void SetPlayingDocument(CXfplayerDoc * playingDocument)
//	{
//		m_pPlayingDocument = playingDocument;
//	};
	//CSongsDirectoriesSet *		m_SongsDirsSet;
	//CDataSource					m_DataSource;
//	HANDLE						m_hHeap;
	int							m_iBackgroundUpdateMillis;

// Operations
//	CXfplayerDoc * GetActiveDocument()
//	{
//		return m_pActiveDocument;
//	};

//	void SetActiveDocument(CXfplayerDoc * pDoc)
//	{
//		m_pActiveDocument = pDoc;
//	};

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVmsApp)
	public:
	virtual bool InitInstance();
	virtual int ExitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, CAFX_CMDHANDLERINFO* pHandlerInfo);
	virtual Document* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CVmsApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	afx_msg void OnFileNew();
	afx_msg void OnHelp();
	afx_msg void OnHelpFinder();
	afx_msg void OnFileNewFromplayerview();
	afx_msg void OnUpdateFileNewFromplayerview(CCmdUI* pCmdUI);
	afx_msg void OnToolsAlbum();
	afx_msg void OnUpdateToolsAlbum(CCmdUI* pCmdUI);
	afx_msg void OnToolsOptions();
	afx_msg void OnUpdateToolsOptions(CCmdUI* pCmdUI);
   DECL_GEN_SIGNAL(_001Alloc)
};

CXfplayerThreadV1 * CVmcApp::GetThreadV1()
{
	return m_pThreadV1;
}
CXfplayerThreadV2 * CVmcApp::GetThreadV2()
{
	return m_pThreadV2;
}
CXfplayerThreadV3 * CVmcApp::GetThreadV3()
{
	return m_pThreadV3;
}


