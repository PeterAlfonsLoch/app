#include "StdAfx.h"
#include "AppMessageWindow.h"
#include "VmpPlusThread.h"
#include "XfplayerThreadV2.h"
#include "AudioSpectrumViewUpdateHint.h"
#include "file_association.h"
#include "VmspPlaylistCallback.h"

#include "VmpHighThread.h"
#include "DDEFrameWnd.h"
#include "document_manager.h"

#include "ToolsOptionsDoc.h"
#include "ToolsOptionsMDIChildWnd.h"
#include "ToolsOptionsSongDirectoriesListView.h"

#include "FileAssociationsFormView.h"

#include "AlbumDoc.h"
#include "AlbumFrameWnd.h"
#include "AlbumMainView.h"

#include "document_manager.h"
#include "VmpPlaylistCallback.h"


// Text documents
#include "VmsTextFrame.h"
#include "VmsTextDoc.h"
#include "VmsTextView.h"



// User Interface
#include "optionsdialog.h"

//#include "splash.h"

#include "optionsimagesdialog.h"

#include "XfplayerViewUpdateHint.h"

#include "Configuration.h"

// CD Browsing Classes

#include "CDBrowseDoc.h"
#include "CDBrowseMDIChildWnd.h"
#include "CDBrowseView.h"


#include "notify_icon.h"

#include "AudioSpectrumDoc.h"
#include "AudioSpectrumView.h"

AFX_STATIC_DATA const char _afxShellOpenFmt[] = "%s\\shell\\open\\%s";
AFX_STATIC_DATA const char _afxShellPrintFmt[] = "%s\\shell\\print\\%s";
AFX_STATIC_DATA const char _afxShellPrintToFmt[] = "%s\\shell\\printto\\%s";
AFX_STATIC_DATA const char _afxDefaultIconFmt[] = "%s\\DefaultIcon";
AFX_STATIC_DATA const char _afxShellNewFmt[] = "%s\\ShellNew";

AFX_STATIC_DATA const char _afxFileSection[] = "Recent File List";
AFX_STATIC_DATA const char _afxFileEntry[] = "File%d";

#define DEFAULT_ICON_INDEX 0

AFX_STATIC_DATA const char _afxIconIndexFmt[] = ",%d";
AFX_STATIC_DATA const char _afxCommand[] = "command";
AFX_STATIC_DATA const char _afxOpenArg[] = _T(" \"%1\"");
AFX_STATIC_DATA const char _afxPrintArg[] = _T(" /p \"%1\"");
AFX_STATIC_DATA const char _afxPrintToArg[] = _T(" /pt \"%1\" \"%2\" \"%3\" \"%4\"");
AFX_STATIC_DATA const char _afxDDEArg[] = " /dde";

AFX_STATIC_DATA const char _afxDDEExec[] = "ddeexec";
AFX_STATIC_DATA const char _afxDDEOpen[] = _T("[open(\"%1\")]");
AFX_STATIC_DATA const char _afxDDEPrint[] = _T("[print(\"%1\")]");
AFX_STATIC_DATA const char _afxDDEPrintTo[] = _T("[printto(\"%1\",\"%2\",\"%3\",\"%4\")]");

AFX_STATIC_DATA const char _afxShellNewValueName[] = "NullFile";
AFX_STATIC_DATA const char _afxShellNewValue[] = "";

// recursively remove a registry key if and only if it has no subkeys


namespace vmsp
{
    // BEGIN_MESSAGE_MAP(application, ca77::application)
   /*   //{{AFX_MSG_MAP(application)
      ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
      ON_COMMAND(ID_FILE_OPEN, on_file_open)
      ON_COMMAND(ID_FILE_NEW, _001OnFileNew)
      ON_COMMAND(ID_HELP, OnHelp)
      ON_COMMAND(ID_HELP_FINDER, OnHelpFinder)
      ON_COMMAND(ID_FILE_NEW_FROMPLAYERVIEW, OnFileNewFromplayerview)
      ON_UPDATE_COMMAND_UI(ID_FILE_NEW_FROMPLAYERVIEW, OnUpdateFileNewFromplayerview)
      ON_COMMAND(ID_TOOLS_ALBUM, OnToolsAlbum)
      ON_UPDATE_COMMAND_UI(ID_TOOLS_ALBUM, OnUpdateToolsAlbum)
      ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
      ON_UPDATE_COMMAND_UI(ID_TOOLS_OPTIONS, OnUpdateToolsOptions)
      ON_UPDATE_COMMAND_UI(ID_FILE_MRU_FILE1, OnUpdateRecentFileMenu)
      ON_UPDATE_COMMAND_UI(ID_LANGUAGE_CHANGE, OnUpdateLanguageChangeMenu)
      ON_COMMAND(ID_LANGUAGE_ENUS, OnLanguageEnus)
      ON_UPDATE_COMMAND_UI(ID_LANGUAGE_ENUS, OnUpdateLanguageEnus)
      ON_COMMAND(ID_LANGUAGE_PTBR, OnLanguagePtbr)
      ON_UPDATE_COMMAND_UI(ID_LANGUAGE_PTBR, OnUpdateLanguagePtbr)
      ON_COMMAND(ID_LANGUAGE_DE, OnLanguageDe)
      ON_UPDATE_COMMAND_UI(ID_LANGUAGE_DE, OnUpdateLanguageDe)
      ON_COMMAND(ID_LANGUAGE_JP, OnLanguageJp)
      ON_UPDATE_COMMAND_UI(ID_LANGUAGE_JP, OnUpdateLanguageJp)
      ON_COMMAND(ID_CONTEXT_HELP, OnContextHelp)
      ON_COMMAND(ID_PLAYER, OnPlayer)
      ON_COMMAND(ID_TOOLS_OPTIONS_FILE_ASSOCIATIONS, OnToolsOptionsFileAssociations)
      ON_COMMAND(ID_TOOLS_OPTIONS_SONG_DIRECTORIES, OnToolsOptionsSongDirectories)
      ON_COMMAND(ID_FILE_OPEN_CD, OnFileOpenCd)
      //}}AFX_MSG_MAP
      // Standard file based document commands
   //   ON_COMMAND(ID_FILE_NEW, ca77::application::_001OnFileNew)
   //   ON_COMMAND(ID_FILE_OPEN, ca77::application::on_file_open)
      // Standard print setup command
      ON_COMMAND(ID_FILE_PRINT_SETUP, ca77::application::OnFilePrintSetup)
       ON_THREAD_MESSAGE(WM_USER, OnUserMessage)
       ON_THREAD_MESSAGE(WM_APP, OnAppMessage)*/
    // END_MESSAGE_MAP()

   application::application() :
      m_evInitialized(FALSE, TRUE)
   {
      m_pdocumentmanager = NULL;

      m_pwndMessageBoxParent = NULL;
   //string::m_dwResourceCP = 1252;
   //   m_pActiveDocument = NULL;
   //   m_pPlayingDocument = NULL;
      m_pMainDocTemplate = NULL;
      m_pxfplayerdoc = NULL;
       m_pMidiDocTemplate = NULL;
      m_phighthread = NULL;
      m_pthreadV2 = NULL;
   //   m_pthreadV3 = NULL;

   //   m_pplayerdoctemplateOLE = NULL;

      MusicalPlayerCentralContainer::set_app(this);
       
       //m_hPlayerMenuShared = NULL;
       m_hPlayerAccelTable = NULL;
       m_pmenuPlayerShared = NULL;
   //    m_pilMenuV033 = new ::image_list();

       m_pAlbumThread = NULL;
   //    AFX_MODULE_STATE * pState = AfxGetAppModuleState();
     //  pState->m_pCurrentWinApp = this;
   //   m_lpDirectDraw = NULL;
   //   m_pplaylistdoc = NULL;
      m_hmoduleResource = NULL;
   //   m_elanguage = langDefault;
      // TODO: add construction code here,
      // Place all significant initialization in initialize_instance

   }

   void application::construct()
   {
      //m_pszAppName         = _strdup("mplite");
      //m_strLicense         = "vmp";
      m_strBaseSupportId   = "votagus_ca2_vmp";
      m_eexclusiveinstance = ::radix::ExclusiveInstanceGlobal; // currently because audio devices globals
      m_lpoptionsdialog    = NULL;
      m_pdatabase          = NULL;
      m_pfileassociation   = NULL;
      m_precentfilelist    = NULL;
      
      // DDE variables
      m_hszAppName         = NULL;
      m_hszSystemTopic     = NULL;

      m_strInstallToken    = "vmp";
   }


   bool application::initialize_instance()
   {
      System.factory().creatable_small < XfplayerDoc >();
      System.factory().creatable_small < KaraokeSDIFrame >();
      System.factory().creatable_small < AudioSpectrumDoc >();
      System.factory().creatable_small < AudioSpectrumView >();
      System.factory().creatable_small < XfplayerView >();

      connect_command("file_open", &application::_001OnFileOpen);
      m_dataid = "VmpApp";

      if(!ca84::application::initialize_instance())
         return false;

      InitializeResourceId();

      if(!mediamanager::mediamanager_container::initialize_container(this))
         return false;

      if(!PlaylistCentralContainer::initialize(this))
         return false;


      m_strHelpFilePath = m_strModuleFolder + "vmpen.chm";
      m_pszHelpFilePath = _tcsdup(m_strHelpFilePath);


      if(!MusicalPlayerCentralContainer::Initialize(this))
         return false;


      GetMixerVisualCentral().m_idPlaybackIcon  = "mixer\\icon_playback.png";
      GetMixerVisualCentral().m_idPlaybackTab   = "<string id='mplite:mixer_playback_tab'>Playback</string>";
      GetMixerVisualCentral().m_idRecordingIcon = "mixer\\icon_recording.png";
      GetMixerVisualCentral().m_idRecordingTab  = "<string id='mplite:mixer_recording_tab'>Recording</string>";

      string strKey("veriwell\\Musical Player\\");
      strKey += get_version();
      SetRegistryKey(strKey);

      string strPath = GetProfileString("language", "resource path", "");
      VERIFY(SetLanguageResourcePath(strPath));


      if(!midi_central_container::initialize_central_container(this))
      {
         return false;
      }

      if(!MusicalPlayerCentralContainer::Initialize(this))
      {
         return false;
      }
//      SetRegistryKey("Veriwell");

      TRACE("application::initialize_instance current thread %X\n", GetCurrentThreadId());

      if(!command_line().m_bRunAutomated &&
         !command_line().m_bRunEmbedded
         && command_line().m_nShellCommand != gen::command_line::FileDDE)
      {
   /*      pSplashThread = (CSplashThread *) AfxBeginThread(&typeid(CSplashThread));
         pSplashThread->Initialize(&pSplashThread);
         pSplashThread->m_evInitialized.Lock();*/
      }
      else
      {
         SetMainWnd(NULL);
      }

    /*  keeper <::ca::window *> keepMessageBoxParent(
         &m_pwndMessageBoxParent,
         pSplashThread == NULL ?
         NULL
         : pSplashThread->GetMainWnd(),
         NULL,
         true);*/


//      mplite::InitializeFileManager("mplite/mainframe");

      
    //  CMessageFilterMainHook::AppGetMessageFilterMainHook(&m_pmfmh);
      //m_pmfmh->MessageFilterHook();


      {
         MEMORYSTATUS ms;
         GlobalMemoryStatus(&ms);
         if(ms.dwAvailPhys <  30 * 1024 * 1024)
         {
            savings().save(gen::resource_memory);
         }
      }


      GetPlaylistCentral().m_strMatter = "mplite/playlist";
      GetPlaylistCentral().m_typeinfoFrameWnd = &typeid(PlaylistFrame);
      GetPlaylistCentral().m_typeinfoView = &typeid(CPlaylistView);
      m_pplaylistcentralcallback = new mplite::playlist_central_callback(this);
      if(!GetPlaylistCentral().Initialize(this, m_pplaylistcentralcallback))
      {
         simple_message_box(NULL, "Failed to initialize Playlist Central");
         return false;
      }




        TRACE("GdiGetBatchLimit %d", GdiGetBatchLimit());
      GdiSetBatchLimit(50);

      m_XFToolTipV1ClassName = System.RegisterWndClass(NULL, 0, 0, 0);
      m_strMessageWndClassName = System.RegisterWndClass(NULL, 0, 0, 0);
       
   //   BaseMenuCentral::SetMenuCentral(new BaseMenuCentral());
   /*   UINT uiaMenuV003Map [][2] =
      {
         {ID_FILE_NEW, 0},
         {ID_FILE_OPEN, 1},
         {ID_FILE_SAVE, 2},
         {ID_VIEW_FULL_SCREEN, 7},
         {ID_TOOLS_ALBUM, 8},
         {ID_VIEW_PLAYLIST, 9},
         {ID_VIEW_LYRICS, 10},
         {ID_TOOLS_MIXER, 11},
         {ID_PLAY, 12},
         {ID_STOP, 13},
         {ID_PAUSE, 14},
         {ID_NEXTSONG, 15},
         {ID_VIEW_LEVELMETER, 18},
         {ID_WINDOW_LEVELMETER, 18},
         {ID_PLAYER, 19},
         {ID_ALBUM_NAVIGATOR, 20},
         {ID_ALBUM_FULLLIST, 21},
         {ID_ALBUM_TREELIST, 22},
         {ID_ALBUM_SEARCHLIST, 23},
         {ID_ALBUM_RESERVESONG, 24},
         {-1, 25}, //ID_CHECK
         {ID_SCORING_ENABLE, 26},
         {ID_ALBUM_DUPLICATESLIST, 27},
         {ID_VIEW_BOUNCINGBALL, 28},
         {ID_VIEW_GRADUALFILLING, 29},
         {ID_VIEW_BOUNCE_BALL1, 30},
         {ID_VIEW_BOUNCE_BALL2, 31},
         {ID_APP_EXIT, 32},
         {ID_REMOVE_SONG, 33},
         {ID_VMSGUI_CLOSE, 32},
         {ID_VIEW_IMAGE_ZOOMALL, 34},
         {ID_VIEW_IMAGE_TILE, 35},
         {ID_VIEW_IMAGE_STRETCH, 36},
         {ID_VIEW_IMAGE_ZOOMEXTEND, 37},
         {ID_VIEW_COMPACT_SIZE, 38},
         {ID_VMSGUI_WINDOW_MINIMIZE, 39},
         {ID_VIEW_LYRICVIEW_SPECTRUM, 40},
         {ID_VIEW_PLAYERCONTROLSETV19, 41},
         {ID_WINDOW_PLAYERCONTROLSETV19, 41},
         {-1, -1}
      };*/

   //CVmsGdiApi::open();

   //  BaseMenuCentral::GetMenuCentral()->MenuV033CreateImageMap(uiaMenuV003Map);

     /* BaseRelation < UINT, UINT, UINT, UINT > * prel;
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageMap(&prel);
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList()->create(IDB_MENUV033, 18, 1, RGB(192, 192, 192));
      System.imaging().CreateGrayVRCPImageList(NULL, BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(), BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList());
      m_pmenuPlayerShared = new CMenuV033(BaseMenuCentral::GetMenuCentral());*/

      string strModuleFolder(m_strModuleFolder);
      string strLib;
      string strExe;

      /*
      m_pImaging = new imaging();
      imaging::SetImaging(m_pImaging);
      */

      m_pMixerCentral = new MixerCentral(this);
      /* trans m_pMixerCentral->CreateEx(
         0, m_strMessageWndClassName, NULL,
         0, 0, 0, 0,
         NULL, NULL, NULL);*/


      if(!BeginVSeriesThreads())
         return false;

      
      m_XFViewClassName = System.RegisterWndClass(
         CS_DBLCLKS |
         CS_OWNDC,
         0, 0, 0);

      GetMidiCentral().SetMidiOutDevice(MIDI_MAPPER);
      GetAudioWaveCentral().m_uiWaveInDevice = WAVE_MAPPER;

   #if  (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) // DCOM
      HRESULT hRes = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
   #else
      CoInitialize(NULL);
   #endif
      
/*      ELanguage elanguageFinal;
      ELanguage elanguageDefault = GetDefaultLanguage();
      ELanguage elanguageOldDefault = (ELanguage) GetProfileInt("Language", "Default", langDefault);
      if(elanguageDefault != elanguageOldDefault)
         elanguageFinal = elanguageDefault;
      else
         elanguageFinal = (ELanguage) GetProfileInt("Language", "Current", elanguageDefault);
      WriteProfileInt("Language", "Default", elanguageDefault);

      SetLanguage(elanguageFinal);*/

      /*if(pSplashThread != NULL)
      {
         pSplashThread->GetMainWnd()->SendMessage(APPM_LANGUAGE, WPARAM_LANGUAGE_UPDATE, 0);
      }*/

      LoadAppSettings();



      LoadStdProfileSettings(64);  // Load standard INI file options (including MRU)

      m_pdocumentmanager = new vmsp::document_manager(this);
      if(m_pdocumentmanager == NULL)
         return false;

      // Register the application's document templates.  ::userbase::document templates
      //  serve as the connection between documents, frame windows and views.

      vmsp::document_manager & documentmanager = GetDocumentManager();
      if(!documentmanager.CreateTemplates())
         return false;

      PlaylistCentral & playlistcentral = GetPlaylistCentral();   

      playlistcentral.m_typeinfoFrameWnd = &typeid(PlaylistFrame);
      playlistcentral.m_typeinfoView = &typeid(PlaylistListView);

   //::userbase::single_document_template * pdoctemplatePlaylist = playlistcentral.CreateDocTemplate();

   //   _001AddDocTemplate(pdoctemplatePlaylist);

   /*   ::userbase::multiple_document_template * pvmstextdoctemplate;
      pvmstextdoctemplate = new ::userbase::multiple_document_template(
         this,
         IDR_VMSTEXT,
         &typeid(CVmsTextDoc),
         &typeid(CVmsTextFrame),
         &typeid(CVmsTextView));
   //  _001AddDocTemplate(pvmstextdoctemplate);
      m_pvmstextdoctemplate = pvmstextdoctemplate;
   */

      m_pdoctemplateFileAssociations = new
            ::userbase::single_document_template(
            this,
            "system/form",
            &typeid(CToolsOptionsDoc),
            &typeid(CToolsOptionsMDIChildWnd),
            &typeid(FileAssociationsFormView));

      m_pdoctemplateCDBrowse = new
            ::userbase::single_document_template(
            this,
            "system/form",
            &typeid(CCDBrowseDoc),
            &typeid(CDBrowseMDIChildWnd),
            &typeid(CDBrowseView));

      m_pdoctemplateSongDirectories = new
            ::userbase::single_document_template(
            this,
            "system/form",
            &typeid(CToolsOptionsDoc),
            &typeid(CToolsOptionsMDIChildWnd),
            &typeid(CToolsOptionsSongDirectoriesListView));

      if(!GetMixerVisualCentral().Initialize(this))
         return false;


      // Midi ::userbase::document Template
       





      if(command_line().m_nShellCommand == gen::command_line::FileDDE)
      {
         m_pddeframewnd = new DDEFrameWnd(this);
         if(!m_pddeframewnd->LoadFrame("system/form"))
            return false;
      }

      // Note: MDI applications register all server objects without regard
      //  to the /Embedding or /Automation on the command line.
      // create main MDI Frame ::ca::window
      

      // Enable DDE Execute open
      //EnableShellOpen();
   //   RegisterShellFileTypes(TRUE);

      // Parse command line for standard shell commands, DDE, file open
   //   CCommandLineInfo cmdInfo;
   //   ParseCommandLine(cmdInfo);

      // Check to see if launched as OLE server
      if (command_line().m_bRunEmbedded || command_line().m_bRunAutomated)
      {
         // System was run with /Embedding or /Automation.  Don't show the
         //  main ::ca::window in this case.
         m_evInitialized.SetEvent();
         if(command_line().m_bRunEmbedded)
         {
            //System.simple_message_box("Veriwell Musical Player Running Embedded");
         }
         if(command_line().m_bRunAutomated)
         {
            //System.simple_message_box("Veriwell Musical Player Running Automated");
         }
         
         return true;
      }

      if(command_line().m_nShellCommand != gen::command_line::FileDDE)
      {
         // create main MDI Frame ::ca::window
   /*      CMainFrame* pMainFrame = new CMainFrame;
         if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
            return FALSE;
         GetMainWnd() = pMainFrame;

         // Enable drag/drop open
         GetMainWnd()->DragAcceptFiles();*/
      }


      // When a server application is launched stand-alone, it is a good idea
      //  to update the system registry in case it has been damaged.
   //   documentmanager.UpdateRegistry();
   //   m_serverKar.UpdateRegistry(OAT_DOC_OBJECT_SERVER);
   //   m_serverSt3.UpdateRegistry(OAT_DOC_OBJECT_SERVER);
   //   COleObjectFactory::UpdateRegistryAll();

       //System.simple_message_box("9");
      // dispatch commands specified on the command line
      if (!_001ProcessShellCommand(command_line()))
         return false;


      //AfxDebugBreak();

      if(command_line().m_nShellCommand == gen::command_line::FileDDE)
      {
         ASSERT_KINDOF(DDEFrameWnd, m_pddeframewnd);
         m_pddeframewnd->ShowWindow(SW_HIDE);
         m_pddeframewnd->UpdateWindow();
      }
      else
      {
         if(GetMainWnd() == NULL)
         {
            _001OnFileNew();
         }
   /*      if(GetMainWnd() != NULL)
         {
            KaraokeSDIFrame* pMainFrame = (KaraokeSDIFrame *) GetKaraokeSDIFrame();
            GetMainWnd() = pMainFrame;
            
            ASSERT_KINDOF(KaraokeSDIFrame, pMainFrame);

            if(command_line().m_nShellCommand != CCommandLineInfo::FileOpen)
            {
               OpenDefaultPlaylist();
            }

            if(pMainFrame != NULL)
            {
               // The main ::ca::window has been initialized, so show and update it.
               pMainFrame->ShowWindow(m_nCmdShow);
               pMainFrame->UpdateWindow();
               pMainFrame->ActivateFrame();
            }
         }*/
      }



       /*
        * create the main DirectDraw object
        */

      // The one and only ::ca::window has been initialized, so show and update it.


       
       // Enable drag/drop open
      if(GetMainWnd() != NULL)
      {
   // trans      GetMainWnd()->DragAcceptFiles();
      }


      if(GetMainWnd() != NULL)
      {
         // The main ::ca::window has been initialized, so show and update it.
         GetMainWnd()->ShowWindow(m_nCmdShow);
         GetMainWnd()->UpdateWindow();
      }

   //  _Module.UpdateRegistryFromResource(IDR_VMSPLAYER, TRUE);
   //   _Module.RegisterServer(TRUE);



      if(false && command_line().m_nShellCommand != gen::command_line::FileDDE)
      {
         VerifyBrowsers();


         /*DBInterface::db()->SongsPostBuildAlbumMessage(
            &System,
            (SongsAlbum::EBuildSongsAlbumOperation)
            (SongsAlbum::eBuildSongsAlbumDeleteNotFound |
            SongsAlbum::eBuildSongsAlbumAddNew |
            SongsAlbum::eBuildSongsAlbumCreateSearchReferences),
            false);*/
      }




      

      /*if(pSplashThread != NULL)
      {
         pSplashThread->SetFocusToApp();
         pSplashThread->Kill();
         keepMessageBoxParent.KeepAway();
      }*/

       m_evInitialized.SetEvent();

       ::user::interaction * pwndMain = GetMainWnd();

      if(command_line().m_nShellCommand != gen::command_line::FileDDE)
      {
         SendMessageToWindows(WM_APP, 179, 0);
      }

      vmsp::file_association fileassociation(this);

      fileassociation.set_app(this);

      fileassociation.CheckAssociations();

      m_pnotifyicon = new vmsp::notify_icon(this);
      m_pnotifyicon->Start();

      return true;
   }
   int application::exit_instance() 
   {
      SetThreadPriority(THREAD_PRIORITY_HIGHEST);

      VERIFY(GetAudioWaveCentral().Finalize());
       if(m_pMixerCentral != NULL)
       {
           m_pMixerCentral->SendMessage(WM_CLOSE);
           delete m_pMixerCentral;
           m_pMixerCentral = NULL;
       }

       if(m_pfontcentral != NULL)
       {
   //        delete m_pfontcentral;
           m_pfontcentral = NULL;
       }
      
      if(m_phighthread != NULL)
      {
         m_phighthread->SetThreadPriority(THREAD_PRIORITY_NORMAL);
         m_phighthread->PostThreadMessage(WM_QUIT, 0, 0);
      }


      if(m_pthreadV2 != NULL)
      {
         m_pthreadV2->SetThreadPriority(THREAD_PRIORITY_NORMAL);
         m_pthreadV2->PostThreadMessage(WM_QUIT, 0, 0);
      }
      


      if(m_hmoduleResource != NULL)
      {
         FreeLibrary(m_hmoduleResource);
      }

      return ca77::application::exit_instance();

   }




   void application::Exit()
   {

       ASSERT(GetMainWnd() != NULL);
       GetMainWnd()->SendMessage(WM_CLOSE);

   }
   void application::OnFileManagerOpenFile(
         ::filemanager::data * pdata,
         ::fs::item_array & itema)
   {
      musctrl::MusicalPlayerCentral & playercentral = GetMusicalPlayerCentral();
      
      document * pdoc;
      bool bFirst = true;
      ::userbase::document_template::Confidence econfidence;
       for(int i = 0; i < itema.get_size(); i++)
      {
         econfidence = playercentral.get_document_template()->MatchDocType(itema[i].m_strPath, pdoc);
         if(econfidence == ::userbase::document_template::yesAttemptNative)
         {
            PlaylistCentral & playlistcentral = PlaylistCentralContainer::AppGetPlaylistCentral(get_app());
            playercentral.get_document_template()->ReserveSong(itema[i].m_strPath, bFirst, true);
            PlaylistDoc * pdoc = playlistcentral.GetCurrentPlaylist(true);
            if(pdoc != NULL)
            {
               ::view * pview = pdoc->get_view();
               if(pview != NULL)
               {
                  simple_frame_window * pframe = dynamic_cast < simple_frame_window * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pframe->m_etranslucency = ::user::window_interface::TranslucencyTotal;
                     pframe->m_wndframework.SetAppearanceTransparency(window_frame::Transparent);
                     ::view * pview = GetMusicalPlayerCentral().get_document_template()->get_document()->get_view();
                     pframe->m_pupdowntarget = dynamic_cast < window_frame::UpDownTarget * > (pview);
                     pframe->window_frame::CWorkSetDownUpInterface::m_iType = vmsp::ViewPlaylist;
                     pframe->WfiDown();
                  }
               }
            }

            bFirst = false;
         }
         else if(econfidence == ::userbase::document_template::yesAlreadyOpen)
         {
            TRACE("The file is already open.\n");
         }
         else
         {
            _001OpenDocumentFile(itema[i].m_strPath);
         }
      }
   }


   void application::on_file_open() 
   {
      // TODO: add your command handler code here
   //   ca77::application::on_file_open();
   //   return;
      //XfplayerOpenFileDialog dlgFile;


      ::filemanager::document * pdoc = (::filemanager::document *) GetStdFileManagerTemplate()->open(this, true, true);
      if(pdoc != NULL)
      {
         ::view * pview = pdoc->get_view();
         if(pview != NULL)
         {
            simple_frame_window * pframe = dynamic_cast < simple_frame_window * > (pview->GetParentFrame());
            if(pframe != NULL)
            {
               pframe->m_etranslucency = ::user::window_interface::TranslucencyTotal;
               pframe->m_wndframework.SetAppearanceTransparency(window_frame::Transparent);
               pdoc->get_filemanager_data()->m_bTransparentBackground = true;
               pdoc->Initialize(true);
               ::view * pview = GetMusicalPlayerCentral().get_document_template()->get_document()->get_view();
               pframe->m_pupdowntarget = dynamic_cast < window_frame::UpDownTarget * > (pview);
               pframe->window_frame::CWorkSetDownUpInterface::m_iType = vmsp::ViewFileManager;
               pframe->WfiDown();

            }
         }
      }


   /*   musctrl::MusicalPlayerCentral & playercentral = GetMusicalPlayerCentral();

      
      dlgFile.DoPrompt(IDS_XFPLAYER_OPENFILETITLE,
         OFN_HIDEREADONLY
         | OFN_FILEMUSTEXIST
         | OFN_ALLOWMULTISELECT
         | OFN_EXPLORER);

      stringa & straFile = dlgFile.m_straFile;

      ::userbase::document * pdoc;
      bool bFirst = true;
      ::userbase::document_template::Confidence econfidence;
       for(int i = 0; i < straFile.get_size(); i++)
      {
         econfidence = playercentral.get_document_template()->MatchDocType(straFile[i], pdoc);
         if(econfidence == ::userbase::document_template::yesAttemptNative)
         {
            playercentral.get_document_template()->ReserveSong(straFile[i], bFirst, true);
            bFirst = false;
         }
         else if(econfidence == ::userbase::document_template::yesAlreadyOpen)
         {
            TRACE("The file is already open.\n");
         }
         else
         {
            _001OpenDocumentFile(straFile[i]);
         }
      }
   */

   }

   void application::_001OnFileNew() 
   {
      musctrl::MusicalPlayerCentral & playercentral = GetMusicalPlayerCentral();
      playercentral.get_document_template()->open_document_file(NULL, true, m_puiInitialPlaceHolderContainer);
   }



   void application::pre_translate_message(gen::signal_object * pobj) 
   {
      SCAST_PTR(user::win::message::base, pbase, pobj);
      // TODO: add your specialized code here and/or call the base class
       if(pbase->m_hwnd == NULL)
       {
          switch(pbase->m_uiMessage)
         {
         case WM_DISPLAYCHANGE:
            int i;
            i = 2;
            break;
           case VMSM_ECONOMODECHANGE:
               OnChangeEconoMode();
               pbase->m_bRet = true;
               return;
           case WM_USER + 113:
               //ASSERT(FALSE);
               ViewToolsAlbum();
               pbase->m_bRet = true;
               //m_pAlbumDocTemplate->open_document_file(NULL);
               return;
         default:
            break;
         }
       }
       if(pbase->m_uiMessage == WM_USER + 1)
      {
   //      GetMainWnd()->SetForegroundWindow();
   //      GetMainWnd()->SetActiveWindow();
   //      GetMainWnd()->BringWindowToTop();
         pbase->m_bRet = true;
         return;
      }
   /*    else if(pMsg->message == WM_USER)
      {
           if(pMsg->wParam == 1)
           {
               if(pMsg->lParam == 1)
               {
                   DBInterface::db()->OnSongsUpdated();
               }
               else if(pMsg->lParam == 3)
               {
                   DBInterface::db()->OnSongsInfoV001Updated();
               }
           }
       }*/
   //   else if(pMsg->message == VMSM_EXCEPTION)
   //   {
   //      if(pMsg->wParam == EXCEPTION_OLEDB)
   //      {
   /*         COLEDBException * pE = (COLEDBException * ) pMsg->lParam;
             CDBErrorDialog dlg;
             dlg.Init(pE->m_spUnk, pE->m_iid);
             dlg.DoModal();
             pE->Delete();*/
   //         return TRUE;
   //      }
   //   }
   /*    else if(pMsg->message == VMSM_V001)
       {
           if(pMsg->hwnd == NULL)
           {
               if(pMsg->wParam == NOTIFY_BUILDALBUMPROGRESSUPDATE ||
                   pMsg->wParam == NOTIFY_BUILDALBUMSTATUSUPDATE ||
                   pMsg->wParam == NOTIFY_BUILDALBUMTASKSUPDATE)
               {
                   ASSERT(FALSE);
                   db_server* pDataCentral = GetDBCentral();
   /*               if(pDataCentral->IsBuildingSongsAlbum())
                   {
                       critical_section *pcs;
                       CDBBuildAlbumThreadData * lpdata =
                           pDataCentral->GetActiveBuildAlbumThreadData(&pcs);
                       if(lpdata != NULL)
                       {
                           lpdata->m_ptaskdlg->PostMessage(VMSM_V001, pMsg->wParam, 0);
                       }
                       pcs->Unlock();
                   }
                   else
                   {
                   //    ASSERT(FALSE);
                   }*/
               /*}
               else if(pMsg->wParam == NOTIFY_BUILDALBUMDELETE)
               {
                   db_server* pDataCentral = GetDBCentral();
   //               pDataCentral->DeleteBuildAlbumThreadData((CDBBuildAlbumThreadData *) pMsg->lParam);
               }
               else if(pMsg->wParam == NOTIFY_BUILDALBUMFINISHED)
               {
                   db_server* pDataCentral = GetDBCentral();
     //              pDataCentral->OnFinishedBuildAlbum((CDBBuildAlbumThreadData *) pMsg->lParam);
               }
               return TRUE;
           }
       }*/
      ::veriedit::application::pre_translate_message(pobj);
   }

   void application::LoadAppSettings()
   {
   //      if(!DBInterface::db()->IsWorking())
   //      return;

   /*db_long_set * pLongsSet = DBInterface::db()->get_db_long_set();
   //   if(pLongsSet->m_spRowset != NULL)
   //   {
         if(!pLongsSet->Load("MRU", "Count", (int &) m_nMaxMRU))
            m_nMaxMRU = _AFX_MRU_COUNT;

           int iEnable;
           if(!pLongsSet->Load("MRU", "Enable", iEnable))
            m_nMaxMRU = _AFX_MRU_COUNT;
           if(!iEnable)
               m_nMaxMRU = 0;

           if(!pLongsSet->Load("Images", "ChangeTime", m_iBackgroundUpdateMillis))
            m_iBackgroundUpdateMillis =  BACKGROUND_IMAGE_CHANGE_DEFAULT_SECONDS * 1000;
         else
            m_iBackgroundUpdateMillis *= 1000;
   //   }
   //   else
   //   {
   //      m_iBackgroundUpdateMillis = BACKGROUND_IMAGE_CHANGE_DEFAULT_SECONDS * 1000;
   //   }

      if(m_iBackgroundUpdateMillis < (BACKGROUND_IMAGE_CHANGE_MIN_SECONDS * 1000))
      {
         m_iBackgroundUpdateMillis = BACKGROUND_IMAGE_CHANGE_MIN_SECONDS * 1000;
      }

      //int iValue = GetProfileInt("Initialization", "Initialized", -1);
      //if(iValue == -1)
      //{
         // if GetProfileInt returned -1, it means that the entry was not
         // found
      //   WriteProfileInt("Initialization", "Initialized", 1);
      int iInitialized;
      if(!pLongsSet->Load("Initialization", "Initialized", iInitialized))
      {
           bool bAdd;
         pLongsSet->Save("Initialization", "Initialized", 1);
         string strModuleFolder(m_strModuleFolder);
         string strPath;
           string str;
           str.load_string(IDS_FOLDER_IMAGES);
         strPath += str;
         CDBImageDirectorySet * pImagesDirsSet = DBInterface::db()->GetImageDirSet();
           bAdd = true;
         if(pImagesDirsSet->m_spRowsetChange == NULL)
           {
               DBInterface::db()->OpenImagesDirsSet();
               if(pImagesDirsSet->m_spRowsetChange == NULL)
               {
   //                System.simple_message_box("application::LoadAppSettings() Fail 1000");
     //              bAdd = false;
               }

           }
           if(bAdd)
           {
               char buffer[MAX_PATH * 2];
               GetWindowsDirectory(buffer, sizeof(buffer));
               string strWallpaper(buffer);
               strWallpaper += "\\Web\\Wallpaper";
             pImagesDirsSet->add(strPath);
               pImagesDirsSet->add(strWallpaper);
               pImagesDirsSet->add(buffer);
               pImagesDirsSet->close();
               DBInterface::db()->OpenImagesDirsSet();
           }
         
         GetDefaultSongFolderPath(strPath);
         DBSongDirectorySet * pSongsDirsSet = DBInterface::db()->GetSongsDirsSet();
           bAdd = true;
         if(pSongsDirsSet->m_spRowsetChange == NULL)
           {
               DBInterface::db()->OpenSongsDirsSet();
               if(pSongsDirsSet->m_spRowsetChange == NULL)
               {
       //            System.simple_message_box("application::LoadAppSettings() Fail 2000");
         //          bAdd = false;
               }

           }
           if(bAdd)
           {
             pSongsDirsSet->add(strPath);
               pSongsDirsSet->close();
               DBInterface::db()->OpenSongsDirsSet();
           }
       }

      int iDev = MIDI_MAPPER;
      if(data_get(vmsp::Configuration::CfgMidiOutDevice, 0, 0, iDev))
      {
          GetMidiCentral().SetMidiOutDevice((UINT) iDev);
      }
      iDev = WAVE_MAPPER;
      if(data_get(vmsp::Configuration::CfgWaveInDevice, 0, 0, iDev))
      {
          GetAudioWaveCentral().m_uiWaveInDevice = (UINT) iDev;
      }
   */

   }


   void application::RegisterShellFileTypes(BOOL bCompat)
   {
      ASSERT(user::application::m_pdocmanager != NULL);
   //   m_pdocmanager->RegisterShellFileTypes(bCompat);
   //   ASSERT(!m_pdocmanager->m_templateptra.is_empty());  // must have some doc templates

      string strPathName, strTemp, strResourcePathName;
    
      strPathName = get_module_folder();

      stringa strarray;

      string str;

      throw not_implemented_exception();
      /*str.load_string(IDS_MID);
      strarray.add(str);
      str.load_string(IDS_KAR);
      strarray.add(str);
      str.load_string(IDS_ST3);
      strarray.add(str);*/

   /*CStrTokenizer strTokenizer;

      strTokenizer = str;*/

      stringa strarrayDostring;


      vmsp::file_association fileassociation(this);

      /*for (int iTemplate = 0; iTemplate < strarray.get_size(); iTemplate++)
      {
         strarrayDostring.remove_all();
         strarrayDostring.add_tokens(strarray[iTemplate],"\n", true);
         
         string strOpenCommandLine = strPathName;
         string strPrintCommandLine = strPathName;
         string strPrintToCommandLine = strPathName;
         string strDefaultIconCommandLine = strPathName;
           
           int nIconIndex = 1;
         if (bCompat)
         {
            string strIconIndex;
         //   HICON hIcon = ::ExtractIcon(System.m_hInstance, strPathName, nTemplateIndex);
               HICON hIcon = ::ExtractIcon(System.m_hInstance, strPathName, nIconIndex);
            if (hIcon != NULL)
            {
               //strIconIndex.Format(_afxIconIndexFmt, nTemplateIndex);
                   strIconIndex.Format(_afxIconIndexFmt, nIconIndex);
               DestroyIcon(hIcon);
            }
            else
            {
               strIconIndex.Format(_afxIconIndexFmt, DEFAULT_ICON_INDEX);
            }
            strDefaultIconCommandLine += strIconIndex;
         }

         string strFilterExt, strFileTypeId, strFileTypeName;
         strFileTypeId = strarrayDostring[::userbase::document_template::regFileTypeId];
         if (!strFileTypeId.is_empty())
         {
            strFileTypeName = strarrayDostring[::userbase::document_template::regFileTypeName];
            // enough info to register it
            if (strFileTypeName.is_empty())
               strFileTypeName = strFileTypeId;    // use id name

            ASSERT(strFileTypeId.find(' ') == -1);  // no spaces allowed

            // first register the type ID of our server
            if (!_AfxSetRegKey(strFileTypeId, strFileTypeName))
               continue;       // just skip it

            if (bCompat)
            {
               // path\DefaultIcon = path,1
               strTemp.Format(_afxDefaultIconFmt, (const char *)strFileTypeId);
               if (!_AfxSetRegKey(strTemp, strDefaultIconCommandLine))
                  continue;       // just skip it
            }

            strTemp = strarrayDostring[::userbase::document_template::windowTitle];
            // If MDI System
            if (strTemp.is_empty())
            {
               // path\shell\open\ddeexec = [open("%1")]
               strTemp.Format(_afxShellOpenFmt, (const char *)strFileTypeId,
                  (const char *)_afxDDEExec);
               if (!_AfxSetRegKey(strTemp, _afxDDEOpen))
                  continue;       // just skip it

               if (bCompat)
               {
                  // path\shell\print\ddeexec = [print("%1")]
                  strTemp.Format(_afxShellPrintFmt, (const char *)strFileTypeId,
                     (const char *)_afxDDEExec);
                  if (!_AfxSetRegKey(strTemp, _afxDDEPrint))
                     continue;       // just skip it

                  // path\shell\printto\ddeexec = [printto("%1","%2","%3","%4")]
                  strTemp.Format(_afxShellPrintToFmt, (const char *)strFileTypeId,
                     (const char *)_afxDDEExec);
                  if (!_AfxSetRegKey(strTemp, _afxDDEPrintTo))
                     continue;       // just skip it

                  // path\shell\open\command = path /dde
                  // path\shell\print\command = path /dde
                  // path\shell\printto\command = path /dde
                  strOpenCommandLine += _afxDDEArg;
                  strPrintCommandLine += _afxDDEArg;
                  strPrintToCommandLine += _afxDDEArg;
               }
               else
               {
                  strOpenCommandLine += _afxOpenArg;
               }
            }
            else
            {
               // path\shell\open\command = path filename
               // path\shell\print\command = path /p filename
               // path\shell\printto\command = path /pt filename printer driver port
               strOpenCommandLine += _afxOpenArg;
               if (bCompat)
               {
                  strPrintCommandLine += _afxPrintArg;
                  strPrintToCommandLine += _afxPrintToArg;
               }
            }

            // path\shell\open\command = path filename
            strTemp.Format(_afxShellOpenFmt, (const char *)strFileTypeId,
               (const char *)_afxCommand);
            if (!_AfxSetRegKey(strTemp, strOpenCommandLine))
               continue;       // just skip it

            if (bCompat)
            {
               // path\shell\print\command = path /p filename
               strTemp.Format(_afxShellPrintFmt, (const char *)strFileTypeId,
                  (const char *)_afxCommand);
               if (!_AfxSetRegKey(strTemp, strPrintCommandLine))
                  continue;       // just skip it

               // path\shell\printto\command = path /pt filename printer driver port
               strTemp.Format(_afxShellPrintToFmt, (const char *)strFileTypeId,
                  (const char *)_afxCommand);
               if (!_AfxSetRegKey(strTemp, strPrintToCommandLine))
                  continue;       // just skip it
            }
            strFilterExt = strarrayDostring[::userbase::document_template::filterExt];
               CStrTokenizer strtokenizer;
               strtokenizer = strFilterExt;
               while(strtokenizer.GetNextToken(strFilterExt, ";", false))
               {
                if (!strFilterExt.is_empty())
                {
                   ASSERT(strFilterExt[0] == '.');

                   LONG lSize = _MAX_PATH * 2;
                   LONG lResult = ::RegQueryValue(HKEY_CLASSES_ROOT, strFilterExt,
                      strTemp.GetBuffer(lSize), &lSize);
                   strTemp.ReleaseBuffer();

                   if (lResult != ERROR_SUCCESS || strTemp.is_empty() ||
                      strTemp == strFileTypeId)
                   {
                      // no association for that suffix
                      if (!_AfxSetRegKey(strFilterExt, strFileTypeId))
                         continue;

                      if (bCompat)
                      {
                         strTemp.Format(_afxShellNewFmt, (const char *)strFilterExt);
                         (void)_AfxSetRegKey(strTemp, _afxShellNewValue, _afxShellNewValueName);
                      }
                   }
                       else
                       {
                       }
                   }
            }
         }
         fileassociation.UpdateServerRegistration(strarray[iTemplate]);
      }*/
   }

   //bool application::InitDirectDraw()
   //{
   //    HANDLE hLibrary = LoadLibrary("d3d8.dll");
   //    if(hLibrary == NULL)
   //        return false;
   //    m_spDirectDraw = Direct3DCreate8(D3D_SDK_VERSION);
   //    return true;
   //}



   void application::OnFileNewFromplayerview() 
   {
      // TODO: add your command handler code here
   //    XfplayerDoc * pDoc = (XfplayerDoc *) GetPlayerDocTemplate()->get_document(0);
     //  m_pMainDocTemplate->open_document_file(pDoc->get_path_name());
      
   }

   void application::OnUpdateFileNewFromplayerview(cmd_ui * pcmdui) 
   {
      // TODO: add your command update UI handler code here
   //    XfplayerDoc * pDoc = (XfplayerDoc *) GetPlayerDocTemplate()->get_document(0);
     //  pcmdui->Enable(pDoc->GetMidiPlayer() &&
       //   pDoc->GetMidiSequence()->GetState() != ::mus::midi::sequence::StatusNoFile);
   }


   int application::GetEconoMode_()
   {
       ASSERT(FALSE);
       return -1;
       //return m_iEconoMode;
   }

   void application::OnChangeEconoMode()
   {

      if(GetMainWnd() != NULL)
           GetMainWnd()->SendMessage(VMSM_ECONOMODECHANGE);
   }


   /*KaraokeSDIFrame * application::GetKarWnd()
   {
       XfplayerDoc * pdoc;
      musctrl::MusicalPlayerCentral & playercentral =
         musctrl::MusicalPlayerCentral::AppGetMusicalPlayerCentral();
      musctrl::userbase::single_document_template * pdoctemplate =
         playercentral.get_document_template();
       if(pdoctemplate != NULL)
       {
           if(pdoc = (XfplayerDoc *) pdoctemplate->get_document(0))
           {
               if(pdoc->GetLyricView())
               {
                   return (KaraokeSDIFrame *) pdoc->GetLyricView()->GetParentFrame();
               }
           }
       }
       return NULL;
   }*/

   void application::_001OnToolsAlbum(gen::signal_object * pobj) 
   {
      // TODO: add your command handler code here
       ViewToolsAlbum();
      
   }

   void application::OnUpdateToolsAlbum(cmd_ui * pcmdui) 
   {
      // TODO: add your command update UI handler code here
      
   }

   VMSRESULT application::OpenToolsAlbum()
   {
   //   if(CDataCentral::db()->IsWorking())
      //{
         wait_cursor cwc(get_app());



         if(m_pAlbumThread == NULL)
         {
            CreateAlbumThread();
         }
         if(m_pAlbumThread != NULL)
         {
   //        m_pAlbumThread->PostMessageViewAlbum(false);
         }
         else
         {
         }
   //   }
   //   else
   //   {
   //      System.simple_message_box(IDS_NODATABASESUPPORTERROR_RESOURCEUNAVAILABLE, MB_ICONINFORMATION);
   //   }
   //    if(m_pAlbumThread == NULL)
     //  {
       //    m_pAlbumThread = (mediamanager::AlbumBuildThread *) AfxBeginThread(
         //      &typeid(mediamanager::AlbumBuildThread));

   //    }
     //  else
       //{
         //  m_pAlbumThread->ViewToolsAlbum();
       //}
   //        application * pApp = (application *)&System;
   /*    if(GetDBCentral()->IsWorking())
       {*/
          if(m_pAlbumDocTemplate == NULL)
          {
               m_pAlbumDocTemplate = new ::userbase::single_document_template(
                  this,
                   "mplite/mainframe",
                   &typeid(AlbumDoc),
                   &typeid(AlbumFrameWnd),
                   &typeid(AlbumMainView));
    //           _001AddDocTemplate(m_pAlbumDocTemplate);
               //m_pAlbumDocTemplate->
               //type_info* pRuntimeClass = &typeid(AlbumFrameWnd);
              //::radix::object* pObject = pRuntimeClass->CreateObject();
              //ASSERT(base < AlbumFrameWnd >::bases(pObject));
              //AlbumFrameWnd * pAlbumFrameWnd = (AlbumFrameWnd *) pObject;
               //create_context cc;
               //cc.m_pCurrentDoc = NULL;
               //cc.m_pCurrentFrame = pAlbumFrameWnd;
               //cc.m_pLastView = NULL;
               //cc.m_pNewDocTemplate = NULL;
               //cc.m_typeinfoNewView = &typeid(AlbumFormView);
               //System.simple_message_box("7.4");
              //if (!pAlbumFrameWnd->LoadFrame(IDR_ALBUM,
               //    WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
               //    NULL, &cc))

   //            {
   //             delete m_pAlbumFrameWnd;
   //             m_pAlbumDocTemplate = NULL;
               //}
               //m_pAlbumFrameWnd = pAlbumFrameWnd;
          }
          m_pAlbumDocTemplate->open_document_file(NULL);
          /*
          //dlg.DoModal();
          /*if(m_pAlbumDocTemplate != NULL)
          {
               if(GetDBCentral()->IsBuildingSongsAlbum())
               {
                   critical_section *pcs;
                   CDBBuildAlbumThreadData * lpData =
                       GetDBCentral()->GetActiveBuildAlbumThreadData(&pcs);
                   if(lpData != NULL)
                   {
                       //lpdata->m_ptaskdlg->m_pCloseWindow = m_pAlbumFrameWnd;
                  lpdata->m_ptaskdlg->SetPendingShowCommandFlag(true);
                   }
                   pcs->Unlock();
               }
               else
               {
   //                m_pAlbumDialog->Update(); // retirar se possível
                 //m_pAlbumFrameWnd->ShowWindow(SW_SHOWNORMAL);
                 /*m_pAlbumDialog->SetWindowPos(
                       ZORDER_TOP,
                    0, 0,
                    0, 0,
                    SWP_NOMOVE |
                    SWP_NOSIZE); //|
                    //SWP_SHOWWINDOW);*/
                  //m_pAlbumFrameWnd->InitialUpdateFrame(NULL, true);
                   //m_pAlbumFrameWnd->ActivateFrame();
               /*}
          }
          
   //       ::ca::window * pParent = GetParent();
       }
       else
       {
           System.simple_message_box(
               IDS_NODATABASESUPPORTERROR_RESOURCEUNAVAILABLE,
               MB_OK |
               MB_ICONINFORMATION);

       }*/

       /*application * pApp = (application *)&System;
       if(pApp->GetDBCentral()->IsWorking())
       {
          if(m_pAlbumFrameWnd == NULL)
          {
               type_info* pRuntimeClass = &typeid(AlbumFrameWnd);
              ::radix::object* pObject = pRuntimeClass->CreateObject();
              ASSERT(base < AlbumFrameWnd >::bases(pObject));
              AlbumFrameWnd * pAlbumFrameWnd = (AlbumFrameWnd *) pObject;
               create_context cc;
               cc.m_pCurrentDoc = NULL;
               cc.m_pCurrentFrame = pAlbumFrameWnd;
               cc.m_pLastView = NULL;
               cc.m_pNewDocTemplate = NULL;
               cc.m_typeinfoNewView = &typeid(AlbumFormView);
               //System.simple_message_box("7.4");
              if (!pAlbumFrameWnd->LoadFrame(IDR_ALBUM,
                   WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
                   NULL, &cc))

               {
   //             delete m_pAlbumFrameWnd;
                m_pAlbumFrameWnd = NULL;
               }
               m_pAlbumFrameWnd = pAlbumFrameWnd;
          }
          //dlg.DoModal();
          if(m_pAlbumFrameWnd != NULL)
          {
               if(pApp->GetDBCentral()->IsBuildingSongsAlbum())
               {
                   critical_section *pcs;
                   CDBBuildAlbumThreadData * lpData =
                       pApp->GetDBCentral()->GetActiveBuildAlbumThreadData(&pcs);
                   if(lpData != NULL)
                   {
                       lpdata->m_ptaskdlg->m_pCloseWindow = m_pAlbumFrameWnd;
                  lpdata->m_ptaskdlg->SetPendingShowCommandFlag(true);
                   }
                   pcs->Unlock();
               }
               else
               {
   //                m_pAlbumDialog->Update(); // retirar se possível
                 //m_pAlbumFrameWnd->ShowWindow(SW_SHOWNORMAL);
                 /*m_pAlbumDialog->SetWindowPos(
                       ZORDER_TOP,
                    0, 0,
                    0, 0,
                    SWP_NOMOVE |
                    SWP_NOSIZE); //|
                    //SWP_SHOWWINDOW);*/
                  //m_pAlbumFrameWnd->InitialUpdateFrame(NULL, true);
                   //m_pAlbumFrameWnd->ActivateFrame();
     //          }
   //       }
          
   //       ::ca::window * pParent = GetParent();
       /*}
       else
       {
           System.simple_message_box(
               IDS_NODATABASESUPPORTERROR_RESOURCEUNAVAILABLE,
               MB_OK |
               MB_ICONINFORMATION);

       }*/
       return VMSR_SUCCESS;

   }

   VMSRESULT application::ViewToolsAlbum()
   {
       return OpenToolsAlbum();
   }

   mediamanager::AlbumBuildThread * application::GetAlbumThread()
   {
       if(m_pAlbumThread == NULL)
       {
           CreateAlbumThread();
       }
       return m_pAlbumThread;
   }

   ::userbase::multiple_document_template * application::GetMidiDocTemplate()
   {
       return m_pMidiDocTemplate;
   }


   VMSRESULT application::SetAlbumThread(mediamanager::AlbumBuildThread *pAlbumThread)
   {
       m_pAlbumThread = pAlbumThread;
       return VMSR_SUCCESS;
   }

   string application::GetAppFolder()
   {
      char lpszModuleFilePath[MAX_PATH + 1];
      GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);
      char lpszModuleFolder[MAX_PATH + 1];
      LPTSTR lpszModuleFileName;
      GetFullPathName(lpszModuleFilePath, MAX_PATH + 1, lpszModuleFolder, &lpszModuleFileName);
      string strModuleFolder(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);
      return strModuleFolder;
   }

   VMSRESULT application::CreateAlbumThread()
   {
       m_pAlbumThread = AfxBeginThread < mediamanager::AlbumBuildThread > (this); 
       if(m_pAlbumThread != NULL)
       {
           return VMSR_SUCCESS;
       }
       else
       {
           return VMSR_E_FAIL;
       }

   }


   void application::OnToolsOptions() 
   {
      OptionsDialog optionsDialog(this);
      ASSERT(FALSE);
      // optionsDialog.DoModal();
   }

   void application::OnUpdateToolsOptions(cmd_ui * pcmdui) 
   {
      // TODO: add your command update UI handler code here
       pcmdui->Enable();   
   }




   void application::OnAppMessage(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj);
      musctrl::MusicalPlayerCentral & playercentral =
         musctrl::MusicalPlayerCentral::AppGetMusicalPlayerCentral(this);
      musctrl::single_document_template * pdoctemplate =
         playercentral.get_document_template();
      switch(pbase->m_wparam)
      {
      case 178:
         {
            Scoring::UpdateMessage * lpsum = (Scoring::UpdateMessage *) pbase->m_lparam ;
            if(lpsum == NULL)
               return;
   /*         XfplayerDoc * pdoc = (XfplayerDoc *) pdoctemplate->get_document(0);
            if(pdoc == NULL)
            {
               delete lpsum;
               return;
            }
            CAudioSpectrumViewUpdateHint uh;
            uh.m_lpwaveformatex = GetAudioWaveCentral().GetWaveIn()->GetFormatEx();         
            uh.m_dDeltaScore = lpsum->m_dDeltaScore;
            uh.m_dScoreAddUp = lpsum->m_dScoreAddUp;*/
            delete lpsum;
            lpsum = NULL;
   /*         ::userbase::document * pdoctarget = (::userbase::document *) pdoc->GetAudioSpectrumDoc();
            pdoctarget->update_all_views(NULL, 0, &uh);*/
         }
         break;
      default:
         break;
      }
   }


   void application::OnUserMessage(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj);
      switch(pbase->m_wparam)
      {
      case 21:
   //                    ASSERT(FALSE);
   //                  //ReserveSong_(pMsg->lParam);
         
           GetMusicalPlayerCentral().get_document_template()->ReserveSong(pbase->m_lparam, false, true);
           break;
       case 22:
         {
            dword_array * pdwa = (dword_array *) pbase->m_lparam;
            GetMusicalPlayerCentral().get_document_template()->ReserveSong((LPINT) &pdwa->get_data()[1], pdwa->get_at(0), false, true);
            delete pdwa;
         }
         break;
       case 23:
           {
            ASSERT(FALSE);
               //stringa * pstra = (stringa *) lParam;
               //GetPlayerDocTemplate()->ReserveSong(pstra, false, true);
   //            delete pstra;
           }
           break;
       case 24:
           {
               stringa * pwstra = (stringa *) pbase->m_lparam;
               GetMusicalPlayerCentral().get_document_template()->ReserveSong(*pwstra, false, true);
               delete pwstra;
           }
           break;
      }
      if(pbase->m_wparam == 1)
      {
         if(pbase->m_lparam == 1)
         {
   //           DBInterface::db()->OnSongsUpdated();
         }
         else if(pbase->m_lparam == 3)
         {
   //            DBInterface::db()->OnSongsInfoV001Updated();
         }
      }

      switch(pbase->m_wparam)
      {
      case 131415:
         ViewToolsAlbum();
         break;
      case 565758:
         {
   /*           CDBBuildAlbumThreadData * lpdata = 
                   (CDBBuildAlbumThreadData *)lParam;
               ::userbase::single_document_template * pAlbumDocTemplate = NULL;
               if(GetAlbumThread())
               {
                   pAlbumDocTemplate = GetAlbumThread()->GetAlbumDocTemplate();
               }
               bool bVisible = false;
               if(pAlbumDocTemplate != NULL)
               {
                   bVisible = pAlbumDocTemplate->get_document_count() != NULL;

                   // avoid thread quit on close all documents
                   GetAlbumThread()->GetMainWnd() = NULL;

                   GetAlbumThread()->PostThreadMessage(mediamanager::AlbumBuildThread::MessageMain, mediamanager::AlbumBuildThread::MessageMainCloseAllAlbumDocuments, FALSE);
               }
               //AlbumFrameWnd * pAlbum = GetAlbumDocTemplate();
               //bool bVisible;
               //if(pAlbum != NULL)
               //{
                 //  bVisible = (pAlbum->GetStyle() & WS_VISIBLE) != 0;
                   //if(bVisible)
                     //  pAlbum->ShowWindow(SW_HIDE);
               //}
               lpdata->bVisible = bVisible;*/
           }
           break;
       case 676869:
           {
               ASSERT(FALSE);
   /*            CDBBuildAlbumThreadData * lpdata = 
                   (CDBBuildAlbumThreadData *)lParam;
               if(!lpdata->m_ptaskdlg->create(IDD_TASK))
               {
                   System.simple_message_box("Could not create task dialog");
                   return;
               }
       
               GetAlbumThread()->GetMainWnd() = lpdata->m_ptaskdlg;
           */
           }
       case 787970:
           {
   /*           CDBBuildAlbumThreadData * lpdata = 
                   (CDBBuildAlbumThreadData *)lParam;
               if(m_pAlbumDocTemplate != NULL)
               {
                   if(lpdata->bVisible)
                   {
                       lpdata->lpDataCentral->m_csBuildAlbumThreadData.Lock();
                       lpdata->m_evStarted.Lock();
                       //lpdata->m_ptaskdlg->m_pCloseWindow = pAlbum;
           //            lpdata->m_ptaskdlg->m_lparamClose = 10;
                       lpdata->lpDataCentral->m_csBuildAlbumThreadData.Unlock();
                   }
               }*/
           }
           break;
       case 345456:
           {
               bool bFullBuild = (pbase->m_lparam & 0x80000000) != 0;
               int eop = pbase->m_lparam & 0x7fffffff;
               mediamanager::AlbumBuildThread * pThread = GetAlbumThread();
               if(pThread == NULL)
                   return;
       
   /*           mediamanager::AlbumBuildThread::CBuildRequest * lpbr = new mediamanager::AlbumBuildThread::CBuildRequest();

               lpbr->m_pdc = GetDBCentral();
               lpbr->m_eop = (SongsAlbum::EBuildSongsAlbumOperation) eop;
               lpbr->m_bfb = bFullBuild;

               pThread->PostThreadMessage(mediamanager::AlbumBuildThread::MessageMain, mediamanager::AlbumBuildThread::MessageMainCreateBuildAlbumThread, (LPARAM) lpbr);*/


           }
           break;
       case 321432:
           {
               // On Task Dialog Stop
   //            ASSERT(DBInterface::db() != NULL);
   //           DBInterface::db()->SetBuildAlbumThreadsCancelFlag();
           }
           break;
       case 3214:
           {
               OnChangeEconoMode();

           }
           break;
       case 534231:
           {
            ASSERT(FALSE);
               //GetKarWnd()->SendMessageToDescendants(WM_USER, 534231);
           }
           break;
       default:;
           break;
       }
   }

   void application::RegisterShellExtension(bool bRegister)
   {
       char lpszModuleFilePath[MAX_PATH + 1];
      GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);
      
       char lpszModuleFolder[MAX_PATH + 1];
      LPTSTR lpszModuleFileName;
      GetFullPathName(lpszModuleFilePath, MAX_PATH + 1, lpszModuleFolder, &lpszModuleFileName);
      
       string strModuleFolder(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);
       string str("vmsse.dll");
       string strFormat;
      if(bRegister)
      {
         strFormat.Format(" /s %s%s",strModuleFolder,str);
      }
      else
      {
         strFormat.Format(" /u /s %s%s",strModuleFolder,str);
      }
       ShellExecute(GetMainWnd()->GetTopLevelParent()->_get_handle(), "open", "regsvr32.exe", strFormat, strModuleFolder,SW_SHOW); 

   /*    CRegKey regKey;

       UUID uuida[2];
       uuida[0] = CLSID_AlbumSongFolder;
       uuida[1] = CLSID_AlbumSongView;
       

       int i;
       string strParam;
       string strCLSID;
       string strBase;
       string strSystemRoot;
       string str;

       {
           char lpBuffer[MAX_PATH];
           GetWindowsDirectory(
               lpBuffer,  // address of buffer for system directory
               MAX_PATH);        // size of directory buffer);
           strSystemRoot = lpBuffer;
       }

       for(i = 0; i < 2; i++)
       {
           UUID uuid = uuida[i];
           unsigned char * lpstr = NULL;
       
           UuidToString(&uuid, &lpstr);

           strParam = lpstr;
           strCLSID = strParam;
       

           RpstringFree(&lpstr);

           
       
           str.Format("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Desktop\\NameSpace\\{%s}", strParam);

       
           if( ERROR_SUCCESS != regKey.open(
               HKEY_LOCAL_MACHINE,
               str))
           {
               VERIFY((regKey.create(
                   HKEY_LOCAL_MACHINE,
                   str,
                   REG_OPTION_NON_VOLATILE) == ERROR_SUCCESS));
           }

           regKey.SetValue("Meus Karaokês");

           regKey.close();



           strBase.Format("CLSID\\{%s}", strParam);
           str.Format("%s", strBase);

           if( ERROR_SUCCESS != regKey.open(
               HKEY_CLASSES_ROOT,
               str))
           {
               VERIFY((regKey.create(
                   HKEY_CLASSES_ROOT,
                   str,
                   REG_OPTION_NON_VOLATILE) == ERROR_SUCCESS));
           }

           str.Format("%s", "Meus Karaokês");

           regKey.SetValue(str);
           regKey.close();
    



           str.Format("%s\\DefaultIcon", strBase);
           if( ERROR_SUCCESS != regKey.open(
               HKEY_CLASSES_ROOT,
               str))
           {
               VERIFY((regKey.create(
                   HKEY_CLASSES_ROOT,
                   str,
                   REG_OPTION_NON_VOLATILE) == ERROR_SUCCESS));
           }

           char lpszModuleFilePath[MAX_PATH + 1];
          GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);
          
           char lpszModuleFolder[MAX_PATH + 1];
          LPTSTR lpszModuleFileName;
          GetFullPathName(lpszModuleFilePath, MAX_PATH + 1, lpszModuleFolder, &lpszModuleFileName);
          
           string strModuleFolder(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);
       #define IDR_XFPLAYER_INDEX 2
           str.Format("%svms.exe,%d", strModuleFolder, IDR_XFPLAYER_INDEX);
           //str.Format("%svms.exe,%d", strModuleFolder, 3);
           regKey.SetValue(str);
           regKey.close();

           str.Format("SOFTWARE\\Microsoft\\WindowsNT\\CurrentVersion\\ShellExtensions\\Approved\\{%s}", strCLSID);
           if( ERROR_SUCCESS != regKey.open(
               HKEY_LOCAL_MACHINE,
               str))
           {
               VERIFY((regKey.create(
                   HKEY_LOCAL_MACHINE,
                   str,
                   REG_OPTION_NON_VOLATILE) == ERROR_SUCCESS));
           }

           str.Format("Meus Karaokês", strSystemRoot);
           regKey.SetValue(str);
           regKey.close();

           //HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Shell Extensions\Approved

           str.Format("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved");
           if( ERROR_SUCCESS != regKey.open(
               HKEY_LOCAL_MACHINE,
               str))
           {
               VERIFY((regKey.create(
                   HKEY_LOCAL_MACHINE,
                   str,
                   REG_OPTION_NON_VOLATILE) == ERROR_SUCCESS));
           }

           str.Format("Meus Karaokês", strSystemRoot);
           regKey.SetValue(str, strCLSID);
           regKey.close();
       }

       UUID uuid = CLSID_AlbumSongFolder;
       unsigned char * lpstr = NULL;

       UuidToString(&uuid, &lpstr);

       strParam = lpstr;
       strCLSID = strParam;


       RpstringFree(&lpstr);

   //    string strBase;
       strBase.Format("CLSID\\{%s}", strParam);
       str.Format("%s\\Shell\\open\\Command", strBase);


       if( ERROR_SUCCESS != regKey.open(
           HKEY_CLASSES_ROOT,
           str))
       {
           VERIFY((regKey.create(
               HKEY_CLASSES_ROOT,
               str,
               REG_OPTION_NON_VOLATILE) == ERROR_SUCCESS));
       }

       str.Format("%s\\explorer.exe /root,::{%s}", strSystemRoot, strCLSID);

       regKey.SetValue(str);
       regKey.close();

       str.Format("%s\\Shell\\Explore\\Command", strBase);
       if( ERROR_SUCCESS != regKey.open(
           HKEY_CLASSES_ROOT,
           str))
       {
           VERIFY((regKey.create(
               HKEY_CLASSES_ROOT,
               str,
               REG_OPTION_NON_VOLATILE) == ERROR_SUCCESS));
       }

       str.Format("%s\\explorer.exe /e,/root,::{%s}", strSystemRoot, strCLSID);
       regKey.SetValue(str);
       regKey.close();*/


   }

   db_server * application::GetDBCentral()
   {
       return dynamic_cast < db_server * > (&db());
   }

      

   void application::OnUpdateRecentFileMenu(cmd_ui * pcmdui) 
   {
      // TODO: add your command update UI handler code here
       TRACE("application::OnUpdateRecentFileMenu");
       if(m_pRecentFileList == NULL)
       {
           pcmdui->Enable(FALSE);
           string str;
           throw not_implemented_exception();
           //str.load_string(IDS_RECENT_FILE);
           pcmdui->SetText(str);
   /*       for (int iMRU = 1; iMRU < 10; iMRU++)
             pcmdui->m_pMenu->DeleteMenu(pcmdui->m_nID + iMRU, MF_BYCOMMAND);
           return;*/
       }
   //      ASSERT(m_pRecentFileList->m_arrNames != NULL);

   /*   ::userbase::menu* pMenu = pcmdui->m_pMenu;
      if (m_pRecentFileList->m_strOriginal.is_empty() && pMenu != NULL)
         pMenu->GetMenuString(pcmdui->m_nID, m_pRecentFileList->m_strOriginal, MF_BYCOMMAND);*/

   /*   if (m_pRecentFileList->m_arrNames[0].is_empty())
      {
         // no MRU files
         if (!m_pRecentFileList->m_strOriginal.is_empty())
            pcmdui->SetText(m_pRecentFileList->m_strOriginal);
         pcmdui->Enable(FALSE);
         return;
      }

      if (pcmdui->m_pMenu == NULL)
         return;

   /*   ::userbase::menu * pmenu = CMenuUtil::FindPopupMenuFromID(pcmdui->m_pMenu, pcmdui->m_nID);
       
       if(pmenu == NULL)
       {
           pmenu = pcmdui->m_pMenu;
       }

       bool bCmdUIMenu = pmenu == pcmdui->m_pMenu;

      for (int iMRU = 0; iMRU < m_pRecentFileList->m_nSize; iMRU++)
         pcmdui->m_pMenu->DeleteMenu(pcmdui->m_nID + iMRU, MF_BYCOMMAND);

       int nIndex = pcmdui->m_nIndex;
       int nID = pcmdui->m_nID;

      char szCurDir[_MAX_PATH];
      GetCurrentDirectory(_MAX_PATH, szCurDir);
      int nCurDir = lstrlen(szCurDir);
      ASSERT(nCurDir >= 0);
      szCurDir[nCurDir] = '\\';
      szCurDir[++nCurDir] = '\0';

      string strName;
      string strTemp;
      for (iMRU = 0; iMRU < m_pRecentFileList->m_nSize; iMRU++)
      {
         if (!m_pRecentFileList->GetDisplayName(strName, iMRU, szCurDir, nCurDir))
            break;

         // double up any '&' characters so they are not underlined
         const char * lpszSrc = strName;
         LPTSTR lpszDest = strTemp.GetBuffer(strName.get_length()*2);
         while (*lpszSrc != 0)
         {
            if (*lpszSrc == '&')
               *lpszDest++ = '&';
            if (_istlead(*lpszSrc))
               *lpszDest++ = *lpszSrc++;
            *lpszDest++ = *lpszSrc++;
         }
         *lpszDest = 0;
         strTemp.ReleaseBuffer();

         // insert mnemonic + the file name
         char buf[10];
         wsprintf(buf, "&%d ", (iMRU+1+m_pRecentFileList->m_nStart) % 10);
           
   //      pcmdui->m_pMenu->InsertMenu(pcmdui->m_nIndex++,
   //         MF_STRING | MF_BYPOSITION, pcmdui->m_nID++,
   //         string(buf) + strTemp);
         pmenu->InsertMenu(nIndex,
            MF_STRING | MF_BYPOSITION, nID,
            string(buf) + strTemp);
           nIndex++;
           nID++;
           if(bCmdUIMenu)
           {
               pcmdui->m_nIndex = nIndex;
               pcmdui->m_nID = nID;
           }
      }

      // update end menu count
       if(bCmdUIMenu)
       {
          pcmdui->m_nIndex--; // point to last menu added
          pcmdui->m_nIndexMax = pcmdui->m_pMenu->GetMenuItemCount();
       }

      pcmdui->m_bEnableChanged = TRUE;    // all the added items are enabled
      */

   }

   LRESULT application::GetPaintMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
   {
   //    for(int i = 0; i < m_pha.get_size(); i++)
     //  {
       //    m_pha.element_at(i)->PaintHookGetPaintMsgProc(nCode, wParam, lParam);
       //}
       return 0;
   }

   void application::UpdateMRU(BOOL bEnable, int iCount)
   {
       if(m_pRecentFileList != NULL)
       {
   /*        CRecentFileList * plist = m_pRecentFileList;
           m_pRecentFileList = NULL;
           delete plist;*/
       }
       if(bEnable)
       {
   /*      m_pRecentFileList = new CRecentFileList(0, _afxFileSection, _afxFileEntry,
            iCount);
          m_pRecentFileList->ReadList();*/
       }

   }








   bool application::RestoreEnhancedMetaFiles()
   {
      ASSERT(FALSE);
/*      CreateFileFromRawResource(
         IDR_EMF_VMP447CV,
         "EMF",
         m_strModuleFolder + "vmp447cv.emf");
      CreateFileFromRawResource(
         IDR_EMF_VMPCOOLGRAY,
         "EMF",
         m_strModuleFolder + "vmpcoolgray.emf");
      CreateFileFromRawResource(
         IDR_EMF_VMP,
         "EMF",
         m_strModuleFolder + "vmsp.emf");
  */    
      return true;
   }

   void application::AddToRecentFileList(const char * lpszPathName) 
   {
      string str;
      GetPlaylistCentral().GetDefaultPath(str);
      if(System.file().path().is_equal(str, lpszPathName))
         return;
      userbase::application::AddToRecentFileList(lpszPathName);
      
   }

   CVmsTextDoc * application::OpenTextFile(const char * lpcsz)
   {
      return dynamic_cast < CVmsTextDoc * > (m_pvmstextdoctemplate->open_document_file(lpcsz));
   }



   void application::OnContextHelp() 
   {
      // TODO: add your command handler code here
      ca77::application::OnContextHelp();
   }



   ::userbase::document * application::GetXfplayerDoc()
   {
      return m_pxfplayerdoc;
   }

   void application::SetXfplayerDoc(::userbase::document *pdoc)
   {
      m_pxfplayerdoc = pdoc;
   }

   bool application::_001ProcessShellCommand(gen::command_line& rCmdInfo)
   {
      BOOL bResult = TRUE;
      switch (rCmdInfo.m_nShellCommand)
      {
      case gen::command_line::FileNew:
         if (!System._001SendCommand("file::new"))
            _001OnFileNew();
         if (GetMainWnd() == NULL)
            bResult = FALSE;
         break;

         // If we've been asked to open a file, call open_document_file()

      case gen::command_line::FileOpen:
         if (!_001OpenDocumentFile(rCmdInfo.m_varFile))
            bResult = FALSE;
         break;

         // If the ::fontopus::user wanted to print, hide our main ::ca::window and
         // fire a message to ourselves to start the printing

      case gen::command_line::FilePrintTo:
      case gen::command_line::FilePrint:
         m_nCmdShow = SW_HIDE;
         //ASSERT(m_pCmdInfo == NULL);
         open_document_file(rCmdInfo.m_varFile);
         //m_pcmdinfo = &rCmdInfo;
         GetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_PRINT_DIRECT);
         //m_pcmdinfo = NULL;
         bResult = FALSE;
         break;

         // If we're doing DDE, hide ourselves

      case gen::command_line::FileDDE:
   //      m_pCmdInfo = (CCommandLineInfo *) SW_SHOW;
         m_nDDECmdShow = SW_SHOW;
         //m_pCmdInfo = &command_line();
         m_nCmdShow = SW_HIDE;
         break;

      // If we've been asked to unregister, unregister and then terminate
      case gen::command_line::AppUnregister:
         {
            UnregisterShellFileTypes();
            BOOL bUnregistered = Unregister();

            // if you specify /EMBEDDED, we won't make an success/failure box
            // this use of /EMBEDDED is not related to OLE

            if (!rCmdInfo.m_bRunEmbedded)
            {
               /* linux
               if (bUnregistered)
                  System.simple_message_box(AFX_IDP_UNREG_DONE);
               else
                  System.simple_message_box(AFX_IDP_UNREG_FAILURE);
                  */
                
               if (bUnregistered)
                  System.simple_message_box(NULL, "System unregistered");
               else
                  System.simple_message_box(NULL, "Failed to unregister application");
            }
            bResult = FALSE;    // that's all we do

            // If nobody is using it already, we can use it.
            // We'll flag that we're unregistering and not save our state
            // on the way out. This new object gets deleted by the
            // cast object destructor.

            throw not_implemented_exception();
/*            if (m_pcmdinfo == NULL)
            {
               m_pcmdinfo = new gen::command_line;
               m_pcmdinfo->m_nShellCommand = gen::command_line::AppUnregister;
            }*/
         }
         break;
      }
      return bResult;
   }



   bool application::MessageWindowListener(
      UINT message,
      WPARAM wparam,
      LPARAM lparam)
   {
      musctrl::MusicalPlayerCentral & playercentral =
         musctrl::MusicalPlayerCentral::AppGetMusicalPlayerCentral(this);
      musctrl::single_document_template * pdoctemplate =
         playercentral.get_document_template();

   /*   if(ca77::application::MessageWindowListener(
         message, wparam, lparam))
         return true;*/
      switch(message)
      {
      case WM_APP:
         switch(wparam)
         {
         case 178:
            {
               ASSERT(FALSE);
               Scoring::UpdateMessage * lpsum = (Scoring::UpdateMessage *) lparam ;
   /*            XfplayerDoc * pdoc = (XfplayerDoc *) pdoctemplate->get_document(0);
               if(pdoc == NULL)
               {
                  delete lpsum;
                  return TRUE;
               }
               CAudioSpectrumViewUpdateHint uh;
               uh.m_lpwaveformatex = GetAudioWaveCentral().GetWaveIn()->GetFormatEx();         
               uh.m_dDeltaScore = lpsum->m_dDeltaScore;
               uh.m_dScoreAddUp = lpsum->m_dScoreAddUp;*/
               delete lpsum;
               lpsum = NULL;
   /*            ::userbase::document * pdoctarget = (::userbase::document *) pdoc->GetAudioSpectrumDoc();
               if(pdoctarget != NULL)
                  pdoctarget->update_all_views(NULL, 0, &uh);*/
               return TRUE;
            }
         default:
            break;
         }
      default:
         break;
      }

      return FALSE;
   }

   void application::GetDefaultSongFolderPath(string &strPath)
   {
      string str;
      throw not_implemented_exception();
       //str.load_string(IDS_FOLDER_SONGS);

      strPath = m_strModuleFolder;
      strPath += str;

   }

   void application::OnPlayer() 
   {
      XfplayerViewUpdateHint uh;
      uh.AddType(XfplayerViewUpdateHint::TypeShowPlayer);
      ::userbase::document_template * ptemplate = GetMusicalPlayerCentral().get_document_template();
      
      ptemplate->update_all_views(NULL, 0, &uh);

      if(!uh.m_bShowPlayer)
      {
         GetMusicalPlayerCentral().get_document_template()->open_document_file(NULL);
      }
      
   }


   BOOL application::OnDDECommand(LPTSTR lpszCommand) 
   {
      string strCommand = lpszCommand;
      ::document* pdoc = NULL;

      // open format is "[open("%s")]" - no whitespace allowed, one per line
      // print format is "[print("%s")]" - no whitespace allowed, one per line
      // print to format is "[printto("%s","%s","%s","%s")]" - no whitespace allowed, one per line
      //CCommandLineInfo cmdInfo;
      command_line().m_nShellCommand = gen::command_line::FileDDE;

      if (gen::str::begins_eat(strCommand, "[open(\""))
      {
         command_line().m_nShellCommand = gen::command_line::FileOpen;
      }
      else if(gen::str::begins_eat(strCommand, "[print(\""))
      {
         command_line().m_nShellCommand = gen::command_line::FilePrint;
      }
      else if(gen::str::begins_eat(strCommand, "[printto(\""))
      {
         command_line().m_nShellCommand = gen::command_line::FilePrintTo;
      }
      else
         return FALSE; // not a command we handle

      int i = strCommand.find('"');
      if (i == -1)
         return FALSE; // illegally terminated

      command_line().m_varFile = strCommand.Left(i);
      strCommand = strCommand.Right(strCommand.get_length() - i);

      gen::command_line* pOldInfo = NULL;
      BOOL bRetVal = TRUE;

      // If we were started up for DDE retrieve the Show state
/*      if (m_pcmdinfo != NULL)
      {
         m_nCmdShow = m_nDDECmdShow;
         //m_pm_cmdinfo = &command_line();
      }
      else
         pOldInfo = m_pCmdInfo;*/

      if (command_line().m_nShellCommand == gen::command_line::FileOpen)
      {

         // then open the document
         open_document_file(command_line().m_varFile);

         // show the application ::ca::window
         ::user::interaction * pMainWnd = GetMainWnd();
         int nCmdShow = m_nCmdShow;
         if (nCmdShow == -1 || nCmdShow == SW_SHOWNORMAL)
         {
            if (pMainWnd->IsIconic())
               nCmdShow = SW_RESTORE;
            else
               nCmdShow = SW_SHOW;
         }
         pMainWnd->ShowWindow(nCmdShow);
         if (nCmdShow != SW_MINIMIZE)
            pMainWnd->SetForegroundWindow();


         // next time, show the ::ca::window as default
         m_nCmdShow = -1;
         goto RestoreAndReturn;
      }

      if (command_line().m_nShellCommand == gen::command_line::FilePrintTo)
      {
         if (strCommand.Left(3) != _T("\",\""))
         {
            bRetVal = FALSE;
            goto RestoreAndReturn;
         }
         else
         {
            strCommand = strCommand.Right(strCommand.get_length() - 3);
            i = strCommand.find('"');
            if (i == -1)
            {
               bRetVal = FALSE;
               goto RestoreAndReturn;
            }
            else
            {
               command_line().m_strPrinterName = strCommand.Left(i);
               strCommand = strCommand.Right(strCommand.get_length() - i);
            }
         }

         if (strCommand.Left(3) != _T("\",\""))
         {
            bRetVal = FALSE;
            goto RestoreAndReturn;
         }
         else
         {
            strCommand = strCommand.Right(strCommand.get_length() - 3);
            i = strCommand.find('"');
            if (i == -1)
            {
               bRetVal = FALSE;
               goto RestoreAndReturn;
            }
            else
            {
               command_line().m_strDriverName = strCommand.Left(i);
               strCommand = strCommand.Right(strCommand.get_length() - i);
            }
         }

         if (strCommand.Left(3) != _T("\",\""))
         {
            bRetVal = FALSE;
            goto RestoreAndReturn;
         }
         else
         {
            strCommand = strCommand.Right(strCommand.get_length() - 3);
            i = strCommand.find('"');
            if (i == -1)
            {
               bRetVal = FALSE;
               goto RestoreAndReturn;
            }
            else
            {
               command_line().m_strPortName = strCommand.Left(i);
               strCommand = strCommand.Right(strCommand.get_length() - i);
            }
         }
      }

      // get document count before opening it
      int nOldCount; nOldCount = get_document_count();

      // open the document, then print it.
      pdoc = _001OpenDocumentFile(command_line().m_varFile);
   //m_pCmdInfo = &command_line();
      GetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_PRINT_DIRECT);
//      m_pCmdInfo = NULL;

      // close the document if it wasn't open previously (based on doc count)
      if (get_document_count() > nOldCount)
      pdoc->on_close_document();


   RestoreAndReturn:
      //m_pCmdInfo = pOldInfo;
      return bRetVal;

   }

   bool application::BeginVSeriesThreads()
   {
      {
           
           
         
         if(!(m_phighthread = AfxBeginThread < CVmpHighThread > (this)))
         {
            return FALSE;
         }

         GetAudioWaveCentral().Initialize(this);
   //   GetAudioWaveCentral().GetWaveIn()->open(GetPlusThread());

         //pruntimeclass = &typeid();
         if(!(m_pthreadV2 = AfxBeginThread < XfplayerThreadV2 >(this)))
         {
            return FALSE;
         }


   /*      pruntimeclass = &typeid(XfplayerThreadV3);
         if(!(m_pthreadV3 = dynamic_cast<XfplayerThreadV3 *>(AfxBeginThread(pruntimeclass))))
         {
            return FALSE;
         }

         m_pthreadV3->SetHighThread(GetHighThread());*/
      }

      return true;
   }

   CVmpHighThread * application::GetHighThread()
   {
      if(m_phighthread == NULL)
      {
         if(!(m_phighthread = AfxBeginThread < CVmpHighThread > (this)))
         {
            AfxPostQuitMessage(0);
         }
      }
      return m_phighthread;
   }


   XfplayerThreadV2 * application::GetThreadV2()
   {
      if(m_pthreadV2 == NULL)
      {
         if(!(m_pthreadV2 = AfxBeginThread < XfplayerThreadV2 > (this)))
         {
            AfxPostQuitMessage(0);
         }
      }


      return m_pthreadV2;
   }



   void application::VerifyBrowsers()
   {
      //CFileFind filefind;
      string str;
      string strDestination;
      string strSource;
      string strVersion;
      string strFormat;
      strSource = m_strModuleFolder + "npvmp.dll";
      win::registry reg;
      {
      HKEY hkeyMozilla = NULL;
      HKEY hkeyMozilla10 = NULL;
      HKEY hkeyMozilla11 = NULL;
      HKEY hkeyExtensions = NULL;
      if(ERROR_SUCCESS ==
         RegOpenKey(
            HKEY_LOCAL_MACHINE,
            "Software\\Mozilla",
            &hkeyMozilla))
      {
         if(ERROR_SUCCESS ==
            RegOpenKey(
               hkeyMozilla,
               "Mozilla 1.0",
               &hkeyMozilla10))
         {
            if(ERROR_SUCCESS ==
               RegOpenKey(
                  hkeyMozilla10,
                  "Extensions",
                  &hkeyExtensions))
            {
               if(reg.RegQueryValue(
                  hkeyExtensions,
                  "Plugins",
                  str))
               {
                  strDestination = str + "\\npvmp.dll";
                  if(!System.file().exists(strDestination))
                  {
                     if(IDYES == System.simple_message_box(NULL, "Mozilla 1.0 seems to be installed. Do you wish to install Veriwell Musical Player Plugin for Mozilla 1.0?", MB_ICONQUESTION | MB_YESNO))
                     {
                        if(CopyFile(strSource, strDestination, false))
                        {
                           System.simple_message_box(NULL, "You will need to restart Mozilla 1.0 for changes to take effect.", MB_ICONINFORMATION);
                        }
                        else
                        {
                           System.simple_message_box(NULL, "Could not instal the plugin.", MB_ICONINFORMATION);
                        }
                     }
                  }
               }
            
               RegCloseKey(hkeyExtensions);
            }
            RegCloseKey(hkeyMozilla10);
         }

         if(ERROR_SUCCESS ==
            RegOpenKey(
               hkeyMozilla,
               "Mozilla 1.1",
               &hkeyMozilla11))
         {
            if(ERROR_SUCCESS ==
               RegOpenKey(
                  hkeyMozilla11,
                  "Extensions",
                  &hkeyExtensions))
            {
               if(reg.RegQueryValue(
                  hkeyExtensions,
                  "Plugins",
                  str))
               {
                        strDestination = str + "\\npvmp.dll";
                        if(!System.file().exists(strDestination))
                        {
                           if(IDYES == System.simple_message_box(NULL, "Mozilla 1.1 seems to be installed. Do you wish to install Veriwell Musical Player Plugin for Mozilla 1.1?", MB_ICONQUESTION | MB_YESNO))
                           {
                              if(CopyFile(strSource, strDestination, false))
                              {
                                 System.simple_message_box(NULL, "You will need to restart Mozilla 1.1 for changes to take effect.", MB_ICONINFORMATION);
                              }
                              else
                              {
                                 System.simple_message_box(NULL, "Could not instal the plugin.", MB_ICONINFORMATION);
                              }
                           }
                        }
               }
            
               RegCloseKey(hkeyExtensions);
            }
            RegCloseKey(hkeyMozilla10);
         }
         RegCloseKey(hkeyMozilla);
      }   

      }





      // NETSCAPE
      {
      HKEY hkeyNetscape = NULL;
      HKEY hkeyNetscapeNavigator = NULL;
      HKEY hkeyNetscapeCurrent = NULL;
      HKEY hkeyNetscapeMain = NULL;

      if(ERROR_SUCCESS ==
         RegOpenKey(
            HKEY_LOCAL_MACHINE,
            "Software\\Netscape",
            &hkeyNetscape))
      {
         if(ERROR_SUCCESS ==
            RegOpenKey(
               hkeyNetscape,
               "Netscape Navigator",
               &hkeyNetscapeNavigator))
         {
            if(reg.RegQueryValue(
               hkeyNetscapeNavigator,
               "CurrentVersion",
               strVersion))
            {

               if(ERROR_SUCCESS ==
                  RegOpenKey(
                     hkeyNetscapeNavigator,
                     strVersion,
                     &hkeyNetscapeCurrent))
               {
                  if(ERROR_SUCCESS ==
                     RegOpenKey(
                        hkeyNetscapeCurrent,
                        "Main",
                        &hkeyNetscapeMain))
                  {
                     if(reg.RegQueryValue(
                        hkeyNetscapeMain,
                        "Install Directory",
                        str))
                     {
                        strDestination = str + "\\Program\\Plugins\\npvmp.dll";
                        if(!System.file().exists(strDestination))
                        {
                           strFormat.Format("Netscape Navigator %s seems to be installed in your computer. Do you wish to install Veriwell Musical Player Plugin for Netscape Navigator %s?", strVersion, strVersion);

                           if(IDYES == System.simple_message_box(NULL, strFormat, MB_ICONQUESTION | MB_YESNO))
                           {
                              if(CopyFile(strSource, strDestination, false))
                              {
                                 strFormat.Format("You will need to restart Netscape Navigator %s for changes to take effect.", strVersion);
                                 System.simple_message_box(NULL, strFormat, MB_ICONINFORMATION);
                              }
                              else
                              {
                                 System.simple_message_box(NULL, "Could not instal the plugin.", MB_ICONINFORMATION);
                              }
                           }
                        }
                     }
                     
                     RegCloseKey(hkeyNetscapeMain);
                  }
                  RegCloseKey(hkeyNetscapeCurrent);
               }
               RegCloseKey(hkeyNetscapeNavigator);
            }
            RegCloseKey(hkeyNetscape);
         }   
      
      }
      }
   }

   void application::data_on_after_change(gen::signal_object * pobj)
   {
      /*ca77::application::data_on_after_change(key, iLine, iColumn, puh);
      switch(iConfigurationId)
      {
      case _vmsdb::Configuration::CfgUserInterfaceLanguage:
         OnAfterLanguageChange(GetLanguage(), puh);
         break;
      case vmsp::Configuration::CfgKaraokeEncoding:
         OnAfterKaraokeEncodingChange(puh);
         break;
      case vmsp::Configuration::CfgMidiOutDevice:
         {
            int i;
            if(data_get(vmsp::Configuration::CfgMidiOutDevice, 0, 0, i))
            {
               _vmsmus::midi_central_container::AppGetMidiCentral().SetMidiOutDevice ((UINT) i);
            }
         }
         break;
      }*/
   }

   void application::SetKaraokeEnconding(DWORD dwCodePage)
   {

   /*   VmsDataServerInterface & db = GetVmsDataServerInterface();

      COleVariant var;

      var.vt = VT_I4;
      var.intVal = dwCodePage;

      db.set_data("KaraokeEncoding", GetLanguage(), 0, var);
   */
   }

   void application::OnAfterKaraokeEncodingChange(::database::update_hint * puh)
   {
      /*
      VmsDataServerInterface & db = GetVmsDataServerInterface();

      COleVariant var;
      var.vt = VT_I4;
      DWORD dwCodePage;

      if(db.get_data(vmsp::Configuration::CfgKaraokeEncoding, GetLanguage(), 0, var))
      {
         ASSERT(var.vt == VT_I4);
         dwCodePage = var.intVal;
         
         PostThreadMessage(
            APPM_LANGUAGE, 
            vmsp::Configuration::WPARAM_LANGUAGE_KARAOKEENCODING_UPDATE, 
            0);

      }
   */
   }

   DWORD application::GetKaraokeEncoding()
   {
   /*
      VmsDataServerInterface & db = GetVmsDataServerInterface();

      COleVariant var;
      var.vt = VT_I4;
      DWORD dwCodePage;

      if(db.get_data(vmsp::Configuration::CfgKaraokeEncoding, GetLanguage(), 0, var))
      {
         ASSERT(var.vt == VT_I4);
         dwCodePage = var.intVal;
         return dwCodePage;
      }
      else
         return CP_OEMCP;
   */
      return 0;
   }

   void application::OnToolsOptionsFileAssociations() 
   {
      CToolsOptionsDoc * pdoc = 
         dynamic_cast < CToolsOptionsDoc * > (m_pdoctemplateFileAssociations->open_document_file(NULL));

   }

   void application::OnToolsOptionsSongDirectories() 
   {
      CToolsOptionsDoc * pdoc = 
         dynamic_cast < CToolsOptionsDoc * > (m_pdoctemplateSongDirectories->open_document_file(NULL));
      
   }


   // App command to run the dialog
   void application::OnAppAbout()
   {
   }



   void application::OnFileOpenCd() 
   {
      m_pdoctemplateCDBrowse->open_document_file(NULL);
      
   }

   vmsp::notify_icon * application::GetNotifyIcon()
   {
      return m_pnotifyicon;
   }

   bool application::_001OnUpdateCmdUi(cmd_ui * pcmdui)
   {
      if(pcmdui->m_id == "tools::album")
      {
         pcmdui->Enable();
         return true;
      }
      else if(pcmdui->m_id == "file::open")
      {
         pcmdui->Enable();
         return true;
      }
      return ca84::application::_001OnUpdateCmdUi(pcmdui);;
   }

   bool application::_001OnCommand(class id id)
   {
      if(id == "tools::album")
      {
         ViewToolsAlbum();
         return true;
      }
      else if(id == "file::open")
      {
         on_file_open();
         return true;
      }
      return ca84::application::_001OnCommand(id);
   }







   ::document * application::_001OpenDocumentFile(var varFile)
   {
      return GetMusicalPlayerCentral().get_document_template()->open_document_file(varFile);   
   }


   void application::_001OnFileOpen(gen::signal_object * pobj)
   {
      on_file_open();
      pobj->m_bRet = true;
   }

} // namespace vmsp

