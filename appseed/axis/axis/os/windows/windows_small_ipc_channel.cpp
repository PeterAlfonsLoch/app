#include "framework.h"

extern CLASS_DECL_AXIS bool (WINAPI * g_pfnChangeWindowMessageFilter)(
    _In_ UINT message,
    _In_ uint32_t dwFlag);


small_ipc_channel_base::small_ipc_channel_base()
{
   m_oswindow = NULL;
}

small_ipc_channel_base::~small_ipc_channel_base()
{
}

bool small_ipc_tx_channel::open(const char * pszKey, launcher * plauncher)
{

   if(m_oswindow != NULL)
      close();


   int32_t jCount = 23;
   int32_t iCount;

   if(plauncher != NULL)
      iCount = plauncher->m_iStart;
   else
      iCount = 2;

   m_oswindow = NULL;

   for(int32_t i = 0; i < iCount; i++)
   {
      for(int32_t j = 0; j < jCount; j++)
      {
         m_oswindow = ::FindWindow(NULL, pszKey);
         if(m_oswindow != NULL)
            break;
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


bool small_ipc_tx_channel::send(const char * pszMessage, uint32_t dwTimeout)
{

   if(!is_tx_ok())
      return false;

   COPYDATASTRUCT cds;

   cds.dwData = 0x80000000;
   cds.cbData = (uint32_t) strlen_dup(pszMessage);
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

      uint32_t dwError = ::GetLastError();

      if(dwError == ERROR_TIMEOUT)
         return false;

   }

   return true;
}

bool small_ipc_tx_channel::send(int32_t message, void * pdata, int32_t len, uint32_t dwTimeout)
{

   if(message == 0x80000000)
      return false;

   if(!is_tx_ok())
      return false;

   COPYDATASTRUCT cds;

   cds.dwData = (uint32_t) message;
   cds.cbData = (uint32_t) MAX(0, len);
   cds.lpData = (void *) pdata;

   if(dwTimeout == INFINITE)
   {

      SendMessage(m_oswindow, WM_COPYDATA, (WPARAM) 0, (LPARAM) &cds);

   }
   else
   {

      DWORD_PTR dwptr;

      if(!::SendMessageTimeout(m_oswindow, WM_COPYDATA, (WPARAM) 0, (LPARAM) &cds, SMTO_BLOCK, dwTimeout, &dwptr))
         return false;

      uint32_t dwError = ::GetLastError();

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
      uint32_t dwLastError = ::GetLastError();
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

void small_ipc_rx_channel::receiver::on_receive(small_ipc_rx_channel * prxchannel, int32_t message, void * pdata, int32_t len)
{
}

void small_ipc_rx_channel::receiver::on_post(small_ipc_rx_channel * prxchannel, int64_t a, int64_t b)
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

void * small_ipc_rx_channel::on_receive(small_ipc_rx_channel * prxchannel, int32_t message, void * pdata, int32_t len)
{

   if(m_preceiver != NULL)
   {
      m_preceiver->on_receive(prxchannel, message, pdata, len);
   }

   // ODOW - on date of writing : return ignored by this windows implementation

   return NULL;

}


void * small_ipc_rx_channel::on_post(small_ipc_rx_channel * prxchannel, int64_t a, int64_t b)
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

   int32_t iRet = 0;

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

         on_receive(this, (int32_t) pcds->dwData, pcds->lpData, pcds->cbData);

      }

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