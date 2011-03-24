#pragma once

// DDEML - Dynamic Data Exchange Management Library
#include <ddeml.h>

#define VMPLIGHT_GUID "{873779CF-F79E-4975-B87D-76B3CE8A9F48}"
#define VM_SIMPLE_MSG "VM_SIMPLE"##VMPLIGHT_GUID
#define DECLARE_USER_MESSAGE(name) \
     static const UINT name;
#define IMPLEMENT_USER_MESSAGE(name) \
     static const UINT name = ::RegisterWindowMessage(name##_MSG);

IMPLEMENT_USER_MESSAGE(VM_SIMPLE)

class OptionsDialog;
class playlist_callback;
class ::userbase::image_manager;

class FileManagerTemplate;
class MusicalPlayerLightDB;
class ::user::form;

namespace vmplite
{
   class file_association;
   class document_manager;
}

class stringa;

class EncodingMapItem
{
public:
   DWORD    m_dwCodePage;
   id       m_id;
   UINT     m_uiString;
};

class RecentFileList;

namespace mplite
{

   class database;
   class playlist_central_callback;

   class CLASS_DECL_CA2_CUBE application :
      virtual public ::eluce::application
   {
   public:
      OptionsDialog *                  m_lpoptionsdialog;
      vmplite::file_association *       m_pfileassociation;
      ::userbase::image_manager *     m_pimagemanager;
      mplite::database *               m_pdatabase;
      base_array < EncodingMapItem, EncodingMapItem &>
                                       m_encodinga;

      RecentFileList *                  m_precentfilelist;
      playlist_central_callback *      m_pplaylistcentralcallback;

      MusicalPlayerLightDB *           m_pdb;
      bool                             m_bInline;

      HSZ                              m_hszAppName;
      HSZ                              m_hszSystemTopic;

      ::userbase::document_template *           m_pdoctemplateAlbum;
      DWORD                            m_dwDde;

      stringa                        m_straLanguagePath;
      string                           m_strLanguagePath;


      virtual void construct();

      void AddToRecentFileList(const char * lpszPathName);

      void AddCodePage(DWORD dwCodePage, id lpcszCommand, id uiString);
      int GetCodePageCommandCount();
      bool GetCodePageCommandData(EncodingMapItem & item, int iIndex);
      DWORD CommandToCodePage(class id id);

      bool SetLanguageResourcePath(const char * lpcsz);
      void OnUpdatePopupMenu(cmd_ui *pcmdui);
      void GetAvailableLanguages(stringa & stra);
      void ProcessCommandLine(const wchar_t * lpsz);
      virtual ::document * _001OpenDocumentFile(var varFile);
      void LoadStdProfileSettings(UINT nMaxMRU = 4);
      bool InitializeLocalDataCentral();

      void CreateTemplates();

      

      mplite::database & mplitedb();


      static HDDEDATA CALLBACK DdeCallback(
         UINT uType,
         UINT uFmt,
         HCONV hconv,
         HDDEDATA hsz1,
         HDDEDATA hsz2,
         HDDEDATA hdata,
         HDDEDATA dwData1,
         HDDEDATA dwData2);

      
      //virtual void request(var & varFile, var & varQuery);
      virtual void on_request(var & varFile, var & varQuery);
      
      virtual void OnFileManagerOpenFolder(
         ::filemanager::data * pdata,
         ::fs::item & item);

      virtual bool GetFileManagerItemCallback(
         ::filemanager::data * pdata, 
         id id, 
         ::fs::item_array & itema);

      virtual void OnFileManagerItemUpdate(
         ::filemanager::data * pdata,
         cmd_ui * pcmdui,
         ::fs::item_array & item);

      virtual void OnFileManagerItemCommand(
         ::filemanager::data * pdata,
         id user,
         ::fs::item_array & item);

      virtual void OnFileManagerInitializeFormPreData(
         ::filemanager::data * pdata, 
         id uiId, 
         ::user::form * pform);

      PlaylistCallbackInterface * GetNewPlaylistCallback();
      ::userbase::image_manager & GetImageManager();
      void AddDocumentFile(const char * lpszFileName);
   //   virtual void OnEvent(_vmsdb::EDBEvent event, LPARAM lparam);
      void RegisterShellFileTypes(BOOL bCompat);
      virtual void _001CloseAllDocuments(bool bEndSession);
      //document_manager * m_pdocmanager;
      bool m_bATLInited;
      int m_iBackgroundUpdateMillis;
      application();
      virtual ~application();
      bool MessageWindowListener(unsigned int,unsigned int,long);
      DECL_GEN_SIGNAL(data_on_after_change)
      virtual ::userbase::document* _vmsguserbaseOpenDocumentFile(const char * lpszFileName);

      virtual bool UpdateRegistry();
      virtual bool CreateDocumentTemplates();

   public:
      virtual bool initialize_instance();
      virtual int exit_instance();
      virtual BOOL OnDDECommand(LPTSTR lpszCommand);
      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 

      afx_msg void OnAppAbout();
      afx_msg void OnToolsOptions();
      afx_msg void OnUpdateToolsOptions(cmd_ui * pcmdui);
      afx_msg void on_file_open();
      afx_msg void OnFileOpenEx();
      afx_msg void OnViewPlaylist();
      afx_msg void OnUpdateViewPlaylist(cmd_ui * pcmdui);
      afx_msg void _001OnFileNew();
      afx_msg void OnViewAlbum();
      afx_msg void OnUpdateViewAlbum(cmd_ui * pcmdui);
      afx_msg void OnFileAdd();
      //afx_msg void OnLanguageChange(UINT uiId);
      //afx_msg void OnUpdateLanguageChange(cmd_ui * pcmdui);
      DECL_GEN_SIGNAL(_001OnUpdateViewEncoding)

      void InitializeResourceId();
      
      ::document * open_document_file(var varFile);
      afx_msg BOOL OnOpenRecentFile(UINT nID);
      afx_msg void OnUpdateRecentFileMenu(cmd_ui * pcmdui);


      virtual bool bergedge_start();
      virtual ::ca::application * get_app() const;
      virtual bool on_install();
   };


   CLASS_DECL_CA2_CUBE application & cast (::ca::application * papp);
   CLASS_DECL_CA2_CUBE class database & db(::ca::application * papp);

} // namespace mplite

