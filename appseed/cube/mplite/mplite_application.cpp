#include "StdAfx.h"

#include "libcharguess/libcharguess.h"
#include "userbase/userbase_image_manager.h"
#include "file_association.h"     

#include "MediaLibraryDoc.h"
#include "MediaLibraryView.h"
#include "MediaLibraryChildFrame.h"
#include "MediaLibraryListView.h"
#include "MediaLibraryExplorerView.h"

#include "mplite_library_view.h"
#include "mplite_library_tree_view.h"
#include "mplite_library_list_view.h"

#include "OptionsDoc.h"
#include "OptionsChildFrame.h"
#include "OptionsView.h"
#include "OptionsFileAssociationView.h"
#include "OptionsFoldersView.h"
#include "OptionsKaraokeView.h"


#include "RecentFileList.h"

#include "MusicalPlayerLightDB.h"

#include "OptionsAudioDevicesView.h"

namespace mplite
{

   application::application()
   {
      m_pdocmanager = NULL;
   }

   application::~application()
   {
   }


   void application::construct()
   {
      //m_pszAppName         = _strdup("mplite");
      m_strLicense         = "mplite";
      m_strBaseSupportId   = "votagus_ca2_mplite";
      m_eexclusiveinstance = ::radix::ExclusiveInstanceNone; // oldly Global because audio devices globals
      m_lpoptionsdialog    = NULL;
      m_pdatabase          = NULL;
      m_pfileassociation   = NULL;
      m_precentfilelist    = NULL;
      
      // DDE variables
      m_hszAppName         = NULL;
      m_hszSystemTopic     = NULL;

      m_strInstallToken    = "mplite";
   }


   bool application::initialize_instance()
   {
      System.factory().creatable_small < OptionsAudioDevicesView > ();
      System.factory().creatable_small < document > ();
      System.factory().creatable_small < main_frame > ();
      System.factory().creatable_small < mplite::pane_view > ();
      System.factory().creatable_small < view > ();
      System.factory().creatable_small < MediaLibraryDoc > ();
      System.factory().creatable_small < MediaLibraryChildFrame > ();
      System.factory().creatable_small < MediaLibraryView > ();
      System.factory().creatable_small < MediaLibraryListView > ();
      System.factory().creatable_small < MediaLibraryExplorerView > ();
      System.factory().creatable_small < OptionsDoc > ();
      System.factory().creatable_small < OptionsChildFrame > ();
      System.factory().creatable_small < OptionsView > ();
      System.factory().creatable_small < OptionsFileAssociationView > ();
      System.factory().creatable_small < OptionsFoldersView > ();
      System.factory().creatable_small < OptionsKaraokeView > ();

      System.factory().creatable_small < mplite::command_frame > ();
      System.factory().creatable_small < mplite::command_document > ();
      System.factory().creatable_small < mplite::command_view > ();

      System.factory().creatable_small < library::view > ();
      System.factory().creatable_small < library::tree_view > ();
      System.factory().creatable_small < library::list_view > ();


      ::SetPriorityClass(::GetCurrentProcess(), HIGH_PRIORITY_CLASS);

      m_dataid = "VmpLightApp";
      connect_update_cmd_ui("view_encoding", &application::_001OnUpdateViewEncoding);

      AddCodePage(
         1252, // Latin1
         "view_encoding:Latin1",
         "IDS_VIEW_ENCODING_LATIN1");

      AddCodePage(
         950, // BIG 5
         "view_encoding:BIG 5",
         "IDS_VIEW_ENCODING_BIG5");

      AddCodePage(
         51932, // Japanese (EUCJP)
         "view_encoding:Japanese (EUCJP)",
         "IDS_VIEW_ENCODING_SHIFTEUCJP");

      AddCodePage(
         50220, // Japanese (IS02022JP)
         "view_encoding:Japanese (IS02022JP)",
         "IDS_VIEW_ENCODING_ISO2022JP");

      AddCodePage(
         932, // Japanese (ShiftJIS)
         "view_encoding:Japanese (ShiftJIS)",
         "IDS_VIEW_ENCODING_SHIFTJIS");

      AddCodePage(
         10001, // Japanese (Mac)
         "view_encoding:Japanese (Mac)",
         "IDS_VIEW_ENCODING_MACJP");
      
      AddCodePage(
         77777, // Auto detect
         "view_encoding:Autodetect",
         "IDS_VIEW_ENCODING_AUTODETECT");


      if(!ca84::application::initialize_instance())
         return false;

      InitializeResourceId();

      if(!mediamanager::mediamanager_container::initialize_container(this))
         return false;

      if(!PlaylistCentralContainer::initialize(this))
         return false;

   //   audio_decode::g_pfactory->SetFactoryImpl(new notsad_win::Factory());

      
      /* linux
      GetMixerVisualCentral().m_uiIdPlaybackIcon  = IDI_MIXER_PLAYBACK;
      GetMixerVisualCentral().m_uiIdPlaybackTab   = IDS_MIXER_PLAYBACK_TAB;
      GetMixerVisualCentral().m_uiIdRecordingIcon = IDI_MIXER_RECORDING;
      GetMixerVisualCentral().m_uiIdRecordingTab  = IDS_MIXER_RECORDING_TAB;
      */

      GetMixerVisualCentral().m_idPlaybackIcon  = "mixer\\icon_playback.png";
      GetMixerVisualCentral().m_idPlaybackTab   = "<string id='mplite:mixer_playback_tab'>Playback</string>";
      GetMixerVisualCentral().m_idRecordingIcon = "mixer\\icon_recording.png";
      GetMixerVisualCentral().m_idRecordingTab  = "<string id='mplite:mixer_recording_tab'>Recording</string>";

//      DWORD dw = ::_getmbcp();

   //   AfxDebugBreak();

      string strKey("veriwell\\Musical Player\\");
      strKey += get_version();
      SetRegistryKey(strKey);

      string strPath = GetProfileString("language", "resource path", "");
      //VERIFY(SetLanguageResourcePath(strPath));


      if(!midi_central_container::initialize_central_container(this))
      {
         return false;
      }

      if(!MusicalPlayerCentralContainer::Initialize(this))
      {
         return false;
      }

      win::registry::Key keyFirefox;
      if(keyFirefox.OpenKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Mozilla\\Mozilla Firefox", false))
      {
         string strFirefoxCurrentVersion;
         if(keyFirefox.QueryValue("CurrentVersion", strFirefoxCurrentVersion))
         {
            strFirefoxCurrentVersion = strFirefoxCurrentVersion.Mid(0, max(strFirefoxCurrentVersion.find(" "), 0));
            string strExtensionsFolderKey;
            win::registry::Key keyExtensions;
            if(keyExtensions.OpenKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Mozilla\\Mozilla Firefox " + strFirefoxCurrentVersion + "\\extensions", false))
            {
               string strExtensionsFolder;
               if(keyExtensions.QueryValue("Plugins", strExtensionsFolder))
               {
                  string strPlugin;
                  strPlugin = strExtensionsFolder + "\\npmplite.dll";
                  if(!System.file().exists(strPlugin))
                  {
                     string strPluginSrc;
                     strPluginSrc = m_strModuleFolder + "npmplite.dll";
                     TRACE("SourceFile: %s\n", strPluginSrc);
                     ::CopyFile(strPluginSrc, strPlugin, false);
                  }
               }
            }
         }
      }

      // 2010-09-23 by qamilox@uol.com.br
      // vmsbasewnd???!?

      // Register your unique class name that you wish to use
      /*WNDCLASS wndcls;

      memset(&wndcls, 0, sizeof(WNDCLASS));   // start with NULL
                                               // defaults

      wndcls.style = CS_GLOBALCLASS | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;

      //you can specify your own ::ca::window procedure
      wndcls.lpfnWndProc = ::DefWindowProc; 
      wndcls.hInstance = System.m_hInstance;
      wndcls.hIcon = NULL; // LoadIcon(IDR_MAINFRAME); // or load a different icon
      wndcls.hCursor = NULL; //LoadCursor( IDC_ARROW );
      wndcls.hbrBackground = NULL; // (HBRUSH) (COLOR_WINDOW + 1);
      wndcls.lpszMenuName = NULL;

      // Specify your own class name for using FindWindow later
      wndcls.lpszClassName = "vmsbasewnd";

   //   AfxDebugBreak();

      // Register the new class and exit if it fails
      if(!AfxRegisterClass(&wndcls))
      {
         TRACE("Class Registration Failed\n");
         return false;
      }*/

      LibCharGuess::Init();


      gen::command_line cmdInfo;
      _001ParseCommandLine(cmdInfo);


      if(!mediamanager::get(this)->Initialize())
      {
         return false;
      }


      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";
      GetStdFileManagerTemplate()->m_strToolBar = "mplite\\filemanager_toolbar.xml";
      GetStdFileManagerTemplate()->m_strDialogBar = "IDR_FILEMANAGER_DIALOGBAR";
      GetStdFileManagerTemplate()->m_strMenuBar = "IDR_FILEMANAGER_OPENMUSIC";
      //GetStdFileManagerTemplate()->m_strFilePopup = IDR_POPUP_FILEOPEN_ITEM;
      GetStdFileManagerTemplate()->m_strFilePopupSubstId = "ID_SUBST_SO_SHELL_MENU";
   //   GetStdFileManagerTemplate()->m_uiFolderPopup = IDR_POPUP_FILEOPEN_DIRECTORY;
      //GetStdFileManagerTemplate()->m_strPopup = IDR_POPUP_FILEOPEN;
      GetStdFileManagerTemplate()->m_idExpandBox = "IDI_FILEMANAGER_EXPANDBOX";
      GetStdFileManagerTemplate()->m_idCollapseBox = "IDI_FILEMANAGER_COLLAPSEBOX";
      GetStdFileManagerTemplate()->m_pfilelistcallback = new filelist_callback(this);

      m_pimagemanager = new ::userbase::image_manager();


      if(!InitializeLocalDataCentral())
      {
         simple_message_box(NULL, "Could not initialize Local data central");
         return false;
      }


      /*MessageFilterHookManager * pmfmh;
      if(MessageFilterHookManager::AppGetMessageFilterHookManager(&pmfmh))
      {
         pmfmh->MessageFilterHook();
      }*/


   //   BaseMenuCentral::SetMenuCentral(new BaseMenuCentral());
     // BaseMenuCentral::GetMenuCentral()->m_papp = this;
      /*xxxUINT uiaMenuMap [][2] =
      {
         {ID_LANGUAGE_CHANGE           , IDI_LANGUAGE_CHANGE},
         {ID_VIEW_FULLSCREEN           , IDI_VIEW_FULLSCREEN},
         {ID_FILE_OPEN_EX              , IDI_FILE_OPEN_EX},
         {ID_FILE_OPEN                 , IDI_FILE_OPEN_EX},
         {ID_FILE_ADD                  , IDI_FILE_ADD},
         {ID_EDIT_REMOVE               , IDI_EDIT_REMOVE},
         {ID_KARAOKE_GRADUAL_FILLING   , IDI_KARAOKE_GRADUAL_FILLING},
         {ID_KARAOKE_BOUNCING_BALL     , IDI_KARAOKE_BOUNCING_BALL},
         {ID_EXECUTE_PLAY              , IDI_EXECUTE_PLAY},
         {ID_EXECUTE_STOP              , IDI_EXECUTE_STOP},
         {ID_EXECUTE_PAUSE             , IDI_EXECUTE_PAUSE},
         {ID_EXECUTE_MINUS_ONE         , IDI_EXECUTE_MINUS_ONE},
         {ID_VIEW_KARAOKE              , IDI_VIEW_KARAOKE},
         {ID_VIEW_PLAYLIST             , IDI_VIEW_PLAYLIST},
         {ID_VIEW_ALBUM                , IDI_VIEW_ALBUM},
         {ID_APP_EXIT                  , IDI_APP_EXIT},
         {-1, -1}
      };*/

      //xxxGetImageManager().Initialize(uiaMenuMap);
      UINT ui1;
      GetImageManager().m_rel.Lookup("ID_FILE_OPEN_EX", ui1);
      //xxxBaseMenuCentral::GetMenuCentral()->MenuV033CreateImageMap(uiaMenuMap);


      string strCommandImage = System.dir().matter("command_image.xml");
      strCommandImage = Application.file().as_string(strCommandImage);
      xml::node node(get_app());
      node.load(strCommandImage);
      BaseMenuCentral::GetMenuCentral(this)->MenuV033AddImageMap(&node);


      System.font_central().Initialize();
      System.font_central().CreateLyricViewFonts();

   /*   GetMusicalPlayerCentral().m_pruntimeclassDocument = &typeid(document);
      GetMusicalPlayerCentral().m_typeinfoFrameWnd = &typeid(CMainFrame);
      GetMusicalPlayerCentral().m_typeinfoView = &typeid(CMPLightView);
      GetMusicalPlayerCentral().m_pruntimeclassIPFrame = &typeid(CInPlaceFrame);
      GetMusicalPlayerCentral().m_uiResourceId = IDR_MAINFRAME;
      GetMusicalPlayerCentral().m_uiResourceIdEmbedding = IDR_SRVR_EMBEDDED;
      GetMusicalPlayerCentral().m_uiResourceIdInPlace = IDR_SRVR_INPLACE;
      GetMusicalPlayerCentral().CreateDocTemplate();

      add_document_template(GetMusicalPlayerCentral().CreateDocTemplate());*/


      CreateDocumentTemplates();
      UpdateRegistry();



      GetPlaylistCentral().m_strMatter = "mplite/playlist";
      GetPlaylistCentral().m_typeinfoFrameWnd = &typeid(PlaylistFrame);
      GetPlaylistCentral().m_typeinfoView = &typeid(PlaylistListView);
      m_pplaylistcentralcallback = new playlist_central_callback(this);
      if(!GetPlaylistCentral().Initialize(this, m_pplaylistcentralcallback))
      {
         simple_message_box(NULL, "Failed to initialize Playlist Central");
         return false;
      }



      LoadStdProfileSettings();  // Load standard INI file options (including MRU)



      // Register the application's document templates.  ::userbase::document templates
      //  serve as the connection between documents, frame windows and views.

   /*   single_document_template* pDocTemplate;
      pDocTemplate = new single_document_template(
         IDR_MAINFRAME,
         &typeid(document),
         &typeid(CMainFrame),       // main SDI frame ::ca::window
         &typeid(CMPLightView));
      pDocTemplate->SetServerInfo(
         IDR_SRVR_EMBEDDED, IDR_SRVR_INPLACE,
         &typeid(CInPlaceFrame));*/
   //   add_document_template(pDocTemplate);

      CreateTemplates();


      // Connect the COleTemplateServer to the document template.
      //  The COleTemplateServer creates new documents on behalf
      //  of requesting OLE containers by using information
      //  specified in the document template.
      //m_server.ConnectTemplate(clsid, pDocTemplate, TRUE);
         // Note: SDI applications register server objects only if /Embedding
         //   or /Automation is present on the command line.

      // Enable DDE Execute open

      _001EnableShellOpen();
      RegisterShellFileTypes(TRUE);

      m_dwDde = 0;
      if(!DdeInitializeW(&m_dwDde,         // receives instance identifier 
         (PFNCALLBACK) DdeCallback, // pointer to callback function 
         //CBF_FAIL_EXECUTES |        // filter XTYPE_EXECUTE 
         APPCMD_FILTERINITS, // filter notifications 
         0))
      {
         m_hszAppName = DdeCreateStringHandleW(m_dwDde, L"vmpLight", 0);
         m_hszSystemTopic = DdeCreateStringHandleW(m_dwDde, L"System", 0);
         DdeNameService(m_dwDde, m_hszAppName, 0, DNS_REGISTER);
      }
      

   //   AfxDebugBreak();


      m_bInline = false;
      m_pfileassociation = new vmplite::file_association(this);
      m_pfileassociation->CheckAssociations();

      data_pulse_change("MidiOutDevice", ::ca::system::idEmpty, NULL);

      return true;
   }



   /////////////////////////////////////////////////////////////////////////////
   // application message handlers


/*      void application::SetLanguage(enum gen::application::ELanguage)
      {
      }
      enum gen::application::ELanguage application::GetLanguage()
      {
         return langDefault;
      }
      enum gen::application::ELanguage application::GetDefaultLanguage()
      {
         return langDefault;
      }
      bool application::MessageWindowListener(unsigned int,unsigned int,long)
      {
         return true;
      }

   void application::OnToolsOptions() 
   {
   /*   m_lpoptionsdialog = new OptionsDialog();
      m_lpoptionsdialog->create(IDD_OPTIONS, NULL);*/
      
  // }

   void application::RegisterShellFileTypes(BOOL bCompat)
   {
      return;

      string strPathName, strTemp, strResourcePathName;
    
      strPathName = get_module_folder();

      stringa strarray;

      string str;

      throw not_implemented_exception();
      /*
      str.load_string(IDS_MID);
      strarray.add(str);
      str.load_string(IDS_KAR);
      strarray.add(str);
      str.load_string(IDS_ST3);
      strarray.add(str);
      */
      string_tokenizer strTokenizer;

      strTokenizer = str;

      stringa strarrayDocString;


   //   _vmsp::file_association fileassociation;

      for (int iTemplate = 0; iTemplate < strarray.get_size(); iTemplate++)
      {
         strarrayDocString.remove_all();
         strarrayDocString.add_tokens(strarray[iTemplate],"\n", true);
         
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
               strIconIndex.Format(document_manager::_afxIconIndexFmt, nIconIndex);
               DestroyIcon(hIcon);
            }
            else
            {
               strIconIndex.Format(document_manager::_afxIconIndexFmt, DEFAULT_ICON_INDEX);
            }
            strDefaultIconCommandLine += strIconIndex;
         }

         string strFilterExt, strFileTypeId, strFileTypeName;
         strFileTypeId = strarrayDocString[document_template::regFileTypeId];
         if (!strFileTypeId.is_empty())
         {
            strFileTypeName = strarrayDocString[document_template::regFileTypeName];
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
               strTemp.Format(document_manager::_afxDefaultIconFmt, (const char *)strFileTypeId);
               if (!_AfxSetRegKey(strTemp, strDefaultIconCommandLine))
                  continue;       // just skip it
            }

            strTemp = strarrayDocString[document_template::windowTitle];
            // If MDI System
            if (strTemp.is_empty())
            {
               // path\shell\open\ddeexec = [open("%1")]
               strTemp.Format(document_manager::_afxShellOpenFmt, (const char *)strFileTypeId,
                  (const char *)document_manager::_afxDDEExec);
               if (!_AfxSetRegKey(strTemp, document_manager::_afxDDEOpen))
                  continue;       // just skip it

               if (bCompat)
               {
                  // path\shell\print\ddeexec = [print("%1")]
                  strTemp.Format(document_manager::_afxShellPrintFmt, (const char *)strFileTypeId,
                     (const char *)document_manager::_afxDDEExec);
                  if (!_AfxSetRegKey(strTemp, document_manager::_afxDDEPrint))
                     continue;       // just skip it

                  // path\shell\printto\ddeexec = [printto("%1","%2","%3","%4")]
                  strTemp.Format(document_manager::_afxShellPrintToFmt, (const char *)strFileTypeId,
                     (const char *)document_manager::_afxDDEExec);
                  if (!_AfxSetRegKey(strTemp, document_manager::_afxDDEPrintTo))
                     continue;       // just skip it

                  // path\shell\open\command = path /dde
                  // path\shell\print\command = path /dde
                  // path\shell\printto\command = path /dde
                  strOpenCommandLine += document_manager::_afxDDEArg;
                  strPrintCommandLine += document_manager::_afxDDEArg;
                  strPrintToCommandLine += document_manager::_afxDDEArg;
               }
               else
               {
                  strOpenCommandLine += document_manager::_afxOpenArg;
               }
            }
            else
            {
               // path\shell\open\command = path filename
               // path\shell\print\command = path /p filename
               // path\shell\printto\command = path /pt filename printer driver port
               strOpenCommandLine += document_manager::_afxOpenArg;
               if (bCompat)
               {
                  strPrintCommandLine += document_manager::_afxPrintArg;
                  strPrintToCommandLine += document_manager::_afxPrintToArg;
               }
            }

            // path\shell\open\command = path filename
            strTemp.Format(document_manager::_afxShellOpenFmt, (const char *)strFileTypeId,
               (const char *)document_manager::_afxCommand);
            if (!_AfxSetRegKey(strTemp, strOpenCommandLine))
               continue;       // just skip it

            if (bCompat)
            {
               // path\shell\print\command = path /p filename
               strTemp.Format(document_manager::_afxShellPrintFmt, (const char *)strFileTypeId,
                  (const char *)document_manager::_afxCommand);
               if (!_AfxSetRegKey(strTemp, strPrintCommandLine))
                  continue;       // just skip it

               // path\shell\printto\command = path /pt filename printer driver port
               strTemp.Format(document_manager::_afxShellPrintToFmt, (const char *)strFileTypeId,
                  (const char *)document_manager::_afxCommand);
               if (!_AfxSetRegKey(strTemp, strPrintToCommandLine))
                  continue;       // just skip it
            }
            strFilterExt = strarrayDocString[document_template::filterExt];
               string_tokenizer strtokenizer;
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
                         strTemp.Format(document_manager::_afxShellNewFmt, (const char *)strFilterExt);
                         (void)_AfxSetRegKey(strTemp, document_manager::_afxShellNewValue, document_manager::_afxShellNewValueName);
                      }
                   }
                       else
                       {
                       }
                   }
            }
         }
   //      fileassociation.UpdateServerRegistration(strarray[iTemplate]);
      }
   }

   /*
   void application::OnEvent(_vmsdb::EDBEvent eevent, LPARAM lparam)
   {
      switch(eevent)
      {
      case _vmsdb::DBEventGetDefaultImageDirectorySet:
         {
            stringa * pwstra = (stringa *) lparam;
            ASSERT_VALID(pwstra);

            string str;
            string str;
            string strPath;

            simpledb::ca::application * papp = (simpledb::ca::application *) this;
            string strModuleFolder(m_strModuleFolder);
            // xxx str.load_string(IDS_FOLDER_IMAGES);
            str = strModuleFolder;
            str += "Images";
            strPath += str;

            gen::international::ACPToUnicode(str, strPath);
            pwstra->add(str);

            char buffer[MAX_PATH * 2];
            GetWindowsDirectory(buffer, sizeof(buffer));
            string strWallpaper(buffer);
            strWallpaper += "\\Web\\Wallpaper";
            
            gen::international::ACPToUnicode(str, strWallpaper);
            pwstra->add(str);

         }
         break;
      }
   }
   */

   BOOL application::OnDDECommand(LPTSTR lpszCommand) 
   {
      if (m_pdocmanager != NULL)
         return m_pdocmanager->OnDDECommand(lpszCommand);
      else
         return FALSE;
   //   return gen::application::OnDDECommand(lpszCommand);
   }


   HDDEDATA CALLBACK application::DdeCallback(
      UINT uType,
      UINT uFmt,
      HCONV hconv,
      HDDEDATA hsz1,
      HDDEDATA hsz2,
      HDDEDATA hdata,
      HDDEDATA dwData1,
      HDDEDATA dwData2
      )
   { 
      UNREFERENCED_PARAMETER(uFmt);
      UNREFERENCED_PARAMETER(hconv);
      UNREFERENCED_PARAMETER(dwData1);
      UNREFERENCED_PARAMETER(dwData2);
      switch (uType) 
      { 
      case XTYP_REGISTER: 
      case XTYP_UNREGISTER: 
         return (HDDEDATA) NULL; 
    
      case XTYP_ADVDATA: 
         return (HDDEDATA) DDE_FACK; 
    
      case XTYP_XACT_COMPLETE: 
         return (HDDEDATA) NULL; 
         
      case XTYP_CONNECT: 
      {
         application * papp = dynamic_cast < application * > (::ca::get_thread()->m_papp->m_psystem);
         if(!DdeCmpStringHandles((HSZ) hsz1, papp->m_hszSystemTopic))
         {
            if(!DdeCmpStringHandles((HSZ) hsz2, papp->m_hszAppName))
            {
               return (HDDEDATA) TRUE; 
            }
         }
         return (HDDEDATA) FALSE; 
      }
      
      case XTYP_DISCONNECT: 
         return (HDDEDATA) NULL; 
    
      case XTYP_EXECUTE: 
      {
         // get the command string
         DWORD dwSize = DdeGetData(
            hdata,
            NULL, 
            0, 
            0);
         
         string str;
         
         dwSize = DdeGetData(
            hdata,
            (LPBYTE) str.GetBuffer(dwSize), 
            dwSize, 
            0);
         
         str.ReleaseBuffer();
         
         throw not_implemented_exception();
         /*
         // execute the command
         if (!System.OnDDECommand( (LPTSTR)(const wchar_t *)str))
            TRACE1("Error: failed to execute DDE command '%S'.\n", str);
         */
         // 
         VERIFY(DdeFreeDataHandle(hdata));            
         return (HDDEDATA) NULL; 
      }

      default: 
         return (HDDEDATA) NULL; 
      } 
   } 

   void application::ProcessCommandLine(const wchar_t * lpwstr)
   {
      UNREFERENCED_PARAMETER(lpwstr);
      gen::command_line rCmdInfo;

   /*   int numargs;
      int numchars;
      wparse_cmdline(
         (wchar_t *) lpwstr, 
         NULL, 
         NULL,
         &numargs,
         &numchars);

      m_pszCmdLine = new WCHAR[numchars];
      m_argv = new WCHAR*[numargs];

      wparse_cmdline(
         (wchar_t *) lpwstr, 
         m_argv, 
         m_pszCmdLine,
         &numargs,
         &numchars);

      m_argc = numargs - 1;

      for (int i = 1; i < m_argc; i++)
      {
         const wchar_t * pszParam = m_argv[i];
         BOOL bFlag = FALSE;
         BOOL bLast = ((i + 1) == m_argc);
         if (pszParam[0] == '-' || pszParam[0] == '/')
         {
            // remov flag specifier
            bFlag = TRUE;
            ++pszParam;
         }
         rCmdInfo.ParseParam(pszParam, bFlag, bLast);
      }

      _001ProcessShellCommand(rCmdInfo);*/
   }


   void application::GetAvailableLanguages(stringa &stra)
   {

      string strPathName;

      strPathName = get_module_folder();

      stringa wstraFilter;

      wstraFilter.add("*.dll");

      string str;
      str = strPathName;

      str += "language\\";

      stringa wstraBase;
      wstraBase.add(str);
      bool_array baBase;
      baBase.add(false);

      ex2::file_set_sp fileset(get_app());

      fileset->add_search(wstraBase, baBase);
      fileset->add_filter(wstraFilter);
      
      string wstrFile;
      stra.remove_all();
      for(int i = 0; i < fileset->get_file_count(); i++)
      {
         fileset->file_at(i, wstrFile);
         stra.add(wstrFile);
      }
      /*string wstr1;
      wstr1 = str + L"language\\vmslightptbr.dll";
      stra.add(wstr1);

      string wstr2;
      wstr1 = str + L"language\\vmslightjp.dll";
      stra.add(wstr1);*/

   }

   void application::OnUpdatePopupMenu(cmd_ui *pcmdui)
   {
      if(pcmdui->m_id == "tools::language_change")
      {
   //      MENUITEMINFO mii;
         
   /*      ::userbase::menu * pmenu = pcmdui->m_pMenu;
         
         pmenu->DeleteMenu(pcmdui->m_nID, MF_BYCOMMAND);
         
         UINT uiId = ID_LANGUAGE_CHANGE1;
         pmenu->InsertMenu(pcmdui->m_nIndex++,
            MF_BYPOSITION,
            uiId,
            "English");
         uiId++;
         
         stringa stra;
         GetAvailableLanguages(stra);
         
         m_straLanguagePath.remove_all();

         string str;
         for(int i = 0; i < stra.get_size(); i++, uiId++)
         {
            
            HINSTANCE hinst = win::LoadLibrary(stra[i]);
            if(hinst == NULL)
               continue;
            if(!str.load_string(hinst, IDS_VIEW_LANGUAGE))
               continue;
            
            m_straLanguagePath.add(stra[i]);

            ::InsertMenuW(
               pmenu->GetSafeHmenu(),
               pcmdui->m_nIndex++,
               MF_BYPOSITION,
               uiId,
               str);
            
         }
         pcmdui->m_nIndex--;
         
         pcmdui->m_nIndexMax = pmenu->GetMenuItemCount();

         pcmdui->m_bContinueRouting = TRUE;*/
         
      }
      

   }

   bool application::SetLanguageResourcePath(const char * lpcsz)
   {
      if(lpcsz == NULL || lstrlenA(lpcsz) <= 0)
      {
         m_strLanguagePath = "";
//         AfxSetResourceHandle(m_hInstance);
      }
      else
      {
         HMODULE hmodule = ::LoadLibrary(lpcsz);
         if(hmodule == NULL)
            return false;
         m_strLanguagePath = lpcsz;
  //       AfxSetResourceHandle(hmodule);
      }
      WriteProfileString("language", "resource path", lpcsz);
      SendMessageToWindows(APPM_LANGUAGE, 0, 0);
      return true;
   }

   /*void application::OnLanguageChange(UINT uiId) 
   {
      int i = uiId - ID_LANGUAGE_CHANGE1;
      if(i == 0)
      {
         SetLanguageResourcePath("");
      }
      else
      {
         string str(m_straLanguagePath[i - 1]);
         SetLanguageResourcePath(str);
      }
   }

   void application::OnUpdateLanguageChange(cmd_ui * pcmdui) 
   {
      if(pcmdui->m_id == "tools::language_change")
      {
         ::userbase::menu_button_cmd_ui * pcmdui1 = dynamic_cast < ::userbase::menu_button_cmd_ui * > (pcmdui);
         if(pcmdui1 != NULL)
         {
            ::userbase::menu_item_ptra * pitema = pcmdui1->m_pitema;

            
   //         pmenu->DeleteMenu(pcmdui->m_nID, MF_BYCOMMAND);

            int iStartIndex = pcmdui->m_nIndex;
            
            int iIndex = iStartIndex;
            ::userbase::menu_item * pitem = new ::userbase::menu_item(this);
            pitem->m_id = id("tools::language_change1");
            pitem->m_button._001SetButtonText("English");
            pitem->m_iLevel = pitema->m_pitemContainer != NULL ? pitema->m_pitemContainer->m_iLevel + 1 : 0;
            pitema->set_at(iIndex, pitem);
   //xxx         uiId++;
            iIndex++;
            
            stringa stra;
            GetAvailableLanguages(stra);
            
            m_straLanguagePath.remove_all();

            string str;
            string str;
            for(int i = 0; i < stra.get_size(); i++) // , uiId++)
            {
               pitem = new ::userbase::menu_item(this);
               HINSTANCE hinst = win::LoadLibrary(stra[i]);
               if(hinst == NULL)
                  continue;
               if(!str.load_string(hinst, IDS_VIEW_LANGUAGE))
                  continue;
               
               m_straLanguagePath.add(stra[i]);

               //pitem->m_id = uiId;
               pitem->m_button._001SetButtonText("English");
               pitem->m_iLevel = pitema->m_pitemContainer != NULL ? pitema->m_pitemContainer->m_iLevel + 1 : 0;
               pitema->insert_at(iIndex, pitem);
               iIndex++;
               
            }
            pcmdui->m_nIndex = iStartIndex;
            
            pcmdui->m_nIndexMax = pitema->get_size();

      ////      pcmdui->m_bContinueRouting = TRUE;
            pcmdui->Enable(!m_strLanguagePath.is_empty());    // all the added items are enabled
            
         }
         else
         {

            ::userbase::menu * pmenu = pcmdui->m_pMenu;

            if(pcmdui->m_pSubMenu != NULL)
            {
               pmenu = pcmdui->m_pSubMenu;
            }
            
   /*         pmenu->DeleteMenu(pcmdui->m_nID, MF_BYCOMMAND);

            int iStartIndex = pcmdui->m_nIndex;
            
            UINT uiId = ID_LANGUAGE_CHANGE1;
            pmenu->InsertMenu(pcmdui->m_nIndex++,
               MF_BYPOSITION,
               uiId,
               "English");
            uiId++;
            
            stringa stra;
            GetAvailableLanguages(stra);
            
            m_straLanguagePath.remove_all();

            string str;
            for(int i = 0; i < stra.get_size(); i++, uiId++)
            {
               
               HINSTANCE hinst = win::LoadLibrary(stra[i]);
               if(hinst == NULL)
                  continue;
               if(!str.load_string(hinst, IDS_VIEW_LANGUAGE))
                  continue;
               
               m_straLanguagePath.add(stra[i]);

               SimpleMenu::_InsertMenuItem(
                  *pcmdui->m_pMenu,
                  *pmenu,
                  pcmdui->m_nIndex++,
                  MF_BYPOSITION,
                  uiId,
                  str);
               
            }
            pcmdui->m_nIndex = iStartIndex;
            
            pcmdui->m_nIndexMax = pmenu->GetMenuItemCount();

      ////      pcmdui->m_bContinueRouting = TRUE;
            pcmdui->Enable(!m_strLanguagePath.is_empty());    // all the added items are enabled*/
            
     /*    }
      }
      else
      {
         bool bCurrent;
         if(pcmdui->m_id == "tools::language_change1")
         {
            bCurrent = m_strLanguagePath.is_empty() != 0;
         }
         else
         {
            // xxx string str(m_straLanguagePath[pcmdui->m_nID - ID_LANGUAGE_CHANGE1 - 1]);
            // bCurrent = m_strLanguagePath == str;
         }
         pcmdui->Enable(!bCurrent);
         pcmdui->SetCheck(bCurrent ? 1 : 0);
      }
   }*/

   bool application::GetFileManagerItemCallback(
      ::filemanager::data * pdata, 
      id id, 
      ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(itema);
      if(id == "ID_ADDTOMEDIALIBRARY")
      {
         return true;
      }
      else if(id == "ID_EXECUTE_ADDTOPLAYLIST")
      {
         return true;
      }
      return false;
   }

   void application::OnFileManagerItemUpdate(
         ::filemanager::data * pdata,
         cmd_ui * pcmdui,
         ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      if(pcmdui->m_id == "ID_ADDTOMEDIALIBRARY")
      {
         pcmdui->Enable(itema.get_size() > 0);
      }
      else if(pcmdui->m_id == "ID_EXECUTE_ADDTOPLAYLIST")
      {
         pcmdui->Enable(itema.get_size() > 0);
      }
      else
      {
         pcmdui->Enable(false);
      }
   }

   void application::OnFileManagerItemCommand(
         ::filemanager::data * pdata,
         id user,
         ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      if(user == "ID_ADDTOMEDIALIBRARY")
      {
         stringa stra;
         data_get("SongDirectorySet", ::ca::system::idEmpty, stra);
         for(int i = 0; i < itema.get_size(); i++)
         {
            stra.add_unique(itema[i].m_strPath);
         }
         data_set("SongDirectorySet", ::ca::system::idEmpty, stra);
      }
      else if(user == "ID_EXECUTE_ADDTOPLAYLIST")
      {
         int iItem = 0;
         for(int i = 0; i < itema.get_size(); i++)
         {
            if(!itema[i].m_flags.is_signalized(::fs::FlagFolder))
            {
               PlaylistDoc::EAddSong eaddsong;
               if(iItem == 0)
               {
                  eaddsong = PlaylistDoc::AddSongAndPlayIfNotPlaying;
               }
               else
               {
                  eaddsong = PlaylistDoc::AddSongOnly;
               }

               if(itema[i].m_flags.is_signalized(::fs::FlagInZip))
               {
                  GetPlaylistCentral().GetCurrentPlaylist()->AddSong(
                     itema[i].m_strPath,
                     eaddsong, true, true);
               }
               else
               {
                  GetPlaylistCentral().GetCurrentPlaylist()->AddSong(
                     itema[i].m_strPath,
                     eaddsong, true, true);
               }
               iItem++;
            }
         }
      }

   }

   void application::OnFileManagerInitializeFormPreData(
      ::filemanager::data * pdata, 
      id uiId, 
      ::user::form * pform)
   {
      UNREFERENCED_PARAMETER(pdata);
      if(uiId == "AFX_IDW_DIALOGBAR")
      {
         class user::control::descriptor control;

         control.m_bTransparent = true;
         control.set_type(user::control::type_static);
         control.m_typeinfo = &typeid(simple_static);
         control.m_id = "IDC_STATIC_SEARCH";
         //control.m_uiText = IDS_APP_OPTIONS_GENERAL_SYNCH_DELAY;
         //control.add_function(user::control::function_static2);
         pform->_001AddControl(control);
      }
   }


   bool application::GetCodePageCommandData(EncodingMapItem & itemParam, int iIndex)
   {
      if(iIndex >= 0 && iIndex < m_encodinga.get_size())
      {
         itemParam = m_encodinga[iIndex];
         return true;
      }
      return false;
   }

   DWORD application::CommandToCodePage(class id id)
   {
      EncodingMapItem item;
      for(int i = 0; i < GetCodePageCommandCount(); i++)
      {
         if(GetCodePageCommandData(item, i))
         {
            if(item.m_id == id)
               return item.m_dwCodePage;
         }
      }
      return 0xffffffff;
   }

   void application::AddCodePage(
      DWORD dwCodePage, 
      id lpcszCommand,
      id uiString)
   {
//      int iNewIndex = 0;
      for(int i = 0 ; i < m_encodinga.get_size(); i++)
      {
         EncodingMapItem & item = m_encodinga[i];
         if(item.m_id == lpcszCommand)
         {
            // already added
            ASSERT(FALSE);
            return ;
         }
      }
      EncodingMapItem item;
      item.m_dwCodePage       = dwCodePage;
      item.m_id               = id(lpcszCommand);
      item.m_uiString         = uiString;
      m_encodinga.add(item);
   }

   int application::GetCodePageCommandCount()
   {
      return m_encodinga.get_size();
   }

   void application::_001OnUpdateViewEncoding(gen::signal_object * pobj) 
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      //if(pcmdui->m_pcmdui->m_nID == ID_VIEW_ENCODING)
      //{
         ::userbase::menu_button_cmd_ui * pcmdui1 = dynamic_cast < ::userbase::menu_button_cmd_ui * > (pcmdui->m_pcmdui);
         if(pcmdui1 != NULL)
         {
            ::userbase::menu_item_ptra * pitema = pcmdui1->m_pitema;
            
            pitema->remove_at(pcmdui->m_pcmdui->m_nIndex);

            int iStartIndex = pcmdui->m_pcmdui->m_nIndex;
            int iIndex = iStartIndex;
            
            int iCount = GetCodePageCommandCount();

            ::userbase::menu_item menuitem(this);
            EncodingMapItem item;
            string str;
            wstring wstr;
            //CommandIdSpace idspace;

            for(int i = 0; i < iCount; i++)
            {
               if(GetCodePageCommandData(item, i))
               {
       //                if(!str.load_string(item.m_uiString))
                  //   continue;
               
                  menuitem.m_id = item.m_id;
                  menuitem.m_button._001SetButtonText(str);
                  menuitem.m_iLevel = pitema->m_pitemContainer != NULL ? pitema->m_pitemContainer->m_iLevel + 1 : 0;
                  pitema->insert_at(iIndex, menuitem);
                  iIndex++;
               }
            }
            pcmdui->m_pcmdui->m_nIndex = iStartIndex;
            
            pcmdui->m_pcmdui->m_nIndexMax = iIndex;

         }
         else
         {

            ::userbase::menu * pmenu = pcmdui->m_pcmdui->m_pMenu;

            if(pcmdui->m_pcmdui->m_pSubMenu != NULL)
            {
               pmenu = pcmdui->m_pcmdui->m_pSubMenu;
            }
            
   /*         pmenu->DeleteMenu(pcmdui->m_pcmdui->m_nID, MF_BYCOMMAND);

            int iStartIndex = pcmdui->m_pcmdui->m_nIndex;
            
            int iCount = GetCodePageCommandCount();

            EncodingMapItem item;
            string str;
            for(int i = 0; i < iCount; i++)
            {
               if(GetCodePageCommandData(item, i))
               {
                  if(!str.load_string(item.m_uiString))
                     continue;
               

                  SimpleMenu::_InsertMenuItem(
                     *pcmdui->m_pcmdui->m_pMenu,
                     *pmenu,
                     pcmdui->m_pcmdui->m_nIndex++,
                     MF_BYPOSITION,
                     ID_VIEW_ENCODING_1 + i,
                     str);
               }
               
            }
            pcmdui->m_pcmdui->m_nIndex = iStartIndex;
            
            pcmdui->m_pcmdui->m_nIndexMax = pmenu->GetMenuItemCount();

      ////      pcmdui->m_pcmdui->m_bContinueRouting = TRUE;
            //pcmdui->m_pcmdui->Enable(!m_strLanguagePath.is_empty());    // all the added items are enabled*/
         }
         
      //}
   /*   else
      {
         bool bCurrent;
         if(pcmdui->m_pcmdui->m_nID == ID_LANGUAGE_CHANGE1)
         {
            bCurrent = m_strLanguagePath.is_empty();
         }
         else
         {
            string str(m_wstraLanguagePath[pcmdui->m_pcmdui->m_nID - ID_LANGUAGE_CHANGE1 - 1]);
            bCurrent = m_strLanguagePath == str;
         }
         pcmdui->m_pcmdui->Enable(!bCurrent);
         pcmdui->m_pcmdui->SetCheck(bCurrent ? 1 : 0);
      }*/
         pcmdui->m_bRet = true;
   }

   void application::AddToRecentFileList(const char * lpszPathName)
   {
      ASSERT_VALID(this);
      ASSERT(lpszPathName != NULL);
      ASSERT(AfxIsValidString(lpszPathName));

      if (m_precentfilelist != NULL)
         m_precentfilelist->add(lpszPathName);
   }


   /////////////////////////////////////////////////////////////////////////////
   // MRU file list default implementation

   void application::OnUpdateRecentFileMenu(cmd_ui * pcmdui)
   {
      
      ASSERT_VALID(this);
      if (m_precentfilelist == NULL) // no MRU files
         pcmdui->Enable(FALSE);
      else
      {
         if(pcmdui->m_id == "FILE_MRU_FILE1")
            pcmdui->Enable(TRUE);
         else
            m_precentfilelist->UpdateMenu(pcmdui);
      }
   }

   /////////////////////////////////////////////////////////////////////////////
   // MRU file list default implementation

   BOOL application::OnOpenRecentFile(UINT nID)
   {
      ASSERT_VALID(this);
      ASSERT(m_precentfilelist != NULL);

      ASSERT(nID >= ID_FILE_MRU_FILE1);
      ASSERT(nID < ID_FILE_MRU_FILE1 + (UINT)m_precentfilelist->get_size());
      int nIndex = nID - ID_FILE_MRU_FILE1;
      ASSERT((*m_precentfilelist)[nIndex].get_length() != 0);

      TRACE2("MRU: open file (%d) '%s'.\n", (nIndex) + 1,
            (*m_precentfilelist)[nIndex]);

      if (_001OpenDocumentFile((*m_precentfilelist)[nIndex]) == NULL)
         m_precentfilelist->remove(nIndex);

      return TRUE;
   }


   void application::on_file_open() 
   {
   /*   XfplayerOpenFileDialog dlgFile(IDS_XFPLAYER_OPENFILETITLE,
         OFN_HIDEREADONLY
         | OFN_FILEMUSTEXIST
         | OFN_ALLOWMULTISELECT
         | OFN_EXPLORER);

      dlgFile.DoModal();

      stringa & stra = dlgFile.m_straFile;

      for(int i = 0; i < stra.get_size(); i++)
      {
         _001OpenDocumentFile(stra[i]);
      }*/
   }

   void application::OnFileOpenEx() 
   {
      GetStdFileManagerTemplate()->open(this);
   }

   void application::OnFileAdd() 
   {

   /*   XfplayerOpenFileDialog dlgFile(IDS_XFPLAYER_OPENFILETITLE,
         OFN_HIDEREADONLY
         | OFN_FILEMUSTEXIST
         | OFN_ALLOWMULTISELECT
         | OFN_EXPLORER);

      dlgFile.DoModal();

      stringa & stra = dlgFile.m_straFile;

      for(int i = 0; i < stra.get_size(); i++)
      {
         _001OpenDocumentFile(stra[i]);
      }
   */   
   }



   ::userbase::document* application::_vmsguserbaseOpenDocumentFile(const char * lpszFileName) 
   {
      document * pplayerdoc = dynamic_cast < document * > (GetMusicalPlayerCentral().get_document_template()->get_document(0));
      if(pplayerdoc == NULL)
      {
         pplayerdoc = dynamic_cast < document * >
            (GetMusicalPlayerCentral().get_document_template()->open_document_file(NULL));
      }
      PlaylistDoc * pdoc = GetPlaylistCentral().GetCurrentPlaylist(true, false);

      if(pdoc != NULL)
      {
         if(pplayerdoc != NULL)
         {
            pplayerdoc->AttachPlaylist(pdoc);
         }
         if(lpszFileName != NULL)
         {
            pdoc->AddSong(
               lpszFileName,
               PlaylistDoc::AddSongAndPlayIfNotPlaying, 
               false,
               true);
         }
      }
      return dynamic_cast < ::userbase::document * > (GetMusicalPlayerCentral().get_document_template()->get_document(0));
   }


   void application::AddDocumentFile(const char * lpszFileName)
   {
      document * pplayerdoc = dynamic_cast < document * > (GetMusicalPlayerCentral().get_document_template()->get_document(0));
      if(pplayerdoc == NULL)
      {
         pplayerdoc = dynamic_cast < document * >
            (GetMusicalPlayerCentral().get_document_template()->open_document_file(NULL));
      }
      PlaylistDoc * pdoc = GetPlaylistCentral().GetCurrentPlaylist(true);

      if(pdoc != NULL)
      {
         if(pplayerdoc != NULL)
         {
            pplayerdoc->AttachPlaylist(pdoc);
         }
         if(lpszFileName != NULL)
         {
            pdoc->AddSong(
               lpszFileName,
               PlaylistDoc::AddSongOnly, 
               false,
               true);
         }
      }

   }

   void application::_001OnFileNew() 
   {

      ::user::interaction * pui = m_puiInitialPlaceHolderContainer;

      if(pui == NULL && m_pbergedge != NULL)
      {
         pui = m_pbergedge->force_get_document()->get_view();
      }

      GetMusicalPlayerCentral().get_document_template()->open_document_file(NULL, TRUE, m_pbergedge->force_get_document()->get_bergedge_view());   

      PlaylistCentral & playlistcentral = PlaylistCentralContainer::AppGetPlaylistCentral(this);
      PlaylistDoc * pdoc = playlistcentral.GetCurrentPlaylist(true);
      pdoc->restart(true);

   }

   void application::_001CloseAllDocuments(bool bEndSession)
   {
      userbase::application::_001CloseAllDocuments(bEndSession);
      if(m_pdocmanager != NULL)
      {
         m_pdocmanager->close_all_documents(bEndSession);
      }
   }


   ::document * application::open_document_file(var varFile)
   {
      return _001OpenDocumentFile(varFile);
   }

   void application::InitializeResourceId()
   {
      {
   //      window_frame::FrameSchema::ButtonIdSpace idspace;
   /*     SetResourceId(idspace, window_frame::FrameSchema::ButtonClose, ID_VMSGUI_CLOSE);
         SetResourceId(idspace, window_frame::FrameSchema::ButtonUp, ID_VMSGUI_WINDOW_UP);
         SetResourceId(idspace, window_frame::FrameSchema::ButtonDown, ID_VMSGUI_WINDOW_DOWN);
         SetResourceId(idspace, window_frame::FrameSchema::ButtonMinimize, ID_VMSGUI_WINDOW_MINIMIZE);
         SetResourceId(idspace, window_frame::FrameSchema::ButtonMaximize, ID_VMSGUI_WINDOW_MAXIMIZE);
         SetResourceId(idspace, window_frame::FrameSchema::ButtonRestore, ID_VMSGUI_WINDOW_RESTORE);
         SetResourceId(idspace, window_frame::FrameSchema::ButtonNotifyIcon, ID_VMSGUI_NOTIFY_ICON);*/
      }
      {
   //      mixer::IdSpace idspace;
         /*SetResourceId(idspace, mixer::IdsMuteAll, IDS_MIXER_MUTEALL);
         SetResourceId(idspace, mixer::IdsMute, IDS_MIXER_MUTE);*/
      }
   }



   bool application::bergedge_start()
   {
      // dispatch commands specified on the command line
      if (!m_bInline && !_001ProcessShellCommand(command_line()))
         return false;

      if(command_line().m_nShellCommand == gen::command_line::FileDDE)
      {
         //_001OpenDocumentFile(NULL);
      }

      // Threads initialized here to avoid DDE missreading

      /*VERIFY(GetAudioWaveCentral().Initialize());

      ::ca::type_info * pruntimeclass = &typeid(CVmpHighThread);
      if(!(m_phighthread = dynamic_cast<CVmpHighThread *>(AfxBeginThread(pruntimeclass))))
      {
         return FALSE;
      }*/

      // The one and only ::ca::window has been initialized, so show and update it.
   //   GetMainWnd()->ShowWindow(SW_SHOW);
   //   GetMainWnd()->UpdateWindow();
      
      return true;
   }

   ::ca::application * application::get_app() const
   {
      return ::eluce::application::get_app();
   }



   void application::CreateTemplates()
   {
      ::userbase::single_document_template* pDocTemplate;
      pDocTemplate = new ::userbase::single_document_template(
         this,
         "mplite/album",
         &typeid(MediaLibraryDoc),
         &typeid(MediaLibraryChildFrame),       // main SDI frame ::ca::window
         &typeid(::mplite::library::view));
      userbase::application::add_document_template(pDocTemplate);
      m_pdoctemplateAlbum = pDocTemplate;
   }


   void application::OnUpdateToolsOptions(cmd_ui * pcmdui) 
   {
      pcmdui->Enable();   
      pcmdui->_001SetCheck(m_lpoptionsdialog != NULL);
   }


   void application::data_on_after_change(gen::signal_object * pobj)
   {
      simpledb::application::data_on_after_change(pobj);
   /* dbbreak   VmsDataChangeHint * pch = (VmsDataChangeHint *) pobj;
      if(*pch->m_pkey == "SongDirectorySet")
      {
         stringa stra;
         data_get("SongDirectorySet", 0, 0, stra);

         mediamanager::get(this)->BuildAlbum(stra);
      } */
   //   switch(key.get_type())
     // {
      //case _vmsdb::DataKeyType_vmplight:
         {
   /*   dbbreak      switch(pch->m_pkey->get_value())
            {
         //   case _vmsdb::CConfiguration::CfgUserInterfaceLanguage:
         //      OnAfterLanguageChange(GetLanguage(), puh);
         //      break;
         //   case _vmsp::CConfiguration::CfgKaraokeEncoding:
         //      OnAfterKaraokeEncodingChange(puh);
         //      break;
            case _vms::DataKeyMidiOutDevice:
               {
                  int i;
                  if(data_get("MidiOutDevice", 0, 0, i))
                  {
                     GetMidiCentral().SetMidiOutDevice ((UINT) i);
                  }
               }
               break;
            } */
         }
      //default:
        // break;
      //}
   }

   void application::OnViewPlaylist() 
   {
      PlaylistDoc * pdoc = GetPlaylistCentral().GetCurrentPlaylist(true);
      if(pdoc != NULL)
      {
         pdoc->PopViews();
         document * pplayerdoc = dynamic_cast < document * > (GetMusicalPlayerCentral().get_document_template()->get_document(0));
         if(pplayerdoc != NULL)
         {
            pplayerdoc->AttachPlaylist(pdoc);
         }
      }
      
   }

   void application::OnUpdateViewPlaylist(cmd_ui * pcmdui) 
   {
      pcmdui->Enable();
      
   }

   //AFX_STATIC_DATA const char _afxFileSection[] = "Recent File List";
   //AFX_STATIC_DATA const char _afxFileEntry[] = "File%d";
   AFX_STATIC_DATA const char _afxPreviewSection[] = "Settings";
   AFX_STATIC_DATA const char _afxPreviewEntry[] = "PreviewPages";

   int application::exit_instance() 
   {
      System.font_central().Finalize();

      GetAudioWaveCentral().close();
      /*MessageFilterHookManager * pmfmh;
      if(MessageFilterHookManager::AppGetMessageFilterHookManager(&pmfmh))
      {
         pmfmh->MessageFilterUnhook();
      }*/
      
      /*
      if (command_line().m_nShellCommand != CCommandLineInfo::AppUnregister)
      {
         if (!afxContextIsDLL)
         {
         //   SaveStdProfileSettings();
            ASSERT_VALID(this);

            if (m_precentfilelist != NULL)
               m_precentfilelist->WriteList();

            if (m_nNumPreviewPages != 0)
               WriteProfileInt(_afxPreviewSection, _afxPreviewEntry, m_nNumPreviewPages);
         }
      }
      */
      mediamanager::get(this)->Finalize();

      LibCharGuess::Done();

      if(m_pdocmanager != NULL)
      {
         delete m_pdocmanager;
         m_pdocmanager = NULL;
      }
      
      return ::ca84::application::exit_instance();
   }

   void application::OnViewAlbum() 
   {
      m_pdoctemplateAlbum->open_document_file(NULL);   
   }

   void application::OnUpdateViewAlbum(cmd_ui * pcmdui) 
   {
      pcmdui->Enable();
   }



   ::userbase::image_manager & application::GetImageManager()
   {
      return *m_pimagemanager;
   }

   PlaylistCallbackInterface * application::GetNewPlaylistCallback()
   {
      ::document * pdoc;
      
      if(GetMusicalPlayerCentral().get_document_template()->get_document(0) != NULL)
         pdoc = GetMusicalPlayerCentral().get_document_template()->get_document(0);
      else
         pdoc = GetMusicalPlayerCentral().get_document_template()->open_document_file(NULL);
      
      if(pdoc == NULL)
         return NULL;

      mediaplay::view_update_hint uh;

      uh.set_type(mediaplay::view_update_hint::TypeGetPlaylistCallback);

      pdoc->update_all_views(NULL, 0, &uh);

      if(uh.m_pplaylistcallback == NULL)
         return NULL;

      return uh.m_pplaylistcallback;
   }


   void application::on_request(var & varFile, var & varQuery)
   {
      UNREFERENCED_PARAMETER(varQuery);

      ::user::interaction * pui = m_puiInitialPlaceHolderContainer;

      if(pui == NULL && m_pbergedge != NULL)
      {
         pui = m_pbergedge->force_get_document()->get_view();
      }

      GetMusicalPlayerCentral().get_document_template()->open_document_file(NULL, TRUE, m_pbergedge->force_get_document()->get_bergedge_view());   

      if(varFile.get_type() == var::type_string)
      {
         PlaylistCentral & playlistcentral = PlaylistCentralContainer::AppGetPlaylistCentral(get_app());
         PlaylistDoc * pdoc = playlistcentral.GetCurrentPlaylist(true);
         pdoc->AddSong(varFile, PlaylistDoc::AddSongAndPlayIfNotPlaying, true, true);
      }
      else if(varFile.stra().get_count() > 0)
      {
         PlaylistCentral & playlistcentral = PlaylistCentralContainer::AppGetPlaylistCentral(get_app());
         PlaylistDoc * pdoc = playlistcentral.GetCurrentPlaylist(true);
         bool bAddSongAndPlayIfNotPlaying = true;
         for(int i = 0; i < varFile.stra().get_count(); i++)
         {
            string strPath = varFile.stra()[i];
/*            if(itema[i].m_flags.is_signalized(filemanager::FlagInZip))
            {
               pdoc->AddSong(itema[i].m_strPath + ":" + itema[i].m_strExtra, 
               bAddSongAndPlayIfNotPlaying ?
               PlaylistDoc::AddSongAndPlayIfNotPlaying :
               PlaylistDoc::AddSongOnly, true, true);
            }
            else
            {*/
               pdoc->AddSong(strPath, bAddSongAndPlayIfNotPlaying ? PlaylistDoc::AddSongAndPlayIfNotPlaying : PlaylistDoc::AddSongOnly, true, true);
            //}
            // flag could be used always, but due race conditions, it may not started playing
            bAddSongAndPlayIfNotPlaying = false;
         }
      }
      else
      {
         _001OnFileNew();
      }
   }

   void application::OnFileManagerOpenFolder(
      ::filemanager::data * pdata, 
      ::fs::item & item)
   {
      pdata->FileManagerBrowse(item);
   }



   bool application::InitializeLocalDataCentral()
   {
      m_pdatabase = new mplite::database(this);

      if(m_pdatabase == NULL)
      {
         TRACE("VmpLightApp::initialize_instance failed to instatiate LightDB\n");
         return false;
      }

      if(!m_pdatabase->Initialize())
      {
         TRACE("VmpLightApp::initialize_instance failed to initialize LightDB\n");
         return false;
      }

      m_pdb = new MusicalPlayerLightDB(this);

   // dbbreak   GetDataServer()->SetNextServer(m_pdb);
      return true;
   }

   void application::LoadStdProfileSettings(UINT nMaxMRU)
   {
      int iMRUCount = _AFX_MRU_COUNT;
      data_get("MRUCount", ::ca::system::idEmpty, iMRUCount);
      int iMRUEnable = 1;
      if(data_get("MRUEnable", ::ca::system::idEmpty, iMRUEnable))
      {
         if(!iMRUEnable)
         {
            iMRUCount = 0;
         }
      }

      ASSERT_VALID(this);
      ASSERT(m_precentfilelist == NULL);

//      UINT nMaxMRU = 15;
      if (nMaxMRU != 0)
      {
         // create file MRU since nMaxMRU not zero
         m_precentfilelist = new RecentFileList(0, _afxFileSection, _afxFileEntry,
            nMaxMRU, "MRUFiles");
         m_precentfilelist->ReadList();
      }
      // 0 by default means not set
      m_nNumPreviewPages = GetProfileInt(_afxPreviewSection, _afxPreviewEntry, 0);


      gen::application::LoadStdProfileSettings(iMRUCount);
   }


/*
   int application::DoMessageBox(const char * lpszPrompt, UINT nType, UINT nIDPrompt)
   {
      // disable windows for modal dialog
      //xxx EnableModeless(FALSE);
      HWND hWndTop;
      HWND hWnd = ::ca::window::GetSafeOwner_(NULL, &hWndTop);

      // set help context if possible
      DWORD* pdwContext = NULL;
      if (hWnd != NULL)
      {
         // use cast-level context or frame level context
         LRESULT lResult = ::SendMessage(hWndTop, WM_HELPPROMPTADDR, 0, 0);
         if (lResult != 0)
            pdwContext = (DWORD*)lResult;
      }
      // for backward compatibility use cast context if possible
      if (pdwContext == NULL && this != NULL)
         pdwContext = &m_dwPromptContext;

      DWORD dwOldPromptContext = 0;
      if (pdwContext != NULL)
      {
         // save old prompt context for restoration later
         dwOldPromptContext = *pdwContext;
         if (nIDPrompt != 0)
            *pdwContext = HID_BASE_PROMPT+nIDPrompt;
      }

      // determine icon based on type specified
      if ((nType & MB_ICONMASK) == 0)
      {
         switch (nType & MB_TYPEMASK)
         {
         case MB_OK:
         case MB_OKCANCEL:
            nType |= MB_ICONEXCLAMATION;
            break;

         case MB_YESNO:
         case MB_YESNOCANCEL:
            nType |= MB_ICONEXCLAMATION;
            break;

         case MB_ABORTRETRYIGNORE:
         case MB_RETRYCANCEL:
            // No default icon for these types, since they are rarely used.
            // The caller should specify the icon.
            break;
         }
      }

   #ifdef _DEBUG
      if ((nType & MB_ICONMASK) == 0)
         TRACE0("Warning: no icon specified for message box.\n");
   #endif

      char szAppName[_MAX_PATH];
      const char * pszAppName;
      if (this != NULL)
         pszAppName = m_pszAppName;
      else
      {
         pszAppName = szAppName;
         GetModuleFileName(NULL, szAppName, _MAX_PATH);
      }

      int nResult =
         ::MessageBox(hWnd, lpszPrompt, pszAppName, nType);

      // restore prompt context if possible
      if (pdwContext != NULL)
         *pdwContext = dwOldPromptContext;

      // re-enable windows
      if (hWndTop != NULL)
         ::EnableWindow(hWndTop, TRUE);
   //xxx    EnableModeless(TRUE);

      return nResult;
   }
*/

   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)  
   {
      if(userbase::application::_001OnCmdMsg(pcmdmsg))
         return TRUE;

   /*   BOOL bResult;
      if(nCode == CN_UPDATE_COMMAND_UI)
      {
           ASSERT(nCode == CN_UPDATE_COMMAND_UI);
         ASSERT(pExtra != NULL);
         cmd_ui * pcmdui = (cmd_ui *)pExtra;
         ASSERT(pcmdui->m_nID == nID);           // sanity assert
         ASSERT(!pcmdui->m_bContinueRouting);    // idle - not set
         OnUpdatePopupMenu(pcmdui);
         bResult = !pcmdui->m_bContinueRouting;
         //pcmdui->m_bContinueRouting = FALSE; 
      }
      else
      {
           //ASSERT(FALSE);
           bResult = FALSE;
      }
      if(bResult)
         return bResult;*/

      return gen::application::_001OnCmdMsg(pcmdmsg);
   }

   ::document * application::_001OpenDocumentFile(var varFile)
   {
      if(command_line().m_varQuery.has_property("file"))
      {
         return GetMusicalPlayerCentral().get_document_template()->open_document_file(command_line().m_varQuery["file"], true, m_pbergedge->get_document()->get_bergedge_view(), NULL);   
      }
      else if(varFile.is_empty())
      {
         return GetMusicalPlayerCentral().get_document_template()->open_document_file(NULL, true, m_pbergedge->get_document()->get_bergedge_view());   
      }
      else
      {
         return GetMusicalPlayerCentral().get_document_template()->open_document_file(varFile, true, m_pbergedge->get_document()->get_bergedge_view());   
      }
   }

   bool application::on_install()
   {
      string strFormat;

      win::registry::Key keyKar(HKEY_CLASSES_ROOT, ".kar", true);
      keyKar.SetValue(NULL, "veriwell.musical.studio.file");

      win::registry::Key keyMid(HKEY_CLASSES_ROOT, ".mid", true);
      keyMid.SetValue(NULL, "veriwell.musical.studio.file");

      win::registry::Key keyMk1(HKEY_CLASSES_ROOT, ".mk1", true);
      keyMk1.SetValue(NULL, "veriwell.musical.studio.file");

      win::registry::Key keyLink4(HKEY_CLASSES_ROOT, "veriwell.musical.studio.file\\DefaultIcon", true);
      strFormat = System.dir().matter("mplite/mainframe/doc.ico");
      keyLink4.SetValue(NULL, strFormat);

      win::registry::Key keyLink3(HKEY_CLASSES_ROOT, "veriwell.musical.studio.file\\shell", true);
      keyLink3.SetValue(NULL, "open");

      win::registry::Key keyLink2(HKEY_CLASSES_ROOT, "veriwell.musical.studio.file\\shell\\open", true);
      keyLink2.SetValue(NULL, "&open");

      win::registry::Key keyLink1(HKEY_CLASSES_ROOT, "veriwell.musical.studio.file\\shell\\open\\command", true);

      strFormat.Format("\"%s\" \"%%L\"", System.dir().ca2module("cubeapp.exe"));
      keyLink1.SetValue(NULL, strFormat);

      /*if(VistaTools::IsVista() && VistaTools::IsElevated() == S_OK)
      {
         string strCommand = m_strModulePath;
         strCommand = System.url().url_encode(strCommand);
         DWORD dwSessId;

         HANDLE hProcess = ::GetCurrentProcess();
         DWORD dwId = ::GetProcessId(hProcess);

         ProcessIdToSessionId(dwId, &dwSessId);
         xml::node * pnode = new xml::node;
         pnode->m_strName = "run";
         pnode->add_attr("sessionid", dwSessId);
         pnode->add_attr("command", strCommand);
         machine_event_central().command(pnode);
      }*/
      return ca2::application::on_install();
   }

   bool application::UpdateRegistry()
   {
      //return m_pdocmanager->UpdateRegistry();
      return true;
   }

   bool application::CreateDocumentTemplates()
   {
      musctrl::MusicalPlayerCentral & playercentral = Application.GetMusicalPlayerCentral();

      playercentral.m_pruntimeclassDocument  = &typeid(document);
      playercentral.m_typeinfoFrameWnd  = &typeid(main_frame);
      playercentral.m_typeinfoView      = &typeid(pane_view);
      playercentral.m_strMatter              = "mplite/mainframe";
      //playercentral.m_uiResourceIdEmbedding  = IDR_SRVR_EMBEDDED;
      //playercentral.m_uiResourceIdInPlace    = IDR_SRVR_INPLACE;

      musctrl::single_document_template* pPlayerSingleDocTemplate;
      pPlayerSingleDocTemplate = playercentral.CreateDocTemplate();
      add_document_template(pPlayerSingleDocTemplate);

      // Connect the COleTemplateServer to the document template.
      //    The COleTemplateServer creates new documents on behalf
      //    of requesting OLE containers by using information
      //    specified in the document template.
   //   m_serverMid.ConnectTemplate(clsidMid, playercentral.get_document_template(), FALSE);
      //m_serverKar.ConnectTemplate(clsidKar, playercentral.get_document_template(), FALSE);
      //m_serverSt3.ConnectTemplate(clsidSt3, playercentral.get_document_template(), FALSE);

      // Register all OLE server factories as running.  This enables the
      //    OLE libraries to create objects from other applications.
   //   m_serverMid.RegisterAll();
      //m_serverKar.RegisterAll();
      //m_serverSt3.RegisterAll();

   //xxx   _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE);

      return true;
   }

   mplite::database & application::mplitedb()
   {
      return *m_pdatabase;
   }


   application & cast (::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

   class database & db(::ca::application * papp)
   {
      return (dynamic_cast < application *> ( papp))->mplitedb();
   }


} // namespace mplite


