#include "framework.h"

extern bool (WINAPI * g_pfnChangeWindowMessageFilter)(
    _In_ UINT message,
    _In_ DWORD dwFlag);


small_ipc_channel_base::small_ipc_channel_base()
{
   m_hwnd = NULL;
}

small_ipc_channel_base::~small_ipc_channel_base()
{
}

bool small_ipc_tx_channel::open(const char * pszKey, launcher * plauncher)
{

   if(m_hwnd != NULL)
      close();


   int jCount = 23;
   int iCount;

   if(plauncher != NULL)
      iCount = 11;
   else
      iCount = 2;

   m_hwnd = NULL;

   for(int i = 0; i < iCount; i++)
   {
      for(int j = 0; j < jCount; j++)
      {
         m_hwnd = ::FindWindow(NULL, pszKey);
         if(m_hwnd != NULL)
            break;
         if(i <= 0)
         {
            break;
         }
         Sleep(884);
      }
      if(m_hwnd != NULL)
         break;
      if(plauncher != NULL)
      {
         plauncher->start();
      }
   }
   m_strKey = pszKey;
   return true;

}

bool small_ipc_tx_channel::close()
{

   if(m_hwnd == NULL)
      return true;

   m_hwnd = NULL;

   m_strKey = "";

   return true;

}


bool small_ipc_tx_channel::send(const char * pszMessage)
{

   COPYDATASTRUCT cds;

   cds.dwData = 15111984;
   cds.cbData = (DWORD) strlen_dup(pszMessage);
   cds.lpData = (void *) pszMessage;

   SendMessage(m_hwnd, WM_COPYDATA, (WPARAM) NULL, (LPARAM) &cds);

   return true;
}


small_ipc_rx_channel::small_ipc_rx_channel()
{
   m_preceiver = NULL;
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

   m_hwnd = ::CreateWindowExA(0, "small_ipc_rx_channel_message_window_class", pszKey, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, hinstance, NULL);
   
   if(m_hwnd == NULL)
   {
      DWORD dwLastError = ::GetLastError();
      return false;
   }

   SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR) this);

   m_strWindowProcModule = pszWindowProcModule;

   
   
   return true;
}


bool small_ipc_rx_channel::destroy()
{

   if(m_hwnd != NULL)
   {
      ::DestroyWindow(m_hwnd);
      m_hwnd = NULL;
   }

   return true;

}

void small_ipc_rx_channel::receiver::on_receive(const char * pszMessage)
{
}

void * small_ipc_rx_channel::on_receive(const char * pszMessage)
{

   if(m_preceiver != NULL)
   {
      m_preceiver->on_receive(pszMessage);
   }

   // ODOW - on date of writing : return ignored by this windows implementation
   return NULL;

}



LRESULT CALLBACK small_ipc_rx_channel::s_message_window_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
   int iRet = 0;
   small_ipc_rx_channel * pchannel = (small_ipc_rx_channel *) GetWindowLongPtr(hwnd, GWLP_USERDATA);
   if(pchannel == NULL)
   {
      return ::DefWindowProcA(hwnd, message, wparam, lparam);
   }
   else
   {
      return pchannel->message_window_proc(message, wparam, lparam);
   }
}



ATOM small_ipc_rx_channel::register_class(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			   = 0;
	wcex.lpfnWndProc	   = &small_ipc_rx_channel::s_message_window_proc;
	wcex.cbClsExtra	   = 0;
	wcex.cbWndExtra	   = 0;
	wcex.hInstance		   = hInstance;
	wcex.hIcon			   = NULL;
	wcex.hCursor		   = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
   wcex.lpszMenuName	   = NULL;
	wcex.lpszClassName	= "small_ipc_rx_channel_message_window_class";
	wcex.hIconSm		   = NULL;

	return RegisterClassEx(&wcex);
}


LRESULT small_ipc_rx_channel::message_window_proc(UINT message, WPARAM wparam, LPARAM lparam)
{
   if(message == WM_COPYDATA)
   {
      COPYDATASTRUCT * pcds = (COPYDATASTRUCT *) lparam;
      if(pcds->dwData == 15111984)
      {
         vsstring strMessage((const char *)pcds->lpData, pcds->cbData);
         on_receive(strMessage);
      }
      else
      {
         ::DefWindowProcA(m_hwnd, message, wparam, lparam);
      }
   }
   else
   {
      ::DefWindowProcA(m_hwnd, message, wparam, lparam);
   }
   return 0;
}
