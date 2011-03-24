#include "StdAfx.h"


void simple_se_translator(unsigned int uiCode, EXCEPTION_POINTERS * ppointers)
{
   throw 0;
}




namespace npca2
{

   VOID CALLBACK TimerProcRedraw(HWND hwnd,  UINT uMsg,  UINT_PTR idEvent,  DWORD dwTime);

   plugin::plugin() :
      m_bInitialized(false)
   {
      m_puiHost               = NULL;
      m_bCa2JustInstalled     = false;
      m_iHealingSurface       = 0;
      m_pszUrl                = NULL;
      m_iEdge                 = -1;
      m_pbergedge             = NULL;
      m_bAppStarted           = false;
      m_hEventReady           = NULL;
      m_psystem               = NULL;

      npca2::MyRegisterClass(g_hinstance);



      m_hwndMessage = ::CreateWindowExA(0, "TeDigoSó", "ca2::fontopus::ccvotagus::spaboot:callback_window", 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, NULL, NULL);

      ::SetTimer(m_hwndMessage, (UINT_PTR) this, 50, TimerProcRedraw);
   }



   void plugin::onBarePaint(HDC hdc, LPCRECT lprect)
   {
      RECT rectWindow;
      get_window_rect(&rectWindow);
      int cx = rectWindow.right - rectWindow.left;
      int cy = rectWindow.bottom - rectWindow.top;
      RECT rect;
      rect.left      = 0;
      rect.top       = 0;
      rect.bottom    = cy;
      rect.right     = cx;
      {
         HPEN hpen = ::CreatePen(PS_SOLID, 1, RGB(84, 84, 77));
         HBRUSH hbrush = (HBRUSH) ::GetStockObject(NULL_BRUSH);
         ::SelectObject(hdc, hpen);
         ::SelectObject(hdc, hbrush);
         ::Rectangle(hdc, lprect->left, lprect->top, lprect->right, lprect->bottom);
         ::DeleteObject(hbrush);
         ::DeleteObject(hpen);
      }
      HFONT hfont = ::CreatePointFont_dup(100, "Lucida Sans Unicode", hdc);
      HFONT hfontOld = (HFONT) ::SelectObject(hdc, (HGDIOBJ) hfont);
      ::SelectObject(hdc, hfont);
//         ::FillSolidRect_dup(hdc, &rect, RGB(255, 255, 255));
      //::SetBkColor(
      ::SetBkMode(hdc, TRANSPARENT);
      ::SetTextColor(hdc, RGB(84, 84, 77));
      const char * psz = "Thank you";
      ::TextOutU_dup(hdc, 10, 10, psz, strlen(psz));
      ::SelectObject(hdc, hfontOld);
   }



/*   UINT __cdecl plugin::ThreadProcStart(LPVOID lpv)
   {
      plugin * pplugin = (plugin *) lpv;
      try
      {
         return pplugin->start_bergedge_cube();
      }
      catch(...)
      {
      }
      return -1;
   }*/



   void plugin::on_prepare_memory()
   {
   }


   void plugin::start_ca2()
   {
      update_spa_installed();
      if(is_spa_installed())
      {
         update_spa_updated();
         if(is_spa_updated())
         {
            update_ca2_installed();
            if(is_ca2_installed())
               update_ca2_updated();
         }
      }
   

      if(is_spa_installed() && is_spa_updated() && is_ca2_installed() && is_ca2_updated())
      {
         npca2_plugin_start_bergedge_cube();
      }
      else
      {
         starter_start("mplite");
      }

   }


   int plugin::starter_start(const char * pszId)
   {
      set_installing_ca2();
      npca2::starter_start * pstart = new npca2::starter_start;
      pstart->m_pplugin  = this;
      pstart->m_strId      = pszId;
      _beginthreadex(NULL, 0, _ca2_starter_start, pstart, 0, &g_nCa2StarterStartThreadID); 
   //      ::SetTimer(hWnd, 19841977, 100, NULL);
      return 0;
   }




   bool plugin::hist(const char * pszUrl)
   {
      return open_url(pszUrl);
   }


   void plugin::run_start_install(const char * pszInstall)
   {
   
      {
         XNode node;
         // remove install tag : should be turned into a function dependant of spalib at maximum
         if(!node.Load(file::get_contents(dir::appdata("spa_install.xml").c_str()).c_str()))
            goto install;
         XNode * lpnodeInstalled = node.GetChild("installed");
         if(lpnodeInstalled == NULL)
            goto install;
         XNode * pnode = lpnodeInstalled->GetChildByAttr("application", "id", pszInstall);
         if(pnode == NULL)
            goto install;
         lpnodeInstalled->RemoveChild(pnode);
         file::put_contents(dir::appdata("spa_install.xml").c_str(), node.GetXML(NULL).c_str());
      }
install:


      starter_start(pszInstall);


   }


   void plugin::onPaint(HDC hdcWindow, LPCRECT lprect)
   {
      RECT rectWindow;
      get_window_rect(&rectWindow);

      int cx = rectWindow.right - rectWindow.left;
      int cy = rectWindow.bottom - rectWindow.top;

      RECT rect;
      rect.left         = 0;
      rect.top          = 0;
      rect.right        = cx;
      rect.bottom       = cy;

      HBITMAP hbmp      = ::CreateCompatibleBitmap(hdcWindow, cx, cy);
      HDC hdc           = ::CreateCompatibleDC(hdcWindow);
      HBITMAP hbmpOld   =  (HBITMAP) ::SelectObject(hdc, (HGDIOBJ) hbmp);
   
      ::BitBlt(hdc, 0, 0, cx, cy, hdcWindow, m_rect.left, m_rect.top, SRCCOPY);

      HFONT hfontOld = NULL;
      HFONT hfont = NULL;
      if(is_installing_ca2())
      {
         ca2_install_canvas_on_paint(hdc, &rect, m_iHealingSurface);
      }
      else if(!is_ca2_installed())
      {
         RECT rect;
         rect.left      = 0;
         rect.top       = 0;
         rect.bottom    = cx;
         rect.right     = cy;
         ::FillSolidRect(hdc, &rect, RGB(255, 255, 255));
         ::SetTextColor(hdc, RGB(255, 0, 255));
         const char * psz = "ca2 is not installed! You may try to install using low level install_spaboot.exe.";
         ::TextOutU(hdc, 10, 10, psz, strlen(psz));
      }
      else
      {
         RECT rect;
         rect.left      = 0;
         rect.top       = 0;
         rect.bottom    = cx;
         rect.right     = cy;
         ::FillSolidRect(hdc, &rect, RGB(255, 255, 255));
         ::SetTextColor(hdc, RGB(255, 255, 255));
         const char * psz = "Thank you";
         ::TextOutU(hdc, 10, 10, psz, strlen(psz));
      }
      POINT pointViewport;
      ::SetViewportOrgEx(hdc, 0, 0, &pointViewport);
      ::BitBlt(hdcWindow, lprect->left, lprect->top, lprect->right - lprect->left, lprect->bottom - lprect->top, 
               hdc,       lprect->left - m_rect.left, lprect->top - m_rect.top, SRCCOPY);
      ::SelectObject(hdc, (HGDIOBJ) hbmpOld);
      if(hfontOld != NULL)
      {
         ::SelectObject(hdc,(HGDIOBJ)  hfontOld);
      }
      if(hfont != NULL)
      {
         ::DeleteObject(hfont);
      }
      ::DeleteObject(hbmp);
      ::DeleteDC(hdc);
   }

   int plugin::npca2_plugin_start_bergedge_cube()
   {
      bool bNew = false;
      if(m_psystem == NULL)
      {
         m_bAppStarted = false;
         
         _set_purecall_handler(_ca2_purecall);

         if(get_heap_mutex() == NULL)
         {
            set_heap_mutex(new mutex());
         }

         if(::icube::get_heap_itema() == NULL)
         {
            ::icube::set_heap_itema(new class ::icube::system::heap_item_array());
         }

         m_psystem = new ::npca2::system();

         m_psystem->m_pplugin = this;

/*         ::win::main_init_data * pinitmaindata  = new ::win::main_init_data;

         pinitmaindata->m_hInstance             = g_hinstance;
         pinitmaindata->m_hPrevInstance         = NULL;
         pinitmaindata->m_nCmdShow              = SW_SHOW;

         m_psystem->init_main_data(pinitmaindata);
         */

         //new_wstring_manager();


      //   papp->m_bSessionSynchronizedCursor  = false;
         //papp->m_bSessionSynchronizedScreen  = false;
//         papp->set_app(papp);

         m_psystem->m_hInstance = g_hinstance;
      
         if(!m_psystem->InitApplication())
            return 0;
      
         if(!m_psystem->process_initialize())
            return 0;

         m_psystem->set_history(new npca2::history(m_psystem, this));
         m_psystem->m_prunstartinstaller = new npca2::run_start_installer(m_psystem, this);

         m_psystem->m_bInitializeProDevianMode = false;
         string strId;
         strId.Format("npca2::%08x", (UINT_PTR) m_psystem);
         m_psystem->command_line().m_varQuery["local_mutex_id"] = strId;
         m_psystem->command_line().m_varQuery["client_only"] = true;


      }

   

      //set_app(papp);
      


      m_puiHost = create_host_interaction();
      m_puiHost->m_pplugin = this;


      m_puiHost->_001InstallMessageHandling(m_puiHost->m_pimpl);

      if(m_puiHost != NULL)
      {
         m_puiHost->m_bRectOk = true;
         m_puiHost->m_pimpl->m_bRectOk = true;
         m_puiHost->m_rectParentClient = m_rect;
         m_puiHost->m_rectParentClient.offset(-point64(m_puiHost->m_rectParentClient.top_left()));
         m_puiHost->m_pimpl->m_rectParentClient = m_puiHost->m_rectParentClient;
         m_puiHost->SendMessageA(WM_SIZE);
         m_puiHost->SendMessageA(WM_MOVE);
      }

      if(!check(npca2::check_before_auth))
         return 0;


      m_psystem->m_puiInitialPlaceHolderContainer = m_puiHost;
//	   hwnd_map* pMap = afxMapHWND(TRUE);
      //pMap->set_permanent(m_hwnd, dynamic_cast < win::window * >(m_puiHost->m_pimpl));
      //App(papp).get_twf()->m_bRun = false;
      //App(papp).get_twf()->m_bProDevianMode = false;
      m_psystem->add_frame(m_puiHost);
      m_puiHost->layout();

      if(m_hEventReady == NULL)
         m_hEventReady = ::CreateEventA(NULL, TRUE, FALSE, NULL);

      if(bNew || !m_bAppStarted)
      {
         m_bAppStarted = true;
         m_psystem->Begin();
         //AfxBeginThread(m_psystem, ThreadProcStart, (LPVOID) this);
      }

      m_bInitialized = true;

      if(!bNew && !m_bPreCheck)
      {
         pre_check();
      }
      if(m_puiHost != NULL)
      {
         //m_puiHost->defer_check(check_before_start);
      }
      return 0;
   }

   bool plugin::os_native_bergedge_start()
   {
      
      if(!m_bPreCheck)
      {
         pre_check();
      }

      m_bApp = true;
      m_puiHost->defer_check(check_before_start);
      
      return true;

   }


/*   UINT plugin::start_bergedge_cube()
   {
   
      ::icube::system * papp = m_psystem;
      
      if(!papp->initialize_instance())
         return 0;

//      if(!papp->bergedge_start())
  //       return 0;


    //  papp->m_puiInitialPlaceHolderContainer = papp->get_edge(0, true)->get_bergedge_view();



      papp->m_bShouldInitializeGTwf = false;
/*      win::thread * pthread = dynamic_cast < win::thread *> (papp->smart_pointer < ::ca::thread > ::m_p);
      win::thread * pthreadCur = dynamic_cast < win::thread *> (papp->GetThread()->m_p);
      pthread->m_hThread = pthreadCur->m_hThread;
      pthread->m_nThreadID = pthreadCur->m_nThreadID;

      papp->_001InstallMessageHandling(pthreadCur);*/

  /*    ::SetEvent(m_hEventReady);
      

      /*if(papp->does_launch_window_on_startup())
      {
         int iRetry = 100;
         while(papp->m_pwndMain == NULL && (iRetry > 0))
         {
            Sleep(100);
            iRetry--;
         }
         if(papp->m_pwndMain != NULL)
         {
   //            papp->m_pwndMain->SetParent(pview);
            papp->m_pwndMain->ModifyStyle(0, WS_CHILD);
            papp->m_pwndMain->SetWindowPos(NULL, 0, 0, 400, 400, SWP_SHOWWINDOW);
         }
      }*/


   //   pplugin->m_pframe = dynamic_cast < bergedge::frame * > (pplugin->m_papp->get_edge(0, true)->get_bergedge_view()->GetParentFrame());


   /*   papp->m_puiInitialPlaceHolderContainer = pplugin->m_pframe;

      App(pplugin->m_papp).GetThread()->SetMainWnd(pplugin->m_pframe);
      pplugin->m_pframe->m_bCustomFrame = false;
      pplugin->m_pframe->GetParent()->layout();*/



      /*try
      {
         papp->run();
      }
      catch(...)
      {
      }

      int iExitCode = -1;

      try
      {
         iExitCode = papp->exit_instance();
         //TRACE("Exit Code from retract_app %d (exit_instance %s)", iExitCode, typeid(*papp).raw_name());
      }
      catch(...)
      {
      }
      pthread->m_hThread = NULL;
      pthread->m_nThreadID = NULL;
   
      WIN_THREAD(papp->smart_pointer < ::ca::thread >::m_p)->m_bRun = false;
      ::SetEvent(m_hEventReady);
      //papp->m_bRun = false;

      return iExitCode;
   }*/

   void plugin::onCa2Paint(HDC hdcWindow, LPCRECT lprect)
   {
      if(m_puiHost == NULL)
         return;
      RECT rect;
      rect.left = m_rect.left;
      rect.top = m_rect.top;
      rect.right = m_rect.right;
      rect.bottom = m_rect.bottom;
      rect.bottom -= rect.top;
      rect.top = 0;
      rect.right -= rect.left;
      rect.left = 0;
      rect64 rectWindow;
      m_puiHost->GetWindowRect(&rectWindow);
      RECT rectDesktop;
      ::GetWindowRect(::GetDesktopWindow(), &rectDesktop);
      int w = rectDesktop.right;
      int h = rectDesktop.bottom;
      HBITMAP hbmp = ::CreateCompatibleBitmap(hdcWindow, w, h);
      HDC hdc = ::CreateCompatibleDC(hdcWindow);
      HBITMAP hbmpOld =  (HBITMAP) ::SelectObject(hdc, (HGDIOBJ) hbmp);
      HFONT hfontOld = NULL;
      HFONT hfont = NULL;
      ::BitBlt(hdc, lprect->left + rectWindow.left - m_rect.left, lprect->top + rectWindow.top - m_rect.top, lprect->right - lprect->left, lprect->bottom - lprect->top, hdcWindow, lprect->left, lprect->top, SRCCOPY);
      try
      {
         ca::graphics * pgraphics = m_psystem->graphics_from_os_data(hdc);
         pgraphics->set_app(m_puiHost->m_papp);
         m_puiHost->_000OnDraw(pgraphics);
      }
      catch(...)
      {
      }
      POINT pointViewport;
      ::SetViewportOrgEx(hdc, 0, 0, &pointViewport);
      ::BitBlt(hdcWindow, lprect->left, lprect->top, lprect->right - lprect->left, lprect->bottom - lprect->top, hdc, lprect->left + rectWindow.left - m_rect.left, lprect->top + rectWindow.top - m_rect.top, SRCCOPY);
      ::SelectObject(hdc, (HGDIOBJ) hbmpOld);
      if(hfontOld != NULL)
      {
         ::SelectObject(hdc,(HGDIOBJ)  hfontOld);
      }
      if(hfont != NULL)
      {
         ::DeleteObject(hfont);
      }
      ::DeleteObject(hbmp);
      ::DeleteDC(hdc);

   }


   bool plugin::pre_check()
   {
      if(m_bPreCheck)
         return true;
      ::primitive::memory * pmemory = new ::primitive::memory;
      pmemory->set_app(m_psystem);
      gen::memory_file * pmemoryfile = new gen::memory_file(m_psystem, *pmemory);
      ::sockets::http::file * pfile = new ::sockets::http::file(m_psystem, pmemoryfile);
      pfile->m_ulFlags &= ~::ca::ca::flag_auto_clean;
      pfile->m_p->m_ulFlags &= ~::ca::ca::flag_auto_clean;

      if(m_pszUrl == NULL)
         return false;

      if(gen::str::ends_ci(m_pszUrl, ".mp3")
      || gen::str::ends_ci(m_pszUrl, ".kar")
      || gen::str::ends_ci(m_pszUrl, ".mid")
      || gen::str::ends_ci(m_pszUrl, ".st3"))
      {
         if(m_pmemory != NULL)
         {
            m_psystem->command_line().m_varQuery["file"].propset()["file"] = (::ca::object *) m_pfile;
            m_psystem->command_line().m_varQuery["file"].propset()["url"] = m_psystem->url().url_decode(m_pszUrl);
            m_psystem->open_by_file_extension(0, m_pszUrl);
         }
         else 
         {
            m_psystem->command_line().m_varQuery["uri"] = m_pszUrl;
            try
            {
               m_psystem->open_by_file_extension(0, m_psystem->url().url_decode(m_pszUrl));
            }
            catch(...)
            {
               return false;
            }
         }
      }

      m_pmemory = pmemory;
      m_pfile = pfile->m_p;

      m_bPreCheck = true;
      return true;
   }


   bool plugin::check(e_check echeck)
   {
      string str;
      on_prepare_memory();
      LPSTR lpszAlloc = NULL;
      int iCount =  0;
      if(m_pmemory != NULL && m_lpbMemory == NULL)
      {
         lpszAlloc = (char *) m_pmemory->GetAllocation();
         iCount = m_pmemory->get_size();
      }
      else
      {
         lpszAlloc = (char *) m_lpbMemory;
         iCount = m_iMemory;
      }

      // TODO |) : Should parse Content-type:
      // ALSO: this case only happens if all file has been downloaded before the plugin has initialized
      if(gen::str::ends_ci(m_pszUrl, ".mp3")
      || gen::str::ends_ci(m_pszUrl, ".mid")
      || gen::str::ends_ci(m_pszUrl, ".kar")
      || gen::str::ends_ci(m_pszUrl, ".st3"))
      {
      }
      else
      {
         LPSTR lpszStart = lpszAlloc;
         LPSTR lpszEnd = NULL;
         int i = 0;
         for(; i < iCount; i++)
         {
            lpszEnd = &lpszStart[i];
            if(*lpszEnd == '\n')
            {
               str = string(lpszStart, lpszEnd - lpszStart);
               break;
            }
         }
         str.trim();

         if(echeck >= check_before_start && str == "ca2login")
         {
            delete m_psystem->m_puser;
            m_psystem->m_puser = NULL;
            m_psystem->create_current_user();
            gen::property_set set(m_psystem);
            set.parse_url_query(string(lpszEnd + 1, iCount - (lpszEnd - lpszStart) - 1));
            string strLocation = set["ruri"];
            strLocation = m_psystem->url().set(strLocation, "sessid", m_psystem->m_puser->m_strSessid);
            strLocation = m_psystem->url().remove(strLocation, "action");
            open_url(strLocation);
            return false;
         }
         else if(echeck >= check_before_auth && str == "ca2logout")
         {
            m_psystem->logout();
            gen::property_set set(m_psystem);
            set.parse_url_query(string(lpszEnd + 1, iCount - (lpszEnd - lpszStart) - 1));
            string strLocation = set["ruri"];
            strLocation = m_psystem->url().remove(strLocation, "sessid");
            strLocation = m_psystem->url().remove(strLocation, "action");
            string strUrl;
            strUrl = "https://fontopus.com/sec?action=logout";
            strUrl = m_psystem->url().set(strUrl, "ruri", strLocation);
            open_url(strUrl);
            return false;
         }
         else if(echeck >= check_before_start && str == "ca2prompt")
         {
            m_puiHost->layout();
            lpszStart = lpszEnd;
            for(; (lpszEnd - lpszAlloc) <= iCount; i++)
            {
               if(*lpszEnd == '\0' || !gen::ch::is_whitespace(lpszEnd))
                  break;
               lpszEnd = (char *) gen::str::utf8_inc(lpszEnd);
            }
            lpszStart = lpszEnd;
            for(; (lpszEnd - lpszAlloc) <= iCount; i++)
            {
               if(*lpszEnd == '\0' || gen::ch::is_space_char(lpszEnd) || (lpszEnd - lpszAlloc) == iCount)
               {
                  str = string(lpszStart, lpszEnd - lpszStart);
                  break;
               }
               lpszEnd = (char *) gen::str::utf8_inc(lpszEnd);
            }
            if(!m_bApp)
            {
               ::WaitForSingleObject(m_hEventReady, (1984 + 1977) * 20);
               if(!m_bApp)
               {
                  printf("Bergedge application is not initialized. Cannot start mplite.");
                  return true;
               }
            }
            if(str.has_char())
            {
               string strId = str;
               int iFind = strId.find("?");
               if(iFind >= 0)
               {
                  strId = strId.Left(iFind);
               }
               if(!is_installed(strId))
               {
                  starter_start(strId);
               }
               else
               {
                  var varFile;
                  gen::property_set setParameters(m_psystem);
                  m_psystem->m_puiInitialPlaceHolderContainer = m_puiHost;
                  var varId;
                  string strId = m_psystem->url().get_script(str);
                  string strParameters = m_psystem->url().get_query(str);
                  setParameters.parse_url_query(strParameters);
                  ::ca2::application_request * prequest = new ::ca2::application_request;
                  prequest->m_iEdge = 0;
                  prequest->m_strApp = strId;
                  prequest->m_varFile = varFile;
                  prequest->m_varQuery = setParameters;
                  m_psystem->PostThreadMessageA(WM_APP + 2043, 0, (LPARAM) prequest);
               }
            }
         }
      }
      return true;
   }


   void plugin::finalize()
   {
      ::KillTimer(m_hwndMessage, (UINT_PTR) this);
      if(!m_bAppStarted)
         return;

      try
      {
         m_puiHost->DestroyWindow();
      }
      catch(...)
      {
      }

      ::radix::thread * pthread = dynamic_cast < ::radix::thread * > (m_psystem->smart_pointer < ::ca::thread >::m_p);

      if(pthread->m_bRun)
      {
         ::ResetEvent(m_hEventReady);
         pthread->m_bRun = false;
         ::WaitForSingleObject(m_hEventReady, (1984 + 1977) * 20);
      }
      try
      {
         ::DeleteObject(m_hEventReady);
      }
      catch(...)
      {
      }

      _se_translator_function pfn = _set_se_translator(&simple_se_translator);
      try
      {
         delete m_psystem;
      }
      catch(...)
      {
      }
      _set_se_translator(pfn);

   }



   VOID CALLBACK TimerProcRedraw(HWND hwnd,  UINT uMsg,  UINT_PTR idEvent,  DWORD dwTime)
   {

      plugin * pplugin = (plugin *) idEvent;
      try
      {
         pplugin->redraw();
      }
      catch(...)
      {
      }
   }



//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
/*   case WM_COPYDATA:
      {
         COPYDATASTRUCT * pcds = (COPYDATASTRUCT *) lParam;
         if(pcds->dwData == 15111984)
         {
            std::string str((const char *) pcds->lpData, pcds->cbData);
            g_straRestartCommandLine.decode_v16(str.c_str());
         }
      }
      break;*/
   default:
      return DefWindowProc(hWnd, message, wParam, lParam);
   }
	return 0;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			   = 0;
	wcex.lpfnWndProc	   = WndProc;
	wcex.cbClsExtra	   = 0;
	wcex.cbWndExtra	   = 0;
	wcex.hInstance		   = hInstance;
	wcex.hIcon			   = NULL;
	wcex.hCursor		   = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	//wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_CCVOTAGUS_CA2_SPA);
   wcex.lpszMenuName	   = NULL;
	wcex.lpszClassName	= "TeDigoSó";
	wcex.hIconSm		   = NULL;

	return RegisterClassEx(&wcex);
}

} // namespace npca2


