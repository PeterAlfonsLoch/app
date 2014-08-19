#include "framework.h"


class keep_event_reset
{
public:
   
   
   event * m_pevent;
   
   
   keep_event_reset(event * pevent)
   {
      m_pevent = pevent;
      pevent->ResetEvent();
   }
   ~keep_event_reset()
   {
      m_pevent->SetEvent();
   }
   
   
};


namespace mac
{

   
   window_draw::window_draw(::axis::application * papp) :
   element(papp),
   ::thread(papp),
   ::user::window_draw(papp),
   message_queue(papp),
   m_mutexRendering(papp),
   m_mutexRgnUpdate(papp),
   m_semaphoreBuffer(papp),
   m_mutexRender(papp),
   m_wndpaOut(papp)
   {
      m_dwLastRedrawRequest = ::get_tick_count();
      m_bRender = false;
//      m_pbuffer = new user::buffer(papp);
//      m_pbuffer->m_spdib.create(allocer());
      m_dwLastUpdate = false;
      m_bProDevianMode = true;
      
   }
   
   extern void _001DeferPaintLayeredWindowBackground(void * hwnd, ::draw2d::graphics * pdc);
   window_draw::~window_draw()
   {
      
      //      ::DestroyWindow((oswindow) m_spwindowMessage->Detach());
      
   }
   
   
   
   /*
    void window_draw::OnPaint(void * hwnd, CPaintDC & spgraphics)
    {
    UNREFERENCED_PARAMETER(hwnd);
    UNREFERENCED_PARAMETER(spgraphics);
    }
    */
   
   void window_draw::message_queue_message_handler(signal_details * pobj)
   {
      SCAST_PTR(::message::axis, pbase, pobj);
      if(pbase->m_uiMessage == (WM_USER + 1984 + 1977))
      {
         _synch_redraw();
      }
   }
   
   void window_draw::asynch_redraw()
   {
      DWORD dwTick = ::get_tick_count();
      if(m_iFramesPerSecond == 0)
      {
         if(dwTick - m_dwLastUpdate < 1000)
            return;
      }
      else
      {
         if(dwTick - m_dwLastUpdate < 1000 / m_iFramesPerSecond)
            return;
      }
      _asynch_redraw();
   }
   
   void window_draw::_asynch_redraw()
   {
      if(!m_bProDevianMode)
      {
         m_spuiMessage->post_message(WM_USER + 1984 + 1977);
      }
   }
   
   void window_draw::synch_redraw()
   {
      
      /*      if(!m_bProDevianMode && ::IsWindow((oswindow) m_spwindowMessage->get_os_data()))
       {
       m_spwindowMessage->send_message(WM_USER + 1984 + 1977);
       }*/
   }
   
   void window_draw::_synch_redraw()
   {
      
      keep_event_reset keepeventreset(&m_eventFree);
      
      static DWORD s_dwLastAnalysisFrame = 0;
      static DWORD s_dwLastFrameFrame = 0;
      static DWORD s_iAnalysisFrameFailureCount = 0;
      static DWORD s_iFrameFailureCount = 0;
      DWORD iFailureTime;
      if(m_iFramesPerSecond == 0)
      {
         iFailureTime = 1000 / 12;
      }
      else
      {
         iFailureTime = 1000 / m_iFramesPerSecond;
      }
      m_dwLastUpdate = ::get_tick_count();
      UpdateBuffer();
      return;
//      if(m_pbuffer->GetBuffer()->get_os_data() != NULL)
  //    {
         //m_pbuffer->m_spdib->fill_channel(255, visual::rgba::channel_alpha);
         //ScreenOutput();
    //  }
      DWORD dwTakeTime = ::get_tick_count() - m_dwLastUpdate;
      m_dwLastDelay = dwTakeTime;
      if(dwTakeTime > iFailureTime)
      {
         s_dwLastAnalysisFrame += dwTakeTime;
         s_dwLastFrameFrame += dwTakeTime;
         TRACE("window_draw::_synch_redraw :: System has exceeded prodevian performance failure time - %d milliseconds", iFailureTime);
         TRACE("window_draw::_synch_redraw :: took - %d milliseconds", dwTakeTime);
         s_iAnalysisFrameFailureCount++;
         DWORD iTimeFrame = 2000;
         DWORD iMaxFailureCount = 3;
         if(s_dwLastAnalysisFrame > iTimeFrame ||
            dwTakeTime > (iFailureTime * iMaxFailureCount))
         {
            s_dwLastAnalysisFrame = 0;
            if(s_iAnalysisFrameFailureCount > iMaxFailureCount
               || (dwTakeTime > (iFailureTime * iMaxFailureCount)))
            {
               s_iFrameFailureCount++;
            }
            s_iAnalysisFrameFailureCount = 0;
         }
         DWORD iMaxFrameFailureCount = 3;
         DWORD iFrameTimeFrame = iTimeFrame * iMaxFrameFailureCount;
         if(s_dwLastFrameFrame > iFrameTimeFrame)
         {
            s_dwLastFrameFrame = 0;
            if(s_iFrameFailureCount > iMaxFailureCount)
            {
               TRACE("window_draw::_synch_redraw :: during prodevian Performance Analysis Time Frame - %d milliseconds -,", iTimeFrame);
               TRACE("window_draw::_synch_redraw :: failure count has exceeded the maximum count - %d", iMaxFailureCount);
               TRACE("window_draw::_synch_redraw :: Going to try to save some resource that may favor drawing perfomance");
               if(!Session.savings().is_trying_to_save(::axis::resource_blur_background))
               {
                  TRACE("window_draw::_synch_redraw :: System is not trying to save \"blur background\" resource");
                  TRACE("window_draw::_synch_redraw :: Going to try to save \"blur background\" resource");
                  Session.savings().try_to_save(::axis::resource_blur_background);
               }
               else if(!Session.savings().is_trying_to_save(::axis::resource_blurred_text_embossing))
               {
                  TRACE("window_draw::_synch_redraw :: System is not trying to save \"blurred text embossing\" resource");
                  TRACE("window_draw::_synch_redraw :: Going to try to save \"blurred text embossing\" resource");
                  Session.savings().try_to_save(::axis::resource_blurred_text_embossing);
               }
               else if(!Session.savings().is_warning(::axis::resource_processing))
               {
                  TRACE("window_draw::_synch_redraw :: System is not warning to save \"processing\" resource");
                  TRACE("window_draw::_synch_redraw :: Going to warn to save \"processing\" resource");
                  Session.savings().warn(::axis::resource_processing);
               }
               else if(!Session.savings().is_trying_to_save(::axis::resource_processing))
               {
                  TRACE("window_draw::_synch_redraw :: System is not trying to save \"processing\" resource");
                  TRACE("window_draw::_synch_redraw :: Going to try to save \"processing\" resource");
                  Session.savings().try_to_save(::axis::resource_blur_background);
               }
            }
            s_iFrameFailureCount = 0;
         }
         
      }
   }
   
   
   int32_t window_draw::run()
   {
      return RedrawProc();
   }
   
   
   bool window_draw::pre_run()
   {
      
      if(!create_message_queue("ca2::twf - ca2 Transparent Window Framework"))
      {
         
         TRACE("Could not initialize ca2::twf - ca2 Transparent Window Framework!");
         
         return 0;
         
      }
      
      return true;
      
   }
   
   
   UINT window_draw::RedrawProc()
   {
      MESSAGE msg;
      while(m_bRun && ::get_thread()->m_bRun)
      {
         try
         {
            if(m_bProDevianMode)
            {
               _synch_redraw();
            }
         }
         catch(...)
         {
         }
         //         while(::PeekMessage(&msg, ::caNULL, NULL, NULL, PM_NOREMOVE))
         while(::PeekMessage(&msg, NULL, 0, 0, 0))
         {
            ::get_thread()->pump_message();
         }
         int32_t iUiDataWriteWindowTimeForTheApplicationInThisMachine = 8;
         if(m_iFramesPerSecond == 0)
         {
            Sleep(1000);
         }
         else if((1000 / m_iFramesPerSecond) > m_dwLastDelay)
         {
            Sleep(max((DWORD) max(0, iUiDataWriteWindowTimeForTheApplicationInThisMachine), (1000 / m_iFramesPerSecond) - m_dwLastDelay));
         }
         else
         {
            Sleep(iUiDataWriteWindowTimeForTheApplicationInThisMachine);
         }
      }
      //delete this;
      return 0;
   }
   
   DWORD g_dwLastWindowDraw;
   // lprect should be in screen coordinates
   bool window_draw::UpdateBuffer()
   {
      
       
       if(m_bRender)
         return false;
      
       single_lock sl(&m_mutexRender, FALSE);
      
       if(!sl.lock(duration::zero()))
         return false;

       keep<bool> keepRender(&m_bRender, true, false, true);
      
      user::interaction_ptr_array wndpa(get_app());
      
      wndpa = get_wnda();
      
      rect rectWindow;

       rect rect9;
      
      user::oswindow_array wndaApp;
      
      m_wndpaOut.remove_all();
      
      
      for(int32_t l = 0; l < wndpa.get_count();)
      {
         try
         {
            if(wndpa[l].oprop("session").is_new())
            {
               wndpa[l]._001UpdateWindow();
            }
            l++;
         }
         catch(simple_exception & se)
         {
            if(se.m_strMessage == "no more a window")
            {
               System.frames().remove(&wndpa[l]);
               wndpa.remove_at(l);
               
            }
         }
         catch(...)
         {
            System.frames().remove(&wndpa[l]);
            wndpa.remove_at(l);
         }
      }
      return true;
      
      for(index j = wndaApp.get_upper_bound(); j >= 0; j--)
      {
         oswindow hwndTopic = wndaApp[j];
         
          ::user::interaction * pwnd = NULL;
         //::window * pwnd = dynamic_cast < ::window * > (System.window_map().get((int_ptr) hwndTopic));
         //if(pwnd == NULL)
         //{
         for(int32_t l = 0; l < wndpa.get_count(); l++)
         {
            if(wndpa[l].get_safe_handle() == hwndTopic)
            {
                pwnd = dynamic_cast < ::user::interaction * > (&wndpa[l]);
               break;
            }
         }
         if(!::IsWindowVisible((oswindow) wndaApp[j]) || ::IsIconic((oswindow) wndaApp[j]) || pwnd == NULL)
            continue;
         
         
      }
      
      
      return true;
   }
   
   
   
   user::interaction_ptr_array window_draw::get_wnda()
   {
      
      return System.frames();
      
   }
   
   
} // namespace mac



