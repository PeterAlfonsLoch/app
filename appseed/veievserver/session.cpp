#include "StdAfx.h"

namespace veievserver
{

   session::session(::ca::application * papp):
      ca(papp),
      m_dibUser(get_app()),
      m_dibScreen(get_app()),
      m_dibDiff(get_app()),
      m_dibFrame(get_app())
   { 
      m_pbergedge         = NULL;
      m_pframe       = NULL;
      m_bDrawCursor  = true;
   }


   void session::initialize()
   {
      m_iFrameCount     = 1;
      m_iFrame          = 0;
      start_bergedge start;

      start.m_pbergedge = new bergedge::bergedge;
      m_pbergedge = start.m_pbergedge;
      m_pbergedge->m_bSessionSynchronizedCursor  = false;
      m_pbergedge->m_bSessionSynchronizedScreen  = false;

      m_pbergedge->set_app(get_app());

      start.m_hEventReady = ::CreateEventA(NULL, TRUE, FALSE, NULL);

      AfxBeginThread(get_app(), ThreadProcStart, (LPVOID) &start);

      ::WaitForSingleObject(start.m_hEventReady, (1984 * 1977) * 20);

      ::DeleteObject(start.m_hEventReady);

      m_pframe = dynamic_cast < bergedge::frame * > (m_pbergedge->get_document()->get_bergedge_view()->GetParentFrame());

      
      App(m_pbergedge).GetThread()->SetMainWnd(m_pframe);
      m_pframe->m_bCustomFrame = false;
      m_pframe->layout();
   }

   void session::take_screenshot()
   {
      CSingleLock slSnaphost(&m_mutexSnapshot, TRUE);

      if(m_pbergedge->get_document()->get_bergedge_view() == NULL)
         return;

      rect rectScreen;
      rectScreen = m_pbergedge->m_rectScreen;

      rect rectDesk;
      m_pbergedge->get_screen_rect(rectDesk);


      m_dibScreen->create(rectScreen.width(), rectScreen.height());

      ::ca::dib_sp dib(get_app());
      try
      {
         try
         {
            m_dibScreen->create(rectScreen.size());
            m_dibUser->create(rectScreen.size());
            m_dibDiff->create(rectScreen.size());
            dib->create(rectDesk.size());
            m_pframe->_000OnDraw(dib->get_graphics());
            rect rectWindow;
            m_pframe->GetWindowRect(rectWindow);
            dib->get_graphics()->SetViewportOrg(null_point());
            dib->get_graphics()->SelectClipRgn(NULL);
            //dib->get_graphics()->FillSolidRect(300, 300, 100, 100, RGB(255, 0, 0));
            if(m_bDrawCursor)
            {
               point ptCursor;
               m_pbergedge->get_cursor_pos(&ptCursor);
               ::visual::cursor * pcursor = m_pbergedge->get_cursor();
               pcursor->to(dib->get_graphics(), ptCursor); 
               //dib->get_graphics()->TextOut(ptCursor.x, ptCursor.y, "Exception");
            }
            m_dibScreen->from(null_point(), dib->get_graphics(), rectWindow.top_left(), rectScreen.size());
         }
         catch(...)
         {
            m_dibScreen->get_graphics()->TextOut(100, 100, "Exception");
         }
      }
      catch(...)
      {
      }

      class size size = m_pbergedge->m_rectScreen.size();

   }

   void session::PostMessage(UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {

      MSG * pmsg = new MSG;
      pmsg->message = uiMessage;
      pmsg->wParam = wparam;
      pmsg->lParam = lparam;
      UINT message = WM_APP+1;
      m_pframe->SendMessage(WM_APP + 1, 0, (LPARAM) pmsg);

   }


   UINT AFX_CDECL session::ThreadProcStart(LPVOID lpv)
   {
      
      start_bergedge * pstart = (start_bergedge *) lpv;

      ::bergedge::bergedge * papp = pstart->m_pbergedge;

      if(!papp->InitApplication())
         return 0;
      
      if(!papp->process_initialize())
         return 0;
      
      papp->command_line().m_varQuery["show_platform"] = 1;
      
     papp->command_line().m_varQuery["show_platform"] = 1;

      if(!papp->initialize_instance())
         return 0;

      papp->m_psystem->get_twf()->m_bRun = false;
      win::thread * pthread = dynamic_cast < win::thread *> (App(papp).smart_pointer < ::ca::thread > ::m_p);
      win::thread * pthreadCur = dynamic_cast < win::thread *> (App(papp).GetThread()->m_p);
      pthread->m_hThread = pthreadCur->m_hThread;
      pthread->m_nThreadID = pthreadCur->m_nThreadID;

      

      
/*      if(!papp->bergedge_start())
         return 0;*/


      if(papp->does_launch_window_on_startup())
      {
         int iRetry = 100;
         while(papp->m_pwndMain == NULL && (iRetry > 0))
         {
            Sleep(100);
            iRetry--;
         }
         if(papp->m_pwndMain != NULL)
         {
//            papp->m_pwndMain->SetParent(pview);
            papp->m_pwndMain->ModifyStyle(0, WS_CHILD);
            papp->m_pwndMain->SetWindowPos(NULL, 0, 0, 400, 400, SWP_SHOWWINDOW);
         }
      }

      ::SetEvent(pstart->m_hEventReady);

      try
      {
         papp->run();
      }
      catch(...)
      {
      }

      int iExitCode = -1;

      try
      {
         iExitCode = papp->exit_instance();
         papp->m_psystem->log().trace("Exit Code from retract_app %d (exit_instance %s)", iExitCode, typeid(*papp).raw_name());
      }
      catch(...)
      {
      }
   
      try
      {
         delete papp;
      }
      catch(...)
      {
      }

      return iExitCode;
   }

} // namespace veievserver