#include "StdAfx.h"
#include "win/Kerr/ThreadPool.h"
#include <ShlObj.h>
#include <math.h>


HHOOK g_mousehookLL;
HHOOK g_keyboardhookLL;
winservice_1_thread * g_pservice;


winservice_1_thread::winservice_1_thread(::ca::application * papp) :
   ::ca::ca(papp),
   ::thread(papp),
   simple_thread(papp)
{
   m_hwndWinactionarea  = NULL;
   m_hwndCommand        = NULL;
   m_hwndWinutil        = NULL;
   m_hwndWindesk        = NULL;
}

winservice_1_thread::~winservice_1_thread()
{
}

int winservice_1_thread::Run()
{
   
   m_strWinactionarea = Application.dir().module("winactionareaapp.exe");
   m_id = Application.dir().module("commandapp.link");
   m_strWinutil = Application.dir().module("winutilapp.link");

   ensure_apps();

   win_hook();

	while (m_bRun)
	{
		AfxPumpMessage();
	}

   win_unhook();
	
   m_stopped.Signal();

   return 0;
}





string winservice_1_thread::stage()
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


bool winservice_1_thread::win_hook()
{
   g_pservice = this;
   if((g_mousehookLL =
      SetWindowsHookEx(
      WH_MOUSE_LL,
      LowLevelMouseProc,
      AfxGetInstanceHandle(),
      NULL)) == NULL)
   {
      DWORD dw = ::GetLastError();
      string strFormat;
      strFormat.Format("winservice_1_thread::win_hook mouse hook failed %d", dw);
      Application.log().print(strFormat);
      return false;
   }
   if((g_keyboardhookLL =
      SetWindowsHookEx(
      WH_KEYBOARD_LL,
      LowLevelKeyboardProc,
      AfxGetInstanceHandle(),
      NULL)) == NULL)
   {
      DWORD dw = ::GetLastError();
      string strFormat;
      strFormat.Format("winservice_1_thread::win_hook keyboard hook failed %d", dw);
      Application.log().print(strFormat);
      return false;
   }
   return true;
}


void winservice_1_thread::LowLevelMouseMessage(          int nCode,
    WPARAM wparam,
    LPARAM lparam
)
{
   if(wparam == WM_MOUSEMOVE)
   {
      HWND hwndDesktop = ::GetDesktopWindow();
      rect rectDesktop;
      ::GetWindowRect(hwndDesktop, rectDesktop);
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
         if(::IsWindow(m_hwndWinactionarea))
            PostMessage(m_hwndWinactionarea, WM_APP + 2000, 0, 1);
         if(::IsWindow(m_hwndCommand))
            PostMessage(m_hwndCommand, WM_APP + 2000, 0, 1);
      }
      else if(m_bTimerOn && r > 69.0) 
      {
         m_bTimerOn = false;
         ensure_apps();
         if(::IsWindow(m_hwndWinactionarea))
            PostMessage(m_hwndWinactionarea, WM_APP + 2000, 0, 0);
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
               base_wnd * pwnd = base_wnd::from_handle(hwnd);
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
}

LRESULT CALLBACK winservice_1_thread::LowLevelMouseProc(          int nCode,
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

LRESULT CALLBACK winservice_1_thread::LowLevelKeyboardProc(int nCode, WPARAM wparam, LPARAM lparam)
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

bool winservice_1_thread::LowLevelKeyboardMessage(int nCode, WPARAM wparam, LPARAM lparam)
{
   UINT uiMessage = wparam;
   LPKBDLLHOOKSTRUCT pstruct = (LPKBDLLHOOKSTRUCT) lparam;
   bool bControlKeyDown = GetAsyncKeyState (VK_CONTROL) >> ((sizeof(SHORT) * 8) - 1);
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




bool winservice_1_thread::win_unhook()
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


void winservice_1_thread::ensure_apps()
{
   if(::IsWindow(m_hwndWindesk) &&
      ::IsWindow(m_hwndWinutil) &&
      ::IsWindow(m_hwndWinactionarea) &&
      ::IsWindow(m_hwndCommand))
      return;
   EnumWindows(GetAppsEnumWindowsProc, (LPARAM) this);
   if(!::IsWindow(m_hwndWindesk))
   {
      Application.assert_running_local("windesk");
   }
   if(!::IsWindow(m_hwndWinutil))
   {
      Application.assert_running_local("winutil");
   }
   if(!::IsWindow(m_hwndWinactionarea))
   {
      Application.assert_running_local("winactionarea");
   }
   if(!::IsWindow(m_hwndCommand))
   {
      Application.assert_running_local("command");
   }
}


BOOL CALLBACK winservice_1_thread::GetAppsEnumWindowsProc(      
    HWND hwnd,
    LPARAM lParam)
{
   winservice_1_thread * pview = (winservice_1_thread *) lParam;
   DWORD dwThreadId;
   DWORD dwProcessId;
   HICON hicon16;
   HICON hicon48;
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




