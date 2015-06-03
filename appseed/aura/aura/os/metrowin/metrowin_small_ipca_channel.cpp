//#include "framework.h"
//#include "metrowin.h"
#ifndef METROWIN

namespace aura
{

   
   namespace ipc
   {


      extern bool (WINAPI * g_pfnChangeWindowMessageFilter)(
         _In_ UINT message,
         _In_ DWORD dwFlag);


      base::base()
      {
         m_hwnd = NULL;
      }

      base::~base()
      {
      }

      bool tx::open(const char * pszChannel,launcher * plauncher)
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
               m_hwnd = ::FindWindow(NULL,pszChannel);
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
         m_strBaseChannel = pszChannel;
         return true;

      }

      bool tx::close()
      {

         if(m_hwnd == NULL)
            return true;

         m_hwnd = NULL;

         m_strBaseChannel = "";

         return true;

      }


      bool tx::send(const char * pszMessage,DWORD dwTimeout)
      {

         if(!is_tx_ok())
            return false;

         COPYDATASTRUCT cds;

         cds.dwData = 0x80000000;
         cds.cbData = (DWORD)strlen_dup(pszMessage);
         cds.lpData = (void *)pszMessage;

         if(dwTimeout == INFINITE)
         {

            SendMessage(m_hwnd,WM_COPYDATA,(WPARAM)NULL,(LPARAM)&cds);

         }
         else
         {

            DWORD_PTR dwptr;

            if(!::SendMessageTimeout(m_hwnd,WM_COPYDATA,(WPARAM)NULL,(LPARAM)&cds,SMTO_BLOCK,dwTimeout,&dwptr))
               return false;

            DWORD dwError = ::GetLastError();

            if(dwError == ERROR_TIMEOUT)
               return false;

         }

         return true;
      }


      bool tx::is_tx_ok()
      {

         return ::IsWindow(m_hwnd) != FALSE;

      }


      bool tx::send(int message,void * pdata,int len,DWORD dwTimeout)
      {

         if(message == 0x80000000)
            return false;

         if(!is_tx_ok())
            return false;

         COPYDATASTRUCT cds;

         cds.dwData = (DWORD)message;
         cds.cbData = (DWORD)max(0,len);
         cds.lpData = (void *)pdata;

         if(dwTimeout == INFINITE)
         {

            SendMessage(m_hwnd,WM_COPYDATA,(WPARAM)NULL,(LPARAM)&cds);

         }
         else
         {

            DWORD_PTR dwptr;

            if(!::SendMessageTimeout(m_hwnd,WM_COPYDATA,(WPARAM)NULL,(LPARAM)&cds,SMTO_BLOCK,dwTimeout,&dwptr))
               return false;

            DWORD dwError = ::GetLastError();

            if(dwError == ERROR_TIMEOUT)
               return false;

         }

         return true;

      }


      rx::rx()
      {

         m_preceiver    = NULL;

      }


      rx::~rx()
      {

      }


      bool rx::create(const char * pszChannel,const char * pszWindowProcModule)
      {


         if(g_pfnChangeWindowMessageFilter != NULL)
         {
            g_pfnChangeWindowMessageFilter(WM_COPYDATA,MSGFLT_ADD);
         }

         HINSTANCE hinstance = ::GetModuleHandleA(pszWindowProcModule);

         ATOM atom = register_class(hinstance);

         m_hwnd = ::CreateWindowExA(0,"small_ipc_rx_channel_message_queue_class",pszChannel,0,0,0,0,0,HWND_MESSAGE,NULL,hinstance,NULL);

         if(m_hwnd == NULL)
         {
            DWORD dwLastError = ::GetLastError();
            return false;
         }

         SetTimer(m_hwnd,198477,84,NULL);

         SetWindowLongPtr(m_hwnd,GWLP_USERDATA,(long_ptr) this);

         m_strWindowProcModule = pszWindowProcModule;



         return true;
      }


      bool rx::destroy()
      {

         if(m_hwnd != NULL)
         {
            ::DestroyWindow(m_hwnd);
            m_hwnd = NULL;
         }

         return true;

      }

      void rx::receiver::on_receive(rx * prx,const char * pszMessage)
      {
      }

      void rx::receiver::on_receive(rx * prx,int message,void * pdata,int len)
      {
      }

      void rx::receiver::on_post(rx * prx,int a,int b)
      {
      }

      void * rx::on_receive(rx * prx,const char * pszMessage)
      {

         if(m_preceiver != NULL)
         {
            m_preceiver->on_receive(prx,pszMessage);
         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return NULL;

      }

      void * rx::on_receive(rx * prx,int message,void * pdata,int len)
      {

         if(m_preceiver != NULL)
         {
            m_preceiver->on_receive(prx,message,pdata,len);
         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return NULL;

      }


      void * rx::on_post(rx * prx,int a,int b)
      {

         if(m_preceiver != NULL)
         {
            m_preceiver->on_post(prx,a,b);
         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return NULL;

      }


      LRESULT CALLBACK rx::s_message_queue_proc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam)
      {

         int iRet = 0;

         rx * pchannel = (rx *)GetWindowLongPtr(hwnd,GWLP_USERDATA);

         if(pchannel == NULL)
         {

            return ::DefWindowProcA(hwnd,message,wparam,lparam);

         }
         else
         {

            return pchannel->message_queue_proc(message,wparam,lparam);

         }

      }



      ATOM rx::register_class(HINSTANCE hInstance)
      {
         WNDCLASSEX wcex;

         wcex.cbSize = sizeof(WNDCLASSEX);

         wcex.style			   = 0;
         wcex.lpfnWndProc	   = &rx::s_message_queue_proc;
         wcex.cbClsExtra	   = 0;
         wcex.cbWndExtra	   = 0;
         wcex.hInstance		   = hInstance;
         wcex.hIcon			   = NULL;
         wcex.hCursor		   = LoadCursor(NULL,IDC_ARROW);
         wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
         wcex.lpszMenuName	   = NULL;
         wcex.lpszClassName	= "small_ipc_rx_channel_message_queue_class";
         wcex.hIconSm		   = NULL;

         return RegisterClassEx(&wcex);
      }


      LRESULT rx::message_queue_proc(UINT message,WPARAM wparam,LPARAM lparam)
      {

         if(message == WM_USER + 100)
         {

            on_post(this,wparam,lparam);

         }
         else if(message == WM_COPYDATA)
         {

            COPYDATASTRUCT * pcds = (COPYDATASTRUCT *)lparam;

            if(pcds->dwData == 0x80000000)
            {

               string strMessage((const char *)pcds->lpData,pcds->cbData);

               on_receive(this,strMessage);

            }
            else
            {

               on_receive(this,(int)pcds->dwData,pcds->lpData,pcds->cbData);

            }

         }
         else
         {

            return ::DefWindowProcA(m_hwnd,message,wparam,lparam);

         }

         return 0;

      }



      bool rx::on_idle()
      {

         return false;

      }

      bool rx::is_rx_ok()
      {

         return ::IsWindow(m_hwnd) != FALSE;

      }


      bool ipc::open_ab(const char * pszChannel,const char * pszModule,launcher * plauncher)
      {

         m_strChannel = pszChannel;

         m_rx.m_preceiver = this;

         string strChannelRx = m_strChannel + "-a";
         string strChannelTx = m_strChannel + "-b";


         if(!m_rx.create(strChannelRx,pszModule))
         {
            return false;
         }

         if(!tx::open(strChannelTx,plauncher))
         {
            return false;
         }

         return true;

      }

      bool ipc::open_ba(const char * pszChannel,const char * pszModule,launcher * plauncher)
      {

         m_strChannel = pszChannel;

         m_rx.m_preceiver = this;

         string strChannelRx = m_strChannel + "-b";
         string strChannelTx = m_strChannel + "-a";


         if(!m_rx.create(strChannelRx,pszModule))
         {
            return false;
         }

         if(!tx::open(strChannelTx,plauncher))
         {
            return false;
         }

         return true;

      }


      bool ipc::is_rx_tx_ok()
      {

         return m_rx.is_rx_ok() && is_tx_ok();

      }


   } // namespace ipc


} // namespace aura



#endif
