// xfplayer.h : main header file for the XFPLAYER application
//

#if !defined(AFX_XFPLAYER_H__425B3AF8_87E8_496E_A2FB_F65440DED14C__INCLUDED_)
#define AFX_XFPLAYER_H__425B3AF8_87E8_496E_A2FB_F65440DED14C__INCLUDED_

#include "VMSException.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

//#include "resource.h"       // main symbols
//#include "DummyCS.h"

//#include "imagedirectory.h"
//#include "imagefile.h"
//#include "songdirectory.h"

//#include "longs.h"
//#include "Xfplayer_i.h"

#include "RelationV001.h"
#include "BaseMapPtrToPtr.h"
#include "VmsGuiApp.h"
#include "../vms/Vms.h"	// Added by ClassView
#include "VmspOleTemplateServer.h"	// Added by ClassView

#include "MessageFilterMainHook.h"

#define ATTENTION ASSERT(FALSE);


/////////////////////////////////////////////////////////////////////////////
// CVcdpApp:
// See xfplayer.cpp for the implementation of this class
//

class CXfplayerDoc;
class CVmsGuiMultiDocTemplate;
class CVmsGuiSingleDocTemplate;
class CXfplayerSingleDocTemplate;
class CSingleDocTemplateV003;
class CMSMultiDocTemplate;
class CWaveIn;
class CXfplayerThreadV1;
class CXfplayerThreadV2;
class CXfplayerThreadV3;
class CSplashThread;
class CVmsGdiFont;
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
class CPlaylistDoc;
class CVmsTextDoc;
class CDDEFrameWnd;


int AppMsgBox
(
    HWND                    hwnd,
    UINT                    fuStyle,
    PTSTR                  pszFormat,
    ...
);


#include "DataCentral.h"
#include "WaveCentral.h"

class CVcdpApp :
	public CVmsGuiApp,
	public CWaveCentral
{
    friend CXfplayerSingleDocTemplate;
    friend CSingleDocTemplateV003;
    friend CMenuBarV033;
    friend CImaging;
    friend CSavings;
    friend CFontCentral;
public:
	CVcdpApp();
// Attributes
//	BOOL m_bATLInited;
//	BOOL InitATL();
//	enum EVmpConfiguration
//	{
//		CfgKaraokeEncoding = CfgVmsGuiEnd,
//	};

	
	UINT				m_nDDECmdShow;
	BOOL ProcessShellCommand(CCommandLineInfo& rCmdInfo);
    virtual LRESULT GetPaintMsgProc(int nCode, WPARAM wParam, LPARAM lParam);
protected:
    CMessageFilterMainHook *        m_pmfmh;
    //int m_iEconoMode;
//	CXfplayerDoc*					m_pPlayingDocument;
//	CXfplayerDoc*					m_pActiveDocument;
	CMSMultiDocTemplate*		    m_pMainDocTemplate;
    CVmsGuiMultiDocTemplate *             m_pPlaylistDocTemplate;
    CVmsGuiMultiDocTemplate *             m_pMidiDocTemplate;
	CXfplayerDoc *					m_pxfplayerdoc;
    CSingleDocTemplate *			m_pdoctemplateCD;

	CDDEFrameWnd *					m_pddeframewnd;
	
	//CXfplayerSingleDocTemplate *    m_pplayerdoctemplateOLE;
//	CXfplayerDoc	*               m_pPlayerDoc;
	
    //CDBCentral *				    m_pdbcentral;

    CMixerCentral *                 m_pMixerCentral;

//	CWaveIn	*						m_pWaveIn;
	CXfplayerThreadV1 *				m_pthreadV1;
	CXfplayerThreadV2 *				m_pthreadV2;
	CXfplayerThreadV3 *				m_pthreadV3;
//    CFont *                          m_pfontMenu;
//	CFont *                         m_pfontStandard;
	//CSplashThread *					m_pSplashThread;
    CImaging *                      m_pImaging;
//    CRelationV001<UINT, UINT, UINT, UINT> m_relMenuV033ImageMap;
//    CImageList    *                 m_pilMenuV033;

    CKaraokeSDIFrame *              m_pKarWnd;
    //CAlbumFrameWnd *                  m_pAlbumFrameWnd;
    CVmsGuiSingleDocTemplate *            m_pAlbumDocTemplate;
public:
    CVmsGuiSingleDocTemplate *      m_pdoctemplateFileAssociations;
protected:
    CAlbumThread *                  m_pAlbumThread;
	CMultiDocTemplate *				m_pvmstextdoctemplate;
//	LPDIRECTDRAW					m_lpDirectDraw;
//    CComPtr<IDirect3D8>             m_spDirectDraw;
    CSavings *                      m_psavings;
    CFontCentral *                  m_pfontcentral;
    CWelcomeDialog *                m_pwelcomedlg;
	CPlaylistDoc *					m_pplaylistdoc;
	
	HMODULE							m_hmoduleResource;

	CWnd *							m_pwndMessageBoxParent;
public:
    
    CEvent                          m_evInitialized;
protected:
	virtual void VmsDataOnAfterChange(int iConfigurationId, int iLine, int iColumn);
	CFontCentral * GetFontCentral();
	VMSRESULT OpenToolsAlbum();
	VMSRESULT CreateAlbumThread();
    CImaging * GetImaging();
	int       GetEconoMode_();
    virtual bool MessageWindowListener(
		UINT message,
		WPARAM wparam,
		LPARAM lparam);
public:
	DWORD GetKaraokeEncoding();
	void OnAfterKaraokeEncodingChange();
	void SetKaraokeEnconding(DWORD dwCodePage);
	void OnAfterLanguageChange(ELanguage elanguage);
	ELanguage GetDefaultLanguage();
	void VerifyBrowsers();
	int GetDocumentCount();
	bool BeginVSeriesThreads();
	void GetDefaultSongFolderPath(CString &strPath);
	CKaraokeSDIFrame * GetKaraokeSDIFrame();
	void SetXfplayerDoc(CXfplayerDoc * pdoc);
	CXfplayerDoc * GetXfplayerDoc();
	void OnCloseDefaultPlaylist();
	CVmsTextDoc * OpenTextFile(LPCTSTR lpcsz);
	void GetDefaultPlaylistPathName(CString & str);
	CPlaylistDoc * OpenDefaultPlaylist();
	CPlaylistDoc * GetDefaultPlaylist();
	
	bool RestoreEnhMetaFiles();
	
	//bool InitializeDataCentral(CCommandLineInfo & cmdinfo);
	
	CString GetLanguageDllPath(ELanguage elanguage);
//	bool SetLanguage(ELanguage elanguage);
	CString GetModuleFolder();
	void UpdateMRU(BOOL bEnable, int nCount);
    CXfplayerSingleDocTemplate * GetPlayerDocTemplate();
	void SetWelcomeDialog(CWelcomeDialog*pdlg);
	CWelcomeDialog* GetWelcomeDialog();
	
	void RegisterShellExtension(bool bRegister = true);

	CSavings * GetSavings();
//	VMSRESULT ReserveSong(LPCTSTR lpcszPath, bool bDoPlay);
//	VMSRESULT ReserveSongs(LPINT lpiaSongs, int iSongCount);
//    VMSRESULT ReserveSong_(int iCode);
	CString GetAppFolder();
	VMSRESULT SetAlbumThread(CAlbumThread * pAlbumThread);
	
	//CFont * GetStandartFont();
	CMultiDocTemplate * GetMidiDocTemplate();
    CMessageFilterMainHook * GetMessageFilterMainHook();
	//CSingleDocTemplate * GetAlbumDocTemplate();
    CAlbumThread * GetAlbumThread();
	VMSRESULT ViewToolsAlbum();
	CKaraokeSDIFrame * GetKarWnd();
	//void SetEconoMode(int iNewEconoMode);
	void OnChangeEconoMode();

	
	CMultiDocTemplate * GetPlaylistDocTemplate();
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
	CSplashThread * GetSplashThread_();
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
	//CWaveIn * GetWaveIn();
//	CXfplayerDoc * GetOnlyDocument();
	
	void Exit();
	CString m_XFToolTipV1ClassName;
	CString m_XFViewClassName;
    CString m_strMessageWndClassName;
	void LoadAppSettings();

	//UINT			m_uiMidiOutDevice;
//    UINT            m_uiWaveInDevice;
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
    UINT                        m_nMaxMRU;

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
	//{{AFX_VIRTUAL(CVcdpApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	virtual void AddToRecentFileList(LPCTSTR lpszPathName);
	virtual int DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt);
	virtual BOOL OnDDECommand(LPTSTR lpszCommand);
	//}}AFX_VIRTUAL

// Implementation
	CVmspOleTemplateServer m_serverMid;
	CVmspOleTemplateServer m_serverKar;
	CVmspOleTemplateServer m_serverSt3;
		// Server object for document creation
	//{{AFX_MSG(CVcdpApp)
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
	afx_msg void OnUpdateRecentFileMenu(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLanguageChangeMenu(CCmdUI* pCmdUI);
	afx_msg void OnLanguageEnus();
	afx_msg void OnUpdateLanguageEnus(CCmdUI* pCmdUI);
	afx_msg void OnLanguagePtbr();
	afx_msg void OnUpdateLanguagePtbr(CCmdUI* pCmdUI);
	afx_msg void OnLanguageDe();
	afx_msg void OnUpdateLanguageDe(CCmdUI* pCmdUI);
	afx_msg void OnLanguageJp();
	afx_msg void OnUpdateLanguageJp(CCmdUI* pCmdUI);
	afx_msg void OnContextHelp();
	afx_msg void OnPlayer();
	afx_msg void OnToolsOptionsFileAssociations();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
    afx_msg void OnUserMessage(WPARAM wParam, LPARAM lParam );
    afx_msg void OnAppMessage(WPARAM wParam, LPARAM lParam );
private:
	BOOL m_bATLInited;
private:
	BOOL InitATL();
};

//inline CDBCentral * CVcdpApp::GetDBCentral()
//{
//	return m_pDBCentral;
//}

inline CMixerCentral * CVcdpApp::GetMixerCentral()
{
	return m_pMixerCentral;
}

/////////////////////////////////////////////////////////////////////////////
int CALLBACK BrowseCallbackProc(
    HWND hwnd, 
    UINT uMsg, 
    LPARAM lParam, 
    LPARAM lpData
    ); 

void AFX_EXT_CLASS AddStringLines(LPCTSTR lpStr, CStringArray *pArray);

//void BubbleSort(LPINT lpInt, int size);



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XFPLAYER_H__425B3AF8_87E8_496E_A2FB_F65440DED14C__INCLUDED_)
#include "Vmsp_i.h"
