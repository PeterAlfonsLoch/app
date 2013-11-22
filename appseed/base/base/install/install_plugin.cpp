#include "framework.h"


#undef new
#if defined(WINDOWS)
#include <gdiplus.h>
#endif


#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp)                        ((int32_t)(int16_t)LOWORD(lp))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp)                        ((int32_t)(int16_t)HIWORD(lp))
#endif


#ifdef LINUX
#include "boot/linux/ca_os_cross_win_gdi_internal.h"
#endif


#ifdef WINDOWS
#include <process.h>
#endif

#ifdef WINDOWS

void simple_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers)
{
   //throw 0;
}

#endif // defined WINDOWS


namespace install
{

   plugin::plugin(sp(base_application) papp) :
      element(papp),
      ::simple_ui::style(papp),
      ::simple_ui::interaction(papp),
      hotplugin::plugin(papp),
      m_login(papp, 49, 49),
      m_canvas(papp)

   {

      m_login.set_parent(this);

      m_pstyle = this;

      m_login.m_pcallback     = this;
      m_login.m_pstyle        = this;

      m_iHealingSurface       = 0;
      m_iEdge                 = -1;
      m_bAppStarted           = false;
      m_pbReady               = NULL;

#ifdef METROWIN

      throw "todo"; // small_ipc_channel

#else

      m_dwTimeout             = (1984 + 1977) * 11;

#endif

      m_bLogged               = false;
      m_bLogin                = false;

      m_bRestartCa2           = false;
      m_bPendingStream        = false;
      m_dwLastRestart         = 0;

      m_startca2.m_pplugin = this;

      m_startca2.begin();

   }


   plugin::~plugin()
   {
   }

   void plugin::on_prepare_memory()
   {
   }

   void plugin::restart_small_ipc_channel()
   {

      if(!is_installing())
      {

         if((get_tick_count() - m_dwLastRestart) > (1984 + 1977) * 5)
         {

            m_dwLastRestart = get_tick_count();

            start_ca2();

         }

      }


   }


   bool plugin::is_installing()
   {

      if(m_phost->m_bInstalling)
      {

         if((::get_tick_count() - m_dwLastInstallingCheck) > 1984)
         {

            m_dwLastInstallingCheck = get_tick_count();

            try
            {

               m_phost->m_bInstalling = System.install().is_lock_file_locked();

            }
            catch(...)
            {
            }

         }

      }
      else if((::get_tick_count() - m_dwLastInstallingCheck) > ((1984 + 1977) * 2))
      {

         m_dwLastInstallingCheck = get_tick_count();

         try
         {

            m_phost->m_bInstalling = System.install().is_lock_file_locked();

         }
         catch(...)
         {
         }

      }

      return m_phost->m_bInstalling;

   }



   bool plugin::thread_start_ca2_on_idle()
   {

#ifdef METROWIN

      throw "todo";

#else

      bool bJob = false;

      if(m_bRestartCa2 && m_phost != NULL)
      {

         if(is_rx_tx_ok())
         {

            m_dwLastOk = get_tick_count();

            m_bRestartCa2        = false;

            m_bPendingStream     = false;

            bJob                 = true;

         }
         else if(get_tick_count() - m_dwLastOk > ((1984 + 1977) * 2))
         {
            try
            {

               string str;

               str = hex::lower_from((int_ptr) m_phost);

               m_phost->m_strBitmapChannel = str;

               ::hotplugin::container_launcher launcher(str);

               string strChannel = "\\core\\ca2plugin-container-";

               strChannel += str;

   #ifdef WINDOWS
               open_ab(strChannel, "plugin-container.exe", &launcher);
   #else
               open_ab(strChannel, &launcher);
   #endif

            }
            catch(...)
            {

            }

            m_bRestartCa2        = false;

            m_bPendingStream     = true;

            bJob                 = true;

            m_dwLastOk           = get_tick_count();

         }

      }

      if(m_bPendingStream && m_phost != NULL)
      {

         if(m_phost->m_bStream)
         {

            try
            {

               //set_ready();

               ensure_tx(::hotplugin::message_set_plugin_url, (void *) (const char*) m_phost->m_strPluginUrl, (int32_t) m_phost->m_strPluginUrl.length());

               ensure_tx(::hotplugin::message_set_ready, m_phost->m_puchMemory, (int32_t) m_phost->m_countMemory);

            }
            catch(...)
            {

            }

            m_bPendingStream     = false;

            bJob                 = true;

         }

      }

      return bJob;

#endif

   }

   bool plugin::thread_start_ca2::on_idle()
   {

      return m_pplugin->thread_start_ca2_on_idle();

   }



   void plugin::start_ca2()
   {




      if(!m_bLogged)
      {

         xxdebug_box("plugin::start_ca2 not logged", "not logged", 0);

         m_bLogin = true;
         m_login.m_bVisible = false;
         m_bLogged = calc_logged();

         return;

      }

      if(System.install().is_lock_file_locked())
      {

         System.install().set_installing_ca2();

         if(!m_phost->m_bInstalling)
         {

            m_phost->m_bInstalling = true;

            // shouldn't do advanced operations using ca
            // starter_start will only kick a default app-install.exe if one isn't already running, cleaning file lock if any

         }

         set_ready();

         return;

      }

      System.install().update_ca2_installed(true);

      if(System.install().is_ca2_installed())
      {

         m_bRestartCa2        = true;

         m_bPendingStream     = false;

      }
      else
      {

         set_ready();

      }


   }






   bool plugin::hist(const char * pszUrl)
   {
      return open_url(pszUrl);
   }


   void plugin::run_start_install(const char * pszType, const char * pszInstall, const char * pszLocale, const char * pszSchema)
   {

      {

         ::xml::document node;

         // remove install tag : should be turned into a function dependant of spalib at maximum

         if(!node.load(file_as_string_dup(dir::appdata("install.xml"))))
            goto run_install;


#if CA2_PLATFORM_VERSION == CA2_BASIS

         ::xml::node * lpnodeVersion = node.get_child("basis");

#else

         ::xml::node * lpnodeVersion = node.get_child("stage");

#endif

         if(lpnodeVersion == NULL)
            goto run_install;

         string strBuild = System.install().get_latest_build_number(NULL);

         ::xml::node * lpnodeInstalled = node.GetChildByAttr("installed", "build", strBuild);

         if(lpnodeInstalled == NULL)
            goto run_install;

         ::xml::node * lpnodeType = lpnodeInstalled->get_child(pszType);

         if(lpnodeType == NULL)
            goto run_install;

         ::xml::node * pnode = lpnodeType->GetChildByAttr(pszType, "id", pszInstall);

         if(pnode == NULL)
            goto run_install;

         lpnodeType->remove_child(pnode);

         file_put_contents_dup(dir::appdata("install.xml"), node.get_xml(NULL));

      }

   run_install:

      m_phost->starter_start(pszInstall);


   }

   void plugin::on_paint(::draw2d::graphics * pgraphics, LPCRECT lprect)
   {

#ifdef METROWIN

      throw "todo";

#else

      if (!is_installing() && System.install().is_ca2_installed())
      {

         if(ensure_tx(::hotplugin::message_paint, (void *) lprect, sizeof(*lprect)))
         {

            m_phost->blend_bitmap(pgraphics, lprect);

            return;

         }

      }

#endif


      RECT rect;

      RECT rectWindow;
      ::hotplugin::plugin::get_window_rect(&rectWindow);

      int32_t cx = rectWindow.right - rectWindow.left;
      int32_t cy = rectWindow.bottom - rectWindow.top;

      rect.left         = 0;
      rect.top          = 0;
      rect.right        = cx;
      rect.bottom       = cy;

      //simple_bitmap b;

      pgraphics->OffsetViewportOrg(::hotplugin::plugin::m_rect.left, ::hotplugin::plugin::m_rect.top);

      //b.create(cx, cy, pgraphics);

      //simple_graphics pgraphics;

      //pgraphics->create_from_bitmap(b);

      //pgraphics->bit_blt(0, 0, cx, cy, pgraphics, ::hotplugin::plugin::m_rect.left, ::hotplugin::plugin::m_rect.top, SRCCOPY);

//      HFONT hfontOld = NULL;
//      HFONT hfont = NULL;

      if(m_bLogin)
      {
         m_login.draw(pgraphics);
      }
      else if (System.install().is_installing_ca2())
      {
         m_canvas.on_paint(pgraphics, &rect);
      }
      else if (!System.install().is_ca2_installed())
      {
         /* HPEN hpen = (HPEN) ::create_solid(1, RGB(0, 0, 0));
         HPEN hpenOld = (HPEN) ::SelectObject(hdc, hpen);
         HBRUSH hbrush = (HBRUSH) ::create_solid(RGB(255, 0, 255));
         HBRUSH hbrushOld = (HBRUSH) ::SelectObject(hdc, hbrush);

         ::Ellipse(hdc, 23, 23, 49, 49);

         ::SelectObject(hdc, (HGDIOBJ) hpenOld);
         ::SelectObject(hdc, (HGDIOBJ) hbrushOld);*/

         /*         RECT rect;
         rect.left      = 0;
         rect.top       = 0;
         rect.bottom    = cx;
         rect.right     = cy;
         ::FillSolidRect_dup(hdc, &rect, RGB(255, 255, 255));
         ::SetTextColor(hdc, RGB(255, 0, 255));
         const char * psz = "ca is not installed! You may try to install using low level spaboot_install.exe.";
         ::TextOutU_dup(hdc, 10, 10, psz, strlen_dup(psz));*/
      }
      else
      {
      }

#ifdef WINDOWS

      pgraphics->SetViewportOrg(0, 0);
      //pgraphics.bit_blt(lprect->left                , lprect->top                 , lprect->right - lprect->left, lprect->bottom - lprect->top,
        //     pgraphics         , lprect->left - ::hotplugin::plugin::m_rect.left  , lprect->top - ::hotplugin::plugin::m_rect.top    , SRCCOPY);

      /*string strx = itoa_dup(lprect->left);
      string stry = itoa_dup(lprect->top);
      TextOut(hdcWindow, lprect->left + 10, lprect->top + 10, strx, strx.get_length());
      TextOut(hdcWindow, lprect->left + 110, lprect->top + 10, stry, stry.get_length());
      string strx2 = itoa_dup(m_rect.left);
      string stry2 = itoa_dup(m_rect.top);
      TextOut(hdcWindow, lprect->left + 210, lprect->top + 10, strx2, strx2.get_length());
      TextOut(hdcWindow, lprect->left + 310, lprect->top + 10, stry2, stry2.get_length());
      */
         //hdc,       lprect->left, lprect->top, SRCCOPY);
      //::BitBlt(hdcWindow, m_rect.left, m_rect.top, cx, cy, hdc, 0, 0, SRCCOPY);

#endif

      if(!m_bLogin || !m_login.m_bVisible)
      {

         on_bare_paint(pgraphics, lprect);

      }


   }






#ifdef WINDOWS

   LRESULT plugin::message_handler(UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {

      if (!is_installing() && System.install().is_ca2_installed())
      {

         MESSAGE msg;

         memset(&msg, 0, sizeof(msg));

         // only valid fields
         msg.message    = uiMessage;
         msg.wParam     = wparam;
         msg.lParam     = lparam;

#ifdef METROWIN

         throw "todo";

#else

         ensure_tx(::hotplugin::message_message, &msg, sizeof(msg));

#endif

      }
      else
      {
         if(m_bLogin)
         {

            if(uiMessage == WM_LBUTTONDOWN)
            {
               m_login.on_lbutton_down((int16_t)GET_X_LPARAM(lparam) - ::hotplugin::plugin::m_rect.left, (int16_t)GET_Y_LPARAM(lparam) - ::hotplugin::plugin::m_rect.top);
            }
            else if(uiMessage == WM_LBUTTONUP)
            {
               m_login.on_lbutton_up((int16_t)GET_X_LPARAM(lparam) - ::hotplugin::plugin::m_rect.left, (int16_t)GET_Y_LPARAM(lparam) - ::hotplugin::plugin::m_rect.top);
            }
            else if(uiMessage == WM_MOUSEMOVE)
            {

               int32_t x = (int16_t) GET_X_LPARAM(lparam) - ::hotplugin::plugin::m_rect.left;

               int32_t y = (int16_t) GET_Y_LPARAM(lparam) - ::hotplugin::plugin::m_rect.top;

               POINT ptCursor;

               ::GetCursorPos(&ptCursor);

               m_ptCursorPhase.x = (int16_t) GET_X_LPARAM(lparam) - ptCursor.x;

               m_ptCursorPhase.y = (int16_t) GET_Y_LPARAM(lparam) - ptCursor.y;

               m_login.on_mouse_move(x, y);

            }
            else if(uiMessage == WM_KEYDOWN)
            {
               if(wparam == VK_SHIFT)
               {
                  m_bPluginShiftKey = true;
               }
            }
            else if(uiMessage == WM_KEYUP)
            {


#ifdef METROWIN

               throw "todo";


#else

               string str;
               wchar_t wsz[32];

               BYTE baState[256];

               ZERO(baState);
               for(int i = 0; i < 256; i++)
               {
   //               baState[i] = (BYTE) GetAsyncKeyState(i);
               }

               baState[wparam & 0xff] = 0x80;

/*               if((GetAsyncKeyState(::user::key_shift) & 0x80000000) != 0)
               {
                  baState[::user::key_shift] |= 0x80;
               }
*/
               if(m_bPluginShiftKey)
               {
                  baState[VK_SHIFT] |= 0x80;
               }

               int32_t iRet = ToUnicodeEx((UINT) wparam, 0, baState, wsz, 32, 0, GetKeyboardLayout(GetCurrentThreadId()));
               str = wsz;
               m_login.on_char(static_cast<UINT>(wparam), str);
               if(m_bPluginShiftKey && wparam == VK_SHIFT)
               {
                  m_bPluginShiftKey = false;
               }

#endif

            }

         }
         else if((uiMessage == WM_LBUTTONUP
            || uiMessage == WM_RBUTTONUP
            || uiMessage == WM_MBUTTONUP) &&
            System.install().is_installing_ca2())
         {

            m_iHealingSurface = m_canvas.increment_mode();

         }
      }
      return 0;
   }
#else
   int32_t plugin::message_handler(XEvent * pevent)
   {
      /*      switch(uiMessage)
      {
      default:
      {
      if((uiMessage == WM_LBUTTONUP
      || uiMessage == WM_RBUTTONUP
      || uiMessage == WM_MBUTTONUP) &&
      is_installing_ca2())
      {
      m_iHealingSurface++;
      }
      }
      }*/
      return 0;
   }
#endif

   bool plugin::initialize()
   {
      start_ca2();
      return true;
   }


   void plugin::on_paint_progress(::draw2d::graphics * pgraphics, LPCRECT lprect)
   {
      set_progress_rate(extract_spa_progress_rate());
      ::hotplugin::plugin::on_paint_progress(pgraphics, lprect);
   }

   double plugin::extract_spa_progress_rate()
   {

      DWORD dwRead;

      HANDLE hfile = ::create_file(dir::element("install.log"), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

      double dRate = 0.0;

      bool bRate = false;

      bool bStatus = false;

      if(hfile != INVALID_HANDLE_VALUE)
      {

         int32_t iTell = ::SetFilePointer(hfile, 0, NULL, SEEK_END);
         iTell--;
         string strLine;
         int32_t iSkip = 0;
         bool bNormal = false;
         bool bBold = false;
//         bool bPreNormal = false;
         bool bStart = false;
         char ch;
         while(iTell >= 0 && !bStart && !(bNormal && bBold))
         {
            if(iTell > 0)
            {
               ::SetFilePointer(hfile, iTell, NULL, SEEK_SET);
               if(!ReadFile(hfile, &ch,  1, &dwRead, NULL))
                  break;
               if(dwRead <= 0)
                  break;
            }

            if(iTell > 0 && ch == '\r')
            {
               iSkip++;
            }
            else if(iTell > 0 && ch == '\n')
            {
               iSkip++;
            }
            else if(iTell <= 0 || iSkip > 0)
            {
               iSkip = 0;
               strLine.trim();
               if(::str::begins_eat(strLine, "get application name"))
               {
                  m_strStatus = "";
                  return 0.0;
               }
               else if(!bRate && ::str::begins_eat(strLine, "|||"))
               {
                  bRate = true;
                  dRate = ((double) atoi_dup(strLine)) / (1000.0 * 1000.0 * 1000.0 );
               }
               else if(!bStatus && ::str::begins_eat(strLine, ":::::"))
               {
                  bStatus = true;
                  m_strStatus = strLine;
               }

               if(bRate && bStatus)
                  break;

               strLine = ch;
            }
            else
            {
               strLine = ch + strLine;
            }
            iTell--;
         }
         ::CloseHandle(hfile);
      }
      return dRate;
   }


   void plugin::deferred_prodevian_redraw()
   {

      ::hotplugin::plugin::deferred_prodevian_redraw();

      // this flag is only set if spaadmin is installing ca files while npca2 is started
      // it isn't set when npca2 is already running and spaadmin starts, may be only in the case above, when npca2 restarts.
      // this enables spaadmin to install ca files to ca folder, because npca2 would not use any ca shared libraries.
      if(m_phost->m_bRunningSpaAdmin)
      {
         throw todo(get_app());
         /*if(!_c_lock_is_active("Global\\::ca::fontopus::ca2_spa::7807e510-5579-11dd-ae16-0800200c7784"))
         {
            m_phost->m_bRunningSpaAdmin = false;
            m_phost->start_plugin();
            return;
         }*/
      }


      if(m_phost->is_ca2_installation_ready())
      {
         m_phost->set_ca2_installation_ready(false);
         m_phost->start_ca2();
      }

   }

#ifndef METROWIN


   void plugin::on_receive(small_ipc_rx_channel * prxchannel, int32_t message, void * pdata, int32_t len)
   {

      if(prxchannel == &m_rxchannel)
      {

         if(message == ::hotplugin::message_open_url)
         {

            string strUrl((const char *) pdata, len);

            open_url(strUrl);

         }

      }

   }


   void plugin::on_post(small_ipc_rx_channel * prxchannel, int64_t a, int64_t b)
   {

      if(prxchannel == &m_rxchannel)
      {

         if(a == 1)
         {

            m_phost->m_bInstalling = b != FALSE;

         }
         else if(a == 3)
         {

            if(b == 1)
            {

               if(m_phost->m_bStream)
               {

                  m_bRestartCa2        = true;

                  m_bPendingStream     = false;

               }

            }

         }

      }

   }

#endif

   void plugin::set_window_rect(LPCRECT lpcrect)
   {

      ::hotplugin::plugin::set_window_rect(lpcrect);

      if (!is_installing() && System.install().is_ca2_installed())
      {

#ifdef METROWIN

         throw "todo";

#else

         ensure_tx(::hotplugin::message_set_window, (void *) lpcrect, sizeof(RECT));

#endif

      }

   }


   void plugin::on_ready()
   {

      if (!m_bInstalling && System.install().is_ca2_installed())
      {

         xxdebug_box("on_ready", "on_ready", 0);

         m_bRestartCa2     = true;

         m_bPendingStream  = false;

      }
      else
      {

         string strPrompt;

         if(m_phost->m_puchMemory != NULL)
         {

            strPrompt = string((const char *) m_phost->m_puchMemory, m_phost->m_countMemory);

         }
         else
         {

            int32_t iTry = 0;

            retry_get_prompt:

            strPrompt = Application.http().get(m_phost->m_strPluginUrl);

            if(strPrompt.is_empty())
            {

               if(iTry < 9)
               {

                  Sleep(iTry * 84);

                  iTry++;

                  goto retry_get_prompt;

               }

            }

         }

         string strLocale;

         throw todo(get_app());
//         if(strPrompt.is_empty() || !url_query_get_param_dup(strLocale, "locale", strPrompt) || strLocale.is_empty())
         //          strLocale = str_get_system_default_locale_dup();

         if(strLocale.is_empty())
            strLocale = "en";

         string strSchema;

         throw todo(get_app());
//         if (strPrompt.is_empty() || !url_query_get_param_dup(strSchema, "schema", strPrompt) || strSchema.is_empty())
  //          strSchema = str_get_system_default_schema_dup();

         if(strSchema.is_empty())
            strSchema = "en";

         m_phost->starter_start(": app=session session_start=session app_type=application install locale=" + strLocale + " schema=" + strSchema);

      }

   }

   bool plugin::calc_logged()
   {

      m_login.initialize();

      m_login.start_login();

      return m_bLogged;

   }

   void plugin::login_result(::fontopus::login::e_result eresult)
   {

      if(eresult == ::fontopus::login::result_ok)
      {

         m_bLogged   = true;
         m_bLogin    = false;

         start_ca2();

      }
      else
      {

         m_login.defer_translate(this);

         m_bLogin    = true;
         set_focus(&m_login.m_editUser);
         m_login.m_editUser.m_strText = "";
         m_login.m_password.m_strText = "";
         m_login.m_bVisible = true;

      }


   }

   string plugin::defer_get_plugin()
   {

      string str;

      int32_t iAttemptStream = 0;
      int32_t iAttemptUrl = 0;
      int32_t iAttempt = 0;

restart:

      while(!m_phost->m_bStream)
      {
         iAttemptStream++;
         if(iAttemptStream > 49)
            return "";
         Sleep(iAttemptStream * 84);
      }

      while(m_phost->m_strPluginUrl.is_empty())
      {
         if(!m_phost->m_bStream)
         {
            iAttemptStream = 0;
            goto restart;
         }
         iAttemptUrl++;
         if(iAttemptUrl > 49)
            return "";
         Sleep(iAttemptUrl * 84);
      }

      while((str = Application.http().get(m_phost->m_strPluginUrl)).is_empty())
      {
         if(!m_phost->m_bStream)
         {
            iAttemptStream = 0;
            goto restart;
         }
         iAttempt++;
         if(iAttempt > 7)
            return "";
         Sleep(iAttempt * 840);
      }

      return str;

   }




} // namespace install


::hotplugin::plugin * new_hotplugin(sp(base_application) papp)
{
   return new ::install::plugin(papp);
}


