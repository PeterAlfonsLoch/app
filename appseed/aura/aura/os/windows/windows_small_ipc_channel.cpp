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


extern LPFN_ChangeWindowMessageFilter g_pfnChangeWindowMessageFilter;

small_ipc_channel_base::small_ipc_channel_base()
{

   m_oswindow = NULL;

}


small_ipc_channel_base::~small_ipc_channel_base()
{

   if(m_oswindow != NULL)
   {

      ::DestroyWindow(m_oswindow);

      m_oswindow = NULL;

   }

}


bool small_ipc_tx_channel::open(const char * pszKey, launcher * plauncher)
{

   if(m_oswindow != NULL)
      close();


   int jCount = 23;
   int iCount;

   if(plauncher != NULL)
      iCount = plauncher->m_iStart + 1;
   else
      iCount = 2;

   m_oswindow = NULL;

   for(int i = 0; i < iCount; i++)
   {
      for(int j = 0; j < jCount; j++)
      {
         m_oswindow = ::FindWindow(NULL, pszKey);
         if(m_oswindow != NULL)
            break;
//         m_oswindow = FindDesktopWindow(pszKey);
  //       if(m_oswindow != NULL)
    //        break;
         if(i <= 0)
         {
            break;
         }
         Sleep(1000);
      }
      if(m_oswindow != NULL)
         break;
      if(plauncher != NULL)
      {
         if (plauncher->m_iStart <= 0)
            return false;
         plauncher->start();
         plauncher->m_iStart--;
      }
   }
   m_strKey = pszKey;
   return true;

}

bool small_ipc_tx_channel::close()
{

   if(m_oswindow == NULL)
      return true;

   m_oswindow = NULL;

   m_strKey = "";

   return true;

}


bool small_ipc_tx_channel::send(const char * pszMessage, unsigned int dwTimeout)
{

   if(!is_tx_ok())
      return false;

   COPYDATASTRUCT cds;

   cds.dwData = 0x80000000;
   cds.cbData = (unsigned int) strlen(pszMessage);
   cds.lpData = (void *) pszMessage;

   if(dwTimeout == INFINITE)
   {

      SendMessage(m_oswindow, WM_COPYDATA, (WPARAM) 0, (LPARAM) &cds);

   }
   else
   {

      DWORD_PTR dwptr;

      if(!::SendMessageTimeout(m_oswindow, WM_COPYDATA, (WPARAM) 0, (LPARAM) &cds, SMTO_BLOCK, dwTimeout, &dwptr))
         return false;

      unsigned int dwError = ::GetLastError();

      if(dwError == ERROR_TIMEOUT)
         return false;

   }

   return true;
}

bool small_ipc_tx_channel::send(int message, void * pdata, int len, unsigned int dwTimeout)
{

   if(message == 0x80000000)
      return false;

   if(!is_tx_ok())
      return false;

   COPYDATASTRUCT cds;

   cds.dwData = (unsigned int) message;
   cds.cbData = (unsigned int) MAX(0, len);
   cds.lpData = (void *) pdata;

   if(dwTimeout == INFINITE)
   {

      if(message >= WM_APP)
      {

         SendMessage(m_oswindow,message, 0, 0);

      }
      else
      {

         SendMessage(m_oswindow,WM_COPYDATA,(WPARAM)0,(LPARAM)&cds);

      }

   }
   else
   {

      DWORD_PTR dwptr;

      if(!::SendMessageTimeout(m_oswindow, WM_COPYDATA, (WPARAM) 0, (LPARAM) &cds, SMTO_BLOCK, dwTimeout, &dwptr))
         return false;

      unsigned int dwError = ::GetLastError();

      if(dwError == ERROR_TIMEOUT)
         return false;

   }

   return true;

}



bool small_ipc_tx_channel::is_tx_ok()
{
   
   return ::IsWindow(m_oswindow) != FALSE;

}




small_ipc_rx_channel::small_ipc_rx_channel()
{

   m_preceiver    = NULL;

}


small_ipc_rx_channel::~small_ipc_rx_channel()
{

}


bool small_ipc_rx_channel::create(const char * pszKey, const char * pszWindowProcModule)
{


   if(g_pfnChangeWindowMessageFilter != NULL)
   {
      g_pfnChangeWindowMessageFilter(WM_COPYDATA, MSGFLT_ADD);
   }

   HINSTANCE hinstance = ::GetModuleHandleA(pszWindowProcModule);

   ATOM atom = register_class(hinstance);

   m_oswindow = ::CreateWindowExA(0, "small_ipc_rx_channel_message_queue_class", pszKey, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, hinstance, NULL);
   
   if(m_oswindow == NULL)
   {
      unsigned int dwLastError = ::GetLastError();
      return false;
   }

   SetTimer(m_oswindow, 888888, 84, NULL);

   SetWindowLongPtr(m_oswindow, GWLP_USERDATA, (LONG_PTR) this);

   m_strWindowProcModule = pszWindowProcModule;

   
   
   return true;
}


bool small_ipc_rx_channel::destroy()
{

   if(m_oswindow != NULL)
   {
      ::DestroyWindow(m_oswindow);
      m_oswindow = NULL;
   }

   return true;

}

void small_ipc_rx_channel::receiver::on_receive(small_ipc_rx_channel * prxchannel, const char * pszMessage)
{
}

void small_ipc_rx_channel::receiver::on_receive(small_ipc_rx_channel * prxchannel, int message, void * pdata, int len)
{
}

void small_ipc_rx_channel::receiver::on_post(small_ipc_rx_channel * prxchannel, long long int a, long long int b)
{
}

void * small_ipc_rx_channel::on_receive(small_ipc_rx_channel * prxchannel, const char * pszMessage)
{

   if(m_preceiver != NULL)
   {
      m_preceiver->on_receive(prxchannel, pszMessage);
   }

   // ODOW - on date of writing : return ignored by this windows implementation

   return NULL;

}

void * small_ipc_rx_channel::on_receive(small_ipc_rx_channel * prxchannel, int message, void * pdata, int len)
{

   if(m_preceiver != NULL)
   {
      m_preceiver->on_receive(prxchannel, message, pdata, len);
   }

   // ODOW - on date of writing : return ignored by this windows implementation

   return NULL;

}


void * small_ipc_rx_channel::on_post(small_ipc_rx_channel * prxchannel, long long int a, long long int b)
{

   if(m_preceiver != NULL)
   {
      m_preceiver->on_post(prxchannel, a, b);
   }

   // ODOW - on date of writing : return ignored by this windows implementation

   return NULL;

}


LRESULT CALLBACK small_ipc_rx_channel::s_message_queue_proc(oswindow oswindow, UINT message, WPARAM wparam, LPARAM lparam)
{

   int iRet = 0;

   small_ipc_rx_channel * pchannel = (small_ipc_rx_channel *) GetWindowLongPtr(oswindow, GWLP_USERDATA);

   if(pchannel == NULL)
   {

      return ::DefWindowProcA(oswindow, message, wparam, lparam);

   }
   else
   {

      return pchannel->message_queue_proc(message, wparam, lparam);

   }

}



ATOM small_ipc_rx_channel::register_class(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			   = 0;
	wcex.lpfnWndProc	   = &small_ipc_rx_channel::s_message_queue_proc;
	wcex.cbClsExtra	   = 0;
	wcex.cbWndExtra	   = 0;
	wcex.hInstance		   = hInstance;
	wcex.hIcon			   = NULL;
	//wcex.hCursor		   = LoadCursor(NULL, IDC_ARROW);
   wcex.hCursor		   = NULL;
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
   wcex.lpszMenuName	   = NULL;
	wcex.lpszClassName	= "small_ipc_rx_channel_message_queue_class";
	wcex.hIconSm		   = NULL;

	return RegisterClassEx(&wcex);
}


LRESULT small_ipc_rx_channel::message_queue_proc(UINT message, WPARAM wparam, LPARAM lparam)
{
   
   if(message == WM_USER + 100)
   {
      
      on_post(this, wparam, lparam);

   }
   else if(message == WM_COPYDATA)
   {

      COPYDATASTRUCT * pcds = (COPYDATASTRUCT *) lparam;

      if(pcds == NULL)
      {

         return 0;

      }
      else if(pcds->dwData == 0x80000000)
      {

         string strMessage((const char *)pcds->lpData, pcds->cbData);

         on_receive(this, strMessage.c_str());

      }
      else 
      {

         on_receive(this, (int) pcds->dwData, pcds->lpData, pcds->cbData);

      }

   }
   else if(message >= WM_APP)
   {

      on_receive(this,message,(void *) wparam,lparam);

   }
   else
   {

      return ::DefWindowProcA(m_oswindow, message, wparam, lparam);

   }

   return 0;

}



bool small_ipc_rx_channel::on_idle()
{

   return false;

}

bool small_ipc_rx_channel::is_rx_ok()
{

   return ::IsWindow(m_oswindow) != FALSE;

}


bool small_ipc_channel::open_ab(const char * pszKey, const char * pszModule, launcher * plauncher)
{

   m_vssChannel = pszKey;

   m_rxchannel.m_preceiver = this;

   string strChannelRx = m_vssChannel + "-a";
   string strChannelTx = m_vssChannel + "-b";

   if(!::IsWindow(m_rxchannel.m_oswindow))
   {

      if(!m_rxchannel.create(strChannelRx.c_str(),pszModule))
      {

         return false;

      }

   }

   if(!small_ipc_tx_channel::open(strChannelTx.c_str(),plauncher))
   {
      return false;
   }

   return true;

}

bool small_ipc_channel::open_ba(const char * pszKey, const char * pszModule, launcher * plauncher)
{

   m_vssChannel = pszKey;

   m_rxchannel.m_preceiver = this;

   string strChannelRx = m_vssChannel + "-b";
   string strChannelTx = m_vssChannel + "-a";


   if(!::IsWindow(m_rxchannel.m_oswindow))
   {

      if(!m_rxchannel.create(strChannelRx.c_str(),pszModule))
      {

         return false;

      }

   }

   if(!small_ipc_tx_channel::open(strChannelTx.c_str(),plauncher))
   {
      return false;
   }

   return true;

}


bool small_ipc_channel::is_rx_tx_ok()
{

   return m_rxchannel.is_rx_ok() && is_tx_ok();

}