#include "StdAfx.h"
#include "netnodeThread.h"
#include "netnodeSocketThread.h"
#include "netnodeSocket.h"


BEGIN_MESSAGE_MAP(netnodeThread, thread)
	//{{AFX_MSG_MAP(MessageWindow)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_THREAD_MESSAGE(WM_APP, OnApp)
END_MESSAGE_MAP()


netnodeThread * KickNetNode(netnodeApp * papp)
{
	netnodeThread * pthread = AfxBeginThread < netnodeThread > (papp);	
   pthread->set_app(papp);
   return pthread;
}

netnodeThread::netnodeThread(::ca::application * papp)
: thread(papp), ::ca::ca(papp)
{
	m_evInitialized.ResetEvent();
	m_bInitialized = false;

	m_plistensocket = NULL;
}

netnodeThread::~netnodeThread(void)
{
}


bool netnodeThread::InitInstance()
{
   AfxSocketInit();
		int iCount = 2;
	int i;
	for(int i = 0; i < iCount; i++)
	{
		netnodeSocketThread * pthread = AfxBeginThread < netnodeSocketThread > (get_app());
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


/*	m_plistensocket = new netnodeListenSocket(this);
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


void netnodeThread::OnApp(WPARAM wparam, LPARAM lparam)
{
	if(wparam == 122)
	{
		m_plistensocket = new netnodeListenSocket(this);
		//Sleep(15000);

      string strServer;
      int iServer;

      AStrArray straServer;
      Application.db().data_server_load(data_id("netnode"), data_id(), data_id(), straServer);

      if(straServer.get_size() > 0)
      {
         strServer = straServer[0];
      }
      else
      {
         strServer = "0.0.0.0";
      }
      iServer = 80;

		if(!m_plistensocket->Create(iServer, SOCK_STREAM, FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE 
         , strServer))
		{
			DWORD dw = ::GetLastError();
			TRACE("error %u", dw);
         Application.simple_message_box("Port 80 in use");
			AfxGetApp()->PostThreadMessage(WM_APP, 3, 0);
			return;
		}
		if(!m_plistensocket->Listen())
		{
			DWORD dw = ::GetLastError();
			TRACE("error %u", dw);
			AfxGetApp()->PostThreadMessage(WM_APP, 3, 1);
			return;
		}
	}
	else if(wparam == 1)
	{
		netnodeListenSocket * plistensocket = (netnodeListenSocket *) lparam;
		netnodeSocket * psocket = new netnodeSocket(get_app());
		//CSingleLock sl(&m_csNetNodeSocket);
		plistensocket->Accept(*psocket);
	}
	if(wparam == 122)
	{
		m_bInitialized = true;
		m_evInitialized.SetEvent();
	}
	else if(wparam == 1)
	{
		::PostThreadMessage(m_pi.dwThreadId, WM_APP, 1, 0);
	}
	else if(wparam == 2)
	{
		m_pnext->PostThreadMessageA(WM_APP, 1, 0);
	}
/*   else if(wparam == 3)
   {
	   netnodeApp * papp = dynamic_cast < netnodeApp * > (AfxGetApp());
      papp->edgify_app(0, &typeid(bergedgeApp));
   }*/
}

BOOL netnodeThread::PreTranslateMessage(LPMSG lpmsg)
{
   if(lpmsg->message == (WM_APP + 1234) && lpmsg->hwnd == NULL)
   {
   }
   return thread::PreTranslateMessage(lpmsg);
}
