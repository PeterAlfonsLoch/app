#include "framework.h"



#ifdef LINUX
#include <dlfcn.h>
#include <link.h>
#include <ctype.h>
#include <unistd.h>
#elif defined(APPLEOS)
#include <dlfcn.h>
#include <mach-o/dyld.h>
#endif

#ifdef WINDOWS
#include <cderr.h>      // Commdlg Error definitions
#include <winspool.h>
#endif


namespace core
{


   const char application::gen_FileSection[] = "Recent File List";
   const char application::gen_FileEntry[] = "File%d";
   const char application::gen_PreviewSection[] = "Settings";
   const char application::gen_PreviewEntry[] = "PreviewPages";


   application::application():
      element(this), // start m_paxisapp as this for constructor referencing this app
      m_mutex(this),
      thread(NULL),
      m_simpledb(this)
   {

      if(m_paxisapp == NULL)
      {
         set_app(this);
      }


      // almost always forgotten, assumed, as exception, responsability of application to add first ref on constructor.
      ::add_ref(this);

      srand(::get_tick_count());

      m_bService = false;

      m_iResourceId = 8001;

      ::core::profiler::initialize();

      m_pszRegistryKey = NULL;
      m_pszHelpFilePath = NULL;
      m_pszProfileName = NULL;

      m_pcoreapp = this;

      m_pwndMain = NULL;

      m_pdocmanager = NULL;

      m_strInstallType = "application";

      m_psignal->connect(this,&application::on_application_signal);

      m_eexclusiveinstance = ExclusiveInstanceNone;
      m_peventReady = NULL;
      m_strLocale = "_std";
      m_strSchema = "_std";

      m_pcalculator = NULL;
      m_pcolorertake5 = NULL;


   }


   application::~application()
   {

   }



   void application::construct(const char * pszId)
   {

      if(pszId == NULL)
      {

         m_strId = "";

      }
      else
      {

         m_strId = pszId;

      }

      ::base::application::construct(m_strId);

      if(m_strAppName.is_empty())
      {

         if(m_strAppId.has_char())
         {

            m_strAppName = m_strAppId;

         }
         else if(m_strInstallToken.has_char())
         {

            m_strAppName = m_strInstallToken;
         }

      }

   }

   application * application::get_app() const
   {
      return (application *) this;
   }


   int32_t application::exit()
   {

      int32_t iExit = 0;

      try
      {
         thread::exit();
      }
      catch(...)
      {
      }

      return iExit;

   }


   bool application::is_system()
   {

      return false;

   }


   bool application::is_session()
   {

      return false;

   }


   bool application::is_installing()
   {

      return ::base::application::is_installing();

   }


   bool application::is_uninstalling()
   {

      return ::base::application::is_uninstalling();

   }


   bool application::is_serviceable()
   {

      return ::base::application::is_serviceable();

   }



   int32_t application::main()
   {

      return ::base::application::main();

   }


   bool application::os_native_bergedge_start()
   {
      return true;
   }

   bool application::process_initialize()
   {





      if(!::base::application::process_initialize())
         return false;

      m_spuserex = create_userex();

      if(m_spuserex == NULL)
         return false;

      m_spuserex->construct(this);

      m_spuserfs = create_userfs();

      if(m_spuserfs == NULL)
         return false;

      m_spuserfs->construct(this);


      return true;

   }




   bool application::initialize1()
   {

      m_splicense = new class ::fontopus::license(this);

      if(!::base::application::initialize1())
         return false;


      m_puinteraction = canew(::user::uinteraction::uinteraction(this));

      m_puinteraction->construct(this);

      if(!m_puinteraction->initialize())
         return false;




      if(!is_installing() && !is_uninstalling() && !is_system())
      {

         simpledb().set_keyboard_layout(NULL,::action::source::system());

      }



      m_dwAlive = ::get_tick_count();

      if(!is_system())
      {
         Platform.register_bergedge_application(this);
      }




      if(!m_spuserfs->initialize())
         return false;

      m_simpledb.construct(this);

      if(!m_simpledb.initialize())
         return false;

      if(!m_simpledb.initialize2())
         return false;


      if(!m_spuserex->initialize())
         return false;

      if(!is_system() && !is_session() && !is_installing() && !is_uninstalling())
      {

         string str;
         // if system locale has changed (compared to last recorded one by core)
         // use the system locale
         if(data_get("system_locale",str))
         {
            if(str.has_char())
            {
               if(str != Session.get_locale())
               {
                  try
                  {
                     data_set("system_locale",Session.get_locale());
                     data_set("locale",Session.get_locale());
                  }
                  catch(...)
                  {
                  }
               }
            }
         }
         else
         {
            data_set("system_locale",Session.get_locale());
         }

         if(command()->m_varTopicQuery["locale"].get_count() > 0)
         {
            str = command()->m_varTopicQuery["locale"].stra()[0];
            data_set("system_locale",str);
            data_set("locale",str);
            Session.set_locale(str,::action::source::database());
         }
         else if(command()->m_varTopicQuery["lang"].get_count() > 0)
         {
            str = command()->m_varTopicQuery["lang"].stra()[0];
            data_set("system_locale",str);
            data_set("locale",str);
            Session.set_locale(str,::action::source::database());
         }
         else if(data_get("locale",str))
         {
            if(str.has_char())
            {
               Session.set_locale(str,::action::source::database());
            }
         }
         // if system schema has changed (compared to last recorded one by core)
         // use the system schema
         if(data_get("system_schema",str))
         {
            if(str.has_char())
            {
               if(str != Session.get_schema())
               {
                  try
                  {
                     data_set("system_schema",Session.get_schema());
                     data_set("schema",Session.get_schema());
                  }
                  catch(...)
                  {
                  }
               }
            }
         }
         else
         {
            data_set("system_schema",Session.get_schema());
         }

         if(command()->m_varTopicQuery["schema"].get_count() > 0)
         {
            str = command()->m_varTopicQuery["schema"].stra()[0];
            data_set("system_schema",str);
            data_set("schema",str);
            Session.set_schema(str,::action::source::database());
         }
         else if(data_get("schema",str))
         {
            if(str.has_char())
            {
               Session.set_schema(str,::action::source::database());
            }
         }

         // keyboard layout
         if(data_get("keyboard_layout",str) && str.has_char())
         {
            Session.user()->set_keyboard_layout(str,::action::source::database());
         }
         else
         {
            Session.user()->set_keyboard_layout(NULL,::action::source::database());
         }

         data_pulse_change("ca2","savings",NULL);


         Sess(this).fill_locale_schema(*Session.str_context()->m_plocaleschema);


         Sys(this).appa_load_string_table();

      }


      /*if(!m_spuser->initialize1())
      return false;
      if(!m_spuser->initialize2())
      return false;*/

      if(!m_spuserex->initialize1())
         return false;
      if(!m_spuserex->initialize2())
         return false;



      return true;

   }


   bool application::initialize2()
   {

      if(!::base::application::initialize2())
         return false;

      return true;

   }


   bool application::initialize3()
   {

      if(!::base::application::initialize3())
         return false;

      return true;

   }











   void application::on_request(sp(::create_context) pcreatecontext)
   {

      ::base::application::on_request(pcreatecontext);

   }







   /*   ::lemon::array & application::array()
   {

   return *m_plemonarray;

   }
   */

   bool application::initialize_instance()
   {

      if(!::base::application::initialize_instance())
         return false;

      return true;

   }


   int32_t application::exit_instance()
   {

      try
      {
         if(!is_system())
         {
            Platform.unregister_bergedge_application(this);
         }
      }
      catch(...)
      {

      }


      try
      {

         thread         * pthread = this;

         if(pthread != NULL)
         {

            try
            {
               // avoid calling CloseHandle() on our own thread handle
               // during the thread destructor
               // avoid thread object data auto deletion on thread termination,
               // letting thread function terminate
               pthread->m_bAutoDelete = false;

               pthread->set_os_data(NULL);

               pthread->set_run(false);

            }
            catch(...)
            {

            }

         }

      }
      catch(...)
      {

      }

      try
      {

         ::base::application   * papp = m_pimpl.detach();

         if(papp != NULL && papp != this && !papp->is_system())
         {

            try
            {

               papp->exit_instance();

            }
            catch(...)
            {

            }

         }

      }
      catch(...)
      {

      }

      try
      {

         if(System.get_application_count() <= 1)
         {

            if(System.thread::get_os_data() != NULL)
            {
               System.post_thread_message(WM_QUIT);

            }

         }

      }
      catch(...)
      {
         ::simple_message_box(NULL,"a","b",MB_OK);
         m_iReturnCode = -1;

      }

      return m_iReturnCode;

      try
      {
         ::base::application::exit_instance();
      }
      catch(...)
      {
      }

      return 0;

   }


   LRESULT application::GetPaintMsgProc(int32_t nCode,WPARAM wParam,LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(nCode);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      return 0;
   }





   bool application::CreateFileFromRawResource(UINT nID,const char * lpcszType,const char * lpcszFilePath)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpcszType);
      UNREFERENCED_PARAMETER(lpcszFilePath);
      /*      HINSTANCE hinst = ::core::FindResourceHandle(MAKEINTRESOURCE(nID), lpcszType);
      if(hinst == NULL)
      return false;
      HRSRC hrsrc = ::FindResource(
      hinst,
      MAKEINTRESOURCE(nID),
      lpcszType);
      if(hrsrc == NULL)
      return false;
      HGLOBAL hres = ::LoadResource(hinst, hrsrc);
      if(hres == NULL)
      return false;
      uint32_t dwResSize = ::SizeofResource(hinst, hrsrc);

      if(hres != NULL)
      {
      UINT FAR* lpnRes = (UINT FAR*)::LockResource(hres);
      try
      {
      // create the .mdb file
      ::file::binary_buffer_sp f(get_app());

      if(f->open(lpcszFilePath, ::file::mode_create | ::file::mode_write ))
      {
      // write the ::fontopus::user-defined resource to the .mdb file
      f->write(lpnRes, dwResSize);
      f->flush();
      }
      else
      {
      #ifdef DEBUG
      g_dumpcontext << "File could not be opened \n";
      #endif
      }
      }
      catch(::core::file_exception_sp * pe)
      {
      #ifdef DEBUG
      //         g_dumpcontext << "File could not be opened " << pe->m_cause << "\n";
      #endif
      }


      #ifndef WIN32 //unlock Resource is obsolete in the Win32 API
      ::UnlockResource(hres);
      #endif
      ::FreeResource(hres);
      }
      return true;*/

      return false;
   }

#ifdef WINDOWS

   bool application::OnMessageWindowMessage(LPMESSAGE lpmsg)
   {
      UNREFERENCED_PARAMETER(lpmsg);
      return false;
   }

#elif defined(LINUX)

   bool application::OnMessageWindowMessage(XEvent * pevent)
   {
      UNREFERENCED_PARAMETER(pevent);
      return false;
   }

#endif

   void application::OnAppLanguage(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      m_signalAppLanguageChange.emit();
   }



   void application::OnUpdateRecentFileMenu(cmd_ui * pcmdui)
   {
      UNREFERENCED_PARAMETER(pcmdui);
      /*TRACE("\nCVmsGenApp::OnUpdateRecentFileMenu");
      if(m_pRecentFileList == NULL)
      {
      pcmdui->Enable(FALSE);
      //string str;
      //str.load_string(IDS_RECENT_FILE);
      //pcmdui->SetText(str);
      for (int32_t iMRU = 1; iMRU < 10; iMRU++)
      pcmdui->m_pMenu->DeleteMenu(pcmdui->m_nID + iMRU, MF_BYCOMMAND);
      return;
      }

      ASSERT(m_pRecentFileList->m_arrNames != NULL);

      ::user::menu* pMenu = pcmdui->m_pMenu;
      if (m_pRecentFileList->m_strOriginal.is_empty() && pMenu != NULL)
      pMenu->GetMenuString(pcmdui->m_nID, m_pRecentFileList->m_strOriginal, MF_BYCOMMAND);

      if (m_pRecentFileList->m_arrNames[0].is_empty())
      {
      // no MRU files
      if (!m_pRecentFileList->m_strOriginal.is_empty())
      pcmdui->SetText(m_pRecentFileList->m_strOriginal);
      pcmdui->Enable(FALSE);
      return;
      }

      if (pcmdui->m_pMenu == NULL)
      return;

      ::user::menu * pmenu = CMenuUtil::FindPopupMenuFromID(pcmdui->m_pMenu, pcmdui->m_nID);

      //if(pmenu == NULL)
      //{
      // pmenu = pcmdui->m_pMenu;
      //}

      bool bCmdUIMenu = pmenu == pcmdui->m_pMenu;

      if(!bCmdUIMenu)
      return;

      int32_t nID = pcmdui->m_nID;
      int32_t nIndex = CMenuUtil::GetMenuPosition(pmenu, nID);

      for (int32_t iMRU = 0; iMRU < m_pRecentFileList->m_nSize; iMRU++)
      pcmdui->m_pMenu->DeleteMenu(pcmdui->m_nID + iMRU, MF_BYCOMMAND);



      char szCurDir[_MAX_PATH];
      GetCurrentDirectory(_MAX_PATH, szCurDir);
      int32_t nCurDir = lstrlen(szCurDir);
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

      pcmdui->m_bEnableChanged = TRUE;    // all the added items are enabled*/

   }

   bool application::GetResourceData(UINT nID,const char * lpcszType,primitive::memory &storage)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpcszType);
      UNREFERENCED_PARAMETER(storage);
      /*      HINSTANCE hinst = ::core::FindResourceHandle(MAKEINTRESOURCE(nID), lpcszType);

      if(hinst == NULL)
      return false;

      HRSRC hrsrc = ::FindResource(
      hinst,
      MAKEINTRESOURCE(nID),
      lpcszType);

      if(hrsrc == NULL)
      return false;

      HGLOBAL hres = ::LoadResource(hinst, hrsrc);
      if(hres == NULL)
      return false;

      uint32_t dwResSize = ::SizeofResource(hinst, hrsrc);

      if(hres != NULL)
      {
      UINT FAR* lpnRes = (UINT FAR*)::LockResource(hres);
      try
      {
      storage.set_data(lpnRes, dwResSize);
      }
      catch(::core::file_exception_sp * pe)
      {
      #ifdef DEBUG
      //            g_dumpcontext << "File could not be opened " << pe->m_cause << "\n";
      #endif
      }


      #ifndef WIN32 //unlock Resource is obsolete in the Win32 API
      ::UnlockResource(hres);
      #endif
      ::FreeResource(hres);
      }
      return true;*/
      return false;

   }

#ifdef WINDOWSEX

   HENHMETAFILE application::LoadEnhMetaFile(UINT uiResource)
   {
      primitive::memory storage;
      if(!GetResourceData(uiResource,"EnhMetaFile",storage))
      {
         return NULL;
      }
      return SetEnhMetaFileBits((UINT)storage.get_size(),storage.get_data());
   }

#endif

   /////////////////////////////////////////////////////////////////////////////
   // WinApp UI related functions

   void application::EnableModelessEx(bool bEnable)
   {
      UNREFERENCED_PARAMETER(bEnable);
#ifdef ___NO_OLE_SUPPORT
      UNUSED(bEnable);
#endif

      // no-op if main window is NULL or not a frame_window
      /*      sp(::user::interaction) pMainWnd = System.m_puiMain;
      if (pMainWnd == NULL || !pMainWnd->is_frame_window())
      return;*/

#ifndef ___NO_OLE_SUPPORT
      // check if notify hook installed
      /*   ::core::frame_window* pFrameWnd =
      dynamic_cast < ::core::frame_window * > (pMainWnd);
      ASSERT(pFrameWnd != NULL);
      if (pFrameWnd->GetNotifyHook() != NULL)
      pFrameWnd->GetNotifyHook()->OnEnableModeless(bEnable);*/
#endif
   }


   /*id_space * application::GetGenIdSpace()
   {
   return m_pidspace;
   }*/

   /*
   string application::load_string(const id_space * pspace, int32_t iKey)
   {
   string str;
   int32_t iId = GetResourceId(pspace, iKey);
   if(iId == -1)
   return str;
   str.load_string(iId);
   return str;
   }
   */





   // Main running routine until application exits
   int32_t application::run()
   {
      /*   if (m_puiMain == NULL) // may be a service or console application window
      {
      // Not launched /Embedding or /Automation, but has no main window!
      TRACE(::axis::trace::category_AppMsg, 0, "Warning: m_puiMain is NULL in application::run - quitting application.\n");
      __post_quit_message(0);
      }*/
      //      return application::run();
      return ::base::application::run();

   }


   /////////////////////////////////////////////////////////////////////////////
   // application idle processing
   bool application::on_idle(LONG lCount)
   {
      /*      if (lCount <= 0)
      {
      thread::on_idle(lCount);

      // call doc-template idle hook
      ::count count = 0;
      if (m_pdocmanager != NULL)
      count = m_pdocmanager->get_template_count();

      for(index index = 0; index < count; index++)
      {
      sp(impact_system) ptemplate = m_pdocmanager->get_template(index);
      ASSERT_KINDOF(impact_system, ptemplate);
      ptemplate->on_idle();
      }
      }
      else if (lCount == 1)
      {
      VERIFY(!thread::on_idle(lCount));
      }
      return lCount < 1;  // more to do if lCount < 1*/
      return 0;
   }

   /////////////////////////////////////////////////////////////////////////////
   // Special exception handling

   void application::process_window_procedure_exception(::exception::base* e,signal_details * pobj)
   {
      ENSURE_ARG(e != NULL);
      ENSURE_ARG(pobj != NULL);
      SCAST_PTR(::message::base,pbase,pobj);
      // handle certain messages in thread
      switch(pbase->m_uiMessage)
      {
      case WM_CREATE:
      case WM_PAINT:
         return thread::process_window_procedure_exception(e,pobj);
      }

      // handle all the rest
      //linux UINT nIDP = __IDP_INTERNAL_FAILURE;   // generic message string
      const char * nIDP = "Internal Failure";
      pbase->set_lresult(0);        // sensible default
      if(pbase->m_uiMessage == WM_COMMAND)
      {
         if(pbase->m_lparam == 0)
            //linux nIDP = __IDP_COMMAND_FAILURE; // command (not from a control)
            nIDP = "Command Failure";
         pbase->set_lresult((LRESULT)TRUE);        // pretend the command was handled
      }
      if(base_class < memory_exception >::bases(e))
      {
         e->ReportError(MB_ICONEXCLAMATION | MB_SYSTEMMODAL,nIDP);
      }
      else if(base_class < user_exception >::bases(e))
      {
         // ::fontopus::user has not been alerted yet of this catastrophic problem
         e->ReportError(MB_ICONSTOP,nIDP);
      }
   }

   bool application::_001OnCmdMsg(::axis::cmd_msg * pcmdmsg)

   {
      if(command_target_interface::_001OnCmdMsg(pcmdmsg))
         return TRUE;
      return 0;
   }



   /*
   bool application::hex_to_memory(primitive::memory & memory, const char * pszHex)
   {
   ::count len = strlen(pszHex);
   ::count count = (len + 1) / 2;
   memory.allocate(count);
   index i = 0;
   byte b;
   while(*pszHex != '\0')
   {
   char ch = (char) tolower(*pszHex);
   if(ch >= '0' && ch <= '9')
   {
   b = ch - '0';
   }
   else if(ch >= 'a' && ch <= 'f')
   {
   b = ch - 'a' + 10;
   }
   else
   {
   return false;
   }
   pszHex++;
   if(*pszHex == '\0')
   {
   memory.get_data()[i] = b;
   return true;
   }
   b = b << 4;
   ch = (char) tolower(*pszHex);
   if(ch >= '0' && ch <= '9')
   {
   b |= (ch - '0');
   }
   else if(ch >= 'a' && ch <= 'f')
   {
   b |= (ch - 'a' + 10);
   }
   else
   {
   return false;
   }
   pszHex++;
   memory.get_data()[i] = b;
   i++;
   }
   return true;
   }


   void application::memory_to_hex(string & strHex, primitive::memory & memory)
   {
   ::count count = memory.get_size();
   LPSTR lpsz = strHex.GetBufferSetLength(count * 2);
   for(index i = 0; i < count; i++)
   {
   *lpsz++ = ::hex::lower_from((byte) ((memory.get_data()[i] >> 4) & 0xf));
   *lpsz++ = ::hex::lower_from((byte) (memory.get_data()[i] & 0xf));
   }
   strHex.ReleaseBuffer(count * 2);
   }
   */











   // // BEGIN_MESSAGE_MAP(application, command_target)
   //{{__MSG_MAP(application)
   // Global File commands
   //   ON_COMMAND(ID_APP_EXIT, &application::OnAppExit)
   // MRU - most recently used file menu
   //   ON_UPDATE_COMMAND_UI(ID_FILE_MRU_FILE1, &application::OnUpdateRecentFileMenu)
   //   ON_COMMAND_EX_RANGE(ID_FILE_MRU_FILE1, ID_FILE_MRU_FILE16, &application::OnOpenRecentFile)
   //}}__MSG_MAP
   // // END_MESSAGE_MAP()

   /*#ifdef WINDOWS


   typedef LANGID (WINAPI*PFNGETUSERDEFAULTUILANGUAGE)();
   typedef LANGID (WINAPI*PFNGETSYSTEMDEFAULTUILANGUAGE)();


   class CActivationContext
   {
   protected :
   HANDLE m_hCtxt;
   uint_ptr m_uCookie;

   // If pointers are NULL then we are on a platform that does not support WinSXS.
   typedef HANDLE (WINAPI * PFNCreateActCtx)(PCACTCTX);
   static PFNCreateActCtx s_pfnCreateActCtx;

   typedef void (WINAPI * PFNReleaseActCtx)(HANDLE);
   static PFNReleaseActCtx s_pfnReleaseActCtx;

   typedef bool (WINAPI * PFNActivateActCtx)(HANDLE, uint_ptr*);
   static PFNActivateActCtx s_pfnActivateActCtx;

   typedef bool (WINAPI * PFNDeactivateActCtx)(uint32_t, uint_ptr);
   static PFNDeactivateActCtx s_pfnDeactivateActCtx;

   static bool s_bPFNInitialized;

   public:
   CActivationContext(HANDLE hCtxt = INVALID_HANDLE_VALUE) : m_hCtxt( hCtxt ), m_uCookie( 0 )
   {
   // Multiple threads initializing is fine since they will initialize the pointers to the
   // same value.
   if (!s_bPFNInitialized)
   {
   HMODULE hKernel = GetModuleHandle("KERNEL32");
   ENSURE (hKernel != NULL);
   #ifdef _UNICODE
   s_pfnCreateActCtx = (PFNCreateActCtx) GetProcAddress(hKernel, "CreateActCtxW");
   #else
   s_pfnCreateActCtx = (PFNCreateActCtx) GetProcAddress(hKernel, "CreateActCtxA");
   #endif
   s_pfnReleaseActCtx = (PFNReleaseActCtx) GetProcAddress(hKernel, "ReleaseActCtx");
   s_pfnActivateActCtx = (PFNActivateActCtx) GetProcAddress(hKernel, "ActivateActCtx");
   s_pfnDeactivateActCtx = (PFNDeactivateActCtx) GetProcAddress(hKernel, "DeactivateActCtx");
   if (s_pfnCreateActCtx != NULL)
   {
   // If one of the functions is present then all the functions have to be present.
   ENSURE( s_pfnReleaseActCtx != NULL &&
   s_pfnActivateActCtx != NULL &&
   s_pfnDeactivateActCtx != NULL);
   }
   else
   {
   // If one of the functions is not present then all the functions should not be present.
   ENSURE( s_pfnReleaseActCtx == NULL &&
   s_pfnActivateActCtx == NULL &&
   s_pfnDeactivateActCtx == NULL);
   }
   s_bPFNInitialized = true;
   }
   };

   ~CActivationContext()
   {
   Release();
   }

   bool create( PCACTCTX pactctx )
   {
   // NULL on a platform that do not support WinSXS
   if (s_pfnCreateActCtx == NULL)
   {
   return true;
   }

   ASSERT( pactctx != NULL );
   if ( pactctx == NULL )
   {
   return false;
   }

   ASSERT( m_hCtxt == INVALID_HANDLE_VALUE );
   if ( m_hCtxt != INVALID_HANDLE_VALUE )
   {
   return false;
   }

   return ( ( m_hCtxt = s_pfnCreateActCtx( pactctx ) ) != INVALID_HANDLE_VALUE );
   }

   void Release()
   {
   // NULL on a platform that do not support WinSXS
   if (s_pfnReleaseActCtx == NULL)
   {
   return;
   }

   if ( m_hCtxt != INVALID_HANDLE_VALUE )
   {
   Deactivate();
   s_pfnReleaseActCtx( m_hCtxt );
   }
   }

   bool Activate()
   {
   // NULL on a platform that do not support WinSXS
   if (s_pfnActivateActCtx == NULL)
   {
   return true;
   }

   ASSERT( m_hCtxt != INVALID_HANDLE_VALUE );
   if ( m_hCtxt == INVALID_HANDLE_VALUE )
   {
   return false;
   }

   ASSERT( m_uCookie == 0 );
   if ( m_uCookie != 0 )
   {
   return false;
   }

   return ( s_pfnActivateActCtx( m_hCtxt, &m_uCookie) == TRUE );
   }

   bool Deactivate()
   {
   // NULL on a platform that do not support WinSXS
   if (s_pfnDeactivateActCtx == NULL)
   {
   return true;
   }

   if ( m_uCookie != 0 )
   {
   uint_ptr uCookie = m_uCookie;
   m_uCookie = 0;
   return ( s_pfnDeactivateActCtx(0, uCookie) == TRUE );
   }
   return true;
   }
   };


   CActivationContext::PFNCreateActCtx CActivationContext::s_pfnCreateActCtx = NULL;
   CActivationContext::PFNReleaseActCtx CActivationContext::s_pfnReleaseActCtx = NULL;
   CActivationContext::PFNActivateActCtx CActivationContext::s_pfnActivateActCtx = NULL;
   CActivationContext::PFNDeactivateActCtx CActivationContext::s_pfnDeactivateActCtx = NULL;
   bool CActivationContext::s_bPFNInitialized = false;


   // HINSTANCE of the module
   extern "C" IMAGE_DOS_HEADER __ImageBase;

   */


   bool application::LoadSysPolicies()
   {
      return _LoadSysPolicies();
   }

   // This function is not exception safe - will leak a registry key if exceptions are thrown from some places
   // To reduce risk of leaks, I've declared the whole function throw(). This despite the fact that its callers have
   // no dependency on non-throwing.
   bool application::_LoadSysPolicies() throw()
   {

#ifdef WINDOWSEX

      HKEY hkPolicy = NULL;
      DWORD dwValue = 0;
      DWORD dwDataLen = sizeof(dwValue);
      DWORD dwType = 0;

      // clear current policy settings.
      m_dwPolicies = ___SYSPOLICY_NOTINITIALIZED;

      static __system_policy_data rgExplorerData[] =
      {
         {"NoRun",___SYSPOLICY_NORUN},
         {"NoDrives",___SYSPOLICY_NODRIVES},
         {"RestrictRun",___SYSPOLICY_RESTRICTRUN},
         {"NoNetConnectDisconnect",___SYSPOLICY_NONETCONNECTDISCONNECTD},
         {"NoRecentDocsHistory",___SYSPOLICY_NORECENTDOCHISTORY},
         {"NoClose",___SYSPOLICY_NOCLOSE},
         {NULL,0}
      };

      static __system_policy_data rgNetworkData[] =
      {
         {"NoEntireNetwork",___SYSPOLICY_NOENTIRENETWORK},
         {NULL,0}
      };

      static __system_policy_data rgComDlgData[] =
      {
         {"NoPlacesBar",___SYSPOLICY_NOPLACESBAR},
         {"NoBackButton",___SYSPOLICY_NOBACKBUTTON},
         {"NoFileMru",___SYSPOLICY_NOFILEMRU},
         {NULL,0}
      };

      static __system_policies rgPolicies[] =
      {
         {"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",
         rgExplorerData},
         {"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",
         rgNetworkData},
         {"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Comdlg32",
         rgComDlgData},
         {NULL,0}
      };

      __system_policies *pPolicies = rgPolicies;
      __system_policy_data *pData = NULL;

      while(pPolicies->szPolicyKey != NULL)
      {

         if(ERROR_SUCCESS == ::RegOpenKeyEx(
            HKEY_CURRENT_USER,
            pPolicies->szPolicyKey,
            0,
            KEY_QUERY_VALUE,
            &hkPolicy
            ))
         {
            pData = pPolicies->pData;
            while(pData->szPolicyName)
            {
               if(ERROR_SUCCESS == ::RegQueryValueEx(
                  hkPolicy,
                  pData->szPolicyName,
                  NULL,
                  &dwType,
                  (BYTE*)&dwValue,
                  &dwDataLen))
               {
                  if(dwType == REG_DWORD)
                  {
                     if(dwValue != 0)
                        m_dwPolicies |= pData->dwID;
                     else
                        m_dwPolicies &= ~pData->dwID;
                  }
               }
               dwValue = 0;
               dwDataLen = sizeof(dwValue);
               dwType = 0;
               pData++;
            }
            ::RegCloseKey(hkPolicy);
            hkPolicy = NULL;
         }
         pPolicies++;
      };

#endif

      return TRUE;


   }

   bool application::GetSysPolicyValue(uint32_t dwPolicyID,bool *pbValue)
   {
      if(!pbValue)
         return FALSE; // bad pointer
      *pbValue = (m_dwPolicies & dwPolicyID) != 0;
      return TRUE;
   }

   bool application::InitApplication()
   {


      LoadSysPolicies();

      return TRUE;


   }



   /*   void application::LoadStdProfileSettings(UINT nMaxMRU)
   {
   UNREFERENCED_PARAMETER(nMaxMRU);
   ASSERT_VALID(this);

   // 0 by default means not set
   m_nNumPreviewPages = GetProfileInt(gen_PreviewSection, gen_PreviewEntry, 0);
   }*/

   /*void application::ParseCommandLine(CCommandLineInfo& rCmdInfo)
   {
   for (int32_t i = 1; i < __argc; i++)
   {
   const char * pszParam = __targv[i];
   bool bFlag = FALSE;
   bool bLast = ((i + 1) == __argc);
   if (pszParam[0] == '-' || pszParam[0] == '/')
   {
   // remove flag specifier
   bFlag = TRUE;
   ++pszParam;
   }
   rCmdInfo.ParseParam(pszParam, bFlag, bLast);
   }
   }*/

   /////////////////////////////////////////////////////////////////////////////
   // CCommandLineInfo implementation

   /*CCommandLineInfo::CCommandLineInfo()
   {
   m_bShowSplash = TRUE;
   m_bRunEmbedded = FALSE;
   m_bRunAutomated = FALSE;
   m_nShellCommand = FileNew;
   }

   CCommandLineInfo::~CCommandLineInfo()
   {
   }

   void CCommandLineInfo::ParseParam(const char* pszParam,bool bFlag,bool bLast)
   {
   if (bFlag)
   {
   const astring strParam(pszParam);
   ParseParamFlag(strParam.GetString());
   }
   else
   ParseParamNotFlag(pszParam);

   ParseLast(bLast);
   }*/

   /*
   #ifdef UNICODE
   void CCommandLineInfo::ParseParam(const char* pszParam, bool bFlag, bool bLast)
   {
   if (bFlag)
   ParseParamFlag(pszParam);
   else
   ParseParamNotFlag(pszParam);

   ParseLast(bLast);
   }
   #endif // UNICODE
   */

   /*
   void CCommandLineInfo::ParseParamFlag(const char* pszParam)
   {
   // OLE command switches are case insensitive, while
   // shell command switches are case sensitive

   if (lstrcmpA(pszParam, "pt") == 0)
   m_nShellCommand = FilePrintTo;
   else if (lstrcmpA(pszParam, "p") == 0)
   m_nShellCommand = FilePrint;
   else if (::__invariant_stricmp(pszParam, "Register") == 0 ||
   ::__invariant_stricmp(pszParam, "Regserver") == 0)
   m_nShellCommand = AppRegister;
   else if (::__invariant_stricmp(pszParam, "Unregister") == 0 ||
   ::__invariant_stricmp(pszParam, "Unregserver") == 0)
   m_nShellCommand = AppUnregister;
   else if (lstrcmpA(pszParam, "dde") == 0)
   {
   m_nShellCommand = FileDDE;
   }
   else if (::__invariant_stricmp(pszParam, "Embedding") == 0)
   {
   m_bRunEmbedded = TRUE;
   m_bShowSplash = FALSE;
   }
   else if (::__invariant_stricmp(pszParam, "Automation") == 0)
   {
   m_bRunAutomated = TRUE;
   m_bShowSplash = FALSE;
   }
   }

   void CCommandLineInfo::ParseParamNotFlag(const char* pszParam)
   {
   if (m_strFileName.is_empty())
   m_strFileName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strPrinterName.is_empty())
   m_strPrinterName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strDriverName.is_empty())
   m_strDriverName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strPortName.is_empty())
   m_strPortName = pszParam;
   }

   #ifdef UNICODE
   void CCommandLineInfo::ParseParamNotFlag(const char* pszParam)
   {
   if (m_strFileName.is_empty())
   m_strFileName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strPrinterName.is_empty())
   m_strPrinterName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strDriverName.is_empty())
   m_strDriverName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strPortName.is_empty())
   m_strPortName = pszParam;
   }
   #endif

   void CCommandLineInfo::ParseLast(bool bLast)
   {
   if (bLast)
   {
   if (m_nShellCommand == FileNew && !m_strFileName.is_empty())
   m_nShellCommand = FileOpen;
   m_bShowSplash = !m_bRunEmbedded && !m_bRunAutomated;
   }
   }
   */

   /////////////////////////////////////////////////////////////////////////////
   // App termination

   void application::SaveStdProfileSettings()
   {
      ASSERT_VALID(this);


      //      if (m_nNumPreviewPages != 0)
      //       WriteProfileInt(gen_PreviewSection, gen_PreviewEntry, m_nNumPreviewPages);
   }






#ifdef WINDOWSEX


   /////////////////////////////////////////////////////////////////////////////
   // WinHelp Helper


   void application::WinHelp(uint_ptr dwData,UINT nCmd)
   {
      UNREFERENCED_PARAMETER(dwData);
      UNREFERENCED_PARAMETER(nCmd);

      // return global cast help mode state to FALSE (backward compatibility)
      m_bHelpMode = FALSE;
      // trans pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle update

      //trans pMainWnd->WinHelp(dwData, nCmd);
   }

   /////////////////////////////////////////////////////////////////////////////
   // HtmlHelp Helper

   void application::HtmlHelp(uint_ptr dwData,UINT nCmd)
   {

      UNREFERENCED_PARAMETER(dwData);

      UNREFERENCED_PARAMETER(nCmd);

      // return global cast help mode state to FALSE (backward compatibility)
      m_bHelpMode = FALSE;
      // trans pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle update

      // trans pMainWnd->HtmlHelp(dwData, nCmd);
   }


   void application::WinHelpInternal(uint_ptr dwData,UINT nCmd)
   {
      UNREFERENCED_PARAMETER(dwData);
      UNREFERENCED_PARAMETER(nCmd);
      //   sp(::user::interaction) pMainWnd = System.m_puiMain;
      //   ENSURE_VALID(pMainWnd);

      // return global cast help mode state to FALSE (backward compatibility)
      m_bHelpMode = FALSE;
      // trans pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle update
      // trans pMainWnd->WinHelpInternal(dwData, nCmd);
   }


#endif





   /////////////////////////////////////////////////////////////////////////////
   // application idle processing

   void application::DevModeChange(LPTSTR lpDeviceName)
   {
      UNREFERENCED_PARAMETER(lpDeviceName);

#ifdef WINDOWS
      if(m_hDevNames == NULL)
         return;

#endif

   }



   bool application::on_run_exception(::exception::exception & e)
   {

      ::OutputDebugString("An unexpected error has occurred and no special exception handling is available.");

      if(typeid(e) == typeid(not_installed))
      {

         not_installed & notinstalled = dynamic_cast <not_installed &> (e);

         if(::is_debugger_attached() && !file_exists_dup("C:\\ca2\\config\\plugin\\disable_manual_install_warning.txt"))
         {

            try
            {

               if(!(bool)System.oprop("not_installed_message_already_shown"))
               {

                  ::simple_message_box(NULL,"Debug only message, please install:\n\n\n\t" + notinstalled.m_strId + "\n\ttype = " + notinstalled.m_strType + "\n\tlocale = " + notinstalled.m_strLocale + "\n\tschema = " + notinstalled.m_strSchema + "\n\tbuild number = " + notinstalled.m_strBuild + "\n\n\nThere are helper scripts under <solution directory>/nodeapp/stage/install/","Debug only message, please install.",MB_ICONINFORMATION | MB_OK);

                  System.oprop("not_installed_message_already_shown") = true;

               }

            }
            catch(...)
            {

            }

         }
         else
         {

            hotplugin::host::host_starter_start_sync(": app=session session_start=" + notinstalled.m_strId + " app_type=" + notinstalled.m_strType + " install locale=" + notinstalled.m_strLocale + " schema=" + notinstalled.m_strSchema,get_app(),NULL);

         }

         return false;

      }

      //simple_message_box_timeout("An unexpected error has occurred and no special exception handling is available.<br>Timeout: $simple_message_box_timeout", 5000);

      return true; // continue or exit application? by default: continue by returning true

   }







   bool application::final_handle_exception(::exception::exception & e)
   {
      UNREFERENCED_PARAMETER(e);
      //linux      exit(-1);

      if(!is_system())
      {

         // get_app() may be it self, it is ok...
         if(Sys(get_app()).final_handle_exception((::exception::exception &) e))
            return true;


      }

      return false;
   }


   /*   bool application::open_link(const char * pszLink, const char * pszTarget)
   {
   UNREFERENCED_PARAMETER(pszLink);
   UNREFERENCED_PARAMETER(pszTarget);
   return false;
   }
   */










   void application::_001OnFileNew()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      /*      if (m_pdocmanager != NULL)
      m_pdocmanager->_001OnFileNew();*/
   }

   void application::on_file_open()
   {
      ENSURE(m_pdocmanager != NULL);
      //m_pdocmanager->on_file_open();
   }

   // prompt for file name - used for open and save as
   bool application::do_prompt_file_name(var & varFile,UINT nIDSTitle,uint32_t lFlags,bool bOpenFileDialog,sp(::user::impact_system) ptemplate,sp(::user::document) pdocument)
      // if ptemplate==NULL => all document templates
   {
      if(Platform.m_pfilemanager != NULL)
      {
         return Platform.m_pfilemanager->do_prompt_file_name(varFile,nIDSTitle,lFlags,bOpenFileDialog,ptemplate,pdocument);
      }
      ENSURE(m_pdocmanager != NULL);
      /*      return m_pdocmanager->do_prompt_file_name(fileName, nIDSTitle, lFlags,
      bOpenFileDialog, ptemplate);*/
      return FALSE;
   }

   // This is core API library.
   //
   //
   //
   //
   //
   //
   //
   //




   /*void ::core::FormatString1(string & rString, UINT nIDS, const char * lpsz1)
   {
   __format_strings(rString, nIDS, &lpsz1, 1);
   }

   void ::core::FormatString2(string & rString, UINT nIDS, const char * lpsz1,
   const char * lpsz2)
   {
   const char * rglpsz[2];
   rglpsz[0] = lpsz1;
   rglpsz[1] = lpsz2;
   __format_strings(rString, nIDS, rglpsz, 2);
   }*/

   /////////////////////////////////////////////////////////////////////////////


   /////////////////////////////////////////////////////////////////////////////
   // Basic Help support (for backward compatibility to core API 2.0)

   void application::OnHelp()  // use context to derive help context
   {
      if(m_dwPromptContext != 0)
      {
         // do not call WinHelp when the error is failing to lauch help
         //         if (m_dwPromptContext != HID_BASE_PROMPT+__IDP_FAILED_TO_LAUNCH_HELP)
         //          WinHelpInternal(m_dwPromptContext);
         return;
      }

      // otherwise, use window::OnHelp implementation
      /* trans ::window_sp pwindow = System.m_puiMain;
      ENSURE_VALID(pwindow);
      if (!pwindow->is_frame_window())
      pwindow->OnHelp();
      else
      ((pwindow))->OnHelp();*/
   }


   void application::OnHelpIndex()
   {

#ifdef WINDOWSEX

      WinHelpInternal(0L,HELP_INDEX);

#endif

   }


   void application::OnHelpFinder()
   {

#ifdef WINDOWSEX

      WinHelpInternal(0L,HELP_FINDER);

#endif

   }


   void application::OnHelpUsing()
   {

#ifdef WINDOWSEX

      WinHelpInternal(0L,HELP_HELPONHELP);

#endif

   }


   /////////////////////////////////////////////////////////////////////////////
   // Context Help Mode support (backward compatibility to core API 2.0)

   void application::OnContextHelp()
   {
      // just use frame_window::OnContextHelp implementation
      /* trans   m_bHelpMode = HELP_ACTIVE;
      sp(::user::frame_window) pMainWnd = (System.m_puiMain);
      ENSURE_VALID(pMainWnd);
      ENSURE(pMainWnd->is_frame_window());
      pMainWnd->OnContextHelp();
      m_bHelpMode = pMainWnd->m_bHelpMode;
      pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle update */
   }

   /////////////////////////////////////////////////////////////////////////////


   // This is core API library.
   //
   //
   //
   //
   //
   //
   //
   //




   /////////////////////////////////////////////////////////////////////////////
   // WinApp support for printing

   /*bool application::GetPrinterDeviceDefaults(PRINTDLG* pPrintDlg)
   {
   UpdatePrinterSelection(m_hDevNames == NULL); //force default if no current
   if (m_hDevNames == NULL)
   return FALSE;               // no printer defaults

   ENSURE_ARG(pPrintDlg != NULL);
   pPrintDlg->hDevNames = m_hDevNames;
   pPrintDlg->hDevMode = m_hDevMode;

   ::GlobalUnlock(m_hDevNames);
   ::GlobalUnlock(m_hDevMode);
   return TRUE;
   }*/

   void application::UpdatePrinterSelection(bool bForceDefaults)
   {
      UNREFERENCED_PARAMETER(bForceDefaults);
   }


   void application::OnFilePrintSetup()
   {
   }

   void application::SelectPrinter(HANDLE hDevNames,HANDLE hDevMode,bool bFreeOld)
   {
      UNREFERENCED_PARAMETER(hDevNames);
      UNREFERENCED_PARAMETER(hDevMode);
      UNREFERENCED_PARAMETER(bFreeOld);
      throw not_implemented(get_app());
   }

   ::draw2d::graphics * application::CreatePrinterDC()
   {
      throw not_implemented(get_app());
   }

   /////////////////////////////////////////////////////////////////////////////


   // This is core API library.
   //
   //
   //
   //
   //
   //
   //
   //



   /////////////////////////////////////////////////////////////////////////////
   // application User Interface Extensions

   void application::OnAppExit()
   {

      // same as double-clicking on main window close box

      ASSERT(m_puiMain != NULL);

      m_puiMain->send_message(WM_CLOSE);

   }


   void application::HideApplication()
   {
      try
      {
         if(m_puiMain == NULL)
            return;

         // hide the application's windows before closing all the documents
         m_puiMain->ShowWindow(SW_HIDE);
         // trans    m_puiMain->ShowOwnedPopups(FALSE);

         // put the window at the bottom of zorder, so it isn't activated
         m_puiMain->SetWindowPos(ZORDER_BOTTOM,0,0,0,0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
      }
      catch(...)
      {
      }

   }





   bool application::save_all_modified()
   {
      /*      if (m_pdocmanager != NULL)
      return m_pdocmanager->save_all_modified();*/
      return TRUE;
   }

   void application::close_all_documents(bool bEndSession)
   {
      /*if (m_pdocmanager != NULL)
      m_pdocmanager->close_all_documents(bEndSession);*/
   }


   bool application::OnDDECommand(LPTSTR lpszCommand)
   {
      /*      if (m_pdocmanager != NULL)
      return m_pdocmanager->OnDDECommand(lpszCommand);
      else*/
      return FALSE;
   }



   void application::EnableModeless(bool bEnable)
   {
      DoEnableModeless(bEnable);
   }

   void application::DoEnableModeless(bool bEnable)
   {
      UNREFERENCED_PARAMETER(bEnable);
#ifdef ___NO_OLE_SUPPORT
      UNUSED(bEnable);
#endif

      // no-op if main window is NULL or not a frame_window
      /*   sp(::user::interaction) pMainWnd = System.m_puiMain;
      if (pMainWnd == NULL || !pMainWnd->is_frame_window())
      return;*/

#ifndef ___NO_OLE_SUPPORT
      // check if notify hook installed
      /*xxx
      ASSERT_KINDOF(frame_window, pMainWnd);
      sp(::user::frame_window) pFrameWnd = (sp(::user::frame_window))pMainWnd;
      if (pFrameWnd->m_pNotifyHook != NULL)
      pFrameWnd->m_pNotifyHook->OnEnableModeless(bEnable);
      */
#endif
   }

   int32_t application::DoMessageBox(const char * lpszPrompt,UINT nType,UINT nIDPrompt)
   {
      return ShowAppMessageBox(this,lpszPrompt,nType,nIDPrompt);
   }



#ifdef WINDOWS

   int32_t application::simple_message_box(sp(::user::interaction) pwndOwner,UINT fuStyle,const char * pszFormat,...)
   {
      va_list va;
      va_start(va,pszFormat);
      string str;
      str.FormatV(pszFormat,va);
      va_end(va);
      return simple_message_box(pwndOwner,str,fuStyle);
   }

#endif


   // Helper for message boxes; can work when no application can be found
   int32_t application::ShowAppMessageBox(sp(application)pApp,const char * lpszPrompt,UINT nType,UINT nIDPrompt)
   {

      throw not_implemented(pApp);

   }


   /* int32_t ::core::simple_message_box(const char * lpszText, UINT nType, UINT nIDHelp)
   {
   application* papp = &System;
   if (papp != NULL)
   {
   return papp->m_pcoreapp->DoMessageBox(lpszText, nType, nIDHelp);
   }
   else
   {
   return application::ShowAppMessageBox(NULL, lpszText, nType, nIDHelp);
   }
   }
   */

   /*int32_t System.simple_message_box(UINT nIDPrompt, UINT nType, UINT nIDHelp)
   {
   string string;
   if (!string.load_string(nIDPrompt))
   {
   TRACE(::axis::trace::category_AppMsg, 0, "Error: failed to load message box prompt string 0x%04x.\n",
   nIDPrompt);
   ASSERT(FALSE);
   }
   if (nIDHelp == (UINT)-1)
   nIDHelp = nIDPrompt;
   return System.simple_message_box(string, nType, nIDHelp);
   }*/







   /*bool application::ProcessShellCommand(CCommandLineInfo& rCmdInfo)
   {
   bool bResult = TRUE;
   switch (rCmdInfo.m_nShellCommand)
   {
   case CCommandLineInfo::FileNew:
   if (!System._001SendCommand("file::new"))
   _001OnFileNew();
   if (m_puiMain == NULL)
   bResult = FALSE;
   break;

   // If we've been asked to open a file, call open_document_file()

   case CCommandLineInfo::FileOpen:
   if (!open_document_file(rCmdInfo.m_strFileName))
   bResult = FALSE;
   break;

   // If the ::fontopus::user wanted to print, hide our main window and
   // fire a message to ourselves to start the printing

   case CCommandLineInfo::FilePrintTo:
   case CCommandLineInfo::FilePrint:
   m_nCmdShow = SW_HIDE;
   ASSERT(m_pCmdInfo == NULL);
   if(open_document_file(rCmdInfo.m_strFileName))
   {
   m_pCmdInfo = &rCmdInfo;
   ENSURE_VALID(m_puiMain);
   m_puiMain->SendMessage(WM_COMMAND, ID_FILE_PRINT_DIRECT);
   m_pCmdInfo = NULL;
   }
   bResult = FALSE;
   break;

   // If we're doing DDE, hide ourselves

   case CCommandLineInfo::FileDDE:
   m_pCmdInfo = (CCommandLineInfo*)(uint_ptr)m_nCmdShow;
   m_nCmdShow = SW_HIDE;
   break;

   // If we've been asked to register, exit without showing UI.
   // Registration was already done in initialize_instance().
   case CCommandLineInfo::AppRegister:
   {
   Register();
   bResult = FALSE;    // that's all we do

   // If nobody is using it already, we can use it.
   // We'll flag that we're unregistering and not save our state
   // on the way out. This new object gets deleted by the
   // cast object destructor.

   if (m_pCmdInfo == NULL)
   {
   m_pCmdInfo = new CCommandLineInfo;
   m_pCmdInfo->m_nShellCommand = CCommandLineInfo::AppUnregister;
   }
   break;
   }

   // If we've been asked to unregister, unregister and then terminate
   case CCommandLineInfo::AppUnregister:
   {
   bool bUnregistered = Unregister();

   // if you specify /EMBEDDED, we won't make an success/failure box
   // this use of /EMBEDDED is not related to OLE

   if (!rCmdInfo.m_bRunEmbedded)
   {
   /* linux
   if (bUnregistered)
   System.simple_message_box(__IDP_UNREG_DONE);
   else
   System.simple_message_box(__IDP_UNREG_FAILURE);
   */

   /*if (bUnregistered)
   System.simple_message_box("System unregistered");
   else
   System.simple_message_box("Failed to unregister application");

   }
   bResult = FALSE;    // that's all we do

   // If nobody is using it already, we can use it.
   // We'll flag that we're unregistering and not save our state
   // on the way out. This new object gets deleted by the
   // cast object destructor.

   if (m_pCmdInfo == NULL)
   {
   m_pCmdInfo = new CCommandLineInfo;
   m_pCmdInfo->m_nShellCommand = CCommandLineInfo::AppUnregister;
   }
   }
   break;
   }
   return bResult;
   }*/

   /*   void application::InitLibId()
   {
   }

   bool application::Register()
   {
   return TRUE;
   }

   bool application::Unregister()
   {
   HKEY    hKey = 0;
   char   szBuf[_MAX_PATH+1];
   LONG    cSize = 0;
   bool    bRet = TRUE;

   /*xxx POSITION pos = get_template_count();
   while (pos != NULL)
   {
   sp(impact_system) pTempl = get_template(pos);
   if (pTempl != NULL)
   pTempl->on_simple_action(0, CN_OLE_UNREGISTER, NULL, NULL);
   }*/

   // remove profile information -- the registry entries exist if
   // SetRegistryKey() was used.

   /*    if (m_pszRegistryKey)
   {
   ENSURE(m_pszProfileName != NULL);

   string strKey = "Software\\";
   strKey += m_pszRegistryKey;
   string strSubKey = strKey + "\\" + m_pszProfileName;

   DelRegTree(HKEY_CURRENT_USER, strSubKey);

   // If registry key is is_empty then remove it

   uint32_t   dwResult;
   if ((dwResult = ::RegOpenKey(HKEY_CURRENT_USER, strKey, &hKey)) ==
   ERROR_SUCCESS)
   {
   if (::RegEnumKey(hKey, 0, szBuf, _MAX_PATH) == ERROR_NO_MORE_ITEMS)
   DelRegTree(HKEY_CURRENT_USER, strKey);
   ::RegCloseKey(hKey);
   }
   if (RegQueryValue(HKEY_CURRENT_USER, strSubKey, szBuf, &cSize) == ERROR_SUCCESS)
   bRet = TRUE;
   }
   return bRet;
   }*/

   //   LONG delete_registry_tree_helper(HKEY hParentKey, const string & strKeyName);

   // Under Win32, a reg key may not be deleted unless it is is_empty.
   // Thus, to delete a tree,  one must recursively enumerate and
   // delete all of the sub-keys.

   /*LONG application::DelRegTree(HKEY hParentKey, const string & strKeyName)
   {
   return delete_registry_tree_helper(hParentKey, strKeyName);
   }

   LONG delete_registry_tree_helper(HKEY hParentKey, const string & strKeyName)
   {
   char   szSubKeyName[MAX_PATH + 1];
   HKEY    hCurrentKey;
   uint32_t   dwResult;

   if ((dwResult = RegOpenKey(hParentKey, strKeyName, &hCurrentKey)) ==
   ERROR_SUCCESS)
   {
   // remove all subkeys of the key to delete
   while ((dwResult = RegEnumKey(hCurrentKey, 0, szSubKeyName, MAX_PATH)) ==
   ERROR_SUCCESS)
   {
   try
   {
   // temp string constructed from szSubKeyName can throw in Low Memory condition.
   if ((dwResult = delete_registry_tree_helper(hCurrentKey, szSubKeyName)) != ERROR_SUCCESS)
   break;
   }
   catch(memory_exception* e)
   {
   dwResult = ERROR_NOT_ENOUGH_MEMORY;
   e->Delete();
   break;
   }
   }

   // If all went well, we should now be able to delete the requested key
   if ((dwResult == ERROR_NO_MORE_ITEMS) || (dwResult == ERROR_BADKEY))
   {
   dwResult = RegDeleteKey(hParentKey, strKeyName);
   }
   RegCloseKey(hCurrentKey);
   }

   return dwResult;
   }*/

   //void application::EnableShellOpen()
   //{
   /*   ASSERT(m_atomApp == NULL && m_atomSystemTopic == NULL); // do once
   if (m_atomApp != NULL || m_atomSystemTopic != NULL)
   {
   return;
   }

   // Win95 & Win98 sends a WM_DDE_INITIATE with an atom that points to the
   // int16_t file name so we need to use the int16_t file name.
   string strShortName;
   __get_module_short_file_name(System.m_hInstance, strShortName);

   // strip out path
   string strFileName = ::PathFindFileName(strShortName);
   // strip out extension
   LPTSTR pszFileName = strFileName.GetBuffer();
   ::PathRemoveExtension(pszFileName);
   strFileName.ReleaseBuffer();

   m_atomApp = ::GlobalAddAtom(strFileName);
   m_atomSystemTopic = ::GlobalAddAtom("system");*/
   //}

   void application::RegisterShellFileTypes(bool bCompat)
   {
      ENSURE(m_pdocmanager != NULL);
      //      m_pdocmanager->RegisterShellFileTypes(bCompat);
   }

   void application::UnregisterShellFileTypes()
   {
      ENSURE(m_pdocmanager != NULL);
      //    m_pdocmanager->UnregisterShellFileTypes();
   }


   int32_t application::get_open_document_count()
   {
      ENSURE(m_pdocmanager != NULL);
      //  return m_pdocmanager->get_open_document_count();
      return 0;
   }


   // This is core API library.
   //
   //
   //
   //
   //
   //
   //
   //

   /////////////////////////////////////////////////////////////////////////////
   // application Settings Helpers


   void application::SetRegistryKey(const char * lpszRegistryKey)
   {
      ASSERT(m_pszRegistryKey == NULL);
      ASSERT(lpszRegistryKey != NULL);
      ASSERT(m_strAppName.has_char());

      //bool bEnable = __enable_memory_tracking(FALSE);
      free((void *)m_pszRegistryKey);
      m_pszRegistryKey = strdup(lpszRegistryKey);
      free((void *)m_pszProfileName);
      m_pszProfileName = strdup(m_strAppName);
      //__enable_memory_tracking(bEnable);
   }

   void application::SetRegistryKey(UINT nIDRegistryKey)
   {
      UNREFERENCED_PARAMETER(nIDRegistryKey);
      ASSERT(m_pszRegistryKey == NULL);
      throw not_implemented(get_app());
      /*char szRegistryKey[256];
      VERIFY(::core::LoadString(nIDRegistryKey, szRegistryKey));
      SetRegistryKey(szRegistryKey);*/
   }


#ifdef WINDOWSEX

   // returns key for HKEY_CURRENT_USER\"Software"\RegistryKey\ProfileName
   // creating it if it doesn't exist
   // responsibility of the caller to call RegCloseKey() on the returned HKEY
   HKEY application::GetAppRegistryKey()
   {
      ASSERT(m_pszRegistryKey != NULL);
      ASSERT(m_pszProfileName != NULL);

      HKEY hAppKey = NULL;
      HKEY hSoftKey = NULL;
      HKEY hCompanyKey = NULL;
      if(RegOpenKeyEx(HKEY_CURRENT_USER,"software",0,KEY_WRITE | KEY_READ,
         &hSoftKey) == ERROR_SUCCESS)
      {
         DWORD dw;
         if(RegCreateKeyEx(hSoftKey,m_pszRegistryKey,0,REG_NONE,
            REG_OPTION_NON_VOLATILE,KEY_WRITE | KEY_READ,NULL,
            &hCompanyKey,&dw) == ERROR_SUCCESS)
         {
            RegCreateKeyEx(hCompanyKey,m_pszProfileName,0,REG_NONE,
               REG_OPTION_NON_VOLATILE,KEY_WRITE | KEY_READ,NULL,
               &hAppKey,&dw);
         }
      }
      if(hSoftKey != NULL)
         RegCloseKey(hSoftKey);
      if(hCompanyKey != NULL)
         RegCloseKey(hCompanyKey);

      return hAppKey;
   }

   // returns key for:
   //      HKEY_CURRENT_USER\"Software"\RegistryKey\AppName\lpszSection
   // creating it if it doesn't exist.
   // responsibility of the caller to call RegCloseKey() on the returned HKEY
   HKEY application::GetSectionKey(const char * lpszSection)
   {
      ASSERT(lpszSection != NULL);

      HKEY hSectionKey = NULL;
      HKEY hAppKey = GetAppRegistryKey();
      if(hAppKey == NULL)
         return NULL;

      DWORD dw;
      RegCreateKeyEx(hAppKey,lpszSection,0,REG_NONE,REG_OPTION_NON_VOLATILE,KEY_WRITE | KEY_READ,NULL,&hSectionKey,&dw);
      RegCloseKey(hAppKey);
      return hSectionKey;
   }

#endif

   /*   UINT application::GetProfileInt(const char * lpszSection, const char * lpszEntry,
   int32_t nDefault)
   {
   ASSERT(lpszSection != NULL);
   ASSERT(lpszEntry != NULL);
   if (m_pszRegistryKey != NULL) // use registry
   {
   HKEY hSecKey = GetSectionKey(lpszSection);
   if (hSecKey == NULL)
   return nDefault;
   uint32_t dwValue;
   uint32_t dwType;
   uint32_t dwCount = sizeof(uint32_t);
   LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
   (LPBYTE)&dwValue, &dwCount);
   RegCloseKey(hSecKey);
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_DWORD);
   ASSERT(dwCount == sizeof(dwValue));
   return (UINT)dwValue;
   }
   return nDefault;
   }
   else
   {
   ASSERT(m_pszProfileName != NULL);
   return ::GetPrivateProfileInt(lpszSection, lpszEntry, nDefault,
   m_pszProfileName);
   }
   }

   string application::GetProfileString(const char * lpszSection, const char * lpszEntry,
   const char * lpszDefault)
   {
   ASSERT(lpszSection != NULL);
   ASSERT(lpszEntry != NULL);
   if (m_pszRegistryKey != NULL)
   {
   HKEY hSecKey = GetSectionKey(lpszSection);
   if (hSecKey == NULL)
   return lpszDefault;
   string strValue;
   uint32_t dwType=REG_NONE;
   uint32_t dwCount=0;
   LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
   NULL, &dwCount);
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_SZ);
   lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
   (LPBYTE)strValue.GetBuffer(dwCount/sizeof(char)), &dwCount);
   strValue.ReleaseBuffer();
   }
   RegCloseKey(hSecKey);
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_SZ);
   return strValue;
   }
   return lpszDefault;
   }
   else
   {
   ASSERT(m_pszProfileName != NULL);

   if (lpszDefault == NULL)
   lpszDefault = "";   // don't pass in NULL
   char szT[4096];
   uint32_t dw = ::GetPrivateProfileString(lpszSection, lpszEntry,
   lpszDefault, szT, _countof(szT), m_pszProfileName);
   ASSERT(dw < 4095);
   return szT;
   }
   }

   bool application::GetProfileBinary(const char * lpszSection, const char * lpszEntry,
   BYTE** ppData, UINT* pBytes)
   {
   ASSERT(lpszSection != NULL);
   ASSERT(lpszEntry != NULL);
   ASSERT(ppData != NULL);
   ASSERT(pBytes != NULL);
   *ppData = NULL;
   *pBytes = 0;
   if (m_pszRegistryKey != NULL)
   {
   HKEY hSecKey = GetSectionKey(lpszSection);
   if (hSecKey == NULL)
   {
   return FALSE;
   }

   // ensure destruction

   // linux ::core::CRegKey rkSecKey(hSecKey);

   uint32_t dwType=0;
   uint32_t dwCount=0;
   LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType, NULL, &dwCount);
   *pBytes = dwCount;
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_BINARY);
   *ppData = new BYTE[*pBytes];
   lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
   *ppData, &dwCount);
   }
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_BINARY);
   return TRUE;
   }
   else
   {
   delete [] *ppData;
   *ppData = NULL;
   }
   return FALSE;
   }
   else
   {
   ASSERT(m_pszProfileName != NULL);

   string str = GetProfileString(lpszSection, lpszEntry, NULL);
   if (str.is_empty())
   return FALSE;
   ASSERT(str.get_length()%2 == 0);
   int_ptr nLen = str.get_length();
   *pBytes = UINT(nLen)/2;
   *ppData = new BYTE[*pBytes];
   for (int32_t i=0;i<nLen;i+=2)
   {
   (*ppData)[i/2] = (BYTE)
   (((str[i+1] - 'A') << 4) + (str[i] - 'A'));
   }
   return TRUE;
   }
   }


   bool application::WriteProfileInt(const char * lpszSection, const char * lpszEntry,
   int32_t nValue)
   {
   ASSERT(lpszSection != NULL);
   ASSERT(lpszEntry != NULL);
   if (m_pszRegistryKey != NULL)
   {
   HKEY hSecKey = GetSectionKey(lpszSection);
   if (hSecKey == NULL)
   return FALSE;
   LONG lResult = RegSetValueEx(hSecKey, lpszEntry, NULL, REG_DWORD,
   (LPBYTE)&nValue, sizeof(nValue));
   RegCloseKey(hSecKey);
   return lResult == ERROR_SUCCESS;
   }
   else
   {
   ASSERT(m_pszProfileName != NULL);

   char szT[16];
   _stprintf_s(szT, _countof(szT), "%d", nValue);
   return ::WritePrivateProfileString(lpszSection, lpszEntry, szT,
   m_pszProfileName);
   }
   }

   bool application::WriteProfileString(const char * lpszSection, const char * lpszEntry,
   const char * lpszValue)
   {
   ASSERT(lpszSection != NULL);
   if (m_pszRegistryKey != NULL)
   {
   LONG lResult;
   if (lpszEntry == NULL) //delete whole departament
   {
   HKEY hAppKey = GetAppRegistryKey();
   if (hAppKey == NULL)
   return FALSE;
   lResult = ::RegDeleteKey(hAppKey, lpszSection);
   RegCloseKey(hAppKey);
   }
   else if (lpszValue == NULL)
   {
   HKEY hSecKey = GetSectionKey(lpszSection);
   if (hSecKey == NULL)
   return FALSE;
   // necessary to cast away const below
   lResult = ::RegDeleteValue(hSecKey, (LPTSTR)lpszEntry);
   RegCloseKey(hSecKey);
   }
   else
   {
   HKEY hSecKey = GetSectionKey(lpszSection);
   if (hSecKey == NULL)
   return FALSE;
   lResult = RegSetValueEx(hSecKey, lpszEntry, NULL, REG_SZ,
   (LPBYTE)lpszValue, (lstrlen(lpszValue)+1)*sizeof(char));
   RegCloseKey(hSecKey);
   }
   return lResult == ERROR_SUCCESS;
   }
   else
   {
   ASSERT(m_pszProfileName != NULL);
   ASSERT(lstrlen(m_pszProfileName) < 4095); // can't read in bigger
   return ::WritePrivateProfileString(lpszSection, lpszEntry, lpszValue,
   m_pszProfileName);
   }
   }

   bool application::WriteProfileBinary(const char * lpszSection, const char * lpszEntry,
   LPBYTE pData, UINT nBytes)
   {
   ASSERT(lpszSection != NULL);
   if (m_pszRegistryKey != NULL)
   {
   LONG lResult;
   HKEY hSecKey = GetSectionKey(lpszSection);
   if (hSecKey == NULL)
   return FALSE;
   lResult = RegSetValueEx(hSecKey, lpszEntry, NULL, REG_BINARY,
   pData, nBytes);
   RegCloseKey(hSecKey);
   return lResult == ERROR_SUCCESS;
   }

   // convert to string and write out
   LPTSTR lpsz = new char[nBytes*2+1];
   UINT i;
   for (i = 0; i < nBytes; i++)
   {
   lpsz[i*2] = (char)((pData[i] & 0x0F) + 'A'); //low nibble
   lpsz[i*2+1] = (char)(((pData[i] >> 4) & 0x0F) + 'A'); //high nibble
   }
   lpsz[i*2] = 0;

   ASSERT(m_pszProfileName != NULL);

   bool bResult = WriteProfileString(lpszSection, lpszEntry, lpsz);
   delete[] lpsz;
   return bResult;
   }

   #include "framework.h"*/




   /*   property_set & application::propset(object * pobject)
   {
   single_lock sl(&m_mapObjectSet, TRUE);
   return m_mapObjectSet[pobject];
   }

   property_set * application::existing_propset(object * pobject)
   {
   single_lock sl(&m_mapObjectSet, TRUE);
   auto p = m_mapObjectSet.PLookup(pobject);
   if(p == NULL)
   return NULL;
   return &p->m_value;
   }*/



   bool application::does_launch_window_on_startup()
   {
      return true;
   }

   bool application::activate_app()
   {
      if(m_puiMain != NULL)
      {
         m_puiMain->ShowWindow(SW_SHOWNORMAL);
      }
      return true;
   }



















   bool application::finalize()
   {

      bool bFinalize = true;

      try
      {
         ::base::application::finalize();
      }
      catch(...)
      {
         bFinalize = false;
      }

      return bFinalize;

   }




   sp(::user::interaction) application::get_request_parent_ui(sp(::user::interaction) pinteraction,sp(::create_context) pcreatecontext)
   {

      sp(::user::interaction) puiParent = NULL;

      if(puiParent == NULL)
      {
         puiParent = pcreatecontext->m_puiParent;
      }

      if(puiParent == NULL && pcreatecontext->m_spApplicationBias.is_set())
      {
         puiParent = pcreatecontext->m_spApplicationBias->m_puiParent;
      }

      if(puiParent == NULL && m_pbasesession != NULL && m_pbasesession->m_pcoreplatform != NULL && !pcreatecontext->m_bClientOnly
         && !pcreatecontext->m_bOuterPopupAlertLike && m_pbasesession->m_pcoreplatform != this)
      {
         puiParent = plat(this).get_request_parent_ui(pinteraction,pcreatecontext);
      }

      return puiParent;

   }







   void application::_001OnFileNew(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      var varFile;
      var varQuery;

      varQuery["command"] = "new_file";

      request_file_query(varFile,varQuery);

      //m_pimpl->_001OnFileNew();
   }


   sp(::user::document) application::_001OpenDocumentFile(var varFile)
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }

      return m_pimpl->_001OpenDocumentFile(varFile);

   }


   void application::_001EnableShellOpen()
   {

      m_pimpl->_001EnableShellOpen();

   }


   bool application::_001OnDDECommand(const char * lpcsz)
   {
      throw not_implemented(get_app());
      //return m_pimpl->_001OnDDECommand(lpcsz);
   }

   //   ::core::file_system & application::file_system()
   // {
   //  return m_spfilesystem;
   //}





   string application::get_version()
   {
      return m_pimpl->get_version();
   }


   bool application::Ex2OnAppInstall()
   {
      return true;
   }

   bool application::Ex2OnAppUninstall()
   {
      return true;
   }





   ::window_sp application::get_desktop_window()
   {
#if defined(METROWIN) || defined(APPLEOS)
      throw todo(this);
      /*#elif defined(LINUX)

      synch_lock sl(&user_mutex());

      xdisplay pdisplay.
      pdisplay.open(NULL) = XOpenDisplay(NULL);

      oswindow window(pdisplay, DefaultRootWindow(pdisplay));

      XCloseDisplay(pdisplay);

      return window_from_os_data(window);
      */
#else
      return window_from_os_data(::GetDesktopWindow());
#endif
   }



   void application::set_env_var(const string & var,const string & value)
   {
      m_pimpl->set_env_var(var,value);
   }



   void application::assert_valid() const
   {
      thread::assert_valid();


      if(::get_thread() != (thread*)this)
         return;     // only do subset if called from different thread

      ASSERT(::get_thread() == this);
      //ASSERT(afxCurrentInstanceHandle == m_hInstance);

      /*      if (m_pdocmanager != NULL)
      ASSERT_VALID(m_pdocmanager);*/
   }

   void application::dump(dump_context & dumpcontext) const
   {

      ::base::application::dump(dumpcontext);

      //dumpcontext << "\nm_lpCmdLine = " << m_strCmdLine;
      //dumpcontext << "\nm_nCmdShow = " << m_nCmdShow;
      //dumpcontext << "\nm_pszAppName = " << m_strAppName;
      dumpcontext << "\nm_bHelpMode = " << m_bHelpMode;
      dumpcontext << "\nm_pszHelpFilePath = " << m_pszHelpFilePath;
      dumpcontext << "\nm_pszProfileName = " << m_pszProfileName;

#ifdef WINDOWS
      dumpcontext << "\nm_hDevMode = " << (void *)m_hDevMode;
      dumpcontext << "\nm_hDevNames = " << (void *)m_hDevNames;
#endif

      dumpcontext << "\nm_dwPromptContext = " << (UINT)m_dwPromptContext;
      //      dumpcontext << "\nm_eHelpType = " << m_eHelpType;


      /*      if (m_pdocmanager != NULL)
      m_pdocmanager->dump(dumpcontext);*/

      dumpcontext << "\nm_nWaitCursorCount = " << m_iWaitCursorCount;
      dumpcontext << "\nm_nNumPreviewPages = " << m_nNumPreviewPages;

      dumpcontext << "\n";
   }








   void application::install_message_handling(::message::dispatch * pdispatch)
   {
      thread::install_message_handling(pdispatch);
      IGUI_WIN_MSG_LINK(WM_APP + 2043,pdispatch,this,&application::_001OnApplicationRequest);
   }




   bool application::base_support()
   {

      //if(!application::base_support())
      // return false;

      if(m_strBaseSupportId.is_empty())
      {

         property_set propertyset;

         message_box("err\\developer\\base_support\\support_id_not_specified.xml",propertyset);

         return false;

      }

      return true;
   }

   string application::message_box(const string & pszMatter,property_set & propertyset)
   {
      UNREFERENCED_PARAMETER(propertyset);
      UNREFERENCED_PARAMETER(pszMatter);
      return "";
   }

   bool application::bergedge_start()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }

      return true;
   }








#ifdef WINDOWSEX
   bool Is_Vista_or_Later()
   {
      OSVERSIONINFOEX osvi;
      DWORDLONG dwlConditionMask = 0;
      byte op = VER_GREATER_EQUAL;

      // Initialize the OSVERSIONINFOEX structure.

      ZeroMemory(&osvi,sizeof(OSVERSIONINFOEX));
      osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
      osvi.dwMajorVersion = 6;
      //   osvi.dwMinorVersion = 1;
      //   osvi.wServicePackMajor = 0;
      //   osvi.wServicePackMinor = 0;

      // Initialize the condition mask.

      VER_SET_CONDITION(dwlConditionMask,VER_MAJORVERSION,op);
      //VER_SET_CONDITION( dwlConditionMask, VER_MINORVERSION, op );
      //VER_SET_CONDITION( dwlConditionMask, VER_SERVICEPACKMAJOR, op );
      //VER_SET_CONDITION( dwlConditionMask, VER_SERVICEPACKMINOR, op );

      // Perform the test.

      return VerifyVersionInfo(
         &osvi,
         VER_MAJORVERSION | VER_MINORVERSION |
         VER_SERVICEPACKMAJOR | VER_SERVICEPACKMINOR,
         dwlConditionMask) != FALSE;
   }
#endif

   bool application::initialize()
   {

      if(!::base::application::initialize())
         return false;

      xxdebug_box("::base::application::initialize ok","::base::application::initialize ok",MB_ICONINFORMATION);

      m_pcalculator = new ::calculator::calculator(this);

      m_pcalculator->construct(this);

      if(!m_pcalculator->initialize())
         return false;
      xxdebug_box("m_pcalculator::initialize ok","m_pcalculator::initialize ok",MB_ICONINFORMATION);

      m_pcolorertake5 = new ::colorertake5::colorertake5(this);

      m_pcolorertake5->construct(this);

      if(!m_pcolorertake5->initialize())
         return false;


      xxdebug_box("m_pcolorertake5::initialize ok","m_pcolorertake5::initialize ok",MB_ICONINFORMATION);

      m_dwAlive = ::get_tick_count();


      //m_dwAlive = ::get_tick_count();

      //if(is_system())
      //{

      //   System.m_spcopydesk.alloc(allocer());

      //   if(!System.m_spcopydesk->initialize())
      //      return false;

      //}

      //if(is_system()
      //   && command_thread()->m_varTopicQuery["app"] != "app-core/netnodelite"
      //   && command_thread()->m_varTopicQuery["app"] != "app-core/netnode_dynamic_web_server"
      //   && command_thread()->m_varTopicQuery["app"] != "app-gtech/alarm"
      //   && command_thread()->m_varTopicQuery["app"] != "app-gtech/sensible_service")
      //{
      //   System.http().defer_auto_initialize_proxy_configuration();
      //}



      //<<<<<<< .mine
      //      if(!System.m_spcopydesk->initialize())
      //         return false;
      //
      //   }
      //
      //   if(is_system()
      //      && command_thread()->m_varTopicQuery["app"] != "app-core/netnodelite"
      //      && command_thread()->m_varTopicQuery["app"] != "app-core/netnode_dynamic_web_server"
      //      && command_thread()->m_varTopicQuery["app"] != "app-gtech/sensible_netnode"
      //      && command_thread()->m_varTopicQuery["app"] != "app-gtech/sensible_service")
      //   {
      //      System.http().defer_auto_initialize_proxy_configuration();
      //   }
      //
      //
      //
      //=======
      //>>>>>>> .r7309
      m_dwAlive = ::get_tick_count();

      if(is_system())
      {
         System.factory().creatable_small < ::userex::keyboard_layout >();
      }

      //      if(!::cubebase::application::initialize())
      //       return false;


      //      m_puserbase = new ::user::user();

      //    m_puserbase->construct(this);

      //  if(!m_puserbase->initialize())
      //return false;


      xxdebug_box("m_pfilemanager::initialize ok","m_pfilemanager::initialize ok",MB_ICONINFORMATION);

      m_pusermail = canew(::usermail::usermail(this));

      m_pusermail->construct(this);

      if(!m_pusermail->initialize())
         return false;

      xxdebug_box("m_pusermail::initialize ok","m_pusermail::initialize ok",MB_ICONINFORMATION);

      m_dwAlive = ::get_tick_count();





      m_dwAlive = ::get_tick_count();

      //m_splicense(new class ::fontopus::license(this));


      if(!is_system())
      {
         Platform.register_bergedge_application(this);
      }

      xxdebug_box("register_bergedge_application ok","register_bergedge_application ok",MB_ICONINFORMATION);

      m_dwAlive = ::get_tick_count();

      ensure_app_interest();


      xxdebug_box("ensure_app_interest ok","ensure_app_interest ok",MB_ICONINFORMATION);
      return true;

   }

   void application::pre_translate_message(signal_details * pobj)
   {
      SCAST_PTR(::message::base,pbase,pobj);
      if(pbase->m_uiMessage == WM_USER + 124 && pbase->m_pwnd == NULL)
      {
         /*      OnMachineEvent((flags < machine_event::e_flag> *) pmsg->lParam);
         delete (flags < machine_event::e_flag> *) pmsg->lParam;*/
         pbase->m_bRet = true;
         return;
      }
      return thread::pre_translate_message(pobj);
   }

   void application::_001OnApplicationRequest(signal_details * pobj)
   {
      SCAST_PTR(::message::base,pbase,pobj);
      if(pbase->m_wparam == 2)
      {
         pobj->m_bRet = true;
         // when wparam == 2 lparam is a pointer to a ::core::command_fork
         // that should be treated as command_line on request, i.e.,
         // a fork whose Forking part has been done, now
         // the parameters are going to be passed to this new application
         sp(::create_context) pcreatecontext(pbase->m_lparam);
         try
         {
            on_request(pcreatecontext);
         }
         catch(not_installed & e)
         {

            System.on_run_exception(e);

            throw exit_exception(e.get_app());

         }
         catch(exit_exception & e)
         {
            throw e;
         }
         catch(...)
         {
         }
         sp(::core::platform) pbergedge = pcreatecontext->m_spCommandLine->m_varQuery["bergedge_callback"].cast < ::core::platform >();
         // todobergedge
         /*if(pbergedge != NULL)
         {
         pbergedge->on_app_request_bergedge_callback(this);
         }*/
         pcreatecontext->m_spCommandLine->m_eventReady.SetEvent();

      }
   }


   void application::_001CloseApplication()
   {
      set_run(false);
      post_thread_message(WM_QUIT);
   }





   void application::EnableShellOpen()
   {
      ASSERT(m_atomApp == 0 && m_atomSystemTopic == 0); // do once
      if(m_atomApp != 0 || m_atomSystemTopic != 0)
      {
         return;
      }

      // Win95 & Win98 sends a WM_DDE_INITIATE with an atom that points to the
      // int16_t file name so we need to use the int16_t file name.
      string strShortName;
      strShortName = System.get_module_file_path();

      // strip out path
      //string strFileName = ::PathFindFileName(strShortName);
      // strip out extension
      //LPTSTR pszFileName = strFileName.GetBuffer();
      //::PathRemoveExtension(pszFileName);
      //strFileName.ReleaseBuffer();

      //      m_atomApp = ::GlobalAddAtom(strFileName);
      //    m_atomSystemTopic = ::GlobalAddAtom("system");
   }



   sp(::user::interaction) application::uie_from_point(point pt)
   {

      user::interaction_ptr_array wnda = frames();

      user::oswindow_array oswindowa;

      oswindowa = wnda.get_hwnda();

      user::window_util::SortByZOrder(oswindowa);

      for(int32_t i = 0; i < oswindowa.get_count(); i++)
      {

         sp(::user::interaction) puieWindow = wnda.find_first(oswindowa[i]);

         sp(::user::interaction) puie = puieWindow->_001FromPoint(pt);

         if(puie != NULL)
            return puie;

      }

      return NULL;

   }


   bool application::on_install()
   {

      if(!::base::application::on_install())
         return false;

      string strId = m_strId;

      char chFirst = '\0';

      if(strId.get_length() > 0)
      {

         chFirst = strId[0];

      }

      return true;

   }


   bool application::on_run_install()
   {
      if(m_strId == "session" || m_strAppName == "session")
      {
         if(!directrix()->m_varTopicQuery.has_property("session_start"))
         {
            System.post_thread_message(WM_QUIT);
         }
      }
      else
      {
         System.post_thread_message(WM_QUIT);
      }


      return true;
   }

   bool application::on_uninstall()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }

      return true;
   }

   bool application::on_run_uninstall()
   {

      if(m_strId == "session")
      {
         if(!directrix()->m_varTopicQuery.has_property("session_start"))
         {
            System.post_thread_message(WM_QUIT);
         }
      }
      else
      {
         System.post_thread_message(WM_QUIT);
      }

      return true;
   }



   bool application::start_application(bool bSynch,application_bias * pbias)
   {
      /*      try
      {
      if(pbias != NULL)
      {
      papp->m_pcoreapp->m_puiInitialPlaceHolderContainer = pbias->m_puiParent;
      }
      }
      catch(...)
      {
      }*/
      try
      {
         if(pbias != NULL)
         {
            if(pbias->m_pcallback != NULL)
            {
               pbias->m_pcallback->connect_to(this);
            }
         }
      }
      catch(...)
      {
      }

      manual_reset_event * peventReady = NULL;

      if(bSynch)
      {
         peventReady = new manual_reset_event(get_app());
         m_peventReady = peventReady;
         peventReady->ResetEvent();
      }

      m_pthreadimpl.alloc(allocer());

      m_pthreadimpl->m_pthread = this;

      if(pbias != NULL)
      {

         m_biasCalling = *pbias;

      }

      if(bSynch)
      {

         if(!begin_synch(&m_iReturnCode))
            return false;

      }
      else
      {

         begin();

      }


      return true;

   }




   void application::on_application_signal(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //      SCAST_PTR(signal_details, psignal, pobj);
      /*if(psignal->m_esignal == signal_exit_instance)
      {
      if(m_copydesk.is_set()
      && m_copydesk->IsWindow())
      {
      m_copydesk->DestroyWindow();
      }
      }*/
   }

   void application::defer_add_document_template(sp(::user::impact_system) ptemplate)
   {

      Application.userex()->defer_add_document_template(ptemplate);

   }


   sp(::user::printer) application::get_printer(const char * pszDeviceName)
   {

      return m_pimpl->get_printer(pszDeviceName);

   }




   bool application::set_keyboard_layout(const char * pszPath,::action::context actioncontext)
   {

      return Session.user()->keyboard().load_layout(pszPath,actioncontext);

   }

   string application::message_box(const char * pszMatter,property_set & propertyset)
   {
      ::userex::message_box box(this);
      box.show(pszMatter,&propertyset);
      return box.m_strResponse;
   }


   int32_t application::track_popup_menu(const char * pszMatter,point pt,sp(::user::interaction) puie)
   {
      UNREFERENCED_PARAMETER(pszMatter);
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(puie);
      return 1;
   }



   bool application::get_fs_size(string & strSize,const char * pszPath,bool & bPending)
   {
      int64_t i64Size;
      if(!get_fs_size(i64Size,pszPath,bPending))
      {
         strSize.Empty();
         return false;
      }
      if(i64Size > 1024 * 1024 * 1024)
      {
         double d = (double)i64Size / (1024.0 * 1024.0 * 1024.0);
         strSize.Format("%0.2f GB",d);
      }
      else if(i64Size > 1024 * 1024)
      {
         double d = (double)i64Size / (1024.0 * 1024.0);
         strSize.Format("%0.1f MB",d);
      }
      else if(i64Size > 1024)
      {
         double d = (double)i64Size / (1024.0);
         strSize.Format("%0.0f KB",d);
      }
      else if(i64Size > 0)
      {
         strSize.Format("1 KB");
      }
      else
      {
         strSize.Format("0 KB");
      }
      if(bPending)
      {
         strSize = "~" + strSize;
      }
      return true;
   }

   bool application::get_fs_size(int64_t & i64Size,const char * pszPath,bool & bPending)
   {
      db_server * pcentral = dynamic_cast <db_server *> (&System.m_simpledb.db());
      if(pcentral == NULL)
         return false;
      return pcentral->m_pfilesystemsizeset->get_cache_fs_size(i64Size,pszPath,bPending);
   }


   void application::set_title(const char * pszTitle)
   {

      Platform.set_app_title(m_strInstallType,m_strAppName,pszTitle);

   }


   bool application::_001CloseApplicationByUser(sp(::user::interaction) pwndExcept)
   {

      // attempt to save all documents
      if(!save_all_modified())
         return false;     // don't close it

      // hide the application's windows before closing all the documents
      HideApplication();

      // close all documents first
      close_all_documents(FALSE);


      Application.userex()->_001CloseAllDocuments(FALSE);


      // there are cases where destroying the documents may destroy the
      //  main window of the application.
      //bool b::core::ContextIsDll = afxContextIsDLL;
      //if (!b::core::ContextIsDll && papp->m_pcoreapp->GetVisibleFrameCount() <= 0)
      if(Application.userex()->GetVisibleTopLevelFrameCountExcept(pwndExcept) <= 0)
      {

         post_thread_message(WM_QUIT);

      }

      return true;

   }

   oswindow application::get_ca2_app_wnd(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
      return NULL;
   }


   int32_t application::send_simple_command(const char * psz,void * osdataSender)
   {
      string strApp;
      stringa stra;
      stra.add_tokens(psz,"::",true);
      if(stra.get_size() > 0)
      {
         strApp = stra[0];
         oswindow oswindow = get_ca2_app_wnd(strApp);
         if(oswindow != NULL)
         {
            return send_simple_command((void *)oswindow,psz,osdataSender);
         }
      }
      return -1;
   }

   int32_t application::send_simple_command(void * osdata,const char * psz,void * osdataSender)
   {
#ifdef WINDOWSEX
      ::oswindow oswindow = (::oswindow) osdata;
      if(!::IsWindow(oswindow))
         return -1;
      COPYDATASTRUCT cds;
      memset(&cds,0,sizeof(cds));
      cds.dwData = 888888;
      cds.cbData = (uint32_t)strlen(psz);
      cds.lpData = (PVOID)psz;
      return (int32_t)SendMessage(oswindow,WM_COPYDATA,(WPARAM)osdataSender,(LPARAM)&cds);
#else
      throw todo(get_app());
#endif
   }


   void application::ensure_app_interest()
   {

#ifndef METROWIN

      for(int32_t i = 0; i < m_straAppInterest.get_count(); i++)
      {
         if(m_straAppInterest[i] != m_strAppName && !::IsWindow(m_mapAppInterest[m_straAppInterest[i]]))
         {
            System.assert_running_local(m_straAppInterest[i]);
         }
      }

#else

      //throw todo(get_app());

#endif

   }




   sp(::axis::application) application::get_system()
   {
      return new application();
   }


















   /*
   sp(::core::application) application::assert_running(const char * pszAppId)
   {


   sp(::core::application) papp = NULL;


   try
   {

   bool bFound = false;

   for(int32_t i  = 0; i < System.m_appptra.get_count(); i++)
   {
   try
   {

   papp = System.m_appptra(i);

   if(papp->m_pcoreapp->m_strAppName == pszAppId)
   {
   bFound = true;
   break;
   }

   }
   catch(...)
   {
   }

   }

   bool bCreate = !bFound;

   if(bFound)
   {

   bool bRunning = false;

   try
   {
   if(papp->m_pcoreapp->is_running())
   {
   bRunning = true;
   }
   }
   catch(...)
   {
   }

   if(!bRunning)
   {

   try
   {
   papp->m_pcoreapp->post_thread_message(WM_QUIT);
   }
   catch(...)
   {
   }
   try
   {
   papp.release();
   }
   catch(...)
   {
   }

   bCreate = true;

   }


   }

   if(bCreate)
   {

   sp(::create_context) spcreatecontext(allocer());

   papp = Session.start_application("application", pszAppId, spcreatecontext);

   }

   }
   catch(const ::exit_exception & e)
   {

   throw e;

   }
   catch(const ::exception::exception & e)
   {

   if(!Application.on_run_exception((::exception::exception &) e))
   throw exit_exception(get_app());

   }
   catch(...)
   {

   papp = NULL;

   }


   return papp;

   }
   */





   //typedef  void (* PFN_ca2_factory_exchange)(sp(::axis::application) papp);




   ::file::binary_buffer_sp application::friendly_get_file(var varFile,UINT nOpenFlags)
   {

      try
      {

         return Session.m_file.get_file(varFile,nOpenFlags);

      }
      catch(::file::exception & e)
      {

         string strMessage = e.get_message();

         App(this).simple_message_box(NULL,strMessage,MB_OK);

         return NULL;

      }

   }




   ::userex::userex * application::create_userex()
   {

      return canew(::userex::userex(this));

   }


   ::userfs::userfs * application::create_userfs()
   {

      return canew(::userfs::userfs(this));

   }


   ::html::html * application::create_html()
   {

      return canew(::html::html(this));

   }










   sp(::axis::application) application::instantiate_application(const char * pszType,const char * pszId,application_bias * pbias)
   {

      sp(::axis::application) papp = NULL;

      string strId(pszId);

      if(strId.CompareNoCase("session") == 0)
      {

         ::core::platform * psession = new ::core::platform(m_paxisapp->m_pbasesession);

         papp = psession;

         psession->construct("session");

         psession->m_strAppId = "session";

      }
      else
      {

         string strNewId;

         if(strId == "bergedge")
         {

            strNewId = "app/core/bergedge";

         }
         else if(strId == "cube")
         {

            strNewId = "app/core/cube";

         }
         else
         {

            strNewId = strId;

         }

         papp = Platform.get_new_app(this,pszType,strNewId);

         if(papp == NULL)
            return NULL;

         papp->m_pcoreapp->m_pbasesession = m_pbasesession;

         if(papp != NULL)
         {

            if(strId == "bergedge" || strId == "cube")
            {

               papp->m_pcoreapp->m_strAppId = strId;

            }

            if(papp->m_pcoreapp->m_strInstallToken.is_empty())
            {

               papp->m_pcoreapp->m_strInstallToken = papp->m_pcoreapp->m_strAppId;

            }

         }

      }

      papp->m_pcoreapp->m_pcoresystem = m_pcoresystem;

      papp->m_pbasesystem = m_pbasesystem;

      papp->m_pcoreapp->command_central()->consolidate(command_central());

      //   papp->m_pcoreapp->m_bSystemSynchronizedCursor = m_bSystemSynchronizedCursor;

      if(pbias != NULL)
      {

         papp->m_pcoreapp->propset().merge(pbias->m_set);

      }
      else
      {

         papp->m_pcoreapp->oprop("SessionSynchronizedInput") = true;
         papp->m_pcoreapp->oprop("NativeWindowFocus") = true;

      }

      if((papp == NULL || papp->m_pcoreapp->m_strAppId != strId)
         &&
         (!Application.command()->m_varTopicQuery.has_property("install")
         && !Application.command()->m_varTopicQuery.has_property("uninstall")))
      {

         TRACE("Failed to instantiate %s, going to try installation through ca2_cube_install",strId);

         string strCommandLine;

         strCommandLine = " : app=" + strId;
         strCommandLine += " locale=" + string(Session.str_context()->m_plocaleschema->m_idLocale);
         strCommandLine += " style=" + string(Session.str_context()->m_plocaleschema->m_idSchema);
         strCommandLine += " install";

         System.install().start(strCommandLine,Application.command()->m_varTopicQuery["build_number"]);

         throw installing_exception(get_app());

         return NULL;

      }

      return papp;

   }


   sp(::axis::application) application::create_application(const char * pszType,const char * pszId,bool bSynch,application_bias * pbias)
   {

      sp(::axis::application) pbaseapp = instantiate_application(pszType,pszId,pbias);

      if(pbaseapp == NULL)
         return NULL;

      sp(::axis::application) papp = (pbaseapp);

      if(!papp->m_pcoreapp->start_application(bSynch,pbias))
      {
         try
         {
            pbaseapp.release();
         }
         catch(...)
         {
         }
         return NULL;
      }


      return pbaseapp;

   }


   sp(::user::document) application::place_hold(sp(::user::interaction) pui)
   {

      return NULL;

   }



   bool application::add_library(::axis::library * plibrary)
   {

      plibrary->set_app(this);

      System.add_library(plibrary);

      return true;

   }


   void application::data_on_after_change(signal_details * pobj)
   {
      SCAST_PTR(::database::change_event,pchange,pobj);
      if(pchange->m_key.m_idKey == "ca2")
      {
         if(pchange->m_key.m_idIndex == "savings")
         {
            pchange->data_get(Session.savings().m_eresourceflagsShouldSave);
         }
      }
   }


   int32_t application::simple_message_box(sp(::user::interaction) puiOwner,const char * pszMessage,UINT fuStyle)
   {

      if(!Session.user().is_set())
         return ::base::application::simple_message_box(puiOwner,pszMessage,fuStyle);

      return userex()->simple_message_box(puiOwner,pszMessage,fuStyle);

   }


   int32_t application::simple_message_box_timeout(sp(::user::interaction) pwndOwner,const char * pszMessage,::duration durationTimeOut,UINT fuStyle)
   {

      if(!Session.user().is_set())
         return ::base::application::simple_message_box_timeout(pwndOwner,pszMessage,durationTimeOut,fuStyle);

      return userex()->simple_message_box_timeout(pwndOwner,pszMessage,durationTimeOut,fuStyle);

   }


} // namespace core














