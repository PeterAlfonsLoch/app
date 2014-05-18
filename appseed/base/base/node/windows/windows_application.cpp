#include "framework.h"


namespace windows
{


   application::application(sp(::base::application) papp) :
      element(papp)
   {

      ::thread::m_pimpl.create(allocer());

      ::thread::m_pimpl->m_puser = this;

      m_pbasesystem                    =  papp->m_pbaseapp->m_pbasesystem;

      m_atomApp = m_atomSystemTopic    = NULL;

      shell::theWindowsShell.Initialize();

   }


   application::~application()
   {

   }


   void application::_001OnFileNew()
   {

   }


   sp(::user::object) application::_001OpenDocumentFile(var varFile)
   {

      return NULL;

   }


   void application::_001EnableShellOpen()
   {

      ASSERT(m_atomApp == NULL && m_atomSystemTopic == NULL); // do once

      m_atomApp            = ::GlobalAddAtomW(::str::international::utf8_to_unicode(m_strAppName));

      m_atomSystemTopic    = ::GlobalAddAtomW(L"system");

   }


   bool application::_001OnDDECommand(const char * lpcsz)
   {

      UNREFERENCED_PARAMETER(lpcsz);

      return FALSE;

   }


   HINSTANCE application::GetHinstance()
   {

      return NULL;

   }

   string application::get_version()
   {

      char lpszModuleFilePath[MAX_PATH + 1];
      GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);

      DWORD dw;

      DWORD dwResSize = GetFileVersionInfoSize(      
         lpszModuleFilePath,
         &dw);


      if(dwResSize > 0)
      {
         LPVOID lpdata = new BYTE[dwResSize];
         if(GetFileVersionInfo(      
            lpszModuleFilePath,
            0,
            dwResSize,
            lpdata))
         {
            UINT cbTranslate;
            struct LANGANDCODEPAGE {
               WORD wLanguage;
               WORD wCodePage;
            } *lpTranslate;

            // read the list of languages and code pages.

            VerQueryValue(lpdata, 
               TEXT("\\VarFileInfo\\Translation"),
               (LPVOID*)&lpTranslate,
               &cbTranslate);

            string strKey;
            //for( i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
            for(int32_t i=0; i < 1; i++ )
            {
               LPTSTR lpsz;
               UINT uiSize;

               strKey.Format(
                  TEXT("\\StringFileInfo\\%04x%04x\\FileDescription"),
                  lpTranslate[i].wLanguage,
                  lpTranslate[i].wCodePage);




               strKey.Format(
                  TEXT("\\StringFileInfo\\%04x%04x\\FileVersion"),
                  lpTranslate[i].wLanguage,
                  lpTranslate[i].wCodePage);

               // Retrieve file description for language and code page "i". 
               VerQueryValue(lpdata, 
                  (LPTSTR) (const char *) strKey, 
                  (LPVOID *)&lpsz, 
                  &uiSize); 


               string strVersion(lpsz, uiSize);

               return strVersion;
            }
         }
         delete [] (LPBYTE) lpdata;
      }


      return "";

   }


   bool application::Ex2OnAppInstall()
   {
#ifdef IMPLEMENT_VISTA_TOOLS
      if(VistaTools::IsVista())
      {
         if(VistaTools::IsElevated() != S_OK)
         {
            TRACE0("Error! Installing application ( : (un)install run parameter ) without Elevation (required since Vista Windows version)");
            return false;
         }
      }
#endif 
      return true;
   }


   bool application::Ex2OnAppUninstall()
   {
      if(VistaTools::IsVista())
      {
         if(VistaTools::IsElevated() != S_OK)
         {
            TRACE0("Error! Installing application ( : (un)install run parameter ) without Elevation (required since Vista Windows version)");
            return false;
         }
      }
      return true;
   }


   void application::TermThread(HINSTANCE hInstTerm)
   {

   }





   bool application::process_initialize()
   {

      return true;

   }

   bool application::initialize1()
   {

      set_run();

      return true;

   }

   bool application::initialize2()
   {
      return true;
   }

   bool application::initialize3()
   {
      return true;
   }

   // thread termination
   int32_t application::exit_instance() // default will 'delete this'
   {

      set_os_data(NULL);

      set_run(false);

      int32_t iRet = ::base::application::exit_instance();

      return iRet;

   }




   void application::SetCurrentHandles()
   {

      string strExeName;
      strExeName = System.get_module_title();

      __init_thread();

   }

   ::window_sp application::FindWindow(const char * lpszClassName, const char * lpszWindowName)
   {
      return window::FindWindow(lpszClassName, lpszWindowName);
   }

   ::window_sp application::FindWindowEx(oswindow oswindowParent, oswindow oswindowChildAfter, const char * lpszClass, const char * lpszWindow)
   {
      return window::FindWindowEx(oswindowParent, oswindowChildAfter, lpszClass, lpszWindow);
   }


   void application::get_time(struct timeval *p)
   {
   #ifdef _WIN32
      FILETIME ft; // Contains a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 (UTC).
      GetSystemTimeAsFileTime(&ft);
      uint64_t tt;
      memcpy(&tt, &ft, sizeof(tt));
      tt /= 10; // make it usecs
      p->tv_sec = (long)tt / 1000000;
      p->tv_usec = (long)tt % 1000000;
   #else
      gettimeofday(p, NULL);
   #endif
   }

   void application::set_env_var(const string & var,const string & value)
   {
   #if (defined(SOLARIS8) || defined(SOLARIS))
      {
         static stdmap<string, char *> vmap;
         if (vmap.find(var) != vmap.end())
         {
            delete[] vmap[var];
         }
         vmap[var] = new char[var.get_length() + 1 + value.get_length() + 1];
         sprintf(vmap[var], "%s=%s", var, value);
         putenv( vmap[var] );
      }
   #elif defined _WIN32
      {
         string slask = var + "=" + value;
         _putenv( (const char *)slask);
      }
   #else
      setenv(var, value, 1);
   #endif
   }

   uint32_t application::get_thread_id()
   {
      return ::GetCurrentThreadId();
   }



   bool application::set_main_init_data(::core::main_init_data * pdata)
   {

      m_pmaininitdata = (::windows::main_init_data *) pdata;

      if(m_pmaininitdata != NULL && m_pimpl->is_system())
      {
         if(!win_init(m_pmaininitdata))
            return false;
      }

      return true;

   }

   bool application::win_init(main_init_data * pdata)
   {
         ASSERT(pdata->m_hPrevInstance == NULL);

         HINSTANCE hInstance        = pdata->m_hInstance;
//         HINSTANCE hPrevInstance    = pdata->m_hPrevInstance;
         string strCmdLine          = pdata->m_vssCommandLine;
         UINT nCmdShow              = pdata->m_nCmdShow;

         // handle critical errors and avoid Windows message boxes
         SetErrorMode(SetErrorMode(0) | SEM_FAILCRITICALERRORS | SEM_NOOPENFILEERRORBOX);

         m_hinstance = hInstance;
         m_pbaseapp->m_hinstance = hInstance;
         m_pimpl->m_hinstance = hInstance;
         //hPrevInstance; // Obsolete.
         m_strCmdLine = strCmdLine;
         m_nCmdShow = nCmdShow;
         //pApp->SetCurrentHandles();
         m_pimpl->SetCurrentHandles();

         string strCgcl = read_resource_as_string_dup(NULL, 1984, "CGCL");

         if (strCgcl.has_char())
         {
            directrix()->m_varTopicQuery["cgcl_app"] = strCgcl;
            m_pimpl->directrix()->m_varTopicQuery["cgcl_app"] = strCgcl;
         }

         // Initialize window::m_pfnNotifyWinEvent
      /*   HMODULE hModule = ::GetModuleHandle("user32.dll");
         if (hModule != NULL)
         {
            window::m_pfnNotifyWinEvent = (window::PFNNOTIFYWINEVENT)::GetProcAddress(hModule, "NotifyWinEvent");
         }*/

      return true;

   }

   bool application::update_module_paths()
   {

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
         GetModuleFileName(::GetModuleHandleA("core.dll"), lpszModuleFilePath, MAX_PATH + 1);
         m_strCa2ModulePath = lpszModuleFilePath;

         char lpszModuleFolder[MAX_PATH + 1];
         LPTSTR lpszModuleFileName;
         GetFullPathName(lpszModuleFilePath, MAX_PATH + 1, lpszModuleFolder, &lpszModuleFileName);
         string strModuleFolder(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);
         m_strCa2ModuleFolder = strModuleFolder;

      }


      return true;

   }

   void application::ShowWaitCursor(bool bShow)
   {

      if(bShow)
      {

         HCURSOR hcursorWait =  ::LoadCursor(NULL, IDC_WAIT);

         HCURSOR hcursorPrevious = ::SetCursor(hcursorWait);
         
    //     if(hcursorPrevious != hcursorWait)
  //         m_hcurWaitCursorRestore = hcursorPrevious;

      }
      else
      {

//         ::SetCursor(m_hcurWaitCursorRestore);
      }

   }
   
   sp(::user::printer) application::get_printer(const char * pszDeviceName)
   {

      //::windows::printer * pprinter = new ::windows::printer(get_app());

      sp(::user::printer) pprinter(allocer());

      if(!pprinter->open(pszDeviceName))
      {

         delete pprinter;

         return NULL;

      }

      return pprinter;

   }

   string application::veriwell_multimedia_music_midi_get_default_library_name()
   {
      return "music_midi_mmsystem";
   }

   string application::multimedia_audio_mixer_get_default_library_name()
   {
      return "audio_mixer_mmsystem";
   }

   string application::multimedia_audio_get_default_library_name()
   {
      return "audio_mmsystem";
   }

   string application::draw2d_get_default_library_name()
   {

      string str;

      if (file_exists_dup("C:\\ca2\\config\\draw2d.txt"))
      {

         str = file_as_string_dup("C:\\ca2\\config\\draw2d.txt");

      }
      else
      {

         string strPath;

         strPath = ::dir::userappdata("draw2d.txt");

         str = file_as_string_dup(strPath);

      }

      if(str.has_char())
         return "draw2d_" + str;
      else
         return "draw2d_gdiplus";
   }


} // namespace windows






