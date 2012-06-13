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

   cds.dwData = 0xffffffffu;
   cds.cbData = (DWORD) strlen_dup(pszMessage);
   cds.lpData = (void *) pszMessage;

   SendMessage(m_hwnd, WM_COPYDATA, (WPARAM) NULL, (LPARAM) &cds);

   return true;
}


bool small_ipc_tx_channel::send(int message, void * pdata, int len)
{

   if(message == 0xffffffff)
      return false;

   COPYDATASTRUCT cds;

   cds.dwData = (DWORD) message;
   cds.cbData = (DWORD) max(0, len);
   cds.lpData = (void *) pdata;

   SendMessage(m_hwnd, WM_COPYDATA, (WPARAM) NULL, (LPARAM) &cds);

   return true;
}


small_ipc_rx_channel::small_ipc_rx_channel()
{
   m_preceiver    = NULL;
   m_bWait        = false;
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

   SetTimer(m_hwnd, 198477, 84, NULL);

   SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (long_ptr) this);

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

void small_ipc_rx_channel::receiver::on_receive(int message, void * pdata, int len)
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

void * small_ipc_rx_channel::on_receive(int message, void * pdata, int len)
{

   if(m_preceiver != NULL)
   {
      m_preceiver->on_receive(message, pdata, len);
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
      if(pcds->dwData == 0xffffffffu)
      {
         vsstring strMessage((const char *)pcds->lpData, pcds->cbData);
         on_receive(strMessage);
         if(m_bWait && m_iWait == -1)
         {
            m_bWait = false;
         }
      }
      else 
      {
         on_receive((int)pcds->dwData, pcds->lpData, pcds->cbData);
         if(m_bWait && m_iWait == (int)pcds->dwData)
         {
            m_bWait = false;
         }
      }
   }
   else
   {
      return ::DefWindowProcA(m_hwnd, message, wparam, lparam);
   }
   return 0;
}



void small_ipc_rx_channel::prepare_wait()
{
   
   prepare_wait(-1);

}

bool small_ipc_rx_channel::wait(DWORD dwTimeout)
{
   
   return wait(-1, dwTimeout);

}

void small_ipc_rx_channel::prepare_wait(int message)
{

   m_bWait = true;
   m_iWait = message;

}

bool small_ipc_rx_channel::wait(int message, DWORD dwTimeout)
{
	

   MSG msg;

   DWORD dwStart = ::GetTickCount();

   while(m_bWait)
	{
      GetMessage(&msg, NULL, 0, 0xffffffffu);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
      if(::GetTickCount() - dwStart > dwTimeout)
      {
         return false;
      }
	}

   return true;

}

