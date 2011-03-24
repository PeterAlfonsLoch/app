// vmpLight.h : main header file for the VMPLIGHT application
//

#if !defined(AFX_VMPLIGHT_H__C3015FEE_0261_4679_AED8_87CA142EA6B8__INCLUDED_)
#define AFX_VMPLIGHT_H__C3015FEE_0261_4679_AED8_87CA142EA6B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

// DDEML - Dynamic Data Exchange Management Library
#include <ddeml.h>


// {873779CF-F79E-4975-B87D-76B3CE8A9F48}
/*DEFINE_GUID(<<name>>, 
0x873779cf, 0xf79e, 0x4975, 0xb8, 0x7d, 0x76, 0xb3, 0xce, 0x8a, 0x9f, 0x48);

// {873779CF-F79E-4975-B87D-76B3CE8A9F48}
static const GUID <<name>> = 
{ 0x873779cf, 0xf79e, 0x4975, { 0xb8, 0x7d, 0x76, 0xb3, 0xce, 0x8a, 0x9f, 0x48 } };*/

#define VMPLIGHT_GUID "{873779CF-F79E-4975-B87D-76B3CE8A9F48}"
#define VM_SIMPLE_MSG "VM_SIMPLE"##VMPLIGHT_GUID
#define DECLARE_USER_MESSAGE(name) \
     static const UINT name;
#define IMPLEMENT_USER_MESSAGE(name) \
     static const UINT name = ::RegisterWindowMessage(name##_MSG);

IMPLEMENT_USER_MESSAGE(VM_SIMPLE)

#include "resource.h"       // main symbols



class OptionsDialog;
class MusicalPlayerLightPlaylistCallback;
class CUserInterfaceImageManager;

class FileManagerTemplate;
class VmpLightDB;
class MusicalPlayerLightDB;
class Ex1FormInterface;


namespace vmplite
{
   class FileAssociation;
   class DocumentManager;
}

class WStrArray;

class EncodingMapItem
{
public:
   DWORD    m_dwCodePage;
   UINT     m_uiBaseCommand;
   int      m_iIndex;
   UINT     m_uiString;
};

class RecentFileList;

/////////////////////////////////////////////////////////////////////////////
// MusicalPlayerLightApp:
// See vmpLight.cpp for the implementation of this class
//

class MusicalPlayerLightApp :
   public gen::App,
   public Ex1App,
   public igui::AppInterface,
   public guibase::AppInterface,
   public simpledb::AppInterface,
   public mus::CMidiCentralContainer,
   public PlaylistCentralContainer,
   public musctrl::PlayerDocContainer,
   public musctrl::MusicalPlayerCentralContainer,
   public FileManagerCallbackInterface,
   public aud::WaveCentralContainer,
   public filemanager::Application
{
protected:
   OptionsDialog *               m_lpoptionsdialog;
   vmplite::FileAssociation * m_pfileassociation;
   CUserInterfaceImageManager *  m_pimagemanager;
   VmpLightDB *                  m_plightdb;
   BaseArray < EncodingMapItem, EncodingMapItem &>
                                 m_encodinga;

   RecentFileList *	            m_precentfilelist;

   MusicalPlayerLightDB *        m_pdb;
//   CMap < UINT, UINT, DWORD, DWORD > m_mapIdToCodePage;
   //CMap < UINT, UINT, DWORD, DWORD > m_mapIdToCodePage;
public:
   void AddToRecentFileList(LPCTSTR lpszPathName);

	void AddCodePage(DWORD dwCodePage, UINT uiBaseCommand, UINT uiString);
   int GetCodePageCommandCount(UINT uiBaseCommand);
   bool GetCodePageCommandData(EncodingMapItem & item, UINT uiCommand);
   DWORD CommandToCodePage(UINT uiId);

	bool SetLanguageResourcePath(LPCTSTR lpcsz);
   void OnUpdatePopupMenu(CCmdUI *pcmdui);
	void GetAvailableLanguages(AStrArray & wstra);
	void ProcessCommandLine(LPCWSTR lpsz);
	virtual void * _001OpenDocumentFile(LPCSTR lpcsz);
	virtual void _001OnFileNew();
	void LoadStdProfileSettings();
	bool InitializeLocalDataCentral();
	CString GetVersion();

   VmpLightDB * GetLightDB();

   HSZ m_hszAppName;
   HSZ m_hszSystemTopic;

   static HDDEDATA CALLBACK DdeCallback(
      UINT uType,
      UINT uFmt,
      HCONV hconv,
      HDDEDATA hsz1,
      HDDEDATA hsz2,
      HDDEDATA hdata,
      HDDEDATA dwData1,
      HDDEDATA dwData2);

   DocTemplate *                 m_pdoctemplateAlbum;
   DWORD                         m_dwDde;

   AStrArray                     m_straLanguagePath;
   CString                       m_strLanguagePath;
	
   virtual void OnFileManagerOpenFile(
      FileManagerDDX & ddx,
      FileManagerItemArray & itema);
	
   virtual void OnFileManagerOpenFolder(
      FileManagerDDX & ddx,
      FileManagerItem & item);

   virtual bool GetFileManagerItemCallback(
      FileManagerDDX & ddx, 
      UINT iId, 
      FileManagerItemArray & itema);

   virtual void OnFileManagerItemUpdate(
      FileManagerDDX & ddx,
      CCmdUI * pcmdui,
      FileManagerItemArray & item);

   virtual void OnFileManagerItemCommand(
      FileManagerDDX & ddx,
      UINT ui,
      FileManagerItemArray & item);

   virtual void OnFileManagerInitializeFormPreData(
      FileManagerDDX & ddx, 
      UINT uiId, 
      Ex1FormInterface * pform);


   int DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt);

	PlaylistCallbackInterface * GetNewPlaylistCallback();
	CUserInterfaceImageManager & GetImageManager();
	void AddDocumentFile(LPCTSTR lpszFileName);
   virtual void OnEvent(_vmsdb::EDBEvent event, LPARAM lparam);
   void RegisterShellFileTypes(BOOL bCompat);
   BOOL _001ProcessShellCommand(gen::CommandLineInfo& rCmdInfo);
	bool InitATL();
   vmplite::DocumentManager * m_pdocmanager;
   bool m_bATLInited;
   int m_iBackgroundUpdateMillis;
	MusicalPlayerLightApp();
	~MusicalPlayerLightApp();
   virtual Ex1FactoryImpl * Ex1AppGetFactoryImpl();
   void SetLanguage(enum gen::App::ELanguage);
   enum gen::App::ELanguage GetLanguage();
   enum gen::App::ELanguage GetDefaultLanguage();
   bool MessageWindowListener(unsigned int,unsigned int,long);
   DECL_GEN_SIGNAL(VmsDataOnAfterChange)
// Overrides
	virtual Document* _vmsguibaseOpenDocumentFile(LPCTSTR lpszFileName);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MusicalPlayerLightApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnDDECommand(LPTSTR lpszCommand);
   virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(MusicalPlayerLightApp)
	afx_msg void OnAppAbout();
	afx_msg void OnToolsOptions();
	afx_msg void OnUpdateToolsOptions(CCmdUI* pCmdUI);
	afx_msg void OnFileOpen();
   afx_msg void OnFileOpenEx();
	afx_msg void OnViewPlaylist();
	afx_msg void OnUpdateViewPlaylist(CCmdUI* pCmdUI);
	afx_msg void OnFileNew();
	afx_msg void OnViewAlbum();
	afx_msg void OnUpdateViewAlbum(CCmdUI* pCmdUI);
	afx_msg void OnFileAdd();
	afx_msg void OnLanguageChange(UINT uiId);
	afx_msg void OnUpdateLanguageChange(CCmdUI* pCmdUI);
   afx_msg void OnUpdateViewEncoding(CCmdUI* pCmdUI);

   //}}AFX_MSG
   void InitializeResourceId();
	
   CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
   afx_msg BOOL OnOpenRecentFile(UINT nID);
   afx_msg void OnUpdateRecentFileMenu(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

inline VmpLightDB * MusicalPlayerLightApp::GetLightDB()
{
   return m_plightdb;
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VMPLIGHT_H__C3015FEE_0261_4679_AED8_87CA142EA6B8__INCLUDED_)
