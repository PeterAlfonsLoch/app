#include "StdAfx.h"

namespace veievserver
{

   socket_thread::socket_thread(::ca::application * papp)
   : thread(papp), ca(papp)
   {
      m_psocket = NULL;
      m_evCanInit.ResetEvent();
	   m_evInitialized.ResetEvent();
	   m_bInitialized = false;

   }

   socket_thread::~socket_thread(void)
   {
   }

   void socket_thread::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      IGUI_WIN_MSG_LINK(WM_APP, pinterface, this, &socket_thread::OnApp);
   }


   bool socket_thread::initialize_instance()
   {
	   //app.get_script_manager()->LoadEnv();


   /*	STARTUPINFO startupinfo;
	   memset(&startupinfo, 0, sizeof(startupinfo));
	   if(!::CreateProcess(NULL, "netnoderewrite.exe", 
		   NULL,
		   NULL,
		   TRUE,
		   0, 
		   NULL,
		   ".",
		   &startupinfo,
		   &m_pi))
	   {
		   return FALSE;
	   }

   	
	   WaitForInputIdle(m_pi.hProcess, INFINITE);


   //	m_hChildThreadId = ::OpenThread(THREAD_ALL_ACCESS, TRUE, m_pi.dwThreadId);

	   ::PostThreadMessage(m_pi.dwThreadId, WM_APP, 0, m_nThreadID);

	   PostThreadMessage(WM_APP, 0, 0);*/

   	


   /*	m_plistensocket = new netnodeListenSocket(this);
	   //Sleep(15000);
	   if(!m_plistensocket->create(80, SOCK_STREAM))
	   {
		   DWORD dw = ::GetLastError();
		   TRACE("error %u", dw);
		   return FALSE;
	   }
	   if(!m_plistensocket->Listen())
	   {
		   DWORD dw = ::GetLastError();
		   TRACE("error %u", dw);
		   return FALSE;
	   }*/
      m_evInitialized.SetEvent();
	   return true;
   }


   void socket_thread::OnApp(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj);
	   if(pbase->m_wparam == 0)
	   {
   	   ::sockets::socket_handler h(get_app());
         h.EnablePool();
         ::sockets::listen_socket<::veievserver::socket> ll(h);
         ll.m_bDetach = true;
         while(true)
         {
            if(m_iPort == 443)
            {
               ll.EnableSSL();
            }
            //Application.http().get("https://fontopus.com/ca2api/i2com/register_netshareserver?address=" + m_strIp);
	         if (ll.Bind(m_strIp, m_iPort))
	         {
               string strMessage;
               strMessage.Format("could not bind to address %s %d", m_strIp, m_iPort);
               Application.simple_message_box(NULL, strMessage);
		         return;
	         }
	         h.add(&ll);
	         while (true)
	         {
		         h.Select(8,0);
               if(m_pservice->m_stopping)
                  break;
	         }
         }
	   }
	   if(pbase->m_wparam == 0)
	   {
		   m_bInitialized = true;
		   m_evInitialized.SetEvent();
	   }
	   else if(pbase->m_wparam == 1)
	   {
		   ::PostThreadMessage(m_pi.dwThreadId, WM_APP, 1, 0);
	   }
   }



} // namespace netshareserver