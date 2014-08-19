#include "framework.h"

#ifndef METROWIN

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


bool small_ipc_tx_channel::send(const char * pszMessage, DWORD dwTimeout)
{

   if(!is_tx_ok())
      return false;

   COPYDATASTRUCT cds;

   cds.dwData = 0x80000000;
   cds.cbData = (DWORD) strlen_dup(pszMessage);
   cds.lpData = (void *) pszMessage;

   if(dwTimeout == INFINITE)
   {

      SendMessage(m_hwnd, WM_COPYDATA, (WPARAM) NULL, (LPARAM) &cds);

   }
   else
   {

      DWORD_PTR dwptr;

      if(!::SendMessageTimeout(m_hwnd, WM_COPYDATA, (WPARAM) NULL, (LPARAM) &cds, SMTO_BLOCK, dwTimeout, &dwptr))
         return false;

      DWORD dwError = ::GetLastError();

      if(dwError == ERROR_TIMEOUT)
         return false;

   }

   return true;
}


bool small_ipc_tx_channel::is_tx_ok()
{
   
   return ::IsWindow(m_hwnd) != FALSE;

}


bool small_ipc_tx_channel::send(int message, void * pdata, int len, DWORD dwTimeout)
{

   if(message == 0x80000000)
      return false;

   if(!is_tx_ok())
      return false;

   COPYDATASTRUCT cds;

   cds.dwData = (DWORD) message;
   cds.cbData = (DWORD) MAX(0, len);
   cds.lpData = (void *) pdata;

   if(dwTimeout == INFINITE)
   {

      SendMessage(m_hwnd, WM_COPYDATA, (WPARAM) NULL, (LPARAM) &cds);

   }
   else
   {

      DWORD_PTR dwptr;

      if(!::SendMessageTimeout(m_hwnd, WM_COPYDATA, (WPARAM) NULL, (LPARAM) &cds, SMTO_BLOCK, dwTimeout, &dwptr))
         return false;

      DWORD dwError = ::GetLastError();

      if(dwError == ERROR_TIMEOUT)
         return false;

   }

   return true;

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

   m_hwnd = ::CreateWindowExA(0, "small_ipc_rx_channel_message_queue_class", pszKey, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, hinstance, NULL);
   
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

void small_ipc_rx_channel::receiver::on_receive(small_ipc_rx_channel * prxchannel, const char * pszMessage)
{
}

void small_ipc_rx_channel::receiver::on_receive(small_ipc_rx_channel * prxchannel, int message, void * pdata, int len)
{
}

void small_ipc_rx_channel::receiver::on_post(small_ipc_rx_channel * prxchannel, int a, int b)
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


void * small_ipc_rx_channel::on_post(small_ipc_rx_channel * prxchannel, int a, int b)
{

   if(m_preceiver != NULL)
   {
      m_preceiver->on_post(prxchannel, a, b);
   }

   // ODOW - on date of writing : return ignored by this windows implementation

   return NULL;

}


LRESULT CALLBACK small_ipc_rx_channel::s_message_queue_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{

   int iRet = 0;

   small_ipc_rx_channel * pchannel = (small_ipc_rx_channel *) GetWindowLongPtr(hwnd, GWLP_USERDATA);

   if(pchannel == NULL)
   {

      return ::DefWindowProcA(hwnd, message, wparam, lparam);

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
	wcex.hCursor		   = LoadCursor(NULL, IDC_ARROW);
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

      if(pcds->dwData == 0x80000000)
      {

         string strMessage((const char *)pcds->lpData, pcds->cbData);

         on_receive(this, strMessage);

      }
      else 
      {

         on_receive(this, (int) pcds->dwData, pcds->lpData, pcds->cbData);

      }

   }
   else
   {

      return ::DefWindowProcA(m_hwnd, message, wparam, lparam);

   }

   return 0;

}



bool small_ipc_rx_channel::on_idle()
{

   return false;

}

bool small_ipc_rx_channel::is_rx_ok()
{

   return ::IsWindow(m_hwnd) != FALSE;

}


bool small_ipc_channel::open_ab(const char * pszKey, const char * pszModule, launcher * plauncher)
{

   m_vssChannel = pszKey;

   m_rxchannel.m_preceiver = this;

   string strChannelRx = m_vssChannel + "-a";
   string strChannelTx = m_vssChannel + "-b";


   if(!m_rxchannel.create(strChannelRx, pszModule))
   {
      return false;
   }

   if(!small_ipc_tx_channel::open(strChannelTx, plauncher))
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


   if(!m_rxchannel.create(strChannelRx, pszModule))
   {
      return false;
   }

   if(!small_ipc_tx_channel::open(strChannelTx, plauncher))
   {
      return false;
   }

   return true;

}


bool small_ipc_channel::is_rx_tx_ok()
{

   return m_rxchannel.is_rx_ok() && is_tx_ok();

}


#endif
