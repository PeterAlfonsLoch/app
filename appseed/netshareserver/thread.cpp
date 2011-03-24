#include "StdAfx.h"
#include "thread.h"
#include "socket_thread.h"
#include "socket.h"

namespace netshareserver
{

    // BEGIN_MESSAGE_MAP(thread, ::thread)
	//{{AFX_MSG_MAP(MessageWindow)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
//	ON_THREAD_MESSAGE(WM_APP, OnApp)
 // END_MESSAGE_MAP()


thread * KickNetShareServer(netshareserver_service * papp)
{
	thread * pthread = AfxBeginThread < thread > (papp->get_app());	
   pthread->set_app(papp->get_app());
   pthread->m_pservice = papp;
   return pthread;
}

thread::thread(::ca::application * papp) :
   ::ca::ca(papp),
   ::thread(papp),
   m_loginthread(papp)
{
	m_evInitialized.ResetEvent();
	m_bInitialized = false;

	m_plistensocket = NULL;
}

thread::~thread(void)
{
}

void thread::_001InstallMessageHandling(igui::win::message::Dispatch * pinterface)
{
   IGUI_WIN_MSG_LINK(WM_APP, pinterface, this, &thread::OnApp);
}


bool thread::initialize_instance()
{
   AfxSocketInit();
		int iCount = 2;
	int i;
	for(int i = 0; i < iCount; i++)
	{
		socket_thread * pthread = AfxBeginThread < socket_thread >(get_app());
      pthread->m_pthread = this;
      pthread->m_evCanInit.SetEvent();
		m_ptrathread.add(pthread);
	}
	int iCount2 = iCount - 1;
	for(i = 0; i < iCount2; i++)
	{
		m_ptrathread[i]->m_pnext = m_ptrathread[i + 1];
	}
	m_ptrathread[i]->m_pnext = m_ptrathread[0];

	m_pthreadCurrent = m_ptrathread[0];

	PostThreadMessage(WM_APP, 122, 0);


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

	
	//PostThreadMessage(WM_APP, 0, 0);


/*	m_plistensocket = new listen_socket(this);
	//Sleep(15000);
	if(!m_plistensocket->Create(80, SOCK_STREAM))
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
	return true;
}


void thread::OnApp(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::base, pbase, pobj);
	if(pbase->m_wparam == 122)
	{
		m_plistensocket = new listen_socket(this);
		//Sleep(15000);
      string strServer;
      int iServer;
      AStrArray straServer;
      straServer = straServer = Application.db().data_load("netshareserver", System.idEmpty, System.idEmpty);

      if(straServer.get_size() > 0)
      {
         strServer = straServer[0];
      }
      else
      {
         strServer = "0.0.0.0";
      }
      iServer = 80;
		if(!m_plistensocket->Create(iServer, SOCK_STREAM, FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE,
         strServer))
		{
			DWORD dw = ::GetLastError();
			TRACE("error %u", dw);
         string strError;
         strError.Format("Could not connect to %s:%d");
         Application.simple_message_box(strError);
			AfxGetApp()->PostThreadMessage(WM_APP, 3, 0);
			return;
		}
      register_server(strServer);
		if(!m_plistensocket->Listen())
		{
			DWORD dw = ::GetLastError();
			TRACE("error %u", dw);
			AfxGetApp()->PostThreadMessage(WM_APP, 3, 1);
			return;
		}
	}
	else if(pbase->m_wparam == 1)
	{
		listen_socket * plistensocket = (listen_socket *) pbase->m_lparam;
		socket * psocket = new socket(plistensocket);
		//CSingleLock sl(&m_cssocket);

      if(plistensocket->m_ptrasocket.get_size() == 0)
      {
         string str;
         LPVOID pvParam = (LPVOID) (LPCTSTR) str.GetBufferSetLength(4096);
         SystemParametersInfo(SPI_GETDESKWALLPAPER, 0, pvParam, 0);
         str.ReleaseBuffer();
         Application.data_set("Global", "DESKWALLPAPER", str);
         str.Empty();
         SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, pvParam, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
      }

		plistensocket->Accept(*psocket);
      plistensocket->m_ptrasocket.add(psocket);
	}
	if(pbase->m_wparam == 122)
	{
		m_bInitialized = true;
		m_evInitialized.SetEvent();
	}
	else if(pbase->m_wparam == 1)
	{
		::PostThreadMessage(m_pi.dwThreadId, WM_APP, 1, 0);
	}
	else if(pbase->m_wparam == 2)
	{
		m_pnext->PostThreadMessageA(WM_APP, 1, 0);
	}
   else if(pbase->m_wparam == 543218)
   {
      //for(int i = 0; i < m_plistensocket->m_ptrasocket.get_size(); i++)
      //{
//         m_plistensocket->m_ptrasocket[i]->send_snapshot();
      //}
      //m_evSent.SetEvent();
   }
/*   else if(wparam == 3)
   {
	   netnodeApp * papp = dynamic_cast < netnodeApp * > (AfxGetApp());
      papp->edgify_app(0, &typeid(bergedgeApp));
   }*/
}

BOOL thread::PreTranslateMessage(LPMSG lpmsg)
{
   if(lpmsg->message == (WM_APP + 1234) && lpmsg->hwnd == NULL)
   {
   }
   return ::thread::PreTranslateMessage(lpmsg);
}

void thread::register_server(const char * pszServer)
{
   string strUrl;
   strUrl = "https://fontopus.com/ca2api/register_netshareserver?debug&explain&address=";
   strUrl += pszServer;
   string strPath(strUrl);
   ca39::user * puser = ApplicationUser;
   if(puser != NULL && puser->m_strSessid.GetLength() > 0)
   {
      if(strPath.find("?") >= 0)
      {
         strPath += "&";
         strPath += puser->m_strSessid;
      }
      else
      {
         strPath += "?";
         strPath += puser->m_strSessid;
      }
   }
   string str;
   Application.sync_load_url(str, strPath, 
      puser, puser->m_phttpcookies);
   
}

void thread::on_login_thread_response(int iAuth, char const * pszResponse)
{
}

} // namespace netshareserver