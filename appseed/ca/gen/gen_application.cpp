#include "framework.h"


#ifdef LINUX
#define __USE_GNU
#include <dlfcn.h>
#include <link.h>
#undef __USE_GNU
#include <ctype.h>
#endif


namespace gen
{

   UINT application::APPM_LANGUAGE = WM_APP + 117;
   WPARAM application::WPARAM_LANGUAGE_UPDATE = 1;


   application::application()
   {
         m_plemonarray              = new lemon::array(this);
         m_base64.set_app(this);
         m_pmath                    = new math::math(this);
         m_pgeometry                = new geometry::geometry(this);
         //m_pidspace = new id_space("veribell-{E856818A-2447-4a4e-B9CC-4400C803EE7A}", NULL);
         m_iResourceId              = 8001;
         m_psavings                 = new class savings(this);
         m_pcommandthread           = new ::gen::command_thread(this);
   }

   application::~application()
   {
   }

   math::math & application::math()
   {
      return *m_pmath;
   }

   geometry::geometry & application::geometry()
   {
      return *m_pgeometry;
   }

   savings & application::savings()
   {
      return *m_psavings;
   }
   lemon::array & application::lemon_array()
   {
      return *m_plemonarray;
   }

   class base64 & application::base64()
   {
      return m_base64;
   }

   bool application::process_initialize()
   {

      if(is_system())
      {

#ifdef WINDOWS

         {
            char lpszModuleFilePath[MAX_PATH + 1];
            GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);
            m_strModulePath = lpszModuleFilePath;
            char lpszModuleFolder[MAX_PATH + 1];
            LPTSTR lpszModuleFileName;
            GetFullPathName(lpszModuleFilePath, MAX_PATH + 1, lpszModuleFolder, &lpszModuleFileName);
            string strModuleFolder(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);
            m_strModuleFolder = strModuleFolder;
         }

         {
            char lpszModuleFilePath[MAX_PATH + 1];
            GetModuleFileName(::GetModuleHandleA("ca.dll"), lpszModuleFilePath, MAX_PATH + 1);
            m_strCa2ModulePath = lpszModuleFilePath;
            char lpszModuleFolder[MAX_PATH + 1];
            LPTSTR lpszModuleFileName;
            GetFullPathName(lpszModuleFilePath, MAX_PATH + 1, lpszModuleFolder, &lpszModuleFileName);
            string strModuleFolder(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);
            m_strCa2ModuleFolder = strModuleFolder;
         }

#else
         {

            char * lpszModuleFolder = br_find_exe_dir(NULL);

            if(lpszModuleFolder == NULL)
               return false;

            m_strModuleFolder = lpszModuleFolder;

            free(lpszModuleFolder);

         }

         {

            void * handle = dlopen("ca.so", 0);

            if(handle == NULL)
               return false;

            link_map * plm;

            dlinfo(handle, RTLD_DI_LINKMAP, &plm);

            m_strCa2ModuleFolder = System.dir().name(plm->l_name);

            dlclose(handle);


         }

#endif


      }
      else
      {
         m_strModulePath   = System.m_strModulePath;
         m_strModuleFolder = System.m_strModuleFolder;
      }

      if(!::ex1::application::process_initialize())
         return false;

      if(is_system())
      {
         System.factory().cloneable_large < stringa > ();
         System.factory().cloneable_large < ::primitive::memory > ();
      }
      return true;
   }

   bool application::initialize_instance()
   {

      if(!ex1::application::initialize_instance())
        return FALSE;


      return TRUE;
   }


   int application::exit_instance()
   {

      try
      {
         if(m_plemonarray != NULL)
         {
            delete m_plemonarray;
         }
      }
      catch(...)
      {
      }
      m_plemonarray = NULL;



      try
      {
         if(m_pmath != NULL)
         {
            delete m_pmath;
         }
      }
      catch(...)
      {
      }
      m_pmath = NULL;



      try
      {
         if(m_pgeometry != NULL)
         {
            delete m_pgeometry;
         }
      }
      catch(...)
      {
      }
      m_pgeometry = NULL;



      try
      {
         if(m_psavings != NULL)
         {
            delete m_psavings;
         }
      }
      catch(...)
      {
      }
      m_psavings = NULL;



      try
      {
         if(m_pcommandthread != NULL)
         {
            delete m_pcommandthread;
         }
      }
      catch(...)
      {
      }
      m_pcommandthread = NULL;


      return ex1::application::exit_instance();
   }

   LRESULT application::GetPaintMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(nCode);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      return 0;
   }





   bool application::CreateFileFromRawResource(UINT nID, const char * lpcszType, const char * lpcszFilePath)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpcszType);
      UNREFERENCED_PARAMETER(lpcszFilePath);
/*      HINSTANCE hinst = ::gen::FindResourceHandle(MAKEINTRESOURCE(nID), lpcszType);
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
       DWORD dwResSize = ::SizeofResource(hinst, hrsrc);

      if(hres != NULL)
       {
         UINT FAR* lpnRes = (UINT FAR*)::LockResource(hres);
           try
           {
              // create the .mdb file
              ex1::filesp f(get_app());

              if(f->open(lpcszFilePath, ::ex1::file::mode_create | ::ex1::file::mode_write ))
              {
                 // write the ::fontopus::user-defined resource to the .mdb file
                 f->write(lpnRes, dwResSize);
                 f->Flush();
              }
              else
              {
               #ifdef DEBUG
                  g_dumpcontext << "File could not be opened \n";
               #endif
              }
           }
           catch(ex1::file_exception_sp * pe)
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

   bool application::OnMessageWindowMessage(LPMSG lpmsg)
   {
      UNREFERENCED_PARAMETER(lpmsg);
      return false;
   }

#endif

   void application::OnAppLanguage(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      m_signalAppLanguageChange.emit();
   }

   string application::get_ca2_module_folder()
   {
      single_lock sl(&m_mutex, true);
      return m_strCa2ModuleFolder;
   }

   string application::get_ca2_module_file_path()
   {

#ifdef WINDOWS

      char lpszModuleFilePath[MAX_PATH + 1];

      GetModuleFileName(::GetModuleHandleA("ca.dll"), lpszModuleFilePath, MAX_PATH + 1);

      string strModuleFileName(lpszModuleFilePath);

      return strModuleFileName;

#else

      void * handle = dlopen("ca.so", 0);

      if(handle == NULL)
         return "";

      link_map * plm;

      dlinfo(handle, RTLD_DI_LINKMAP, &plm);

      string strModuleFileName(plm->l_name);

      dlclose(handle);

      return strModuleFileName;

#endif

   }

   string application::get_module_folder()
   {
      return m_strModuleFolder;
   }

   string application::get_module_file_path()
   {

#ifdef WINDOWS

      char lpszModuleFilePath[MAX_PATH + 1];

      GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);

      string strModuleFileName(lpszModuleFilePath);

      return strModuleFileName;

#else

      char * lpszModuleFilePath = br_find_exe_dir("app");

      if(lpszModuleFilePath == NULL)
         return "";

      string strModuleFileName(lpszModuleFilePath);

      free(lpszModuleFilePath);

      return strModuleFileName;

#endif

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
         for (int iMRU = 1; iMRU < 10; iMRU++)
            pcmdui->m_pMenu->DeleteMenu(pcmdui->m_nID + iMRU, MF_BYCOMMAND);
         return;
      }

      ASSERT(m_pRecentFileList->m_arrNames != NULL);

      ::userbase::menu* pMenu = pcmdui->m_pMenu;
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

      ::userbase::menu * pmenu = CMenuUtil::FindPopupMenuFromID(pcmdui->m_pMenu, pcmdui->m_nID);

      //if(pmenu == NULL)
      //{
        // pmenu = pcmdui->m_pMenu;
      //}

      bool bCmdUIMenu = pmenu == pcmdui->m_pMenu;

      if(!bCmdUIMenu)
         return;

      int nID = pcmdui->m_nID;
      int nIndex = CMenuUtil::GetMenuPosition(pmenu, nID);

      for (int iMRU = 0; iMRU < m_pRecentFileList->m_nSize; iMRU++)
         pcmdui->m_pMenu->DeleteMenu(pcmdui->m_nID + iMRU, MF_BYCOMMAND);



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

      pcmdui->m_bEnableChanged = TRUE;    // all the added items are enabled*/

   }

   bool application::GetResourceData(UINT nID, const char * lpcszType, primitive::memory &storage)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpcszType);
      UNREFERENCED_PARAMETER(storage);
/*      HINSTANCE hinst = ::gen::FindResourceHandle(MAKEINTRESOURCE(nID), lpcszType);

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

      DWORD dwResSize = ::SizeofResource(hinst, hrsrc);

      if(hres != NULL)
      {
         UINT FAR* lpnRes = (UINT FAR*)::LockResource(hres);
         try
         {
            storage.set_data(lpnRes, dwResSize);
         }
         catch(ex1::file_exception_sp * pe)
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

#ifdef WINDOWS

   HENHMETAFILE application::LoadEnhMetaFile(UINT uiResource)
   {
      primitive::memory storage;
      if(!GetResourceData(uiResource, "EnhMetaFile", storage))
      {
         return NULL;
      }
      return SetEnhMetaFileBits((UINT) storage.get_size(), storage.get_data());
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

      // no-op if main ::ca::window is NULL or not a frame_window_interface
/*      ::user::interaction* pMainWnd = System.GetMainWnd();
      if (pMainWnd == NULL || !pMainWnd->IsFrameWnd())
         return;*/

   #ifndef ___NO_OLE_SUPPORT
      // check if notify hook installed
   /*   gen::frame_window_interface* pFrameWnd =
         dynamic_cast < gen::frame_window_interface * > (pMainWnd);
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
   string application::load_string(const id_space * pspace, int iKey)
   {
      string str;
      int iId = GetResourceId(pspace, iKey);
      if(iId == -1)
         return str;
      str.load_string(iId);
      return str;
   }
   */



   void application::assert_valid() const
   {
      ex1::application::assert_valid();
   }

   void application::dump(dump_context & dumpcontext) const
   {
      ex1::application::dump(dumpcontext);
   }


   int application::run()
   {
      return ex1::application::run();
   }

   bool application::on_idle(LONG lCount)
   {
      return ex1::application::on_idle(lCount);
   }

   void application::ProcessWndProcException(base_exception* e, gen::signal_object * pobj)
   {
      return ex1::application::ProcessWndProcException(e, pobj);
   }

   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)

   {
      if(command_target_interface::_001OnCmdMsg(pcmdmsg))
         return TRUE;
      return ex1::application::_001OnCmdMsg(pcmdmsg);
   }

   ::ca::application * application::get_app() const
   {
      return ex1::application::get_app();
   }

   string application::get_module_title()
   {
      return file_title(get_module_file_path());
   }

   string application::get_module_name()
   {
      return file_name(get_module_file_path());
   }

   string application::get_local_mutex_id()
   {
      return command().m_varTopicQuery["local_mutex_id"];
   }

   string application::get_global_mutex_id()
   {
      return command().m_varTopicQuery["global_mutex_id"];
   }

   bool application::hex_to_memory(primitive::memory & memory, const char * pszHex)
   {
      count len = strlen(pszHex);
      count count = (len + 1) / 2;
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

   int nibble_to_low_hex(byte nibble)
   {
      if(nibble >= 0 && nibble <= 9)
      {
         return nibble + '0';
      }
      else if(nibble >= 10 && nibble <= 15)
      {
         return nibble + 'a' - 10;
      }
      else
      {
         return -1;
      }
   }

   void application::memory_to_hex(string & strHex, primitive::memory & memory)
   {
      count count = memory.get_size();
      LPSTR lpsz = strHex.GetBufferSetLength(count * 2);
      for(index i = 0; i < count; i++)
      {
         *lpsz++ = (char) nibble_to_low_hex((memory.get_data()[i] >> 4) & 0xf);
         *lpsz++ = (char) nibble_to_low_hex(memory.get_data()[i] & 0xf);
      }
      strHex.ReleaseBuffer(count * 2);
   }

   ::gen::command_thread & application::command_central()
   {
      return *m_pcommandthread;
   }

   ::gen::command_thread & application::command()
   {
      return *m_pcommandthread;
   }

   ::gen::command_thread & application::guideline()
   {
      return *m_pcommandthread;
   }

   ::gen::command_thread & application::directrix()
   {
      return *m_pcommandthread;
   }

   ::gen::command_thread & application::axiom()
   {
      return *m_pcommandthread;
   }

   bool application::verb()
   {
      axiom().run();
      return true;
   }

   ::gen::command_thread & application::creation()
   {
      return *m_pcommandthread;
   }

} // namespace gen

