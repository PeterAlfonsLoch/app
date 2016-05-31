//#include "framework.h"

typedef int
(WINAPI * LPFN_ChangeWindowMessageFilter)(
 UINT message,
 DWORD dwFlag);

/*bool GetWindowText(string & str, HWND hwnd)
{

   DWORD_PTR lresult = 0;

   if(!::SendMessageTimeoutW(hwnd,WM_GETTEXTLENGTH,0,0,SMTO_ABORTIFHUNG,84,&lresult))
      return false;

   wstring wstr;

   if(!::SendMessageTimeoutW(hwnd,WM_GETTEXT,(LPARAM)wstr.alloc(lresult + 1),lresult + 1,SMTO_ABORTIFHUNG,84,&lresult))
      return false;

   str = wstr;

   return true;

}


HWND FindDesktopWindow(const string & strWindowName);
HWND FindDesktopWindow(const string & strDesktopName,const string & strFindWindow);

struct find_desktop_window
{
   HWND m_hwnd;
   string m_strFindWindow;
};

BOOL CALLBACK FindDesktopWindow_EnumWindowsProc(
   _In_ HWND   hwnd,
   _In_ LPARAM lParam
   )
{
   find_desktop_window * pfind = (find_desktop_window *)(lParam);
   string str;
   if(!GetWindowText(str,hwnd))
   {
      return TRUE;
   }
   if(pfind->m_strFindWindow == str)
   {
      pfind->m_hwnd = hwnd;
      return FALSE;
   }
   return TRUE;
}




HWND FindDesktopWindow(const string & strDesktopName,const string & strFindWindow)
{
   //Open desktop handle to switch to.
   HDESK hDesktopToSwitch = OpenDesktop(strDesktopName,DF_ALLOWOTHERACCOUNTHOOK,TRUE,GENERIC_ALL);
   if(NULL == hDesktopToSwitch)
   {

      return NULL;
   }

   find_desktop_window find;
   find.m_hwnd = NULL;
   find.m_strFindWindow= strFindWindow;

   //Switch the desktop.
   if(FALSE == ::EnumDesktopWindows(hDesktopToSwitch,FindDesktopWindow_EnumWindowsProc,(LPARAM) &find))
   {
      //         CloseDesktop(hDesktopToSwitch);
      //       return NULL;
   }

   CloseDesktop(hDesktopToSwitch);

   return find.m_hwnd;

}

BOOL CALLBACK FindDesktopWindow_EnumDesktopProc(LPTSTR lstrDesktopName,LPARAM lParam);

HWND FindDesktopWindow(const string & strWindowName)
{
 
   HWINSTA hWindowsStation = GetProcessWindowStation();
   if(NULL == hWindowsStation)
      throw false;

   find_desktop_window find;

   find.m_hwnd = NULL;
   find.m_strFindWindow = strWindowName;

   EnumDesktops(hWindowsStation,&::FindDesktopWindow_EnumDesktopProc,reinterpret_cast <LPARAM> (&find));

   return find.m_hwnd;

}



//Function enumerates all the desktops of the windows station.
BOOL CALLBACK FindDesktopWindow_EnumDesktopProc(LPTSTR lstrDesktopName,LPARAM lParam)
{

   find_desktop_window * pfind = (find_desktop_window *)(lParam);

   try
   {
      //Adding Desktop Name To DesktopName List.
      pfind->m_hwnd = FindDesktopWindow(lstrDesktopName, pfind->m_strFindWindow);
      if(pfind->m_hwnd != NULL)
      {
         return FALSE;
      }
   }
   catch(...)
   {
   }

   return TRUE;
}*/


