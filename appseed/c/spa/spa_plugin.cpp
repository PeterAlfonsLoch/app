#include "framework.h"
#include <gdiplus.h>


#ifdef LINUX
#include "c/linux/c_os_cross_win_gdi_internal.h"
#endif


#ifdef WINDOWS
#include <process.h>
#endif

#ifdef WINDOWS

void simple_se_translator(unsigned int uiCode, EXCEPTION_POINTERS * ppointers)
{
   //throw 0;
}

#endif // defined WINDOWS


namespace spa
{

   plugin::plugin() :
      m_login(this)
   {

      m_iHealingSurface       = 0;
      m_iEdge                 = -1;
      m_bAppStarted           = false;
      m_pbReady               = NULL;
      m_dwTimeout             = (1984 + 1977) * 11;

   }


   plugin::~plugin()
   {
   }

   void plugin::on_prepare_memory()
   {
   }

   void plugin::restart()
   {

      if(!is_installing())
      {

         if((GetTickCount() - m_dwLastRestart) > (1984 + 1977) * 5)
         {

            m_dwLastRestart = GetTickCount();

            start_ca2();

         }

      }


   }


   bool plugin::is_installing()
   {

      if(m_phost->m_bInstalling)
      {

         if((::GetTickCount() - m_dwLastInstallingCheck) > 1984)
         {

            m_dwLastInstallingCheck = GetTickCount();

            try
            {

               m_phost->m_bInstalling = is_installation_lock_file_locked();

            }
            catch(...)
            {
            }

         }

      }
      else if((::GetTickCount() - m_dwLastInstallingCheck) > ((1984 + 1977) * 2))
      {

         m_dwLastInstallingCheck = GetTickCount();

         try
         {

            m_phost->m_bInstalling = is_installation_lock_file_locked();

         }
         catch(...)
         {
         }

      }

      return m_phost->m_bInstalling;

   }


   void plugin::start_ca2()
   {


      if(is_installation_lock_file_locked())
      {

         set_installing_ca2();

         if(!m_phost->m_bInstalling)
         {
            
            m_phost->m_bInstalling = true;
            
            // shouldn't do advanced operations using ca2
            // starter_start will only kick a default app-install.exe if one isn't already running, cleaning file lock if any

         }

         set_ready();

         return;

      }

      update_ca2_installed(true);

      if(is_ca2_installed())
      {


         vsstring str;

#ifdef _AMD64_
         str = itohex_dup(((int*) m_phost)[1]);
         str += itohex_dup((unsigned int) m_phost);
#else    
         str = itohex_dup((int) m_phost);
#endif

         m_phost->m_strBitmapChannel = str;

         ::hotplugin::container_launcher launcher(str);

         vsstring strChannel = "\\ca2\\ca2plugin-container-";
         strChannel += str;




         open_ab(strChannel, "plugin-container.exe", &launcher);


         if(m_phost->m_bStream)
         {
            //set_ready();
            ensure_tx(::hotplugin::message_set_ready, m_phost->m_puchMemory, m_phost->m_countMemory);
         }


         return;

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


   void plugin::run_start_install(const char * pszType, const char * pszInstall)
   {

      {

         XNode node;

         // remove install tag : should be turned into a function dependant of spalib at maximum

         if(!node.Load(file_get_contents_dup(dir::appdata("spa_install.xml"))))
            goto install;

         XNode * lpnodeInstalled = node.GetChild("installed");

         if(lpnodeInstalled == NULL)
            goto install;

         XNode * lpnodeType = lpnodeInstalled->GetChild(pszType);

         if(lpnodeType == NULL)
            goto install;

         XNode * pnode = lpnodeType->GetChildByAttr(pszType, "id", pszInstall);

         if(pnode == NULL)
            goto install;

         lpnodeType->RemoveChild(pnode);

         file_put_contents_dup(dir::appdata("spa_install.xml"), node.GetXML(NULL));

      }

install:

      m_phost->starter_start(pszInstall);


   }

   void plugin::on_paint(HDC hdcWindow, LPCRECT lprect)
   {

      if(!is_installing() && is_ca2_installed())
      {

         struct
         {


            HDC m_hdc;
            RECT m_rect;


         } paint;

         paint.m_hdc       = hdcWindow;

         paint.m_rect      = *lprect;

         if(ensure_tx(::hotplugin::message_paint, &paint, sizeof(paint)))
         {
               
            m_phost->blend_bitmap(hdcWindow, lprect);

            return;

         }

      }


      RECT rect;

      RECT rectWindow;
      get_window_rect(&rectWindow);

      int cx = rectWindow.right - rectWindow.left;
      int cy = rectWindow.bottom - rectWindow.top;

      rect.left         = 0;
      rect.top          = 0;
      rect.right        = cx;
      rect.bottom       = cy;

      //int cx = rect.right - rect.left;
      //int cy = rect.bottom - rect.top;

#ifdef WINDOWS

      HBITMAP hbmp      = ::CreateCompatibleBitmap(hdcWindow, cx, cy);
      HDC hdc           = ::CreateCompatibleDC(hdcWindow);
      HBITMAP hbmpOld   =  (HBITMAP) ::SelectObject(hdc, (HGDIOBJ) hbmp);

      ::BitBlt(hdc, 0, 0, cx, cy, hdcWindow, m_rect.left, m_rect.top, SRCCOPY);

#else

      HDC hdc = hdcWindow;

#endif

      HFONT hfontOld = NULL;
      HFONT hfont = NULL;

      if(m_login.m_bVisible)
      {
         m_login.draw(hdc);
      }
      else if(is_installing_ca2())
      {
         m_canvas.on_paint(hdc, &rect);
      }
      else if(!is_ca2_installed())
      {
         /* HPEN hpen = (HPEN) ::CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
         HPEN hpenOld = (HPEN) ::SelectObject(hdc, hpen);
         HBRUSH hbrush = (HBRUSH) ::CreateSolidBrush(RGB(255, 0, 255));
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
         const char * psz = "ca2 is not installed! You may try to install using low level spaboot_install.exe.";
         ::TextOutU_dup(hdc, 10, 10, psz, strlen_dup(psz));*/
      }
      else
      {
      }

#ifdef WINDOWS

      POINT pointViewport;
      ::SetViewportOrgEx(hdc, 0, 0, &pointViewport);
      ::BitBlt(hdcWindow   , lprect->left                , lprect->top                 , lprect->right - lprect->left, lprect->bottom - lprect->top,
             hdc         , lprect->left - m_rect.left  , lprect->top - m_rect.top    , SRCCOPY);

      /*vsstring strx = itoa_dup(lprect->left);
      vsstring stry = itoa_dup(lprect->top);
      TextOut(hdcWindow, lprect->left + 10, lprect->top + 10, strx, strx.get_length());
      TextOut(hdcWindow, lprect->left + 110, lprect->top + 10, stry, stry.get_length());
      vsstring strx2 = itoa_dup(m_rect.left);
      vsstring stry2 = itoa_dup(m_rect.top);
      TextOut(hdcWindow, lprect->left + 210, lprect->top + 10, strx2, strx2.get_length());
      TextOut(hdcWindow, lprect->left + 310, lprect->top + 10, stry2, stry2.get_length());
      */
         //hdc,       lprect->left, lprect->top, SRCCOPY);
      //::BitBlt(hdcWindow, m_rect.left, m_rect.top, cx, cy, hdc, 0, 0, SRCCOPY);
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

#endif

      on_bare_paint(hdcWindow, lprect);


   }




   



#ifdef WINDOWS

   uint_ptr plugin::message_handler(uint_ptr uiMessage, WPARAM wparam, LPARAM lparam)
   {

      if(!is_installing() && is_ca2_installed())
      {

         MSG msg;

         // only valid fields
         msg.message = uiMessage;
         msg.wParam = wparam;
         msg.lParam = lparam;

         ensure_tx(::hotplugin::message_message, &msg, sizeof(msg));

      }
      else
      {
         switch(uiMessage)
         {
         case WM_TIMER:
            {
               switch(wparam)
               {
               case 8477:
                  {
                     KillTimer(get_host_window(), 8477);
                     start_ca2();
                  }
                  break;
               }
            }
            return 0;
         default:
            {
               if((uiMessage == WM_LBUTTONUP
                  || uiMessage == WM_RBUTTONUP
                  || uiMessage == WM_MBUTTONUP) &&
                  is_installing_ca2())
               {
                  
                  m_iHealingSurface = m_canvas.increment_mode();

               }
            }
         }
      }
      return 0;
   }
#else
   int plugin::message_handler(XEvent * pevent)
   {
      /*      switch(uiMessage)
      {
      case WM_TIMER:
      {
      switch(wparam)
      {
      case 8477:
      {
      KillTimer(get_host_window(), 8477);
      start_ca2();
      }
      break;
      }
      }
      return 0;
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


   void plugin::on_paint_progress(HDC hdc, LPCRECT lprect)
   {
      set_progress_rate(extract_spa_progress_rate());
      ::hotplugin::plugin::on_paint_progress(hdc, lprect);
   }

   double plugin::extract_spa_progress_rate()
   {
      DWORD dwRead;
      HANDLE hfile = ::CreateFileA(dir::ca2("install.log"), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
      if(hfile != INVALID_HANDLE_VALUE)
      {
         int iTell = ::SetFilePointer(hfile, 0, NULL, SEEK_END);
         iTell--;
         vsstring strLine;
         int iSkip = 0;
         bool bNormal = false;
         bool bBold = false;
         bool bPreNormal = false;
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
               if(strLine == "--")
               {
                  return 0.0;
               }
               else if(strLine.begins_eat("|||"))
               {
                  return ((double) atoi_dup(strLine)) / (1000.0 * 1000.0 * 1000.0 );
               }
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
      return 0.0;
   }


   void plugin::deferred_prodevian_redraw()
   {

      ::hotplugin::plugin::deferred_prodevian_redraw();

      // this flag is only set if spaadmin is installing ca2 files while npca2 is started
      // it isn't set when npca2 is already running and spaadmin starts, may be only in the case above, when npca2 restarts.
      // this enables spaadmin to install ca2 files to ca2 folder, because npca2 would not use any ca2 shared libraries.
      if(m_phost->m_bRunningSpaAdmin)
      {
         if(!_c_lock_is_active("Global\\ca2::fontopus::ccvotagus_ca2_spa::7807e510-5579-11dd-ae16-0800200c7784"))
         {
            m_phost->m_bRunningSpaAdmin = false;
            m_phost->start_plugin();
            return;
         }
      }


      if(m_phost->is_ca2_installation_ready())
      {
         m_phost->set_ca2_installation_ready(false);
         m_phost->start_ca2();
      }

   }

   void plugin::on_receive(small_ipc_rx_channel * prxchannel, int message, void * pdata, int len)
   {

      if(prxchannel == &m_rxchannel)
      {

         if(message == ::hotplugin::message_open_url)
         {

            vsstring strUrl((const char *) pdata, len);

            open_url(strUrl);

         }

      }

   }


   void plugin::on_post(small_ipc_rx_channel * prxchannel, int a, int b)
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
                  //set_ready();
                  ensure_tx(::hotplugin::message_set_ready, m_phost->m_puchMemory, m_phost->m_countMemory);
               }

            }

         }

      }

   }

   
   void plugin::set_window_rect(LPCRECT lpcrect)
   {
    
      ::hotplugin::plugin::set_window_rect(lpcrect);

      if(!is_installing() && is_ca2_installed())
      {
      
         ensure_tx(::hotplugin::message_set_window, (void *) lpcrect, sizeof(RECT));

      }

   }


   void plugin::on_ready()
   {

      if(!m_bInstalling && is_ca2_installed())
      {

         //MessageBox(NULL, "on_ready", "on_ready", 0);
         ensure_tx(::hotplugin::message_set_ready, m_phost->m_puchMemory, m_phost->m_countMemory);

      }
      else
      {

         vsstring strPrompt((const char *) m_phost->m_puchMemory, m_phost->m_countMemory);

         vsstring strLocale;

         if(!url_query_get_param_dup(strLocale, "locale", strPrompt) || strLocale.is_empty())
            strLocale = str_get_system_default_locale_dup();

         if(strLocale.is_empty())
            strLocale = "en";

         vsstring strSchema;

         if(!url_query_get_param_dup(strSchema, "schema", strPrompt) || strSchema.is_empty())
            strSchema = str_get_system_default_schema_dup();

         if(strSchema.is_empty())
            strSchema = "en";

         m_phost->starter_start(": app=session session_start=session app_type=application install locale=" + strLocale + " schema=" + strSchema);

      }

   }

   bool plugin::calc_logged()
   {
      return false;
   }


} // namespace spa


::hotplugin::plugin * new_hotplugin()
{
   return new ::spa::plugin();
}
