#include "framework.h"


#ifdef WINDOWS
#undef new
#include <gdiplus.h>
#endif

#if defined(LINUX) || defined(ANDROID) || defined(APPLEOS)
#include <sys/mman.h>
//#include <sys/stat.h>
//#include <fcntl.h>
#endif

void CLASS_DECL_CORE __cdecl _ca2_purecall_();


void CLASS_DECL_CORE __cdecl _ca2_purecall_()
{
    throw simple_exception(get_thread_app());
}

namespace plugin
{

   void ms_get_dup_status_callback(void * p, int32_t i, uint_ptr dw);
   void my_se_translator_function(uint32_t, struct _EXCEPTION_POINTERS* );


   plugin::plugin(sp(::axis::application) papp) :
      element(papp),
      ::simple_ui::style(papp),
      ::user::interaction(papp),
      hotplugin::plugin(papp),
      ::base::session(papp)
   {

      m_puiHost               = NULL;
      m_iHealingSurface       = 0;
      m_iEdge                 = -1;
      m_bAppStarted           = false;
      m_pbReady               = NULL;
      m_bMainReady            = false;

      m_pbitmap               = NULL;
      m_pgraphics             = NULL;

#ifdef WINDOWS
      m_hfileBitmap           = INVALID_HANDLE_VALUE;
      m_hfilemapBitmap        = NULL;
      m_pcolorref             = NULL;
#else
      m_hfileBitmap           = -1;
      m_pcolorref             = (uint32_t *) MAP_FAILED;
#endif
      m_pmutexBitmap          = NULL;

   }

   bool plugin::hist(const char * pszUrl)
   {
      return open_link(pszUrl, "");
   }

   void plugin::run_start_install(const char * pszInstall)
   {
      UNREFERENCED_PARAMETER(pszInstall);
   }

   int32_t plugin::start_ca2_system()
   {

#ifdef METROWIN

      throw todo(get_app());

      return 0;

#else

      string strMutex = m_phost->m_vssChannel;

      ::str::begins_eat_ci(strMutex, "\\core\\");

      m_pmutexBitmap = new mutex(get_thread_app(), false, "Global\\" + strMutex);

      bool bNew = false;

      //Sleep(15 * 1000);

      synch_lock mlSystem(&m_phost->m_mutexSystem);

      if(m_phost->get_system() == NULL)
      {

#ifdef WINDOWS

         _set_purecall_handler(_ca2_purecall_);

#endif

         ::core::system * psystem = new ::core::system();

         psystem->m_bDoNotExitIfNoApplications = true;

         m_phost->m_pbaseapp = psystem;

         mlSystem.unlock();

//         int32_t nReturnCode = 0;

/*         ::win::main_init_data * pinitmaindata  = new ::win::main_init_data;

         pinitmaindata->m_hInstance             = hInstance;
         pinitmaindata->m_hPrevInstance         = hPrevInstance;
         pinitmaindata->m_vssCommandLine        = ::str::international::unicode_to_utf8(::GetCommandLineW());
         pinitmaindata->m_nCmdShow              = nCmdShow;


         psystem->init_main_data(pinitmaindata);*/

#ifdef WINDOWS

         psystem->m_hinstance = ::GetModuleHandle("core.dll");

#endif

         if(!psystem->InitApplication())
            return 0;

         if(!psystem->process_initialize())
            return 0;

         psystem->start_application(true, NULL);



      }

      mlSystem.unlock();

//      if(m_psystem == NULL)
  //    {

    //     m_psystem = m_phost->get_system();

      //      set_app(m_phost->get_system());
//         m_bAppStarted = false;
//
//         m_psystem = new ::plugin::system((::core::system *) m_phost->get_system());
//
//         System.m_pplugin = this;
//
//#ifdef WINDOWS
//
//         System.m_hinstance = ::GetModuleHandle("core.dll");
//
//#endif
//
//         if(!System.InitApplication())
//            return 0;
//
//         if(!System.process_initialize())
//            return 0;
//
//         System.set_history(new history(m_psystem, this));
//
//         System.m_prunstartinstaller = new run_start_installer(m_psystem, this);
//
//         System.m_bInitializeProDevianMode = false;
//
//         string strId;
//         strId.Format("npca2::%08x", (uint_ptr) m_psystem);
//
//         System.command()->m_varTopicQuery["local_mutex_id"] = strId;
//
//         set_app(m_psystem);

//      }

      m_puiHost = create_host_interaction();
      m_puiHost->m_pplugin = this;
      m_puiHost->install_message_handling(m_puiHost->m_pimpl);

      if(m_puiHost != NULL)
      {
//         System.oprop("top_parent") = m_puiHost;

         System.oprop("top_parent") = m_puiHost;

/*         m_puiHost->m_bRectOk = true;
         m_puiHost->m_pimpl->m_bRectOk = true;
         m_puiHost->m_rectParentClient = m_rect;
         m_puiHost->m_rectParentClient.offset(-point64(m_puiHost->m_rectParentClient.top_left()));
         m_puiHost->m_pimpl->m_rectParentClient = m_puiHost->m_rectParentClient;
         m_puiHost->SendMessageA(WM_SIZE);
         m_puiHost->SendMessageA(WM_MOVE);*/
//         class rect rect = m_phost->m_rect;
  //       set_window_rect(rect);
      }

///      System.m_puiInitialPlaceHolderContainer = m_puiHost;
      System.add_frame(m_puiHost);
      m_puiHost->layout();

      if(m_pbReady == NULL)
         m_pbReady = (bool *) memory_alloc(sizeof(bool));


#ifdef WINDOWS
      // Create Message Queue
      MESSAGE msg;
	   PeekMessage(&msg, NULL, 0, 0xffffffffu, FALSE);
#endif


      if(bNew || !m_bAppStarted)
      {
         m_bAppStarted = true;
//         System.begin();
      }

      m_bInitialized = true;

      m_bApp = true;

      set_ready();

      return 0;

#endif

   }


   void plugin::on_paint(::draw2d::graphics * pgraphics, const RECT & lprectOut)
   {

      UNREFERENCED_PARAMETER(lprectOut);

      ::rect rectClient;

      GetClientRect(rectClient);

      try
      {

         ensure_bitmap_data(rectClient.width(), rectClient.height(), true);

         if(m_puiHost == NULL)
            return;

         if(m_dib.is_null())
            m_dib.alloc(allocer());

         if(m_dib.is_null())
            return;

         m_dib->create(rectClient.size());

         if(m_dib->area() <= 0)
            return;

         m_dib->Fill(0, 0, 0, 0);



//         ::draw2d::graphics_sp dc(get_app());

         //dc->CreateCompatibleDC(NULL);

         //m_dib->defer_realize(dc);

         try
         {

            /*
            RECT rect;

            rect.left = 100;
            rect.right = 500;
            rect.top = 100;
            rect.bottom = 500;

            m_dib->get_graphics()->FillSolidRect(&rect, ARGB(128, 255, 255, 127));
            */

            m_puiHost->_000OnDraw(m_dib->get_graphics());

         }
         catch(...)
         {
         }

#ifdef WINDOWSEX

         ((Gdiplus::Graphics *) m_dib->get_graphics()->get_os_data())->Flush(Gdiplus::FlushIntentionSync);

         ::GdiFlush();

#endif

         m_sizeBitmap.cx = abs_dup(rectClient.width());

         m_sizeBitmap.cy = abs_dup(rectClient.height());

         {

            synch_lock sl(m_pmutexBitmap);

            memcpy(m_pcolorref, m_dib->get_data(), abs_dup(m_sizeBitmap.cy) * abs_dup(m_sizeBitmap.cx) * 4);

         }


      }
      catch(...)
      {
      }

      try
      {

         if(System.install().is_installing_ca2())
         {

            reload_plugin();

         }

      }
      catch(...)
      {
      }

   }

   void plugin::on_ready()
   {
      m_puiHost->post_message(host_interaction::message_check, 0, 1);
   }

   void plugin::start_ca2_login()
   {
      __begin_thread(m_puiHost->get_app(), &plugin::thread_proc_ca2_login, (LPVOID) this);
   }

   void plugin::start_ca2_logout()
   {
      __begin_thread(m_puiHost->get_app(), &plugin::thread_proc_ca2_logout, (LPVOID) this);
   }

   UINT c_cdecl plugin::thread_proc_ca2_login(LPVOID pvoid)
   {
      plugin * pplugin = (plugin *) pvoid;
      pplugin->ca2_login();
      return 0;
   }

   UINT c_cdecl plugin::thread_proc_ca2_logout(LPVOID pvoid)
   {
      plugin * pplugin = (plugin *) pvoid;
      pplugin->ca2_logout();
      return 0;
   }

   void plugin::ca2_login()
   {

      property_set set(get_app());

      set.parse_url_query(m_strCa2LoginRuri);

      string strLocation = set["ruri"];

      if(strLocation.is_empty())
         strLocation = m_strCa2LoginRuri;

      property_set setUri(get_app());

      setUri.parse_url_query(strLocation);

      if(System.url().get_server(strLocation).is_empty())
      {
         strLocation = System.url().override_if_empty(strLocation, get_host_location_url(), false);
      }

      string strSessId = set["sessid"];

      property_set setLogin(get_app());

      ::fontopus::user * puser = NULL;

      //Sleep(15 * 1000);

      while(puser == NULL)
      {
         puser = ::root::session().fontopus()->login(setLogin);
      }

      if(strSessId == puser->m_strFontopusServerSessId || puser->m_strFontopusServerSessId.get_length() < 16)
      {

         System.url().string_remove(strLocation, "sessid");

      }
      else
      {

         System.url().string_set(strLocation, "sessid", puser->m_strFontopusServerSessId);

      }

      System.url().string_remove(strLocation, "action");

      open_link(strLocation, "");

   }

   void plugin::ca2_logout()
   {

      ::root::session().fontopus()->logout();

      property_set set(get_app());

      set.parse_url_query(m_strCa2LogoutRuri);

      string strLocation = set["ruri"];

      strLocation = System.url().string_remove(strLocation, "sessid");

      strLocation = System.url().string_remove(strLocation, "action");

      string strUrl;

      strUrl = "https://account.ca2.cc/sec?action=logout";

      System.url().string_set(strUrl, "ruri", strLocation);

      open_link(strUrl, "");

   }


   void ms_get_dup_status_callback(void * p, int32_t i, uint_ptr dw)
   {

      if(i == -3)
      {
//         int32_t * pi = (int32_t *) p;
//         simple_http_status * ps = (simple_http_status *) dw;
  //       *pi = ps->m_dwStatusCode;
      }

   }


   void plugin::ready_on_main_thread()
   {

      if(m_bMainReady)
         return;

      keep < bool > keepMainReady(&m_bMainReady, true, false, true);

      xxdebug_box("core plugin plugin", "ready_on_main_thread", 0);

      ::count iCount = get_memory_length();

      if(iCount > 0)
      {
         m_memory.allocate(iCount + 1);

         read_memory(m_memory, iCount);

         m_memory.get_data()[iCount] = '\0';

         open_ca2_string((const char *) m_memory.get_data());
      }
      else if(m_phost->m_pbasecomposer->m_strPluginUrl.get_length() > 0)
      {

         string strPluginUrl     = System.url().override_if_empty(m_phost->m_pbasecomposer->m_strPluginUrl,get_host_location_url());

         string strExtension     = System.file().extension(System.url().get_script(strPluginUrl));

         if(strExtension.is_empty() || strExtension.compare_no_case("ca2") == 0)
         {
            // remark alarm
            // STRESS : http_get_dup
            // in core library normally System or Application.http() is used
            string strPluginData;

//            ::http::e_status estatus = ::http::status_fail;

            string strUrl = strPluginUrl;

            strUrl = System.url().string_set(strUrl, "authnone", 1);

            property_set set(get_app());

            for (int32_t iAttempt = 0; iAttempt < 3; iAttempt++)
            {

               //strPluginData = http_get_dup(strPluginUrl, false, &ms_get_dup_status_callback, (void *) &iStatusCode, false);

               Application.http().get(strUrl, strPluginData, set);

               if(::http::status_succeeded(set["get_status"]))
                  break;

            }

            if (::http::status_succeeded(set["get_status"]))
            {

               open_ca2_string(strPluginData);

            }

         }
         else
         {

            application_bias * pbiasCreate = new application_bias;
            pbiasCreate->m_puiParent = m_puiHost;
            pbiasCreate->m_set["NativeWindowFocus"] = false;
            System.get_session(0)->open_by_file_extension("\"" + strPluginUrl + "\"", pbiasCreate);

         }

      }

   }

   void plugin::open_ca2_string(const char * psz)
   {

      try
      {

         //Sleep(15 * 1000);

         LPSTR lpszAlloc = (LPSTR) (void *) psz;

         strsize iCount = strlen(psz);

         //Sleep(15 * 1000);

         string strPluginUrl;

         strPluginUrl = m_phost->m_pbasecomposer->m_strPluginUrl;

         System.url().override_if_empty(strPluginUrl, get_host_location_url());

         string strPluginScript = System.url().get_script(m_phost->m_pbasecomposer->m_strPluginUrl);


         property_set headers(get_app());

         headers.parse_http_headers(m_phost->m_pbasecomposer->m_strPluginHeaders);

         string strContentType = headers[__id(content_type)];

         string str1;

         // TODO |) : Should parse Content-type:
         // ALSO: this case only happens if all file has been downloaded before the plugin has initialized
         if(::str::ends_ci(strPluginScript, ".mp3")
         || ::str::ends_ci(strPluginScript, ".mid")
         || ::str::ends_ci(strPluginScript, ".karaoke")
         || ::str::ends_ci(strPluginScript, ".st3"))
         {
            //System.m_puiInitialPlaceHolderContainer = m_puiHost;
            application_bias * pbiasCreate = new application_bias;
            pbiasCreate->m_puiParent = m_puiHost;
            pbiasCreate->m_set["NativeWindowFocus"] = false;
            System.get_session(0)->open_by_file_extension("\"" + strPluginUrl + "\"", pbiasCreate);
         }
         else
         {
            LPSTR lpszStart = lpszAlloc;
            LPSTR lpszEnd = NULL;
            int32_t i = 0;
            for(; i < iCount; i++)
            {
               lpszEnd = &lpszStart[i];
               if(*lpszEnd == '\n')
               {
                  str1 = string(lpszStart, lpszEnd - lpszStart);
                  break;
               }
            }
            str1.trim();

            string str2;

            lpszStart = lpszEnd;
            for(; (lpszEnd - lpszAlloc) <= iCount; i++)
            {
               if(*lpszEnd == '\0' || !::str::ch::is_whitespace(lpszEnd))
                  break;
               lpszEnd = (char *) ::str::utf8_inc(lpszEnd);
            }
            lpszStart = lpszEnd;
            for(; (lpszEnd - lpszAlloc) <= iCount; i++)
            {
               if(*lpszEnd == '\0' || ::str::ch::is_space_char(lpszEnd) || (lpszEnd - lpszAlloc) == iCount)
               {
                  str2 = string(lpszStart, lpszEnd - lpszStart);
                  break;
               }
               lpszEnd = (char *) ::str::utf8_inc(lpszEnd);
            }

            string strId = str2;
            strsize iFind = strId.find("?");
            if(iFind >= 0)
            {
               strId = strId.Left(iFind);
            }
            property_set set(get_app());
            set.parse_url_query(str2);

            string strBuildNumber =  set["build_number"];

            string strLocale = set["locale"];

            string strSchema = set["schema"];

            string strRuri = set["ruri"];

            if(strBuildNumber.is_empty())
            {

               strBuildNumber = "latest";

            }

                  //Sleep(15 * 1000);
            if(str1 == "ca2login")
            {
               // graphical - 2 - user interface for login - fontopus - through the plugin
               /*if(!System.install().is(NULL, strBuildNumber, "application", "app/core/fontopus", strLocale, strSchema))
               {
/*                  System.install().start(": app=session session_start=app/core/fontopus app_type=application install");
#ifdef WINDOWS
                  ::TerminateProcess(::GetCurrentProcess(), 0);
#else
                  kill(0, SIGSTOP);
#endif
                  m_bMainReady = false;*/

/*                  string strCommandLine(": app=session session_start=app/core/fontopus app_type=application install ruri=\"" + strRuri + "\" locale=" + strLocale + " schema=" + strSchema);


#ifdef WINDOWSEX
                  PostMessage(m_phost->::small_ipc_tx_channel::m_oswindow, WM_USER + 100, 1, 1);
#else
                  throw not_implemented(get_app());
#endif
                  System.install().start(strCommandLine);

                  m_phost->m_bReload = true;

#ifdef WINDOWSEX
         //          ::TerminateProcess(::GetCurrentProcess(), 0);
#else
            //        kill(0, SIGSTOP);
#endif

                  m_bMainReady = false;



                  return;
               }*/
               m_strCa2LoginRuri = string(lpszEnd + 1, iCount - (lpszEnd - lpszStart) - 1);
               start_ca2_login();
            }
            else if(str1 == "ca2logout")
            {
               // graphical - 2 - user interface for logout - fontopus - through the plugin
               /*if(!System.install().is(NULL, strBuildNumber, "application", "app/core/fontopus", strLocale, strSchema))
               {
                  /*
                  System.install().start(": app=session session_start=app/core/fontopus app_type=application install");
#ifdef WINDOWS
                  ::TerminateProcess(::GetCurrentProcess(), 0);
#else
                  kill(0, SIGSTOP);
#endif
                  m_bMainReady = false;*/

/*                  string strCommandLine(": app=session session_start=app/core/fontopus app_type=application install ruri=\"" + strRuri + "\" locale=" + strLocale + " schema=" + strSchema);

#ifdef WINDOWSEX
                  PostMessage(m_phost->::small_ipc_tx_channel::m_oswindow, WM_USER + 100, 1, 1);
#else
                  throw not_implemented(get_app());
#endif

                  System.install().start(strCommandLine);

                  m_phost->m_bReload = true;

#ifdef WINDOWSEX
         //          ::TerminateProcess(::GetCurrentProcess(), 0);
#else
            //        kill(0, SIGSTOP);
#endif

                  m_bMainReady = false;


                  return;
               }*/
               m_strCa2LogoutRuri = string(lpszEnd + 1, iCount - (lpszEnd - lpszStart) - 1);
               start_ca2_logout();
            }
            else if(str1 == "ca2prompt")
            {
               if(System.url().get_script(get_host_location_url()) == "/non_auth")
               {
                  m_strCa2LoginRuri = System.url().set_script(get_host_location_url(), "/");
                  start_ca2_login();
               }
               else
               {
                  m_puiHost->layout();
                  if(!m_bApp)
                  {
                     while(!*m_pbReady)
                     {
                        Sleep(284);
                     }
                     if(!m_bApp)
                     {
                        printf("Session application is not initialized. Cannot start mplite.");
                        return;
                     }
                  }
                  if(str2.has_char())
                  {

                     string strType = set["app_type"];

                     if(strType.is_empty())
                        strType = "application";

                     strLocale.trim();

                     strSchema.trim();

                     if(strId.has_char() && !System.install().is(NULL, strBuildNumber, strType, strId, strLocale, strSchema))
                     {

                        string strCommandLine;

                        strCommandLine = ": app=session session_start=" + strId;

                        for(int32_t i = 0; i < set.m_propertya.get_count(); i++)
                        {

                           if(!set.m_propertya[i].get_string().has_char()
                           &&
                             (set.m_propertya[i].name() == "build_number"
                           || set.m_propertya[i].name() == "app_type"
                           || set.m_propertya[i].name() == "locale"
                           || set.m_propertya[i].name() == "schema"
                           || set.m_propertya[i].name() == "app"
                           || set.m_propertya[i].name() == "session_start"
                             )
                           )
                              continue;


                           strCommandLine += " ";

                           strCommandLine += set.m_propertya[i].name();

                           if(!set.m_propertya[i].get_string().has_char())
                              continue;

                           strCommandLine += "=";

                           strCommandLine += set.m_propertya[i].get_string();

                        }

                        if(set["app_type"].is_empty())
                           strCommandLine += " app_type=" + strType;

                        strCommandLine += " install";

                        //m_phost->starter_start(strCommandLine, get_app(), this);

                        System.install().asynch_install(strCommandLine, strBuildNumber, true);

#ifdef WINDOWSEX
                        ExitProcess(0);
#endif

                        //m_phost->m_pszReloadCommandLine = (const char *) HeapAlloc(GetProcessHeap(), 0, strCommandLine.get_length() + 1);
                        //strncpy((char *) m_phost->m_pszReloadCommandLine, strCommandLine, strCommandLine.get_length() + 1);


#ifdef WINDOWSEX
//                        PostMessage(m_phost->::small_ipc_tx_channel::m_oswindow, WM_USER + 100, 1, 1);
#else
                        throw not_implemented(get_app());
#endif

//                        System.install().start(strCommandLine);

                        //m_phost->m_bReload = true;

#ifdef WINDOWSEX
  //                      ExitProcess(0);
#else
                //        kill(0, SIGSTOP);
#endif

                        //m_bMainReady = false;

                        return;
                        //m_puiHost->SetTimer(88881115, (5000 )* 2, NULL);

                     }
                     else
                     {
                        m_puiHost->KillTimer(19841115);
                        //Sleep(15 * 1000);
   //                     System.m_puiInitialPlaceHolderContainer = m_puiHost;
                        xxdebug_box("plugin", "open_ca2_string", 0);
                        application_bias * pbiasCreate = new application_bias;
                        pbiasCreate->m_set["NativeWindowFocus"] = false;
                        pbiasCreate->m_puiParent = m_puiHost;
                        System.post_fork_uri(str2, pbiasCreate);
                     }
                  }
               }
            }
         }
      }
      catch(installing_exception &)
      {
         m_bReload = true;
/*#ifdef WINDOWS
         ::TerminateProcess(::GetCurrentProcess(), 0);
#else
         kill(0, SIGSTOP);
#endif*/
      }
   }

   void my_se_translator_function(uint32_t, struct _EXCEPTION_POINTERS* )
   {
   }

   bool plugin::finalize()
   {

      if(!m_bAppStarted)
         return true;


      g_bExiting = true;

#ifdef WINDOWS
      _set_se_translator(&my_se_translator_function);
#endif

      try
      {
         m_puiHost->DestroyWindow();
      }
      catch(...)
      {
      }


      try
      {
         get_thread()->post_to_all_threads(WM_QUIT, 0, 0);
      }
      catch(...)
      {
      }

      Sleep(1984);

      try
      {

         thread * pthread = &System;

         if(pthread->get_run())
         {
            if(m_pbReady != NULL)
            {
               *m_pbReady = false;
            }
            pthread->m_pbReady = m_pbReady;
            pthread->m_bRun = false;
            int32_t iRepeat = 0;
            while((m_pbReady != NULL || !*m_pbReady) && iRepeat < 49)
            {
               Sleep(284);
               iRepeat++;
            }
         }


      }
      catch(...)
      {
      }

      try
      {
         memory_free(m_pbReady);
      }
      catch(...)
      {
      }

      //try
      //{
      //   delete m_psystem;
      //}
      //catch(...)
      //{
      //}

#ifdef WINDOWS
/*      while(true)
      {
         try
         {
            if(!::FreeLibrary(g_hmoduleOs))
            {
               break;
            }

         }
         catch(...)
         {
         }

      }*/
#endif


      return true;

   }



#ifdef WINDOWSEX

   LRESULT plugin::message_handler(UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {

      if(m_puiHost != NULL)
      {

         if(uiMessage >= WM_MOUSEFIRST && uiMessage <= WM_MOUSELAST)
         {

            point pt = point(lparam);

            //pt.x -= m_rect.left;

            //pt.y -= m_rect.top;

            lparam = pt.lparam();

         }

         if(uiMessage == WM_MOUSEMOVE)
         {

            ::window_sp pwindow = m_puiHost->m_pimpl;

            pwindow->m_bMouseHover = true; // avoids tracking mouse leave;

         }

         ::window_sp pwindow = m_puiHost->m_pimpl;

         oswindow oswindow = pwindow->get_handle();

         bool bIsWindow = ::IsWindow(oswindow) != FALSE;

         if(bIsWindow)
         {

            smart_pointer < message::base > spbase;

            spbase = m_puiHost->get_base(m_puiHost, uiMessage, wparam, lparam);

            m_puiHost->message_handler(spbase);

            return spbase->get_lresult();

         }
         else
         {

            return 0;

         }

      }

      return 0;

   }

#elif defined(METROWIN)

   LRESULT plugin::message_handler(UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {

      return 0;

   }

#else

   int32_t plugin::message_handler(XEvent * pevent)
   {

      return 0;

   }

#endif

   bool plugin::os_native_bergedge_start()
   {

      m_bApp = true;

      set_ready();

      return true;

   }

   void plugin::set_window_rect(const RECT & rect)
   {

      SetPlacement(rect);

      if(m_puiHost != NULL)
      {

         m_puiHost->m_bRectOk = true;

         ::rect rectHost(rect);

         rectHost.offset(-rectHost.top_left());

         m_puiHost->SetPlacement(rectHost);

         rect64 rectWindow64;

         m_puiHost->GetWindowRect(rectWindow64);

         class rect rectWindow;

         rectWindow = rectWindow64;

         m_puiHost->SetWindowPos(ZORDER_TOP, rectWindow.left, rectWindow.top, rectWindow.width(), rectWindow.height(), 0);

         m_puiHost->send_message(WM_SIZE);

         m_puiHost->send_message(WM_MOVE);

         m_puiHost->layout();

      }

   }



} // namespace plugin




