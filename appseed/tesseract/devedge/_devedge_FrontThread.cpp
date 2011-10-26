#include "StdAfx.h"
#include "devedgeFrontThread.h"

void CLASS_DECL_CA2_TESSERACT KickDevEdgeFront(::ca::application * papp)
{
   AfxBeginThread < devedgeFrontThread > (papp);   
}

devedgeFrontThread::devedgeFrontThread(::ca::application * papp)
: thread(papp)
{
   m_evInitialized.ResetEvent();
   m_bInitialized = false;

   //m_plistensocket = NULL;
}

devedgeFrontThread::~devedgeFrontThread()
{
}


void devedgeFrontThread::install_message_handling(::user::win::message::dispatch * pinterface)
{
   IGUI_WIN_MSG_LINK(WM_APP, pinterface, this, &devedgeFrontThread::OnApp);
}


bool devedgeFrontThread::initialize_instance()
{

   int iCount = 2;
   int i;
   for(int i = 0; i < iCount; i++)
   {
//   devedgeSocketThread * pthread = AfxBeginThread < devedgeSocketThread >(get_app());
//      m_ptrathread.add(pthread);
   }
   int iCount2 = iCount - 1;
   for(i = 0; i < iCount2; i++)
   {
//   m_ptrathread[i]->m_pnext = m_ptrathread[i + 1];
   }
//   m_ptrathread[i]->m_pnext = m_ptrathread[0];

//   m_pthreadCurrent = m_ptrathread[0];

   PostThreadMessage(WM_APP, 0, 0);


/*   STARTUPINFO startupinfo;
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


//   m_hChildThreadId = ::OpenThread(THREAD_ALL_ACCESS, TRUE, m_pi.dwThreadId);

   ::PostThreadMessage(m_pi.dwThreadId, WM_APP, 0, m_nThreadID);

   PostThreadMessage(WM_APP, 0, 0);*/

   
   //PostThreadMessage(WM_APP, 0, 0);


/*   m_plistensocket = new devedgeListenSocket(this);
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
   return true;
}


void devedgeFrontThread::OnApp(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj);
   if(pbase->m_wparam == 0)
   {
/*   m_plistensocket = new devedgeListenSocket(this);
      //Sleep(15000);
      if(!m_plistensocket->create(10011, SOCK_STREAM))
      {
         DWORD dw = ::GetLastError();
         TRACE("error %u", dw);
         System.PostThreadMessage(WM_APP, 3, 0);
         return;
      }
      if(!m_plistensocket->Listen())
      {
         DWORD dw = ::GetLastError();
         TRACE("error %u", dw);
         System.PostThreadMessage(WM_APP, 3, 1);
         return;
      }*/
   }
   else if(pbase->m_wparam == 1)
   {
//   devedgeListenSocket * plistensocket = (devedgeListenSocket *) pbase->m_lparam;
//      devedgeSocket * psocket = new devedgeSocket(plistensocket);
      //single_lock sl(&m_csNetNodeSocket);
//   plistensocket->Accept(*psocket);
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
   else if(pbase->m_wparam == 2)
   {
      m_pnext->PostThreadMessageA(WM_APP, 1, 0);
   }
}