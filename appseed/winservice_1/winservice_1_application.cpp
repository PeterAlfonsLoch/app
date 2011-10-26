#include "StdAfx.h"

#pragma comment(lib, "Wtsapi32.lib")

typedef struct _NOTIFYICONDATAA1 {
    DWORD cbSize;
    HWND hWnd;
    UINT uID;
    UINT uFlags;
    UINT uCallbackMessage;
    HICON hIcon;
} NOTIFYICONDATAA1, *PNOTIFYICONDATAA1;

typedef struct _NOTIFYICONDATAW1 {
    DWORD cbSize;
    HWND hWnd;
    UINT uID;
    UINT uFlags;
    UINT uCallbackMessage;
    HICON hIcon;
} NOTIFYICONDATAW1, *PNOTIFYICONDATAW1;

typedef struct _NOTIFYICONDATAA2 {
    DWORD cbSize;
    HWND hWnd;
    UINT uID;
    UINT uFlags;
    UINT uCallbackMessage;
    HICON hIcon;
    CHAR   szTip[64];
} NOTIFYICONDATAA2, *PNOTIFYICONDATAA2;

typedef struct _NOTIFYICONDATAW2 {
    DWORD cbSize;
    HWND hWnd;
    UINT uID;
    UINT uFlags;
    UINT uCallbackMessage;
    HICON hIcon;
    WCHAR  szTip[64];
} NOTIFYICONDATAW2, *PNOTIFYICONDATAW2;

typedef struct _NOTIFYICONDATAA3 {
    DWORD cbSize;
    HWND hWnd;
    UINT uID;
    UINT uFlags;
    UINT uCallbackMessage;
    HICON hIcon;
    CHAR   szTip[128];
    DWORD dwState;
    DWORD dwStateMask;
    CHAR   szInfo[256];
    union {
        UINT  uTimeout;
        UINT  uVersion;  // used with NIM_SETVERSION, values 0, 3 and 4
    } DUMMYUNIONNAME;
    CHAR   szInfoTitle[64];
    DWORD dwInfoFlags;
} NOTIFYICONDATAA3, *PNOTIFYICONDATAA3;

typedef struct _NOTIFYICONDATAW3 {
    DWORD cbSize;
    HWND hWnd;
    UINT uID;
    UINT uFlags;
    UINT uCallbackMessage;
    HICON hIcon;
    WCHAR  szTip[128];
    DWORD dwState;
    DWORD dwStateMask;
    WCHAR  szInfo[256];
    union {
        UINT  uTimeout;
        UINT  uVersion;  // used with NIM_SETVERSION, values 0, 3 and 4
    } DUMMYUNIONNAME;
    WCHAR  szInfoTitle[64];
    DWORD dwInfoFlags;
} NOTIFYICONDATAW3, *PNOTIFYICONDATAW3;

typedef struct _NOTIFYICONDATAA4 {
    DWORD cbSize;
    HWND hWnd;
    UINT uID;
    UINT uFlags;
    UINT uCallbackMessage;
    HICON hIcon;
    CHAR   szTip[128];
    DWORD dwState;
    DWORD dwStateMask;
    CHAR   szInfo[256];
    union {
        UINT  uTimeout;
        UINT  uVersion;  // used with NIM_SETVERSION, values 0, 3 and 4
    } DUMMYUNIONNAME;
    CHAR   szInfoTitle[64];
    DWORD dwInfoFlags;
    GUID guidItem;
} NOTIFYICONDATAA4, *PNOTIFYICONDATAA4;

typedef struct _NOTIFYICONDATAW4 {
    DWORD cbSize;
    HWND hWnd;
    UINT uID;
    UINT uFlags;
    UINT uCallbackMessage;
    HICON hIcon;
    WCHAR  szTip[128];
    DWORD dwState;
    DWORD dwStateMask;
    WCHAR  szInfo[256];
    union {
        UINT  uTimeout;
        UINT  uVersion;  // used with NIM_SETVERSION, values 0, 3 and 4
    } DUMMYUNIONNAME;
    WCHAR  szInfoTitle[64];
    DWORD dwInfoFlags;
    GUID guidItem;
} NOTIFYICONDATAW4, *PNOTIFYICONDATAW4;

typedef struct _NOTIFYICONDATAA5 {
    DWORD cbSize;
    HWND hWnd;
    UINT uID;
    UINT uFlags;
    UINT uCallbackMessage;
    HICON hIcon;
    CHAR   szTip[128];
    DWORD dwState;
    DWORD dwStateMask;
    CHAR   szInfo[256];
    union {
        UINT  uTimeout;
        UINT  uVersion;  // used with NIM_SETVERSION, values 0, 3 and 4
    } DUMMYUNIONNAME;
    CHAR   szInfoTitle[64];
    DWORD dwInfoFlags;
    GUID guidItem;
    HICON hBalloonIcon;
} NOTIFYICONDATAA5, *PNOTIFYICONDATAA5;

typedef struct _NOTIFYICONDATAW5 {
    DWORD cbSize;
    HWND hWnd;
    UINT uID;
    UINT uFlags;
    UINT uCallbackMessage;
    HICON hIcon;
    WCHAR  szTip[128];
    DWORD dwState;
    DWORD dwStateMask;
    WCHAR  szInfo[256];
    union {
        UINT  uTimeout;
        UINT  uVersion;  // used with NIM_SETVERSION, values 0, 3 and 4
    } DUMMYUNIONNAME;
    WCHAR  szInfoTitle[64];
    DWORD dwInfoFlags;
    GUID guidItem;
    HICON hBalloonIcon;
} NOTIFYICONDATAW5, *PNOTIFYICONDATAW5;









namespace winservice_1
{


   application::application()
   {
      m_pthread               = NULL;
      m_pupdatethread         = NULL;
      m_strAppName            = "winservice_1";
      m_strBaseSupportId      = "votagus_ca2_winservice_1";
      m_eexclusiveinstance    = ::radix::ExclusiveInstanceLocal;
      m_ptraywnd              = NULL;
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
      if(!cube2::application::initialize_instance())
         return FALSE;

      CoInitialize(NULL);

//      pointer_list *objects;

      m_ptraywnd = new shell_traywnd(this);
      if(!m_ptraywnd->create())
         return false;

	   OSVERSIONINFO osver;

	   osver.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );
   	
      if(!::GetVersionEx( &osver ))
         return false;
   			
      const char * pszShellReadyEvent;

      if(osver.dwMajorVersion >= 6)
      {
         pszShellReadyEvent = "ShellDesktopSwitchEvent";
      }
      else
      {
         pszShellReadyEvent = "msgina: ShellReadyEvent";
      }

      HANDLE hShellReadyEvent = OpenEvent(EVENT_MODIFY_STATE, FALSE, pszShellReadyEvent );

      if(hShellReadyEvent)
      {
         //if(!::WaitForSingleObject(hShellReadyEvent, 0))
         {
            SetEvent(hShellReadyEvent);
            AfxBeginThread < windows_run > (this);
         }
         CloseHandle(hShellReadyEvent);
      }

      m_pthread = AfxBeginThread < winservice_1::thread > (this);
      m_pupdatethread = AfxBeginThread < update_schedule_thread > (this);
      LoadShellTrayObjects(&m_plistShellObjects);
      return TRUE;
   }

   BOOL application::exit_instance()
   {
      FreeShellTrayObjects(m_plistShellObjects);
      CoUninitialize();
      if(m_ptraywnd != NULL)
      {
         m_ptraywnd->DestroyWindow();
         delete m_ptraywnd;
         m_ptraywnd = NULL;
      }
      return ::cube2::application::exit_instance();
   }


   void application::on_request(::ca::create_context * pcreatecontext)
   {

   }


   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
   		
   {
      return gen::application::_001OnCmdMsg(pcmdmsg);
   }



   CLASS_DECL_CA2_WINSERVICE_1 ::ca::application * get_new_app()
   {
      return new application;
   }

   void application::OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      if(itema.get_size() > 0)
      {
         ::ShellExecuteW(
            NULL, 
            L"open", 
            gen::international::utf8_to_unicode(itema[0].m_strPath),
            NULL,
            gen::international::utf8_to_unicode(System.dir().name(itema[0].m_strPath)),
            SW_SHOW);
      }
      
   }



   bool application::RunShellLink()
   {
      STARTUPINFO si;
      memset(&si, 0, sizeof(si));
      si.cb = sizeof(si);
      PROCESS_INFORMATION pi;
      memset(&pi, 0, sizeof(pi));
      DWORD dwError;
      string str;
   #ifdef _DEBUG
      str = "cast\\stage\\ca2\\fontopus\\cast\\main\\front\\Debug\\winshelllinkapp.exe";
   #else
      str = "cast\\stage\\ca2\\fontopus\\cast\\main\\front\\Release\\winshelllinkapp.exe";
   #endif
      if(::CreateProcess(System.dir().votagus(str), 
                         " : usehostlogin",
                         NULL, NULL, FALSE, 0, NULL, NULL,
                         &si, &pi))
      {
         return true;
      }
      else
      {
         dwError = ::GetLastError();
         MessageBox(NULL, "Could not start winshelllink", "spa ignition", MB_OK);
         return false;
      }

   }

   bool application::RunLoginStartup()
   {
      STARTUPINFO si;
      memset(&si, 0, sizeof(si));
      si.cb = sizeof(si);
      PROCESS_INFORMATION pi;
      memset(&pi, 0, sizeof(pi));
      DWORD dwError;
      string str;
   #ifdef _DEBUG
      str = "cast\\stage\\ca2\\fontopus\\cast\\main\\front\\Debug\\loginstartupapp.exe";
   #else
      str = "cast\\stage\\ca2\\fontopus\\cast\\main\\front\\Release\\loginstartupapp.exe";
   #endif
      if(::CreateProcess(System.dir().votagus(str), 
                         " : usehostlogin loginstartup",
                         NULL, NULL, FALSE, 0, NULL, NULL,
                         &si, &pi))
      {
         return true;
      }
      else
      {
         dwError = ::GetLastError();
         MessageBox(NULL, "Could not start winshelllink", "spa ignition", MB_OK);
         return false;
      }

   }

   bool application::InstallStartupLinks()
   {
      string strStartup;
      strStartup = System.dir().appdata("loginstartup\\run");
      string strWinservice1Link     = System.dir().path(strStartup, "winservice1.link");
      string strCommandLink         = System.dir().path(strStartup, "command.link");
      string strWinActionAreaLink   = System.dir().path(strStartup, "winactionarea.link");
      string strWinUtilLink         = System.dir().path(strStartup, "winutil.link");
   #ifdef _DEBUG
      string strWinservice1      = System.dir().votagus("cast\\stage\\ca2\\fontopus\\cast\\main\\front\\Debug\\winservice_1app.exe");
      string strCommand          = System.dir().votagus("cast\\stage\\ca2\\fontopus\\cast\\main\\front\\Debug\\commandapp.exe");
      string strWinActionArea    = System.dir().votagus("cast\\stage\\ca2\\fontopus\\cast\\main\\front\\Debug\\winactionareaapp.exe");
      string strWinUtil          = System.dir().votagus("cast\\stage\\ca2\\fontopus\\cast\\main\\front\\Debug\\winutilapp.exe");
   #else
      string strWinservice1      = System.dir().votagus("cast\\stage\\ca2\\fontopus\\cast\\main\\front\\Release\\winservice_1app.exe");
      string strCommand          = System.dir().votagus("cast\\stage\\ca2\\fontopus\\cast\\main\\front\\Release\\commandapp.exe");
      string strWinActionArea    = System.dir().votagus("cast\\stage\\ca2\\fontopus\\cast\\main\\front\\Release\\winactionareaapp.exe");
      string strWinUtil          = System.dir().votagus("cast\\stage\\ca2\\fontopus\\cast\\main\\front\\Release\\winutilapp.exe");
   #endif
      make_link(strWinservice1Link     , strWinservice1     , ": usehostlogin run", "");
      make_link(strCommandLink         , strCommand         , ": usehostlogin", "");
      make_link(strWinActionAreaLink   , strWinActionArea   , ": usehostlogin", "");
      make_link(strWinUtilLink         , strWinUtil         , ": usehostlogin", "");

   /*   string str;
      str.Format("<service name=\"CGCLCSTvotagusCa2Fontopus_WinService_1\" control=\"start\" />");
      string strLink;
      strLink = dir().path(strStartup, "winservice_1start.link");
      dir().mk(dir().name(strLink));
      file().put_contents(strLink, str);*/
      return true;
   }

   bool application::make_link(const char * pszLink, const char * pszLocation, const char * pszParameters, const char * pszDirectory)
   {
      string str;
      string strLocation(pszLocation);
      string strParameters(pszParameters);
      string strDirectory(pszDirectory);
      strLocation.replace("\\", "\\\\");
      strParameters.replace("\\", "\\\\");
      strDirectory.replace("\\", "\\\\");
      str.Format("<link location=\"%s\" parameters=\"%s\" directory=\"%s\" />", strLocation, strParameters, strDirectory);
      System.dir().mk(System.dir().name(pszLink));
      Application.file().put_contents(pszLink, str);
      return true;
   }


   void application::_001CloseApplication()
   {
      m_pthread->set_run(false);
      cube2::application::_001CloseApplication();
   }

   application::windows_run::windows_run(::ca::application * papp) :
      ca(papp),
      thread(papp)
   {
   }

   bool application::windows_run::initialize_instance()
   {
      return true;
   }

   int application::windows_run::run()
   {
      {
         win::registry::Key keyLink1(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", false);
         stringa straValueName;
         keyLink1.EnumValueName(straValueName);
         STARTUPINFO si;
         PROCESS_INFORMATION pi;
         for(int i = 0; i < straValueName.get_count(); i++)
         {
            string strValue;
            
            keyLink1.QueryValue(straValueName[i], strValue);
            memset(&si, 0, sizeof(si));
            memset(&pi, 0, sizeof(pi));
            
            if(::CreateProcess(NULL, (char *) (const char *) strValue, NULL, NULL,
               FALSE, 0, NULL, NULL, &si, &pi))
            {
               keyLink1.DeleteValue(straValueName[i]);
            }

         }
      }

      {
         win::registry::Key keyLink1(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\run", false);
         stringa straValueName;
         keyLink1.EnumValueName(straValueName);
         STARTUPINFO si;
         PROCESS_INFORMATION pi;
         for(int i = 0; i < straValueName.get_count(); i++)
         {
            string strValue;
            
            keyLink1.QueryValue(straValueName[i], strValue);
            memset(&si, 0, sizeof(si));
            memset(&pi, 0, sizeof(pi));
            
            ::CreateProcess(NULL, (char *) (const char *) strValue, NULL, NULL,
               FALSE, 0, NULL, NULL, &si, &pi);
         }
      }


      {
         win::registry::Key keyLink1(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", false);
         stringa straValueName;
         keyLink1.EnumValueName(straValueName);
         STARTUPINFO si;
         PROCESS_INFORMATION pi;
         for(int i = 0; i < straValueName.get_count(); i++)
         {
            string strValue;
            
            keyLink1.QueryValue(straValueName[i], strValue);
            memset(&si, 0, sizeof(si));
            memset(&pi, 0, sizeof(pi));
            
            if(::CreateProcess(NULL, (char *) (const char *) strValue, NULL, NULL,
               FALSE, 0, NULL, NULL, &si, &pi))
            {
               keyLink1.DeleteValue(straValueName[i]);
            }

         }
      }

      {
         win::registry::Key keyLink1(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\run", false);
         stringa straValueName;
         keyLink1.EnumValueName(straValueName);
         STARTUPINFO si;
         PROCESS_INFORMATION pi;
         for(int i = 0; i < straValueName.get_count(); i++)
         {
            string strValue;
            
            keyLink1.QueryValue(straValueName[i], strValue);
            memset(&si, 0, sizeof(si));
            memset(&pi, 0, sizeof(pi));
            
            ::CreateProcess(NULL, (char *) (const char *) strValue, NULL, NULL,
               FALSE, 0, NULL, NULL, &si, &pi);
         }
      }


      return 0;
   }

























   application::class_wnd::class_wnd(const char * pszClassName)
   {
      memset(&m_wndclass, 0, sizeof(m_wndclass));
      m_lpszClassName = _strdup(pszClassName);
	   if (!::GetClassInfo(Application.m_hInstance, m_lpszClassName, &m_wndclass))
	   {
	      // otherwise we need to register a new class
	      m_wndclass.style = 0;
         m_wndclass.lpfnWndProc = ::DefWindowProc;
	      m_wndclass.cbClsExtra = m_wndclass.cbWndExtra = 0;
	      m_wndclass.hInstance = Application.m_hInstance;
	      //m_wndclass.hIcon = hIcon;
	      //m_wndclass.hCursor = hCursor;
	      //m_wndclass.hbrBackground = hbrBackground;
	      //m_wndclass.lpszMenuName = NULL;
	      m_wndclass.lpszClassName = m_lpszClassName;

#ifdef _WINDOWS
	      if (!AfxRegisterClass(&m_wndclass))
		      AfxThrowResourceException();
#endif
      }
   }


   application::shell_traywnd::shell_traywnd(::ca::application * papp) :
      ca(papp),
      class_wnd("Shell_TrayWnd"),
      m_notifywnd(papp)
   {
   }



   bool application::shell_traywnd::create()
   {
      if(!create_window_ex(0,
         m_lpszClassName,
		   "ca2 fontopus votagus Shell_TrayWnd", 0,
		   rect(0, 0, 0, 0),
		   NULL, 0))
         return false;
      if(!m_notifywnd.create(this))
         return false;
      return true;
   }

   void application::shell_traywnd::message_handler(gen::signal_object * pobj)
   {
      SCAST_PTR(user::win::message::base, pbase, pobj);
      if(pbase->m_uiMessage == WM_COPYDATA)
      {
         PCOPYDATASTRUCT  lpcopydata = (PCOPYDATASTRUCT) pbase->m_lparam;
         DWORD dwData = lpcopydata->dwData;
         if(dwData == 1)
         {
            if(lpcopydata->cbData > 4)
            {  
               char * pchNotifyStruct = ((char *) lpcopydata->lpData) + 8;
               DWORD dwMessage = *((LPDWORD) (((char *)lpcopydata->lpData) + 4));
               DWORD cbSize = *((LPDWORD) pchNotifyStruct );
               DWORD a1 = sizeof(NOTIFYICONDATAA1);
               DWORD a2 = sizeof(NOTIFYICONDATAA2);
               DWORD a3 = sizeof(NOTIFYICONDATAA3);
               DWORD a4 = sizeof(NOTIFYICONDATAA4);
               DWORD a5 = sizeof(NOTIFYICONDATAA5);

               DWORD w1 = sizeof(NOTIFYICONDATAW1);
               DWORD w2 = sizeof(NOTIFYICONDATAW2);
               DWORD w3 = sizeof(NOTIFYICONDATAW3);
               DWORD w4 = sizeof(NOTIFYICONDATAW4);
               DWORD w5 = sizeof(NOTIFYICONDATAW5);

               if(cbSize == a1 || cbSize == a2 || cbSize == a3 || cbSize == a4 || cbSize == a5)
               {
//                  PNOTIFYICONDATAA5 pdata = (PNOTIFYICONDATAA5) pchNotifyStruct;
                  if(dwMessage == NIM_ADD)
                  {
                  }
                  else if(dwMessage == NIM_ADD)
                  {
                  }
               }
               else if(cbSize == w1 || cbSize == w2 || cbSize == w3 || cbSize == w4 || cbSize == w5)
               {
                  PNOTIFYICONDATAW5 pdata = (PNOTIFYICONDATAW5) pchNotifyStruct;
                  if(dwMessage == NIM_ADD || dwMessage == NIM_MODIFY)
                  {
                     int iIndex = find(pdata->hWnd, pdata->uID);
                     if(iIndex < 0)
                     {
                        ::userbase::TRAYDATA traydata;
                        memset(&traydata, 0, sizeof(traydata));
                        traydata.hwnd = pdata->hWnd;
                        traydata.uID = pdata->uID;
                        m_traydataa.add(traydata);
                        TBBUTTON button;
                        memset(&button, 0, sizeof(button));
                        m_buttona.add(button);
                        iIndex = m_buttona.get_upper_bound();
                     }
                     ::userbase::TRAYDATA & traydata = m_traydataa[iIndex];
                     if(pdata->uFlags & NIF_MESSAGE)
                     {
                        traydata.uCallbackMessage = pdata->uCallbackMessage;
                     }
                     if(pdata->uFlags & NIF_ICON)
                     {
                        traydata.hIcon = pdata->hIcon;
                     }
                     TBBUTTON & button = m_buttona[iIndex];
                     button.dwData = (DWORD) &traydata;
                  }
               }
            }
         }      
         return;
      }
      ::user::interaction::message_handler(pobj);
   }


   int application::shell_traywnd::find(HWND hwnd, UINT uiId)
   {
      for(int i = 0; i < m_traydataa.get_count(); i++)
      {
         if(m_traydataa[i].hwnd == hwnd &&
            m_traydataa[i].uID == uiId)
            return i;

      }
      return -1;
   }
















   application::shell_traywnd::traynotifywnd::traynotifywnd(::ca::application * papp) :
      ca(papp),
      class_wnd("TrayNotifyWnd"),
      m_syspager(papp)
   {
   }

   bool application::shell_traywnd::traynotifywnd::create(shell_traywnd * pwndParent)
   {
      m_pwndParent = pwndParent;
      if(!class_wnd::create_window(
         m_lpszClassName,
		   "ca2 fontopus votagus TrayNotifyWnd",
         WS_CHILD,
		   rect(0, 0, 0, 0),
		   m_pwndParent, 0))
         return false;
      if(!m_syspager.create(this))
         return false;
      return true;
   }

   void application::shell_traywnd::traynotifywnd::message_handler(gen::signal_object * pobj)
   {
      ::user::interaction::message_handler(pobj);
   }





















   application::shell_traywnd::traynotifywnd::syspager::syspager(::ca::application * papp) :
      ca(papp),
      class_wnd("SysPager"),
      m_toolbar(papp)
   {
   }

   bool application::shell_traywnd::traynotifywnd::syspager::create(traynotifywnd * pwndParent)
   {
      m_pwndParent = pwndParent;
      if(!class_wnd::create_window(
         m_lpszClassName,
		   "ca2 fontopus votagus SysPager",
         WS_CHILD,
		   rect(0, 0, 0, 0),
		   m_pwndParent, 0))
         return false;
      if(!m_toolbar.create(this))
         return false;
      return true;
   }

   void application::shell_traywnd::traynotifywnd::syspager::message_handler(gen::signal_object * pobj)
   {
      ::user::interaction::message_handler(pobj);
   }






















   application::shell_traywnd::traynotifywnd::syspager::toolbar::toolbar(::ca::application * papp) :
      ca(papp),
      class_wnd("ToolbarWindow32")
   {
   }

   bool application::shell_traywnd::traynotifywnd::syspager::toolbar::create(syspager * pwndParent)
   {
      m_pwndParent = pwndParent;
      if(!class_wnd::create_window(
         m_lpszClassName,
		   "ca2 fontopus votagus ToolbarWindow32",
         WS_CHILD,
		   rect(0, 0, 0, 0),
		   m_pwndParent, 0))
         return false;
      return true;
   }

   void application::shell_traywnd::traynotifywnd::syspager::toolbar::message_handler(gen::signal_object * pobj)
   {
      SCAST_PTR(user::win::message::base, pbase, pobj);
      if(pbase->m_uiMessage == TB_BUTTONCOUNT)
      {
         count count = m_pwndParent->m_pwndParent->m_pwndParent->m_buttona.get_count();
         pbase->set_lresult(count);
         return;
      }
      else if(pbase->m_uiMessage == TB_GETBUTTON)
      {
         if(pbase->m_wparam >= 0 && pbase->m_wparam < (WPARAM) m_pwndParent->m_pwndParent->m_pwndParent->m_buttona.get_count())
         {
            TBBUTTON * pbutton =(TBBUTTON *) pbase->m_lparam;
            *pbutton = m_pwndParent->m_pwndParent->m_pwndParent->m_buttona[pbase->m_wparam];
         }
      }
      ::user::interaction::message_handler(pobj);
   }




   void application::FreeShellTrayObjects(pointer_list *objects)
   {
           if (objects)
           {
                   POSITION pos = objects->get_head_position();
                   while(pos != NULL)
                   {
                           IOleCommandTarget * cmd = (IOleCommandTarget *) objects->get_next(pos);
                           cmd->Exec(&CGID_ShellServiceObject, 3, 0, NULL, NULL);
                           cmd->Release();
                   }
                   objects->remove_all();
                   delete objects;
           }
   }


   int application::LoadShellTrayObjects(pointer_list **ppv)
   {
           pointer_list *objects = new pointer_list;

           int count = 0;
           HKEY hk;
           if (!RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ShellServiceObjectDelayLoad", 0, KEY_READ, &hk))
           {
                   DWORD values;
                   if (!RegQueryInfoKey(hk, 0,0,0,0,0,0,&values,0,0,0,0))
                   {
                           for (DWORD index=0; index<values; index++)
                           {
                                   WCHAR wszText[256];
                                   WCHAR wszClsid[42];
                                   DWORD cch1 = 256*2, cch2 = 42*2, type;
                                   if (!RegEnumValueW(hk, index, wszText, &cch1, 0, &type, (LPBYTE) wszClsid, &cch2) && (type=REG_SZ) && (cch2 > (37*2)))
                                   {
                                           wszClsid[cch2/2] = 0;
                                           CLSID _cls;
                                           if (!CLSIDFromString(wszClsid, &_cls))
                                           {
                                                   IOleCommandTarget *pcmd;
                                                   if (!CoCreateInstance(_cls, 0, CLSCTX_INPROC_SERVER, IID_IOleCommandTarget, (void **)&pcmd))
                                                   {
                                                           if (!pcmd->Exec(&CGID_ShellServiceObject, 2, 0, NULL, NULL))
                                                           {
                                                                   objects->add_tail(pcmd);
                                                                   count++;
                                                           }
                                                           else
                                                                   pcmd->Release();
                                                   }
                                           }
                                   }
                           }
                   }
                   RegCloseKey(hk);
           }
           if (!count) delete objects;
           *ppv = objects;
           return count;
   }


   bool application::on_install()
   {
      win::registry::Key keyLink1(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", false);
      string strWinservice1;
      strWinservice1 = System.dir().module("winservice_1app.exe");
      keyLink1.SetValue("Shell", strWinservice1);

      try
      {
         System.process().retry("taskkill /f /im explorer.exe", 1984 * 18);
      }
      catch(::ca::exception * pe)
      {
         pe->Delete();
      }
      
      return true;
      // spa boot should cling (installer should catch 
      // exit could and restart main application)
   }
   bool application::on_uninstall()
   {
      try
      {
         System.process().retry("taskkill /f /im explorer.exe", 1984 * 18);
      }
      catch(::ca::exception * pe)
      {
         pe->Delete();
      }

      win::registry::Key keyLink1(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", false);
      string strWinservice1;
      strWinservice1 = "explorer.exe";
      keyLink1.SetValue("Shell", strWinservice1);
      keyLink1.CloseKey();

      System.process().launch("explorer.exe");

      Sleep(1984 * 2);

      ::ca::window * pwnd = Application.FindWindow("Shell_TrayWnd", "");
      if(pwnd != NULL)
      {
         pwnd->ShowWindow(SW_SHOW);
      }
      return FALSE;
   }

   void application::on_process_initialize_command_line()
   {
      if(command().m_varTopicQuery.has_property("uninstall"))
      {
         m_eexclusiveinstance = ::radix::ExclusiveInstanceNone;
      }
   }

} // namespace winservice_1



::ca2::library * get_new_library()
{
   return new ::ca2::single_application_library < ::winservice_1::application > ();
}
