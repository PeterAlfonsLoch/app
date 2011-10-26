#include "StdAfx.h"
#include <ShlObj.h>
#include <math.h>


namespace winservice_1
{

   HHOOK g_mousehookLL;
   HHOOK g_keyboardhookLL;
   thread * g_pservice;


   thread::thread(::ca::application * papp) :
      ca(papp),
      ::radix::thread(papp),
      simple_thread(papp),
      m_window(papp)
   {
      m_window.m_pthread   = this;
      m_hwndWinactionarea  = NULL;
      m_hwndCommand        = NULL;
      m_hwndWinutil        = NULL;
      m_hwndWindesk        = NULL;
      m_hwndBergedge1      = NULL;
      m_hwndBergedge2      = NULL;
      m_hwndBergedge3      = NULL;
      m_hwndBergedge4      = NULL;
      m_hwndWhiteboard     = NULL;
      m_bEnsureApps        = true;
   }

   thread::~thread()
   {
   }

   int thread::run()
   {
      if(!m_window.create())
      {
         throw "could not create message ::ca::window";
      }
      m_strWinactionarea = System.dir().module("winactionareaapp.exe");
      m_id = System.dir().module("commandapp.link");
      m_strWinutil = System.dir().module("winutilapp.link");

      ensure_apps();

      win_hook();

	   while (get_run())
	   {
		   pump_message();
	   }

      win_unhook();
   	
      return 0;
   }





   string thread::stage()
   {
      char path[MAX_PATH * 4];
      if(!SHGetSpecialFolderPath(
         NULL,
         path,
         CSIDL_PROGRAM_FILES | CSIDL_FLAG_CREATE,
         1))
         return "";
      else 
         return path;
   }


   bool thread::win_hook()
   {
      g_pservice = this;
      if((g_mousehookLL =
         SetWindowsHookEx(
         WH_MOUSE_LL,
         LowLevelMouseProc,
         Application.m_hInstance,
         NULL)) == NULL)
      {
         DWORD dw = ::GetLastError();
         string strFormat;
         strFormat.Format("thread::win_hook mouse hook failed %d", dw);
         System.log().print(strFormat);
         return false;
      }
      if((g_keyboardhookLL =
         SetWindowsHookEx(
         WH_KEYBOARD_LL,
         LowLevelKeyboardProc,
         Application.m_hInstance,
         NULL)) == NULL)
      {
         DWORD dw = ::GetLastError();
         string strFormat;
         strFormat.Format("thread::win_hook keyboard hook failed %d", dw);
         System.log().print(strFormat);
         return false;
      }
      return true;
   }


   void thread::LowLevelMouseMessage(          int nCode,
       WPARAM wparam,
       LPARAM lparam
   )
   {
      UNREFERENCED_PARAMETER(nCode);
      if(wparam == WM_MOUSEMOVE)
      {
         rect rectDesktop;
         Application.get_screen_rect(rectDesktop);
         MSLLHOOKSTRUCT * pstruct = (MSLLHOOKSTRUCT *) lparam;
         double r = pow(pow(pstruct->pt.x, 2.0) + pow(rectDesktop.bottom - pstruct->pt.y, 2.0), 0.5);
         if(!m_bTimerOn && r < 23.0)
         {
            m_bTimerOn = true;
            ensure_apps();
            if(::IsWindow(m_hwndWindesk))
               PostMessage(m_hwndWindesk, WM_APP + 2000, 0, 1);
            if(::IsWindow(m_hwndWinutil))
               PostMessage(m_hwndWinutil, WM_APP + 2000, 0, 1);
            if(::IsWindow(m_hwndCommand))
               PostMessage(m_hwndCommand, WM_APP + 2000, 0, 1);
         }
         else if(m_bTimerOn && r > 69.0) 
         {
            m_bTimerOn = false;
            ensure_apps();
            if(::IsWindow(m_hwndWinutil))
               PostMessage(m_hwndWinutil, WM_APP + 2000, 0, 0);
            if(::IsWindow(m_hwndCommand))
               PostMessage(m_hwndCommand, WM_APP + 2000, 0, 0);
         }
      }
      else if(wparam == WM_LBUTTONUP)
      {
   /*      if(m_bAutoHideOnOutClick)
         {
            PMSLLHOOKSTRUCT pmouse = (PMSLLHOOKSTRUCT) lparam;
            point pt = pmouse->pt;
            HWND hwnd = ::WindowFromPoint(pt);
            HWND hwndNew = NULL;
            bool bHide = true;
            while(hwnd != NULL)
            {
               if(hwnd == GetSafeHwnd())
               {
                  bHide = false;
               }
               hwndNew = ::GetParent(hwnd);
               if(hwndNew == NULL)
               {
                  ::ca::window * pwnd = ::ca::window::from_handle(hwnd);
                  if(pwnd != NULL)
                  {
                     hwndNew = pwnd->GetOwner()->GetSafeHwnd();
                  }
               }
               hwnd = hwndNew;
            }
            if(bHide)
            {
               SetTimer(1001, 200, NULL);
            }
         }*/
      }
      if(wparam == WM_MOUSEMOVE)
      {
         MSLLHOOKSTRUCT * pstruct = (MSLLHOOKSTRUCT *) lparam;
         double r = get_winactionarea_radius(pstruct->pt);
         if(!m_bInsideWinactionareaHotspot && r < 23.0)
         {
            m_bInsideWinactionareaHotspot = true;
            bool bLControlKeyDown = (GetAsyncKeyState (VK_LCONTROL) >> ((sizeof(SHORT) * 8) - 1)) != FALSE;
            bool bLAltKeyDown = (GetAsyncKeyState (VK_LMENU) >> ((sizeof(SHORT) * 8) - 1)) != FALSE;
            if(!bLControlKeyDown && !bLAltKeyDown)
            {
               ::PostMessage(m_hwndWinactionarea, WM_APP + 2000, 0, 1);
            }
            else
           { 
               ::PostMessage(m_hwndWinactionarea, WM_APP + 2000, 0, 0);
            }
         }
         else if(m_bInsideWinactionareaHotspot && r > 69.0)
         {
            m_bInsideWinactionareaHotspot = false;
         }
      }
   }

   LRESULT CALLBACK thread::LowLevelMouseProc(          int nCode,
       WPARAM wparam,
       LPARAM lparam
   )
   {
      if(nCode >= 0)
      {
         if(nCode == HC_ACTION)
         {
            g_pservice->LowLevelMouseMessage(nCode, wparam, lparam);
         }
      }
      return CallNextHookEx(g_mousehookLL, nCode, wparam, lparam);
   }

   LRESULT CALLBACK thread::LowLevelKeyboardProc(int nCode, WPARAM wparam, LPARAM lparam)
   {
      if(nCode >= 0)
      {
         if(nCode == HC_ACTION)
         {
            g_pservice->LowLevelKeyboardMessage(nCode, wparam, lparam);
         }
      }
      return CallNextHookEx(g_keyboardhookLL, nCode, wparam, lparam);
   }

   bool thread::LowLevelKeyboardMessage(int nCode, WPARAM wparam, LPARAM lparam)
   {
      UNREFERENCED_PARAMETER(nCode);
      UINT uiMessage = wparam;
      LPKBDLLHOOKSTRUCT pstruct = (LPKBDLLHOOKSTRUCT) lparam;
//      bool bControlKeyDown = (GetAsyncKeyState (VK_CONTROL) >> ((sizeof(SHORT) * 8) - 1)) != FALSE;
      if(uiMessage == WM_KEYUP 
      && pstruct->vkCode == VK_LWIN)
      {
         /*ensure_apps();
         if(::IsWindow(m_hwndWinactionarea))
            PostMessage(m_hwndWinactionarea, WM_APP + 2000, 0, 0);
         if(::IsWindow(m_hwndCommand))
            PostMessage(m_hwndCommand, WM_APP + 2000, 0, 0);
         return true;*/
      }
      return false;
   }




   bool thread::win_unhook()
   {
      if(g_keyboardhookLL != NULL)
      {
         UnhookWindowsHookEx(g_keyboardhookLL);
      }
      if(g_mousehookLL != NULL)
      {
         UnhookWindowsHookEx(g_mousehookLL);
      }
      return true;
   }


   void thread::ensure_apps()
   {
      if(!m_bEnsureApps)
         return;
      if(::IsWindow(m_hwndWindesk) &&
         ::IsWindow(m_hwndWinutil) &&
         ::IsWindow(m_hwndWinactionarea) &&
         ::IsWindow(m_hwndBergedge1) &&
         ::IsWindow(m_hwndBergedge2) &&
         ::IsWindow(m_hwndBergedge3) &&
         ::IsWindow(m_hwndBergedge4) &&
         ::IsWindow(m_hwndCommand) &&
         ::IsWindow(m_hwndWhiteboard))
         return;
//      m_hwndWinservice1       =  ::FindWindow(NULL, "ca2::fontopus::message_wnd::winservice_1");
      m_hwndWinactionarea     =  ::FindWindow(NULL, "ca2::fontopus::message_wnd::winactionarea");
      m_hwndCommand           =  ::FindWindow(NULL, "ca2::fontopus::message_wnd::command");
      m_hwndWinutil           =  ::FindWindow(NULL, "ca2::fontopus::message_wnd::winutil");
      m_hwndWindesk           =  ::FindWindow(NULL, "ca2::fontopus::message_wnd::windesk");
      m_hwndBergedge1         =  ::FindWindow(NULL, "ca2::fontopus::message_wnd::bergedge::bergedge1");
      m_hwndBergedge2         =  ::FindWindow(NULL, "ca2::fontopus::message_wnd::bergedge::bergedge2");
      m_hwndBergedge3         =  ::FindWindow(NULL, "ca2::fontopus::message_wnd::bergedge::bergedge3");
      m_hwndBergedge4         =  ::FindWindow(NULL, "ca2::fontopus::message_wnd::bergedge::bergedge4");
      m_hwndWhiteboard        =  ::FindWindow(NULL, "ca2::fontopus::message_wnd::whiteboard");
      //EnumWindows(GetAppsEnumWindowsProc, (LPARAM) this);
      if(!::IsWindow(m_hwndWindesk))
      {
         System.assert_running_local("windesk");
      }
      if(!::IsWindow(m_hwndWinutil))
      {
         System.assert_running_local("winutil");
      }
      if(!::IsWindow(m_hwndWinactionarea))
      {
         System.assert_running_local("winactionarea");
      }
      if(!::IsWindow(m_hwndCommand))
      {
         System.assert_running_local("command");
      }
      if(!::IsWindow(m_hwndBergedge1))
      {
         System.assert_running_local("bergedge", "bergedge1");
      }
      if(!::IsWindow(m_hwndBergedge2))
      {
         System.assert_running_local("bergedge", "bergedge2");
      }
      if(!::IsWindow(m_hwndBergedge3))
      {
         System.assert_running_local("bergedge", "bergedge3");
      }
      if(!::IsWindow(m_hwndBergedge4))
      {
         System.assert_running_local("bergedge", "bergedge4");
      }
      if(!::IsWindow(m_hwndWhiteboard))
      {
         System.assert_running_local("whiteboard");
      }
   }


   BOOL CALLBACK thread::GetAppsEnumWindowsProc(      
       HWND hwnd,
       LPARAM lParam)
   {
      thread * pview = (thread *) lParam;
//      DWORD dwThreadId;
//      DWORD dwProcessId;
//      HICON hicon16;
//      HICON hicon48;
      DWORD dwptr;
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 1, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 2)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 2, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 4)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 4, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 5)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 5, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 8)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 8, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 11)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 11, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 23)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 23, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 33)
      {
         return TRUE;
      }
      if(::SendMessageTimeout(hwnd, WM_APP + 2000, 33, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr))
      {
         if(dwptr == 1)
         {
            pview->m_hwndCommand = hwnd;
         }
         else if(dwptr == 67)
         {
            pview->m_hwndWinactionarea = hwnd;
         }
         else if(dwptr == 68)
         {
            pview->m_hwndWinutil = hwnd;
         }
         else if(dwptr == 69)
         {
            pview->m_hwndWindesk = hwnd;
         }
      }
      return TRUE;
   }

   double thread::get_winactionarea_radius(point pt)
   {
      return pow(pow(m_ptWinactionareaHotspot.x - pt.x, 2.0) + pow(m_ptWinactionareaHotspot.y - pt.y, 2.0), 0.5);
   }

   void thread::_001OnApp2000(gen::signal_object * pobj)
   {
      SCAST_PTR(user::win::message::base, pbase, pobj);
      if(pbase->m_wparam == 2000)
      {
         m_ptWinactionareaHotspot = point(pbase->m_lparam);
      }
      else if(pbase->m_wparam == 3)
      {
         if(pbase->m_lparam == 6)
         {
            m_bEnsureApps = false;
            set_run(false);
            Application.PostThreadMessage(WM_QUIT, 0, 0);
         }
      }
      pbase->set_lresult(0);
   }

} // namespace winservice_1
